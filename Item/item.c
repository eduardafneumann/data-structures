#include <stdlib.h>
#include <stdio.h>
#include "item.h"

struct item_
{
    char c;
};

ITEM *item_criar(char chave)
{
    ITEM *item = malloc(sizeof(ITEM));
    if (item == NULL)
    {
        return NULL;
    }
    item->c = chave;
    return item;
}

bool item_apagar(ITEM **item)
{
    if (*item == NULL)
    {
        return false;
    }
    free(*item);
    *item == NULL;
    return true;
}

void item_imprimir(ITEM *item)
{
    if (item != NULL)
    {
        printf("Item = %c\n", item->c);
    }
}

char item_get_chave(ITEM *item)
{
    if (item != NULL)
    {
        return item->c;
    }
    return ERRO_CHAR;
}

bool item_set_chave(ITEM *item, char chave)
{
    if (item != NULL)
    {
        item->c = chave;
        return true;
    }
    return false;
}