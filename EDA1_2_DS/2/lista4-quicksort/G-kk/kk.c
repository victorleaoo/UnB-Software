#include <stdio.h>
#include <stdlib.h>

#define key(A) (A)
#define less(A,B) (key(A) < key(B))
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

void quickselect(int *v, int l, int r, int p){
    int j;

    if(r <= l) return;

    j = separa(v, l, r);

    if(j > p)
        quickselect(v, l, j-1, p);
    else if(j < p)
        quickselect(v, j+1, r, p);
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

int main(void){
    int n, p, x; // n = qntd produtos / p = pag apresentada / x = quantidade de produtos por pag

    scanf("%d %d %d", &n, &p, &x);

    int inicio = x*p; // primeiro produto da pag
    int fim = inicio+x; // ultimo produto da pag -> nao incluso

    // cuidado com isso
    if(fim > n){
        fim = n;
    }

    int *v = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    quickselect(v, 0, n-1, inicio);
    quickselect(v, inicio+1, n-1, fim);

    quicksort(v, inicio, fim-1);

    for(int i = inicio; i < fim; i++){
        printf("%d\n", v[i]);
    }

    free(v);

    return 0;
}