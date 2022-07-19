cmake_minimum_required(VERSION 3.16)
project(proto_example)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(interface)
add_executable(proto_example main.cpp)
target_link_libraries(proto_example codec)