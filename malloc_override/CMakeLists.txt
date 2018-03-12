cmake_minimum_required(VERSION 3.4)
project(malloc_override)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb -O0 -rdynamic")

set(SOURCE_FILES main.cpp malloc_overloaded.cpp)
add_executable(malloc_override ${SOURCE_FILES})
target_link_libraries(malloc_override dl)