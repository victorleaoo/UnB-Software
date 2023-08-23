#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
	int dado;
	struct celula *prox;
} celula;

void insere_inicio (celula *le, int x){
	// Alocar
	celula *novo = malloc(sizeof(celula));
	// Salvar o x
	novo -> dado = x;
	// Plugar na lista
	novo -> prox = le -> prox;
	le -> prox = novo;
}

void insere_antes (celula *le, int x, int y){
	// Alocar
	celula *novo = malloc(sizeof(celula));
	// Salvar o x
	novo -> dado = x;

	// Cabeça da lista
	celula *q = le -> prox;

	// Busca por y e vai fazendo passando "q" para prox
	while(q != NULL && q -> dado != y){ // Mesma coisa que: for(p = le; p -> prox != NULL || p -> prox -> dado != y; p = p -> prox) 
		le = q;
		q = q -> prox;
	}

	// Pluga na lista
	novo -> prox = q;
	le -> prox = novo;
}