#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "li.h"

li* li_alloc() {
  return calloc(1,sizeof(li));
}

void li_free(li* L) {

  node* p = L->head;
  node* n = NULL;

  while (p != NULL) {
    n = p->next;
    free(p);
    p = n;
  }

  free(L);
}


int li_insert(li* L, int data) {

  node* n = malloc(sizeof(node));
  if (n == NULL)
    return 0;

  n->data = data;
  n->next = L->head;
  L->head = n;

  return 1;
}

void li_print(li* L) {

  node* p = L->head;
  printf("{");

  while (p != NULL && p->next != NULL) {
    printf("%d, ",p->data);
    p = p->next;
  }

  if (p != NULL)
    printf("%d",p->data);

  printf("}");
}

li* li_union(li* A, li* B){
	int exist = 0;//check if C contains the data
	
	li* C = calloc(1,sizeof(li));
	if (!C) return NULL;
	
	node* n_C;
	node* n = A->head;

	while (n) {//Insert node A to C	
		li_insert(C,n->data);	
		n = n->next;
	}
	
	n_C = C->head;
	n = B->head;
	while (n){//Compare nodes B and C
		while (n_C){
			if (n_C->data == n->data) exist = 1;
			n_C = n_C->next;
		}
		
		if (exist == 0){
			li_insert(C,n->data);	
		}
		exist = 0;
		n_C = C->head;
		n = n->next;
	}
	
	return C;
}

li* li_intersection(li* A, li* B){
	int exist = 0;//check if C contains the data
	
	li* C = calloc(1,sizeof(li));
	if (!C) return NULL;
	
	node* n_A = A->head;
	node* n_B= B->head;
	
	while (n_A) {//Compare nodes A and B
		while (n_B){
			if (n_A->data == n_B->data) exist = 1;
			n_B = n_B->next;
		}
		
		if (exist == 1){
			li_insert(C,n_A->data);	
			
		}
		exist = 0;
		n_B = B->head;
		n_A = n_A->next;
	}
	
	return C;
}


li* li_difference(li* A, li* B){
	int exist = 0;//check if B contains the data
	
	li* C = calloc(1,sizeof(li));
	if (!C) return NULL;
	
	node* n_A = A->head;
	node* n_B = B->head;

	while (n_A) {//A - B
		while (n_B){
			if (n_B->data == n_A->data) exist = 1;
			n_B = n_B->next;
		}
		if (exist == 0){
			li_insert(C,n_A->data);	
		}
		exist = 0;
		n_B = B->head;
		n_A = n_A->next;
	}

	return C;

}
