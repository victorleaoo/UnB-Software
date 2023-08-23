#include <stdio.h>
#include <stdlib.h>

void verificaLimite(int *vetor, int aux, int limite) {
    int i, soma = 0;
    for (i = aux; i < 10000; i ++) {
        if (vetor[i] == 0) break;
        soma += vetor[i];
        if(soma > limite) {
            aux = i + 1;
            verificaLimite(vetor, aux, limite);
            printf("%d\n", vetor[i]);
            break;
        }
    }
}

int main()
{
    int limite, *v, aux = 0, soma = 0;
    v = malloc(10000 * sizeof(int));

    for (int i=0; ; i++){
        scanf("%d", &v[i]);

        if(v[i] == 0){
            scanf("%d", &limite);
            break;
        }
    }
    
    verificaLimite(v, aux, limite);

    return 0;
}