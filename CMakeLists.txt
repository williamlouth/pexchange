cmake_minimum_required(VERSION 3.22)
project(pexchange)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER_LAUNCHER /usr/local/bin/recc)

add_subdirectory(external)

add_executable(pexchange main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g")

add_subdirectory(src)
add_subdirectory(test)
