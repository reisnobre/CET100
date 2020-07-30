#include "contas.h"

int contas_soma(intValores *par) {
	int result;

	result = par->a + par->b;
	return result;
}

int contas_subt(intValores *par) {
	int result;

	result = par->a - par->b;
	return result;
}

int contas_mult(intValores *par) {
	int result;

	result = par->a * par->b;
	return result;
}

