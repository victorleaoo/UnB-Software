// Lista Encadeada: armazena números aleatórios (rand)
// 1 Produtor (criando e colocando na lista) -> Quanto tempo demora para gerar um número?
// 10 Consumidores -> Uma função para cada fazendo requisições
// Quantas requisições por segundo são feitas?
// É possível melhorar a vazão do sistema?

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;

typedef struct no{
    int item;
    struct no *prox;
} no;

no* inicializa_lista(){
    no *p;
    p -> item = 0;
    p -> prox = NULL;
    return p;
}


no* insere(no* l, int elemento){
    no* novo = malloc(sizeof(no));
    novo -> item = elemento;
    novo -> prox = l;
    return novo;
}

/*
void imprime_lista (no* l){
    no* p;

    for(p = l; p != NULL; p = p->prox){
        printf("Elemento: %d\n", p->item);
    }

    return;
}
*/

// Contar quantos insere por segundo -> Quanto tempo demora para um melhor?
void *produtor(no *l){
    sem_wait(&s1);

    int num_rand = rand();

    l = insere(l, num_rand);

    sem_post(&s1);

    return;
}

// Remove da lista
void *consumidor(no *lista){

}


int main(void){
    no *lista = inicializa_lista();

    pthread_t t1, t2[10];

    sem_init(&s1, 0, 1);

    pthread_create(&t1, NULL, produtor, lista); // Gera um numero

    for(int i = 0; i < 10; i++){
        pthread_create(&t2[i], NULL, consumidor, lista); // Faz 10 threads de remoção
    }
    
    pthread_join(t1, NULL);
    
    for (int i = 0; i < 10; i++){
        pthread_join(t2[i], NULL);
    }

    //imprime_lista(lista);

    return 0;
}
