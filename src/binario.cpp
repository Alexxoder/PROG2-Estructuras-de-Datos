  /* 6309536 */
#include "../include/binario.h"
#include "../include/avl.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_binario{
  TInfo dato;
  TBinario derecho, izquierdo;
};

TBinario avlABinario(TAvl a){// creo que es lo mismo que hacer una copia
  if (a!=NULL) {
    TBinario nuevo= new _rep_binario;
    TInfo elem= crearInfo(raizAvl(a),0);
    nuevo->dato=elem;
    nuevo->izquierdo=avlABinario(izqAvl(a));
    nuevo->derecho=avlABinario(derAvl(a));
    return nuevo;
  } else return NULL;
}

TBinario insArrBin(nat inf,nat sup, ArregloNats elems){//por ahora tiene sentido, capaz se puede hacer sin una aux
  TBinario t=NULL;
  if (sup-inf+1>0) {
    int medio = (inf+sup)/2;
    TInfo nodoarr= crearInfo(elems[medio],0);
    t=new _rep_binario;
    t->dato=nodoarr;
    t->izquierdo=insArrBin(inf,medio-1,elems);
    t->derecho=insArrBin(medio+1,sup,elems);
  }
  return t;
}

TBinario binarioBalanceado(ArregloNats elems, nat n){
  return insArrBin(0,n-1,elems);
}

TBinario crearBinario() {
  return NULL;
}

TBinario insertarEnBinario(TInfo i, TBinario b){
  if (b==NULL) {
  TBinario nuevo= new _rep_binario;
    nuevo->dato=i;
    nuevo->izquierdo=nuevo->derecho=NULL;
    b = nuevo;
  } else if (natInfo(i)<natInfo(b->dato)) {
    b->izquierdo = insertarEnBinario(i,b->izquierdo);
  } else if (natInfo(i)>natInfo(b->dato)) {
    b->derecho = insertarEnBinario(i,b->derecho);
  }
  return b;
}

TInfo mayor(TBinario b){
  if (b->derecho==NULL) {
    return b->dato;
  } else return mayor(b->derecho);
}

TBinario removerMayor(TBinario b){
  if (b->derecho==NULL) {
    TBinario aux=b->izquierdo;
    delete b;
    b=aux;
  } else b->derecho = removerMayor(b->derecho);
  return b;
}

TBinario removerDeBinario(nat elem, TBinario b){
  if (b!=NULL) {
    if (elem<natInfo(b->dato)) {
      b->izquierdo=removerDeBinario(elem,b->izquierdo);
    } else if (elem>natInfo(b->dato)) {
      b->derecho=removerDeBinario(elem,b->derecho);
    } else {//elem==natInfo(b->dato)
          if (b->derecho==NULL) {
            TBinario aux=b->izquierdo;
            liberarInfo(b->dato);
            delete b;
            b=aux;
          } else if (b->izquierdo==NULL) {
            TBinario aux=b->derecho;
            liberarInfo(b->dato);
            delete b;
            b=aux;
          } else {//tiene dos hijos
            TInfo maxizq=crearInfo(natInfo(mayor(b->izquierdo)),realInfo(mayor(b->izquierdo)));
            liberarInfo(b->dato);
            b->dato=maxizq;
            b->izquierdo=removerDeBinario(natInfo(maxizq),b->izquierdo);//o remover mayor
          }
    }
  }
  return b;
}

void liberarBinario(TBinario b){
    if (b!=NULL) {
      liberarBinario(b->izquierdo);
      liberarBinario(b->derecho);
      liberarInfo(b->dato);
      delete b;
      b=NULL;
    }
}

bool esVacioBinario(TBinario b){
  return b==NULL;
}

bool balanceo(nat i,nat d){
  double iz=i;
  double de=d;
  double valabs=abs(iz-de);
  return valabs<=1;
}

void recAvl(TBinario b,bool &booli,nat &altura){
  if (booli==0) {
    return;
  } else if (b==NULL) {
    altura=0;
    return;
  } else {
    nat izq=0;
    nat der=0;
    recAvl(b->izquierdo,booli,izq);
    recAvl(b->derecho,booli,der);
    if (booli!=false) {
      booli = balanceo(izq,der);//condición de balanceo
    }
      if (izq>der) {
        altura=izq+1;
      } else{
        altura=der+1;
      }
    }
}

bool esAvl(TBinario b){
  bool val=1;
  nat i;
  recAvl(b,val,i);
  return val;
}

TInfo raiz(TBinario b){
  return b->dato;
}

TBinario izquierdo(TBinario b){
  return b->izquierdo;
}

TBinario derecho(TBinario b){
  return b->derecho;
}

TBinario buscarSubarbol(nat elem, TBinario b){
  TBinario res=b;
  if (!esVacioBinario(b)) {
    while (res!=NULL && natInfo(res->dato)!=elem) {
      if (elem<natInfo(res->dato)) {
        res=res->izquierdo;
      } else res=res->derecho;
    }
  } else res=NULL;
    return res;
}

nat MasGrande(nat m,nat n){
  if (m>=n) {
    return m;
  }else return n;
}

nat alturaBinario(TBinario b){
  if (b==NULL) {
    return 0;
  } else return 1 + MasGrande(alturaBinario(b->izquierdo),alturaBinario(b->derecho));
}

nat cantidadBinario(TBinario b){
  if (b==NULL) {
    return 0;
  } else return 1 + cantidadBinario(b->derecho) + cantidadBinario(b->izquierdo);
}

 void recosuma(nat &i,TBinario b,double &suma){
   if (b!=NULL && i>0) {
    recosuma(i,b->derecho,suma);
    if (i>0 && realInfo(b->dato)>0) {
      i--;
      suma=realInfo(b->dato)+suma;
    }
    recosuma(i,b->izquierdo,suma);
   }
}

double sumaUltimosPositivos(nat i, TBinario b){
  double suma=0;
  recosuma(i,b,suma);
  return suma;
}

 TCadena recoInsert(TBinario b, TCadena cad){
   if (b!=NULL) {
    cad = recoInsert(b->izquierdo,cad);
    cad =insertarAlFinal(copiaInfo(b->dato),cad);
    cad = recoInsert(b->derecho,cad);
   }
   return cad;
 }

TCadena linealizacion(TBinario b){
  TCadena res= crearCadena();
  res=recoInsert(b, res);
  return res;
}

void CopiaConCota(double cota, TBinario b, TBinario &r){
  if (b==NULL) {
    return;
  } else {
    if (realInfo(b->dato) < cota) {
      r=insertarEnBinario(copiaInfo(b->dato),r);
    }
    CopiaConCota(cota,b->izquierdo,r);
    CopiaConCota(cota,b->derecho,r);
  }
  return;
}

TBinario menores(double cota, TBinario b){
  TBinario res=NULL;
  TBinario bizq=NULL;
  TBinario bder=NULL;
  if (realInfo(b->dato)<cota) {
    res=insertarEnBinario(copiaInfo(b->dato),res);
  }
   CopiaConCota(cota,b->izquierdo,bizq);
   CopiaConCota(cota,b->derecho,bder);
    if (res!=NULL) {
      res->izquierdo=bizq;
      res->derecho=bder;
    } else if (bder==NULL) {
      res=bizq;
    } else if (bizq!=NULL) {//acomodo el max de b izquierdo
      TInfo mayorcito=mayor(bizq);
      TBinario r= new _rep_binario;
      r->dato=copiaInfo(mayorcito);
      bizq=removerMayor(bizq);
      r->izquierdo=bizq;
      r->derecho=bder;
      res=r;
    } else {
      res=bder;
    }
 return res;
}

 nat profundidad(nat elem,TBinario b){
   nat cont=0;
   while (b!=NULL && natInfo(b->dato)!=elem) {
     if (natInfo(b->dato)<elem) {
       b=b->derecho;
     } else b=b->izquierdo;
     cont++;
   }
   return cont;
 }

 void imprimeABB (nat n,TBinario b){
   if (!esVacioBinario(b)) {
     imprimeABB(n+1,b->derecho);
     for (nat i = 0; n>0 && i < n; i++) {
       printf("-");
     }
     ArregloChars txt= infoATexto(b->dato);
     printf("%s",txt);
     delete [] txt;
     imprimeABB(n+1,b->izquierdo);
   } else printf("\n");
 }

void imprimirBinario(TBinario b){
  imprimeABB(0,b);
}
