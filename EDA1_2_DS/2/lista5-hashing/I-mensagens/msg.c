#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global, pois pode ser maior que o tamanho da pilha
char max[2097272]; // 2^20 * 2 + 110

int main(void){
    char *msg = &max[1048586];
    int cod, menor = 0, maior = 0, i;
    char letra;

    scanf("%d %c", &cod, &letra);
    i = cod;
    msg[0] = letra; // Assume que o menor elemento é o primeiro

    while (scanf("%d %c", &cod, &letra) == 2){
        cod = cod - i; // pequeno "hash", para que o elemento caiba no vetor, independente do seu valor
        msg[cod] = letra;

        if(cod < menor){
            menor = cod;
        } else if(cod > maior){
            maior = cod;
        }
    }

    msg[maior+1] = '\0'; // Fim de String
    for(int j = menor; j < maior+1; j++){
        printf("%c", msg[j]);
    }
    printf("\n");
    //printf("%s\n", &msg[menor]);
    
    return 0;
}