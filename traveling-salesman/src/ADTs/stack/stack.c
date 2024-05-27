#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ADTs/stack/stack.h"

struct stack_
{
    Element **elements;
    int end;
    int size;
};

Stack *stack_create(int size)
{
    Stack *stack = malloc(sizeof(Stack));
    validate_alocation(stack);
    stack->elements = malloc(element_size() * size);
    validate_alocation(stack->elements);
    stack->size = size;
    stack->end = 0;
    return stack;
}

void stack_erase(Stack *stack)
{
    if (!stack_empty(stack))
    {
        for (int i = 0; i < stack->end; i++)
        {
            element_erase(&(stack->elements[i]));
        }
    }
    if (stack != NULL)
    {
        free(stack->elements);
        stack->elements = NULL;
        free(stack);
    }
}

bool stack_insert(Stack *stack, Element *element)
{
    if (!stack_full(stack))
    {
        stack->elements[stack->end] = element;
        stack->end++;
        return true;
    }
    return false;
}

void stack_remove(Stack *stack)
{
    if (!stack_empty(stack))
    {
        element_erase(&(stack->elements[stack->end - 1]));
        stack->elements[stack->end - 1] = NULL;
        stack->end--;
    }
}

int stack_size(Stack *stack)
{
    return stack->end;
}

bool stack_empty(Stack *stack)
{
    if (stack->end == 0)
        return true;
    return false;
}

bool stack_full(Stack *stack)
{
    if (stack->end < stack->size)
        return false;
    return true;
}

void stack_print(Stack *stack)
{
    for (int i = 0; i < stack->end; i++)
    {
        element_print(stack->elements[i]);
    }
}

int stack_get_key(Stack *stack, int i)
{
    return element_get_key(stack->elements[i]);
}

Stack *stack_copy(Stack *p)
{
    Stack *dest = stack_create(p->size);
    int i = 0;
    while (i < p->size)
    {
        stack_insert(dest, element_create(stack_get_key(p, i)));
        i++;
    }
    return dest;
}