#include <stdio.h>
#include <stdlib.h>

// Para melhorar tem que encontrar uma forma de aguentar mais valores e processar mais rápido (provavelmente, um encadeamento aberto ou aumentar a hash de tempos em tempos). Infelizmente estava sem tempo na época
#define ull unsigned long long
#define M 191 // 27p
#define hash(a) (a % M)

typedef struct pilha_t{
    int topo;
    ull *elem;
} pilha_t;

void inicializa_pilha(pilha_t *p){
    p->topo = -1;
    p->elem = malloc(M*sizeof(ull));
    return;
}

int pilha_vazia(pilha_t *p){
    if(p->topo == -1) return 1;
    else return 0;
}

void empilha(pilha_t *p, ull novo){
    p -> topo++;
    p->elem[p->topo] = novo;
}

ull desempilha(pilha_t *p){
    ull aux = p->elem[p->topo];
    p->topo--;
    return aux;
}

typedef struct Item{
    ull ant;
    ull end;
    ull prox;
    int visitado;
} Item;

Item ht[101];
int N;

Item buscaprox(Item *ht, Item tmp){
    return ht[hash(tmp.prox)];
}

int sanainsana(Item ptr1, Item ptr2, Item *ht){
    pilha_t p;
    inicializa_pilha(&p);

    Item aux = ptr1;

    // empilha o endereço até ptr2 ou acabar
    while(aux.end != 0 && aux.end != ptr2.end){
        empilha(&p, aux.end);
        Item prox = buscaprox(ht, aux);
        aux = prox;
    }

    if(aux.end == ptr2.end){
        empilha(&p, aux.end); // empilha o ptr2
    } else{
        return 0; // não achou ptr2
    }

    while(aux.end != 0 && aux.end != ptr1.end){
        ull teste = desempilha(&p);
        if(aux.end != teste){
            return 0; // se não tirar nada
        } 

        if(aux.visitado != 0){ // evitar loop infinito
            return 0;
        }

        aux.visitado = 1;

        Item ant = ht[hash(aux.ant)];
        aux = ant;
    }

    ull teste = desempilha(&p);
    if(aux.end != teste){
        return 0; // se não tirar nada
    }

    if(pilha_vazia(&p)){
        return 1; // se esvaziou a pilha é porque deu certo
    }

    printf("erro nao vazia\n");

    return 0;
}

int main(void){
    N = 0;

    Item ptr1, ptr2, tmp;

    // Guarda ptr1
    scanf("%llx %llx %llx", &ptr1.end, &ptr1.ant, &ptr1.prox);
    ptr1.visitado = 0;
    ht[hash(ptr1.end)] = ptr1;

    // Guarda ptr2
    scanf("%llx %llx %llx", &ptr2.end, &ptr2.ant, &ptr2.prox);
    ptr2.visitado = 0;
    ht[hash(ptr2.end)] = ptr2;

    N = 2;

    while(scanf("%llx %llx %llx", &tmp.end, &tmp.ant, &tmp.prox) != EOF){
        tmp.visitado = 0;
        ht[hash(tmp.end)] = tmp;
        N++;
    }

    int solve = sanainsana(ptr1, ptr2, ht);
    if(solve == 1){
        printf("sana\n");
        return 0;
    }

    printf("insana\n");

    return 0;
}