#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>
#include <stddef.h>

#include "utils/validate_alocation.h"

typedef struct element_ Element;

Element *element_create(int key);
bool element_erase(Element **element);
int element_get_key(Element *element);
bool element_set_key(Element *element, int key);
void element_print(Element *element);
size_t element_size();

#endif
