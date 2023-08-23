#include <stdio.h>
#include <stdlib.h>

#define key(x) (x)
#define less(a, b) (a < b)
#define exch(A,B) {int t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

int separa(int *v,int l, int r){
  int aux = v[r], i, j = l;

  for(i = l; i < r; i++){
    if(less(v[i], aux)){
      exch(v[i], v[j]);
      j++;
    }
  }    
  
  exch(v[j], v[r]);

  return j;
}

void quicksort(int *v,int l, int r){
  if (l >= r) return; // Critério de parada

  cmpexch(v[(l+r)/2], v[r]);
  cmpexch(v[l], v[(l+r)/2]);
  cmpexch(v[r], v[(l+r)/2]);

  int j = separa(v, l, r);
  quicksort(v, l, j-1);
  quicksort(v, j+1, r);
}

void merge(int *a, int r1, int *b, int r2){

    int *c = malloc((r1 + r2) * sizeof(int));

    int l1i = 0, l2i = 0, ci = 0;

    while (l1i < r1 && l2i < r2){
        if (less(a[l1i], b[l2i])){
            c[ci++] = a[l1i++];
        } else {
            c[ci++] = b[l2i++];
        }
    }

    while (l1i < r1){
        c[ci++] = a[l1i++];
    }
    while (l2i < r2){
        c[ci++] = b[l2i++];
    }

    ci = 0;
    for (l1i = 0; l1i < (r1 + r2); l1i++){
        a[l1i] = c[ci++];
    }

    free(c);
}

int removeRepetidos(int *v, int n){
    int tam = 1;

    for (int i = 1; i < n; i++){
        if (v[i] != v[tam - 1]){
            v[tam++] = v[i];
        }
            
    }

    return tam;
}

int main(){

    int n;
    scanf("%d", &n);

    int *v = malloc(sizeof(int) * (2 * n));

    for (int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    quicksort(v, 0, n-1);

    int tam = removeRepetidos(v, n);

    if (tam % 2 != 0){
        v[tam++] = 1000000000;
    }

    int novo_tam = 0;

    // Novo vetor com os números malucos
    for (int i = 0; i < tam - 1; i += 2){
        v[tam + novo_tam++] = v[i] + v[i + 1];
    }

    // Junção dos vetores
    merge(v, tam, v + tam, novo_tam);
    
    tam = removeRepetidos(v, tam + novo_tam);

    for (int i = 0; i < tam; i += 4){
        printf("%d\n", v[i]);
    }

    printf("Elementos: %d\n", tam);

    return 0;
}