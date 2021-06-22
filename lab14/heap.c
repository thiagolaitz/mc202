#include "heap.h"
#include <stdio.h>

int insert(heap* hp, int* i, int key, int cost){
	//check if key already exists
	//first insert at the end
	//Rearrange array until cost < parent cost
	
	if (i[key] != -1){
		return 0;
	}
	
	hp->pdata[hp->size].key = key;//Set values
	hp->pdata[hp->size].cost = cost;
	i[key] = hp->size;//Set I index
	
	if (hp->size == 0){//Empty case
		hp->size++;
		return 1;
	}

	//Non empty case.
	hp->size++; 
	int child = i[key];
	int parent = (i[key]-1)/2;
	
	//Swap until cost > parent cost
	while (parent >= 0 && cost < hp->pdata[parent].cost){
		swap(hp, i, child, parent);
		child = parent;
		parent = (parent-1)/2;
	}
	
	return 1;
}

void swap(heap* hp, int* i, int root, int smallest){
	//Swap two heap positions
	int cost_aux = hp->pdata[root].cost;
	int key_aux = hp->pdata[root].key;
	int index_aux = root;
	i[hp->pdata[root].key] = smallest;//i1
	i[hp->pdata[smallest].key] = index_aux;//i2
	hp->pdata[root].cost = hp->pdata[smallest].cost;
	hp->pdata[root].key = hp->pdata[smallest].key;
	hp->pdata[smallest].cost = cost_aux;
	hp->pdata[smallest].key = key_aux;

}

void heapify(heap* hp, int* i, int root){

    int smallest = root; //Initialize as root
    int l = 2 * root + 1; // left child = 2*i + 1
    int r = 2 * root + 2; // right child = 2*i + 2
 
    //Case: left child is smaller than root
    if (l < hp->size && hp->pdata[l].cost < hp->pdata[smallest].cost)
        smallest = l;
 
    //Case: right child is smaller than smallest
    if (r < hp->size && hp->pdata[r].cost < hp->pdata[smallest].cost)
        smallest = r;
 
    //Case: smallest is not the root
    if (smallest != root) {
    	
        swap(hp, i, root, smallest);
 
        //heapify the sub-tree
        heapify(hp, i, smallest);
    }
}

int min_heap(heap* hp, int* i){
//Remove first element and return 1. If heap is empty return 0
	if (hp->size == 0){
		printf("heap vazio\n");
		return 0;
	}
	printf("minimo {%d,%d}",hp->pdata[0].key, hp->pdata[0].cost);
	
	int cost = hp->pdata[hp->size-1].cost;//cost of last element
	int key = hp->pdata[0].key;//key removed
	i[key] = -1;//set to -1 
	key = hp->pdata[hp->size-1].key;
	hp->pdata[0].key = key;
	hp->pdata[0].cost = cost;
	hp->size--;
	heapify(hp, i, 0);
	
	printf("\n");
	
	return 1;
}

int reduce(heap* hp, int* i, int key, int cost){
	//check if key exists
	//Change key cost
	//Rearrange array until cost < parent cost
	
	//Key doesn't exist in the heap.
	if (i[key] == -1){
		return 0;
	}
	
	int child = i[key];
	int parent = (i[key]-1)/2;
	hp->pdata[i[key]].cost = cost;
	
	//Swap until cost > cost parent
	while (parent >= 0 && cost < hp->pdata[parent].cost){
		swap(hp, i, child, parent);
		child = parent;
		parent = (parent-1)/2;
	}
	
	return 1;
}

void print_heap(heap* hp){
	
	for (int k = 0; k<hp->size; k++){
		printf("%d: (%d;%d) //", k, hp->pdata[k].key, hp->pdata[k].cost);
	}
	printf("\n");
}

void print_i(int* i, int n){

	for (int k=0; k<n; k++){
		printf("%d->%d ", k, i[k]);
	}
	printf("\n");
}
