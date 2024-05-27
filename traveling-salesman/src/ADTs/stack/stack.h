#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#include "ADTs/element.h"
#include "utils/validate_alocation.h"

#define TAM 100
#define TRUE 1
#define FALSE 0

typedef struct stack_ Stack;

Stack *stack_create(int size);
void stack_erase(Stack* stack);
bool stack_insert(Stack *stack, Element *element);
void stack_remove(Stack *stack);
int stack_size(Stack *stack);
bool stack_empty(Stack* stack);
bool stack_full(Stack *stack);
void stack_print(Stack* stack);
int stack_get_key(Stack* stack, int i);
Stack* stack_copy(Stack* p);

#endif