#include <stdio.h>
#include <string.h>
#define max 10001

int main(){
	char code[max];//Mensagem codificada
	char decoded[max];//Mensagem decodificada
	int freq[26] = {0};//Vetor de recorrencia
	int aux;//Recebe o indice a ser incrementado em freq[]
	int maxl_aux = -1;//Maior freq
	char maxl;//Letra com maior recorrencia/antiga
	int caso;//Caso de codificacao
	
	scanf("%[^\n]s", &code[0]);
	
	for(size_t i=0; i<strlen(code); i++){//Detecta a recorrencia
		aux = code[i];
		if(aux != 32){//Espaco = 32 ASCII
			aux -= 97;//Letra minuscula [97,122]
			freq[aux]++;
		}
	}
	
	for(int k=0; k<26; k++){//letra com maior freq
		if(freq[k] > maxl_aux){
			maxl_aux = freq[k];
			maxl = k+97;
		}
	}	
	
	//Seleciona o caso
	if(maxl == 97){
		caso = 1;
	}
	else if(maxl == 122){
		caso = 2;
	}
	else{
		caso = 3;
	}
	
	switch (caso) {
		case 1://Caso A
			for(size_t i = 0; i<strlen(code); i++){
				if(code[i] == 97){//a
					decoded[i] = 97;
				}
				else if(code[i] == 98){//z
					decoded[i] = 122;
				}
				else if(code[i] == 32){
					decoded[i] = code[i];
				}
				else{
					decoded[i] = code[i] - 1 ;
				}
			}
			break;
			
		case 2://Caso Z
			for(size_t i = 0; i<strlen(code); i++){
				if(code[i] == 97){//y
					decoded[i] = 121;
				}
				else if(code[i] == 122){//z
					decoded[i] = 122;
				}
				else if(code[i] == 32){
					decoded[i] = code[i];
				}
				else{
					decoded[i] = code[i] - 1;
				}
			}
			break;
			
		case 3://Restante
			for(size_t i = 0; i<strlen(code); i++){
				if(code[i] == maxl){
					decoded[i] = code[i];
				}
				else if(code[i] == 32){
					decoded[i] = code[i];
				}
				else{
					if((code[i] - (maxl - 97)) >= 97){
						if((maxl+(maxl-97) >= code[i]) && (code[i] >= maxl)){
							decoded[i] = code[i] - ( maxl - 97) - 1;
						}
						else{
							decoded[i] = code[i] - ( maxl - 97);
						}
					}
					else{
						decoded[i] = code[i] - (maxl - 97) + 26;
					}
				}
			}
			break;
	}

	printf("%s\n", decoded);
	
	return 0;
}
