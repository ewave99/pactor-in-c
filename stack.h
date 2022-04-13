enum DataType {
    LONG_LONG_INT,
    DOUBLE_FLOAT,
    STRING,
    NONE
};

struct NodeValue
{
    enum DataType type;
    union {
        long long int long_long_int_value;
        double double_float_value;
        char * string_value;
    } raw;
};

struct Node
{
    struct Node * last;
    struct Node * next;
    struct NodeValue value;
};

struct Stack
{
    struct Node * bottom;
    struct Node * top;
    int length;
};

void push(struct Stack * stack, struct NodeValue value);
struct NodeValue pop(struct Stack * stack);
struct NodeValue peek(struct Stack * stack);
