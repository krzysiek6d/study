#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    const int PARENT_SLEEP = 20;
    const int CHILD_SLEEP = PARENT_SLEEP/ 2;
    std::cout << "hello " << getpid() << std::endl;

    pid_t cpid;
    if ((cpid = fork()) < 0)
    {
        std::cout << "cant fork";
    }
    else if (cpid == 0)
    {
        std::cout << "child: my pid: " << getpid() << std::endl;
        std::cout << "child: my parent pid: " << getppid() << std::endl;
        std::cout << "child: go sleep for " << CHILD_SLEEP << "sec" << std::endl;
        sleep(10);
        std::cout << "child: woke up, parent is still blocked by sleep, I'll exit in a moment and become a ZOMBIE" << std::endl;
    }
    else
    {
        std::cout << "parent: my pid: " << getpid() << std::endl;
        std::cout << "parent: go sleep for " << PARENT_SLEEP << "sec" << std::endl;
        sleep(20);
        std::cout << "parent: woke up " << std::endl;
        int status;
        do {
            int w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
            if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

           if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    std::cout << "bye " << getpid() << std::endl;

    return 0;
}