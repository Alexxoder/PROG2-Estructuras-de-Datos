  /* 6309536 */
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad){
  TLocalizador a_borrar;
while (cad->inicio != NULL) {
  a_borrar = cad->inicio;
  cad->inicio = cad->inicio->siguiente;
  liberarInfo(a_borrar->dato);
  delete a_borrar;
}
delete cad;
  return;
}

bool esVaciaCadena(TCadena cad) {
  return cad->inicio==NULL;
}

TLocalizador inicioCadena(TCadena cad) {
  /*
  // versión que sigue la especificación
    TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->inicio;
    }
    return res;
  */

  // versión conociendo la implementación:
  // esVaciaCadena(cad) => cad->inicio == NUL
  assert(!esVaciaCadena(cad) || cad->inicio == NULL);
  return cad->inicio;
}

TLocalizador finalCadena(TCadena cad){
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else  {
    res=cad->final;
  }
  return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad){
  return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
  TLocalizador res;
  if (esFinalCadena(loc,cad)) {
    res = NULL;
  }else  {
    res = loc->siguiente;
  }
  return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad){
  TLocalizador res;
  if (esInicioCadena(loc,cad)) {
    res = NULL;
  }else  {
    res = loc->anterior;
  }
  return res;
}

bool esFinalCadena(TLocalizador loc, TCadena cad){
  return (loc != NULL && loc == finalCadena(cad));
}

bool esInicioCadena(TLocalizador loc, TCadena cad){
  return ((loc!=NULL) && (loc == inicioCadena(cad)));
}

TCadena insertarAlFinal(TInfo i, TCadena cad){
      TLocalizador nuevo = new nodoCadena;
        nuevo->dato=i;
        nuevo->siguiente=NULL;
  if (esVaciaCadena(cad)) {
    cad->inicio=nuevo;
    nuevo->anterior=NULL;
  } else { // inserto al final
    nuevo->anterior=cad->final;
    cad->final->siguiente=nuevo;
  }
  cad->final=nuevo;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato=i;
    if (loc==inicioCadena(cad)) {
      nuevo->siguiente=cad->inicio;
      nuevo->anterior=NULL;
      cad->inicio=nuevo;
      loc->anterior=nuevo;
    } else {
        nuevo->anterior=loc->anterior;
        loc->anterior->siguiente=nuevo;
        nuevo->siguiente=loc;
        loc->anterior=nuevo;
    }
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad){
  TLocalizador a_borrar=loc;
  if (esInicioCadena(a_borrar,cad) && esFinalCadena(a_borrar,cad)) {    //si es inicio y finalCadena
      cad->inicio=NULL;
      cad->final=NULL;
  } else if (esInicioCadena(a_borrar,cad)) {
      cad->inicio=a_borrar->siguiente;
      a_borrar->siguiente->anterior=NULL;
  } else if (esFinalCadena(a_borrar,cad)) {
      cad->final=a_borrar->anterior;
      a_borrar->anterior->siguiente=NULL;
  } else if (a_borrar->siguiente!=NULL && a_borrar->anterior!=NULL) {           // si esta en el medio
      a_borrar->anterior->siguiente=a_borrar->siguiente;
      a_borrar->siguiente->anterior=a_borrar->anterior;
  }
  liberarInfo(a_borrar->dato);
  delete a_borrar;
  a_borrar = NULL;
  return cad;
}

void imprimirCadena(TCadena cad){
  TLocalizador aux=inicioCadena(cad);
  while (aux!=NULL) {
    ArregloChars txt= infoATexto(aux->dato);
    printf("%s",txt);
    delete [] txt;
    aux=aux->siguiente;
  }
  printf("\n");
return;
}

TLocalizador kesimo(nat k, TCadena cad){
  TLocalizador kloc=inicioCadena(cad);
  nat cont=1;
  if (k>0 && !esVaciaCadena(cad)) {
    while (kloc->siguiente!=NULL && (k != cont) ) {
      kloc=siguiente(kloc,cad);
      cont++;
    }
  }
    if (k==0 || k > cont) {
      kloc = NULL;
    }
  return kloc;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
  TLocalizador locec = inicioCadena(cad);
  if (!esVaciaCadena(cad) && loc!=NULL) {
    while (locec != NULL && locec != loc ) {
      locec=siguiente(locec,cad);
    }
  }
  return ((!esVaciaCadena(cad)) && (loc==locec));
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad){
  TLocalizador aux= loc1;
  if (localizadorEnCadena(loc1,cad) && localizadorEnCadena(loc2,cad)) {
    while (aux!=NULL && aux!=loc2) {
      aux=siguiente(aux,cad);
    }
  }
  return ( !esVaciaCadena(cad) && (aux==loc2));
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
    if(!esVaciaCadena(sgm))  {
          if (esVaciaCadena(cad)) {
            cad->inicio=sgm->inicio;
            cad->final=sgm->final;
            sgm->inicio=sgm->final=NULL;
          } else {
              if (esFinalCadena(loc,cad)) {
                loc->siguiente=sgm->inicio;
                sgm->inicio->anterior=loc;
                cad->final=sgm->final;
                sgm->inicio=sgm->final=NULL;
              } else{
                TLocalizador desploc=loc->siguiente;
                loc->siguiente= sgm->inicio;
                sgm->inicio->anterior = loc;
                sgm->final->siguiente= desploc;
                desploc->anterior=sgm->final;
                sgm->inicio=sgm->final=NULL;
              }
            }
  }
  liberarCadena(sgm);
return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    TCadena res = crearCadena();
    TLocalizador aux=desde;
    while (aux!=NULL && aux->anterior!=hasta) {
      insertarAlFinal(copiaInfo(aux->dato),res);
      aux=aux->siguiente;
    }
  return res;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
  //assert de cadena vacia??
  if (desde == NULL) {
    return cad;
  } else if (desde == hasta ) {
    cad=removerDeCadena(hasta,cad);
    return cad;
  } else{
    TLocalizador a_borrar=desde;
    desde=desde->siguiente;
    cad=removerDeCadena(a_borrar,cad);
    return borrarSegmento(desde,hasta,cad);
  }
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
  loc->dato=i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
  TInfo aux=loc1->dato;
  cad=cambiarEnCadena(loc2->dato,loc1,cad);
  cad=cambiarEnCadena(aux,loc2,cad);
   return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
  //utilizar el assert??
  if (loc==NULL) {
    return loc;
  } else if (clave==natInfo(loc->dato)) {
    return loc;
  } else return siguienteClave(clave,loc->siguiente,cad);
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
  if (loc==NULL) {
    return loc;
  } else if (clave==natInfo(loc->dato)) {
    return loc;
  } else return anteriorClave(clave,loc->anterior,cad);
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
  TLocalizador minloc=loc;
  TLocalizador sigloc=loc->siguiente;
  while (sigloc!=NULL) {
    if (natInfo(sigloc->dato)<natInfo(minloc->dato)) {
      minloc=sigloc;
    }
    sigloc=sigloc->siguiente;
  }
  return minloc;
}
