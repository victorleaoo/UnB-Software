#include <stdio.h>
#include <stdlib.h>

void busca(int tamanhoN, int tamanhoM, int *N, int *M, int *j){

    int m, e, d, i;

    for(i = 0; i < tamanhoM; i++){
        e = -1;
        d = tamanhoN;
        while(e != (d-1)){ // só encontrou o j quando e == d-1
            m = (e+d)/2;
            if(M[i] > N[m]){
                e = m; // Se tiver à esquerda de m, o esquerdo vira m 
            } else{
                d = m; // Se tiver à direita de m, o direita vira m
            } 
        }
        j[i] = d;
    }
}

int main(void){
    int n, m;

    scanf("%d %d", &n, &m);

    int *vN = malloc(n*sizeof(int));
    int *vM = malloc(m*sizeof(int));
    int *j = malloc(m*sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &vN[i]);
    }

    for(int i = 0; i < m; i++){
        scanf("%d", &vM[i]);
    }

    busca(n, m, vN, vM, j);

    for(int i = 0; i < m; i++){
        printf("%d \n", j[i]);
    }

    return 0;
}