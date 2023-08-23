#include <stdio.h>
#include <stdlib.h>

#define Key(A) (A->valor)
#define less(A, B) (Key(A) > Key(B))
#define exch(A, B) {HT t = B; B = A; A = t;}

struct HT{
    int chave;
    int valor;
};

typedef struct HT *HT;

typedef struct Heap{
    HT *pq;
    int n;
    int tamPossivel;
} Heap;

Heap PQinit(int tamPossivel){
    Heap pq;

    pq.n = 0;
    pq.tamPossivel = tamPossivel;
    pq.pq = malloc((tamPossivel + 1) * sizeof(HT));
    
    return pq;
}

void fixUp(HT *v, int k){
    while(k > 1 && less(v[k/2], v[k])){
        exch(v[k], v[k/2]);
        v[k]->chave = k;
        v[k/2]->chave = k/2;
        k=k/2;
    }

    return;
}

void fixDown(HT *v, int k, int n){
    int j;

    while(2*k < n){
        j = 2*k;
        if(j < n && less(v[j], v[j+1])) j++;
        if(!less(v[k], v[j])) break;
        exch(v[k], v[j]);
        v[k]->chave = k;
        v[j]->chave = j;
        k = j;
    }

    return;
}

void PQrealoc(Heap *pq, int novoTam){
    if (novoTam <= pq->tamPossivel)
        return;

    pq->tamPossivel = pq->tamPossivel*4;
    pq->pq = realloc(pq->pq, (pq->tamPossivel + 1) * sizeof(HT));

    return;
}

HT PQReturnMin(Heap *pq){
    HT menor = pq->pq[1];
    pq->pq[1] = pq->pq[pq->n];
    fixDown(pq->pq, --pq->n, 1);

    return menor;
}

HT PQRemoveHT(Heap *pq, int k){
    HT removido = pq->pq[k];
    pq->pq[k] = pq->pq[pq->n];
    fixDown(pq->pq, --pq->n, k);

    return removido;
}

void PQ_ensureCapacity(Heap *pq, int newCapacity)
{
    if (newCapacity <= pq->tamPossivel)
        return;

    pq->tamPossivel *= 4;
    pq->pq = realloc(pq->pq, (pq->tamPossivel + 1) * sizeof(HT));
    return;
}

void PQinsert(Heap *pq, HT novo){
    PQ_ensureCapacity(pq, pq->n + 1);
    pq->pq[++pq->n] = novo;
    novo->chave = pq->n;
    fixUp(pq->pq, pq->n);
    return;
}

int main(void){
    int n, k;
    while (1){
        scanf(" %d %d\n", &n, &k);
        if(n == 0 && k == 0){
            return 0;
        }

        HT v = malloc(n * sizeof(struct HT));
        Heap pq = PQinit(k);

        for(int i = 0; i < n; i++){
            scanf(" %d", &v[i].valor);
        }

        for(int i = 0; i < k-1; i++){
            PQinsert(&pq, &v[i]);
        }

        for(int i = k-1; i < n; i++){
            PQinsert(&pq, &v[i]);
            printf("%d ", pq.pq[1]->valor);
            PQRemoveHT(&pq, v[i-k+1].chave);
        }
        printf("\n");

        free(pq.pq);
    }
}