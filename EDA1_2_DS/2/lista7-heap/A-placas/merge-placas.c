// Funciona, mas não passa no moj, já que é muito caro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 100000
#define less(A, B) (A < B)

void merge(int *vetor, int l, int m, int r){
   int l1 = l, r1 = m, l1i = l1;
   int l2 = m+1, r2 = r, l2i = l2;

   int *c = malloc((r-l+1)*sizeof(int));
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
      vetor[l1i++] = c[ci];
   }

   free(c);
}

void mergesort(int *vetor, int l, int r){
   if (l >= r) return;
   int meio = (r - l)/2 + l;
   mergesort(vetor, l, meio);
   mergesort(vetor, meio+1, r);
   merge(vetor, l, meio, r); // junta os dois vetores
}

void armazena(int *vetor, int i){
   if(i > M-1) return;
   scanf(" %d", &vetor[i]);
   return ;
}

void imprime(int *vetor){
   int quantidade;
   scanf(" %d", &quantidade);
   mergesort(vetor, 0, M-1);
   int i = 0;
   while(vetor[i] == 0){
      i++;
   }
   int j = i+quantidade-1;
   for(i; i <= j; i++)
      printf("%d ", vetor[i]);
   printf("\n");
}

int main (void){
   int i = 0;
   int *vetor = malloc(M*sizeof(int));
   memset(vetor, 0, sizeof(int)*M);    
   int n;
   while(scanf(" %d", &n) != -1){
      if(n == 1){
         armazena(vetor, i);
         i++;
      }else if(n == 2) imprime(vetor);
   }
        
   return 0;
}