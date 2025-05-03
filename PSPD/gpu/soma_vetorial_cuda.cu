#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void addKernel(float* c, float* a, float* b, int size) {
    int i = threadIdx.x;

    if (i < size) {
        c[i] = a[i] + b[i];
    }
}

int main(int argc, char** argv) {
    const int arraySize = 10000000;
    float *a = (float*)malloc(arraySize * sizeof(float));
    float *b = (float*)malloc(arraySize * sizeof(float));
    float *c = (float*)malloc(arraySize * sizeof(float));

    for (int i = 0; i < arraySize; i++) {
        a[i] = i + 1;
        b[i] = 10 * (i + 1);
    }

    float* dev_a;
    float* dev_b;
    float* dev_c;

    // Allocate GPU buffers for three vectors (two input, one output)
    cudaMalloc((void**)&dev_c, arraySize * sizeof(float));
    cudaMalloc((void**)&dev_a, arraySize * sizeof(float));
    cudaMalloc((void**)&dev_b, arraySize * sizeof(float));

    // Copy input vectors from host memory to GPU buffers.
    cudaMemcpy(dev_a, a, arraySize * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, arraySize * sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (arraySize + threadsPerBlock - 1) / threadsPerBlock;

    // Launch a kernel on the GPU with multiple threads and blocks.
    addKernel<<<blocksPerGrid, threadsPerBlock>>>(dev_c, dev_a, dev_b, arraySize);

    // Copy output vector from GPU buffer to host memory.
    cudaMemcpy(c, dev_c, arraySize * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < 5; i++) {
        printf("%f + %f = %f\n", a[i], b[i], c[i]);
    }

    free(a); free(b); free(c);

    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);

    return 0;
}