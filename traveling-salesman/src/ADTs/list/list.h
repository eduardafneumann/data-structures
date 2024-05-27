#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

#include "ADTs/graph/node.h"
#include "ADTs/element.h"
#include "utils/validate_alocation.h"

typedef struct list_ List;

List *list_create(int size);
bool list_erase(List **list);
bool list_insert(List *list, Node *node);
int list_size(List *list);
bool list_empty(List *list);
bool list_full(List *list);
void list_print(List *list);
Node *list_get_node(List *list, int index);

#endif