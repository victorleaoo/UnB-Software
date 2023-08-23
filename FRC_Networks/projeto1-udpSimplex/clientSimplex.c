/*
Arquivo que lê o arquivo e implementa a fila de mensagens de escrita -> Simplex
Dupla:
  - Victor Hugo Oliveira Leão
  - Vinícius Assumpção de Araújo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY 500
#define PERMS 0600

struct msgform  {
   long mtype;
   char mtext[1024];
   int pid;
};

    // argv[0]: nome do arquivo executado
    // argv[1]: nome do arquivo a ser passado para a fila
    // argv[2]: tamanho PDU
int main(int argc, char *argv[]){
    int msqid;
    struct msgform msg;

    /*
    int PDU_SIZE = atoi(argv[2]);

    if(PDU_SIZE <= 0 || PDU_SIZE > 1024){
        printf("Valor de tamanho da PDU inválido (escolhe um maior que 0 e menor que 1024)\n");
        exit(0);
    }
    */

    // Nome do Arquivo passado por argumento
    char nomeArquivo[64];
    strcpy(nomeArquivo, argv[1]);
    
    // Cria fila de mensagens -> Erro na criação, acaba o program
    if ((msqid = msgget(KEY, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Fila de Mensagens prontas pra envio!\n");

    // Lê arquivo e envia para a fila de mensagens
    FILE *file = fopen(nomeArquivo, "r");

    // Retorna erro caso não exista o arquivo a ser lido
    if (file == NULL) {
        printf("Error");
        exit(1);
    }
    
    int n = 0;
    int c;
    int enviou = 0;

    while ((c = fgetc(file)) != EOF){
        msg.mtext[n++] = (char) c;

        /*
        if(n == PDU_SIZE){
            msg.mtype  = 1;
            msg.pid = getpid();
            int len = strlen(msg.mtext);
            if (msgsnd(msqid, &msg, len+1, 0) == -1){
                perror("msgsnd");
            }
            enviou++;
            n = 0;
            strcpy(msg.mtext, ""); // Limpa a mensagem
            printf("   -> %s\n", msg.mtext);
        }
        */
    }

    /*
    if(enviou == 0){
        msg.mtype  = 1;
        msg.pid = getpid();
        int len = strlen(msg.mtext);
        if (msgsnd(msqid, &msg, len+1, 0) == -1){
            perror("msgsnd");
        }
    }
    */

    // Envia a mensagem (arquivo lido)
    msg.mtype  = 1;
    msg.pid = getpid();
    int len = strlen(msg.mtext);
    if (msgsnd(msqid, &msg, len+1, 0) == -1){
        perror("msgsnd");
    }
    

    // Envia uma mensagem para detectar o final das mensagens
    strcpy(msg.mtext, "fim das mensagens");
    len = strlen(msg.mtext);
    if (msgsnd(msqid, &msg, len+1, 0) == -1) perror("msgsnd");

    printf("message queue: done sending messages.\n");

    return 0;
}