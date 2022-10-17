#include <stdlib.h>
#include <stdio.h>
#include "item.h"
#include "alocacao.h"

struct item_{ 
   int chave;
};

ITEM *item_criar(int chave){
   ITEM *item = malloc(sizeof(ITEM)); verifica_alocacao(item);
   item->chave = chave;
   return(item);
   return(NULL);
}

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL;
      return(true);
   }
   return(false);
}

int item_get_chave(ITEM *item){
   if (item != NULL)
      return(item->chave);

   exit(1);
}

bool item_set_chave(ITEM *item, int chave){
   if (item != NULL){
      item->chave = chave;
      return (true);
   }
   return (false);
}

void item_imprimir(ITEM *item){
   if (item != NULL){
      printf("%d ", item->chave + 1);
   }
     
}

size_t item_size(){
   return sizeof(ITEM*);
}