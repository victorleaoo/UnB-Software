#include <stdio.h>
#include <stdlib.h>

#define less(A, B) (A > B)
#define exch(A, B) {int t = B; B = A; A = t;}

static int *pq;
static int n;

void PQinit(int maxN){
    pq = malloc(maxN*sizeof(int));
    n = 0;
    return;
}

void fixUp(int *v, int k){
    while(k > 1 && less(v[k/2], v[k])){
        exch(v[k], v[k/2]);
        k=k/2;
    }

    return;
}

void fixDown(int *v, int k, int n){
    int j;

    while(2*k < n){
        j = 2*k;
        if(j < n && less(v[j], v[j+1])) j++;
        if(!less(v[k], v[j])) break;
        exch(v[k], v[j]);
        k = j;
    }

    return;
}

int PQdelMin(int *pq){
    int menor = pq[1];
    exch(pq[1], pq[n]);
    fixDown(pq, 1, --n);
    return menor;
}

void PQinsert(int *pq, int novo){
    pq[++n] = novo;
    fixUp(pq, n);
    return;
}

int main(void){
    int op, insere, qntd, v[100005];

    PQinit(100005);

    while(scanf("%d", &op) != EOF){
        if(op == 1){
            scanf("%d", &insere);
            PQinsert(pq, insere);
        } else{
            scanf("%d", &qntd);
            for (int i = 0; i < qntd; i++){
                int menor = PQdelMin(pq);
                v[i] = menor;
            }
            for(int i = 0; i < qntd; i++){
                printf("%d ", v[i]);
                PQinsert(pq, v[i]);
            }
            printf("\n");
        }
    }

    return 0;
}