//Angel Martin Vazquez Perez
//practica5Algoritmo para automatasDETERMINISTAS
//5BV1
#include <stdio.h>
#include <stdlib.h>
#include "MVPColaDet.h"

Estados* crearEstadosDeLinea(char* linea);
char* crearAlfabeto(char* linea);
void asignarEstadoInicial(Estados* estado,char* etiqueta);
void asignarEstadoAceptacion(Estados* estado,char* etiqueta);
void asignarTransiciones(Estados* estados,char* linea);
int validarAutomata(Estados* estados,char* cadena);
void crearAutomataDeterminista(Estados* estados,char* alfabeto);
void generarArchivoTXT(EstadosDeterminista* estadosDeterminista,char* alfabeto);
int main() {
    puts("Bienvenido al practica 5 de transformaciones de automatas no deterministas \n");
    char* cadena = (char*)malloc(250 * sizeof(char));
    Estados* estados;
    FILE* file = fopen("ejemploClase.txt", "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int indice = 0;
    char linea[250];
    char* alfabeto = NULL;
    while (fgets(linea, sizeof(linea), file) != NULL) {
        // Eliminar el salto de línea al final de cada línea leída
        if (linea[cadenaTam(linea) - 1] == '\n') {
            linea[cadenaTam(linea) - 1] = '\0';
        }
        if (indice == 0) {
            estados = crearEstadosDeLinea(linea);
        } else if (indice == 1) {
            alfabeto = crearAlfabeto(linea);
        } else if (indice == 2) {
            char* estadoInicial = copiarCadena(linea);
            asignarEstadoInicial(estados,estadoInicial);
        } else if (indice == 3) {
        char* token = linea;
        char* end = linea;
        
        while (*end) {
            if (*end == ',') {
                *end = '\0'; // Temporalmente terminar la cadena
                asignarEstadoAceptacion(estados, token);
                *end = ','; // Restaurar la coma
                token = end + 1;
            }
            end++;
        }
        // Procesar el último estado
        if (*token) {
            asignarEstadoAceptacion(estados, token);
        }
        } else {    
            asignarTransiciones(estados,linea);
        }
        indice++;
    }

    crearAutomataDeterminista(estados,alfabeto);
    // // for(int i=0;i<estados->cantidadEstados;i++){
    // //     imprimirTransicionesEstado(estados->estados[i]);
    // // }
    fclose(file);
    return 0;
}

Estados* crearEstadosDeLinea(char* linea) {
    Estados* estados = __init_estados();
    char* inicio = linea;
    char* fin = linea;
    
    while (*fin) {
        if (*fin == ',') {
            // Extraer el nombre del estado entre inicio y fin
            int longitud = fin - inicio;
            if (longitud > 0) {
                char* nombreEstado;
                for(int i = 0; i < longitud; i++) {
                    nombreEstado[i] = inicio[i];
                }
                nombreEstado[longitud] = '\0';
               
                Estado* nuevoEstado = crearEstado(copiarCadena(nombreEstado), 0, 0);
                addEstadoEstados(estados, nuevoEstado);
                nuevoEstado->transiciones = __init_transiciones();
            }
            inicio = fin + 1;
        }
        fin++;
    }
    int longitud = fin - inicio;
    if (longitud > 0) {
        char* nombreEstado;
        for(int i = 0; i < longitud; i++) {
            nombreEstado[i] = inicio[i];
        }
        nombreEstado[longitud] = '\0';
        Estado* nuevoEstado = crearEstado(copiarCadena(nombreEstado), 0, 0);
        addEstadoEstados(estados, nuevoEstado);
        nuevoEstado->transiciones = __init_transiciones();
    }
    return estados;
}

char* crearAlfabeto(char* linea) {
    int lenOriginal = cadenaTam(linea); // Usar cadenaTam si está definida y es correcta
    char* alfabeto = (char*)malloc(lenOriginal + 1); // Suficiente espacio
    if (alfabeto == NULL) {
        puts("----ERROR: No hay memoria disponible para el alfabeto");
        return NULL;
    }
    int k = 0; // Índice para la nueva cadena 'alfabeto'
    for (int i = 0; i < lenOriginal; i++) {
        if (linea[i] != ',') { // Copiar solo si no es una coma
            alfabeto[k] = linea[i];
            k++;
        }
    }
    alfabeto[k] = '\0';
    return alfabeto;
}

void asignarEstadoInicial(Estados* estados,char* etiqueta) {
    for (int i = 0; i < estados->cantidadEstados; i++) {
        if (cadenasIguales(estados->estados[i]->etiqueta, etiqueta)) {
            estados->estados[i]->inicial = 1;
            printf("Estado inicial asignado: %s\n", estados->estados[i]->etiqueta);
            return;
        }
    }
    printf("Error: Estado inicial no encontrado\n");
}

void asignarEstadoAceptacion(Estados* estados, char* etiqueta) {
    for(int i = 0; i < estados->cantidadEstados; i++) {
        if (cadenasIguales(estados->estados[i]->etiqueta, etiqueta)) {
            estados->estados[i]->aceptacion = 1;
            printf("Estado de aceptacion: %s\n", estados->estados[i]->etiqueta);
            return;
        }
    }
    printf("Error: Estado de aceptación '%s' no encontrado\n", etiqueta);
}
void asignarTransiciones(Estados* estados, char* linea) {
    printf("Transiciones: %s\n", linea);
    char* inicio = linea;
    char* cursor = linea;
    int componente = 0;
    
    char* nombreOrigen = NULL;
    char* simbolo = NULL;
    char* nombreDestino = NULL;
    
    while (*cursor) {
        if (*cursor == ',' || *cursor == '\0') {
            // Calculamos longitud del componente actual
            int longitud = cursor - inicio;
            
            // Reservamos memoria y copiamos el componente
            char* buffer = (char*)malloc(longitud + 1);
            char* ptr = buffer;
            char* tmp = inicio;
            
            while (tmp < cursor) {
                *ptr++ = *tmp++;
            }
            *ptr = '\0';
            
            // Asignamos a la variable correspondiente
            if (componente == 0) {
                nombreOrigen = buffer;
            } else if (componente == 1) {
                simbolo = buffer;
            } else if (componente == 2) {
                nombreDestino = buffer;
            }
            
            componente++;
            inicio = cursor + 1;
            
            if (componente >= 3) break; // Ya tenemos los 3 componentes
        }
        cursor++;
    }
    
    // Procesar el último componente si no terminó con coma
    if (componente < 3 && *inicio) {
        int longitud = cursor - inicio;
        if (longitud > 0) {
            char* buffer = (char*)malloc(longitud + 1);
            char* ptr = buffer;
            char* tmp = inicio;
            
            while (tmp < cursor) {
                *ptr++ = *tmp++;
            }
            *ptr = '\0';
            
            if (componente == 0) {
                nombreOrigen = buffer;
            } else if (componente == 1) {
                simbolo = buffer;
            } else if (componente == 2) {
                nombreDestino = buffer;
            }
        }
    }
    
    // Verificar que tenemos los 3 componentes
    if (!nombreOrigen || !simbolo || !nombreDestino) {
        printf("Error: Formato de transición incorrecto\n");
        if (nombreOrigen) free(nombreOrigen);
        if (simbolo) free(simbolo);
        if (nombreDestino) free(nombreDestino);
        return;
    }
    
    // Imprimir los componentes
    //printf("Origen: %s, Símbolo: %s, Destino: %s\n", nombreOrigen, simbolo, nombreDestino);

    // parabuscarlosmamahuevasos de estados;
    Estado* estadoOrigenPtr = NULL;
    Estado* estadoDestinoPtr = NULL;
    
    for (int i = 0; i < estados->cantidadEstados; i++) {
        if (cadenasIguales(estados->estados[i]->etiqueta, nombreOrigen)) {
            estadoOrigenPtr = estados->estados[i];
        }
        if (cadenasIguales(estados->estados[i]->etiqueta, nombreDestino)) {
            estadoDestinoPtr = estados->estados[i];
        }
    }
    
    if (estadoOrigenPtr && estadoDestinoPtr) {
        Transicion* transicion = crearTransicion(simbolo, estadoDestinoPtr);
        addTransicionTransiciones(estadoOrigenPtr->transiciones, transicion);
    } else {
        printf("Error: No se encontraron los estados %s o %s\n", nombreOrigen, nombreDestino);
    }
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


void crearAutomataDeterminista(Estados* estados,char* alfabeto){
    printf("Creando automata determinista...\n");
    printf("Alfabeto: %s\n", alfabeto);
    int numNuevosEstados=0;
    Estado* estadoInicial = obtenerEstadoInicial(estados);
    Estados * nuevosEstados= (Estados*)malloc(sizeof(Estados));
    nuevosEstados->cantidadEstados=0;
    nuevosEstados->estados=(Estado**)malloc(sizeof(Estado*)*10);
    Estados* estadosIniciales= cerraduraEpsilon(estadoInicial);
    EstadoDeterminista* estadoA= crearestadoDeterminista("A", estadosIniciales);
    imprimirEstadoDeterminista(estadoA);
    cerraduraEpsilonEstados(estadoA->estados);
    EstadosDeterminista* estadosDeterminista= __init__estadosDeterminista(estadosDeterminista);
    addEstadoDeterministaEstados(estadosDeterminista, estadoA);
    int iteradorNombres=1;

    Cola* cola= crearCola();
    encolar(cola,estadoA);
    while(!estaVaciaCola(cola)){
        EstadoDeterminista* estadoActual= desencolar(cola);
        printf("\nEstado actual a analizar: %s\n", estadoActual->etiqueta);
        imprimirEstadoDeterminista(estadoActual);
        printf("Iterando sobre el alfabeto:\n");
        for (int i = 0; alfabeto[i] != '\0'; i++) {
            char simboloActual = alfabeto[i];
            printf("Simbolo: %c\n", simboloActual);
            // Para usar el símbolo en funciones que esperan char* (como irA o moverA)
            char simboloStr[2];
            simboloStr[0] = simboloActual;
            simboloStr[1] = '\0';
            Estados* nuevosEstadosSimbolo = irAEstados(estadoActual->estados, simboloStr);
            if(nuevosEstadosSimbolo->cantidadEstados==0){
                printf("no se encontraron estados\n");
            }else if(existeEnConjuntoDeterminista(estadosDeterminista,nuevosEstadosSimbolo)){
                EstadoDeterminista* existente= existeEnConjuntoDeterminista(estadosDeterminista,nuevosEstadosSimbolo);
                printf("ya existe el conjunto de estados\n");
                TransicionDeterminista* transicion= crearTransicionDeterminista(simboloStr,existente);
                printf("se agrega la transicion %s\n", transicion->cadena);
                printf("al estado %s\n", existente->etiqueta);
                addTransicionDeterministaTransiciones(estadoActual->transiciones, transicion);
                printf("se agrego la transicion\n");
            }else{
                printf("se creara el nuevo estado");
                char nombreEstado[2];
                nombreEstado[0] = 'A' + iteradorNombres;
                nombreEstado[1] = '\0';
                EstadoDeterminista* nuevoDeterminista= crearestadoDeterminista(nombreEstado, nuevosEstadosSimbolo);
                addEstadoDeterministaEstados(estadosDeterminista, nuevoDeterminista);
                iteradorNombres++;
                encolar(cola,nuevoDeterminista);
                printf("ahora se haran las transiciones");
                TransicionDeterminista* transicion= crearTransicionDeterminista(simboloStr,nuevoDeterminista);
                printf("se agrega la transicion %s\n", transicion->cadena);
                printf("al estado %s\n", nuevoDeterminista->etiqueta);
                addTransicionDeterministaTransiciones(estadoActual->transiciones, transicion);
                printf("se agrego la transicion\n");

            }        
        }
        imprimirEstadoDeterminista(estadoActual);
    }
    imprimirEstadosDeterminista(estadosDeterminista);
    printf("%s",alfabeto);
    generarArchivoTXT(estadosDeterminista,alfabeto);

}
void generarArchivoTXT(EstadosDeterminista* estadosDeterminista,char* alfabeto){
    printf("Alfabeto: %s\n", alfabeto);
    FILE* file = fopen("automataDeterminista.txt", "w");
    if (file == NULL) {
        perror("No se pudo abrir el archivo para escritura");
        return;
    }
    printf("Estados DFA: ");
    for (int i = 0; i < estadosDeterminista->cantidadEstados; i++) {
        fprintf(file, "%s", estadosDeterminista->estados[i]->etiqueta);
        printf("%s", estadosDeterminista->estados[i]->etiqueta);
        if (i < estadosDeterminista->cantidadEstados - 1) {
            fprintf(file, ",");
            printf(",");
        }
    }
    fprintf(file, "\n");
    printf("\n");
    printf("Alfabeto: %s\n", alfabeto);
    int lenAlfabeto = cadenaTam(alfabeto);
    for (int i = 0; i < lenAlfabeto; i++) {
        fprintf(file, "%c", alfabeto[i]);
        if (i < lenAlfabeto - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");
    printf("\n");

    printf("Estado Inicial DFA: %s\n", estadosDeterminista->estados[0]->etiqueta);
    fprintf(file, "%s\n", estadosDeterminista->estados[0]->etiqueta);

    printf("Transiciones DFA:\n");
    for (int i = 0; i < estadosDeterminista->cantidadEstados; i++) {
        EstadoDeterminista* estadoOrigen = estadosDeterminista->estados[i];
        if (estadoOrigen->transiciones) { 
            for (int j = 0; j < estadoOrigen->transiciones->cantidadTransiciones; j++) {
                TransicionDeterminista* trans = &estadoOrigen->transiciones->transicion[j];
                if (trans->sigEstado) {
                    fprintf(file, "%s,%s,%s\n",estadoOrigen->etiqueta,trans->cadena,trans->sigEstado->etiqueta);
                    printf("%s,%s,%s\n",estadoOrigen->etiqueta,trans->cadena,trans->sigEstado->etiqueta);
                }
            }
        }
    }
    fclose(file);
}
