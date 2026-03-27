#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOK_DELIM " \t\r\n"
#define RED "\033[0;31m"
#define RESET "\e[0m"
#define TK_BUFF_SIZE 1024


char *read_line();
char ** split_line(char * line);
int dash_exit(char **args);

int main(int argc, char const *argv[])
{
    char *line;
    char **args;
    int status = 1;
    do
    {
        printf("Sea > ");
        line = read_line();
        args = split_line(line);
    } while (status);
    
    
    return EXIT_SUCCESS;
}

char * read_line()
{
    int buffsize = 2024;
    int position = 0;
    char * buffer = malloc(sizeof(char) * buffsize);
    int c;

    if(!buffer)
    {
        fprinf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        c = getchar();
        if(c == EOF || c =="\n")
        {
            //printf("\n";)
            buffer[position] = "\0";
            return buffer; 
        }
        else
        {
            buffer[position] = c;
        }
        position++;
        if(position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            buffer = realloc(buffer , buffsize);

            if(!buffer)
            {
                fprintf(stderr, "dash: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
}

char ** split_line(char * line)
{
    int buffsize = TK_BUFF_SIZE;
    int position = 0;

    char ** tokens = malloc(buffsize * sizeof(char*));
    char * token;

    if(!tokens)
    {
        fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
        exit(EXIT_FAILURE);
    }
    token = strtok(line, TOK_DELIM);
    
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = realloc(tokens, buffsize* sizeof(char *));

            if(!tokens)
            {
                fprintf(stderr, "%sdash: Allocation error%s\n", RED, RESET);
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