  /* 6309536 */
#include "../include/usoTads.h"
#include "../include/conjunto.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/iterador.h"
#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
  TConjunto aminusb = diferenciaDeConjuntos(c1,c2);
  TConjunto res=diferenciaDeConjuntos(c1,aminusb);
  liberarConjunto(aminusb);

  return res;
}

nat cantidadEnIterador(TIterador it){
  int cant = 0;
  TIterador iter=reiniciarIterador(it);
    while (estaDefinidaActual(iter)) {
      iter=avanzarIterador(iter);
      cant++;
    }
  return cant;
}

TIterador enAlguno(TIterador a, TIterador b){
  TIterador res=crearIterador();
  TIterador ita=reiniciarIterador(a);
  TIterador itb=reiniciarIterador(b);

    while (estaDefinidaActual(ita) || estaDefinidaActual(itb)) {

      if (!estaDefinidaActual(ita)) {
         //si a es vacio hago copia de b
           while (estaDefinidaActual(itb)) {
             res=agregarAIterador(actualEnIterador(itb),res);
             itb=avanzarIterador(itb);
           }
       }
       else if (!estaDefinidaActual(itb)) {
         //si b es vacio hago copia de a
           while (estaDefinidaActual(ita)) {
             res=agregarAIterador(actualEnIterador(ita),res);
             ita=avanzarIterador(ita);
           }
       }
       else if (actualEnIterador(ita)<actualEnIterador(itb)) {
         //si elemento b es mayor agrego a y avanzo a
           res=agregarAIterador(actualEnIterador(ita),res);
           ita=avanzarIterador(ita);
       }
       else if (actualEnIterador(ita)>actualEnIterador(itb)) {
         //si elemento a es mayor agrego b y avanzo b
           res=agregarAIterador(actualEnIterador(itb),res);
           itb=avanzarIterador(itb);
       }
       else if (actualEnIterador(ita)==actualEnIterador(itb)) {
         //si son iguales agrego cualquiera y avanzo los dos
           res=agregarAIterador(actualEnIterador(itb),res);
           ita=avanzarIterador(ita);
           itb=avanzarIterador(itb);
       }
   }
return res;
}

TIterador soloEnA(TIterador a, TIterador b){
  TIterador res = crearIterador();
  TIterador ita =reiniciarIterador(a);
  TIterador itb =reiniciarIterador(b);
  while (estaDefinidaActual(ita)) {
    //si b no esta definida inserto solo a
    if (!estaDefinidaActual(itb)) {

      while (estaDefinidaActual(ita)) {
        res=agregarAIterador(actualEnIterador(ita),res);
        ita=avanzarIterador(ita);
      }

    } else if (estaDefinidaActual(itb)) {

      if (actualEnIterador(ita)<actualEnIterador(itb)) {
        //si elemento b es mayor agrego a y avanzo a
          res=agregarAIterador(actualEnIterador(ita),res);
          ita=avanzarIterador(ita);

      } else if (actualEnIterador(ita)>actualEnIterador(itb)) {
        //si elemento a es mayor avanzo b
          itb=avanzarIterador(itb);

      } else if (actualEnIterador(ita)==actualEnIterador(itb)) {
        //si son iguales avanzo los dos
          ita=avanzarIterador(ita);
          itb=avanzarIterador(itb);
      }
    }
  }
  return res;
}

TIterador recorridaPorNiveles(TBinario b){
  TIterador iter=crearIterador();
  if (!esVacioBinario(b)) {
    TPila pila=crearPila(alturaBinario(b)+cantidadBinario(b)-1);
    TColaBinarios cola=crearColaBinarios();//crear cola
    cola=encolar(b,cola);//encolar raiz
    cola=encolar(NULL,cola);
     while(!estaVaciaColaBinarios(cola)) {
      TBinario t=frente(cola);//frente de la cola
        cola=desencolar(cola);
        if (t==NULL) { //frente null
          if (!estaVaciaColaBinarios(cola)) {//si estavaciacola no sigo encolando
            cola=encolar(t,cola);
          }
          pila=apilar(UINT_MAX,pila);
        } else{ //frente diferente de null
          pila=apilar(natInfo(raiz(t)),pila);//apilo natural
          if (!esVacioBinario(derecho(t))){//encolar hijos
            cola=encolar(derecho(t),cola);
          }
          if (!esVacioBinario(izquierdo(t))){
             cola=encolar(izquierdo(t),cola);
          }

        }

    }
    //desapilo y agrego a iter
    while (!estaVaciaPila(pila)) {
      iter=agregarAIterador(cima(pila),iter);
      pila=desapilar(pila);
    }
    liberarPila(pila);
    liberarColaBinarios(cola);
  }
  //retorno iter
  return iter;
}

void inorderInsert(TBinario b, nat l,TCadena &cad) {
  if (b!=NULL) {
    inorderInsert(izquierdo(b),l-1,cad);
    if (l==1) {
      cad= insertarAlFinal(copiaInfo(raiz(b)),cad);
    }
    inorderInsert(derecho(b),l-1,cad);
  }
}

TCadena nivelEnBinario(nat l, TBinario b){
  TCadena res=crearCadena();
  inorderInsert(b,l,res);
  return res;
}

 bool esHoja(TBinario b){
   return derecho(b)==NULL && izquierdo(b)==NULL;
 }

 bool igualesNat(TLocalizador loc,TBinario b,TCadena cad){
  bool igual = true;
  while ( (!esHoja(b) && loc!=NULL) && igual  ) {

    if ( (derecho(b)!=NULL) && natInfo(raiz(derecho(b))) == natInfo(infoCadena(loc,cad)) ) {//circuito corto
      igual=true;
      b=derecho(b);
    } else if ( (izquierdo(b) !=NULL) && natInfo(raiz(izquierdo(b))) == natInfo(infoCadena(loc,cad))) {//circuito corto
      igual=true;
      b=izquierdo(b);
    } else igual=false;
    loc=siguiente(loc,cad);
  }
  return igual && (esHoja(b) && loc==NULL);
 }

bool esCamino(TCadena c, TBinario b){
  TLocalizador loc=inicioCadena(c);
  if (esVaciaCadena(c) && esVacioBinario(b)) {
    return true;
  } else if (esVaciaCadena(c) || esVacioBinario(b)) {
    return false;
  } else if (natInfo(infoCadena(loc,c)) == natInfo(raiz(b))) {
    return igualesNat(siguiente(loc,c),b,c);
  } return false;
}

bool pertenece(nat elem, TCadena cad){
return (siguienteClave(elem,inicioCadena(cad),cad) != NULL);
}

nat longitud(TCadena cad){
  nat longi=0;
  if (!esVaciaCadena(cad)) {
    TLocalizador loc=inicioCadena(cad);
    while (loc!=NULL) {
      longi++;
      loc=siguiente(loc,cad);
    }
  }
  return longi;
}

bool estaOrdenadaPorNaturales(TCadena cad){
  bool booli;
  if (esVaciaCadena(cad)) {
    booli =esVaciaCadena(cad);
  } else if (inicioCadena(cad)==finalCadena(cad)) {
    booli =inicioCadena(cad)==finalCadena(cad);
  } else {
    TLocalizador ant= inicioCadena(cad);
    TLocalizador act= siguiente(ant,cad);
    while ((act!= NULL) && (natInfo(infoCadena(ant,cad)) <= natInfo(infoCadena(act,cad)) )) {
      ant=act;
      act=siguiente(act,cad);
    }
    booli = act == NULL;
  }
  return booli;
}

bool hayNatsRepetidos(TCadena cad){
  bool booli = 0;                                                               //no me gustan las banderas booleanas, ver si lo arreglo
  if (!esVaciaCadena(cad)) {
    TLocalizador loc =inicioCadena(cad);
    TLocalizador clave;
    while (booli == 0 && loc != finalCadena(cad) ) {
      clave=siguienteClave(natInfo(infoCadena(loc,cad)),siguiente(loc,cad),cad);
      if (clave !=NULL) {
        booli=1;
      }
      loc=siguiente(loc,cad);
    }
  }
  return booli;
}

bool sonIgualesCadena(TCadena c1, TCadena c2){
  TLocalizador loc1=inicioCadena(c1);
  TLocalizador loc2=inicioCadena(c2);
  while ((loc1!=NULL && loc2!= NULL) && sonIgualesInfo(infoCadena(loc1,c1),infoCadena(loc2,c2)) ) {
    loc1=siguiente(loc1,c1);
    loc2=siguiente(loc2,c2);
  }
  return loc1== NULL && loc2 == NULL;
}

TCadena concatenar(TCadena c1, TCadena c2){//NO ME GUSTA PARA NADA
TCadena res;
if (esVaciaCadena(c1)&&esVaciaCadena(c2)) {
  res=crearCadena();
} else if (esVaciaCadena(c2) && !esVaciaCadena(c1)) {
  res=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
} else if (!esVaciaCadena(c2) && esVaciaCadena(c1)) {
  res = copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
} else {
  TCadena cad1=copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
  TCadena cad2=copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
   res=insertarSegmentoDespues(cad2,finalCadena(cad1),cad1);
}
return res;
}

TCadena ordenar(TCadena cad){
  if (!esVaciaCadena(cad)) {
    TLocalizador actual=inicioCadena(cad);
    TLocalizador minimo=menorEnCadena(actual,cad);
    while (actual != NULL && !esFinalCadena(actual,cad)) {
      if (actual != minimo) {
        intercambiar(actual,minimo,cad);
      }
      actual=siguiente(actual,cad);
      minimo=menorEnCadena(actual,cad);
    }
  }
  return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){
  TLocalizador locorig=siguienteClave(original,inicioCadena(cad),cad);
  while (locorig != NULL) {
    TInfo nuevito = crearInfo(nuevo,realInfo(infoCadena(locorig,cad)));
    liberarInfo(infoCadena(locorig,cad));
    cad=cambiarEnCadena(nuevito,locorig,cad);
    locorig=siguienteClave(original,siguiente(locorig,cad),cad);
  }
  return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad){
  TLocalizador locmenor=siguienteClave(menor,inicioCadena(cad),cad);
  TLocalizador locmayor=anteriorClave(mayor,finalCadena(cad),cad);
  return copiarSegmento(locmenor,locmayor,cad);
}
