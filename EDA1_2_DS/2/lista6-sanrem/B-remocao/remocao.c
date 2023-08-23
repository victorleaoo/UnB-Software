#include <stdio.h>
#include <stdlib.h>

#define key(x) (x.atual)
#define ull unsigned long long
#define imprimeItem(x) printf("%llx %llx %llx\n", x.atual, x.ant, x.prox)

typedef struct{
    ull ant;
    ull atual;
    ull prox;
} Item;

Item v[250001];

int buscaBinaria(Item *v, int n, ull x){
    int l = 0, r = n - 1;

    while (l <= r){
        int m = (l + r) / 2;
        if (key(v[m]) == x){
           return m; // retorna indice que encontrou
        } else if (key(v[m]) < x){
            l = m + 1;
        } else{
            r = m - 1;
        }   
    }

    return -1;
}

void merge(Item *a, int tamA, Item *b, int tamB){
    int l1i = 0;
    int l2i = 0;

    Item *c = malloc((tamA+tamB)*sizeof(Item));
    int ci = 0, rc = tamA+tamB;

    while (l1i < tamA && l2i < tamB){
        if(key(a[l1i]) <= key(b[l2i])){
            c[ci++] = a[l1i++];
        } else{
            c[ci++] = b[l2i++];
        }
    }
    
    while (l1i < tamA){
        c[ci++] = a[l1i++];
    }
    while (l2i < tamB){
        c[ci++] = b[l2i++];
    }
    
    l1i = 0;
    for(ci=0; ci < rc; ci++){
        a[l1i++] = c[ci];
    }

    free(c);
}

void mergesort(Item *vetor, int r){
    if (r < 2) return;

    int meio = r/2;

    mergesort(vetor, meio);
    mergesort(&vetor[meio], r - meio);
    merge(vetor, meio, vetor+meio, r - meio); // junta os dois vetores
}

void imprimeAnt(Item *v, int n, ull x){
    int aux = buscaBinaria(v, n, x); // indice do item ou -1

    if (aux == -1 || v[aux].atual == 0) return; // não encontrou ou o atual é igual a 0, deu "erro"

    imprimeAnt(v, n, v[aux].ant);

    imprimeItem(v[aux]);
}

void imprimeProx(Item *v, int n, ull x){
    int aux = buscaBinaria(v, n, x); // indice do item ou -1

    if (aux == -1 || v[aux].atual == 0) return; // não encontrou ou o atual é igual a 0, deu "erro"

    imprimeItem(v[aux]);

    imprimeProx(v, n, v[aux].prox);
}

void imprimeUltimo(Item *v, int n, ull x, ull ultimo){
    int aux = buscaBinaria(v, n, x);

    if (aux == -1 || v[aux].atual == ultimo) return; // não encontrou ou o atual é o último
    
    printf("%llx\n", v[aux].atual);

    imprimeUltimo(v, n, v[aux].prox, ultimo);
}

int main(){
    int n = 0;

    while(scanf("%llx %llx %llx", &v[n].atual, &v[n].ant, &v[n].prox) == 3){
        n++;
    }

    Item ptr1 = v[0], ptr2 = v[1];

    mergesort(v, n);

    int prt1_ant = buscaBinaria(v, n, ptr1.ant);
    int ptr2_prox = buscaBinaria(v, n, ptr2.prox);

    v[prt1_ant].prox = ptr2.prox;
    v[ptr2_prox].ant = ptr1.ant;

    imprimeAnt(v, n, ptr1.ant);
    imprimeProx(v, n, ptr2.prox);
    printf("\n");
    imprimeUltimo(v, n, ptr1.atual, ptr2.prox);

    return 0;
}