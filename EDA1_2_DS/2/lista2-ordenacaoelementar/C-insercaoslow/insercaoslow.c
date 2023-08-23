// NÃO FUNCIONA!!

#include <stdio.h>

#define less(A,B) (A < B)
#define exch(A, B) {int t = B; B = A; A = t;}
#define cmpexch(A, B) {if(less(B, A)) exch(A, B);}

void insertionslow(int *vetor, int l, int r){
    for(int i = l+1; i <= r; i++){
        for(int j = i; j > l; j--){
            cmpexch(vetor[j-2], vetor[i]);
        }
    }
}

int main(void){
    int v[1000], num, i = 0;

    while (scanf("%d", &num) != EOF){
        v[i] = num;
        i++;
    }

    insertionslow(v, 0, i-1);

    int j;

    for (j = 0; j < i - 1; j++){
        printf("%d ", v[j]); 
    }

    printf("%d\n", v[j]);

    return 0;
}