//Angel Martin Vazquez Perez
//practica3Automatas
//5BV1
#include <stdio.h>
#include <stdlib.h>
#include "Automatas.h"
#include <string.h>
//#include "MVPCola.h"

Estados* crearEstadosDeLinea(char* linea);
char* crearAlfabeto(char* linea);
void asignarEstadoInicial(Estado* estado);
void asignarEstadoAceptacion(Estado* estado);
void asignarTransiciones(Estados* estados,char* linea);
int main() {
    puts("Bienvenido al programa número 3 de autómatas\n");

    Estados* estados;
    FILE* file = fopen("automata.txt", "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int indice = 0;
    char linea[250];

    while (fgets(linea, sizeof(linea), file) != NULL) {
        // Eliminar el salto de línea al final de cada línea leída
        if (linea[cadenaTam(linea) - 1] == '\n') {
            linea[cadenaTam(linea) - 1] = '\0';
        }

        if (indice == 0) {
            estados = crearEstadosDeLinea(linea);
        } else if (indice == 1) {
            char* alfabeto = crearAlfabeto(linea);
            printf("Alfabeto: %s\n", alfabeto);
        } else if (indice == 2) {
            int estadoInicial = charToInt(linea);
            asignarEstadoInicial(estados->estados[estadoInicial]);
        } else if (indice == 3) {
            int i = 0;
            while (linea[i] != '\0') {
                if (linea[i] != ',') {
                    int estadoAceptacion = charToInt(linea+i);
                    printf("Estado de aceptación: %d\n", estadoAceptacion);
                    asignarEstadoAceptacion(estados->estados[estadoAceptacion]);
                }
                i++;
            }
        } else {
            asignarTransiciones(estados,linea);
        }
        indice++;
    }
    for(int i=0;i<estados->cantidadEstados;i++){
        imprimirTransicionesEstado(estados->estados[i]);
    }
    fclose(file);
    return 0;
}

Estados* crearEstadosDeLinea(char* linea) {
    Estados* estados = __init_estados();
    char simbolo[2]; // Arreglo para almacenar un carácter y el terminador '\0'
    int i= 0;
    while (linea[i]) {
        if (linea[i] != ',') {
            simbolo[0] = linea[i]; // Copiar el carácter actual
            simbolo[1] = '\0';    // Agregar el terminador de cadena
            Estado* nuevoEstado = crearEstado(simbolo, 0, 0);
            addEstadoEstados(estados, nuevoEstado);
            nuevoEstado->transiciones = __init_transiciones();
        }
        i++;
    }
    return estados;
}

char* crearAlfabeto(char* linea) {
    char* alfabeto = (char*)malloc(strlen(linea) + 1);
    if (alfabeto == NULL) {
        puts("----ERROR: No hay memoria disponible");
        return NULL;
    }
    strcpy(alfabeto, linea);
    return alfabeto;
}

void asignarEstadoInicial(Estado* estado) {
    estado->inicial = 1;
}

void asignarEstadoAceptacion(Estado* estado) {
    estado->aceptacion = 1;
}
void asignarTransiciones(Estados* estados, char* linea) {
    printf("Transiciones: %s\n", linea);
    int estado;
    char simbolo[2]; // Arreglo para almacenar un carácter y el terminador '\0'
    int estadoDestino;
    int i = 0;

    while (linea[i]) {
        if (i == 0) {
            estado = charToInt(linea + i); // Convertir el estado origen
        } else if (i == 2) {
            simbolo[0] = linea[i]; // Copiar el símbolo actual
            simbolo[1] = '\0';    // Agregar el terminador de cadena
        } else if (i == 4) {
            estadoDestino = charToInt(linea + i); // Convertir el estado destino
        }
        i += 2;
    }

    // printf("Estado: %d, Simbolo: %s, Estado destino: %d\n", estado, simbolo, estadoDestino);


    // Crear la transición y agregarla al estado origen
    Transicion* transicion = crearTransicion(simbolo, estados->estados[estadoDestino]);
    addTransicionTransiciones(estados->estados[estado]->transiciones, transicion);
}
