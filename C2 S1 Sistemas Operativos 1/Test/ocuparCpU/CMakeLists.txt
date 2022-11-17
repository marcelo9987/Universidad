cmake_minimum_required(VERSION 3.16)
project(ocuparCpU C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-lpthread)
add_executable(ocuparCpU main.c)
target_link_libraries(ocuparCpU pthread)
