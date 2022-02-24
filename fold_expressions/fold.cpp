#include <iostream>
#include <cassert>
#include <functional>

template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

template<typename Separator, typename Arg, typename ...Args>
void printer_with_separator(Separator&& sep, Arg&& arg, Args&&... args)
{
    std::cout << arg;
    ((std::cout << sep << args), ...);
    std::cout << std::endl;
}

template<typename ...Args>
constexpr bool all(Args&&... args) {
    return (... && args);
}

template<typename T, typename ...Args>
constexpr bool any_equal(T val, Args&&... args) {
    return (... || (val == args));
}

template <class F, class... Args> 
void for_each_argument(F f, Args&&... args) {
    /*[](...){}(
        (
            f(std::forward<Args>(args)), 0
        )...
    );*/
    (f(std::forward<Args>(args)), ...);
}

template<typename T, typename ...Args>
constexpr void multiply_by(T val, Args&... args) {
    
    auto m = [val](auto& v){
        v = v*val;
    };
    for_each_argument(m, args...);
}

int main()
{
    {
        printer("hello world ", 12);
        printer("asd");
    }

    {
        printer_with_separator(", ", "hello world", 12);
        printer_with_separator(", ", "asd");
    }

    {
        static_assert(all(true, true) , "err");
    }

    {
        bool a = true;
        bool b = true;
        //static_assert(all(a, b) , "err");
        assert(all(a,b));
    }

    {
        int v = 11;
        assert(!any_equal(11, 2, 3, 4));
        assert(!any_equal(11));
        assert(any_equal(11, 2, 3, 11, 2));
    }

    {
        // not really a fold expression
        double a = 2.0;
        int b = 7;
        multiply_by(4, a, b);
        assert(8.0 == a);
        assert(28 == b);
    }

}