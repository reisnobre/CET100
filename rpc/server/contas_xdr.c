/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "contas.h"

bool_t
xdr_intValoresStr (XDR *xdrs, intValoresStr *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_intValores (XDR *xdrs, intValores *objp)
{
	register int32_t *buf;

	 if (!xdr_intValoresStr (xdrs, objp))
		 return FALSE;
	return TRUE;
}
