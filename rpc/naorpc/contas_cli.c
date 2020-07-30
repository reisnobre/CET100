#include <stdio.h>
#include <math.h>
#include "contas.h"

int main(int argc, char **argv) {
	intValores par;
	int result;

	par.a = atoi(argv[1]);
	par.b = atoi(argv[2]);

	result = contas_soma(&par);
	printf("\nA soma entre os valores resultou em: %d", result);

	result = contas_mult(&par);
	printf("\nO produto entre os valores resultou em: %d", result);

	printf("\n");
	return 0;
}


