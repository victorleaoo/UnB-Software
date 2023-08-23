#include <stdio.h>

int main(){
	int tmp, menor, i, j, n, c = 0;
	int vetor[1000];

	while(scanf("%d", &n) != EOF){
		vetor[c] = n;
		c++;
	}

	for(i = 0; i < c; i++){
		menor = i;
		for(j = i + 1; j < c; j++){
			if(vetor[j] < vetor[menor]){
				menor = j;
			}
		}
		if(menor != i){
			tmp = vetor[i];
			vetor[i] = vetor[menor];
			vetor[menor] = tmp;
		}
	}

	for(i = 0; i < c; i++){
		printf("%d ", vetor[i]);
	}

	return 0;
}