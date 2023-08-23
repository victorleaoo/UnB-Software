#include <stdio.h>

#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")

int main(){
	int n;
	n=233;
	printf("%s", typeof(n));

	char novo[20];
	sprintf(novo, "%d", n);
	printf("%s", typeof(novo));
	printf("%s", novo);

	return 0;
}