#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>

//globais

int entrada1, entrada2;
sem_t S1; 

//funcoes assinadas

void *QuasePrimoMaluco(void *arg);

//main

int main()
{

    int T;//casos de teste
    void *ret1, *ret2;//retornos das funcoes associadas aos numeros desejados, sao do tipo void pelo fato da funcao ser do tipo void

    scanf("%d", &T);//entrada dos casos de teste

    pthread_t t1, t2;

    if (T % 2 != 0)//trata do caso da entrada T ser impar
    {
        T--;// depois de reduzir T em 1 , ele se torna par e pode ser tratado pela funcao nas threads

        scanf("%d", &entrada1);

        sem_init(&S1, 0, 1);

        pthread_create(&t1, NULL, QuasePrimoMaluco, (void *)&entrada1);

        pthread_join(t1, &ret1);
        printf("%d\n", (int)ret1);

        sem_destroy(&S1);
    }

    while (T > 0)//loop que recebe e trata o restante dos casos
    {   
        scanf("%d", &entrada1);
        scanf("%d", &entrada2);

        T = T - 2;//reduz de dois em dois por tratar as estradas em paralelo, com o uso das threads de tid t1 e t2
        
        sem_init(&S1, 0, 2);//inicializado como 2 em referencia ao numero de de threads utilizadas
        //sem_init(&S2, 0, 10);//inicializado como 10 em referencia ao numero de divisores minimos por quase primos(se pa nem precisa)   

        pthread_create(&t1, NULL, QuasePrimoMaluco, (void *)&entrada1);
        pthread_create(&t2, NULL, QuasePrimoMaluco, (void *)&entrada2);

        pthread_join(t1, &ret1);//valor de retorno da funcao associado ao status de saida do thread fornecida, no caso a resposta desejada
        printf("%d\n", (int)ret1);//imprime o valor de retorno da funcao associado ao status de saida do thread fornecida

        pthread_join(t2, &ret2);//valor de retorno da funcao associado ao status de saida do thread fornecida, no caso a resposta desejada
        printf("%d\n", (int)ret2);//imprime o valor de retorno da funcao associado ao status de saida do thread fornecida
        
        sem_destroy(&S1);
        //sem_destroy(&S2);
    }

    return 0;
}

//funcoes

void *QuasePrimoMaluco(void *arg)
{	
    int *entrada = (int *)arg;
    int n = *entrada++;//incrementa a entrada, busca torna-la impar, afim de iniciar o processo de encontrar o maior nao primo
    int f;
    int qtdDivisores = 0;//numero do divisores inicializado com 0

    if(n <= 508079)
        return 508079;
    
    if (n % 2 == 0)//verifica se o numero eh par, caso sim incrementa mais um para torna-la impar
        n++;
	
	sem_wait(&S1);
	//sem_wait(&S2);
	
    while (qtdDivisores <= 10)
    {
        int qtdDivisores = 0,i;

        //com o n tendo sido incrementado duas vezes ou uma mas verificado como impar, entao pula-se um elemento no laço
        //Alem disso com o uso do "floor(sqrt(n))", verifica se os divisores sao menores que o chao, menor numero inteiro associado, da raiz quadrada de n, a respectiva entrada
        for (i = 3, f = floor(sqrt(n)); i < f; i += 2){
            if (n % i == 0 && i < 11)//a divisao por i eh inteira, mas o numero eh menor que 10
                break;

            else if (n % i == 0 && i > 10)//a divisao por i eh inteira, e o divisor eh maior que 10, entao eh valido
                qtdDivisores++;
        } 

        if (qtdDivisores >= 10)//encontrou o numero correto
            return (void *)n;//retorna o numero correto como saida da funcao
        
        n+=2;
        qtdDivisores = 0;
    }

    sem_post(&S1);
    //sem_post(&S2);

}