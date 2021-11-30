cmake_minimum_required(VERSION 3.20)
project(lasNubes_lib C)

set(CMAKE_C_STANDARD 99)

add_library(lasNubes_lib fechas.c meteo.c)
