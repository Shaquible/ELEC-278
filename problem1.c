#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct stack
{
    Node *tos;
} stack;
typedef struct queue
{
    Node *front;
} queue;

stack pop(stack stack);
Node *newNode(int data);
stack addToStack(Node *new, stack stack);
int main(void)
{
    stack stack;
    stack.tos = NULL;
    int earnings = 0;
    while (1)
    {
        int n, m;
        char word[4];
        if (scanf("%s %i %i", word, &n, &m) == 0)
            break;
        if (strcmp(word, "BUY") == 0)
        {
            for (int i = 0; i < n; i++)
                stack = addToStack(newNode(m), stack);
        }

        else
        {
            for (int i = 0; i < n; i++)
            {
                earnings += (m - stack.tos->data);
                stack = pop(stack);
            }
        }
    }
    printf("%i", earnings);
}

Node *newNode(int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
}

stack addToStack(Node *new, stack stack)
{
    if (stack.tos != NULL)
    {
        stack.tos->next = new;
        new->prev = stack.tos;
    }
    stack.tos = new;
    return stack;
}

stack pop(stack stack)
{
    stack.tos->prev->next = NULL;
    Node *tmp = stack.tos;
    stack.tos = stack.tos->prev;
    free(tmp);
    return stack;
}