cmake_minimum_required(VERSION 3.22)
project(link_libraries_public_inheritance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0")

add_subdirectory(libA)
add_subdirectory(libB_which_uses_libA)

add_executable(link_libraries_public_inheritance main.cpp)
target_link_libraries(link_libraries_public_inheritance libB_which_uses_libA)