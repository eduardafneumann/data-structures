#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stddef.h>

#include "utils/validate_alocation.h"

#define ERRO -32000;

typedef struct node_ Node;

Node *node_create(int next_city, int weight);
bool node_erase(Node **node);
int node_get_city(Node *node);
int node_get_weight(Node *node);
bool node_set_city(Node *node, int city);
bool node_set_weight(Node *node, int weight);
void node_print(Node *node);
size_t node_size();

#endif
