#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *next;
    int value;
};

struct node *front[4];
struct node *end[4];

void insert(int n, int i);
void print(int i);
int main(int argc, char *argv[])
{
    for (int i = 0; i < 4; i++)
    {
        front[i] = NULL;
        end[i] = NULL;
    }
    int temp;
    while (1)
    {
        scanf("%i", &temp);
        if (temp < 0)
            break;
        int i = temp % 4;
        insert(temp, i);
    }
    for (int i = 0; i < 4; i++)
        print(i);
}
void insert(int n, int i)

{
    // Create node to hold value being added to queue
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new != NULL)
    {
        new->value = n;
        new->next = NULL;
        // Make current last node point to new node
        if (end[i] != NULL)
        {
            end[i]->next = new;
        }
        // and update queue's end pointer
        end[i] = new;
        // If queue was empty, new node is also new front node
        if (front[i] == NULL)
            front[i] = new;
    }
}

void print(int i)
// Print all contents of array - primarily used for debugging purposes
{
    struct node *ptr;
    int k = 0; // "Index" in queue - makes output match array
               // implementation
    ptr = front[i];
    int n = 0;
    while (ptr != NULL)
    {
        if (n % 12 == 0)
            printf("\n");
        printf("%5d", ptr->value);
        ptr = ptr->next;
        n++;
    }
}