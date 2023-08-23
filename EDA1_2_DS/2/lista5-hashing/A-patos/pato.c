#include <stdio.h>
#include <stdlib.h>

void maior(int *v, int n){
    int maior = v[0], aux = 0;

    for(int i = 1; i < n; i++){
        if(v[i] > maior){
            maior = v[i];
            aux = i;
        }
    }

    printf("%d\n", aux);
    return;
}

void patos(int n){
    if(n == 0){
        return;
    }

    int cod, maiorCod = 0, j;
    int *v = calloc(n, sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &cod);
        v[cod]++;
    }

    maior(v, n);

    scanf("%d", &j);
    free(v);
    patos(j);
}

int main(void){
    int n; // Quantidade Patos

    scanf("%d", &n);
    patos(n);

    return 0;
}