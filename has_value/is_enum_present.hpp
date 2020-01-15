//
// Created by pawluch on 1/15/20.
//

#ifndef IS_ENUM_PRESENT_HPP
#define IS_ENUM_PRESENT_HPP

template <typename...>
struct make_void { using type = void; };
template <typename... T>
using void_t = typename make_void<T...>::type;

#define IS_ENUM_PRESENT(field) \
template <typename T, typename=void> \
struct enum_contains_##field : std::false_type{}; \
\
template <typename T> \
struct enum_contains_##field<T, void_t<decltype(T::field)>> : std::true_type{}; \

#endif //IS_ENUM_PRESENT_HPP
