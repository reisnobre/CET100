#ifndef __CONTAS_H__
#define __CONTAS_H__

struct intValores {
	int a;
	int b;
};

typedef struct intValores intValores;

int contas_soma(intValores *);
int contas_subt(intValores *);
int contas_mult(intValores *);

#endif // __CONTAS_H__
