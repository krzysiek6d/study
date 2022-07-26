#include <iostream>
#include <User1.h>
#include <User2.h>

int main() {
    std::cout << User1().get() << std::endl;
    std::cout << User2().get() << std::endl;

    return 0;
}
