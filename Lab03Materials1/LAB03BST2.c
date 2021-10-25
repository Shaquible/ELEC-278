#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{
    char password[13];
    struct Node *left;
    struct Node *right;
    int key;
} Node;

Node *newnode(int key, char data[]);
Node *insert(Node *root, int key, char data[]);
int countNodes(Node *root);
int isSort(Node *root);
int main(void)
{

    char *filename = "IDENTS.txt";
    FILE *infile = fopen(filename, "r");
    char temp2[13];
    int temp1;
    char line[256];
    int i = 0;
    Node *root = NULL;
    while (fgets(line, sizeof(line), infile) != NULL)
    {
        sscanf(line, "%010d    %s\n", &temp1, &temp2);
        root = insert(root, temp1, temp2);
    }
    printf("%i, %i\n", isSort(root), countNodes(root));
}

Node *newnode(int key, char data[])
{

    Node *new = (Node *)malloc(sizeof(Node));
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    strcpy(new->password, data);
    return new;
}

Node *insert(Node *root, int key, char data[])
{
    if (root == NULL)
    {
        return newnode(key, data);
    }
    if (root->key > key)
    {
        root->left = insert(root->left, key, data);
    }
    if (root->key < key)
    {
        root->right = insert(root->right, key, data);
    }
    if (root->key == key)
    {
        strcpy(root->password, data);
        return root;
    }
    return root;
}

int isSort(Node *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    if (root->left == NULL && root->right != NULL)
    {
        if (isSort(root->right) == 1)
        {
            return 1;
        }
        else
            return 0;
    }
    if (root->left != NULL && root->right == NULL)
    {
        if (isSort(root->left) == 1)
        {
            return 1;
        }
        else
            return 0;
    }
    if (root->key > root->left->key && root->key < root->right->key)
    {
        if (isSort(root->left) == 1 && isSort(root->right) == 1)
            return 1;
        else
            return 0;
    }
}

int countNodes(Node *root)
{
    int count = 0;
    if (root->left != NULL)
    {
        count += 1 + countNodes(root->left);
    }
    if (root->right != NULL)
    {
        count += 1 + countNodes(root->right);
    }
    return count;
}

Node *findParent(Node *root, Node *n)
{
}