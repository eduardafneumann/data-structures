#ifndef AVL_H
#define AVL_H

#include "item.h"

typedef struct avl_ AVL;

AVL *avl_criar();
void avl_apagar(AVL **avl);
void avl_inserir(AVL *avl, ITEM *item);
void avl_remover(AVL *avl, ITEM *item);
void avl_imprimir(AVL *avl);
ITEM **avl_get_array(AVL *arvore);
bool avl_busca(AVL* arvore, int chave);

#endif
