#include <stdio.h>
#include <stdlib.h>

#define key(A){A.key}
#define less(A,B) (A < B)
#define exch(A, B) {int t = B; B = A; A = t;}
#define cmpexch(A, B) {if(less(B, A)) exch(A, B);}

void insertionsort(int *vetor, int l, int r){
    for(int i = r; i > l; i--){
        cmpexch(vetor[i-1], vetor[i]);
    } 
    for(int i = l+1; i <= r; i++){
        int j = i - 1;
        int tmp = vetor[j + 1]; //segura o valor
        while(less(tmp, vetor[j])){
            vetor[j + 1] = vetor[j--];
        }
        vetor[j + 1] = tmp;
    }
}

int main(void){
    int j, i = 0, r = 10;

    int *v = malloc(r * sizeof(int));

    while(scanf("%d", &v[i]) != EOF) {
        if(i == r-1) {
            r = r*2;
            v = realloc(v, r*sizeof(int));
        }
        i++;
    }

    insertionsort(v, 0, i-1);

    for(j = 0; j < i - 1; j ++){
        printf("%d ", v[j]);
    }
        
    printf("%d\n", v[j]);

    free(v);
    return 0;
}