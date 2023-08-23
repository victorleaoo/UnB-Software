#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Declaração global dos vetores
int v1[10000000];
int v2[10000000];

// Struct Thread
struct thread_st{
    int *v;  // vetor da thread
    int tam; // tamanho do vetor 
    pthread_t tid; // pid da thread para join no fim
};

// Função para qsort fazer a comparação
int comparaSort(const void *a, const void *b){
    if(*(int *)a > *(int*)b) return 1;
    if(*(int *)a < *(int*)b) return -1;
    return 0;
}

// Função que vai fazer o sort
void *threadsort(void *t){
    struct thread_st *a = (struct thread_st*)t; // Cria uma nova thread struct dependendo de qual foi a passada como argumento
    qsort(a->v, a->tam, sizeof(int), comparaSort);
}

// Função para ler vetores
void le_vetores(int qual, int tam){
    if(qual == 1){
        for(int i = 0; i < tam; i++){
            scanf("%d", &v1[i]);
        }
    } else{
        for(int i = 0; i < tam; i++){
            scanf("%d", &v2[i]);
        }
    }
    return;
}

int main(void){
    int tam, igual = 1;

    scanf("%d", &tam);

    // Lê vetores
    le_vetores(1, tam);
    le_vetores(2, tam);

    /* Teste de Impressão
    for(int i = 0; i < tam; i++){
        printf("%d - ", v1[i]);
    }
    printf("\n\n");
    for(int i = 0; i < tam; i++){
        printf("%d - ", v2[i]);
    }
    printf("\n\n");
    */

    // Declaração threads
    struct thread_st t1, t2;
    t1.v = v1;
    t1.tam = tam;
    t2.v = v2;
    t2.tam = tam;

    // Ordenação + Espera (join)
    pthread_create(&t1.tid, NULL, threadsort, (void*)&t1);
    pthread_create(&t2.tid, NULL, threadsort, (void*)&t2);

    pthread_join(t1.tid, NULL);
    pthread_join(t2.tid, NULL);

    for(int i = 0; i < tam; i++){
        if(!(v1[i] == v2[i])){
            igual = 0;
        }
    }

    if(igual == 1){
        printf("Mesmos elementos\n");
        return 0;
    } 
    
    printf("Diferentes\n");
    return 0;
}