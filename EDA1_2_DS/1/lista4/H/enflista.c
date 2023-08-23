#include <stdio.h>

typedef struct celula {
	int dado;
	struct celula *prox;
} celula;

celula *enfileira(celula *f, int x){
	celula *novo = malloc(sizeof(celula)); // Cria o novo
	novo -> prox = f -> prox; // Novo recebe o depois da cabeça
	f -> prox = novo; // o novo da cabeça vira o novo
	f -> dado = x; // Recebe o dado x
	f = novo;
	return novo;
}