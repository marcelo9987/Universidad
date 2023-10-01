cmake_minimum_required(VERSION 3.22.1)
project(EntregaSesion2 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(EntregaSesion2 main.c FuncionesExpresion.c FuncionesExpresion.h pila.c pila.h abin.c abin.h recorridos.c recorridos.h
        pilaOperadores.c
        pilaOperadores.h
        pilaOperandos.c
        pilaOperandos.h)
