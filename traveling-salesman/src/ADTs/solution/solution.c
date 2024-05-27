#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "ADTs/solution/solution.h"

struct solution_
{
    int distance;
    Stack *cities;
};

Solution *solution_create(int n_cities)
{
    Solution *solution = malloc(sizeof(Solution));
    validate_alocation(solution);
    solution->distance = INT_MAX;
    solution->cities = stack_create(n_cities);
    return solution;
}

void solution_erase(Solution *solution)
{
    if (solution != NULL)
    {
        stack_erase(solution->cities);
        free(solution);
        solution = NULL;
    }
}

int solution_get_distance(Solution *solution)
{
    return solution->distance;
}

Stack *solution_get_cities(Solution *solution)
{
    return solution->cities;
}

void solution_store(Solution *solution, Stack *visited, int distance)
{
    stack_erase(solution->cities);
    solution->cities = stack_copy(visited);
    solution->distance = distance;
}

void solution_print(Solution *solution, int origin_city)
{
    stack_print(solution->cities);
    printf("%d\n", origin_city + 1);
}