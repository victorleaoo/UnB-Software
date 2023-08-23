#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define auxey(A) (A.soma)
#define lessq(A,B) (auxey(A) <= auxey(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(lessq(B,A)) exch(A,B);}

typedef struct Item{
    int pos;
    char letra;
    int soma;
} Item;

void merge(Item *vetor, int l, int m, int r){
    int l1 = l, r1 = m, l1i = l1;
    int l2 = m+1, r2 = r, l2i = l2;

    Item *c = malloc((r-l+1)*sizeof(Item));
    int ci = 0;

    int rc = r-l;

    while (l1i <= r1 && l2i <= r2){
        if(lessq(vetor[l2i], vetor[l1i])){
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

void mergesort(Item *vetor, int l, int r){
    if (l >= r) return;
    int meio = (r - l)/2 + l;
    mergesort(vetor, l, meio);
    mergesort(vetor, meio+1, r);
    merge(vetor, l, meio, r); // junta os dois vetores
}

int main(void){
    char v[100000];
    Item letras[100000];
    int j = 0;

    scanf(" %s", v);

    for(int i = 0; i < entradalen(v); i++){
        if (i == 0){
            letras[j].letra = v[i];
            letras[j].pos = 0;
            letras[j].soma = 1;
            continue;
        }

        if(v[i] == v[i-1]){
            letras[j].soma++;
        } else{
            letras[++j].letra = v[i];
            letras[j].pos = i;
            letras[j].soma = 1;
        }
    }

    mergesort(letras, 0, j);

    for (int i = 0; i < j+1; i++){
        printf("%d %c %d\n", letras[i].soma, letras[i].letra, letras[i].pos);
    }
    
    return 0;
} 