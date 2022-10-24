/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include "lista.h"

typedef struct grafo_ GRAFO;

GRAFO *grafo_criar(int n_vertices);
void grafo_apagar(GRAFO *grafo);
void grafo_inserir(GRAFO *grafo, int origem, int destino, int peso);
LISTA *grafo_get_lista(GRAFO *grafo, int indice);
int grafo_tamanho(GRAFO *grafo);
void grafo_imprimir(GRAFO *grafo);

#endif