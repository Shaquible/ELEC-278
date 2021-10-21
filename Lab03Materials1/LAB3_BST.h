// LAB3_BST.H [140916]
// Header file to be used with code for ELEC278 Lab 3.
//
// 201015	DFA	Corrected wrong prototype for withdraw() (not "widthdraw()")

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

typedef int Key;

#define BST_FAIL 0	  // return value when BST function fails
#define BST_SUCCESS 1 // return value when BST function succeeds

// Node in tree has key and pointer to value associated with key.
// Also contains structural components - two pointers to left and
// right subtrees.
typedef struct Node
{
	Key key;
	void *value;
	struct Node *leftChild, *rightChild;
} Node, pNode;

// Tree is basically pointer to top node in a tree.
typedef struct Tree
{
	Node *root;
} Tree;
