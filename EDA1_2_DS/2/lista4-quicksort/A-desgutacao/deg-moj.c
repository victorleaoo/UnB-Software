#include <stdio.h>
#include <stdlib.h>

#define key(A) (A)
#define lessq(A,B) (key(A) <= key(B))
#define exch(A,B) {int t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Item {
    int tamanho;
    char letra[1];
    int pos;
} Item;

void merge(Item letras[100000], int e, int m, int d) {
    Item *c = malloc((d - e + 1) * sizeof(Item));
    int i = e, j = m + 1, k = 0;

    while(i <= m && j <= d) {
        if(lessq(letras[i].tamanho, letras[j].tamanho)) {
            c[k].letra[0] = letras[i].letra[0];
            c[k].pos = letras[i].pos;
            c[k++].tamanho = letras[i++].tamanho;
        } else {
            c[k].letra[0] = letras[j].letra[0];
            c[k].pos = letras[j].pos;
            c[k++].tamanho = letras[j++].tamanho;
        }
    }

    while(i <= m) {
        c[k].letra[0] = letras[i].letra[0];
        c[k].pos = letras[i].pos;
        c[k++].tamanho = letras[i++].tamanho;
    }

    while(j <= d) {
        c[k].letra[0] = letras[j].letra[0];
        c[k].pos = letras[j].pos;
        c[k++].tamanho = letras[j++].tamanho;
    }

    k = 0;

    for(i = e; i <= d; i ++) {
        letras[i].letra[0] = c[k].letra[0];
        letras[i].pos = c[k].pos;
        letras[i].tamanho = c[k++].tamanho;
    }

    free(c);
}


void mergeSort(Item letras[100000], int e, int d) {
    if(e >= d) return;

    mergeSort(letras, e, (e+d)/2);
    mergeSort(letras, ((e+d)/2) + 1, d);
    merge(letras, e, (e+d)/2, d);
}

void separaLetra(char str[100000], Item letras[100000]) {
    int i, k = 0, ini, fim, n, cP, cT, j;
    char cL[1];

    letras[0].letra[0] = str[0];
    letras[0].tamanho = 1;
    letras[0].pos = 0;

    for(i = 1; str[i] != '\0'; i ++) {
        if(str[i] != letras[k].letra[0]) {
            k ++;
            letras[k].letra[0] = str[i];
            letras[k].pos = i;
            letras[k].tamanho = 1;
        } else {
            letras[k].tamanho ++;
        }
    }

    mergeSort(letras, 0, k);

    fim = k;
    for(i = k; i >= 0; i --) {
        if(letras[i].tamanho != letras[i-1].tamanho) {
            for(j = i; j <= fim; j ++)
                printf("%d %c %d\n", letras[j].tamanho, letras[j].letra[0], letras[j].pos);
            fim = i - 1;
        } else if(i == 0)
            for(j = 0; j <= fim; j ++)
                printf("%d %c %d\n", letras[j].tamanho, letras[j].letra[0], letras[j].pos);
    }
}

int main()
{
    char str[100000];
    Item letras[100000];

    scanf("%s", str);

    separaLetra(str, letras);

    return 0;
}