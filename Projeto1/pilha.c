#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#include "item.h"

struct pilha_{
    ITEM **itens;
    int fim;
    int tamanho;
};

PILHA *pilha_criar(int tamanho){
    PILHA *pilha = malloc(sizeof(PILHA));
    if(pilha==NULL){
        printf("Erro ao alocar a lista\n");
    }
    pilha->itens = malloc(item_size() * tamanho);
    if(pilha->itens == NULL) printf("Erro ao alocar a pilha");
    pilha->tamanho = tamanho;
    pilha->fim = 0;

    return pilha;
}

bool pilha_inserir(PILHA *pilha, ITEM *item){
    if(pilha->fim < pilha->tamanho){
        pilha->itens[pilha->fim] = item;
        pilha->fim++;
        return true;
    }
    return false;
}

//nao precisa retornar
void pilha_remover(PILHA *pilha){
    if(!pilha_vazia(pilha)){
        item_apagar(&(pilha->itens[pilha->fim - 1]));
        pilha->itens[pilha->fim - 1] = NULL;
        pilha->fim--;
    }
}

bool pilha_vazia(PILHA* pilha){
    if(pilha->fim == 0) return true;
    return false;
}

// ITEM *pilha_busca(PILHA *pilha, int chave);

int pilha_tamanho(PILHA *pilha){
    return pilha->fim;
}

void pilha_apagar(PILHA* pilha){
    for(int i = 0; i < pilha->fim; i++){
        item_apagar(&(pilha->itens[i]));
    }
    free(pilha->itens);
    pilha->itens = NULL;
    free(pilha);
}

void pilha_imprimir(PILHA* pilha){
    // printf("Pilha: ");
    for(int i = 0; i < pilha->fim; i++){
        item_imprimir(pilha->itens[i]);
    }
}

int pilha_get_chave(PILHA* pilha, int i){
    return item_get_chave(pilha->itens[i]);
}

PILHA* pilha_copia(PILHA* p){
    PILHA* dest = pilha_criar(p->tamanho);
    int i = 0;
    while(i < p->tamanho){
        pilha_inserir(dest, item_criar(pilha_get_chave(p, i)));
        i++;
    }
    return dest;
}