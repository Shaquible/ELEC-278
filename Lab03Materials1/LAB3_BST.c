//LAB3_BST.c - Lab 03 -Keegan, Kelly
// LAB3_BST.C [140916]
//
// Code for ELEC278 Lab 3.  Some code has already been implemented.
// You will develop your own code - look for the comments.

/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2020.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */

#include <stdlib.h>
#include <stdio.h>
#include "Lab3_bst.h"

Node *initNode(Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)
	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
	}
	return n;
} //initNode()

Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree *t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k, v);
	return t;
} //initTree()

void printTreeExplanation(void)
// Prints hint to reader what to expect on screen
{
	static int done = 0;
	if (!done)
	{
		printf("First time explanation of tree display:\n");
		printf("Every node is displayed as a comma-separated pair within brackets:");
		printf(" (kk,vv)\n");
		printf("where kk is the key and vv is the value\n");
		printf("A tree starts with a curly bracket { and ends with a curly bracket }.\n");
		printf("An empty tree will be {}\n");
		printf("A tree with no children will be { (kk,vv),{},{} }\n");
		printf("If either subtree is populated, it will be shown using the same ");
		printf("technique as described above\n");
		printf("(Hint: Start at root - and then match up all the remaining\n");
		printf("brackets, then interpret what those bracket pairs are telling\n");
		printf("you.)\n============\n\n");
		done = 1;
	}
} //printTreeExplanation()

void printTree(Node *root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically knows the types in the tree node
	printTreeExplanation();
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%ld,%d),", root->key, *(int *)root->value);

	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)
		printTree(root->leftChild);
	else
		printf("{}");
	// Marker between left and right subtrees
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)
		printTree(root->rightChild);
	else
		printf("{}");
	// Close display of this tree with closing curly bracket
	printf("}");
} //printTree()

Node *find(Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))
		return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than root node key, so search right
		// subtree
		return find(k, root->rightChild);
	else
		// Key value sought is smaller than root node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k, root->leftChild);
} //find()

int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
	int result = BST_FAIL;
	// this if statement can only be true with first root (root of whole tree)
	if (root == NULL)
	{
		Node *n = initNode(k, v);
		root = n;
		return BST_SUCCESS;
	}

	// already exists in tree ==> can't insert
	if (root->key == k)
		result = BST_FAIL;
	else if (k < root->key)
	{
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else
		{
			// new Node becomes the left subtree
			Node *n = initNode(k, v);
			root->leftChild = n;
			result = BST_SUCCESS;
		}
	}
	else if (k > root->key)
	{ // test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k, v, root->rightChild);
		else
		{
			// no right subtree - new node becomes right subtree
			Node *n = initNode(k, v);
			root->rightChild = n;
			result = BST_SUCCESS;
		}
	}
	return result;
} //insert()

int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see a conditional expression in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
	return (a >= b) ? a : b;
} //intmax()

int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than larger height of node's two subtrees.
{
	int nodeheight = -1; // default returned for empty tree
	if (root != NULL)
	{
		//recursively calls for the height calculation of each child
		int leftH = height(root->leftChild);
		int rightH = height(root->rightChild);
		//adds the height of either the left or right tree depending on which is the larger
		nodeheight = 1 + intmax(leftH, rightH);
	}
	return nodeheight;

} //height()

Node *findParentHelper(Key k, Node *root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
	//checks if the left and right child has the key were looking for if they arent NULL
	if (root->leftChild != NULL)
	{
		if (k == root->leftChild->key)
			return root;
	}
	if (root->rightChild != NULL)
	{
		if (k == root->rightChild->key)
			return root;
	}
	//if the parent  wasn't found then it recursively calls itself on the left or right child to find the parent
	if (k > root->key)
	{
		return findParentHelper(k, root->rightChild);
	}
	if (k < root->key)
	{
		return findParentHelper(k, root->leftChild);
	}

} //findparenthelper()

Node *findParent(Key k, Node *root)
//
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	if (root == NULL)
		return root;
	// real root doesn't have parent so we make it parent of itself
	if (root->key == k)
		return root;
	// root has no children
	if ((root->leftChild == NULL) && (root->rightChild == NULL))
		return NULL;

	// Deal with cases where root has at least one child
	return findParentHelper(k, root);
} //findParent()

//might need to redo
void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
	// Deletion has 3 cases - no subtrees, only left or right subtree, or both
	// left and right subtrees.
	Node *deleteNode = n; // Save copy of pointer to node to delete.
	//for node with no child
	//sets the parents pointer to the node to be deleted to NULL
	if (n->leftChild == NULL && n->rightChild == NULL)
	{
		if (p->leftChild == n)
		{
			p->leftChild = NULL;
		}
		else
		{
			p->rightChild = NULL;
		}
		free(n);
		return;
	}
	//for nodes with two children
	if (n->leftChild != NULL && n->rightChild != NULL)
	{
		//find sucsessor node (the leftmost node in the right subtree)
		Node *current = n->rightChild;
		Node *prev = NULL;
		//finds the leftmost node in the right subtree and its parent node
		while (current->leftChild != NULL)
		{
			prev = current;
			current = current->leftChild;
		}
		//sets the node you want to delete to have the key and value of the sucsessor node
		//then deletes the sucsessor node and sets its parents pointer to it to NULL
		prev->leftChild = NULL;
		n->value = current->value;
		n->key = current->key;
		free(current);
		return;
	}
	//for node with one child
	//it will remove the node to be deleted and sets the parents pointer to it to be the one tree of the deleted node
	if (n->leftChild != NULL || n->rightChild != NULL)
	{
		if (p->leftChild == n)
		{
			if (n->leftChild != NULL)
			{
				p->leftChild = n->leftChild;
			}
			else
			{
				p->leftChild = n->rightChild;
			}
		}
		else
		{
			if (n->leftChild != NULL)
			{
				p->rightChild = n->leftChild;
			}
			else
			{
				p->rightChild = n->rightChild;
			}
		}
		free(n);
		return;
	}
} //delete()

int withdraw(Key k, Node *root, Node *n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);

	if (m != NULL)
	{
		// create a copy of the node with the same key and value
		n = initNode(m->key, m->value);
		p = findParent(k, root);
		// can delete the node
		delete (p, m);
		return 1;
	}

	return 0;
} //withdraw()
