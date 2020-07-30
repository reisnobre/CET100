/* Interface para meu middleware, protótipo das funções CONTAS */
/* nome: contas.x */

struct intValoresStr {
  int a;
  int b;
};

typedef struct intValoresStr intValores;

program CONTASPROG {
  version CONTASVERS {
    int somar(intValores) = 1;
    int subtrair(intValores) = 2;
    int multiplicar(intValores) = 3;
    int dividir(intValores) = 4;
  } = 1;
} = 0x289ABCDE;
