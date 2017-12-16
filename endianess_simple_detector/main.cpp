#include <iostream>
union aa
{
    uint32_t i;
    uint8_t c[4];
} endianCheck = {0x04030201};


int IsLittleEndian()
{
    return endianCheck.c[0] == 1;
}

int main()
{
    IsLittleEndian() ? std::cout << "little endian\n" : std::cout << "big endian\n"; 
    return 0;
}
