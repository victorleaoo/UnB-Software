#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, *soma;
    char string[100];

    scanf("%d", &n);

    soma = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        soma[i] = 0;
        scanf(" %s", string);
        for (int j = 0; j < strlen(string); j++){
            if(string[j] > 48 && string[j] <= 57){
                soma[i] += (string[j]) - '0';
            }
        }
    }

    for (int i = 0; i < n; i++){
        printf("%d\n", soma[i]);
    }
    return 0;
}