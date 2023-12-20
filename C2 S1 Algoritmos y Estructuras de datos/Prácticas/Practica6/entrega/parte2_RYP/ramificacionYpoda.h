//
// Created by imarc on 04/12/2023.
//
#pragma once

#include <stdbool.h>

#include "lista.h"

bool Solucion(const NODO *s);

void BE(NODO *x);

//TPOSICION Seleccionar(TLISTA *l);

void _imprimeInfoNodo(const char *const textoInicial, const NODO *const nodo);

void _insertarEnLaLista(TLISTA *listaDeNodosVivos, NODO *nodo);

void _seleccionarYeliminarDeLaLista(TLISTA *listaDeNodosVivos, NODO *nodo);

void clonaNodos(NODO *destino, const NODO *origen, const bool completo);



