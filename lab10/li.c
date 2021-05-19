#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "li.h"

#define debug 1

void li_free(li* L){
	
	node* n = L->head;
	node* n_next;
	
	while (n) {
		n_next = n->next;
		free(n);
		n = n_next;
	}
	
	free(L);
}

void li_print(li* L){

	printf("\nPrint: \n");
	
	node* p = L->head;
	
	while (p){
		printf("%d ", p->data);
		p = p->next;
	}
}


tuple* li_alloc(int n_size){

	li* L1 = malloc(sizeof(li*));
	li* L2 = malloc(sizeof(li*));
	li* L3 = malloc(sizeof(li*));
	
 	node* n1 = malloc(sizeof(node*));
 	node* n2 = malloc(sizeof(node*));
 	node* n3 = malloc(sizeof(node*));
 	
 	L1->head = n1;
	n1->data = 1;
	L2->head = n2;
	n2->data = 1;
	L3->head = n3;
	n3->data = 1;
	
	for (int i=2; i<=n_size; i++){
		node* k1 = malloc(sizeof(node*));
		node* k2 = malloc(sizeof(node*));
		node* k3 = malloc(sizeof(node*));
		
		n1->next = k1;
		n1 = n1->next;
		n1->data = i;
		
		n2->next = k2;
		n2 = n2->next;
		n2->data = i;
		
		n3->next = k3;
		n3 = n3->next;
		n3->data = i;
	}
	
	tuple* L = malloc(sizeof(tuple*));
	L->t1 = L1;
	L->t2 = L2;
	L->t3 = L3;
	
	return L;
}

int li_mtf(li* L, int* num, int r){
	
	int mtf = 0;		
	
	node* n = NULL;
	node* previous = NULL;
	node* next = NULL;	
	
	for (int q=0; q<r; q++){
		n = L->head;
		mtf++;
		
		while (num[q] != n->data){
			previous = n;
			n = n->next;
			next = n->next;
			mtf++;
		}
		
		if (previous) {
			previous->next = next;
			n->next = L->head;
		}
		previous = NULL;
		L->head = n;
	}
	
	return mtf;
}

int li_transp(li* L, int* num, int r){

	int transp = 0;	
	
	node* n = NULL;
	node* previous = NULL;
	node* p_previous = NULL;
	node* next = NULL;
	
	int cont =0;
	for (int q=0; q<r; q++){
		n = L->head;
		transp++;
		
		while (num[q] != n->data){
			cont++;
			p_previous = previous;
			previous = n;
			n = n->next;
			next = n->next;
			transp++;
		}
		
		if (cont!=0){
			n->next = previous;
			previous->next = next;
			if (cont < 2) {
				L->head = n;
			}
			else{
				p_previous->next = n;
			}
			p_previous = NULL;
		}
		cont = 0;

	}
	
	return transp;
}

//Remove from pos (!=0) and insert at pos_in position. Return L updated.
li* li_remove(li* L, int pos, int pos_in){
	
	node* previous = NULL;
	node* next = NULL;
	node* n = L->head;
	
	for (int i=0; i<pos; i++){
		previous = n;
		n = n->next;
		next = n->next;
	}
	previous->next = next;
	
	//insert n at pos_in position // Fix it
	node* data = n;
	n = L->head;
	if (pos_in == 0){
		L->head = data;
		data->next = n;
	}
	else{
		for (int i=0; i<pos_in; i++){
			previous = n;
			n = n->next;
		}
		previous->next = data;
		data->next = n;
	}
	
	return L;
}

int li_count(li* L, int* num, int r, int N){
	int count = 0;
	
	int* counter = malloc(N*sizeof(int));
	
	int pos = 0;
	int pos_in = 0;
	
	for (int k =0; k<N; k++){
		counter[k] = 0;
	}
	
	node* n;
	//r loop
	//find number
	//rearrange list {Remove and insert at right index}
	for (int q=0; q<r; q++){
		n = L->head;
		count++;
		
		while (num[q] != n->data){
			count++;
			n = n->next;
			pos++;
		}
		
		//find position;
		for (int k=0; k<N; k++){
			if (counter[pos]+1 >= counter[k]){
				pos_in = k;
				k = N;
			}
		}		
		
		//reorders counter array and increment
		int aux = counter[pos_in];

		counter[pos_in] = counter[pos] + 1;
				
		int aux2 = aux;
		for (int i=pos_in+1; i<pos+1; i++){
			aux = counter[i];
			counter[i] = aux2;
			aux2 = aux;
		}
		
		if (pos != 0){
			L = li_remove(L,pos,pos_in);
		}
	
		pos = 0;
	}
	
	free(counter);
	
	return count;
}
