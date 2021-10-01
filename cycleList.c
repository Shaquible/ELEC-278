#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct end
{
    int count;
    struct node *next;
};

struct node *new (int i);
void addToFront(struct end *endPTR, struct node *new);
void printList(struct end *endPTR);
void addToBack(struct end *endPTR, struct node *new);
void deleteFront(struct end *endPTR);
void delete (struct end *endPTR, int val);
int main(void)
{
    struct end *endPTR;
    endPTR->count = 0;
    for (int i = 0; i < 4; i++)
    {
        addToBack(endPTR, new (i));
    }
    delete (endPTR, 2);
    printList(endPTR);
}
struct node *new (int i)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->next = NULL;
    new->data = i;
    return new;
}

void addToFront(struct end *endPTR, struct node *new)
{
    if (endPTR->count == 0)
    {
        endPTR->next = new;
        new->next = endPTR->next;
        endPTR->count = 1;
        return;
    }
    new->next = endPTR->next;
    endPTR->next = new;
    endPTR->count++;
}
void addToBack(struct end *endPTR, struct node *new)
{
    if (endPTR->count == 0)
    {
        endPTR->next = new;
        new->next = endPTR->next;
        endPTR->count = 1;
        return;
    }
    struct node *current = endPTR->next;
    for (int i = 1; i < endPTR->count; i++)
    {
        current = current->next;
    }
    current->next = new;
    new->next = endPTR->next;
    endPTR->count++;
}

void printList(struct end *endPTR)
{
    struct node *current = endPTR->next;
    for (int i = 0; i < endPTR->count; i++)
    {
        printf("%i\n", current->data);
        current = current->next;
    }
}

void deleteFront(struct end *endPTR)
{
    struct node *current = endPTR->next;
    while (current->next != endPTR->next)
    {
        current = current->next;
    }
    current->next = endPTR->next->next;
    free(endPTR->next);
    endPTR->next = current->next;
    endPTR->count--;
}

void delete (struct end *endPTR, int val)
{
    struct node *current = endPTR->next;
    while (current->next->data != val)
    {
        current = current->next;
    }
    struct node *deleted = current->next;
    current->next = current->next->next;
    free(deleted);
    endPTR->count--;
}