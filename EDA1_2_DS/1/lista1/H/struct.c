#include <stdio.h>

typedef struct tipoData{
	int dia;
	int mes;
	int ano;
} tipoData;

typedef struct tipoPessoa{
	char nome[80];
	tipoData dtNascimento;
} tipoPessoa;

struct tipoPessoa separaInfo(char nome[80], int dt_nascimento){
	struct tipoPessoa retorno;
	int i;

	for(i = 0; i < 80; i++){
		retorno.nome[i] = nome[i];
	}

	retorno.dtNascimento.dia = dt_nascimento%100;
	dt_nascimento = dt_nascimento/100;

	retorno.dtNascimento.mes = dt_nascimento%100;
	dt_nascimento = dt_nascimento/100;

	retorno.dtNascimento.ano = dt_nascimento;

	return retorno;
}

/*
int main(){
	struct tipoPessoa pessoa;

	pessoa = separaInfo("Jorge", 20020323);

	printf("Nome: %s\n", pessoa.nome);
	printf("Data de Nascimento: %d/%02d/%d", pessoa.dtNascimento.dia, pessoa.dtNascimento.mes, pessoa.dtNascimento.ano);

	return 0;
}
*/