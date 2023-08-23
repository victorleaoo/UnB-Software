#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct para salvar a quantidade de page faults do Maior n° de quadros
typedef struct Maior{
    int quadrosm;
    int pagefaultsm;
} Maior;

// Verifica se o número buscado está salvo na RAM
int estaRam(int q, int *ram, int num){
    for(int i = 0; i < q; i++){
        if(ram[i] == num){
            return 1;
        }
    }

    return 0;
}

int main(void){
    int n;

    scanf("%d", &n);

    int *v = malloc(sizeof(int)*n);

    // Salva o vetor de valores que será buscado na RAM
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    int q, pf, belady = 0;
    Maior Maior;

    int j = 0;

    while(scanf("%d", &q) != EOF){
        pf = 0;
        int *ram = malloc(sizeof(int)*q);

        // Preenche o vetor inicialmente com 0 para poder verificar abaixo
        memset(ram, 0, sizeof(int)*q);

        // Preenche o vetor da RAM já verificando se tem o valor está na RAM ou não
        for(int i = 0; i < q; i++){
            if(estaRam(q, ram, v[i]) == 0){
                pf++;
            }
            ram[i] = v[i];
        }

        int buscado, pos = 0;

        // Pesquisa os valores na RAM
        for(int i = q; i < n; i++){
            buscado = v[i];
            if(estaRam(q, ram, buscado) == 1){
                continue;
            } else{ // Caso não esteja na RAM, atualiza o número que está a mais tempo na RAM e aumenta um Page Fault
                ram[pos%q] = v[i];
                pos++;
                pf++;
            }
        }

        // Coloca os maiores e Maiores valores como os primeiros
        if(j == 0){
            Maior.pagefaultsm = pf;
            Maior.quadrosm = q;
            j++;
        } else if(pf > Maior.pagefaultsm && q > Maior.quadrosm){
            Maior.pagefaultsm = pf;
            Maior.quadrosm = q;
            belady = 1;
        }

        printf("%d %d\n", q, pf);

        free(ram);
    }

    // Se o maior tiver mais page fault que o Maior, belady detectado
    if(belady == 1){
        printf("Belady detectado\n");
    } else{
        printf("Sem anomalia\n");
    }

    return 0;
}