#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
	int dado;
	struct celula *prox;
} celula;


int recMove (int *v, int i, int elem){
	if(i < 0 || v[i] <= elem) return i;
	v[i+1] = v[i];
	recMove(v, i-1, elem);
}

void ordena (int *v, int n){

	//Caso Base
	if(n <= 1) return;

	//Redução
	ordena (v, n-1);

	//Insere o elemento v[n-1] na posição correta no subvetor v[0...n-1]
	int elem = v[n-1];
	int i = recMove(v, n-2, elem);
	v[i+1] = elem;
}

void errad (celula *l1, celula *l2, celula *l3){

	int celula1[100];
	int i = 0;

	for(celula *p = l1 -> prox; p != NULL; p = p -> prox){
		celula1[i] = p -> dado;
		i++;
	}

	for(celula *q = l2 -> prox; q != NULL; q = q -> prox){
		celula1[i] = q -> dado;
		i++;
	}
	
	ordena(celula1, i);

	int j = i-1;

	while(j >= 0){
		// Alocar
		celula *novo = malloc(sizeof(celula));
		// Salvar o dado
		novo -> dado = celula1[j];
		// Plugar na lista
		novo -> prox = l3 -> prox;
		l3 -> prox = novo;
		j--;
	}
}

void mescla_listas(celula *l1, celula *l2, celula *l3){
	l1 = l1 -> prox;
	l2 = l2 -> prox;
	while(l1 != NULL && l2 != NULL){
		if (l1 -> dado < l2 -> dado){ // l3 recebe o menor valor
			l3 -> prox = l1;
			l1 = l1 -> prox;
		} else{
			l3 -> prox = l2;
			l2 = l2 -> prox;
		}
		l3 = l3 -> prox; // Avança l3
	}

	if(l1 != NULL){ // Depende de qual lista não vai acabar primeiro com o while
		l3 -> prox = l1;
	} else{
		l3 -> prox = l2;
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
	celula l1, l2, l3, no1,no2,no3,no4, no5,no6,no7;

	no1.dado = 1;
	no2.dado = 7; 
	no3.dado = 9;
	no4.dado = 10;

	no5.dado = 2;
	no6.dado = 3;
	no7.dado = 8;

	l1.prox = &no1;
	no1.prox = &no2;
	no2.prox = &no3;
	no3.prox = &no4;
	no4.prox = NULL;

	l2.prox = &no5;
	no5.prox = &no6;
	no6.prox = &no7;
	no7.prox = NULL;

	l3.prox = NULL;

	mescla_listas(&l1, &l2, &l3);

	imprime(&l3);

	return 0;
}
*/