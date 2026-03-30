#include <stdlib.h>
#include <stdio.h>
#include "utils/errors/errorsutil.h"
#include "built/builtfunctions.h"
#include "core/corefunctions.h"
#include "utils/utils.h"
#include "parser/parsers.h"

#define TOK_DELIM " \t\r\n"
#define TK_BUFF_SIZE 1024
/*
Main function, it is a loop that requests that the user enter a command 
*/
int main(void)
{
    char *line; 
    char **args;

    // If 0 will break the loop
    int status = 1;

    // loop that runs while the status is true or 1
    while (status)
    {
        
        printf("Sea > ");
        line = read_line();
        args = split_line(line);

        // If the command entered by the user  is not Null will execute the command
        if(args[0] != NULL)
            status = dash_execute(args);

        // Frees the allocated memory for line and args
        free(line);
        free(args);
    }

    // Exits the shell
    return exitProcess();
}
