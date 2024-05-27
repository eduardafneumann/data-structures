#include <stdlib.h>
#include <stdio.h>

#include "ADTs/graph/graph.h"

struct graph_
{
    List **adj_list;
    int n_cities;
};

Graph *graph_create(int n_cities)
{
    Graph *graph = malloc(sizeof(Graph));
    validate_alocation(graph);

    graph->adj_list = malloc(sizeof(List *) * n_cities);
    validate_alocation(graph->adj_list);

    graph->n_cities = n_cities;
    for (int i = 0; i < n_cities; i++)
    {
        graph->adj_list[i] = list_create(n_cities);
    }
    return graph;
}

void graph_erase(Graph *graph)
{
    if (graph != NULL)
    {
        for (int i = 0; i < graph->n_cities; i++)
        {
            list_erase(&(graph->adj_list[i]));
        }
        free(graph->adj_list);
        free(graph);
    }
}

void graph_insert(Graph *graph, int origin, int destination, int weight)
{
    list_insert(graph->adj_list[origin], node_create(destination, weight));
}

List *graph_get_list(Graph *graph, int index)
{
    if (index < graph->n_cities)
        return graph->adj_list[index];
    else
        return NULL;
}

int graph_size(Graph *graph)
{
    return graph->n_cities;
}

void graph_print(Graph *graph)
{
    for (int i = 0; i < graph->n_cities; i++)
    {
        list_print(graph->adj_list[i]);
    }
}