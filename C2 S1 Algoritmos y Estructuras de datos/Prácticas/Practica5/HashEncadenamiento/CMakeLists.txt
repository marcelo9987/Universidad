cmake_minimum_required(VERSION 3.00)
project(Practica5_encadenamiento C)

set(CMAKE_C_STANDARD 11)

include_directories(HashEncadenamiento)

add_executable(Practica5_encadenamiento
        lista.c
        lista.h
        main.c
        tabla_hash_encadenamiento.c
        tabla_hash_encadenamiento.h)
