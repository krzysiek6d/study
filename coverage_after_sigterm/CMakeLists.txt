cmake_minimum_required(VERSION 3.14)
project(covsig)

set(CMAKE_CXX_FLAGS "--coverage -O0")
add_executable(covsig main.cpp)


add_custom_target(
        coverage
        COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -name "*gcda" | xargs rm
        #COMMAND timeout -s 9 5 ./covsig || echo "SIGKILL sent!"
        COMMAND timeout 5 ./covsig || echo "## SIGTERM sent! ##"

        COMMAND gcovr --html-details --html-theme github.dark-blue -o index.html -r ..
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS covsig
        VERBATIM
        COMMENT Running app with coverage
        )
