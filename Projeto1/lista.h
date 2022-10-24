/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#ifndef LISTA_H
#define LISTA_H

#include "vertice.h"
#include "item.h"
#include <stdbool.h>

typedef struct lista_ LISTA;

LISTA *lista_criar(int tamanho);
bool lista_apagar(LISTA **lista);
bool lista_inserir(LISTA *lista, VERTICE *vertice); // a operção de remoção não será utilizada
int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);
VERTICE *lista_get_vertice(LISTA *lista, int indice);

#endif