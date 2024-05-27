#ifndef SET_H
#define SET_H

#include <stdbool.h>

typedef struct set_ SET;

SET *set_create();
void set_erase(SET **set);
void set_insert(SET *set, int key);
void set_remove(SET *set, int key);
void set_print(SET *set);
bool set_contains(SET* set, int key);
SET *set_intersection(SET *set1, SET *set2);
SET *set_union(SET *set1, SET *set2);

#endif