#include <stdio.h>
#include <string.h>
#define nsenhas 30
#define max_length 9

char senha[nsenhas][max_length];
int n;//indice do array senha
int val[nsenhas];//Recebe o resultado da analise

void valido(int res){//recebe o resultado
	// 0 = in vogal
	// 1 = aceitavel
	// 2 = in consec
	// 3 = in letra
	// 4 = in digito
	// 5 = in tamanho
	
	val[n] = res;
}

void consec(){
	//Verifica se possui +3 consoantes em sequencia
	//Verifica se nao possui +3 vogais em sequencia
	int c_seq = 0;
	char vog[10] = {'a','e','i','o','u','A','E','I','O','U'};
	int v_seq = 0;
	int c_aux = 0;//Diz se c_seq >= 3
	int vog_aux = 0;//diz se e' uma vogal
	
	for(size_t i=0; i<strlen(senha[n]); i++){
		if(((senha[n][i] >= 97) & (senha[n][i] <= 122)) | ((senha[n][i] >= 65) & (senha[n][i] <= 90))){
		//confere se e' uma letra
			for(int k =0; k<10; k++){//confere se e' vogal
				if(senha[n][i] == vog[k]){
					v_seq++;
					vog_aux = 1;
					c_seq = 0;
					if(v_seq == 3){
						valido(2);
					}
				}
			}
			
			if(vog_aux == 0){
				c_seq++;

				if(c_seq == 3){
					c_aux = 1;
				}
			}
			else{
				vog_aux = 0;
			}
		}
	}
	
	if(c_aux == 1){
		valido(1);
	}
	else{
		valido(2);
	}
	
}

void letra(){
	//Confere se possui pelo menos uma letra maiuscula e minuscula
	//Min [97,122]
	//Mai [65,90]]
	int mai = 0;
	int min = 0;
	
	for(size_t i=0; i<strlen(senha[n]); i++){
		if((senha[n][i] >= 97) & (senha[n][i] <= 122)){
			min = 1;
		}
		else if((senha[n][i] >= 65) & (senha[n][i] <= 90)){
			mai = 1;
		}
	}	
	
	if((min == 1) & (mai == 1)){
		//printf("consec");
		consec();
	}
	else{
		valido(3);
	}
}

void digito(){
	//Confere se possui um digito
	char dig[10] = {'0','1','2','3','4','5','6','7','8','9'};
	int aux = 0;
	
	for(size_t i=0; i<strlen(senha[n]); i++){
		for(int v=0; v<10; v++){
			if(senha[n][i] == dig[v]){
			//	printf("letra");
				letra();
				v = 100;
				i = 100;
				aux =1;
			}
		}
	}
	
	if (aux == 0){
		valido(4);//caso nao possua digitos	
	}
}

void vogal(){
	//Confere se possui uma vogal
	char vog[10] = {'a','e','i','o','u','A','E','I','O','U'};
	int aux= 0;
	
	for(size_t i=0; i<strlen(senha[n]); i++){
		for(int v=0; v<10; v++){
			if(senha[n][i] == vog[v]){
				//printf("digito");
				digito();
				i = 100;
				v = 100;
				aux = 1;
			}
		}
	}
	if (aux == 0){
		valido(0);//caso nao possua vogais	
	}
}

void tamanho(){
	//Confere se possui mais de 8 caracteres
	if(strlen(senha[n]) >= 8){
		//printf("vogal");
		vogal();
	}
	else{
		valido(5);
	}

}

int main(){
	char aux[15];
	
	while(strcmp(aux,"fim") != 0){//Recebe a lista de strings
		scanf("%s", &aux[0]);
		if(strcmp(aux,"fim") != 0){
			strcpy(senha[n], aux);
			tamanho();
			n++;
		}
	}
	for(int t = 0; t<n; t++){
		if(val[t] != 1){
			printf("[%s] e' inaceitavel.\n", senha[t]);
		}
		else{
			printf("[%s] e' aceitavel.\n", senha[t]);
		}
	}
	
	return 0;
}
