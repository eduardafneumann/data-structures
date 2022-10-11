#ifndef LISTA_H
#define LISTA_H

#include "vertice.h"
#include "item.h"
#include <stdbool.h>

typedef struct lista_ LISTA;

int lista_tamanho(LISTA *lista);
bool lista_vazia(LISTA *lista);
bool lista_cheia(LISTA *lista);
LISTA *lista_criar(int tamanho);
bool lista_apagar(LISTA **lista);
bool lista_inserir(LISTA *lista, VERTICE *vertice);
void lista_imprimir(LISTA *lista);
VERTICE *lista_get_vertice(LISTA *lista, int indice);

#endif