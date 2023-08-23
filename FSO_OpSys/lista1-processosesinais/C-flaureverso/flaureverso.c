#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sinalrecebido(int s){
    char nome[11];
    int achou = 0;
    if(scanf(" %s", nome) != EOF){
        if(s == SIGUSR1 && strcmp(nome, "Igor3k") == 0){
            printf("Certo\n");
            achou = 1;
        } else if(s == SIGUSR2 && strcmp(nome, "Monark") == 0){
            printf("Certo\n");
            achou = 1;
        } else if(s == SIGINT && strcmp(nome, "Con1") == 0){
            printf("Certo\n");
            achou = 1;
        } else if(s == SIGTERM && strcmp(nome, "Con2") == 0){
            printf("Certo\n");
            achou = 1;
        } else if(s == SIGALRM && strcmp(nome, "Silencio") == 0){
            printf("Certo\n");
            achou = 1;
        }
        if(achou == 0){
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    } else{
        exit(0);
    }
}

int main(void){
    signal(SIGINT, sinalrecebido);
    signal(SIGUSR1, sinalrecebido);
    signal(SIGUSR2, sinalrecebido);
    signal(SIGTERM, sinalrecebido);
    signal(SIGALRM, sinalrecebido);

    // Tem que rodar para sempre (até exit)
    while (1){
        pause();
    } 
}