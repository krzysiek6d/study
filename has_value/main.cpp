#include <iostream>
#include <string>
#include "is_enum_present.hpp"
#include <map>

 typedef enum asd
 {
     value1,
     value2,
     value3
 } asd;


//typedef enum asd
//{
//    value1,
//    value2
//} asd;


IS_ENUM_PRESENT(value3)

template <typename T = asd>
auto get_asd_mapping() -> std::enable_if_t<enum_contains_value3<T>::value, std::map<int, std::string>>
{
    return {
            {T::value1, "str_value1"},
            {T::value2, "str_value2"},
            {T::value3, "str_value3"},
    };
}

template <typename T = asd>
auto get_asd_mapping() -> std::enable_if_t<!enum_contains_value3<T>::value, std::map<int, std::string>>
{
        return {
            {T::value1, "str_value1"},
            {T::value2, "str_value2"},
        };
}

const auto asd_mapping = get_asd_mapping();

int main()
{
    for (auto& x : asd_mapping)
    {
        std::cout << x.first << " " << x.second << std::endl;
    }
}