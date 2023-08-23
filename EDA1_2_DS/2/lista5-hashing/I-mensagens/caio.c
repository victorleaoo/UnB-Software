// Funciona

#include <stdio.h>
#include <stdlib.h>

#define SIZE ((1<<20)+10)
char str[SIZE*2+100];

int main() {
    char *conjunto = &str[SIZE];
    int num, letra, i, menor = 0, maior = 0, aux;

    scanf("%d %c", &num, &letra);

    aux = num;
    conjunto[0] = letra;

    while(scanf("%d %c", &num, &letra) == 2) {
        num -= aux;
        conjunto[num] = letra;
        if(num < menor)
            menor = num;
        else if(num > maior)
            maior = num;
    }

    conjunto[maior+1] = '\0';

    printf("%s\n", &conjunto[menor]);

    return 0;
}