//Angel MArtin VAzquez PErez
//practica3Automatas
//5BV1

#include <stdlib.h>
#include <stdio.h>
#include "MVPstring.h"
typedef struct transicion {
    struct estado* sigEstado; // Cambiado a un único estado
    char* cadena;
} Transicion;
typedef struct transiciones{
    Transicion* transicion;
    int cantidadTransiciones;
}Transiciones;
typedef struct estado{
    char* etiqueta;
    int inicial;
    int aceptacion;
    Transiciones* transiciones;
}Estado;
typedef struct estados{
    Estado** estados;
    int cantidadEstados;
    char* nombreEstados;
}Estados;

//Transiciones 
// Transicion* crearTransicion(Estados* estados,char* cadena,int numEstados);
// char* getCadenaTransicion(Transicion* transicion);
// Estado** getEstadosTransicion(Transicion* transicion);
// int addEstadoTransicion(Transicion* transicion,Estado* estado);

// Transicion* crearTransicion(Estados* estados,char* cadena,int num){
//     Transicion *transicion = (Transicion*) malloc(sizeof(Transicion));
//     transicion->cadena=cadena;
//     transicion->sigEstados=(Estado*) malloc(sizeof(Estado
// }


//Estados
Estado* crearEstado(char* etiqueta,int inicial,int aceptacion);
int isEstadoInicial(Estado* estado);
int istEstadoAceptacion(Estado* estado);
Transicion* getTransiciones(Estado* estado);


Estados* __init_estados(){
    Estados* estados = (Estados*) malloc(sizeof(Estados));
    estados->cantidadEstados=0;
    estados->estados=NULL;
    return estados;
}
void addNombreEstados(Estados* estados,char* nombreEstados){
    estados->nombreEstados=copiarCadena(nombreEstados);
}
Estado* crearEstado(char* etiqueta,int inicial,int aceptacion){
    //printf("etiqueta %s\n",etiqueta);
    Estado* estado = (Estado*) malloc(sizeof(Estado));
    estado->etiqueta=copiarCadena(etiqueta);
    estado->inicial=inicial;
    estado->aceptacion=aceptacion;
    return estado;    
}
void addEstadoEstados(Estados* estados,Estado* estado){
    estados->cantidadEstados++;
    if (estados->estados == NULL) {
        // Si el puntero es NULL, inicializamos con malloc
        estados->estados = (Estado**)malloc(sizeof(Estado*) * estados->cantidadEstados);
    } else {
        // Si ya está inicializado, usamos realloc
        estados->estados = (Estado**)realloc(estados->estados, sizeof(Estado*) * estados->cantidadEstados);
    }

    if (estados->estados == NULL) {
        printf("----ERROR: no hay memoria disponible\n");
        return;
    }
    estados->estados[estados->cantidadEstados-1]=estado;
    printf("cantidaidadetas %d\n",estados->cantidadEstados);
}

Transicion* crearTransicion(char* cadena, Estado* estado) {
    // printf("cadena %s\n",cadena);
    Transicion* transicion = (Transicion*)malloc(sizeof(Transicion));
    if (transicion == NULL) {
        printf("----ERROR: no hay memoria disponible\n");
        return NULL;
    }
    transicion->cadena = copiarCadena(cadena);
    transicion->sigEstado = estado; // Asignar un único estado
    return transicion;
}
Transiciones* __init_transiciones() {
    Transiciones* transiciones = (Transiciones*)malloc(sizeof(Transiciones));
    transiciones->cantidadTransiciones = 0;
    transiciones->transicion = NULL;
    return transiciones;
}
// Agregar una transición a las transiciones
void addTransicionTransiciones(Transiciones* transiciones, Transicion* transicion) {
    transiciones->cantidadTransiciones++;
    if (transiciones->transicion == NULL) {
        // Si el puntero es NULL, inicializamos con malloc
        transiciones->transicion = (Transicion*)malloc(sizeof(Transicion) * transiciones->cantidadTransiciones);
    } else {
        // Si ya está inicializado, usamos realloc
        transiciones->transicion = (Transicion*)realloc(transiciones->transicion, sizeof(Transicion) * transiciones->cantidadTransiciones);
    }

    if (transiciones->transicion == NULL) {
        printf("----ERROR: no hay memoria disponible\n");
        return;
    }
    transiciones->transicion[transiciones->cantidadTransiciones - 1] = *transicion;
}

// Agregar transiciones a un estado
void addTransicionesEstado(Estado* estado, Transiciones* transiciones) {
    estado->transiciones = transiciones;
}
Transicion* getTransiciones(Estado* estado){
    return estado->transiciones->transicion;
}

int setTransicionTransiciones(Transiciones *transiciones,Transicion* transicion){
    transiciones->transicion=transicion;
    return 1;
}
int isEstadoInicial(Estado* estado){
    return estado->inicial;
}
int istEstadoAceptacion(Estado* estado){
    return estado->aceptacion;
}
void imprimirTransiciones(Transiciones* transiciones){

}
void imprimirEstados(Estados* estados){
    for(int i=0;i<estados->cantidadEstados;i++){
        printf("Estado %s\n",estados->estados[i]->etiqueta);
    }
}
// Imprimir las transiciones de un estado
void imprimirTransicionesEstado(Estado* estado) {
    if (estado->transiciones == NULL) {
        printf("El estado %s no tiene transiciones.\n", estado->etiqueta);
        return;
    }
    printf("Transiciones del estado %s:\n", estado->etiqueta);
    for (int i = 0; i < estado->transiciones->cantidadTransiciones; i++) {
        Transicion* transicion = &estado->transiciones->transicion[i];
        printf(" cadena: %s\n", transicion->cadena);
        printf("    Estado destino: %s\n", transicion->sigEstado->etiqueta);
    }
}




typedef struct estadoDeterminista{
    char * etiqueta;
    Estados* estados;
    Transiciones* transiciones;
}EstadoDeterminista;

EstadoDeterminista* crearestadoDeterminista(char* etiqueta, Estados* estados, Transiciones* transiciones){
    EstadoDeterminista* estado = (EstadoDeterminista*) malloc(sizeof(EstadoDeterminista));
    estado->etiqueta=copiarCadena(etiqueta);
    estado->estados=estados;
    estado->transiciones=transiciones;
    return estado;
}
void addTransicionesEstadoDeterminista(EstadoDeterminista* estado, Transiciones* transiciones){
    estado->transiciones=transiciones;
}
void imprimirEstadoDeterminista(EstadoDeterminista* estado){
    printf("Estado determinista %s\n",estado->etiqueta);
    for (int i=0;i<estado->estados->cantidadEstados;i++){
        printf("Estado %s\n",estado->estados->estados[i]->etiqueta);
    }
    // printf("Transiciones\n");
    // for (int i=0;i<estado->transiciones->cantidadTransiciones;i++){
    //     printf("Transicion %s\n",estado->transiciones->transicion[i].cadena);
    //     printf("Estado destino %s\n",estado->transiciones->transicion[i].sigEstado->etiqueta);
    // }

}