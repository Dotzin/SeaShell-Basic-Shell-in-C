#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../utils/errors/errorsutil.h"
#include "parsers.h"

#define TK_BUFF_SIZE 1024 //Sets the default token size as 2^10
#define TOK_DELIM " \t\r\n" // Sets the token delimiter as " "" and the breaks \t \r and \n

char **split_line(char *line)
{
    int buffsize = TK_BUFF_SIZE;
    int position = 0; // Position of the actual token and will be summed by 1 to store the next
    char **tokens = malloc(buffsize * sizeof(char *)); // Alocates the buffsize multiplied by the char size is a array of Strings or array of an arrau of chars
    char *token; 

    // If there is no token, we had an memory allocation error
    if (!tokens)
    {
        memoryAllocationError();
    }


    // it splits the line into tokens, a token is an argument for the command or the command of the shell
    token = strtok(line, TOK_DELIM);

    /* 
    loop to go trough every possible token in 
    the line, an then when the last is Null it stops
    */
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // If the actual position exceeds the allocated memory reallocates more 1024 bytes per char size
        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));

            // Drops allocation error if the memory allocation goes wrong
            if (!tokens)
            {
                memoryAllocationError();
            }
        }

        // continues the strtok from a new one, not the same at the start
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


// Read the line entered by the user
char *read_line()
{
    int buffsize = TK_BUFF_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);  // Alocates the buffsize multiplied by the char size is a array of Strings or array of an arrau of chars
    int c; // int because it stores the ascii decimal value


    // Drops allocation error if the memory allocation goes wrong
    if (!buffer)
    {
        memoryAllocationError();
    }

    // Scans every character and stores it in the buffer array
    while (1)
    {
        c = getchar();

        // if it gets to the end of the line, it sets the last position as \0 then returning the buffer
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }

        // Stores the actual char on the buffer array at the position of the position variable
        else
        {
            buffer[position] = c;
        }

        position++;

        // If the actual position exceeds the allocated memory reallocates more 1024 bytes per char size
        if (position >= buffsize)
        {
            buffsize += TK_BUFF_SIZE;
            buffer = realloc(buffer, buffsize);
            // Drops allocation error if the memory allocation goes wrong
            if (!buffer)
            {
                memoryAllocationError();
            }
        }
    }
}
