cmake_minimum_required(VERSION 3.22.1)
project(Sesion6 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(Sesion6 main.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        floydWarshall.c
        prim.c
)

add_executable(testPrim TESTS/tst_prim.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        )

add_executable(testFW TESTS/tst_fw.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        floydWarshall.c
        )
add_executable(testLeer TESTS/tst_leerArchivo.c ETSEMaps.c ETSEMaps.h grafo.c grafo.h
        ETSEMaps.c
        ETSEMaps.h
        leerArchivo.c
        )
