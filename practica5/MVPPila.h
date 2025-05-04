#include <stdlib.h>
#include <stdio.h>
#include "Automatas.h"
typedef struct camino{
    int tamCamino;
    char* cadenaEstados;
}Camino;

Camino* crearCamino(char* cadena);
Camino* copiarCamino(Camino* camino);
void imprimirCamino(Camino* camino){
    printf("Camino: %s \n",camino->cadenaEstados);
}
Camino* crearCamino(char* cadena){
    Camino* nuevoCamino = (Camino*) malloc(sizeof(Camino));
    nuevoCamino->cadenaEstados=cadena;
    nuevoCamino->tamCamino=1;
}
Camino* copiarCamino(Camino* camino){

}
typedef struct nodoPila{
    struct nodoPila* nodosig;
    Estado* estado;
    Camino* camino;
    int nivel;
}NodoPila;

typedef struct pila{
    NodoPila* tope;
    int tamPila;
}Pila;

Pila* crearPila();
int isEmpty(Pila* pila);
void apilar(Pila* pila, NodoPila* nodo);
NodoPila* crearNodoPila(Estado* estado,Camino* camino, int nivel);
NodoPila* desapilar(Pila* pila);



Pila* crearPila(){
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->tamPila=0;
    pila->tope=NULL;
    return pila;
}
int isEmpty(Pila* pila){
    return pila->tamPila==0;
}
void apilar(Pila* pila, NodoPila* nodo){
    nodo->nodosig=pila->tope;
    pila->tope=nodo;
    pila->tamPila++;
}
NodoPila* crearNodoPila(Estado* estado,Camino* camino, int nivel){
    NodoPila* nuevoNodo = (NodoPila*) malloc(sizeof(NodoPila));
    nuevoNodo->camino=camino;
    nuevoNodo->nivel=nivel;
    nuevoNodo->estado=estado;
    nuevoNodo->nodosig=NULL;
    return nuevoNodo;
}
NodoPila* desapilar(Pila* pila){
    if(isEmpty(pila)){
        return NULL;
    }
    NodoPila* nodoAux= pila->tope;
    pila->tope=nodoAux->nodosig;
    pila->tamPila--;
    return nodoAux;
}
