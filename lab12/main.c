#include <stdio.h>
#include <string.h>
#include "bst.h"

int main(){

	char inst[20];//Command
	int arg = 0;//Key input
	int error = 0; //1 for success and 0 for failure
	node* p = NULL;//Auxiliary pointer
	tree* T = NULL;//Binary Search Tree pointer
	
	while (strcmp(inst, "terminar") != 0){
		scanf(" %s", &inst[0]);
		
		if(strcmp(inst, "criar") == 0){
			if (T){
				bst_free(T);
				T = calloc(1, sizeof(tree));
			}
			else{
				T = calloc(1, sizeof(tree));
			}
		}
		
		else if (strcmp(inst, "inserir") == 0){
			scanf(" %d", &arg);
			if (T){
				p = bst_search(T->root, arg);
				if (!p){
					error = bst_insert(T, arg);
					if (!error) printf("memoria insuficiente\n");
				}
			}
		}
		
		else if (strcmp(inst, "buscar") == 0){
			scanf(" %d", &arg);
			if (T){
				p = bst_search(T->root, arg);
				if (!p) 
					printf("%d nao esta na arvore\n", arg);
				else
					printf("%d esta na arvore\n", arg);
		  }
		}
		
		else if (strcmp(inst, "pre-ordem") == 0){
			if (T && T->root){
				printf("pre-ordem: ");
				bst_pre_order(T->root);
				printf("\n");
			}
			else
				printf("arvore vazia\n");
		}
		
		else if (strcmp(inst, "em-ordem") == 0){
			if (T && T->root){
				printf("em-ordem: ");
				bst_in_order(T->root);
				printf("\n");
			}
			else
				printf("arvore vazia\n");
		}
		
		else if (strcmp(inst, "pos-ordem") == 0){
			if (T && T->root){
				printf("pos-ordem: ");
				bst_post_order(T->root);
				printf("\n");
			}
			else
				printf("arvore vazia\n");
		}
		
		else if (strcmp(inst, "sucessor") == 0){
			scanf(" %d", &arg);
			if (T){
				p = bst_successor(T, arg);
				if (!p) 
					printf("nao ha sucessor de %d\n", arg);
				else 
					printf("sucessor de %d: %d\n", arg, p->key);
			}

		}
		
		else if (strcmp(inst, "predecessor") == 0){
			scanf(" %d", &arg);
			if (T){
				p = bst_predecessor(T, arg);
				if (!p) 
					printf("nao ha predecessor de %d\n", arg);
				else 
					printf("predecessor de %d: %d\n", arg, p->key);
			}
		}
		
		else if (strcmp(inst, "caminho-mais-longo") == 0){
			
			if (T){
				arg = height(T->root);
				if (!arg)
					printf("arvore vazia\n");
				else{
					path(T->root, arg);
				}
			}
			else{
				printf("arvore vazia\n");
			}
		}
		else if (strcmp(inst, "avl?") == 0){
			if (T){	
				arg = avl(T->root);
				if (arg) printf("sim\n");
				else printf("nao\n");
			}
			else{
				printf("sim\n");
			}
		}
		else if (strcmp(inst, "info") == 0){
				if (T){
					info(T);
				}
				else{
					printf("nos: 0, folhas: 0, altura: 0\n");
				}
		}

		else if (strcmp(inst, "remover") == 0){
			scanf(" %d", &arg);
			
			if (!T || !T->root){//Empty tree case
				p = NULL;
			}
			else {
				p = bst_search(T->root, arg);
				if (p){
					bst_delete(T,p);
				}
			}
		}
	}

	return 0;
}
