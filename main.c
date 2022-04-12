#define BUFFER_SIZE 256

#include <stdio.h>
#include "repl.h"
#include "compile.h"

int main(int argc, char ** argv)
{
    if (argc > 2)
    {
        printf("Error: too many arguments.\n");
        return 1;
    }
    if (argc == 1)
        runRepl();
    else if (argc == 2)
        compileFile(argv[1]);

    return 0;
}

