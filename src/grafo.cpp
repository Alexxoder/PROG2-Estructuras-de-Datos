/* 6309536 */
#include "../include/grafo.h"
#include "../include/colCadenas.h"
#include "../include/iterador.h"
#include "../include/avl.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_grafo{
  nat orden;//N
  TColCadenas nodos;
  TAvl *vecinos;
  int aristas;//M
};

TGrafo crearGrafo(nat N, nat M){
  TGrafo nuevo= new _rep_grafo;
  nuevo->orden=N;//??
  nuevo->aristas=M;
  nuevo->nodos=crearColCadenas(N);
  nuevo->vecinos=new TAvl[N];
  for (nat i = 0; i < N; i++) {
    nuevo->vecinos[i]=crearAvl();
  }
  return nuevo;
}

nat cantidadVertices(TGrafo g){
  return g->orden;
}

bool hayMParejas(TGrafo g){
  return g->aristas==0;
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
  nat k1=(v1-1)%g->orden;
  nat k2=(v2-1)%g->orden;
  TInfo info1= crearInfo(v2,d);
  TInfo info2= crearInfo(v1,d);
  g->nodos=insertarEnColCadenas(info1,k1,g->nodos);
  g->vecinos[k1]=insertarEnAvl(v2,g->vecinos[k1]);
  g->nodos=insertarEnColCadenas(info2,k2,g->nodos);
  g->vecinos[k2]=insertarEnAvl(v1,g->vecinos[k2]);
  g->aristas--;
  return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g){
  return estaEnColCadenas(v1,(v2-1)%g->orden,g->nodos);
}

double distancia(nat v1, nat v2, TGrafo g){
  return realInfo(infoEnColCadenas(v1,(v2-1)%g->orden,g->nodos));
}

TIterador vecinos(nat v, TGrafo g){
  TIterador iter = NULL;
  iter= enOrdenAvl(g->vecinos[(v-1)%g->orden]);
  return iter;
}

void liberarGrafo(TGrafo g){
  liberarColCadenas(g->nodos);
  for (nat i = 0; i < g->orden; i++) {
    liberarAvl(g->vecinos[i]);
  }
  delete [] g->vecinos;
  delete g;
}
