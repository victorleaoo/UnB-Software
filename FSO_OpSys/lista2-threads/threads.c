// Para rodar com sucesso: gcc -pthread -o prog prog.c
 
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1,s2;

struct param{
    sem_t *smeu;
    sem_t *svizinho;
    int *x;
};
 
void *i10sv(void *arg){
    struct param *p = (struct param *)arg; // Pega o valor do ponteiro do argumento.
    int x = *(p->x);
 
    for(int i = 0; i < 10; i++)
        printf("=== %d\n", x++);
 
    //*(int *)arg = x;
    //*(struct param *)arg->x = x;
    *(p->x) = x;
    
    // Abrir o semáforo para a próx thread rodar
    sem_post(p->svizinho);
 
    return NULL;
}
 
int main(void){
    int a = 3, b = 10;

    // Caso hajam duas threads e quer que uma execute enquanto a outra espere, pode ser usado o conceito de semáforos 
    // (1-aberto enquanto a thread vai e 0-fechado enquanto outra thread está executando)
    sem_init(&s1, 0, 0); // Vai começar fechado
    sem_init(&s2, 0, 1); // Vai rodar primeiro esse (começa com 1)

    struct param p1, p2;
    p1.x=&a;
    p1.smeu=&s1;
    p1.svizinho=&s2;
 
    p2.x=&b;
    p2.smeu=&s2;
    p2.svizinho=&s1;

    pthread_t t1, t2;
 
    pthread_create(&t1, NULL, i10sv, (void *)&p1);
    // Esperar a thread terminar e se juntar ao fluxo principal.
    pthread_join(t1, NULL); 
    // Só roda essa linha para baixo quando a thread for terminada.
    pthread_create(&t2, NULL, i10sv, (void *)&p2);
    // Esperar a thread terminar e se juntar ao fluxo principal.
    pthread_join(t2, NULL); 
    // Só roda essa linha para baixo quando a thread for terminada.

    // Caso não haja o pthread_join, não é garantia que toda a thread será executada antes da main continuar e acabar.
    // E caso a main acabe, as threads dela morrerão também com ela sem terminarem de executar.
 
}