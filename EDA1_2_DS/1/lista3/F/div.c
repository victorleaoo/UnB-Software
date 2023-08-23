#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
	int dado;
	struct celula *prox;
} celula;

void divide_lista (celula *l, celula *l1, celula *l2){

	int par[100], impar[100], indexPar = 0, indexImpar = 0;

	for(celula *p = l -> prox; p != NULL; p = p -> prox){
		if(p -> dado % 2 == 0){
			par[indexPar] = p -> dado;
			indexPar++;
		} else{
			impar[indexImpar] = p -> dado;
			indexImpar++;
		}
	}

	// l2 com pares
	for(int i = indexPar - 1; i >= 0; i--){
		celula *novo = malloc(sizeof(celula));
		novo -> dado = par[i];
		novo -> prox = l2 -> prox;
		l2 -> prox = novo;
	}

	// l1 com impares
	for(int i = indexImpar - 1; i >= 0; i--){
		celula *novo = malloc(sizeof(celula));
		novo -> dado = impar[i];
		novo -> prox = l1 -> prox;
		l1 -> prox = novo;
	}

}

/*
void imprime (celula *le){
	for(celula *p = le -> prox; p != NULL; p = p -> prox){ // Correr toda a lista encadeada
		printf("%d -> ", p -> dado);
	}
	printf("NULL\n");
}

int main(){
	celula l1, l2, l3, no1,no2,no3,no4,no5,no6;

	no1.dado = 10;
	no2.dado = 4; 
	no3.dado = -9;
	no4.dado = 2;
	no5.dado = 7;
	no6.dado = 10;

	l1.prox = &no1;
	no1.prox = &no2;
	no2.prox = &no3;
	no3.prox = &no4;
	no4.prox = &no5;
	no5.prox = &no6;
	no6.prox = NULL;

	l2.prox = NULL;

	l3.prox = NULL;

	divide_lista(&l1, &l2, &l3);

	imprime(&l1);
	imprime(&l2);
	imprime(&l3);

	return 0;
}
*/