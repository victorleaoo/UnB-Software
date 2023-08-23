#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verificaOrdem(char alunos[101][21], int aux[101], int max) {
    int i = 0, j;
    while(aux[i] < aux[max]) {
        for(j = 0; alunos[aux[i]][j] != '\0'; j ++) {
            if(alunos[aux[i + 1]][j] == '\0') {
                strcpy(alunos[aux[i + 1]], alunos[aux[i]]);
                break;
            }
            else if(alunos[aux[i]][j] > alunos[aux[i + 1]][j]) {
                strcpy(alunos[aux[i + 1]], alunos[aux[i]]);
                break;
            }
            else if(alunos[aux[i]][j] == alunos[aux[i + 1]][j]) {
                continue;
            }
            else if(alunos[aux[i]][j] < alunos[aux[i + 1]][j]) {
                break;
            }
        }
        i ++;
    }

    printf("%s\n", alunos[aux[max]]);
}

void reprov(int n, char alunos[101][21], int numProblemas[101]) {
    int menor = numProblemas[0], j = 0, i, aux[101];
    
    for(i = 1; i < n; i ++){
        if(numProblemas[i] < menor){
            menor = numProblemas[i];
        } 
    }

    // idx repetidos
    for(i = 0; i < n; i ++){
        if(menor == numProblemas[i]) {
            aux[j] = i;
            j++;
        }
    }

    if(j == 1){
        printf("%s\n", alunos[aux[0]]);
    }    
    else{
        verificaOrdem(alunos, aux, j - 1);
    }
}

int main()
{
    int n, i = 0, j = 1;
    int numProblemas[101];
    char alunos[101][21];

    while(scanf("%d", &n) != EOF) {
        for (i = 0; i < n; i ++)
            if(scanf("%s", alunos[i]) == EOF || scanf("%d",&numProblemas[i]) == EOF)
                return 0;
        printf("Instancia %d\n", j);
        reprov(n, alunos, numProblemas);
        printf("\n");
        j++;
    }

    return 0;
}