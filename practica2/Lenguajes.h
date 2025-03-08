#include <stdio.h>
#include <stdlib.h>
#include "MVPstring.h"

typedef struct nodo{
    char * cadena;
    struct nodo* sig;
}Nodo;
typedef struct lenguaje{
    Nodo* inicio;
    Nodo* fin;
    int tam;
}Lenguaje;


Nodo* crearNodo(char * cadena);
int eliminarNodo(Nodo*);


Nodo* crearNodo(char* cadena){
    Nodo* nuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    nuevoNodo->cadena=cadena;
    return nuevoNodo;
}
int eliminarNodo(Nodo* n){
    free(n);
    return 1;
}


void __init__(Lenguaje*);
int isEmpty(Lenguaje*);
int pushLenguaje(Lenguaje*,Nodo*);
Nodo* popLenguaje(Lenguaje* );
void imprimirLenguaje(Lenguaje *L);
void limpiarLenguaje(Lenguaje* L);



void __init__(Lenguaje* L){
    L->tam=0;
    L->inicio=NULL;
    L->fin=NULL;
}
void limpiarLenguaje(Lenguaje*L){
    Nodo* aux;
    while(L->inicio){
        aux=L->inicio;
        L->inicio=L->inicio->sig;
        eliminarNodo(aux);
    }
    L->fin=NULL;
    L->tam=0;
}
int isEmpty(Lenguaje *L){
    return L->inicio==0;
}
int pushLenguaje(Lenguaje* L, Nodo* n) {
    if (isEmpty(L)) {
        L->inicio = n;
    } else {
        Nodo* aux = L->inicio;
        while (aux) {
            if (cadenasIguales(aux->cadena, n->cadena)){
                printf("la cadena %s es igual a %s : \n",aux->cadena,n->cadena);
                return 0; 
            }
            aux = aux->sig;
        }
        L->fin->sig = n;
    }
    L->fin = n;
    n->sig=NULL;
    L->tam++;
    //printf("%d\n",L->tam);
    return 1;
}
Nodo* popLenguaje(Lenguaje* L){
    Nodo* retornar;
    if(!isEmpty(L)){
        Nodo* aux=L->inicio;
        while(aux->sig){
            aux=aux->sig;
        }
        retornar=aux;
    }
    return retornar;
}
void imprimirLenguaje(Lenguaje *L){
    Nodo* aux=L->inicio;
    printf("[");
    while(aux){
        printf("%s",aux->cadena);
        aux=aux->sig;
        if(aux){printf(",");}
    }
    printf("]");
}

Lenguaje* unionLenguajes(Lenguaje* L1,Lenguaje* L2);
Lenguaje* concatenacion(Lenguaje* L1,Lenguaje* L2);
Lenguaje* potenciaDeLenguaje(Lenguaje* L,int potencia);
Lenguaje* invertirLenguaje(Lenguaje* L);
Lenguaje* copiarLenguaje(Lenguaje* L);

Lenguaje* unionLenguajes(Lenguaje* L1,Lenguaje* L2){
    Lenguaje* nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
    if(!nuevoLenguaje){
        puts("no hay ya mas menmoria para el elengujae nuevo");
    }
    __init__(nuevoLenguaje);
    if(!L1->inicio && !L2->inicio){
        printf("lso lenguajes estan vacios");
        return nuevoLenguaje;
    }else if(L1->inicio && !L2->inicio){
        return L1;
    }else if(!L1->inicio && L2->inicio){
        return L2;
    }else{
        Nodo* aux;
        aux=L1->inicio;
        for(int i=0;i<L1->tam;i++){
            Nodo* nuevoNodo= crearNodo(aux->cadena);
            pushLenguaje(nuevoLenguaje,nuevoNodo);
            aux=aux->sig;
        }
        aux=L2->inicio;
        //imprimirLenguaje(nuevoLenguaje);
        for(int i=0;i<L2->tam;i++){
            Nodo* nuevoNodo= crearNodo(aux->cadena);
            pushLenguaje(nuevoLenguaje,nuevoNodo);
            aux=aux->sig;
        }
    }
    return nuevoLenguaje;

}
Lenguaje* concatenacion(Lenguaje* L1,Lenguaje* L2){
    Lenguaje* nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
    if(!nuevoLenguaje){
        puts("no hay ya mas menmoria para el elengujae nuevo");
    }
    __init__(nuevoLenguaje);
    if(!L1->inicio || !L2->inicio){
        printf("lso lenguajes estan vacios");
        return nuevoLenguaje;
    }else{
        Nodo* aux1;
        Nodo* aux2;
        aux1=L1->inicio;
        for(int i=0;i<L1->tam;i++){
            aux2=L2->inicio;
            for(int j=0;j<L2->tam;j++){
                Nodo* nuevoNodo;
                char* nuevaCadena = concatenar(aux1->cadena,aux2->cadena);
                nuevoNodo= crearNodo(nuevaCadena);
                pushLenguaje(nuevoLenguaje,nuevoNodo);
                aux2=aux2->sig;
            }
            aux1=aux1->sig;
        }
    }
    return nuevoLenguaje;
}
Lenguaje* potenciaDeLenguaje(Lenguaje* L,int potencia){
    Lenguaje* nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
    Lenguaje* lenguajeAux=(Lenguaje *) malloc(sizeof(Lenguaje));
    if(!nuevoLenguaje|| !lenguajeAux){
        puts("no hay ya mas menmoria para el elengujae nuevo");
    }
    __init__(nuevoLenguaje);
    __init__(lenguajeAux);
    if(!L->inicio){
        printf("el lenguaje esta vacio");
        return nuevoLenguaje;
    }else if (potencia==0){
        return nuevoLenguaje;
    }else if(potencia==1){
        return L;
    }else{
        lenguajeAux=L;
        if(potencia<0){
            lenguajeAux=invertirLenguaje(L);
            potencia = potencia*-1;
            printf("la potencia es %d",potencia);
        }
        Nodo* aux;
        nuevoLenguaje=lenguajeAux;
        for(int i=1;i<potencia;i++){
            nuevoLenguaje=concatenacion(nuevoLenguaje,lenguajeAux);
        }
    }
    return nuevoLenguaje;
}
Lenguaje* invertirLenguaje(Lenguaje* L){
    Lenguaje* nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
    if(!nuevoLenguaje){
        puts("no hay ya mas menmoria para el elengujae nuevo");
    }
    __init__(nuevoLenguaje);
    if(!L->inicio){
        printf("lso lenguajes estan vacios");
        return nuevoLenguaje;
    }else{
        Nodo* aux;
        aux=L->inicio;
        for(int i=0;i<L->tam;i++){
            Nodo* nuevoNodo;
            char* cadenaInvertida;
            cadenaInvertida=invertirCadena(aux->cadena);
            aux=aux->sig;
            nuevoNodo = crearNodo(cadenaInvertida);
            pushLenguaje(nuevoLenguaje,nuevoNodo);
        }
    }
    return nuevoLenguaje;
}
Lenguaje* copiarLenguaje(Lenguaje* L){
    Lenguaje* nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
    if(!nuevoLenguaje){
        puts("no hay ya mas menmoria para el elengujae nuevo");
    }
    __init__(nuevoLenguaje);
    if(!L->inicio){
        printf("lso lenguajes estan vacios");
        return nuevoLenguaje;
    }else{
    }
    return nuevoLenguaje;
}