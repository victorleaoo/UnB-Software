#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void addVectors(float *c, const float *a, const float *b, int size) {
    #pragma omp parallel for simd
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    const int arraySize = 10000000;
    float *a = (float*)malloc(arraySize * sizeof(float));
    float *b = (float*)malloc(arraySize * sizeof(float));
    float *c = (float*)malloc(arraySize * sizeof(float));

    // Preenchendo os vetores
    for (int i = 0; i < arraySize; i++) {
        a[i] = i + 1;
        b[i] = 10 * (i + 1);
    }

    // Somando os vetores usando OpenMP e SIMD
    addVectors(c, a, b, arraySize);

    // Imprimindo o resultado
    printf("{1, 2, 3, 4, 5} + {10, 20, 30, 40, 50} = {%f, %f, %f, %f, %f}\n", c[0], c[1], c[2], c[3], c[4]);

    // Liberando a memória alocada
    free(a);
    free(b);
    free(c);

    return 0;
}
