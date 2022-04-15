#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum TokenType {
    T_LITERAL_INTEGER,
    T_LITERAL_FLOAT,
    T_LITERAL_STRING,
    T_BUILTINS_ADD,
    T_BUILTINS_SUBTRACT,
    T_BUILTINS_MULTIPLY,
    T_BUILTINS_DIVIDE,
    T_UNKNOWN
};

struct Token {
    enum TokenType type;
    char * raw;
};

int parseFile(FILE * file_ptr);
struct Token processToken(const char * raw);
enum TokenType getTokenType(const char * raw);

int isInteger(char * token);
int toInteger(char * token);

int parseFile(FILE * file_ptr)
{
    char current_char;
    char buffer[256];
    char * buffer_ptr;

    struct Token token;

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

        /* Do stuff with the token */
        token = processToken(buffer);
        /* --- */

        buffer_ptr = buffer;

        while (isspace(current_char))
            current_char = fgetc(file_ptr);
    }

    fclose(file_ptr);

    return 0;
}

struct Token processToken(const char * raw)
{
    struct Token token;
    size_t length;

    length = strlen(raw);
    
    token.raw = (char *) malloc(sizeof(char) * (length + 1));
    strcpy(token.raw, raw);

    token.type = getTokenType(raw);

    return token;
}

enum TokenType getTokenType(const char * raw)
{
    return T_UNKNOWN;
}

int isInteger(char * token)
{
    int is_integer;
    char * token_ptr;

    is_integer = 1;
    token_ptr = token;

    if (* token_ptr == '-')
        token_ptr ++;
    
    while (is_integer == 1 && * token_ptr != 0)
    {
        if (* token_ptr < 48 || * token_ptr >= 58)
        {
            is_integer = 0;
        }
        token_ptr ++;
    }

    return is_integer;
}

int toInteger(char * token)
{
    char * token_ptr;
    int result;
    int sign;

    token_ptr = token;
    result = 0;

    sign = 1;
    if (* token_ptr == '-')
    {
        sign = -1;
        token_ptr ++;
    }

    while (* token_ptr != 0)
    {
        result *= 10;
        result += (int) (* token_ptr) - 48;

        token_ptr ++;
    }

    result *= sign;

    return result;
}
