#define BUFFER_LENGTH 256
#include "parsing.h"

int compileFile(const char * filename)
{
    FILE * file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
        return 1;

    parseFile(file_ptr);

    return 0;
}

