#include "alocacao.h"
#include <stdio.h>
#include <stdlib.h>

void verifica_alocacao(void *ponteiro){
    if(ponteiro==NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
}