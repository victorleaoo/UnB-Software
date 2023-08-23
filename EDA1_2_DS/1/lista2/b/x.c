#include <stdio.h>

void mudaX(char *string, int i){
	if(string[i] != '\0'){
		if(string[i] != 'x'){
			printf("%c", string[i]);
			mudaX(string, i+1); //imprime os não X na ida -> laço q pula de um em um
		}
		else{
			mudaX(string, i+1);
			printf("%c", string[i]); //imprime os X nas voltas
		}
	}
}

int main(){
	char string[101];

	scanf("%s", string);
	mudaX(string, 0);

	return 0;
}