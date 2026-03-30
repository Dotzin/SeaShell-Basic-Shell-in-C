#include <stdio.h>
#include <stdlib.h>
#include "errorsutil.h"

#define RED "\033[0;31m"
#define RESET "\033[0m"

void memoryAllocationError()
{
    fprintf(stderr, RED "dash: Allocation error" RESET "\n");
    exit(EXIT_FAILURE);
}

void notFoundError(char **args)
{
    printf(RED "dash: command not found: %s\n" RESET, args[0]);
}