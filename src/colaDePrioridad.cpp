/* 6309536 */
#include "../include/colaDePrioridad.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoArray {
  nat elem;
  double prioridad;
};

struct _rep_colaDePrioridad{
  nat rango;//N
  nat tope;
  nodoArray * array;
  int * indices;
};


TColaDePrioridad crearCP(nat N){
  TColaDePrioridad nuevo = new _rep_colaDePrioridad;
  nuevo->rango=N;
  nuevo->tope=0;
  nuevo->array= new nodoArray[N+1];
  nuevo->indices= new int[N+1];
  for (nat i = 0; i <= nuevo->rango; i++) {//inicializar
    nuevo->array[i].elem=0;
    nuevo->array[i].prioridad=0;
    nuevo->indices[i]=0;
  }
  return nuevo;
}

nat rangoCP(TColaDePrioridad cp){
  return cp->rango;
}

void filtradoAscend(nodoArray * array,int *ind, nat pos){
   nat h=pos;
   while ((h>1) && (array[h].prioridad<array[h/2].prioridad)) {
     //hago el swap del arreglo heap
     nodoArray aux;
     aux.elem=array[h].elem;
     aux.prioridad=array[h].prioridad;
     array[h]=array[h/2];
     //array[h].elem=array[h/2].elem;
     //array[h].prioridad=array[h/2].prioridad;
     array[h/2]=aux;
     //actualizo arreglo de indices;
     ind[array[h/2].elem]=h/2;
     ind[array[h].elem]=h;
     //avanzo h
     h=h/2;
   }
 }

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
  cp->tope++;
  cp->array[cp->tope].elem=elem;
  cp->array[cp->tope].prioridad=valor;
  cp->indices[elem]=cp->tope;
  filtradoAscend(cp->array,cp->indices,cp->tope);
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp){
  return cp->tope==0;
}

nat prioritario(TColaDePrioridad cp){
  return cp->array[1].elem;
}

 void filtradoDescend(nodoArray * arr,int *ind,nat pos, nat n){
   nodoArray aux;
   bool booli=1;
   while (2*pos<=n && booli) {//o hacer una bandera booleana
    nat h=2*pos;
     if ((h+1<=n) &&(arr[h+1].prioridad <arr[h].prioridad) ) {
       h=h+1;
     }
     if (arr[h].prioridad<arr[pos].prioridad) {
       //swap del heap
       aux=arr[pos];
       arr[pos]=arr[h];
       arr[h]=aux;
       //actualizacion del arreglo de indices
       ind[arr[pos].elem]=pos;
       ind[arr[h].elem]=h;
     } else{ // corto el while con la bandera
       booli=0;
     }
     //avanzo pos
     pos=h;
   }
 }

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  nodoArray aux=cp->array[cp->tope];
  cp->tope--;
  //borrar el indice de elem;
  cp->indices[cp->array[1].elem]=0;
  cp->array[1]=aux;
  filtradoDescend(cp->array,cp->indices,1,cp->tope);
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
   return cp->indices[elem]>0;
}

double prioridad(nat elem, TColaDePrioridad cp){
  return cp->array[cp->indices[elem]].prioridad;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
  //actualizar en orden 1 y luego acomodar en orden logN usando filtrado ascendente o descendente
  double antes=cp->array[cp->indices[elem]].prioridad;
  cp->array[cp->indices[elem]].prioridad=valor;

  if (antes>valor) {// si lo decremento veo si aplico el filtrado ascendente

    filtradoAscend(cp->array,cp->indices,cp->indices[elem]);

  } else if (antes < valor) {//si lo aumente aplico el filtrado ascendente

    filtradoDescend(cp->array,cp->indices,cp->indices[elem],cp->tope);
  }
  return cp;
}

void liberarCP(TColaDePrioridad cp){
  delete [] cp->array;
  delete [] cp->indices;
  delete cp;
}
