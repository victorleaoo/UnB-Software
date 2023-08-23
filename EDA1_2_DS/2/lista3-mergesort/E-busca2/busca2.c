#include <stdio.h>
#include <stdlib.h>

#define less(A,B) (A < B)

void merge(int *v, int *p, int e, int m, int d) {
    int *aux = malloc((d - e + 1) * sizeof(int)), *auxP = malloc((d - e + 1) * sizeof(int));
    int i = e, j = m + 1, k = 0;

    while(i <= m && j <= d) {
        if(less(v[i], v[j])) {
            auxP[k] = p[i];
            aux[k++] = v[i++];
        }
        else {
            auxP[k] = p[j];
            aux[k++] = v[j++];
        }
    }

    while(i <= m) {
        auxP[k] = p[i];
        aux[k++] = v[i++];
    }

    while(j <= d) {
        auxP[k] = p[j];
        aux[k++] = v[j++];
    }

    k = 0;

    for(i = e; i <= d; i ++) {
        p[i] = auxP[k];
        v[i] = aux[k++];
    }

    free(aux);
    free(auxP);
}

void mergesort(int *vetor, int *pos, int l, int r){
    if (l >= r) return;
    int meio = (r - l)/2 + l;
    mergesort(vetor, pos, l, meio);
    mergesort(vetor, pos, meio+1, r);
    merge(vetor, pos, l, meio, r); // junta os dois vetores
}

void buscaBinaria (int *vetor, int *pos, int r, int valor) {
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
        printf("%d\n", pos[d]);
    } else{
        printf("%d\n", -1);
    }
}

int main(void){
    int n, m, i, valor;

    scanf("%d %d", &n, &m);

    int *vN = malloc(n * sizeof(int));
    int *pos = malloc(n * sizeof(int));

    for(i = 0; i < n; i++){
        scanf("%d", &vN[i]);
        pos[i] = i;
    }

    mergesort(vN, pos, 0, n-1);

    for(i = 0; i < m; i++){
        scanf("%d", &valor);
        buscaBinaria(vN, pos, n, valor);
    }

    free(vN);
    free(pos);

    return 0;
}