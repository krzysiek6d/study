#include <fmt/format.h>
#include <fmt/color.h>
#include <cstring>

int main() {
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");
    //fmt::print("Hello \uD83D\uDE1C");
}