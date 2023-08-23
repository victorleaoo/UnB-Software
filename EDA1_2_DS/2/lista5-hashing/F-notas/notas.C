#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct notas{
    int nota;
    int count;
} notas;

#define key(A) (A.count)
#define less(A,B) (key(A) > key(B))

void merge(notas *vetor, int l, int m, int r){
    int l1 = l, r1 = m, l1i = l1;
    int l2 = m+1, r2 = r, l2i = l2;

    notas *c = malloc((r-l+1)*sizeof(notas));
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

void mergesort(notas *vetor, int l, int r){
    if (l >= r) return;
    int meio = (r - l)/2 + l;
    mergesort(vetor, l, meio);
    mergesort(vetor, meio+1, r);
    merge(vetor, l, meio, r); // junta os dois vetores
}

notas v[101];

void inicializa_vetor(){
    memset(v, 0, sizeof(notas)*101);
}

int main(void){
    int n, nota;

    scanf("%d", &n); // n de alunos

    inicializa_vetor();

    for(int i = 0; i < n; i++){
        scanf("%d", &nota);
        v[nota].nota = nota;
        v[nota].count++;
    }

    mergesort(v, 0, 101);

    printf("%d\n", v[0]);

    return 0;
}