#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int dado;
	struct lista *prox;
}lista;

typedef struct pilha{
	lista *base;
	lista *topo;
}pilha;

pilha *cria_pilha(){
	pilha *p = (pilha*)malloc(sizeof(pilha));
	p -> base = NULL;
	p -> topo = NULL;
	return p;
}

void *empilha(pilha *p, int carta){
	lista *novo = (lista*)malloc(sizeof(lista));
	novo -> dado = carta;
	novo -> prox = NULL;
	if(p -> base == NULL){
		p -> base = novo;
  		p -> topo = novo;
 	} else{
  		p->fim->prox = novo;
  		p->fim = novo;
 	}
}

int desenfileira(pilha *p){
	int carta;
	lista *l;

	l = p -> base;
 	carta = l -> dado;

	p -> base = l -> prox;
	if(p -> base == NULL) p -> topo = NULL;

	free(l);

	return carta;
}

int vazio(pilha *p){
	return p -> base == NULL;
}

int main(){

	int n, i, carta, cont = 0;
	pilha *pilha;

	pilha = cria_pilha();

 	scanf("%d", &n);

  	if(n){
   		cont = n;
   		for(i=1;i<=n;i++){
    		empilha(pilha, i);
    	}

		printf("Discarded cards:");

		while(cont != 1){
    		printf(" %d", desenfileira(pilha));
    		empurra(pilha, desenfileira(pilha));
    		if(cont!=2) printf(",");
    		cont--;
    	}
    	if(!vazio(pilha)) printf("\nRemaining card: %d\n", desenfileira(pilha));
   	}

 return 0;
}