#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>

void printTop(struct Stack * stack)
{
    int value;

    value = pop(stack);
    printf("%d\n", value);
}
void printStack(struct Stack * stack)
{
    struct StackItem * node;
    int index;

    node = stack->bottom;
    index = 0;
    while (index < stack->length && node != NULL)
    {
        printf("%d ", node->value);
        node = node->next;
        index ++;
    }
    printf("<- TOP\n");
}

void dup(struct Stack * stack)
{
    int value;

    value = peek(stack);
    push(stack, value);
}
void swap(struct Stack * stack)
{
    int a;
    int b;

    b = pop(stack);
    a = pop(stack);

    push(stack, b);
    push(stack, a);
}
void rot(struct Stack * stack)
{
    int a;
    int b;
    int c;

    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    c = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    b = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    a = pop(stack);

    push(stack, b);
    push(stack, c);
    push(stack, a);
}

void add(struct Stack * stack)
{
    int a;
    int b;
    
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    b = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    a = pop(stack);

    push(stack, a + b);
}
void subtract(struct Stack * stack)
{
    int a;
    int b;
    
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    b = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    a = pop(stack);

    push(stack, a - b);
}
void multiply(struct Stack * stack)
{
    int a;
    int b;
    
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    b = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    a = pop(stack);

    push(stack, a * b);
}
void divide(struct Stack * stack)
{
    int a;
    int b;
    
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    b = pop(stack);
    if (stack->length == 0)
    {
        printf("Stack empty, cannot pop.\n");
        return;
    }
    a = pop(stack);

    if (b != 0)
        push(stack, a / b);
    else
        printf("Cannot divide by zero.");
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

void push(struct Stack * stack, int value)
{
    struct StackItem * new_node;

    new_node = (struct StackItem *) malloc(sizeof(struct StackItem));

    new_node->last = stack->top;
    new_node->next = NULL;
    new_node->value = value;

    if (stack->length > 0)
        stack->top->next = new_node;

    if (stack->length == 0)
        stack->bottom = new_node;
    else if (stack->length == 1)
        stack->bottom->next = new_node;

    stack->top = new_node;

    stack->length ++;
}

int pop(struct Stack * stack)
{
    if (stack->length == 0)
        return -1;

    struct StackItem * old_top;
    struct StackItem * new_top;
    int value;

    old_top = stack->top;

    new_top = old_top->last;
    value = old_top->value;

    if (stack->length > 1)
        new_top->next = NULL;

    stack->top = new_top;

    if (stack->length == 1)
        stack->bottom = NULL;
    else if (stack->length == 2)
        stack->bottom->next = NULL;

    free(old_top);

    stack->length --;

    return value;
}

int peek(struct Stack * stack)
{
    if (stack->top == NULL)
        return -1;
    return stack->top->value;
}

