#include "MVPPila.h"

Estados* cerraduraEpsilon(Estado* estado);
Estados* cerraduraEpsilonEstados(Estados* estados);
Estados* moverAEstados(Estados* estados, char* simbolo);
Estados* moverA(Estado* estados, char* simbolo);
Estados* irAEstados(Estados* estados, char* simbolo);
Estados* irA(Estado* estado, char* simbolo);

int existeEnConnjunto(Estados* estados, Estado* estado){
    for(int i=0;i<estados->cantidadEstados;i++){
        if(cadenasIguales(estados->estados[i]->etiqueta,estado->etiqueta)){
            return 1;
        }
    }
    return 0;
}

Estados* cerraduraEpsilon(Estado* estado){
    char* estadosEpsilon[100];
    for(int i=0;i<100;i++){
        estadosEpsilon[i]=NULL;
    }
    Estados* nuevosEstados= (Estados*)malloc(sizeof(Estados));
    nuevosEstados->cantidadEstados=0;
    nuevosEstados->estados=(Estado**)malloc(sizeof(Estado*)*10);
    int i=1;
    // printf("se estara aplicando la cerradura epsilon al estado %s\n", estado->etiqueta);
    Pila* pila=  crearPila(pila);
    NodoPila* nodoAux;
    Estado* estadoAux;
    NodoPila* nodoInicial = crearNodoPila(estado,NULL,0);
    estadosEpsilon[0]=estado->etiqueta;
    nuevosEstados->estados[0]=estado;
    nuevosEstados->cantidadEstados++;
    apilar(pila,nodoInicial);
    while(!isEmpty(pila)){
        nodoAux= desapilar(pila);
        estadoAux=nodoAux->estado;
        int nuevoNivel= nodoAux->nivel +1;
        if(estadoAux->transiciones==NULL){
            // puts("camino invalido");
            // imprimirCamino(nodoAux->camino);
        }else{
            Transiciones* transicionesAux= estadoAux->transiciones;
            int tamTransiciones= estadoAux->transiciones->cantidadTransiciones;
            while(tamTransiciones!=0){
                Transicion* transicionActual = &transicionesAux->transicion[tamTransiciones-1];
                char* cadenaTransicion = copiarCadena(transicionActual->cadena);
                // printf("comparando la cadena de transicion %s ", cadenaTransicion);
                // printf("con la cadena original %s \n",nuevaCadena);
                if(cadenasIguales(cadenaTransicion,"e")){
                    Estado* estadoActual=transicionActual->sigEstado;
                    NodoPila* nuevoNodo = crearNodoPila(estadoActual,NULL,nuevoNivel-1);
                    estadosEpsilon[i]=estadoActual->etiqueta;
                    nuevosEstados->estados[i]=estadoActual;
                    nuevosEstados->cantidadEstados++;
                    i++;
                    apilar(pila,nuevoNodo);
                }
                tamTransiciones--;                }


            }
        }
    // for (int j=0; j<i; j++){
    //     printf("%s ", estadosEpsilon[j]);
    //     printf("estado %s ", nuevosEstados->estados[j]->etiqueta);
    //     printf("\n");
    // }
    return nuevosEstados;
}
Estados* cerraduraEpsilonEstados(Estados* estados){
    Estados* nuevosEstados= (Estados*)malloc(sizeof(Estados));
    nuevosEstados->cantidadEstados=0;
    nuevosEstados->estados=(Estado**)malloc(sizeof(Estado*)*10);
    for(int i=0;i<estados->cantidadEstados;i++){
        Estados* cerradura= cerraduraEpsilon(estados->estados[i]);
        for(int j=0;j<cerradura->cantidadEstados;j++){
            if(!existeEnConnjunto(nuevosEstados,cerradura->estados[j])){
                nuevosEstados->estados[nuevosEstados->cantidadEstados]=cerradura->estados[j];
                nuevosEstados->cantidadEstados++;
            }
        }
    }
    // printf("estados buenos de la cerradura a todods los estados  \n");
    // for (int j=0; j<nuevosEstados->cantidadEstados; j++){
    //     printf("%s, ", nuevosEstados->estados[j]->etiqueta);
    // }
    // printf("\n");
    return nuevosEstados;
}
Estados* moverAEstados(Estados* estados, char* simbolo){
    Estados* nuevosEstados= (Estados*)malloc(sizeof(Estados));
    nuevosEstados->cantidadEstados=0;
    nuevosEstados->estados=(Estado**)malloc(sizeof(Estado*)*10);
    for(int i=0;i<estados->cantidadEstados;i++){
        Estados* mover= moverA(estados->estados[i],simbolo);
        for(int j=0;j<mover->cantidadEstados;j++){
            if(!existeEnConnjunto(nuevosEstados,mover->estados[j])){
                // printf("se agrega el estado %s\n", mover->estados[j]->etiqueta);
                nuevosEstados->estados[nuevosEstados->cantidadEstados]=mover->estados[j];
                nuevosEstados->cantidadEstados++;
            }
        }
    }
    // printf("Estados buenos de mover A \n");
    // for (int j=0; j<nuevosEstados->cantidadEstados; j++){
    //     printf("estado %s ", nuevosEstados->estados[j]->etiqueta);
    //     printf("\n");
    // }
    return nuevosEstados;
}
Estados* moverA(Estado* estado, char* simbolo){
    Estados* nuevosEstados= (Estados*)malloc(sizeof(Estados));
    nuevosEstados->cantidadEstados=0;
    nuevosEstados->estados=(Estado**)malloc(sizeof(Estado*)*10);
    Transiciones* transicionesAuxSimbolo= estado->transiciones;
    int tamTransiciones= estado->transiciones->cantidadTransiciones;
    // printf("se estara aplicando el mover a con el simbolo %s al estado %s\n", simbolo,estado->etiqueta);
    while(tamTransiciones!=0){
        Transicion* transicionActual = &transicionesAuxSimbolo->transicion[tamTransiciones-1];
        char* cadenaTransicion = copiarCadena(transicionActual->cadena);
        // printf("comparando la cadena de transicion %s ", cadenaTransicion);
        // printf("con la cadena original %s \n",nuevaCadena);
        if(cadenasIguales(cadenaTransicion,simbolo)){
            Estado* estadoActual=transicionActual->sigEstado;
            nuevosEstados->estados[nuevosEstados->cantidadEstados]=estadoActual;
            nuevosEstados->cantidadEstados++;
        }
        tamTransiciones--;
    }
    // for (int j=0; j<nuevosEstados->cantidadEstados; j++){
    //     printf("estado %s ", nuevosEstados->estados[j]->etiqueta);
    //     printf("\n");
    // }
    return nuevosEstados;
}
Estados* irAEstados(Estados* estados, char* simbolo){
    Estados* estadosMover= moverAEstados(estados, simbolo);
    Estados* cerradura= cerraduraEpsilonEstados(estadosMover);
    printf("Estados buenos de ir A con el simbolo %s \n",simbolo);
    for (int j=0; j<cerradura->cantidadEstados; j++){
        printf("estado %s ", cerradura->estados[j]->etiqueta);
        printf("\n");
    }
    return cerradura;
}
Estados* irA(Estado* estado, char* simbolo){
    Estados* estadosMover= moverA(estado, simbolo);
    Estados* cerradura= cerraduraEpsilonEstados(estadosMover);
    printf("Estados buenos de ir A con el simbolo %s \n",simbolo);
    // for (int j=0; j<cerradura->cantidadEstados; j++){
    //     printf("estado %s ", cerradura->estados[j]->etiqueta);
    //     printf("\n");
    // }
    return cerradura;
}

typedef struct EstadosDeterminista{
    EstadoDeterminista** estados;
    int cantidadEstados;
}EstadosDeterminista;

EstadosDeterminista* __init__estadosDeterminista(){
    EstadosDeterminista* estadosDeterminista= (EstadosDeterminista*)malloc(sizeof(EstadosDeterminista));
    estadosDeterminista->cantidadEstados=0;
    estadosDeterminista->estados=NULL;
    return estadosDeterminista;
}
void addEstadoDeterministaEstados(EstadosDeterminista* estadosDeterminista, EstadoDeterminista* estado){
    // Incrementa el contador primero
    estadosDeterminista->cantidadEstados++;

    if (estadosDeterminista->estados == NULL) {
        // Si es el primer estado, reserva memoria inicial (ej. para 10 punteros)
        estadosDeterminista->estados = (EstadoDeterminista**)malloc(sizeof(EstadoDeterminista*) * 10); // Capacidad inicial
        if (estadosDeterminista->estados == NULL) {
            perror("Error al reservar memoria para estados deterministas");
            estadosDeterminista->cantidadEstados--; // Revierte el incremento si falla
            return; // Salir si no se pudo reservar memoria
        }
    } else {
        EstadoDeterminista** temp = (EstadoDeterminista**)realloc(estadosDeterminista->estados, sizeof(EstadoDeterminista*) * estadosDeterminista->cantidadEstados);
        if (temp == NULL) {
            perror("Error al realocar memoria para estados deterministas");
            estadosDeterminista->cantidadEstados--; // Revierte el incremento si falla
            return; // Salir si no se pudo realocar
        }
        estadosDeterminista->estados = temp; // Actualiza el puntero al bloque realocado
    }
    estadosDeterminista->estados[estadosDeterminista->cantidadEstados - 1] = estado;

    // printf(" -> Estado determinista '%s' agregado. Total: %d\n",
    //        estadosDeterminista->estados[estadosDeterminista->cantidadEstados - 1]->etiqueta,
    //        estadosDeterminista->cantidadEstados);
}
void imprimirEstadosDeterminista(EstadosDeterminista* estadosDeterminista){
    printf("Estados del automata determinista\n");
    // printf("cantidad de estados %d\n", estadosDeterminista->cantidadEstados);
    // for(int i=0;i<estadosDeterminista->cantidadEstados;i++){
    //     printf("Estado %s\n",estadosDeterminista->estados[i]->etiqueta);
    // }
    for(int i=0;i<estadosDeterminista->cantidadEstados;i++){
        imprimirEstadoDeterminista(estadosDeterminista->estados[i]);
    }
}


int sonEstadosIguales(Estados* estados1, Estados* estados2){
    int tamEstados1=estados1->cantidadEstados;
    int tamEstados2=estados2->cantidadEstados;
    if(tamEstados1!=tamEstados2){
        return 0;
    }
    for(int i=0;i<tamEstados1;i++){
        if(!existeEnConnjunto(estados1,estados2->estados[i])){
            return 0;
        }
    }
    return 1;
}

EstadoDeterminista* existeEnConjuntoDeterminista(EstadosDeterminista* estadosDet, Estados* estados){
    for(int i=0;i<estadosDet->cantidadEstados;i++){
        if(sonEstadosIguales(estadosDet->estados[i]->estados,estados)){
            return estadosDet->estados[i];
        }
    }
    return NULL;
}




