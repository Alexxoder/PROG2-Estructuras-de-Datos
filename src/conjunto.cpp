  /* 6309536 */
#include "../include/conjunto.h"
#include "../include/usoTads.h"
#include "../include/iterador.h"
#include "../include/avl.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_conjunto{
  TAvl dato;
  nat max;
  nat min;
};

TConjunto crearConjunto(){
  TConjunto s=new _rep_conjunto;
  s->dato=NULL;
  s->max=s->min=0;
  return s;
}

TConjunto singleton(nat elem){
  TConjunto nuevo= crearConjunto();
  TAvl avl=NULL;
  avl=insertarEnAvl(elem,avl);
  nuevo->dato=avl;
  nuevo->max=elem;
  nuevo->min=elem;
  return nuevo;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
  TIterador iter1=iteradorDeConjunto(c1);
  TIterador iter2=iteradorDeConjunto(c2);
  TIterador iter3=enAlguno(iter1,iter2);
  nat cant= cantidadEnIterador(iter3);
  TConjunto res;
  if (cant>0) {
    ArregloNats arr = new nat[cant];
    iter3=reiniciarIterador(iter3);
    for (nat i = 0; i < cant ; i++) {//inicializar array
        arr[i]=actualEnIterador(iter3);
        iter3=avanzarIterador(iter3);
    }
    res= arregloAConjunto(arr,cant);
    delete [] arr;
  } else res= crearConjunto();
  //liberar
  liberarIterador(iter1);
  liberarIterador(iter2);
  liberarIterador(iter3);
  return res;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
  TIterador iter1=iteradorDeConjunto(c1);
  TIterador iter2=iteradorDeConjunto(c2);
  TIterador iter3=soloEnA(iter1,iter2);
  nat cant= cantidadEnIterador(iter3);
  TConjunto res;
  if (cant>0) {
    ArregloNats arr = new nat[cant];
    iter3=reiniciarIterador(iter3);
    for (nat i = 0; i < cant; i++) {
        arr[i]=actualEnIterador(iter3);
        iter3=avanzarIterador(iter3);
      }
    res= arregloAConjunto(arr,cant);
    delete [] arr;
  } else res=crearConjunto();
  //liberar
  liberarIterador(iter1);
  liberarIterador(iter2);
  liberarIterador(iter3);
  return res;
}

bool perteneceAConjunto(nat elem, TConjunto c){
  TAvl nodo= buscarEnAvl(elem,c->dato);
  return nodo!=NULL;
}

bool estaVacioConjunto(TConjunto c){
  return estaVacioAvl(c->dato);
}

nat cardinalidad(TConjunto c){
 nat cardinal = 0;
  if (!estaVacioConjunto(c)) {
    cardinal= cantidadEnAvl(c->dato);
  }
  return cardinal;
}

nat minimo(TConjunto c){
  return c->min;
}

nat maximo(TConjunto c){
  return c->max;
}

TConjunto arregloAConjunto(ArregloNats elems, nat n){
  TConjunto c=crearConjunto();
  c->dato=arregloAAvl(elems,n);
  c->min=elems[0];
  c->max=elems[n-1];
  return c;
}

TIterador iteradorDeConjunto(TConjunto c){
  TIterador iter;
  iter=enOrdenAvl(c->dato);
  return iter;
}

void liberarConjunto(TConjunto c){
  liberarAvl(c->dato);
  delete c;
}
