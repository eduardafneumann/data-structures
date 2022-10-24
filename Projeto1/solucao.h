/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#ifndef SOLUCAO_
#define SOLUCAO_H

#include "pilha.h"

typedef struct solucao_ SOLUCAO;

SOLUCAO *solucao_criar(int n_cidades);
void solucao_apagar(SOLUCAO *solucao);
int solucao_get_dist(SOLUCAO *solucao);
PILHA *solucao_get_cidades(SOLUCAO *solucao);
void solucao_armazena(SOLUCAO *solucao, PILHA *visitadas, int dist);
void solucao_imprimir(SOLUCAO *solucao, int cidade_origem);

#endif