#define LIMIT 200000
char stack[LIMIT] = {0,};
int top = 0;

void push(char ch)
{
    if(top >= LIMIT)
        return;

    stack[top++] = ch;
}

char pop()
{
    if(top <= 0)
        return -1;

    return stack[--top];
}