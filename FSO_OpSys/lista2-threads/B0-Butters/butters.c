#include <stdio.h>
#include <stdlib.h>

int encontrados[10000000];

int preenche_encontrados(){
    int n, i = 0;

    while(scanf("%d", &n) != EOF){
        encontrados[i++] = n;
    }

    return i;
}

int procura_seed(int mi, int mf, int tam){
    int atual, aux, final, aux_rand;

    for(int i = mi; i <= mf; i++){
        aux_rand = i;
        aux = 0;

        for(int l = 0; l < tam; l++){
            for(int j=1; j<10000;j++){
                rand_r(&aux_rand);
            }

            final = (rand_r(&aux_rand) % 256); // ok

            if(final != encontrados[aux]){
                break;
            }  // ok

            if(aux == tam-1 && final == encontrados[aux]){
                return i;
            } 

            aux++;
        }
    }
}

int main(void){
    int mi, mf;
    
    scanf("%d %d", &mi, &mf);

    int tam = preenche_encontrados();

    /*
    for(int i = 0; i < tam; i++){
        printf("\n%d\n", encontrados[i]);
    }
    */

    printf("%d\n", procura_seed(mi, mf, tam));

    return 0;
}