#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
/*
Binary Search Tree
*/

struct node {

	int key;
	struct node* parent;
	struct node* right;
	struct node* left;
};
typedef struct node node;

struct tree {

	node* root;
};
typedef struct tree tree;

/*
Insert data into T. Return 0 in case of failure and 1 in case of success.
*/
int bst_insert(tree* T, int data);

/*
Search for the integer data in binary tree T. If successful returns a pointer to data node or a NULL pointer.
*/
node* bst_search(node* p, int key);

/*
Release memory allocated for the tree nodes.
*/
void bst_free(tree* T);

/*
Return a pointer to key successor if it exists. Return NULL if it doesn't exist. 
*/
node* bst_successor(tree* T, int key);

/*
Return a pointer to key predecessor if it exists. Return NULL if it doesn't exist. 
*/
node* bst_predecessor(tree* T, int key);

/*
Print pre-ordered data from bst on the screen.
*/
void bst_pre_order(node* n);

/*
Print in-ordered data from bst on the screen.
*/
void bst_in_order(node* n);

/*
Print post-ordered data from bst on the screen.
*/
void bst_post_order(node* n);

/*
Return a pointer for the new node after node n is deleted.
*/
node* bst_remove(tree* T, node* n, int key);
	


