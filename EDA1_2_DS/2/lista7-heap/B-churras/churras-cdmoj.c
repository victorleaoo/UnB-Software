#include <stdio.h>
#include <stdlib.h>

#define key(x) (x->value)
#define less(a, b) (key(a) > key(b))
#define swap(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }

struct Item{
    int heap_idx;
    int value;
};
typedef struct Item *Item;

Item NULL_ITEM = NULL;

typedef struct{
    Item *heap;
    int size;
    int tamMax;
} PriorityQueue;

void fixUp(Item *v, int k){
    while(k > 1 && less(v[k/2], v[k])){
        exch(v[k], v[k/2]);
        v[k]->chave = k;
        v[k/2]->chave = k/2;
        k=k/2;
    }

    return;
}

void fixDown(Item *v, int k, int n){
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

PriorityQueue PQinit(int tamMax){
    PriorityQueue pq;
    pq.tamMax=tamMax;
    pq.size=0;
    pq.heap = malloc((tamMax + 1) * sizeof(Item));
    return pq;
}

int PQvazia(PriorityQueue pq){
    return pq.size == 0;
}

void PQrealloc(PriorityQueue *pq, int newtamMax){
    if (newtamMax <= pq->tamMax)
        return;

    pq->tamMax *= 4;
    pq->heap = realloc(pq->heap, (pq->tamMax + 1) * sizeof(Item));
}

void PQ_insert(PriorityQueue *pq, Item x){
    PQrealloc(pq, pq->size + 1);
    pq->heap[++pq->size] = x;
    x->heap_idx = pq->size;
    fixUp(pq->heap, pq->size);
}

Item PQFindTop(PriorityQueue *pq){
    if (PQvazia(*pq))
        return NULL_ITEM;

    Item top = pq->heap[1];

    pq->heap[1] = pq->heap[pq->size--];
    fixDown(pq->heap, pq->size, 1);

    return top;
}

Item PQDel(PriorityQueue *pq, int i){
    if (i < 1 || i > pq->size)
        return NULL_ITEM;

    Item del = pq->heap[i];

    pq->heap[i] = pq->heap[pq->size--];
    fixDown(pq->heap, pq->size, i);

    return del;
}

void solve()
{
    int n, k;
    scanf(" %d %d\n", &n, &k);
    if (n == 0 && k == 0)
        return;

    Item v = malloc(n * sizeof(struct Item));
    for (int i = 0; i < n; i++)
        scanf(" %d", &v[i].value);

    PriorityQueue pq = PQinit(k);
    for (int i = 0; i < k - 1; i++)
        PQ_insert(&pq, &v[i]);

    for (int i = k - 1; i < n; i++)
    {
        PQ_insert(&pq, &v[i]);
        printf("%d%c", pq.heap[1]->value, " \n"[i == n-1]);
        PQDel(&pq, v[i - k + 1].heap_idx);
    }

    free(pq.heap);
    solve();
}

int main()
{
    solve();

    return 0;
}