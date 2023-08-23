#include <stdio.h>
#include <stdlib.h>

#define less(A,B) (A < B)

void merge(int *vetor, int l, int m, int r){
    int l1 = l, r1 = m, l1i = l1;
    int l2 = m+1, r2 = r, l2i = l2;

    int *c = malloc((r-l+1)*sizeof(int));
    int ci = 0;

    int rc = r-l;

    while (l1i <= r1 && l2i <= r2){
        if(less(vetor[l1i], vetor[l2i])){
            c[ci++] = vetor[l1i++];
        } else{
            c[ci++] = vetor[l2i++];
        }
    }
    
    while (l1i <= r1){
        c[ci++] = vetor[l1i++];
    }
    while (l2i <= r2){
        c[ci++] = vetor[l2i++];
    }
    
    l1i = l;
    for(ci=0; ci <= rc; ci++){
        vetor[l1i++] = c[ci];
    }

    free(c);
}

void mergesort(int *vetor, int l, int r){
    if (l >= r) return;
    int meio = (r - l)/2 + l;
    mergesort(vetor, l, meio);
    mergesort(vetor, meio+1, r);
    merge(vetor, l, meio, r); // junta os dois vetores
}


void buscaBinaria(int *vetor, int r, int valor) {
    int e = -1, d = r, m;

    while (e < d - 1) {
        m = (e + d)/2;

        if (vetor[m] < valor){
            e = m;
        } else{
            d = m;
        } 
    }

    if(vetor[d] == valor){
        printf("sim\n");
    } else{
        printf("nao\n");
    }
}

int main(void){
    int qntd, valor;

    scanf("%d", &qntd);

    int *proibidos = malloc(qntd*sizeof(int));

    for(int i = 0; i < qntd; i++){
        scanf("%d", &proibidos[i]);
    }

    mergesort(proibidos, 0, qntd-1);

    while (scanf("%d", &valor) != EOF){
        buscaBinaria(proibidos, qntd-1, valor);
    }
}