//stackproblem.c - Lab 02 - Keegan, Kelly
#include <stdio.h>
char stack[80];
int top = -1;
int push(char data);
int main(void)
{
    int go = 1;

    while (1)
    {
        char temp;
        scanf("%c", &temp);
        if (temp == '\n')
            break;
        if (push(temp) == 0)
            return 0;
    }
    for (int i = top; i >= 0; i--)
    {
        printf("%c", stack[i]);
    }
    if (top >= 0)
        printf("\n");
}

int push(char data)
{
    if (top == 79)
    {
        return 0;
    }
    top++;
    stack[top] = data;
    return 1;
}
