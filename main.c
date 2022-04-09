#define BUFFER_SIZE 256

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Stack
{
    struct Stack * last;
    int value;
};


struct Context
{
    struct Stack * top;
};

void runRepl();
void getInput(char * buffer);
void processInput(char * buffer, struct Context * context);
void processToken(char * token, struct Context * context);

int isInteger(char * token);
int toInteger(char * token);

void push(struct Context * context, int value);
int pop(struct Context * context);

int main()
{
    runRepl();

    return 0;
}

void runRepl()
{
    char buffer[BUFFER_SIZE];
    struct Context * context;
    context = (struct Context *) malloc(sizeof(struct Context));
    while (1)
    {
        getInput(buffer);
        processInput(buffer, context);
    }
}

void getInput(char * buffer)
{
    fgets(buffer, BUFFER_SIZE, stdin); 
    buffer[strcspn(buffer, "\n")] = 0;
}

void processInput(char * buffer, struct Context * context)
{
    char * buffer_ptr;

    char token_buffer[BUFFER_SIZE];
    char * token_buffer_ptr;

    buffer_ptr = buffer;
    
    while (* buffer_ptr != 0)
    {
        token_buffer_ptr = token_buffer;

        while (* buffer_ptr != ' ' && * buffer_ptr != 0)
        {
            * token_buffer_ptr = * buffer_ptr;

            buffer_ptr ++;
            token_buffer_ptr ++;
        }

        * token_buffer_ptr = 0;
        
        processToken(token_buffer, context);

        buffer_ptr ++;
    }
}

void processToken(char * token, struct Context * context)
{
    int int_value;

    if (isInteger(token))
    {
        int_value = toInteger(token);
        push(context, int_value);
    }
    else if (strcmp(token, "pop") == 0)
    {
        int_value = pop(context);
        printf("%d\n", int_value);
    }
}

int isInteger(char * token)
{
    int is_integer;
    char * token_ptr;

    is_integer = 1;
    token_ptr = token;
    
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

    token_ptr = token;
    result = 0;

    while (* token_ptr != 0)
    {
        result *= 10;
        result += (int) (* token_ptr) - 48;

        token_ptr ++;
    }

    return result;
}

void push(struct Context * context, int value)
{
}

int pop(struct Context * context)
{
    return 0;
}
