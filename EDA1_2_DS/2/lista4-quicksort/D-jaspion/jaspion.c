#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(A) (A.jpn)
#define less(A,B) ((strcmp(key(A), key(B)) < 0))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Item{
    char jpn[81];
    char ptbr[81];
} Item;

Item dict[1000001];

int buscaBinaria(Item *vetor, int r, char *valor) {
    int e = -1, d = r, m;

    while (e < d - 1) {
        m = (e + d)/2;

        if (strcmp(key(vetor[m]), valor) < 0){ //************************
            e = m;
        } else{
            d = m;
        } 
    }

    if(strcmp(key(vetor[d]), valor) == 0){ //************************
        return d;
    } else{
        return -1;
    }
}

int separa(Item *v,int l, int r){
  Item aux = v[r];
  int i, j = l;

  for(i = l; i < r; i++){
    if(less(v[i], aux)){
      exch(v[i], v[j]);
      j++;
    }
  }    
  
  exch(v[j], v[r]);

  return j;
}

void quicksort(Item *v,int l, int r){
  if (l >= r) return; // Critério de parada

  cmpexch(v[(l+r)/2], v[r]);
  cmpexch(v[l], v[(l+r)/2]);
  cmpexch(v[r], v[(l+r)/2]);

  int j = separa(v, l, r);
  quicksort(v, l, j-1);
  quicksort(v, j+1, r);
}

void traduz(){
    int m, n;
    scanf("%d %d", &m, &n);

    for(int i = 0; i < m; i++){
        scanf(" %s", dict[i].jpn);
        scanf(" %[^\n]", dict[i].ptbr);
    }

    quicksort(dict, 0, m-1);

    n++;

    while (n--)
    {
        char linha[81];
        gets(linha);
        char *b;
        b = strtok(linha, " "); // separa a linha lida em diferentes partes separadas por " "
        while (b != NULL)
        {
            int j = buscaBinaria(dict, m, b);
            if(j < 0){
                printf("%s", b);
            } else{
                printf("%s", dict[j].ptbr);
            }
            b = strtok(NULL, " ");
            if(b == NULL){
                printf("\n");
            } else{
                printf(" ");
            }
        }
    }
    
/*
    for(int i = 0; i < n; i++){
        char b[81], p;

        while(scanf(" %s%c", b, &p) == 2){ //DIFERENTE DE 0
            //printf("\n\n leu: %s\n\n", b);
            int j = buscaBinaria(dict, m, b);
            //printf("\n\n peguei: %s\n\n", dict[j].jpn);
            if(j < 0){
                printf("%s", b);
            } else{
                printf("%s", dict[j].ptbr);
            }
            printf("%c", p);

            if(p == '\n'){
                break;
            } 
        }
        if(i == n-1){
            scanf(" %s", b);
            int j = buscaBinaria(dict, m, b);
            if(j < 0){
                printf("%s\n", b);
            } else{
                printf("%s\n", dict[j].ptbr);
            }
        }
    }
    */
}


int main(void){
    int t;

    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        traduz();
        printf("\n");
    }

    return 0;
}