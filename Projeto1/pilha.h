#ifndef PILHA_H
#define PILHA_H

#include "item.h"
#include <stdbool.h>

#define TAM 100
#define TRUE 1
#define FALSE 0

typedef struct pilha_ PILHA;

PILHA *pilha_criar(int tamanho);
bool pilha_inserir(PILHA *pilha, ITEM *item);
void pilha_remover(PILHA *pilha);
bool pilha_vazia(PILHA* pilha);
// ITEM *pilha_busca(PILHA *pilha, int chave);
int pilha_tamanho(PILHA *pilha);
void pilha_apagar(PILHA* pilha);
void pilha_imprimir(PILHA* pilha);
int pilha_get_chave(PILHA* pilha, int i);
PILHA* pilha_copia(PILHA* p);

#endif