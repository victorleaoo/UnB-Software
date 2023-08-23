#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item{
    char caracter;
    int count;
}Item;

Item th[128];

#define key(A) (A.count)
#define less(A,B) (key(A) == key(B) ? A.caracter < B.caracter : key(A) < key(B))

void merge(Item *vetor, int l, int m, int r){
    int l1 = l, r1 = m, l1i = l1;
    int l2 = m+1, r2 = r, l2i = l2;

    Item *c = malloc((r-l+1)*sizeof(Item));
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
        //printf("%c - %d\n", vetor[ci].caracter, vetor[ci].count);
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

void inicializa_vetor(){
    memset(th, 0, sizeof(Item)*128);
}

void resolve_caso(char c){
    inicializa_vetor();

    th[c].caracter = c; // atribui o valor do caracter
    th[c].count++;

    char b;
    while(scanf("%c", &b) == 1 && b != '\n'){
        th[b].caracter = b; // atribui o valor do caracter
        th[b].count++;
    } 
    
    mergesort(th, 0, 127); //até aqui, funcionando

    int i = 0;
    while(th[i].count == 0) {
        i++;
    }

    while(i < 128){
        printf("%hd %d\n", th[i].caracter, th[i].count);
        i++;
    }

    printf("\n");
    return;
}

int main(void){
    char c;

    while (scanf("%c", &c) != EOF){
        resolve_caso(c);
    }
    
    return 0;
}