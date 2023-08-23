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

void print_maj(int *v, int n){
    int maj = 0, aux = 0;

    for(int i = 0; i < n; i++){
        if(aux == 0){
            maj = v[i];
            aux++;
        } else if(maj == v[i]){
            aux++;
        } else{
            aux--;
        }
    }

    printf("%d\n", maj);
}

void patos_solucao(int n){
    if(n == 0){
        return;
    }

    int *patos = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &patos[i]);
    }

    mergesort(patos, 0, n-1);
    
    //for(int i = 0; i < n; i++){
    //    printf("%d\n", patos[i]);
    //}

    print_maj(patos, n);

    free(patos);

    int novo;

    scanf("%d", &novo);
    patos_solucao(novo);
}

int main(void){
    int n; // Quantidade Patos

    scanf("%d", &n);
    patos_solucao(n);

    return 0;
}