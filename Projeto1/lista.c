#include "lista.h"
#include "vertice.h"
#include <stdio.h>
#include <stdlib.h>

struct lista_{
    VERTICE **vertices;
    int fim, tamanho;
};

int lista_tamanho(LISTA *lista){
    return lista->fim;
}

bool lista_vazia(LISTA *lista){
    return lista->fim == 0 ? true : false;
}

bool lista_cheia(LISTA *lista){
    return lista->tamanho == lista->fim + 1 ? true : false;
}

LISTA *lista_criar(int tamanho){
    LISTA *lista = malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->vertices = malloc(vertice_size() * tamanho);
        lista->tamanho = tamanho;
        lista->fim = 0;
        return lista;
    }
    printf("Erro ao alocar lista");
    return NULL;
}

bool lista_apagar(LISTA **lista){
    if(!lista_vazia(*lista)){
        for(int i=0; i < (*lista)->fim; i++){
            vertice_apagar(&((*lista)->vertices[i]));
        }
        free((*lista)->vertices);
        (*lista)->vertices = NULL;
        free(*lista);
        return true;
    }
    return false;
}

bool lista_inserir(LISTA *lista, VERTICE *vertice){
    if(!lista_cheia(lista)){
        lista->vertices[lista->fim] = vertice;
        lista->fim++;
    }
    return true;
}

void lista_imprimir(LISTA *lista){
    printf("\nLista: ");
    for(int i = 0; i < lista->fim; i++){
        vertice_imprimir(lista->vertices[i]);
    }
    printf("\n");
}

VERTICE *lista_get_vertice(LISTA *lista, int indice){
    if(indice < lista->fim) return lista->vertices[indice];
    else return NULL;
}
