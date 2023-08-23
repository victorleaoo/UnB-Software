#include <stdio.h>
#include <stdlib.h>

void ordvetor(int *v, int left, int right) {
    int l, r, x, tmp;
     
    l = left;
    r = right;
    x = v[(left + right) / 2];
     
    while(l <= r) {
        while(v[l] < x && l < right) {
            l++;
        }
        while(v[r] > x && r > left) {
            r--;
        }
        if(l <= r) {
            tmp = v[l];
            v[l] = v[r];
            v[r] = tmp;
            l++;
            r--;
        }
    }

    if(r > left) {
        ordvetor(v, left, r);
    }
    
    if(l < right) {
        ordvetor(v, l, right);
    }

}

int main()
{
    int n, i, u, freq = 0;
    int *alunos = malloc(100000*sizeof(int));

    scanf("%d", &n);

    for(i = 0; i < n; i ++) {
        scanf("%d", &alunos[i]);
    }
    
    ordvetor(alunos, 0, n - 1);

    for (i = 0; i < n - 1; i ++) {
        if (alunos[i] == alunos[i + 1]){
            alunos[i] = -1; // se for repetido, -1
        } 
    }  
        
    for (i = 0; i < n; i ++){
        if(alunos[i] != -1){
            freq ++; //se não for repetido, +1 na frequência
        } 
    }
    
    printf("%d\n", freq);

    return 0;
}