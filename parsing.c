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
