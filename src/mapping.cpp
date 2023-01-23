  /* 6309536 */
#include "../include/mapping.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_mapping{
  TColCadenas dato;
  nat cantidad;
  nat mod;
};

TMapping crearMap(nat M){
  TMapping nuevo= new _rep_mapping;
  nuevo->dato=crearColCadenas(M);
  nuevo->cantidad=0;
  nuevo->mod=M;
  return nuevo;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map){
  nat k=clave%map->mod;
  TInfo info=crearInfo(clave,valor);
  map->dato=insertarEnColCadenas(info,k,map->dato);
  map->cantidad++;
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map){
  map->dato=removerDeColCadenas(clave,clave%map->mod,map->dato);
  map->cantidad--;
  return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map){
  return estaEnColCadenas(clave,clave%map->mod,map->dato);
}

double valorEnMap(nat clave, TMapping map){
  return realInfo(infoEnColCadenas(clave,clave%map->mod,map->dato));
}

bool estaLlenoMap(TMapping map){
  return map->cantidad==map->mod;
}

void liberarMap(TMapping map){
  liberarColCadenas(map->dato);
  delete map;
}
