#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void printId()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("uid: %d, euid: %d\n", uid, euid);
}

void dropPriviledges()
{
    seteuid(getuid());
}

void escalatePriviledges()
{
    seteuid(0);
}

void openfile()
{
    FILE* f = fopen("/etc/shadow", "r");
    if (f == NULL)
    {
        perror("fopen");
        return;
    }
    else
    {
        printf("ACCESS OK!\n");
    }
    // char c;
    // while ((c = getc(f)) != EOF)
    //     putchar(c);
    fclose(f);
}

void executeSubProcess(const char* executable)
{
    //system(executable);
    //return;


    auto cpid = fork();
    if (cpid < 0)
    {
        perror("fork");
        exit(-1);
    }
    if (cpid == 0) // child
    {
        printf("CHILD start\n");
        printId();
        openfile();

        execl(executable, "");
        //execve("/bin/sh", ["sh", "-c", executable]);
        printf("CHILD end\n");
    }
    else
    {
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
}


int main()
{
    printf("####default\n");
    printId();
    openfile();

    printf("######## start TRYESCALATION\n");
    executeSubProcess("./tryEscalation");
    printf("######## end TRYESCALATION\n");

    printf("####drop\n");
    dropPriviledges();
    printId();
    openfile();

    printf("######## start TRYESCALATION\n");
    executeSubProcess("./tryEscalation");
    printf("######## end TRYESCALATION\n");

    printId();
    printf("####escalate\n");
    escalatePriviledges();
    printId();
    openfile();

    printf("######## start TRYESCALATION\n");
    executeSubProcess("./tryEscalation");
    printf("######## end TRYESCALATION\n");

}
