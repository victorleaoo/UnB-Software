#include <stdio.h>

int main(){
    int n, a, soma = 0;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++){
        scanf("%d", &a);
        soma += a;
    }

    printf("%d", soma);
    return 0;
}