#include <stdio.h>
#include "compile.h"

int main(int argc, char ** argv)
{
    if (argc == 2)
        compileFile(argv[1]);
    else
    {
        printf("Error: incorrect number of arguments.\n");
        return 1;
    }

    return 0;
}

