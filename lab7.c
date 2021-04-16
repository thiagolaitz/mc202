#include <stdio.h>
#include <string.h>

#define max 1000

struct contato{
	char nome[51];//Nome
	char end[101];//Endereco
	char tel[13];//Telefone
	char ani[9];//Aniversario
};

void buscar(int index, char nome[51], struct contato *pcolecao){
	//Busca pelo nome
	int n = 0;//Numero de buscas positivas
	printf("Resultado da busca:\n");
	
	for(int k = 0; k<index; k++){
		if(strstr(pcolecao->nome, nome) != NULL){//Se possuir a substring
			printf("(%d) %s\t%s\t%s\t%s\n", (k+1), pcolecao->nome, 
			pcolecao->end, pcolecao->tel, pcolecao->ani);
			n++;
		}
		pcolecao++;
	}
	if(n == 0){
		printf("Nenhum contato.\n");
	}
}

void remover(char nome[51], int *index, struct contato *pcolecao){
	/*
	ultimo: index--
	outros: reordenacao + index--
	*/
	int n = 0;//Numero de contatos removidos
	
	for(int k = 0; k<*index; k++){
		if(strcmp(pcolecao->nome, nome) == 0){
			n++;
			if(k != max){//Caso outros
				*index -= 1;
				for(int t=0; t<(*index-k); t++){//Re-ordena o Struct
					*(pcolecao+t) = *(pcolecao+t+1);
				}
				k-=1;
			}
			else{
				*index -= 1;
			}
		}
		else{
			pcolecao++;
		}
	}
	
	printf("Contatos de %s removidos: %d.\n", nome, n);
}

void impressao(struct contato *pcolecao, int index){//Listagem de contatos
	int n = 0;
	printf("Listagem:\n");
	
	for(int k = 0; k < index; k++){
		printf("(%d) %s\t%s\t%s\t%s\n", (k+1), pcolecao->nome, 
		pcolecao->end, pcolecao->tel, pcolecao->ani);
		pcolecao++;
		n++;
	}
	
	if(n == 0){
		printf("Nenhum contato.\n");
	}
}


void inserir(struct contato *pcolecao, int *index){//Adiciona novos contatos em colecao
	char nome[51];
	char end[101];
	char tel[13];
	char ani[9];
	
	if(*index != max){//Espacos disponiveis
		scanf(" %[^\n]s", nome);
		scanf(" %[^\n]s", end);
		scanf(" %[^\n]s", tel);
		scanf(" %[^\n]s", ani);
		strcpy(pcolecao->nome, nome);
		strcpy(pcolecao->end, end);
		strcpy(pcolecao->tel, tel);
		strcpy(pcolecao->ani, ani);
		printf("Contato para %s inserido.\n", nome);
	}
	else{//Sem espacos disponiveis
		scanf(" %[^\n]s", nome);
		scanf(" %[^\n]s", end);
		scanf(" %[^\n]s", tel);
		scanf(" %[^\n]s", ani);
		printf("O contato nao foi inserido.\n");
		*index -= 1;
	}
}

int main(){
	char op = 0;//Salva a operacao desejada
	int index = 0;//Salva a primeira posicao livre de colecao
	char nome[51];//Recebe o nome de busca/remocao
	struct contato colecao[max];//Registro de contatos

	while(op != 'f'){
		scanf(" %c", &op);
		
		if(op == 'i'){
			//printf("Inserir\n");
			inserir(&colecao[index], &index);
			printf("\n");
			index++;
		}
		else if(op == 'r'){
			//printf("Remover\n");
			scanf(" %[^\n]s", nome);
			remover(nome, &index, colecao);
			printf("\n");
		}
		else if(op == 'b'){
			//printf("Busca\n");
			scanf(" %[^\n]s", nome);
			buscar(index, nome, colecao);
			printf("\n");
		}
		else if(op == 'p'){
			//printf("Impressao\n");
			impressao(colecao,index);
			printf("\n");
		}
	}

	return 0;
}
