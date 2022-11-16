cmake_minimum_required(VERSION 3.16)
project(Ej_3 C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-lpthread)
add_executable(Ej_3 main.c)
target_link_libraries(Ej_3 pthread)
