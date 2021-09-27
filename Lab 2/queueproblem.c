//queueproblem.c - Lab 02 - Keegan, Kelly
#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *next;
    int value;
};
//the front and end pointers for the 4 queues are storred in arrays
struct node *front[4];
struct node *end[4];

//function to insert a node in the the que.accepts the data to be inserted
//and the number of the queue its inserted in
void insert(int n, int i);

//function to print the queue and accepts the number of the queue it prints
void print(int i);

int main(int argc, char *argv[])
{
    //for loop to initialize the front and end pointers
    for (int i = 0; i < 4; i++)
    {
        front[i] = NULL;
        end[i] = NULL;
    }
    //scans in the integers
    int temp;
    while (1)
    {
        scanf("%i", &temp);
        //ends the scanning if the int is negative
        if (temp < 0)
            break;
        //computes the modulo to determine which queue the number goes in
        int i = temp % 4;
        //inserts the number into the correct queue
        insert(temp, i);
    }
    //prints each queue
    for (int i = 0; i < 4; i++)
        print(i);
}

void insert(int n, int i)
{
    //reserves the memory for the node
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new != NULL)
    {
        //assigns new value
        new->value = n;
        new->next = NULL;

        if (end[i] != NULL)
        {
            //adds new node to end of list
            end[i]->next = new;
        }
        //updates queue's end pointer
        end[i] = new;
        //updates front pointer if the queue is empty
        if (front[i] == NULL)
            front[i] = new;
    }
}

// prints the queue and accepts which queue to print
void print(int i)
{
    struct node *ptr;
    //sets the head pointer
    ptr = front[i];
    int n = 0;
    //iterates through the list
    while (ptr != NULL)
    {
        //prints a new line after 12 number have been printed
        if (n % 12 == 0)
            printf("\n");
        //prints the data
        printf("%5d", ptr->value);
        //updates pointer and iterator
        ptr = ptr->next;
        n++;
    }
}