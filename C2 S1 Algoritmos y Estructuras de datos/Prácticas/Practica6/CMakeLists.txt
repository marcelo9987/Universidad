cmake_minimum_required(VERSION 3.26)
project(Practica6 C)

set(CMAKE_C_STANDARD 11)

add_executable(backtracking mainBacktracking.c
        backtracking.c
        backtracking.h
        backtrackingConUsadas.c
        backtrackingConUsadas.h
        common.h
)

add_executable(ramificacionYPoda mainRamificacionYPoda.c
        lista.c
        lista.h
        ramificacionYpoda.c
        ramificacionYpoda.h
        common.h

    )

