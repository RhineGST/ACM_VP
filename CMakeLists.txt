cmake_minimum_required(VERSION 3.25)
project(ACM_VP)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wl,--stack=268435456)

add_executable(ACM_VP main.cpp)
