#include <stdlib.h>
#include <stdio.h>
#include "vertice.h"

struct vertice_{ 
   int prox_cidade, peso;
};

VERTICE *vertice_criar(int prox_cidade, int peso){
   VERTICE *vertice;

   vertice = malloc(sizeof(VERTICE));

   if (vertice != NULL){
      vertice->prox_cidade = prox_cidade;
      vertice->peso = peso;
      return(vertice);
   }
   return(NULL);
}

bool vertice_apagar(VERTICE **vertice){
   if (*vertice != NULL){
      free (*vertice);
      *vertice = NULL;
      return(true);
   }
   return(false);
}

int vertice_get_cidade(VERTICE *vertice){
   if (vertice != NULL)
      return(vertice->prox_cidade);

   exit(1);
}

int vertice_get_peso(VERTICE *vertice){
   if (vertice != NULL)
      return(vertice->peso);

   exit(1);
}

bool vertice_set_cidade(VERTICE *vertice, int cidade){
   if (vertice != NULL){
      vertice->prox_cidade = cidade;
      return (true);
   }
   return (false);
}

bool vertice_set_peso(VERTICE *vertice, int peso){
   if (vertice != NULL){
      vertice->peso = peso;
      return (true);
   }
  return (false);
}

void vertice_imprimir(VERTICE *vertice){
   if(vertice != NULL)
      printf(" vertice: cidade %d, peso %d ", vertice->prox_cidade, vertice->peso);
}

size_t vertice_size(){
   return sizeof(VERTICE*);
}