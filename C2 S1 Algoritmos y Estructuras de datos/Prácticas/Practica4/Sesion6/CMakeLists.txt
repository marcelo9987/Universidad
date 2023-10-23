cmake_minimum_required(VERSION 3.22.1)
project(Sesion6 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(Sesion6 main.c funciones.c funciones.h grafo.c grafo.h)

