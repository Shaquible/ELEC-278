//LAB03BST2.c - Lab 03 -Keegan, Kelly
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defines the node with a key, password and two children
typedef struct Node
{
    char password[13];
    struct Node *left;
    struct Node *right;
    int key;
} Node;

//function definitions
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
    //declares filenames for the text files
    char *filename = "IDENTS.txt";
    char *deletename = "DELETES.txt";
    char *lookup = "LOOKUPS.txt";
    //opens the file with the keys and passwords
    FILE *infile = fopen(filename, "r");
    //temp variables for the key, password and line for the scanning in of data
    char temp2[13];
    int temp1;
    char line[256];
    //defines the root of the tree
    Node *root = NULL;
    //scans in the data from the file and inserts it into the tree
    while (fgets(line, sizeof(line), infile) != NULL)
    {
        sscanf(line, "%010d    %s\n", &temp1, &temp2);
        root = insert(root, temp1, temp2);
    }
    //checks if the tree is sorted and ends the program if it is not
    if (isSort(root) == 0)
    {
        return 0;
    }
    //prints the number of nodes
    printf("BST NODES:  %i\n", countNodes(root));
    //closes the file
    fclose(infile);
    //opens the file with nodes to be deleted
    infile = fopen(deletename, "r");
    //scans in the data from the file and deletes the node
    while (fgets(line, sizeof(line), infile) != NULL)
    {
        sscanf(line, "%d", &temp1);
        root = delete (root, temp1);
    }
    //checks that the data is sorted again and ends the program if it is not
    if (isSort(root) == 0)
    {
        return 0;
    }
    //prints the number of nodes after deletion
    printf("NODES AFTER DELETES %i\n", countNodes(root));
    fclose(infile);
    //opens the file for lookups
    infile = fopen(lookup, "r");
    //scans in the key of the node to lookup
    while (fgets(line, sizeof(line), infile) != NULL)
    {
        sscanf(line, "%d", &temp1);
        Node *temp = findNode(temp1, root);
        char id[11];
        for (int j = 0; j < 10; j++)
        {
            id[j] = line[j];
        }
        id[10] = '\0';
        //prints NOT FOUND if the key is not in the tree
        if (temp == NULL)
        {

            printf("ID %s PASSWORD <%s>\n", id, "NOT FOUND");
        }
        //prints the id and password if the node is in the tree
        else
        {
            printf("ID %s PASSWORD <%s>\n", id, temp->password);
        }
    }
    fclose(infile);
}

//searches the BST for the node and then returns it
Node *findNode(int key, Node *root)
{
    Node *current = root;
    while (current->key != key)
    {
        if (key > current->key)
            current = current->right;
        else
            current = current->left;
        if (current == NULL)
        {
            return NULL;
        }
    }
    return current;
}

//mallocs the node, assigns the key and password, and returns the node
Node *newnode(int key, char data[])
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    strcpy(new->password, data);
    return new;
}

//finds the appropriate place to insert the node and inserts it
//function is called recursively to find where to insert the node
Node *insert(Node *root, int key, char data[])
{
    //if the tree is empty, the node is inserted at the root
    if (root == NULL)
    {
        return newnode(key, data);
    }
    //if the key is less than the root, the node is inserted to the left
    if (root->key > key)
    {
        root->left = insert(root->left, key, data);
    }
    //if the key is greater than the root, the node is inserted to the right
    else if (root->key < key)
    {
        root->right = insert(root->right, key, data);
    }
    //if the key is equal to the root, then the password is overwritten
    else if (root->key == key)
    {
        strcpy(root->password, data);
        return root;
    }
    return root;
}

//checks if the tree is sorted, returns 1 if it is and 0 if it is not
int isSort(Node *root)
{
    //base case that the root is NULL
    if (root == NULL)
        return 1;
    //if the left tree key is greater than the root key then it isnt sorted and 0 is returned
    if (root->left != NULL && root->left->key > root->key)
        return 0;
    //if the right tree key is less than the root key then it isnt sorted and 0 is returned
    if (root->right != NULL && root->right->key < root->key)
        return 0;
    //if either of the subtrees arent sroted then 0 is returned, this will be recursively called for all nodes unless a node isnt sorted
    if (!isSort(root->left) || !isSort(root->right))
        return 0;
    //1 is returned if all nodes below the root are sorted
    return 1;
}

//counts the number of nodes in the tree
int countNodes(Node *root)
{
    //base case is the root is null
    if (root == NULL)
        return 0;
    //recursively calls the function to count the nodes in the left and right subtrees
    int count = 1 + countNodes(root->left) + countNodes(root->right);
    //returns the total nodes from the root and below
    return count;
}

Node *delete (Node *root, int key)
{
    //this part searches through the tree for the key to delete and has the base case
    //the entire tree should be updated in thi process if there are any changes
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
//returns the minimum node in the tree from below the root
Node *minNode(Node *root)
{
    //keeps searching as long as the left child of the node isnt NULL
    if (root->left != NULL)
    {
        return minNode(root->left);
    }
    //returns the sent node if its left child is NULL and thus it is the lowest node in the tree from below the root initially sent
    return root;
}