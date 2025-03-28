//Angel Martin Vazquez Perez
//practica3Automatas
//5BV1
#include <stdio.h>
#include <stdlib.h>
#include "MVPPila.h"
#include <string.h>
//#include "MVPCola.h"

Estados* crearEstadosDeLinea(char* linea);
char* crearAlfabeto(char* linea);
void asignarEstadoInicial(Estado* estado);
void asignarEstadoAceptacion(Estado* estado);
void asignarTransiciones(Estados* estados,char* linea);
int validarAutomata(Estados* estados,char* cadena);
int main() {
    puts("Bienvenido al practica 3 de automatas\n");
    char* cadena="111111111111";
    Estados* estados;
    FILE* file = fopen("ejemplo3.txt", "r");
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
                    printf("Estado de aceptacion: %d\n", estadoAceptacion);
                    asignarEstadoAceptacion(estados->estados[estadoAceptacion]);
                }
                i++;
            }
        } else {    
            asignarTransiciones(estados,linea);
        }
        indice++;
    }
    puts("cadenas validas");
    int isValido= validarAutomata(estados,cadena);
    if(isValido){
        printf("cantidad de caminos validos %d", isValido);
    }else{
        printf("no se encontro ningun camion valido");
    }

    // // for(int i=0;i<estados->cantidadEstados;i++){
    // //     imprimirTransicionesEstado(estados->estados[i]);
    // // }
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
Estado* obtenerEstadoInicial(Estados* estados){
    int i=0;
    while(estados->estados[i]){
        if(estados->estados[i]->inicial){
            //printf("se retorna %c", estado);
            return estados->estados[i];
        }
        i++;
    }
    printf("no hay esatdo inicial");
    return NULL;
    
}
int validarAutomata(Estados* estados,char* cadena){
    int valido=0;
    int tamCadena= cadenaTam(cadena);
    Pila* pila=  crearPila(pila);
    NodoPila* nodoAux;
    Estado* estadoAux;
    Estado* estadoInicial = obtenerEstadoInicial(estados);
    printf("El estado Inicial es %s \n", estadoInicial->etiqueta);
    Camino* caminoInicial= crearCamino(estadoInicial->etiqueta);
    NodoPila* nodoInicial = crearNodoPila(estadoInicial,caminoInicial,0);
    apilar(pila,nodoInicial);
    while(!isEmpty(pila)){
        nodoAux= desapilar(pila);
        estadoAux=nodoAux->estado;
        int nuevoNivel= nodoAux->nivel +1;
        //printf("camino actual %s\n", nodoAux->camino->cadenaEstados);
        if(estadoAux->transiciones==NULL){
            puts("camino invalido");
            imprimirCamino(nodoAux->camino);
        }else{
            if(tamCadena==nuevoNivel-1){
                if(istEstadoAceptacion(estadoAux)){
                    printf("caminoValido");
                    imprimirCamino(nodoAux->camino);
                    valido++;
                }
            }else{
                Transiciones* transicionesAux= estadoAux->transiciones;
                int tamTransiciones= estadoAux->transiciones->cantidadTransiciones;
                if(tamTransiciones==0){
                    puts("camino invalido");
                    imprimirCamino(nodoAux->camino);
                }
                while(tamTransiciones!=0){
                    Transicion* transicionActual = &transicionesAux->transicion[tamTransiciones-1];
                    char* cadenaTransicion = transicionActual->cadena;
                    cadenaTransicion[1]='\0';
                    char cadenaEnNivel [2] ="";
                    cadenaEnNivel[0]=cadena[nuevoNivel-1];
                    cadenaEnNivel[1]='\0';
                    char* nuevaCadena=cadenaEnNivel;
                    // printf("comparando la cadena de transicion %s ", cadenaTransicion);
                    // printf("con la cadena original %s \n",nuevaCadena);
                    if(cadenasIguales(cadenaTransicion,nuevaCadena)){
                        //puts("cadenas iguales, se apila");
                        Estado* estadoActual=transicionActual->sigEstado;
                        Camino* nuevoCamino = crearCamino(concatenar(concatenar(nodoAux->camino->cadenaEstados,"->"),estadoActual->etiqueta));
                        NodoPila* nuevoNodo = crearNodoPila(estadoActual,nuevoCamino,nuevoNivel);
                        apilar(pila,nuevoNodo);
                    }
                    tamTransiciones--;
                }
            }
        }
        //puts("todos los camions apilados");
    }
    return valido;
}