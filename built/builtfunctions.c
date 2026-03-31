#include <stdio.h>
// Built-in command that stops the shell
int dash_help(void)
{
    fprintf(stdout, "Welcome to SeaShell! \n At the moment we have these commands: \n dock: ends the Shell\n help: Send every command built in SeaShell");
}


int dash_dock(void)
{
    // returns 0 making the main.c status be 0
    return 0;
}
