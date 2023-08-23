#include <stdio.h>
#include <stdlib.h>

int comparaArquivos(FILE *arquivo1, FILE *arquivo2){
    int c1, c2;

    while ((c1 = fgetc(arquivo1)) == (c2 = fgetc(arquivo2)) && (c1 != EOF) && (c2 != EOF)) {}
    if (c1 == c2) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char **argv){
    for(int i = 1; i < argc; i++){
        FILE *arquivo1 = fopen(argv[i], "r");
        for(int j = i+1; j < argc; j++){
            fseek(arquivo1, 0, SEEK_SET); // reiniciar o ponteiro do arquivo 1 em 0
            FILE *arquivo2 = fopen(argv[j], "r");

            int igual = comparaArquivos(arquivo1, arquivo2);

            if(igual){
                printf("%s %s iguais\n", argv[i], argv[j]);
            } else{
                printf("%s %s diferentes\n", argv[i], argv[j]);
            }

            fclose(arquivo2);
        }
        fclose(arquivo1);
    }

    return 0;
}