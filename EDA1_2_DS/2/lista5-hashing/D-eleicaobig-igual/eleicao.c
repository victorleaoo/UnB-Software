#include <stdio.h>
#include <stdlib.h>

#define key(A) (A.politico)
#define less(A, B) (A.voto == B.voto ? key(A) > key(B) : A.voto > B.voto) // comparar se a quantidade de voto for igual, pelo politico em si
#define exch(A, B)  {pol t = B; B = A; A = t;}
#define cmpexch(A, B) {if (less(B, A)) exch(A, B)}

typedef struct pol{
    int politico;
    int voto;
} pol;
pol pres[91], sen[901], fed[9001], est[90001];
int pn = 0, sn = 0, fedn = 0, estn = 0;

int separa(pol *v, int l, int r)
{
    pol aux = v[r];
    int j = l;
    for (int k = l; k < r; k++){
        if (less(v[k], aux)){
            exch(v[k], v[j]);
            j++;
        }
    }
    exch(v[j], v[r]);
    
    return j;
}

void quicksort(pol *v, int l, int r){
    
    if (l >= r) return;

    cmpexch(v[(l + r) / 2], v[r]);
    cmpexch(v[l], v[(l + r) / 2]);
    cmpexch(v[r], v[(l + r) / 2]);

    int j = separa(v, l, r);
    quicksort(v, l, j - 1);
    quicksort(v, j + 1, r);
}

int main()
{
    long long s, f, e;
    scanf("%lld %lld %lld", &s, &f, &e);

    int valido = 0, invalidoo = 0, presporc = 0, votoLido, l;
    while (scanf("%d%n", &votoLido, &l) != EOF){ 
        if (votoLido < 0){
            invalidoo++;
            continue;
        }

        switch (l){ // Quantidade de caracteres lidos -> Já salva nos vetores o voto do político como index
        case 3: // 3 = Presidente
            pres[votoLido - 10].politico = votoLido;
            pres[votoLido - 10].voto++;
            presporc++;
            break;
        case 4: // 4 = Senador
            sen[votoLido - 100].politico = votoLido;
            sen[votoLido - 100].voto++;
            break;
        case 5: // 5 = Deputado Federal
            fed[votoLido - 1000].politico = votoLido;
            fed[votoLido - 1000].voto++;
            break;
        default:
            est[votoLido - 10000].politico = votoLido;
            est[votoLido - 10000].voto++;
        }
        valido++;
    }

    // "Arruma" os vetores para os índices corretos
    for (int i = 0; i < 91; i++){
        if (pres[i].voto){
            pres[pn++] = pres[i];
        }   
    }
        
    for (int i = 0; i < 901; i++){
        if (sen[i].voto){
            sen[sn++] = sen[i];
        }     
    }
        
    for (int i = 0; i < 9001; i++){
        if (fed[i].voto){
            fed[fedn++] = fed[i];
        }  
    }
        
    for (int i = 0; i < 90001; i++){
        if (est[i].voto){
            est[estn++] = est[i];
        }
    }

    printf("%d %d\n", valido, invalidoo);

    quicksort(pres, 0, pn - 1);
    quicksort(sen, 0, sn - 1);
    quicksort(fed, 0, fedn - 1);
    quicksort(est, 0, estn - 1);

    if ((double)pres[0].voto/presporc >= 0.51){
        printf("%d\n", pres[0].politico);
    } else{
        printf("Segundo turno\n");
    }   

    for (int i = 0; i < s; i++){
        printf("%d%c", sen[i].politico, " \n"[i == s - 1]);
    }
        
    for (int i = 0; i < f; i++){
        printf("%d%c", fed[i].politico, " \n"[i == f - 1]);
    }
        
    for (int i = 0; i < e; i++){
        printf("%d%c", est[i].politico, " \n"[i == e - 1]);
    }

    return 0;
}