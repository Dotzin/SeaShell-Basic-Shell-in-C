#include <stdio.h>
// Built-in command that stops the shell
int dash_help(void)
{
    fprintf(stdout, "Welcome to SeaShell! \n At the moment we have these commands: \n dock: ends the Shell\n help: Send every command built in SeaShell");
    return 1;
}


int dash_dock(void)
{
    // returns 0 making the main.c status be 0
    return 0;
}

// Built-in command that prints the arguments after the echo command
int dash_echo(char **args)
{
    // prints the arguments after the echo command
    int i = 1;
        // while the argument is not null, prints it
        while (args[i] != NULL)
        {
            // prints the argument followed by a space
            fprintf(stdout, "%s ", args[i]);
            i++;
        }
    return 1;
}

