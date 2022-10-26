main includes libB which in public headers includes libA

that;s why linking libA with libB should be public

check libB_which_uses_libA/CMakeLists.txt