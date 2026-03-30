#include <stdlib.h>
#include <stdio.h>
#include "utils/errors/errorsutil.h"
#include "built/builtfunctions.h"
#include "core/corefunctions.h"
#include "utils/utils.h"
#include "parser/parsers.h"

#define TOK_DELIM " \t\r\n"
#define TK_BUFF_SIZE 1024

int main(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        
        printf("Sea > ");
        line = read_line();
        args = split_line(line);

        if(args[0] != NULL)
            status = dash_execute(args);

        free(line);
        free(args);
    }

    return exitProcess();
}
