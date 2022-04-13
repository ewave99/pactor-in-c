#include <stdio.h>
#include <ctype.h>

int compileFile(const char * filename)
{
    FILE * file_ptr;
    char current_char;
    char buffer[256];
    char * buffer_ptr;

    file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
        return 1;

    buffer_ptr = buffer;
    current_char = fgetc(file_ptr);

    while (current_char != EOF)
    {
        while (isspace(current_char) == 0 && current_char != EOF)
        {
            * buffer_ptr = current_char;

            current_char = fgetc(file_ptr);
            buffer_ptr ++;
        }

        * buffer_ptr = 0;

        printf("%s\n", buffer);

        buffer_ptr = buffer;

        while (isspace(current_char))
            current_char = fgetc(file_ptr);
    }

    fclose(file_ptr);

    return 0;
}
