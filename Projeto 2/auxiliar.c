#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>

void verifica_alocacao(void *ponteiro){
    if(ponteiro==NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
}

int max(int a, int b){
    return a>b ? a : b;
}