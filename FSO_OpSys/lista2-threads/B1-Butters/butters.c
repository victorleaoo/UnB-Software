#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int encontrados[10000000];

struct argumento{
    int mi;
    int mf;
    int qual;
    int tam;
};

int preenche_encontrados(){
    int n, i = 0;

    while(scanf("%d", &n) != EOF){
        encontrados[i++] = n;
    }

    return i;
}

void *procura_seed(void *arg){
    int atual, aux, final, aux_rand;

    struct argumento *p = (struct argumento*)arg;

    //printf("%d -> %d - %d -> %d\n\n", p->qual, p->mi, p->mf, p->tam);

    for(int i = p->mi; i <= p->mf; i++){
        aux_rand = i;
        aux = 0;

        for(int l = 0; l < p->tam; l++){
            for(int j=1; j<10000;j++){
                rand_r(&aux_rand);
            }

            final = (rand_r(&aux_rand) % 256); // ok

            if(final != encontrados[aux]){
                break;
            }  // ok

            if(aux == p->tam-1 && final == encontrados[aux]){
                printf("%d\n", i);
                return;
            } 
            aux++;
        }
    }
}

int main(void){
    int mi, mf;

    scanf("%d %d", &mi, &mf);

    int a = 0, b = 1;

    int tam = preenche_encontrados();

    struct argumento arg1, arg2;

    arg1.mi = mi;
    arg1.mf = (mi+mf)/2;
    arg1.qual = 0;
    arg1.tam = tam;

    arg2.mi = (mi+mf)/2 + 1;
    arg2.mf = mf;
    arg2.qual = 1;
    arg2.tam = tam;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, procura_seed, (void *)&arg1);
    pthread_create(&t2, NULL, procura_seed, (void *)&arg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}