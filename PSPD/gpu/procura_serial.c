#include <stdio.h>
#include <stdlib.h>

int countOccurrences(int *arr, int size, int target) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            result++;
        }
    }

    return result;
}

int main() {
    const int arraySize = 10000000;
    const int target = 42;

    int *arr = (int*)malloc(arraySize * sizeof(int));

    // Preencha o vetor com valores para a busca
    for (int i = 0; i < arraySize; i++) {
        arr[i] = i % 50;
    }

    // Conte o número de ocorrências de forma serial
    int result = countOccurrences(arr, arraySize, target);

    // Imprima o resultado
    printf("O número %d aparece %d vezes no vetor.\n", target, result);

    // Libere a memória alocada
    free(arr);

    return 0;
}
