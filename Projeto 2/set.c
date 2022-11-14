#include "avl.h"
#include "set.h"
#include "auxiliar.h"
#include <stdlib.h>
#include<stdio.h>

struct set_
{
    AVL* arvore;
};

SET *set_criar(void){
    SET* set = malloc(sizeof(SET)); verifica_alocacao(set);
    set->arvore = avl_criar();
    return set;
}

void set_apagar(SET **c){
    if(*c != NULL){
        avl_apagar(&((*c)->arvore));
        free(*c); 
        *c = NULL;
    }
}

bool set_pertence(SET *A, int elemento){
    return avl_busca(A->arvore, elemento);
}

bool set_inserir(SET *s, int elemento){
    if(set_pertence(s, elemento)) return false;

    avl_inserir(s->arvore, item_criar(elemento));
    return true;
}

bool set_remover(SET *s, int elemento){
    if(!set_pertence(s, elemento)) return false;

    avl_remover(s->arvore, item_criar(elemento));
    return true;
}

SET *set_interseccao(SET *c1, SET *c2){
    SET *interseccao = set_criar();
    ITEM **array = avl_get_array(c1->arvore);

    int i=0;

    while(array[i]!=NULL){
        if(set_pertence(c2,item_get_chave(array[i])) && !set_pertence(interseccao,item_get_chave(array[i]))){

            set_inserir(interseccao,item_get_chave(array[i]));

        }
        ++i;
    }

    free(array);
    
    return interseccao;
}

SET *set_uniao(SET *set1, SET *set2){
    SET *uniao= set_criar();
    ITEM **array1 = avl_get_array(set1->arvore);
    ITEM **array2 = avl_get_array(set2->arvore);

    for(int i=0; array1[i] != NULL; i++){
        if(!set_pertence(uniao,item_get_chave(array1[i]))){
            set_inserir(uniao,item_get_chave(array1[i]));
        }
    }

    for(int j=0; array2[j]!=NULL; j++){
        if(!set_pertence(uniao,item_get_chave(array2[j]))){
            set_inserir(uniao,item_get_chave(array2[j]));
        }
    }

    free(array1);
    free(array2);

    return uniao;
} 

void set_imprimir(SET *s){
    avl_imprimir(s->arvore);
}

