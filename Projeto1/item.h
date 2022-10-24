/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>
#include <stddef.h>

typedef struct item_ ITEM;

ITEM *item_criar(int chave);
bool item_apagar(ITEM **item);
int item_get_chave(ITEM *item);
bool item_set_chave(ITEM *item, int chave);
void item_imprimir(ITEM *item);
size_t item_size();

#endif
