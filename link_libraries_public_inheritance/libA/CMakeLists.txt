add_library(libA)
target_sources(libA PRIVATE libA.cpp)
target_include_directories(libA PUBLIC include)