#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Contabilizar SIGALRM recebidos
int sig = 0;

void sinalrecebido(int s){
    if(s == SIGUSR1){
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    } else if (s == SIGALRM && sig != 2){
        printf("Ai que sono, quero dormir mais um pouco\n");
        sig++;
    } else{
        printf("Os incomodados que se mudem, tchau\n");
        exit(0);
    }
    
}

int main(void){
    signal(SIGUSR1, sinalrecebido);
    signal(SIGALRM, sinalrecebido);

    // Tem que rodar para sempre (até exit)
    while (1){
        pause();
    } 
}