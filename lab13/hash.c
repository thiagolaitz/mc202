#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

/*
States: 
-2 = removed
-1 = NIL
0 = Occupied
*/

unsigned long djb2(unsigned char* str){
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)){
		hash = ((hash << 5) + hash) ^ c; //hash * 33 XOR c
	}

	return hash;
}

//Search for an available position (removed or empty value)
int double_hashing(hashItem* hashTable, int m, unsigned long djb2_value){
	int pos = 0;
	int i = 0;
	pos = djb2_value%m;
	
	while (hashTable[pos].state != -1 && hashTable[pos].state != -2){
		i++;
		pos = (djb2_value%m + i*(1+djb2_value%(m-2)))%m;
	}
	
	return pos;
}

void insert(unsigned char* text, unsigned long djb2_value, int timestamp, hashItem* hashTable, int m){
	
	int pos;
	pos = double_hashing(hashTable, m, djb2_value);
	hashTable[pos].state = 0;
	hashTable[pos].timestamp = timestamp;
	hashTable[pos].pdata = malloc(strlen((const char*)text)*sizeof(unsigned char));
	strcpy((char*)hashTable[pos].pdata, (char*)text); 
}

int search(unsigned char* text, unsigned long djb2_value, hashItem* hashTable, int m){
	int pos;
	int i = 0;
	pos = djb2_value%m;
	int aux = -1;
	
	while (hashTable[pos].state != -1){
	 	if (strcmp((const char*)text, (const char*)hashTable[pos].pdata) == 0){//match case
	 		aux = hashTable[pos].timestamp;
	 		break;
	 	}
		i++;
		pos = (djb2_value%m + i*(1+djb2_value%(m-2)))%m;
	}
	
	return aux;
}

void remove_item(unsigned char* text, unsigned long djb2_value, int timestamp, hashItem* hashTable, int m){
	int pos;
	int i = 0;
	pos = djb2_value%m;
	
	while (hashTable[pos].state != -1){
	 	if (strcmp((char*)text, (char*)hashTable[pos].pdata) == 0){//Match case
	 		hashTable[pos].timestamp = -1;
	 		hashTable[pos].state = -2;
	 		free(hashTable[pos].pdata);	
	 		break;
	 	}
		i++;
		pos = (djb2_value%m + i*(1+djb2_value%(m-2)))%m;
	}
}


