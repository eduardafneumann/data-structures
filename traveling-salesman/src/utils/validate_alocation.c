#include <stdio.h>
#include <stdlib.h>

#include "utils/validate_alocation.h"

void validate_alocation(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Alocation error.\n");
        exit(1);
    }
}