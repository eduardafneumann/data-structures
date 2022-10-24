/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "vertice.h"
#include "alocacao.h"

struct grafo_
{
    LISTA **lista_adj;
    int n_cidades;
};

GRAFO *grafo_criar(int n_cidades)
{
    GRAFO *grafo = malloc(sizeof(GRAFO)); verifica_alocacao(grafo);
    grafo->lista_adj = malloc(sizeof(LISTA *) * n_cidades); verifica_alocacao(grafo->lista_adj);
    grafo->n_cidades = n_cidades;
    for (int i = 0; i < n_cidades; i++)
    {
        grafo->lista_adj[i] = lista_criar(n_cidades);
    }
    return grafo;
}

void grafo_apagar(GRAFO *grafo)
{
    if(grafo!=NULL){
        for (int i = 0; i < grafo->n_cidades; i++)
        {
            lista_apagar(&(grafo->lista_adj[i]));
        }
        free(grafo->lista_adj);
        free(grafo);
    }
}

void grafo_inserir(GRAFO *grafo, int origem, int destino, int peso)
{
    lista_inserir(grafo->lista_adj[origem], vertice_criar(destino, peso));
}

LISTA *grafo_get_lista(GRAFO *grafo, int indice)
{
    if (indice < grafo->n_cidades)
        return grafo->lista_adj[indice];
    else
        return NULL;
}

int grafo_tamanho(GRAFO *grafo)
{
    return grafo->n_cidades;
}

void grafo_imprimir(GRAFO *grafo)
{
    for (int i = 0; i < grafo->n_cidades; i++)
    {
        lista_imprimir(grafo->lista_adj[i]);
    }
}