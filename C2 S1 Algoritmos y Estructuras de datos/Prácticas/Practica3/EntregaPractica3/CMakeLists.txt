cmake_minimum_required(VERSION 3.00)
project(EntregaPractica3 C)

set(CMAKE_C_STANDARD 11)

add_executable(EntregaPractica3 main.c lista.c lista.h abb.c abb.h
        vacunodromo.h vacunodromo.c cola.h cola.c)
