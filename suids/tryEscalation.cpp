#include <iostream>
#include <unistd.h>

void printId()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("    uid: %d, euid: %d\n", uid, euid);
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
        perror("    fopen");
        return;
    }
    else
    {
        printf("    ACCESS OK!\n");
    }
    // char c;
    // while ((c = getc(f)) != EOF)
    //     putchar(c);
    fclose(f);
}

int main()
{
    printf("    ############## START SYSTEM\n");
    printf("    ####default\n");
    printId();
    openfile();

    printf("    ####drop\n");
    dropPriviledges();
    printId();
    openfile();

    printId();
    printf("    ####escalate\n");
    escalatePriviledges();
    printId();
    openfile();
    printf("    ############## END SYSTEM\n");
    fflush(NULL);

}
