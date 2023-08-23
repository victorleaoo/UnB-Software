#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula{
	char *dado;
	struct celula *prox;
} celula;

celula *cria_pilha(){
	celula *topo = malloc(sizeof(celula));
	topo -> prox = NULL;
	return topo;
}

int empilha(celula *topo, char *str){
	int i;
	celula *novo = malloc(sizeof(celula));
	if(novo == NULL) return 0;

	novo -> dado = str;

	novo -> prox = topo -> prox;
	topo -> prox = novo;
	return 1;
}

void desempilha(celula *topo){
	int i;

	celula *lixo = topo -> prox;

	if (lixo == NULL){
		printf("NULL\n");
	} else{
		topo -> prox = lixo -> prox;
		printf("%s\n", lixo -> dado);
		free(lixo);
	}
}

int main(){
	celula *p = cria_pilha();
	char *string = malloc(200*sizeof(char));
	char *entrada = malloc(200*sizeof(char));

	while(scanf("%s", string) != EOF){
		if(strcmp(string, "inserir") == 0){
			scanf(" %[^\n]", entrada);
			entrada[strlen(entrada)] = '\0';
			empilha(p, entrada);
		} else if (strcmp(string, "desfazer") == 0){
			desempilha(p);
		}
		entrada = malloc (100 * sizeof(char));
	}
	free(string);
	free(entrada);
	return 0;
}