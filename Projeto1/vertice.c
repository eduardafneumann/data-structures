/*
   Projeto 1: problema do caixeiro viajante
   Eduarda Neumann - 12556973
   Jorge Franco - 13695091
   Susy Dutra - 12694007
*/

#include <stdlib.h>
#include <stdio.h>
#include "vertice.h"
#include "alocacao.h"

struct vertice_
{
   int prox_cidade, peso;
};

VERTICE *vertice_criar(int prox_cidade, int peso)
{
   VERTICE *vertice = malloc(sizeof(VERTICE)); verifica_alocacao(vertice);
   vertice->prox_cidade = prox_cidade;
   vertice->peso = peso;
   return (vertice);
}

bool vertice_apagar(VERTICE **vertice)
{
   if (*vertice != NULL)
   {
      free(*vertice);
      *vertice = NULL;
      return (true);
   }
   return (false);
}

int vertice_get_cidade(VERTICE *vertice)
{
   if (vertice != NULL)
      return (vertice->prox_cidade);
   return ERRO;
}

int vertice_get_peso(VERTICE *vertice)
{
   if (vertice != NULL)
      return (vertice->peso);
   return ERRO;
}

bool vertice_set_cidade(VERTICE *vertice, int cidade)
{
   if (vertice != NULL)
   {
      vertice->prox_cidade = cidade;
      return (true);
   }
   return (false);
}

bool vertice_set_peso(VERTICE *vertice, int peso)
{
   if (vertice != NULL)
   {
      vertice->peso = peso;
      return (true);
   }
   return (false);
}

void vertice_imprimir(VERTICE *vertice)
{
   if (vertice != NULL)
      printf(" vertice: cidade %d, peso %d ", vertice->prox_cidade, vertice->peso);
}

size_t vertice_size()
{
   return sizeof(VERTICE *);
}