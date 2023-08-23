#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int matriz1[2000][2000], matriz2[2000][2000], matriz3[2000][2000];
// Sinais dos filhos
int sinalfilho1 = 0, sinalfilho2 = 0;

void filho1(int s){
    sinalfilho1++;
}

void filho2(int s){
    sinalfilho2++;
}

void multiplicaMatrizes(int dim, int l, int r, int sinal){
    // Calcula a multiplicação necessária
    for(int i = l; i < r; i++){
        for(int j = 0; j < dim; j++){
            for(int k = 0; k < dim; k++){
                matriz3[i][j] += matriz1[i][k]*matriz2[k][j];
            }
        }
    }
    // Avisa que acabou e espera
    kill(getppid(), sinal);
    pause();

    // Recebeu de volta, imprime
    for(int i = l; i < r; i++){
        printf("%d", matriz3[i][0]);
            for(int j=1; j< dim; j++){
                printf(" %d", matriz3[i][j]);
        }
        printf("\n");
    }
    kill(getppid(), sinal);

    exit(0);
}

int main(void){
    int dim;

    signal(SIGUSR1, filho1);
    signal(SIGUSR2, filho2);

    scanf("%d", &dim);

    int recebe = dim/2, resto = dim%2;
    pid_t filhos[2];
    int sinais[2];
    sinais[0] = SIGUSR1;
    sinais[1] = SIGUSR2;

    // Leitura matriz 1
    for(int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j ++){
            scanf("%d", &matriz1[i][j]);
            matriz3[i][j]=0; // Garantir que começa zerada
        }
    }

    // Leitura matriz 2
    for(int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j ++){
            scanf("%d", &matriz2[i][j]);
        }
    }
    
    for (int i = 0; i < 2; i++){
        int l = i*recebe, sinal = sinais[i], r;
        if(i == 1){
            r = resto + i*recebe+recebe; // Caso seja ímpar, o resto vai afetar nos resultados
        }else{
            r = i*recebe+recebe;
        }
        filhos[i] = fork(); // Gera o filho
        if(filhos[i]==0){
            multiplicaMatrizes(dim, l, r, sinais[i]);
        }
    }

    pause(); // Espera calcular

    // Um dos dois vai voltar o sinal que acabou de calcular, daí manda esperar
    while(sinalfilho1 == 0 || sinalfilho2 == 0){
        pause();
    }

    kill(filhos[0], SIGUSR1);
    wait(NULL);
    kill(filhos[1], SIGUSR1);
    wait(NULL);
}