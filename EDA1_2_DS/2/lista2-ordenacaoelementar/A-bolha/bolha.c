#include <stdio.h>

#define less(A,B) (A < B)
#define exch(A, B) {int t = B; B = A; A = t;}
#define cmpexch(A, B) {if(less(B, A)) exch(A, B);}

void bubblesort(int *vetor, int l, int r){
    for(int i = l; i < r; i++){
        for(int j = l+1; j <= r; j++){
            cmpexch(vetor[j-1], vetor[j]);
        }
    }
}

int main(void){
    int v[1000], num, i = 0;

    while (scanf("%d", &num) != EOF){
        v[i] = num;
        i++;
    }

    bubblesort(v, 0, i-1);

    int j;

    for (j = 0; j < i - 1; j++){
        printf("%d ", v[j]); 
    }

    printf("%d\n", v[j]);

    return 0;
}