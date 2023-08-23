#include <stdio.h>

int main(){
	int questoes, soma, i;
	char gabarito[100], resposta[100];
	scanf("%d %s %s", &questoes, gabarito, resposta);

	soma = 0;

	for(i=0;i<questoes;i++){
		if(gabarito[i]==resposta[i]){
			soma += 1;
		}
	} 

	printf("%d", soma);
}