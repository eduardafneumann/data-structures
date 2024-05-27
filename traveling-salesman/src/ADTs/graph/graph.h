#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "ADTs/list/list.h"
#include "ADTs/graph/node.h"
#include "utils/validate_alocation.h"

typedef struct graph_ Graph;

Graph *graph_create(int n_nodes);
void graph_erase(Graph *graph);
void graph_insert(Graph *graph, int origin, int destination, int weight);
List *graph_get_list(Graph *graph, int index);
int graph_size(Graph *graph);
void graph_print(Graph *graph);

#endif