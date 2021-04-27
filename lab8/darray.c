#include "darray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define debug 1

char** resize(darray *A, float factor){
	//shrinks or swell A->data by a factor and reallocates data index
	char** buffer;
	buffer = calloc(A->size, sizeof(char*));
	
	int index = A->first;

	for (int i=0; i<A->size; i++){
		buffer[i] = malloc((strlen(A->data[index])+1) * sizeof(char));
		strcpy(buffer[i], A->data[index]);
		free(A->data[index]);
		if (index+1 == A->capacity){
			index=0;
		}
		else{
			index++;
		}
	}
	
	A->data = realloc(A->data, (factor*A->capacity)*sizeof(char*));
	
	i = 0;
	for (int i=0; i<A->size; i++){
		A->data[i] = malloc((strlen(buffer[i])+1)*sizeof(char));
		strcpy(A->data[i], buffer[i]);
		free(buffer[i]);
		i++;
	}
	
	free(buffer);
	A->capacity = factor*A->capacity;
	A->first = 0;
	
	#ifdef debug
	printf("New Capacity: %d\n", A->capacity);
	printf("First: %d\n", A->capacity);
	#endif
	
	return A->data;
}

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

	int index = A->first;
	if (A->first !=-1){	
		for (int i=0; i<A->size; i++){
			free(A->data[index]);
			i++;
			if (index == A->capacity){
				index=0;
			}
			else{
				index++;
			}
		}
	}
	free(A);
}

int da_push(darray* A, char* string){
	int index;//Index to insert
	
	if (A->capacity == A->size){
		A->data = resize(A,2.0);
		if (!A->data) return 0;

	}
	
	if (A->first + A->size < A->capacity){
		if (A->first != -1){
			index = A->first + A->size;
		}
		else {
			index = 0;
		}
	}
	else {
			index = A->first - A->capacity + A->size;
	}
	
	A->data[index] = malloc((strlen(string)+1)*sizeof(char));
	if (!A->data) return 0;
	strcpy(A->data[index], string);
	
	if (A->size == 0 && A->first == -1) A->first++;
	A->size++;
	
	#ifdef debug
	printf("Index: %d\n", index);
	printf("Size: %d\n", A->size);
	#endif
	
	return 1;

}

char* da_pop(darray* A){
	
	if (A->capacity >= 4*(A->size-1)&& A->capacity > A->min_cap){
		A->data = resize(A,0.5);
		if (!A->data) return NULL;
	}
	
	int index = 0;//index to remove
	
	if (A->first + A->size <= A->capacity){
		index = A->first + A->size - 1;
	}
	else {
		index = A->first - A->capacity + A->size -1;
	}
	
	
	if (A->size != 0) {
		A->size--;
		return A->data[index];
	}
	else{
		return NULL;
	}
}

int da_inject(darray* A, char* string){
	int index;//Index to insert

	if (A->capacity == A->size){
		A->data = resize(A,2.0);
		if (!A->data) return 0;
	}		
	
	if (A->first -1 >= 0){
		index = A->first - 1;
	}
	else{
		index = A->capacity - 1;
	}

	A->data[index] = malloc((strlen(string)+1)*sizeof(char));
	if (!A->data) return 0;
	strcpy(A->data[index], string);
	
	A->first = index;
	A->size++;
	
	#ifdef debug
	printf("Size: %d\n", A->size);
	printf("First: %d\n", A->first);
	#endif
	
	return 1;
}

char* da_eject(darray* A){
	
	if (A->capacity >= 4*(A->size-1) && A->capacity > A->min_cap){
		A->data = resize(A,0.5);
		if (!A->data) return NULL;
	}
	int index = A->first;//Index to remove

	if (A->size != 0) A->size--;
	
	if (A->first + 1 < A->capacity){
		A->first++;
	}
	else{
		A->first = 0;
	}
	
	#ifdef debug
	printf("Removed: %s\n", A->data[index]);
	#endif
	return A->data[index];
	
}

char* da_first(darray* A){
	if (A->first != -1)	return A->data[A->first];
	return NULL;
}
	
char* da_last(darray* A){
	int index;
	if (A->first + A->size <= A->capacity){
		index = A->first + A->size - 1;
	}
	else {
		index = A->first - A->capacity + A->size -1;
	}
	if (A->size == 0){
		return NULL;
	}
	
	return A->data[index];
}

int da_is_empty(darray* A){
	return A->size == 0;
}

