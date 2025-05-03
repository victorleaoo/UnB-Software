#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

__global__ void countOccurrences(int *arr, int size, int target, int *result) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size) {
        if (arr[tid] == target) {
            atomicAdd(result, 1);
        }
    }
}

int main() {
    const int arraySize = 10000000;
    const int target = 42;

    int *arr = (int*)malloc(arraySize * sizeof(int));
    int *result = (int*)malloc(sizeof(int));
    *result = 0;

    for (int i = 0; i < arraySize; i++) {
        arr[i] = i % 50;  // Preencha o vetor com valores para a busca
    }

    int *dev_arr;
    int *dev_result;

    // Aloque memória na GPU
    cudaMalloc((void**)&dev_arr, arraySize * sizeof(int));
    cudaMalloc((void**)&dev_result, sizeof(int));

    // Copie o vetor e o resultado para a GPU
    cudaMemcpy(dev_arr, arr, arraySize * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_result, result, sizeof(int), cudaMemcpyHostToDevice);

    // Configura a chamada do kernel
    dim3 dimBlock(256);
    dim3 dimGrid((arraySize + dimBlock.x - 1) / dimBlock.x);

    // Chame o kernel
    countOccurrences<<<dimGrid, dimBlock>>>(dev_arr, arraySize, target, dev_result);

    // Copie o resultado de volta para o host
    cudaMemcpy(result, dev_result, sizeof(int), cudaMemcpyDeviceToHost);

    // Imprima o resultado
    printf("O número %d aparece %d vezes no vetor.\n", target, *result);

    // Libere a memória alocada
    free(arr);
    free(result);
    cudaFree(dev_arr);
    cudaFree(dev_result);

    return 0;
}
