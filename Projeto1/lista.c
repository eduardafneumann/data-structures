/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#include "lista.h"
#include "vertice.h"
#include <stdio.h>
#include <stdlib.h>
#include "alocacao.h"

struct lista_
{
    VERTICE **vertices;
    int fim, tamanho;
};

LISTA *lista_criar(int tamanho)
{
    LISTA *lista = malloc(sizeof(LISTA)); verifica_alocacao(lista);
    lista->vertices = malloc(vertice_size() * tamanho); verifica_alocacao(lista->vertices);
    lista->tamanho = tamanho;
    lista->fim = 0;
    return lista;
}

bool lista_apagar(LISTA **lista)
{
    if (!lista_vazia(*lista))
    {
        for (int i = 0; i < (*lista)->fim; i++)
        {
            vertice_apagar(&((*lista)->vertices[i]));
        }
        free((*lista)->vertices);
        (*lista)->vertices = NULL;
        free(*lista);
        return true;
    }
    return false;
}

bool lista_inserir(LISTA *lista, VERTICE *vertice)
{
    if (!lista_cheia(lista))
    {
        lista->vertices[lista->fim] = vertice;
        lista->fim++;
    }
    return true;
}

int lista_tamanho(LISTA *lista)
{
    return lista->fim;
}

bool lista_vazia(LISTA *lista)
{
    return lista->fim == 0 ? true : false;
}

bool lista_cheia(LISTA *lista)
{
    return lista->tamanho == lista->fim + 1 ? true : false;
}

void lista_imprimir(LISTA *lista)
{
    printf("\nLista: ");
    for (int i = 0; i < lista->fim; i++)
    {
        vertice_imprimir(lista->vertices[i]);
    }
    printf("\n");
}

VERTICE *lista_get_vertice(LISTA *lista, int indice)
{
    if (indice < lista->fim)
        return lista->vertices[indice];
    else
        return NULL;
}
