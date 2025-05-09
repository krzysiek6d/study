
#include <string>
#include <iostream>
#include <variant>
#include <expected>

#include "visit_all.hpp"


void example1()
{
    using MyVariant = std::variant<int, float, std::string, bool>;
    MyVariant v = std::string{"hello"};

    visit_all(v,
              [](int i) { std::cout << "int: " << i << "\n"; },
              [](float f) { std::cout << "float: " << f << "\n"; },  // comment one case to see that compilation fails
              [](const std::string& s) { std::cout << "string: " << s << "\n"; },
              [](bool b) { std::cout << "bool: " << std::boolalpha << b << "\n"; }
    );
}

void example2()
{
    struct ParsingError{};
    struct InvalidCode{int code;};
    struct InvalidValue{std::string value;};
    using MsgErrors = std::variant<ParsingError, InvalidCode, InvalidValue>;
    using MsgData = std::string;

    using Msg = std::expected<MsgData, MsgErrors>;

    auto msg = Msg{"msghello"};
    std::cout << msg.value() << std::endl;

    auto msgErr = Msg{std::unexpected(InvalidCode{404})};
    visit_all(msgErr.error(),
              [](const ParsingError& e) { std::cout << "ParsingError: " << std::endl; }, // comment one case to see that compilation fails
              [](const InvalidCode& e) { std::cout << "InvalidCode: " << e.code << std::endl; },
              [](const InvalidValue& e) { std::cout << "InvalidValue: " << e.value << std::endl; }
    );
}

int main() {
    example1();
    example2();
}