#include <stdio.h>

int count7(long long int n){
	if (n < 1) return 0;
	if (n % 10 == 7) return 1 + count7(n/10);
	else return count7(n/10);
}

int main(){
    long long int n;

	scanf("%lld", &n);

	printf("%d", count7(n));

    return 0;
}