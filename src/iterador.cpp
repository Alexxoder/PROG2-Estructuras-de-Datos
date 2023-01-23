  /* 6309536 */
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoLista *TLista;
struct nodoLista{
  nat dato;
  TLista siguiente;
};

struct _rep_iterador{
  TLista inicio,final,actual;
  bool reinicio;
};

TIterador crearIterador(){
  TIterador iter= new _rep_iterador;
  iter->inicio=iter->final=iter->actual=NULL;
  iter->reinicio=false;
  return iter;
}

TIterador agregarAIterador(nat elem, TIterador iter){

if (iter->reinicio==false) {
  TLista nuevo = new nodoLista;
  nuevo->dato = elem;
  nuevo->siguiente=NULL;
  if (iter->inicio==NULL) {
    iter->inicio=nuevo;
    iter->final=nuevo;
  } else {
    iter->final->siguiente=nuevo;
    iter->final=nuevo;
  }
}
  return iter;
}

TIterador reiniciarIterador(TIterador iter){
  if (iter->inicio!=NULL) {
    iter->actual=iter->inicio;
  }
  iter->reinicio=true;
  return iter;
}

TIterador avanzarIterador(TIterador iter){
  if (estaDefinidaActual(iter)) {
    iter->actual=iter->actual->siguiente;
  }
  return iter;
}

nat actualEnIterador(TIterador iter){
  return iter->actual->dato;
}

bool estaDefinidaActual(TIterador iter){
  return iter->actual!=NULL;
}

void liberarIterador(TIterador iter){
  TLista p=iter->inicio;
  TLista q;
  while (p!=NULL) {
    q=p;
    p=p->siguiente;
    delete q;
  }
  delete iter;
}
