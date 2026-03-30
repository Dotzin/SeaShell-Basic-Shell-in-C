#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include "utils/errorsutil.h"
#include "built/builtfunctions.h"

#define TOK_DELIM " \t\r\n"
#define TK_BUFF_SIZE 1024

char *read_line();
char **split_line(char *line);
int dash_execute(char **args);

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

    return EXIT_SUCCESS;
}

char *read_line()
{
    int buffsize = TK_BUFF_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer)
    {
        memoryAllocationError();
    }

    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }

        position++;
        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            buffer = realloc(buffer, buffsize);
            if (!buffer)
            {
                memoryAllocationError();
            }
        }
    }
}

char **split_line(char *line)
{
    int buffsize = TK_BUFF_SIZE;
    int position = 0;
    char **tokens = malloc(buffsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        memoryAllocationError();
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens)
            {
                memoryAllocationError();
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


int dash_dock(void);


int dash_execute(char **args)
{
    if (strcmp(args[0], "dock") == 0)
        return dash_dock();

    int ret = _spawnvp(_P_WAIT, args[0], (const char * const *) args);
    if (ret == -1)
    {
        notFoundError(args);
    }

    return 1;
}
