#include <stdio.h>
#include <stdlib.h>

#define exch(A, B) {sem t = B; B = A; A = t;}
#define lessNOTA(A, B) (A.nota == B.nota ? A.cod < B.cod : A.nota < B.nota)
#define lessCOD(A, B) (A.cod == B.cod ? A.nota < B.nota : A.cod < B.cod)
#define cmpexchNOTA(A, B) {if(lessNOTA(B, A)) exch(A ,B);}

#define cmpexchCOD(A, B) {if (lessCOD(B, A)) exch(A, B);}

typedef struct sem{
    long long cod;
    int nota;
} sem;
sem sementes[10000001];

int separa(sem *v, int l, int r)
{
    sem aux = v[r];
    int j = l,k;
    
    for (k = l; k < r; k++){
        if (lessNOTA(v[k], aux)){
            exch(v[k], v[j]);
            j++;
        }
    } 
    exch(v[j], v[r]);
    return j;
}

void quicksortMD3(sem *v, int l, int r)
{
    if (l>=r) return;

    exch(v[(l + r) / 2], v[r - 1]);
    cmpexchCOD(v[l], v[r - 1]);
    cmpexchCOD(v[l], v[r]);
    cmpexchCOD(v[r - 1], v[r]);

    int j = separa(v, l, r);
    quicksortMD3(v, l, j - 1);
    quicksortMD3(v, j + 1, r);
}

void insertionsort(sem *v, int l, int r)
{
    int i,j;
    for (i = l + 1, j; i <= r; i++)
    {
        sem temp = v[i];
        j = i;
        while(j > 0 && lessCOD(temp, v[j - 1])){
            v[j] = v[j - 1];
            j--;
        }   
        v[j] = temp;
    }
}

void quicksort2(sem *v, int l, int r)
{
    quicksortMD3(v, l, r);
    insertionsort(v, l, r);
}

void quickselect(sem *v, int l, int r, int p)
{
    cmpexchNOTA(v[(l + r) / 2], v[r]);
    cmpexchNOTA(v[l], v[(l + r) / 2]);
    cmpexchNOTA(v[r], v[(l + r) / 2]);

    int j = separa(v, l, r);
    if (j > p)
        quickselect(v, l, j - 1, p);
    else if (j < p)
        quickselect(v, j + 1, r, p);
}

int main(void){
    int n, i = 0;

    scanf("%d", &n);

    while(scanf("%lld %d", &sementes[i].cod, &sementes[i].nota) != EOF){
        i++;
    }

    quickselect(sementes, 0, i-1, n-1); // N melhores notas
    quicksort2(sementes, 0, n-1); // sort N sementes por codigo

    for(int j = 0; j < n; j++){
        printf("%lld %d\n", sementes[j].cod, sementes[j].nota);
    }

    return 0;
}