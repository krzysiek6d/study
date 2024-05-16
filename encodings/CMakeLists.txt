cmake_minimum_required(VERSION 3.14)
project(encoding)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
        GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(
        fmt)

add_executable(encoding main.cpp)
target_link_libraries(encoding fmt::fmt)