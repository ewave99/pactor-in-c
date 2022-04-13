#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void printNodeValue(struct NodeValue value)
{
    switch(value.type)
    {
        case LONG_LONG_INT:
            printf("%lld", value.raw.long_long_int_value);
            break;
        case DOUBLE_FLOAT:
            printf("%f", value.raw.double_float_value);
            break;
        case STRING:
            printf("%s", value.raw.string_value);
            break;
        default:
            printf("NONE");
            break;
    }
}
void printStack(struct Stack * stack)
{
    struct Node * node;
    int index;

    node = stack->bottom;
    index = 0;
    while (node != NULL)
    {
        printNodeValue(node->value);
        printf(" ");
        node = node->next;
        index ++;
    }
    printf("<- TOP\n");
}


void push(struct Stack * stack, struct NodeValue value)
{
    struct Node * new_node;

    new_node = (struct Node *) malloc(sizeof(struct Node));

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

struct NodeValue pop(struct Stack * stack)
{
    struct Node * old_top;
    struct Node * new_top;
    struct NodeValue value;

    if (stack->length == 0)
    {
        value.type = NONE;
        return value;
    }

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

