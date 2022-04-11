struct StackItem
{
    struct StackItem * last;
    struct StackItem * next;
    int value;
};

struct Stack
{
    struct StackItem * bottom;
    struct StackItem * top;
    int length;
};

void printTop(struct Stack * stack);
void printStack(struct Stack * stack);

void dup(struct Stack * stack);
void swap(struct Stack * stack);
void rot(struct Stack * stack);

int isInteger(char * token);
int toInteger(char * token);

void push(struct Stack * stack, int value);
int pop(struct Stack * stack);
int peek(struct Stack * stack);

void add(struct Stack * stack);
void subtract(struct Stack * stack);
void multiply(struct Stack * stack);
void divide(struct Stack * stack);
