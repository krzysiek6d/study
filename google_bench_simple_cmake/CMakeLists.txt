cmake_minimum_required(VERSION 3.14)
project(g_benchmark)
enable_testing()

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master)

FetchContent_MakeAvailable(
        googlebenchmark)

add_executable(g_benchmark main.cpp)
target_link_libraries(g_benchmark benchmark::benchmark)
