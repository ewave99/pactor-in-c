#include "stack.h"
#include <stdio.h>

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

void dup(struct Stack * stack)
{
    struct NodeValue value;

    value = pop(stack);
    if (value.type == NONE)
        return;
    push(stack, value);
    push(stack, value);
}
void drop(struct Stack * stack)
{
    pop(stack);
}
void swap(struct Stack * stack)
{
    struct NodeValue a,
                     b;

    b = pop(stack);
    if (b.type == NONE) return;
    a = pop(stack);
    if (a.type == NONE) return;

    push(stack, b);
    push(stack, a);
}
void rot(struct Stack * stack)
{
    struct NodeValue a,
                     b,
                     c;

    c = pop(stack);
    if (c.type == NONE) return;
    b = pop(stack);
    if (b.type == NONE) return;
    a = pop(stack);
    if (a.type == NONE) return;

    push(stack, b);
    push(stack, c);
    push(stack, a);
}

void add(struct Stack * stack)
{
    struct NodeValue a,
                     b,
                     result;

    b = pop(stack);
    if (b.type == NONE) return;
    a = pop(stack);
    if (a.type == NONE) return;

    result.type = DOUBLE_FLOAT;
    switch (a.type)
    {
        case LONG_LONG_INT:
            result.raw.double_float_value = (double) a.raw.long_long_int_value;
            break;
        case DOUBLE_FLOAT:
            result.raw.double_float_value = a.raw.double_float_value;
            break;
        default:
            printf("Cannot perform addition on non-numeric value.");
            return;
    }
    switch (b.type)
    {
        case LONG_LONG_INT:
            result.raw.double_float_value += (double) b.raw.long_long_int_value;
            break;
        case DOUBLE_FLOAT:
            result.raw.double_float_value += b.raw.double_float_value;
            break;
        default:
            printf("Cannot perform addition on non-numeric value.");
            return;
    }
    push(stack, result);
}
void subtract(struct Stack * stack)
{
    struct NodeValue a,
                     b,
                     result;

    b = pop(stack);
    if (b.type == NONE) return;
    a = pop(stack);
    if (a.type == NONE) return;

    result.type = DOUBLE_FLOAT;
    switch (a.type)
    {
        case LONG_LONG_INT:
            result.raw.double_float_value = (double) a.raw.long_long_int_value;
            break;
        case DOUBLE_FLOAT:
            result.raw.double_float_value = a.raw.double_float_value;
            break;
        default:
            printf("Cannot perform subtraction on non-numeric value.");
            return;
    }
    switch (b.type)
    {
        case LONG_LONG_INT:
            result.raw.double_float_value -= (double) b.raw.long_long_int_value;
            break;
        case DOUBLE_FLOAT:
            result.raw.double_float_value -= b.raw.double_float_value;
            break;
        default:
            printf("Cannot perform subtraction on non-numeric value.");
            return;
    }
    push(stack, result);
}
