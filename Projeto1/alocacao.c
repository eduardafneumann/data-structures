/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#include <stdio.h>
#include <stdlib.h>
#include "alocacao.h"

void verifica_alocacao(void *ponteiro)
{
    if (ponteiro == NULL)
    {
        printf("Erro de alocação.\n");
        exit(1);
    }
}