//
// Created by imarc on 04/12/2023.
//

#pragma once

#include "lista.h"
#include <stdbool.h>



void AsignacionTrivial(int B[N][N], NODO *const solucion, int *const nNodos);
//void AsignacionTrivial(int B[N][N], int solucion[N], int *const nNodos);

void AsignacionPrecisa(int B[N][N], NODO *const solucion, int *const nNodos);

bool Solucion(NODO s);

