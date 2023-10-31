cmake_minimum_required(VERSION 3.22.1)
project(Sesion6 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)# es una pena, pero puede que tenga que dejar caer el -Wpedantic. Es culpa de %m en el scanf.

add_executable(Sesion6 main.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
)

add_executable(testPrim tst_prim.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        )

add_executable(testFW tst_fw.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        floydWarshall.c
        )
