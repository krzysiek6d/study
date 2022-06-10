cmake_minimum_required (VERSION 3.2)
project(program_args_outside_main)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pg -g3 -w -fsanitize=address" )
add_executable(${PROJECT_NAME} main.cpp)