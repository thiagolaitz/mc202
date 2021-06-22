#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main(){
	int n = 0;//Heap max length
	char command = 'o';//Input command
	int key,cost;//Input arguments
	
	//Set default heap values
	scanf("%d\n", &n);
	heap* hp = malloc(sizeof(heap));
	node* pdata = calloc(n, sizeof(node));
	hp->pdata = pdata;
	hp->size = 0;
	
	//Set default values ​​of the array of index i
	int i[n];
	for (int k=0; k<n; k++){
		i[k] = -1;
	}

	while (command != 't'){
		scanf(" %c", &command);
		if (command == 'i'){
			scanf(" %d %d", &key, &cost);
			insert(hp, i, key, cost);
		}
		else if (command == 'd'){
			scanf(" %d %d", &key, &cost);
			reduce(hp, i, key, cost);
		}
		else if (command == 'm'){
			min_heap(hp, i);
		}
		else if (command == 'p'){
			printf("index: (Key;Cost) //\n");
			print_heap(hp);
		}
		else if (command == 'a'){
			printf("Array I = ");
			print_i(i , n);
		}
	}

	return 0;
}
