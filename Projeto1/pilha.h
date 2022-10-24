/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#ifndef PILHA_H
#define PILHA_H

#include "item.h"
#include <stdbool.h>

#define TAM 100
#define TRUE 1
#define FALSE 0

typedef struct pilha_ PILHA;

PILHA *pilha_criar(int tamanho);
void pilha_apagar(PILHA* pilha);
bool pilha_inserir(PILHA *pilha, ITEM *item);
void pilha_remover(PILHA *pilha); // nao precisa retornar o item, não será utilizado
int pilha_tamanho(PILHA *pilha);
bool pilha_vazia(PILHA* pilha);
bool pilha_cheia(PILHA *pilha);
void pilha_imprimir(PILHA* pilha);
int pilha_get_chave(PILHA* pilha, int i);
PILHA* pilha_copia(PILHA* p);

#endif