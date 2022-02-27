cmake_minimum_required(VERSION 3.21)
project(Practica_1_V0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Practica_1_V0
        main.c
        vectordinamico.c
        vectordinamico.h)
