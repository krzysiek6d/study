#include <variant>
#include <tuple>
#include <type_traits>

#pragma once

// --- Overload helper ---
template <typename... Ts>
struct Overload : Ts... { using Ts::operator()...; };
template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

// --- Extract types from variant ---
template <typename Variant>
struct variant_types;

template <typename... Ts>
struct variant_types<std::variant<Ts...>> {
    using types = std::tuple<Ts...>;
};

// --- Check if a given T is invocable with any of the Visitors ---
template <typename T, typename... Visitors>
constexpr bool is_covered_by_visitors =
        (... || std::is_invocable_v<Visitors, T>) ||
        (... || std::is_invocable_v<Visitors, T&>) ||
        (... || std::is_invocable_v<Visitors, const T&>) ||
        (... || std::is_invocable_v<Visitors, T&&>) ||
        (... || std::is_invocable_v<Visitors, const T&&>);

// --- Compile-time check that every type in Variant is covered ---
template <typename Variant, typename... Visitors>
constexpr void static_check_coverage() {
    using Tuple = typename variant_types<std::remove_cvref_t<Variant>>::types;

    constexpr auto check = []<std::size_t... Is>(std::index_sequence<Is...>) {
        (([] {
            using T = std::tuple_element_t<Is, Tuple>;
            static_assert(is_covered_by_visitors<T, Visitors...>,
                          "Not all types of variant are covered!");
        }()), ...);
    };

    check(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

// --- visit_all wrapper ---
template <typename Variant, typename... Visitors>
decltype(auto) visit_all(Variant&& variant, Visitors&&... visitors) {
    static_check_coverage<Variant, Visitors...>();
    return std::visit(Overload{std::forward<Visitors>(visitors)...}, std::forward<Variant>(variant));
}
