#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *next;
    unsigned int partnumber;
    unsigned int quantity_on_hand;
    unsigned int reorder_threshold;
};
void addToFront(struct node *new, struct node **head);
struct node *newNode(int num, int q, int thresh);
void printList(struct node *head);
void addToBack(struct node *new, struct node **head);
void reverseList(struct node **head);
struct node *copyList(struct node *head);
int main(void)
{
    struct node *head = NULL;
    for (int i = 0; i < 3; i++)
    {
        addToBack(newNode(i, 2 * i, 3 * i), &head);
    }
    printList(head);
    struct node *copy = copyList(head);
    reverseList(&copy);
    printList(copy);
}

struct node *newNode(int num, int q, int thresh)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new != NULL)
    {
        new->next = NULL;
        new->partnumber = num;
        new->quantity_on_hand = q;
        new->reorder_threshold = thresh;
    }
    return new;
}

void addToFront(struct node *new, struct node **head)
{
    new->next = *head;
    *head = new;
}

void addToBack(struct node *new, struct node **head)
{
    struct node *prev;
    struct node *current = *head;
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    while (current != NULL)
    {
        prev = current;
        current = current->next;
    }
    prev->next = new;
}

void printList(struct node *head)
{
    while (head != NULL)
    {
        printf("%i, %i, %i\n", head->partnumber, head->quantity_on_hand, head->reorder_threshold);
        head = head->next;
    }
}

void reverseList(struct node **head)
{
    struct node *current = *head;
    struct node *prev = NULL;
    struct node *next;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

struct node *copyList(struct node *head)
{
    struct node *newHead = NULL;
    struct node *current = head;
    while (current != NULL)
    {
        addToBack(newNode(current->partnumber, current->quantity_on_hand, current->reorder_threshold), &newHead);
        current = current->next;
    }
    return newHead;
}