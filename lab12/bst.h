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
Print the longest and rightmost path from a binary tree.
*/
void path(node* n, int height);

/*
Print if a binary tree is AVL.
*/
int avl(node* n);

/*
Print the number of nodes, leafs and maximum height. Print zero if tree is empty.
*/
void info(tree* T);

/*
Return the maximum height from a binary tree.
*/
int height(node* n);

/*
Deletes node z. If necessary, it uses z sucessor as a change of a two-child node.
*/
void bst_delete(tree* T, node* z);
