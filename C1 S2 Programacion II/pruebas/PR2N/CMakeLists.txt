cmake_minimum_required(VERSION 3.21)
project(Practica_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(TAD)

add_executable(Practica_2
        TAD/cola.c
        TAD/cola.h
        TAD/lista.c
        TAD/lista.h
        main.c
        vacunodromo.c
        vacunodromo.h)
