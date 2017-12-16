#include <iostream>

using namespace std;

struct str1
{
    long long a;
    int b;
};

#pragma pack(push, 1)
struct str2
{
    long long a;
    int b;
};
#pragma pack(pop)

int main()
{
    cout << "default padding: " << endl;
    cout << sizeof(str1::a) << " " << sizeof(str1::b) << " " << sizeof(str1) << endl;
    cout << "padding turned off: " << endl;
    cout << sizeof(str2::a) << " " << sizeof(str2::b) << " " << sizeof(str2) << endl;
    return 0;
}
