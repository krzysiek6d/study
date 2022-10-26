cmake_minimum_required(VERSION 3.22)
project(static_execution_in_another_lib)

add_subdirectory(my_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(static_execution_in_another_lib main.cpp)
target_link_libraries(static_execution_in_another_lib component)
