//stackproblem.c - Lab 02 - Keegan, Kelly
#include <stdio.h>
//initializing the stack
char stack[80];
int top = -1;

int push(char data);
int main(void)
{
    int go = 1;
    //while loop that continues to scan for user input
    while (1)
    {
        char temp;
        scanf("%c", &temp);
        //loop is broken on newline
        if (temp == '\n')
            break;
        //pushes data to the stack
        if (push(temp) == 0)
            //exits if the stack is full
            break;
    }
    //prints each element of the stack starting from the top down
    for (int i = top; i >= 0; i--)
    {
        printf("%c", stack[i]);
    }
    //prints a new line unless the stack is empty
    if (top >= 0)
        printf("\n");
}

//function that pushes data to the top of the stack and returns 0 if the stack is full
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
