#include <stdio.h>

int count7(long long int n){
	if (n < 1) return 0;
	if (n % 10 == 7) return 1 + count7(n/10);
	else return count7(n/10);
}

int main(){
	long long int numero;

	scanf("%lld", &numero);

	printf("%d", count7(numero));

	return 0;
}