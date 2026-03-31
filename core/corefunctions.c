#include <process.h>
#include <string.h>
#include "../utils/errors/errorsutil.h"
#include "../built/builtfunctions.h"


// Executes the commands accordingly with the args
int dash_execute(char **args)
{
    // compares the first argument with a built-in command
    if (strcmp(args[0], "help") == 0)
        return dash_help();

    if (strcmp(args[0], "dock") == 0)
        return dash_dock();

    // Verifies if the first argument is an command that exists on windows
    int ret = _spawnvp(_P_WAIT, args[0], (const char * const *) args);

    // if it does not exists returns -1 and prints the error message
    if (ret == -1)
    {
        notFoundError(args);
    }

    return 1;
}