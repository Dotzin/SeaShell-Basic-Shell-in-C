#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../utils/errors/errorsutil.h"
#include "parser/parsers.h"

#define TK_BUFF_SIZE 1024
#define TOK_DELIM " \t\r\n"


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