#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int dado;
	struct no *esq, *dir;
} no;

typedef struct pilha{ // "A forma mais natural de se escrever um algoritmo recursivo de forma iterativa é usando pilhas" - John Lenon
	struct no *dado;
	struct pilha *prox;
} pilha;

void empilha(pilha **p, no *n){ // Coloca nó na pilha
	pilha *novo = malloc(sizeof(pilha));
	novo -> dado = n;
	novo -> prox = *p;
	*p = novo;
}

no *desempilha(pilha **p){ // desempilha o nó da pilha
	pilha *lixo = *p;
	no *y = lixo -> dado;
	*p = lixo -> prox;
	free(lixo);
	return y;
}

void em_ordem(no *raiz){ 
	no *no_temp = raiz;
	pilha *pilha_temp = NULL;
	int continua = 1;

	while(continua){ // Enquanto o no não é nulo e a pilha não está vazia
		if(no_temp){ // Esquerdo não é nulo
            empilha(&pilha_temp, no_temp);
			no_temp = no_temp -> esq; // Vai pra esquerda
		}
		else{
			if(pilha_temp != NULL){
				no_temp = desempilha(&pilha_temp);
				printf("%d ", no_temp -> dado); // Vai desempilhando e imprimindo
				no_temp = no_temp -> dir; // Vai para a direita
			}
			else{
				continua = 0; // Se a pilha estiver vazia, para o loop
			}
		}
	}
}