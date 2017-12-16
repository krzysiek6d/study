#include <iostream>
#include <memory>

class Base
{
    public:
        Base() : x{0} {}
        virtual void fun(int k = 3)
        {
            std::cout << "Base::fun()" << std::endl;
            x = k;
        }
        int x;
};

class Derived : public Base
{
    public:
        void fun(int k = 4) override
        {
            std::cout << "Derived::fun()" << std::endl;
            x = k;
        }
};

int main()
{
    std::unique_ptr<Base> obj = std::unique_ptr<Derived>(new Derived());
    obj->fun();
    std::cout << "value is: " << obj->x << std::endl;
    return 0;
}
