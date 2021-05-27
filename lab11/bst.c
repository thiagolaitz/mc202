#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "bst.h"


int bst_insert(tree* T, int data) {

  node* knot = calloc(1,sizeof(node));//Allocate a new node
  if (!knot)
    return 0;

  knot->key = data;

  if (T->root == NULL) {//Empty tree case
    T->root = knot;
    return 1;
  }

  node* p = T->root;
  node* pp = NULL;

  while (p != NULL) {
    pp = p;
    if (p->key > data)
      p = p->left;
    else
      p = p->right;
  }


  if (pp->key > data)
    pp->left = knot;
  else
    pp->right = knot;
    
  knot->parent = pp;

  return 1;
}

node* bst_search(node* p, int key) {

  if (p == NULL)//End of searching
    return NULL;

  if (p->key == key)//Key found
    return p;

  if (p->key < key)//Decide where to search
    return bst_search(p->right,key);
  else
    return bst_search(p->left,key);
}


//Release nodes
void bst_free_nodes(node* p) {

  if (p == NULL)
    return;

  bst_free_nodes(p->left);
  bst_free_nodes(p->right);
  free(p);
}

//Release tree
void bst_free(tree* T) {

  bst_free_nodes(T->root);
  free(T);
}

node* bst_successor(tree* T, int key){
	
	node *n = bst_search(T->root, key);
	if (!n)//Key doesn't exist in the tree
		return NULL;
	
	if (n->right){//Right case
		n = n->right;
		while (n->left){
			n = n->left;
		}
		return n;
	}
	
	node* p = n->parent;
	while (p && n==p->right){//Parent Case
		n = p;
		p = p->parent;
	}
	
	return p;
}

node* bst_predecessor(tree* T, int key){
	
	node *n = bst_search(T->root, key);

	if (!n)//Key doesn't exist in the tree
		return NULL;
	
	if (n->left){//Left case
		n = n->left;
		while (n->right){
			n = n->right;
		}
		return n;
	}
	
	node* p = n->parent;
	while (p && n==p->left){//Parent case
		n = p;
		p = p->parent;
	}
	
	return p;
}

//Print pre ordered data
void bst_pre_order(node* n){
	
	if (n){
		printf("%d ", n->key);
		bst_pre_order(n->left);
		bst_pre_order(n->right);
	}
}

//print in ordered data
void bst_in_order(node* n){
	
	if (n){
		bst_in_order(n->left);
		printf("%d ", n->key);
		bst_in_order(n->right);
	}
}

//print post ordered data
void bst_post_order(node* n){
	
	if (n){
		bst_post_order(n->left);
		bst_post_order(n->right);
		printf("%d ", n->key);
	}
}


node* bst_remove(tree* T, node* n, int key){

    if(n == NULL)//End of searching
        return NULL;

    if(n->key < key)//right case
        n->right = bst_remove(T,n->right,key);
    
    else if(n->key > key)//Left case
        n->left = bst_remove(T,n->left,key);
   
    else//Start removing
    {

        if(n->left == NULL && n->right == NULL)//Leaf case
        {
            free(n);
            return NULL;
        }
        
        else if(n->left == NULL)//At least one child
        {
            node* temp = n->right;
            free(n);
            return temp;
        }

        else if(n->right == NULL)
        {
            node* temp = n->left;
            free(n);
            return temp;
        }

        else//Two child case
        {
            node* replace = bst_successor(T,key);
            n->key = replace->key;
            n->right = bst_remove(T,n->right,replace->key);
        }
    }
    return n;
}


