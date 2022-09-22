#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

#define ERRO_CHAR '!'

typedef struct item_ ITEM;

ITEM *item_criar(char chave);
bool item_apagar(ITEM **item);
void item_imprimir(ITEM *item);
char item_get_chave(ITEM *item);
bool item_set_chave(ITEM *item, char chave);

#endif
