/* 6309536 */
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_avl{
  nat dato;
  nat altura;
  nat cantidad;
  TAvl izq,der;
};

TAvl crearAvl(){
  return NULL;
}

bool estaVacioAvl(TAvl avl){
  return avl==NULL;
}

void actualizar(TAvl &avl){
  if (avl!=NULL) {
    avl->cantidad= 1+cantidadEnAvl(avl->der)+cantidadEnAvl(avl->izq);
    nat hizq= alturaDeAvl(avl->izq);
    nat hder=alturaDeAvl(avl->der);
    if (hder>=hizq) {
      avl->altura=1+hder;
    } else avl->altura=1+hizq;
  }
}

TAvl rotacionDerecha(TAvl avl){
  TAvl l=avl;
  TAvl k=avl->izq;
  l->izq=k->der;
  k->der=l;
  actualizar(l);
  actualizar(k);
  return k;
}
TAvl rotacionIzquierda(TAvl avl){
  TAvl k=avl;
  TAvl l=avl->der;
  k->der=l->izq;
  l->izq=k;
  actualizar(k);
  actualizar(l);
  return l;
}

TAvl balancear(TAvl avl){

  int factorEq= alturaDeAvl(avl->izq)-alturaDeAvl(avl->der);

  if (factorEq>1) {
    if (alturaDeAvl(avl->izq->izq)>alturaDeAvl(avl->izq->der)) {
      avl=rotacionDerecha(avl);
    } else{
      avl->izq=rotacionIzquierda(avl->izq);
      avl=rotacionDerecha(avl);
    }
  }

  if (factorEq<-1) {
    if (alturaDeAvl(avl->der->der)>alturaDeAvl(avl->der->izq)) {
        avl=rotacionIzquierda(avl);
    }else{
      avl->der=rotacionDerecha(avl->der);
      avl=rotacionIzquierda(avl);
    }
  }

  return avl;
}

TAvl insertarEnAvl(nat elem, TAvl avl){
  if (avl==NULL) {
    TAvl nuevo = new _rep_avl;
    nuevo->dato=elem;
    nuevo->altura=1;
    nuevo->cantidad=1;
    nuevo->izq=nuevo->der=NULL;
    avl=nuevo;
  } else if (avl->dato>elem) {
    avl->izq=insertarEnAvl(elem,avl->izq);
  } else if (avl->dato<elem) {
    avl->der=insertarEnAvl(elem,avl->der);
  }
  actualizar(avl);
  avl=balancear(avl);
  return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl){
   TAvl res=NULL;
  if (!estaVacioAvl(avl)) {
    if (avl->dato==elem) {
      return avl;
    }else if (avl->dato<elem ) {
      return buscarEnAvl(elem,avl->der);
    } else if (avl->dato>elem) {
        return buscarEnAvl(elem,avl->izq);
    }
  }
  return res;
}

nat raizAvl(TAvl avl){
  return avl->dato;
}

TAvl izqAvl(TAvl avl){
  return avl->izq;
}

TAvl derAvl(TAvl avl){
  return avl->der;
}

nat cantidadEnAvl(TAvl avl){
  nat cant=0;
  if (avl!=NULL) {
    cant=avl->cantidad;
  }
  return cant;
}

nat alturaDeAvl(TAvl avl){
  nat h=0;
  if (avl!=NULL) {
    h=avl->altura;
  }
  return h;
}

 void recIter(TAvl avl,TIterador &iter){
   if (avl!=NULL) {
     recIter(avl->izq,iter);
     iter=agregarAIterador(avl->dato,iter);
     recIter(avl->der,iter);
   }
 }
TIterador enOrdenAvl(TAvl avl){
  TIterador iter=crearIterador();
  recIter(avl,iter);
  return iter;
}

 TAvl insArrAvl(int inf,int sup, ArregloNats elems){
   TAvl avl=NULL;
   if (inf>sup) {
     return avl;
   }
     int medio = (inf+sup)/2;
     nat nodoarr=elems[medio];
     avl=new _rep_avl;
     avl->dato=nodoarr;
     avl->cantidad=1;
     avl->altura=1;
     avl->izq=insArrAvl(inf,medio-1,elems);
     avl->der=insArrAvl(medio+1,sup,elems);
     actualizar(avl);
   return avl;
 }

TAvl arregloAAvl(ArregloNats elems, nat n){
  return insArrAvl(0,n-1,elems);
}

TAvl recuAvl(int h, nat min){
  if (h<=0) {
    return NULL;
  } else if (h==1) {
    TAvl nuevo = new _rep_avl;
    nuevo->dato=min;
    nuevo->izq=nuevo->der=NULL;
    actualizar(nuevo);
    return nuevo;
  } else {
    TAvl nuevo= new _rep_avl;
    nuevo->izq=recuAvl(h-1,min);
    nuevo->dato=nuevo->izq->cantidad+min;
    nuevo->der=recuAvl(h-2,nuevo->dato+1);
    actualizar(nuevo);
    return nuevo;
  }
}

TAvl avlMin(nat h){
  return recuAvl(h,1);
}

void liberarAvl(TAvl avl){
  if (avl!=NULL) {
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
    avl=NULL;
  }
}
