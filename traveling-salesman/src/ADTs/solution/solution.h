#ifndef SOLUTION_H
#define SOLUTION_H

#include "ADTs/stack/stack.h"
#include "utils/validate_alocation.h"

typedef struct solution_ Solution;

Solution *solution_create(int n_cities);
void solution_erase(Solution *solution);
int solution_get_distance(Solution *solution);
Stack *solution_get_cities(Solution *solution);
void solution_store(Solution *solution, Stack *visited, int distance);
void solution_print(Solution *solution, int origin_city);

#endif