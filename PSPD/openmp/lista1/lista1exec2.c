#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[]) {
    int i=0;
    #pragma omp parallel shared(i)
    {
        i=i+10;
    }
    printf("i=%d\n", i);
    return 0;
}