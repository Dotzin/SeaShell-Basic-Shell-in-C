#include <stdio.h>
#include <stdlib.h>
#include "errorsutil.h"

#define RED "\033[0;31m" //Red color
#define RESET "\033[0m" // Reset the colors of the output


//Drops a memory allocation error in red text
void memoryAllocationError()
{
    fprintf(stderr, RED "dash: Allocation error" RESET "\n");
    exit(EXIT_FAILURE);
}

//Drops a not found error in red text
void notFoundError(char **args)
{
    printf(RED "dash: command not found: %s\n" RESET, args[0]);
}