cmake_minimum_required(VERSION 3.21)
project(P1_V3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(P1_V3
        main.c
        vectordinamico.c
        vectordinamico.h)
