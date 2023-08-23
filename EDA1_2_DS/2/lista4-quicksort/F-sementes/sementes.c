#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//macros

#define ull unsigned long long
#define less(a, b) (a.notaSemente == b.notaSemente ? a.codSemente < b.codSemente : a.notaSemente < b.notaSemente)
#define less2(a, b) (a.codSemente == b.codSemente ? a.notaSemente < b.notaSemente : a.codSemente < b.codSemente)
#define exch(a, b) { Item t = a;a = b;b = t;}
#define cmpexch(a, b) {if (less(b, a)) exch(a, b);}
#define cmpexch2(a, b) {if (less2(b, a)) exch(a, b);}

//struct para sementes

typedef struct
{
    long long codSemente;
    int notaSemente;
} Item;

//funcoes assinadas

void quicksort2(Item *sementeCompleto, int l, int r);
void quicksortM3(Item *sementeCompleto, int l, int r);
int separa(Item *sementeCompleto, int l, int r);
void quickselect(Item *sementeCompleto, int l, int r, int i);
void insertionsort(Item *sementeCompleto, int l, int r);

//variaveis globais

Item sementeCompleto[10000001];

//main



