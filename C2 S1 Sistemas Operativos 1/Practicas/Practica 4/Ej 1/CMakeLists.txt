cmake_minimum_required(VERSION 3.16)
project(Ej_1 C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-pthread -Wall -pedantic)
add_executable(Ej_1 main.c)
target_link_libraries(Ej_1 pthread)

