#ifndef SOLUCAO_
#define SOLUCAO_H

typedef struct solucao_ SOLUCAO;

SOLUCAO *solucao_criar(int n_cidades);
void solucao_apagar(SOLUCAO *solucao);
int solucao_get_dist(SOLUCAO *solucao);
void solucao_armazena(SOLUCAO *solucao, PILHA *visitadas, int dist);
solucao_imprimir(SOLUCAO *solucao, int cidade_origem);

#endif