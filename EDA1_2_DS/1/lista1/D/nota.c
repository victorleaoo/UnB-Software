#include <stdio.h>

int main(){
	int area, cortado, B, T;

	scanf("%d %d", &B, &T);

	area = 160*70;

	cortado = (B+T)*70/2;

	if(cortado>area/2){
		printf("1");
	} else if(cortado<area/2){
		printf("2");
	}else{
		printf("0");
	}

	return 0;
}