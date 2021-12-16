#include <stdio.h>
#include <stdlib.h>
struct node
{
    struct node *pleft;
    struct node *pright;
    int data;
};

void print_tree(struct node *proot)
{
    if (proot != NULL)
    {
        printf("{ %i", proot->data);
        if (proot->pleft != NULL || proot->pright != NULL)
        {
            printf("\n");
            print_tree(proot->pleft);
            printf("\n");
            print_tree(proot->pright);
            printf("\n}");
        }
    }
    else
        printf("{}");
}

void insertNode(struct node **proot, int data)
{
    if (*proot == NULL)
    {
        *proot = (struct node *)malloc(sizeof(struct node));
        (*proot)->data = data;
        (*proot)->pleft = NULL;
        (*proot)->pright = NULL;
    }
    else if (data < (*proot)->data)
        insertNode(&(*proot)->pleft, data);
    else
        insertNode(&(*proot)->pright, data);
}

int main()
{
    struct node *root = NULL;

    insertNode(&root, 9);
    insertNode(&root, 4);
    insertNode(&root, 20);
    insertNode(&root, 16);
    insertNode(&root, 10);
    insertNode(&root, 6);
    insertNode(&root, 8);
    print_tree(root);
}

void add_onc(struct node *p)
{
    if (p == NULL)
        return;
    p->data++;
    add_one(p->pleft);
    add_one(p->pright);
}