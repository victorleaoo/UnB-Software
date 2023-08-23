/***********************************/
/* FGA/EngSofware/FRC  udpClient.c */
/* Prof. Fernando W Cruz           */
/***********************************/ 

/*
Dupla:
  - Victor Hugo Oliveira Leão
  - Vinícius Assumpção de Araújo
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> // memset()
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG 100

#define PDU_SIZE 50
#define KEY 500
#define PERMS 0600

struct msgform {
    long     mtype;
    int      pid;
    char     mtext[PDU_SIZE];
} ;

int main(int argc, char *argv[]) {
    int sd, rc, i;

    // Dados do Cliente Local
    struct sockaddr_in ladoCli;

    // Dados do Servidor Remoto
    struct sockaddr_in ladoServ;
    
    // Não foram passados todos os argumentos necessários (IP ou Porta faltando)
    if(argc<3)  {
        printf("uso correto: %s <ip_do_servidor> <porta_do_servidor> \n", argv[0]);
        exit(1); 
    }

    // Preenchendo as informacoes de identificacao do remoto
    ladoServ.sin_family = AF_INET;
    ladoServ.sin_addr.s_addr = inet_addr(argv[1]);
    ladoServ.sin_port = htons(atoi(argv[2]));

    // Preenchendo as informacoes de identificacao do cliente
    ladoCli.sin_family = AF_INET;
    ladoCli.sin_addr.s_addr = htonl(INADDR_ANY);  
    ladoCli.sin_port = htons(0); // usa porta livre entre (1024-5000)

    /* Criando um socket. Nesse momento a variavel
    sd contem apenas dados sobre familia e protocolo  */
    sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd<0) {
        printf("%s: nao pode abrir o socket \n",argv[0]);
        exit(1); 
    }

    /* Relacionando o socket sd com a estrutura ladoCli
    Depois do bind, sd faz referencia a protocolo local, ip local e porta local */
    rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));

    // Bind incompleto
    if(rc<0) {
        printf("%s: nao pode fazer um bind da porta\n", argv[0]);
        exit(1);
    }
    
    // Bind Completo
    printf("{UDP, IP_Cli: %s, Porta_Cli: %u, IP_R: %s, Porta_R: %s}\n", inet_ntoa(ladoCli.sin_addr), ntohs(ladoCli.sin_port), argv[1], argv[2]);


    // Prepara para receber fila de mensagens
    struct msgform msg;
    int msgid; 

    if ((msgid = msgget(KEY, PERMS | IPC_CREAT)) == -1) {
        perror("Erro na criacao da fila");
        exit(1);
    }

    printf("Fila de mensagens pronta para receber mensagens.\n");

    // Recebe as mensagens
    for(;;) {
        if (msgrcv(msgid, &msg, 54, 0, 0) == -1) {
            perror("Erro na recepcao da mensagem");
            exit(1);
        }
        
        printf("\n   -> Texto da mensagem: %s\n", msg.mtext);

        // Verifica se é o fim das mensagens
        int fim = strcmp(msg.mtext,"das mensagens"); // era pra ser "fim das mensagens"

        if(fim != 0){
            // Envia o socket
            rc = sendto(sd, msg.mtext, strlen(msg.mtext), 0,(struct sockaddr *) &ladoServ, sizeof(ladoServ));
            
            // Se não enviou nada (erro)
            if(rc<0) {
                printf("%s: nao pode enviar dados %d \n",argv[0],i-1);
                close(sd);
                exit(1);
            }
        }

        // Fim das mensagens
        if (fim == 0) break;
    }

    printf("Fila de mensagens finalizada após receber mensagens.\n");
 
    return 1;
}
