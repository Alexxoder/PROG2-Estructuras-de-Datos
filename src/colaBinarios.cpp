  /* 6309536 */
#include "../include/colaBinarios.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoBinario{
  TBinario elem;
  nodoBinario * sig;
};
typedef nodoBinario * NodoBin;
struct _rep_colaBinarios{
  NodoBin inicio;
   NodoBin final;
};

TColaBinarios crearColaBinarios(){
  TColaBinarios c = new _rep_colaBinarios;
  c->inicio = c->final = NULL;
  return c;
}

TColaBinarios encolar(TBinario b, TColaBinarios c){
  NodoBin nuevo= new nodoBinario;
  nuevo->elem=b;
  nuevo->sig=NULL;
  if (c->inicio==NULL) {
    c->inicio=nuevo;
  } else {
    c->final->sig=nuevo;
  }
  c->final=nuevo;
  return c;
}

TColaBinarios desencolar(TColaBinarios c){
  if (!estaVaciaColaBinarios(c)) {
    NodoBin a_borrar=c->inicio;
    c->inicio=c->inicio->sig;
    delete a_borrar;
    if (c->inicio==NULL) c->final=NULL;
  }
  return c;
}

void liberarColaBinarios(TColaBinarios c){
  NodoBin cola=c->inicio;
  while (cola!=NULL) {
    NodoBin a_borrar= cola;
    cola=cola->sig;
    delete a_borrar;
  }
  delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c){
  return c->inicio==NULL;
}

TBinario frente(TColaBinarios c){
  return c->inicio->elem;
}
