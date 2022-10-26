add_library(libB_which_uses_libA)
target_sources(libB_which_uses_libA PRIVATE libB_which_uses_libA.cpp)
target_include_directories(libB_which_uses_libA PUBLIC include)

#changing to PRIVATE would fail the compilation because header will not be propagated to main
#this is just PoC. In this case include libA is not needed in header, should be moved to src

target_link_libraries(libB_which_uses_libA PUBLIC libA)