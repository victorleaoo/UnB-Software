/*
Arquivo que recebe a fila de mensagens -> Simplex (SIMULAÇÃO)
Dupla:
  - Victor Hugo Oliveira Leão
  - Vinícius Assumpção de Araújo
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define PDU_SIZE 50
#define KEY 500
#define PERMS 0600

struct msgform {
    long     mtype;
    int      pid;
    char     mtext[PDU_SIZE];
} ;

int main(void) {
    struct msgform msg;
    int msgid;

    // Cria fila de mensagens
    if ((msgid = msgget(KEY, PERMS | IPC_CREAT)) == -1) {
        perror("Erro na criacao da fila");
        exit(1);
    }

    printf("Fila de mensagens pronta para receber mensagens.\n");

    // Recebe as mensagens
    for(;;) {
        if (msgrcv(msgid, &msg, 60, 0, 0) == -1) {
            perror("Erro na recepcao da mensagem");
            exit(1);
        }

        printf("O servidor %d recebeu uma mensagem do cliente %d\n", getpid(),msg.pid);
        
        printf("Texto da mensagem: %s\n", msg.mtext) ;
    }

    printf("Fila de mensagens finalizada após receber mensagens.\n");

    return 0;
}