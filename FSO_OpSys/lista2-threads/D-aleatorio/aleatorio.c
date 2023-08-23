#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int encontrados[10000000];

struct argumento{
    int mi;
    int mf;
    int s;
};

void procura_seed(int mi, int mf, int s){
    int atual, aux, final, aux_rand;

    //printf("%d\n\n", s);

    for(int i = mi; i <= mf; i++){
        aux_rand = i;
        aux = 0;

        for(int j=1; j<100000;j++){
            rand_r(&aux_rand);
        }

        final = (rand_r(&aux_rand) % 8); // ok
        //printf("---- %d\n", final);

        if(final != s){
            continue;
        }  // ok

        if(final == s){
            printf("%d\n", i);
        } 
        aux++;
    }
    return;
}

/*
void *procura_seed(void *arg){
    int atual, aux, final, aux_rand;

    struct argumento *p = (struct argumento*)arg;

    printf("%d -> %d - %d\n\n", p->s, p->mi, p->mf);

    for(int i = p->mi; i <= p->mf; i++){
        aux_rand = i;
        aux = 0;

        for(int j=1; j<10000;j++){
            rand_r(&aux_rand);
        }

        final = (rand_r(&aux_rand) % 8); // ok
        //printf("---- %d\n", final);

        if(final != encontrados[aux]){
            continue;
        }  // ok

        if(final == p->s){
            printf("%d\n", i);
        } 
        aux++;
    }
    return;
}
*/

int main(void){
    int mi, mf, s;

    scanf("%d %d %d", &mi, &mf, &s);

    int a = 0, b = 1;

    /*struct argumento arg1, arg2;

    arg1.mi = mi;
    arg1.mf = (mi+mf)/2;
    arg1.s = s;

    arg2.mi = (mi+mf)/2 + 1;
    arg2.mf = mf;
    arg2.s = s;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, procura_seed, (void *)&arg1);
    pthread_create(&t2, NULL, procura_seed, (void *)&arg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    */

   procura_seed(mi, mf, s);

    return 0;
}