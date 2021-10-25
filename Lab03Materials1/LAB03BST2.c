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

Node *minNode(Node *root);
Node *newnode(int key, char data[]);
Node *insert(Node *root, int key, char data[]);
int countNodes(Node *root);
int isSort(Node *root);
Node *delete (Node *root, int key);
Node *findNode(int key, Node *root);
Node *findParent(Node *root, int key);
int main(void)
{

    char *filename = "IDENTS.txt";
    char *deletename = "DELETES.txt";
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
    fclose(infile);
    FILE *deletefile = fopen(deletename, "r");
    while (fgets(line, sizeof(line), deletefile) != NULL)
    {
        sscanf(line, "%d", &temp1);
        root = delete (root, temp1);
    }
    printf("%i\n", isSort(root));
    printf("%i\n", countNodes(root));
}
Node *findNode(int key, Node *root)
{
    Node *current = root;
    while (current->key != key)
    {
        if (key > current->key)
            current = current->right;
        else
            current = current->left;
    }
    return current;
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
    if (root == NULL)
        return 1;
    if (root->left != NULL && root->left->key > root->key)
        return 0;
    if (root->right != NULL && root->right->key < root->key)
        return 0;
    if (!isSort(root->left) || !isSort(root->right))
        return 0;
    return 1;
}

int countNodes(Node *root)
{
    if (root == NULL)
        return 0;
    int count = 1 + countNodes(root->left) + countNodes(root->right);
    return count;
}

Node *delete (Node *root, int key)
{
    //this part searches through the tree for the key to delete and has the base case
    if (root == NULL)
    {
        return NULL;
    }
    if (key < root->key)
    {
        root->left = delete (root->left, key);
    }
    else if (key > root->key)
    {
        root->right = delete (root->right, key);
    }
    else
    {

        //no children or one child
        //if both children or null the first case is called and then when called again it will trigger the base case and return null
        //pushes the right branch onto the current place of the node
        if (root->left == NULL)
        {
            Node *tmp = root->right;
            free(root);
            return tmp;
        }
        //pushes the left branch onto the current place of the node
        if (root->right == NULL)
        {
            Node *tmp = root->left;
            free(root);
            return tmp;
        }
        //two children
        else
        {
            //finds the smallest node in the right tree to take the place of the node so that the right branch is greater and the left branch is lower
            Node *tmp = minNode(root->right);
            //copies the data over
            strcpy(root->password, tmp->password);
            root->key = tmp->key;
            //calls on the left most node in the right tree to be deleted since it has been moved to the place of the current node
            root->right = delete (root->right, tmp->key);
        }
    }
    return root;
}

Node *minNode(Node *root)
{
    if (root->left != NULL)
    {
        return minNode(root->left);
    }
    return root;
}