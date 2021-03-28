#include <stdio.h>
#include <stdbool.h>

int dados[1000][1000];//matriz de dados
int n,m,r,s,soma,k,t,soma_coluna,rem_coluna,soma_aux;

void primeiro(){
	//Calcula a soma da submatriz com k=0
	//k(coluna) e t(linha)
	soma_aux = 0;
	
	int t0 = t;//valor inicial de t
	int t_aux = t;//indice da linha
	
	for(; t_aux<(r+t0); t_aux++){//de t ate t+r vezes 
		for(int x = 0; x<s; x++){//k(coluna), t(linha)
			soma_aux += dados[t_aux][x];
		}
	}
	
	if(soma_aux > soma){
		soma = soma_aux;
	}
	//printf("Primeira soma: %d\n", soma);
}

void somaf(){
	//realiza a soma das duas funcoes
	int aux = soma_coluna + rem_coluna + soma_aux;
	if(aux > soma){
		soma = aux;
	}
	soma_aux = aux;
	soma_coluna = rem_coluna = 0;
	//printf("Parcial soma: %d\n", soma);
}


void remove_coluna(){
	//Remove a coluna k-1
	int t_aux = t;
	int t0 = t;
	
	for(; t_aux<(r+t0); t_aux++){
		rem_coluna += dados[t_aux][k-1];
	}
	rem_coluna = -rem_coluna;

}


void add_coluna(){
	//Realiza a soma de k+s
	int t_aux = t;
	int t0 = t;
	
	k++;
	for(; t_aux<(r+t0); t_aux++){
		soma_coluna += dados[t_aux][k+s-1];
	}

	//printf("Soma coluna: %d\n", soma_coluna);
}

int main(){
	//Submatriz: r(linha) x s(coluna)
	//Matriz: n(linha) x m(coluna)	
	int caso = 1;
	bool fim = false;

	scanf("%d %d %d %d", &n, &m, &r, &s);//Parametros
	
	//recebe os valores da matriz
	//i = linha, j = coluna
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d", &dados[i][j]);
		}
	}
	
	//Maquina de estados
	while(fim == false){
		switch(caso){
			case 1://Comeco de linha
				primeiro();
				k =0;
				if((k+s) < m){
					caso = 2;
					break;
				}
				else if((t+r)<n){
					t++;
					caso=1;
					break;
					
				}
				else{
					fim = true;
					break;
				}
				
			case 2://Soma coluna
				add_coluna();
				caso = 3;
				break;
			
			case 3://Remove coluna
				remove_coluna();
				caso = 4;
				break;
				
			case 4://Atualiza soma
				somaf();
				if(k+s<m){
					caso = 2;
					break;
				}
				else if((t+r)>= n){
					fim = true;
					break;
				}
				else{
					t++;
					caso = 1;
					break;
				}
		}

	}

	printf("%d\n", soma);
	
	return 0;
}
