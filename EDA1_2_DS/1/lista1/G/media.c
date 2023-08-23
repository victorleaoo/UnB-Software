#include <stdio.h>

int main() {
	int tamanho, i, soma = 0, entrou, vetor[10001];
	float media;

	scanf("%d", &tamanho);

	for(i=0; i<tamanho;i++){
		scanf("%d", &vetor[i]);
		soma += vetor[i];
	}

	media = soma/tamanho;

	entrou = 0;
	for(i=0; i<tamanho; i++){
		if(vetor[i]>media){
			printf("%d ", vetor[i]);
			entrou++;
		}
	}

	if(entrou==0){
		printf("0");
	}

	return 0;
}