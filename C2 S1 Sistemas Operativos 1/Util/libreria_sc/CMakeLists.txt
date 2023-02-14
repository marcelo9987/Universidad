cmake_minimum_required(VERSION 3.24)
project(libreria_sc C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(libreria_sc
        main.c
        mfmsys.utils.c
        mfmsys.utils.h)
