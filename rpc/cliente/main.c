#include <stdio.h>
#include <rpc/rpc.h>
#include "contas.h"

int main(int argc, char **argv) {
  int *res;
  CLIENT *cl;
  intValores val;
  if(argc != 4) printf("Use: prog <int> <int> <host>\n");
  else {
    val.a = atoi(argv[1]);
    val.b = atoi(argv[2]);
    cl = clnt_create(argv[3],CONTASPROG, CONTASVERS, "udp");
    res = somar_1(&val,cl);
    printf("A soma dos valores é: %d\n",*res);
    res = subtrair_1(&val,cl);
    printf("A subtração entre oss valores é: %d\n",*res);
    res = multiplicar_1(&val,cl);
    printf("O produto dos valores é: %d\n",*res);
    if(val.b != 0) {
      res = dividir_1(&val,cl);
      printf("A divisão entre os valores é: %d\n",*res);
    } else printf("Impossível dividir\n");
  }
  return 0;
}
