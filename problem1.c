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
queue addToQueue(Node *new, queue queue);
queue removeFromQueue(queue queue);
int main(void)
{
    stack stack;
    queue queue;
    stack.tos = NULL;
    queue.front = NULL;
    int Stackearnings = 0;
    int QueueEarnings = 0;
    int go = 1;
    while (go == 1)
    {
        int n, m;
        char word[5] = "'\0'";
        scanf("%s %i %i", word, &n, &m);
        if (strcmp(word, "buy") == 0)
        {
            for (int i = 0; i < n; i++)
            {
                stack = addToStack(newNode(m), stack);
                queue = addToQueue(newNode(m), queue);
            }
            continue;
        }

        else if (strcmp(word, "sell") == 0)
        {
            for (int i = 0; i < n; i++)
            {
                Stackearnings += (m - stack.tos->data);
                stack = pop(stack);
                QueueEarnings += (m - queue.front->data);
                queue = removeFromQueue(queue);
            }
            continue;
        }
        else
            go = 0;
    }
    printf("Stack earning: %i\n", Stackearnings);
    printf("Queue earnings: %i\n", QueueEarnings);
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
    Node *tmp = stack.tos;
    stack.tos = stack.tos->prev;
    //stack.tos->next = NULL;
    free(tmp);
    return stack;
}

queue addToQueue(Node *new, queue queue)
{
    if (queue.front != NULL)
    {
        Node *tmp = queue.front;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        new->prev = tmp;
        tmp->next = new;
    }
    else
    {
        queue.front = new;
    }
    return queue;
}

queue removeFromQueue(queue queue)
{
    Node *tmp = queue.front;
    queue.front = queue.front->next;
    free(tmp);
    return queue;
}