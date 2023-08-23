#include <stdio.h>

int main(){
	int i, somaPar, somaImpar, n;

	somaPar = 0;
	somaImpar = 0;

	while(1){
		scanf("%d", &n);
		if(n != 0){
			if(n % 2 == 0){
				somaPar += n;
			}else{
				somaImpar +=n;
			}
		}else{
			printf("%d %d", somaPar, somaImpar);
			break;
		}
	}
	return 0;
}