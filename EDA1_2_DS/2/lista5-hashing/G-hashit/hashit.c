#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ht[101]; // hash table

int hash(char *key){
    int chave = 0;
    
    for(int i = 0; i < strlen(key); i++){
        chave += (key[i]*(i + 1LL));
    }

    return (19 * chave) % 101;
}

int verifica_colisao(char *palavra){
    int k = hash(palavra), prox_pos;

    for(int i = 0; i < 20; i++){
        prox_pos = (k+i*i+23LL*i) % 101;
        if(ht[prox_pos] != NULL && strcmp(ht[prox_pos], palavra) == 0){
            return 0; // adicao nao pode ser feita - colisao
        }
    }
    
    return 1;
}

void solve(){
    int n, tam = 0;
    char key[30];
    scanf("%d", &n); // <= 1000

    for(int i = 0; i < n; i ++){
        ht[i] = NULL;
    }

    for(int j = 0; j < n; j++){
        scanf("%s", key);
        char *palavra = &key[4];

        if(key[0] == 'A'){

            if(verifica_colisao(palavra)){
                int k = hash(palavra), prox_pos;

                for(int l = 0; l < 20; l++){
                    prox_pos = (k + l*l + 23LL*l) % 101;

                    if(ht[prox_pos] == NULL){ // se encontrar um vazio, adiciona
                        ht[prox_pos] = malloc(sizeof(char)*(strlen(palavra)+1));
                        strcpy(ht[prox_pos], palavra);
                        tam++;
                        break;
                    }
                }
            }

        } else if(key[0] == 'D'){
            int k = hash(palavra), prox_pos;

            for (int l = 0; l < 20; l++){
                prox_pos = (k + l*l + 23LL*l) % 101;

                if(ht[prox_pos] != NULL && strcmp(ht[prox_pos], palavra) == 0){
                    free(ht[prox_pos]);
                    ht[prox_pos] = NULL;
                    tam--;
                    break;
                }

            }
        }
    }

    printf("%d\n", tam);

    for(int i = 0; i < 101; i++){
        if(ht[i] != NULL){
            printf("%d:%s\n", i, ht[i]);
        }
    }

    return;
}

int main(void){
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        solve();
    }

    return 0;
}