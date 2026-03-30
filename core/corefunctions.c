#include <process.h>
#include <string.h>
#include "../utils/errors/errorsutil.h"
#include "../built/builtfunctions.h"

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