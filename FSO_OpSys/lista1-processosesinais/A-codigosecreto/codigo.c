#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Variável Ver se a senha for recebida
int senha = 0;

void sinalrecebido(int s){
    printf("Recebi %d\n", s);

    if(s == SIGINT){
        senha = 1;
    } else if(senha == 1 && s == SIGUSR2){
        senha++;
    } else if(senha == 2 && s == SIGTERM){
        printf("Senha acionada\n");
        senha++;
    } else if(senha == 3 && s == SIGUSR1){
        printf("Tchau\n");
        exit(0);
    } else{
        senha = 0; // Reinicia a senha caso não tenha a sequência completa.
    }
}

int main(void){
    signal(SIGINT, sinalrecebido);
    signal(SIGUSR1, sinalrecebido);
    signal(SIGUSR2, sinalrecebido);
    
    signal(SIGTERM, sinalrecebido);

    // Tem que rodar para sempre (até exit)
    while (1){
        pause();
    }
}
