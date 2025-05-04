#include "MVPAlgoritmo.h"

// Nodo de la Cola (almacena punteros a EstadoDeterminista)
typedef struct nodoCola {
    EstadoDeterminista* estadoDet;
    struct nodoCola* siguiente;
} NodoCola;

// Estructura de la Cola
typedef struct cola {
    NodoCola* frente;
    NodoCola* final;
    int tamCola;
} Cola;

Cola* crearCola();
int estaVaciaCola(Cola* cola);
void encolar(Cola* cola, EstadoDeterminista* estadoDet);
EstadoDeterminista* desencolar(Cola* cola);
void liberarCola(Cola* cola); // Para limpiar memoria

Cola* crearCola() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    if (!cola) {
        perror("Error al crear la cola");
        return NULL;
    }
    cola->frente = NULL;
    cola->final = NULL;
    cola->tamCola = 0;
    return cola;
}

int estaVaciaCola(Cola* cola) {
    return (cola == NULL || cola->tamCola == 0);
}

void encolar(Cola* cola, EstadoDeterminista* estadoDet) {
    if (!cola || !estadoDet) return;

    NodoCola* nuevoNodo = (NodoCola*)malloc(sizeof(NodoCola));
    if (!nuevoNodo) {
        perror("Error al crear nodo para encolar");
        return;
    }
    nuevoNodo->estadoDet = estadoDet;
    nuevoNodo->siguiente = NULL;

    if (estaVaciaCola(cola)) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
    cola->tamCola++;
}

EstadoDeterminista* desencolar(Cola* cola) {
    if (estaVaciaCola(cola)) {
         printf("colacaoivacion\n");
        return NULL;
    }

    NodoCola* nodoTemp = cola->frente;
    EstadoDeterminista* estadoDet = nodoTemp->estadoDet;

    cola->frente = cola->frente->siguiente;
    cola->tamCola--;

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoTemp); 
    return estadoDet;
}

// Libera los nodos de la cola, pero NO los EstadoDeterminista apuntados
void liberarCola(Cola* cola) {
    if (!cola) return;
    while (!estaVaciaCola(cola)) {
        desencolar(cola); // Desencolar libera cada nodo
    }
    free(cola); // Liberar la estructura de la cola
}

