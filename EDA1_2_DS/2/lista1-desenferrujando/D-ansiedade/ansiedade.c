#include <stdio.h>

int main() {
    int n, sim = 0, triagem = 0, p = 0, ja = 0;

    char pergunta[3];

	while(scanf("%d", &n) != EOF){
        if(p == 10){
            p = 0;
            sim = 0;
            ja = 0;
        }
        
        scanf(" %s", pergunta);
        
        if (pergunta[0] == 's'){
            sim += 1;
        }
        if (sim > 1 && ja != 1){
            triagem++;
            ja = 1;
        }
        p++;
	}

	printf("%d\n", triagem);

	return 0;
}