#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int inTime;
    int len;
    int start;
} node;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

int isEmpty(queue queue)
{
    if (queue.head == NULL)
        return 1;
    return 0;
}

node *newNode(int enter, int job)
{
    node *new = (node *)malloc(sizeof(node));
    new->inTime = enter;
    new->len = job;
    new->start;
    new->next = NULL;
    return new;
}
void addToQueue(node *new, queue *queue)
{
    if (isEmpty(*queue) == 1)
    {
        queue->head = new;
        queue->tail = new;
        new->start = new->inTime;
        return;
    }
    else
    {
        queue->tail->next = new;
        queue->tail = new;
        return;
    }
}
int removeFromQueue(queue *queue)
{
    if (queue->head == NULL)
    {
        queue->tail = NULL;
        return -1;
    }
    int wait = queue->head->start + queue->head->len - queue->head->inTime;
    node *tmp = queue->head;
    queue->head = queue->head->next;
    if (queue->head != NULL)
        queue->head->start = wait + tmp->start;
    free(tmp);
    return wait;
}
int main(void)
{
    queue jobs;
    jobs.head = NULL;
    jobs.tail = NULL;
    addToQueue(newNode(1, 30), &jobs);
    addToQueue(newNode(2, 5), &jobs);
    int wait = 0;
    while (wait != -1)
    {
        wait = removeFromQueue(&jobs);
        printf("%i\n", wait);
    }
}