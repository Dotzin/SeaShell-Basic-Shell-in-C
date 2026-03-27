#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <windows.h>

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define TK_BUFF_SIZE 1024

char *read_line();
char **split_line(char *line);
int dash_exit(char **args);
int dash_execute(char **args);

int main(int argc, char const *argv[])
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
    int buffsize = 1024;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, RED "dash: Allocation error" RESET "\n");
        exit(EXIT_FAILURE);
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
                fprintf(stderr, RED "dash: Allocation error" RESET "\n");
                exit(EXIT_FAILURE);
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
        fprintf(stderr, RED "dash: Allocation error" RESET "\n");
        exit(EXIT_FAILURE);
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
                fprintf(stderr, RED "dash: Allocation error" RESET "\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


int dash_exit(char **args)
{
    return 0;
}

int dash_execute(char **args)
{
    if (strcmp(args[0], "exit") == 0)
        return dash_exit(args);

    int ret = _spawnvp(_P_WAIT, args[0], args);
    if (ret == -1)
    {
        printf(RED "dash: command not found: %s\n" RESET, args[0]);
    }

    return 1;
}