#include "darray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug 1

darray* da_alloc(int capacity){
	darray *pdarray = malloc(sizeof(darray));
	if (!pdarray) return NULL;

	pdarray->data = calloc(capacity, sizeof(char*));
	if (!pdarray->data) return NULL;
	
	pdarray->first = -1;
	pdarray->size = 0;
	pdarray->min_cap = capacity;
	pdarray->capacity = capacity;
	
	return pdarray;
}

void da_free(darray* A){

	for (int i=0; i<A->capacity; i++){
		free(A->data[i]);
	}
	free(A->data);
	free(A);
}

int da_push(darray* A, char* string){
	int index;//Index to insert
	
	if (A->first + A->size < A->capacity){
			index = A->first + A->size;
	}
	else {
			index = A->first - A->capacity + A->size;
	}
	
	if (A->capacity == A->size){
		A->data = realloc(A->data, (2*A->capacity)*sizeof(char*));
		if (!A) return 0;
		A->capacity = 2*A->capacity;
	}
	
	A->data[A->first + A->size + 1] = malloc(strlen(string)*sizeof(char));
	if (!A->data) return 0;
	strcpy(A->data[A->first + A->size + 1], string);
	
	if (A->size == 0 && A->first == -1) A->first++;
	A->size++;
	
	return 1;

}

char* da_pop(darray* A){
	int index = 0;//index to remove
	
	if (A->first + A->size <= A->capacity){
		index = A->first + A->size - 1;
	}
	else {
		index = A->first - A->capacity + A->size -1;
	}
	
	if (A->capacity <= 4*A->size && A->capacity > A->min_cap){
		A->data = realloc(A->data, (A->capacity)*sizeof(char*)*0.5);
		if (!A->data) return NULL;
		A->capacity = A->capacity/2;
	}
	
	if (A->size != 0) A->size--;
	
	return A->data[index];
}

int da_inject(darray* A, char* string){
	int index;//Index to insert

	if (A->capacity == A->size){
		A->data = realloc(A->data, A->capacity*2*sizeof(char*));
		if (!A->data) return 0;
		A->capacity = 2*A->capacity;
	}		
	
	if (A->first -1 >= 0){
		index = A->first - 1;
	}
	else{
		index = A->capacity - 1;
	}

	strcpy(A->data[index], string);
	A->size++;
	
	return 1;
}

char* da_eject(darray* A){
	int index = A->first;//Index to remove
	
	if (A->capacity <= 4*A->size && A->capacity > A->min_cap){
		A->data = realloc(A->data, (A->capacity)*sizeof(char*)*0.5);
		if (!A->data) return NULL;
		A->capacity = A->capacity/2;
	}

	if (A->size != -1) A->size--;
	
	return A->data[index];
}

char* da_first(darray* A){
	if (A->first != -1)	return A->data[A->first];
	return NULL;
}
	
char* da_last(darray* A){
	if (A->size != 0) return A->data[A->first + A->size];
	return NULL;
}

int da_is_empty(darray* A){
	return A->size == 0;
}

