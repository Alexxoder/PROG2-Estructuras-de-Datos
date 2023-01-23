  /* 6309536 */
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct _rep_pila {
  int * arr;
  int tope;
  int cota;
};

TPila crearPila(nat tamanio){
  TPila p = new _rep_pila;
  p->arr= new int[tamanio];
  p->tope=-1;
  p->cota=tamanio-1;
  return p;
}

TPila apilar(nat num, TPila p){
  if (!estaLlenaPila(p)) {
    p->tope=p->tope+1;
    p->arr[p->tope]=num;
  }
  return p;
}

TPila desapilar(TPila p){
  if (!estaVaciaPila(p)) {
    p->tope--;
  }
  return p;
}

void liberarPila(TPila p){
  delete [] p->arr;
  delete p;
}

bool estaVaciaPila(TPila p){
  return p->tope==-1;
}

bool estaLlenaPila(TPila p){
  return p->tope==p->cota;
}

nat cima(TPila p){
  return p->arr[p->tope];
}
