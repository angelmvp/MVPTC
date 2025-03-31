//Angel Martin Vazquez Perez
//practica3Automatas
//5BV1
#include <stdio.h>
#include <stdlib.h>
#include "MVPPila.h"

Estados* crearEstadosDeLinea(char* linea);
char* crearAlfabeto(char* linea);
void asignarEstadoInicial(Estados* estado,char* etiqueta);
void asignarEstadoAceptacion(Estados* estado,char* etiqueta);
void asignarTransiciones(Estados* estados,char* linea);
int validarAutomata(Estados* estados,char* cadena);
int main() {
    puts("Bienvenido al practica 3 de automatas\n");
    char* cadena = (char*)malloc(250 * sizeof(char));
    Estados* estados;
    FILE* file = fopen("ejemplo3si.txt", "r");
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
    
    int seguir;
    while(seguir){
        
        printf("introduzca la cadena a validar\n");
        scanf("%s",cadena);
        int valido=validarAutomata(estados,cadena);
        if(valido){
            puts("cadenas validas");
            printf("la cadena %s es valida\n", cadena);
            printf("existen %d caminos validos\n", valido);
        }else{
            printf("la cadena %s no es valida\n", cadena);
        }
        printf("desea seguir validando cadenas? 1=si 0=no\n");
        scanf("%d",&seguir);
    }

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
    char* alfabeto = (char*)malloc(cadenaTam(linea) + 1);
    if (alfabeto == NULL) {
        puts("----ERROR: No hay memoria disponible");
        return NULL;
    }
    alfabeto=copiarCadena(linea);
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
            printf("Estado de aceptación asignado: %s\n", estados->estados[i]->etiqueta);
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
                    char* cadenaTransicion = copiarCadena(transicionActual->cadena);
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