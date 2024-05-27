#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

typedef struct element_ ELEMENT;

ELEMENT *element_create(int key);
bool element_erase(ELEMENT **element);
void element_print(ELEMENT *element);
int element_get_key(ELEMENT *element);
bool element_set_key(ELEMENT *element, int key);
int element_comparar(ELEMENT *element1, ELEMENT *element2);

#endif

