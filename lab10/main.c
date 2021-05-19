#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "li.h"

//#define debug 1

int main(){
	
	int n;//Define the initial list [1,...,N]
	int r;//Num of accesses
	int mtf, transp, count = 0;//Method cost
	
	scanf("%d ", &n);
	scanf("%d ", &r);
	
	//int num[r];//Num to be searched
	int* num = malloc(r*sizeof(int));
	
	tuple* L = li_alloc(n);
	li* L1 = L->t1;
	li* L2 = L->t2;
	li* L3 = L->t3;
	
	free(L);
	
	if (!L1 || !L2 || !L3) exit(errno);
	
	
	for (int k=0; k<r; k++){
		scanf("%d", &num[k]);
	}
	
	
	mtf = li_mtf(L1,num,r);
	if (!mtf) exit(errno);
	li_free(L1);
	
	transp = li_transp(L2, num, r);
	if (!transp) exit(errno);
	li_free(L2);
	
	count = li_count(L3, num, r, n);
	if (!count) exit(errno);
	li_free(L3);
	
	printf("MTF: %d\n", mtf);
	printf("Transpose: %d\n", transp);
	printf("Count: %d\n", count);
	
	free(num);
	
	return 0;
}


