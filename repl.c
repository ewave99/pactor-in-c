#define BUFFER_SIZE 256

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "builtins.h"

void runRepl();
void getInput(char * buffer);
void processInput(char * buffer, struct Stack * stack);
void processToken(char * token, struct Stack * stack);

void runRepl()
{
    char buffer[BUFFER_SIZE];
    struct Stack * stack;

    stack = (struct Stack *) malloc(sizeof(struct Stack));

    stack->top = NULL;
    stack->bottom = NULL;
    stack->length = 0;

    while (1)
    {
        getInput(buffer);
        processInput(buffer, stack);
    }
}

void getInput(char * buffer)
{
    fgets(buffer, BUFFER_SIZE, stdin); 
    buffer[strcspn(buffer, "\n")] = 0;
}

void processInput(char * buffer, struct Stack * stack)
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
        
        processToken(token_buffer, stack);

        buffer_ptr ++;
    }
}

void processToken(char * token, struct Stack * stack)
{
    if (strcmp(token, ".") == 0)
    {
        printTop(stack);
    }
    else if (strcmp(token, ".s") == 0)
    {
        printStack(stack);
    }
    else if (strcmp(token, "dup") == 0)
    {
        dup(stack);
    }
    else if (strcmp(token, "swap") == 0)
    {
        swap(stack);
    }
    else if (strcmp(token, "drop") == 0)
    {
        pop(stack);
    }
    else if (strcmp(token, "rot") == 0)
    {
        rot(stack);
    }
    else if (strcmp(token, "+") == 0)
    {
        add(stack);
    }
    else if (strcmp(token, "-") == 0)
    {
        subtract(stack);
    }
    else if (strcmp(token, "*") == 0)
    {
        multiply(stack);
    }
    else if (strcmp(token, "/") == 0)
    {
        divide(stack);
    }
    else if (isInteger(token))
    {
        int int_value = toInteger(token);
        push(stack, int_value);
    }
}

