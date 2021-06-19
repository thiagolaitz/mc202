#include <stdio.h>
#include <string.h>
#include "hash.h"

int main(){
	char command = 'q';
	int m = 6257;//Nearest prime number to 5000/0.8
	hashItem hashTable[m];
	int timestamp = -1;
	unsigned long djb2_value;
	unsigned char text[251];
	int aux;//receive the search value
	
	for (int k=0; k<m; k++){//Define default values for the hashtable
		hashTable[k].state = -1;
		hashTable[k].timestamp = -1;
	}
	
	while (command != 'f'){
		scanf(" %c", &command);
		if (command == 'i'){//Insert case
			scanf("%*c");
			scanf("%[^\n]hhu", &text[0]);
			djb2_value = djb2(text);
			if (search(text, djb2_value, hashTable, m) != -1){
				printf("[%s] ja esta na tabela\n", text);
			}
			else{
				timestamp++;
				insert(text, djb2_value, timestamp, hashTable, m);
				printf("[%s] foi inserida\n", text);
			}
		}
		else if (command == 'b'){//search case
			scanf("%*c");
			scanf("%[^\n]hhu", &text[0]);
			djb2_value = djb2(text);
			aux = search(text, djb2_value, hashTable, m);
			if (aux != -1){
				printf("[%s] esta na tabela, timestamp %d\n", text, aux);
			}
			else {
				printf("[%s] nao esta na tabela\n", text);
			}
		}
		else if (command == 'r'){//remove case
			scanf("%*c");
			scanf("%[^\n]hhu", &text[0]);
			djb2_value = djb2(text);
			aux = search(text, djb2_value, hashTable, m);
			if (aux != -1){
				remove_item(text, djb2_value, timestamp, hashTable, m);
				printf("[%s] foi removida\n", text);
			}
			else {
				printf("[%s] nao esta na tabela\n", text);
			}
		}
		text[0] = '\0';//Reset text
	}
	return 0;
}
