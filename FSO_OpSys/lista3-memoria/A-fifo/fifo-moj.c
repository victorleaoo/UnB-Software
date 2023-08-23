#include <stdio.h>
#include <stdlib.h>

// Verifica se o número buscado está salvo na RAM
int estaRam(int antigo, int pos, int n, int *ram, int k){
    int i = antigo;

    while(1){
        if(ram[i] == k){
            return 1;
        }
        if(i == pos){
            break;
        }
        i = (i+1)%n;
    }
    
    return 0;
}

int main(void){
    int n;

    scanf("%d", &n);

    int *v = malloc(sizeof(int)*n);
    
    // Salva o vetor de valores que será buscado na RAM
    for (int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
    
    int q;
    int maxpf = -1, maxQuadros = 0;
    int j = 0, belady = 0;

    while(scanf("%d", &q) != EOF){
        int pf = 0;
        int pos = 0, antigo = 0;

        int *ram = malloc(sizeof(int)*q);
        
        for(int i = 0; i < n; i++){
            if((pos+1)%q != antigo){
                // Está na ram
                if(pos != antigo && estaRam(antigo, pos, q, ram, v[i])){
                    continue;
                } else{
                    ram[pos++] = v[i];

                    if(pos == q){
                        pos = 0;
                    }
                    pf++;
                }
            }else{
                // Está na ram
                if(estaRam(antigo, pos, q, ram, v[i])){
                    continue;
                } else{
                    antigo++;
                    ram[pos++] = v[i];
                    
                    if(antigo == q){
                        antigo = 0;
                    }
                    
                    if(pos == q){
                        pos = 0;
                    }
                    pf++;
                }
            }
        }

        printf("%d %d\n", q, pf);

        // Coloca os maiores valores como os primeiros
        if(j == 0){
            maxpf = pf;
            maxQuadros = q;
            j++;
        }else if(pf > maxpf && q > maxQuadros){ // Detectar belady
            maxpf = pf;
            maxQuadros = q;
            belady = 1;
        }
    }

    if(belady == 1){
        printf("Belady detectado\n");
    }else {
        printf("Sem anomalia\n");
    }

    return 0;
}