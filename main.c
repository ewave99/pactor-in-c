#define BUFFER_SIZE 256

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Stack
{
    struct Stack * last;
    struct Stack * next;
    int value;
};


struct Context
{
    struct Stack * bottom;
    struct Stack * top;
    int stack_length;
};

void runRepl();
void getInput(char * buffer);
void processInput(char * buffer, struct Context * context);
void processToken(char * token, struct Context * context);

int isInteger(char * token);
int toInteger(char * token);

void push(struct Context * context, int value);
int pop(struct Context * context);

void printStack(struct Context * context);

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

    context->top = NULL;
    context->bottom = NULL;
    context->stack_length = 0;

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

    if (strcmp(token, ".") == 0)
    {
        if (context->top != NULL)
        {
            int_value = pop(context);
            printf("%d\n", int_value);
        }
        else
        {
            printf("Stack empty, cannot pop.\n");
        }
    }
    else if (strcmp(token, ".s") == 0)
    {
        printStack(context);
    }
    else if (strcmp(token, "+") == 0)
    {
        int b = pop(context);
        int a = pop(context);
        int result = a + b;
        push(context, result);
    }
    else if (strcmp(token, "-") == 0)
    {
        int b = pop(context);
        int a = pop(context);
        int result = a - b;
        push(context, result);
    }
    else if (strcmp(token, "*") == 0)
    {
        int b = pop(context);
        int a = pop(context);
        int result = a * b;
        push(context, result);
    }
    else if (strcmp(token, "/") == 0)
    {
        int b = pop(context);
        int a = pop(context);
        if (b != 0)
        {
            int result = a / b;
            push(context, result);
        }
        else
        {
            printf("Cannot divide by zero.\n");
        }
    }
    else if (isInteger(token))
    {
        int_value = toInteger(token);
        push(context, int_value);
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
    struct Stack * new_node;

    new_node = (struct Stack *) malloc(sizeof(struct Stack));

    new_node->last = context->top;
    new_node->next = NULL;
    new_node->value = value;

    if (context->stack_length > 0)
        context->top->next = new_node;

    if (context->stack_length == 0)
        context->bottom = new_node;
    else if (context->stack_length == 1)
        context->bottom->next = new_node;

    context->top = new_node;

    context->stack_length ++;
}

int pop(struct Context * context)
{
    if (context->stack_length == 0)
        return -1;

    struct Stack * old_top;
    struct Stack * new_top;
    int value;

    old_top = context->top;

    new_top = old_top->last;
    value = old_top->value;

    if (context->stack_length > 1)
        new_top->next = NULL;

    context->top = new_top;

    if (context->stack_length == 1)
        context->bottom = NULL;
    else if (context->stack_length == 2)
        context->bottom->next = NULL;

    free(old_top);

    context->stack_length --;

    return value;
}

void printStack(struct Context * context)
{
    struct Stack * node;
    int index;

    node = context->bottom;
    index = 0;
    while (index < context->stack_length && node != NULL)
    {
        printf("%d ", node->value);
        node = node->next;
        index ++;
    }
    printf("<- TOP\n");
}
