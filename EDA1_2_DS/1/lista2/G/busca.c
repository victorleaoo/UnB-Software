#include <stdio.h>

int recMove (long int *v, int i, int elem){
    if(i < 0 || v[i] <= elem) return i;
    v[i+1] = v[i];
    recMove(v, i-1, elem);
}

void ordena (long int *v, long int n){
    //Caso Base
    if(n <= 1) return;

    //Redução
    ordena (v, n-1);

    //Insere o elemento v[n-1] na posição correta no subvetor v[0...n-1]
    int elem = v[n-1];
    int i = recMove(v, n-2, elem);
    v[i+1] = elem;
}

void busca(long int tamanhoN, long int tamanhoM, long int N[], long int M[], long int j[]){

    int m, e, d, i;

    for(i = 0; i < tamanhoM; i++){
        e = -1;
        d = tamanhoN;
        while(e != (d-1)){ // só encontrou o j quando e == d-1
            m = (e+d)/2;
            if(M[i] > N[m]){
                e = m; // Se tiver à esquerda de m, o esquerdo vira m 
            } else{
                d = m; // Se tiver à direita de m, o direita vira m
            } 
        }
        j[i] = d;
    }
}

int main(){

    long int N[100000], M[100000], j[100000], tamanhoN, tamanhoM;

    scanf("%ld %ld", &tamanhoN, &tamanhoM);
 
    for(int i = 0; i < tamanhoN; i++){
        scanf("%ld", &N[i]);
    }
 
    for(int i = 0; i < tamanhoM; i++){
        scanf("%ld", &M[i]);
    }

    // Ordena o vetor N para que seja possível executar a busca
    ordena(N, tamanhoN);
  
    // Faz a busca dos inteiros M
    busca(tamanhoN, tamanhoM, N, M, j);

    for(int i = 0; i < tamanhoM; i++){
        printf("%ld \n", j[i]);
    }

    return 0;
}