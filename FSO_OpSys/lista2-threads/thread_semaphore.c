// NÃO FUNCIONA 100%!!

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NMAX 1000

sem_t s1;
int tickets[NMAX];
int tks_qtd;

// numero indisponivel
int get_ticket(){
    sem_wait(&s1);

    static int iniciado = 0;
    
    if(iniciado==0){
        iniciado++;
        for(int i = 0; i<NMAX; i++)
            tickets[i]=100+i;
    tks_qtd=0;
    }
    
    int ret;
    if(tks_qtd == NMAX){
        ret=-1
    } else{
        ret = tickets[tks_qtd++]; 
        tickets[tks_qtd-1]=-2; // ja foi entregue
    }

    sem_post(&s1);

    return ret;
}

void *comprador(void *arg){
    int tid= *(int*)arg;
    int comprados[100], comprados_i=6;
    // Vai comprar 5 tickets
    for(int i=0; i<5; i++){
        int x = get_ticket();
        comprados[comprados_i--]=x;
        printf("%d comprou: %d\n", tid, x);
        sleep(2); // garante que diferentes threads estao trabalhando ao msm tempo -> sem nao tem alternancia
    }
    for(int i = 0; i < 5; i++){
        return_ticket(comprados[i]);
        printf("%d comprou:: %d\n", tid, comprados[i]);
    }
}

void return_ticket(int i){
    if(tickets[t-100]==-2){
        tickets[t-100]=t; // ticket ja foi entregue, devolve ele
    }
}

int main(void){
    sem_init(&s1, 0, 1);
    pthread_t t[6];
    int x[6];
    for(int i = 1; i<6; i++){
        x[i]=i;
        pthread_create(&t[i], NULL, comprador, (void*)&x[i]);
    }

    for(int i = 1; i<6; i++)
        pthread_join(t[i], NULL);
}
