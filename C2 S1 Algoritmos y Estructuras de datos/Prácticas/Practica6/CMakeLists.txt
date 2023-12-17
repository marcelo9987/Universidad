cmake_minimum_required(VERSION 3.26)
project(Practica6 C)

set(CMAKE_C_STANDARD 11)


add_executable(backtracking
        parte1_backtracking/main.c
        parte2_RYP/common.h
        parte1_backtracking/lista.h
        parte1_backtracking/lista.c
        parte1_backtracking/backtracking.h
        parte1_backtracking/backtracking.c
        parte1_backtracking/backtrackingConUsadas.h
        parte1_backtracking/backtrackingConUsadas.c
)

add_executable(ramificacionYPoda
        parte2_RYP/main.c
        parte2_RYP/common.h
        parte2_RYP/lista.h
        parte2_RYP/lista.c
        parte2_RYP/ramificacionYpoda.h
        parte2_RYP/ramificacionYpoda.c
        parte2_RYP/estimacionesTriviales.h
        parte2_RYP/estimacionesTriviales.c
        parte2_RYP/estimacionesPrecisas.h
        parte2_RYP/estimacionesPrecisas.c
)

add_executable(ramificacionYPoda_minimizacion
        parte2_RYP_minimizacion/main.c
        parte2_RYP_minimizacion/common.h
        parte2_RYP_minimizacion/lista.h
        parte2_RYP_minimizacion/lista.c
        parte2_RYP_minimizacion/ramificacionYpoda.h
        parte2_RYP_minimizacion/ramificacionYpoda.c
        parte2_RYP_minimizacion/estimacionesTriviales.h
        parte2_RYP_minimizacion/estimacionesTriviales.c
        parte2_RYP_minimizacion/estimacionesPrecisas.h
        parte2_RYP_minimizacion/estimacionesPrecisas.c
        parte2_RYP_minimizacion/estimacionesPrecisas.c
)

