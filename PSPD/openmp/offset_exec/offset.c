#include <stdio.h>
#include <omp.h>
#define MAX 13

int main(void) {
    int n=3;
    int lido;
    int sumn=0;
    int offset;

    FILE *fd;

    int i, maximo_for;
    
    #pragma omp parallel private(lido, offset, i, fd, maximo_for) reduction(+:sumn)
    {
    fd=fopen("./arquivo.in", "r");
    offset = (MAX/omp_get_num_threads())*omp_get_thread_num()*3;

    //printf("offset: %d -- Thread: %d\n", offset, omp_get_thread_num());

    fseek(fd, offset, SEEK_SET);

    maximo_for = (omp_get_thread_num() == omp_get_num_threads() - 1) ? ((MAX/omp_get_num_threads()) + MAX%omp_get_num_threads()) : (MAX/omp_get_num_threads());

    for (i=0; i<maximo_for;i++) {
        fscanf(fd, "%d", &lido);
        printf("Numero lido: %d -- Thread: %d\n", lido, omp_get_thread_num());
        if (lido == n)
            sumn++;
        } /* fim-for */
    
    }

    printf("Total de %d's = %d\n", n, sumn);
    return 0;
} 