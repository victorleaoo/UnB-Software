#include <stdio.h>
#include <omp.h>

int main(){
	int myid, nthreads;

	myid = 0;
	nthreads = 2;

	printf("%d of %d - hello world!\n", myid, nthreads);

	return 0;
}
