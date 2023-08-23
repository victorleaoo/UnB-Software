#include <stdio.h>
#include <stdlib.h>

float potencia(int a, int b){
	if (b == 0) return 1;
	if(b > 0){
		return a * potencia(a, b-1);
	} else {
		return ((1 / (potencia(a, -b))));
	}
	
}

int main(){

	int a, b;

	scanf("%d", &a);
	scanf("%d", &b);

	if(a == 0 && b <= 0) {
		printf("indefinido");
	}else{
		printf("%f", potencia(a,b));
	}
	
	return 0;
}