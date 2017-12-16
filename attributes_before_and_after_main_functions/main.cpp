#include <stdio.h>

__attribute__((__constructor__))
void ctor()
{
    printf("hello c-tor!\n");
}

__attribute__((__destructor__))
void dtor()
{
    printf("hello d-tor!\n");
}


int main()
{
    printf("hello main!\n");
}
