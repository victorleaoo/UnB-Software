#include <stdio.h>
#include <stdlib.h>

#define key(A)(A.key)
#define less(A,B) (key(A) < key(B))
#define exch(A, B) {instrucao t = B; B = A; A = t;}
#define cmpexch(A, B) {if(less(B, A)) exch(A, B);}

typedef struct instrucao
{
    int key;
    char inst[16];
} instrucao;

void insertionsort(instrucao *vetor, int l, int r){
    for(int i = r; i > l; i--){
        if(less(vetor[i], vetor[i-1])){
            exch(vetor[i], vetor[i-1])
        }
    }
    for(int i = l+1; i <= r; i++){
        int j = i - 1;
        instrucao tmp = vetor[j + 1]; //segura o valor
        while(less(tmp, vetor[j])){
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = tmp;
    }
}

void buscaBinaria(instrucao *vetor, int l, int r, int valor){
    while (l <= r)
    {
        int m = (l + r) / 2;
        // Encontrou
        if (key(vetor[m]) == valor){
            printf("%s\n", vetor[m].inst);
            return;
        }   

        if (key(vetor[m]) > valor){
            r = m - 1;
        }else{
            l = m + 1;
        }
    }

    // Caso não encontre
    printf("undefined\n");
    return;
}

int main(void){
    int n, valor;

    scanf("%d", &n);

    instrucao *instrucoes = malloc(n*sizeof(instrucao));

    for (int i = 0; i < n; i++){
        scanf("%d %s", &instrucoes[i].key, instrucoes[i].inst);
    }
    
    insertionsort(instrucoes, 0, n-1);

    while(scanf("%d", &valor) != EOF){
        buscaBinaria(instrucoes, 0, n-1, valor);
    }

    return 0;
}