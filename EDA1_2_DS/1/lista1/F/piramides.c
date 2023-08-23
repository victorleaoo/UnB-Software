#include <stdio.h>

int main(){
	int i, j, n, unico;

	scanf("%d", &n);

	for(i=1;i<=n;i++){
		for(j=1; j<=i; j++){
			if(i<10){
				printf("0%d ",i);
			}else{
				printf("%d ", i);
			}
		}
		printf("\n");
	}

	printf("\n");

	for(i=1;i<=n;i++){
		unico=0;
		for(j=1;j<=i;j++){
			unico += 1;
			if(unico<10){
				printf("0%d ",unico);
			}else{
				printf("%d ",unico);
			}
		}
		printf("\n");
	}

	return 0;
}