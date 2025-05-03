#include <stdio.h>
#include <omp.h>

int main() {
    const int num_elements = 901;
    const int num_threads = 4;
    int thread_counts[num_threads];

    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        int count = 0;

        #pragma omp for
        for (int i = 0; i < num_elements; i++) {
            // Simule algum processamento em cada elemento do vetor
            count++;
        }

        thread_counts[tid] = count;
    }

    // Imprima o número de elementos processados por cada thread
    printf("Número de elementos processados por cada thread:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Thread %d: %d elementos\n", i, thread_counts[i]);
    }

    return 0;
}
