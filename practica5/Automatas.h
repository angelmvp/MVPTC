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



// EstadoDeterminista* crearestadoDeterminista(char* etiqueta, Estados* estados); // Modificado
// TransicionesDeterministas* __init_transicionesDeterministas();
// TransicionDeterminista* crearTransicionDeterminista(char* cadena, EstadoDeterminista* destino);
// void addTransicionDeterministaTransiciones(TransicionesDeterministas* lista, TransicionDeterminista* nueva);
// void imprimirEstadoDeterminista(EstadoDeterminista* estado); 

typedef struct estadoDeterminista{
    char * etiqueta;
    Estados* estados;
    struct transicionesDeterministas* transiciones; 
}EstadoDeterminista;

// Transición para el DFA
typedef struct transicionDeterminista {
    EstadoDeterminista* sigEstado;
    char* cadena;                  
} TransicionDeterminista;

typedef struct transicionesDeterministas {
    TransicionDeterminista* transicion; 
    int cantidadTransiciones;
} TransicionesDeterministas;

TransicionesDeterministas* __init_transicionesDeterministas() {
    TransicionesDeterministas* trans = (TransicionesDeterministas*)malloc(sizeof(TransicionesDeterministas));
    if (!trans) { /* Manejar error */ return NULL; }
    trans->cantidadTransiciones = 0;
    trans->transicion = NULL; 
    return trans;
}

EstadoDeterminista* crearestadoDeterminista(char* etiqueta, Estados* estados){ // Quitar Transiciones* de los args
    EstadoDeterminista* estado = (EstadoDeterminista*) malloc(sizeof(EstadoDeterminista));
    if (!estado) { /* Manejar error */ return NULL; }
    estado->etiqueta = copiarCadena(etiqueta); 
    estado->estados = estados;
    estado->transiciones = __init_transicionesDeterministas(); 
    return estado;
}




TransicionDeterminista* crearTransicionDeterminista(char* cadena, EstadoDeterminista* destino) {
    TransicionDeterminista* trans = (TransicionDeterminista*)malloc(sizeof(TransicionDeterminista));
    if (!trans) {
         return NULL; 
    }
    trans->cadena = copiarCadena(cadena); 
    trans->sigEstado = destino; 
    return trans;
}

void addTransicionDeterministaTransiciones(TransicionesDeterministas* lista, TransicionDeterminista* nueva) {
    if (!lista || !nueva) return;
    lista->cantidadTransiciones++;
    lista->transicion = (TransicionDeterminista*)realloc(lista->transicion, sizeof(TransicionDeterminista) * lista->cantidadTransiciones);
    if (!lista->transicion) {
        perror("Error al realocar memoria para transiciones deterministas");
        lista->cantidadTransiciones--; 
        return;
    }
    // Copiar la estructura (no solo el puntero)
    lista->transicion[lista->cantidadTransiciones - 1] = *nueva;
}

void imprimirEstadoDeterminista(EstadoDeterminista* estado){
    if (!estado) {
        printf("Estado determinista NULL\n");
        return;
    }
    printf("Estado %s ", estado->etiqueta);
    // Imprimir el conjunto de estados NFA que representa
    if (estado->estados) {
        printf("= {");
        for (int i = 0; i < estado->estados->cantidadEstados; i++) {
            printf("%s%s", estado->estados->estados[i]->etiqueta, (i == estado->estados->cantidadEstados - 1) ? "" : ",");
        }
        printf("}\n");
    } else {
        printf("= {NULL}\n");
    }

    // Imprimir transiciones DFA
    if (estado->transiciones && estado->transiciones->cantidadTransiciones > 0) {
        printf("  Transiciones \n");
        for (int i = 0; i < estado->transiciones->cantidadTransiciones; i++) {
            TransicionDeterminista* t = &estado->transiciones->transicion[i];
            printf(" %s-> %s\n", t->cadena, (t->sigEstado ? t->sigEstado->etiqueta : "NULL"));
        }
    } else {
        printf("  (Sin transiciones DFA definidas)\n");
    }
}
