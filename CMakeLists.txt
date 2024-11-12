cmake_minimum_required(VERSION 3.25)
project(ACM_VP)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wl,--stack=1073741824)

add_executable(ACM_VP main.cpp)
