#include <rpc/rpc.h>
#include "contas.h"

int *somar_1_svc(intValores *v, struct svc_req *rqstp)
{
  static int res;
  res = v->a + v->b;
  return &res;
}

int *subtrair_1_svc(intValores *v, struct svc_req *rqstp)
{
  static int res;
  res = v->a - v->b;
  return &res;
}

int *multiplicar_1_svc(intValores *v, struct svc_req *rqstp)
{
  static int res;
  res = v->a * v->b;
  return &res;
}

int *dividir_1_svc(intValores *v, struct svc_req *rqstp)
{
  static int res;
  res = v->a / v->b;
  return &res;
}

