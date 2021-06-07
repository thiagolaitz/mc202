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


void replace(tree* T, node* u, node* v){
	if (!u->parent){
		T->root =  v;
	}
	else if (u == u->parent->left){
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if (v){
		v->parent = u->parent;
	}
}

void bst_delete(tree* T, node* z){

		node* y;
		if (!z->left){
			replace(T, z, z->right);
		}
		else if (!z->right){
			replace(T, z, z->left);
		}
		else{
			y = z->right;
			while (y->left){
				y = y->left;
			}
			if (y->parent != z){
				replace(T, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			replace(T, z, y);
			y->left = z->left;
			y->left->parent = y;
		}
}

//Return the maximum value between a and b
int max(int a, int b){

	if (a>=b){
		return a;
	}
	else{
		return b;
	}
}

int height(node* n){
	
	if (!n) return 0;
	
	return 1 + max(height(n->left), height(n->right));
}

int avl(node* n){

	int left_height;
	int right_height;
	
	if (!n) return 1;
	
	left_height = height(n->left);
	right_height = height(n->right);
	
	if (abs(left_height-right_height) <= 1 && avl(n->left) && avl(n->right)) {
		return 1;
	}
	
	return 0;
}

/*
This function receives as an input the root node and the maximum height of a binary search tree. Using the given information,
it searches the rightmost path comparing the current path height and the maximum height.
It is done by always trying to go using the right node; 
at the end of a path, it backs to the point where you have gone to the right but could have gone to the left.
For mapping the path, it uses an auxiliary vector which has the values 0(left), 1(right), and -1(back). 
*/
void path(node* n,int height){
		int array[height];
		int index = 0;
		node* root = n;
		
		while (index != height - 1){
			if (n->right != NULL){
				n = n->right;
				array[index] = 1;
				index++;
			}
			else if (n->left != NULL) {
				n = n->left;
				array[index] = 0;
				index++;
			}
			else {
				
				while (array[index] != 1 || n->left==NULL){
					n = n->parent;
					index--;
				}
				n = n->left;
				array[index] = 0;
				index++;
			}
		}
		printf("caminho mais longo e mais a direita: ");
		n = root;
		for (int i=0; i<=index; i++){
			printf("%d ", n->key);
			if (array[i] == 0){
				n = n->left;
			}
			else {
				n = n->right;
			}
		}
		printf("\n");
}

int nnodes(node* n){
	
	int aux = 1;
	if (!n) 
		return 0;
	else{
		aux += nnodes(n->left);
		aux += nnodes(n->right);
		return aux;
	}
}

int nleaf(node* n){

	if (!n) return 0;
	
	if(!n->left && !n->right){
		return 1;
	}
	else{
		return nleaf(n->left) + nleaf(n->right);
	}
}

void info(tree* T){
	int h = height(T->root);
	int nodes = nnodes(T->root);
	int leaf = nleaf(T->root);
	
	if (!T->root){
		printf("nos: 0, folhas: 0, altura: 0\n");
	}
	else{
		printf("nos: %d, folhas: %d, altura: %d\n", nodes, leaf, (h-1));
	}
}


