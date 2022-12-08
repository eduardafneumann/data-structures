#ifndef SET_H
#define SET_H

#include "item.h"

typedef struct set_ SET;

// operações básicas

SET *set_criar();
void set_apagar(SET **set);
void set_inserir(SET *set, int chave);
void set_remover(SET *set, int chave);
void set_imprimir(SET *set);

// operações específicas

bool set_pertence(SET* set, int chave);
SET *set_interseccao(SET *set1, SET *set2);
SET *set_uniao(SET *set1, SET *set2);

#endif