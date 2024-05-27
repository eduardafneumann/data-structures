#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

void validate_alocation(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Alocation error.\n");
        exit(1);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}