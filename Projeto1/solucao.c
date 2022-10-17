#include "solucao.h"
#include <stdlib.h>
#include "pilha.h"
#include "alocacao.h"
#include <limits.h>
#include <stdio.h>


struct solucao_
{
    int dist;
    PILHA *cidades;
};

SOLUCAO *solucao_criar(int n_cidades){    
    SOLUCAO *solucao = malloc(sizeof(SOLUCAO*)); verifica_alocacao(solucao);
    solucao->dist = INT_MAX;
    solucao->cidades = pilha_criar(n_cidades);
    return solucao;
}

void solucao_apagar(SOLUCAO *solucao){
    if(solucao!=NULL){
        pilha_apagar(solucao->cidades);
        free(solucao);
        solucao = NULL;
    }
}

int solucao_get_dist(SOLUCAO *solucao){
    return solucao->dist;
}

PILHA *solucao_get_cidades(SOLUCAO *solucao){
    return solucao->cidades;
}

void solucao_armazena(SOLUCAO *solucao, PILHA *visitadas, int dist)
{
    pilha_apagar(solucao->cidades);
    solucao->cidades = pilha_copia(visitadas);
    solucao->dist = dist;
}

void solucao_imprimir(SOLUCAO *solucao, int cidade_origem){
    pilha_imprimir(solucao->cidades);
    printf("%d\n", cidade_origem + 1);
}