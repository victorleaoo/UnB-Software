#include <stdio.h>

int main() {
	int soma, n;

	soma = 0;

	while(scanf("%d", &n) != EOF){
		soma += 1;
	}

	printf("%d", soma);

	return 0;
}