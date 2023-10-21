cmake_minimum_required(VERSION 3.00)
project(EntregaPractica3 C)
set (compilador GCCa)

if(compilador STREQUAL "GCC")
    SET(CMAKE_C_COMPILER /usr/bin/gcc)
else ()
    SET(CMAKE_C_COMPILER /usr/bin/clang)
endif()

set(CMAKE_CXX_FLAGS -Wall -Wextra -Werror -pedantic -Wconversion)

set(CMAKE_C_STANDARD 11)

add_executable(EntregaPractica3 main.c lista.c lista.h abb.c abb.h
        vacunodromo.h vacunodromo.c cola.h cola.c)
