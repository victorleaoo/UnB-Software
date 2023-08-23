#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hash(A) (hashU(A))

typedef struct Item{
    char id[5]; // talvez precise aumentar
    char first[51]; // talvez precise aumentar
    char last[51]; // talvez precise aumentar
    char birthday[12];
    char phone[18];
} Item;

typedef struct ht_t{
    Item **v;
    int tam;
} ht_t;

int hashU(const char *x){
    int h = 5381;

    for (int i = 0; x[i] != '\0'; i++){
        h = (h * 33 + x[i]) % 1572869;
    }

    return h;
}

int htInit(ht_t *ht, int tam){
    ht -> v = malloc(sizeof(Item *)* tam);
    memset(ht -> v, 0, sizeof(Item *)* tam);
    return ht -> v == NULL ? 0 : 1;
}

Item htSearch(ht_t *ht, const char * id){
    if(ht -> v[hash(id)] == 0){
        return 0;
    } else{
        return ht->v[hash(id)];
    }
}

int htInsert(ht_t *ht, Item *novo){
    ht -> v[hash(*novo->id)] = novo;
    return 1;
}

int main(void){
    char cmd[6], c;

    while(scanf(" %s", cmd) != EOF){
        c = cmd[0];
        
        switch (c){
        case 'a':
            Item *ind = malloc(sizeof(Item));
            scanf(" %s %s %s %s %s", ind->id, ind->first, ind->last, ind->birthday, ind->phone);
            
            if(htSearch(ht, ind->id)){
                printf("ID %s ja cadastrado.\n", ind->id);
            } else{
                htInsert(ht, ind);
            }
            
            break;
        case 'd':
            char id[5]; // se mudar em item tem que mudar aqui
            scanf(" %s", id);

            Item Item = htSearch(ht, id);

            if(Item == NULL){
                printf("ID %s ja cadastrado.\n", Item.id);
            } else{
                htDelete(ht, Item);
            }

            break;
        case 'i':
            char id[5]; // se mudar em item tem que mudar aqui
            scanf(" %s", id);
            
            Item Item = htSearch(ht, id);
            
            if(Item == NULL){
                printf("ID %s nao existente.\n", id);
            } else{
                printf("%s %s %s %s\n", Item.first, Item.last, Item.birthday, Item.phone);
            }

            break;
        default:

            break;
        }
    }


    return 0;
}