#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

namespace net
{
    int socket()
    {
        int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            printf("socket creation failed...\n");
            exit(-1);
        }
        return sockfd;
    }

    void connect(int sockfd, unsigned short port)
    {
        sockaddr_in servaddr{};
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
        servaddr.sin_port = ::htons(port);

        if (::connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
            perror("connect failed");
            exit(-1);
        }
        printf("connected successfully to %hu\n", port);
    }

    std::string recv(int sockfd)
    {
        std::string result;
        while (true)
        {
            const int NULL_VALUE = 0;
            char buf[10] = {};
            int bytes = ::recv(sockfd, buf, sizeof(buf), NULL_VALUE);
            if (bytes < 0)
            {
                perror("recv failed");
                exit(-1);
            }
            if (bytes == 0)
            {
                throw std::runtime_error("connection closed by peer");
            }
            std::string data(buf);
            result += data;
            
            if (buf[bytes-1] == '\n')
                break;
        }
        return result;
    }
}

namespace mplx
{
    bool isSetEmpty(int max_fd, fd_set& set)
    {
        bool isSetEmpty = true;
        for (int i = 0; i < max_fd+1; i++)
        {
            if (FD_ISSET(i, &set))
            {
                isSetEmpty = false;
                break;
            }
        }
        return isSetEmpty;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "please provide tcp ports to connect" << std::endl;
        return 0;
    }
    std::vector<int> sockets;

    fd_set master_set, readfds;
    FD_ZERO(&readfds);
    int max_fd;

    for (int i = 1; i < argc; i++)
    {
        int port = std::stoi(argv[i]);
        auto sockfd = net::socket();
        net::connect(sockfd, port);

        max_fd = sockfd;
        FD_SET(sockfd, &master_set);
        printf ("Setup fd number %d \n",sockfd);
    }

    while(true)
    {
        if (mplx::isSetEmpty(max_fd, master_set))
            break;

        struct 	timeval tv;
        tv.tv_sec = 5;
        memcpy(&readfds, &master_set, sizeof(master_set));
        if (select(max_fd+1 , &readfds, NULL, NULL, &tv) < 0) { 
            perror("select");
            continue;
        }
        for (int i = 0; i < max_fd+1; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                try
                {
                    auto data = net::recv(i);
                    std::cout << "received: " << data;
                }
                catch(const std::runtime_error& e)
                {
                    std::cerr << e.what() << '\n';
                    FD_CLR(i, &master_set);
                    close(i);
                }
            }
        }
    }

}