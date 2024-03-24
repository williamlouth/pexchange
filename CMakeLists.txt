cmake_minimum_required(VERSION 3.28)
project(pexchange)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

add_executable(pexchange main.cpp)

add_subdirectory(src)
add_subdirectory(test)
