#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#include "utils/validate_alocation.h"
#include "ADTs/list/list.h"
#include "ADTs/graph/graph.h"
#include "ADTs/stack/stack.h"
#include "ADTs/solution/solution.h"

typedef struct info_
{
    Graph *graph;
    int origin_city;
    bool *visited;
    Solution *best_solution;
    Stack *current_path;
} Info;

void read_graph(Graph *graph)
{
    int node1, node2, weight;
    while (scanf("%d %d %d", &node1, &node2, &weight) != EOF)
    {
        node1--;
        node2--;
        graph_insert(graph, node1, node2, weight);
        graph_insert(graph, node2, node1, weight);
    }
}

Info *info_create()
{
    // Reading input

    int n_cities;
    if (scanf("%d", &n_cities) < 1)
        printf("Reading error.");
    int origin_city;
    if (scanf("%d", &origin_city) < 1)
        printf("Reading error.");
    origin_city--;

    // Creating the graph, the best solution, array of visited cities and path stack

    Graph *graph = graph_create(n_cities);

    Solution *best_solution = solution_create(n_cities);

    bool *visited = malloc(sizeof(bool) * n_cities);
    validate_alocation(visited);
    for (int i = 0; i < n_cities; i++)
        visited[i] = false;

    Stack *current_path = stack_create(n_cities);
    stack_insert(current_path, element_create(origin_city));

    // Read the graph

    read_graph(graph);

    // Creating and initializinf info

    Info *info = malloc(sizeof(Info));
    info->graph = graph;
    info->origin_city = origin_city;
    info->visited = visited;
    info->best_solution = best_solution;
    info->current_path = current_path;

    return info;
}

void info_erase(Info *info)
{
    graph_erase(info->graph);
    free(info->visited);
    solution_erase(info->best_solution);
    stack_erase(info->current_path);
    free(info);
}

void solve(Info *info, int city, int distance)
{
    List *neighborhood = graph_get_list(info->graph, city);
    Node *next_city;
    int weight, neighbor;

    for (int i = 0; i < list_size(neighborhood); i++)
    {
        next_city = list_get_node(neighborhood, i);
        weight = node_get_weight(next_city);
        neighbor = node_get_city(next_city);

        if (neighbor == info->origin_city)
        {
            // Is a valid path
            if (stack_size(info->current_path) == graph_size(info->graph))
            {
                distance += weight;
                // It's smaller than the best one so far
                if (distance < solution_get_distance(info->best_solution))
                {
                    solution_store(info->best_solution, info->current_path, distance);
                }
            }
        }
        else
        {
            if (!info->visited[neighbor])
            {
                stack_insert(info->current_path, element_create(neighbor));
                info->visited[neighbor] = true;

                solve(info, neighbor, distance + weight);

                info->visited[neighbor] = false;
                stack_remove(info->current_path);
            }
        }
        next_city = NULL;
    }
    neighborhood = NULL;
}

int main()
{
    // criando info
    Info *info = info_create();
    graph_size(info->graph);

    // resolvendo
    solve(info, info->origin_city, 0);

    // imprimindo a solução
    solution_print(info->best_solution, info->origin_city);

    // desalocando a memória
    info_erase(info);

    return 0;
}