#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Manipulação dos sinais
int sinal = 0;

void sinalrecebido(int s){
    if(sinal == 0){
        sinal++;
        if(fork() == 0){
            exit(0); // Cria zumbi (mata o filho sem o pai receber o sinal)
        }
    } else if(sinal == 1){
        sinal++;
        wait(NULL); // Mata zumbi
    } else{
        exit(0);
    }
}

int main(void){
    signal(SIGUSR1, sinalrecebido);
    signal(SIGUSR2, sinalrecebido);

    // Tem que rodar para sempre (até exit)
    while (1){
        pause();
    } 
}