#include <stdio.h>
#include <stdlib.h>

#include "ADTs/list/list.h"

struct list_
{
    Node **nodes;
    int end, size;
};

List *list_create(int size)
{
    List *list = malloc(sizeof(List));
    validate_alocation(list);
    list->nodes = malloc(node_size() * size);
    validate_alocation(list->nodes);
    list->size = size;
    list->end = 0;
    return list;
}

bool list_erase(List **list)
{
    if (!list_empty(*list))
    {
        for (int i = 0; i < (*list)->end; i++)
        {
            node_erase(&((*list)->nodes[i]));
        }
        free((*list)->nodes);
        (*list)->nodes = NULL;
        free(*list);
        return true;
    }
    return false;
}

bool list_insert(List *list, Node *node)
{
    if (!list_full(list))
    {
        list->nodes[list->end] = node;
        list->end++;
    }
    return true;
}

int list_size(List *list)
{
    return list->end;
}

bool list_empty(List *list)
{
    return list->end == 0 ? true : false;
}

bool list_full(List *list)
{
    return list->size == list->end + 1 ? true : false;
}

void list_print(List *list)
{
    printf("\nList: ");
    for (int i = 0; i < list->end; i++)
    {
        node_print(list->nodes[i]);
    }
    printf("\n");
}

Node *list_get_node(List *list, int index)
{
    if (index < list->end)
        return list->nodes[index];
    else
        return NULL;
}
