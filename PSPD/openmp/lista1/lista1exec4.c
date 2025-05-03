#include <stdio.h>
#include <omp.h>
#define N 300000

// 0m5.890s
/* int main(void) {
    int i;
    int primos=0;

    for (i=N; i>1; i--) {
        int j=2;
        while (j<i) {
            if (i%j == 0)
                break;
            j++;
        } 
        if (j==i)
            primos++;
    } 

    printf("%d primos!\n", primos);
    return 0;
}  
*/

// 4: 0m2.506s
// 8: 0m1.867s
// 16: 0m0.984s
// 32: 0m0.820s
int main(void) {
    int i;
    int primos=0;

    #pragma omp parallel for reduction(+:primos)
    for (i=N; i>1; i--) {
        int j=2;
        while (j<i) {
            if (i%j == 0)
                break;
            j++;
        } 
        if (j==i)
            primos++;
    } 

    printf("%d primos!\n", primos);
    return 0;
}  