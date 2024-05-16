#include<iostream>
#include <stdint.h>
#include <type_traits>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

enum A : uint8_t{
    A_a = 0,
    A_b = 1,
};

enum class B : uint8_t{
	B_a = 0,
	B_b = 1,
};

template<typename T> concept IsEnum = std::is_enum_v<T>;
auto& operator<<(auto& t, IsEnum auto s)
{
    t << static_cast<int>(s);
    return t;
}

int main()
{
	{
		auto x = A::A_b;
		std::cout << "hello: " << x << std::endl;
		std::cout << "hello: " << static_cast<int>(x) << std::endl;
    }
    
    {
    	boost::optional<A> x = A::A_b;
		std::cout << "hello: " << x << std::endl;
    }
    
    {
		auto x = B::B_b;
		std::cout << "hello: " << x << std::endl;
		std::cout << "hello: " << static_cast<int>(x) << std::endl;
    }
    
    {
    	boost::optional<B> x = B::B_b;
		std::cout << "hello: " << x << std::endl;
    }
    
    uint8_t d = 4;
    std::cout << "d: " << d << std::endl;
}
