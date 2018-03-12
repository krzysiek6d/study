#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void dupa2()
{
    char* text;
    text = (char*)malloc(6);
    strncpy(text, "dupa1\0", 6);
    free(text);
}


void dupa()
{

}

int main() {

    dupa2();
    return 0;
}