#include <libB_which_uses_libA/libB_which_uses_libA.hpp>

#include <iostream>

void printB()
{
    std::cout << "printB" << std::endl;
    std::cout << "calling libA print..." << std::endl;
    printA();
}