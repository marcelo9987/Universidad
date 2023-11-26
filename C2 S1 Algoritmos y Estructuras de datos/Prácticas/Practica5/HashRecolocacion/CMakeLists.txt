cmake_minimum_required(VERSION 3.00)
project(Practica5_recolocacion C)

set(CMAKE_C_STANDARD 11)

#include_directories(HashEncadenamiento)

add_executable(Practica5_recolocacion
        main.c
        tabla_hash_recolocacion.c
        tabla_hash_recolocacion.h)
