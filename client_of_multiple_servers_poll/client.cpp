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
#include <poll.h>
#include <signal.h>

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


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "please provide tcp ports to connect" << std::endl;
        return 0;
    }
    std::vector<pollfd> fds;

    for (int i = 1; i < argc; i++)
    {
        int port = std::stoi(argv[i]);
        auto sockfd = net::socket();
        net::connect(sockfd, port);

        pollfd fdp{};
        fdp.fd = sockfd;
        fdp.events = POLLIN;
        fds.push_back(fdp);

        printf ("Setup fd number %d \n",sockfd);
    }

    while(!fds.empty())
    {
        if (poll(fds.data() , fds.size(), 5 * 1000) < 0) { 
            perror("poll");
            continue;
        }
        for (int i = fds.size() - 1; i >=0 ; i--) // for easy removal
        {
            if (fds[i].revents & POLLIN)
            {
                try
                {
                    auto data = net::recv(fds[i].fd);
                    std::cout << "received: " << data;
                }
                catch(const std::runtime_error& e)
                {
                    std::cerr << e.what() << '\n';
                    close(fds[i].fd);
                    fds.erase(fds.begin() + i);
                }
            }
        }
    }

}