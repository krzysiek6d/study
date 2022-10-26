#include <stdio.h>

static bool component()
{
    printf("Hello from component\n");
    return true;
}

static bool isinitialized = component();