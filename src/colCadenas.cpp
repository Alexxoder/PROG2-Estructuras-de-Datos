  /* 6309536 */
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_colCadenas{
  TCadena *arr;
  nat cota;
};

TColCadenas crearColCadenas(nat M){
  TColCadenas res= new _rep_colCadenas;
  res->cota=M-1;
  res->arr= new TCadena[res->cota+1];
  for (nat i = 0; i < res->cota+1; i++) {
    res->arr[i]=crearCadena();
  }
  return res;
}

TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col){
  if (pos<=col->cota) {
    TCadena cad=col->arr[pos];
     if (esVaciaCadena(cad)) {
       cad=insertarAlFinal(info,cad);
     } else cad=insertarAntes(info,inicioCadena(cad),cad);
  }
   return col;
}

 // este capaz con siguiente clave
bool estaEnColCadenas(nat dato, nat pos, TColCadenas col){
  TLocalizador loc=NULL;
  if (pos<=col->cota) {
    TCadena cad=col->arr[pos];
    loc=siguienteClave(dato,inicioCadena(cad),cad);
  }
  return loc != NULL;
}


TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col){//la Precondición, no controlo p<=cota
  TCadena cad=col->arr[pos];
  TLocalizador loc= siguienteClave(dato,inicioCadena(cad),cad);
  return infoCadena(loc,cad);
}

 // desde pos hasta cero
TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col){//precon, no controlo
  TCadena cad=col->arr[pos];
  cad=removerDeCadena(siguienteClave(dato,inicioCadena(cad),cad),cad);
  return col;
}

void liberarColCadenas(TColCadenas col){
  for (nat i = 0; i <= col->cota; i++) {
    TCadena cad=col->arr[i];
      liberarCadena(cad);
  }
  delete [] col->arr;
  delete col;
}
