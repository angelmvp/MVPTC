#include <stdio.h>
#include <stdlib.h>
#include "Lenguajes.h"

int main(){
    puts("bienvenido al programa numero 2\n");
    int n1,n2;
    Lenguaje* L1;
    Lenguaje* L2;
    L1= (Lenguaje* )malloc(sizeof(Lenguaje));
    L2= (Lenguaje* )malloc(sizeof(Lenguaje));
    if (!L1 || !L2) {
        printf("no hay meoria crear listas\n");
        return 1;
    }
    __init__(L1);
    __init__(L2);
    printf("intoduzca la cantidad de elementos en el Lenguaje 1: ");
    scanf("%d",&n1);
    getchar();
    for(int i=0;i<n1;i++){
        char* cadena = (char*)malloc(sizeof(char)*100);
        printf("introduzca la cadena %d: ",i+1);
        scanf("%[^\n]",cadena);
        getchar();
        Nodo* nodo=crearNodo(cadena);
        pushLenguaje(L1,nodo);
    }
    printf("ahora intoduzca la cantidad de elementos en el Lenguaje 2: ");
    scanf("%d",&n2);
    getchar();
    for(int i=0;i<n2;i++){
        char* cadena = (char*)malloc(sizeof(char)*100);
        printf("introduzca la cadena %d: ",i+1);
        scanf("%[^\n]",cadena);
        getchar();
        Nodo* nodo=crearNodo(cadena);
        pushLenguaje(L2,nodo);
    }
    int continuar=1;
    while(continuar!=0){
        Lenguaje* nuevoLenguaje;
        nuevoLenguaje= (Lenguaje *) malloc(sizeof(Lenguaje));
        if(!nuevoLenguaje){
            puts("no hay ya mas menmoria para el elengujae nuevo");
        }
        puts("que operacion desea realizar: ");
        puts("1.- Union");
        puts("2.- Concatenacion");
        puts("3.- Potencia");
        puts("4.- Salir");
        int opcion;
        scanf("%d",&opcion);
        getchar();
        switch(opcion){
            case 1:
                nuevoLenguaje=unionLenguajes(L1,L2);
                printf("\nel tamanio del lenaguaje resultante es %d ",nuevoLenguaje->tam);
                puts("La Union de los 2 lenguajes es :");
                imprimirLenguaje(nuevoLenguaje);
                limpiarLenguaje(nuevoLenguaje);
                //free(nuevoLenguaje);
                break;
            case 2:
            puts("que concatenacion quiere realizar:");
            puts("1.- L1L2");
            puts("2.- L2L1");
            int opcion2;
            scanf("%d",&opcion2);
            getchar();
            if(opcion2==1){
                nuevoLenguaje=concatenacion(L1,L2);
            }else{
                nuevoLenguaje=concatenacion(L2,L1);
            }
            printf("\nel tamanio del lenaguaje resultante es %d ",nuevoLenguaje->tam);
            puts("La Concatenacion de los 2 lenguajes es :");
            imprimirLenguaje(nuevoLenguaje);
            limpiarLenguaje(nuevoLenguaje);
            //free(nuevoLenguaje);
                break;
            case 3:
                puts("A que lenguaje quiere la potencia  realizar:");
                puts("1.- L1");
                puts("2.- L2");
                int opcion3;
                scanf("%d",&opcion3);
                getchar();
                puts("a que potencia quiere elevar el lenguaje");
                int potenciaN;
                scanf("%d",&potenciaN);
                getchar();
                if(opcion3==1){
                    nuevoLenguaje=potenciaDeLenguaje(L1,potenciaN);
                }else{
                    nuevoLenguaje=potenciaDeLenguaje(L2,potenciaN);
                }
                printf("\nel tamanio del lenaguaje resultante es %d \n",nuevoLenguaje->tam);
                printf("El lenguaje elevado a la potencia es %d : ",potenciaN);
                imprimirLenguaje(nuevoLenguaje);
                limpiarLenguaje(nuevoLenguaje);
                //free(nuevoLenguaje);
                break;
            default:
                continuar=0;
                break;
            
        }
    }
    puts("gracias adios");
    // puts("Lenguaje 1:");
    // imprimirLenguaje(L1);
    // puts("Lenguaje 2:");
    // imprimirLenguaje(L2);
}