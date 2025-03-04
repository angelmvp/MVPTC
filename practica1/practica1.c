#include <stdio.h>
#include <stdlib.h>
#include "MVPCadenas.h"


int main(){
    char* cadena;
    int eleccion,seguir=1;
    char* arregloEliminar;
    cadena = (char *)malloc(200 * sizeof(char));
    arregloEliminar = (char *)malloc(200 * sizeof(char));
    if (cadena == NULL) {
        printf("----ERROR:ya no tienes memoriaa\n");
        return 1;
    }
    char *cadenaPrueba="hola";
    char * nuevaCadena=elevaPotencia(cadenaPrueba,6);
    printf("bienvenido al programa de la practica 1 de teoria computacional acerca de cadenas\n");
    printf("Introduzca la cadena a analizar: ");
    scanf("%[^\n]", cadena);
    printf("la cadena tiene un tamanio de %d\n",cadenaTam(cadena));
    do{
        int n=0,p=0,s=0;
        printf("----------------------------\n");
        printf("la cadena a analizar es %s\n",cadena);
        printf("que operacion quiere realizar \n");
        printf("1.-ObtenerPrefijo\n2.-ObtenerSubfijo\n3.-ObtenerSubcadena\n");
        printf("4.-ObtenerSubsecuencia\n5.-Elevar a una potencia\n6.->>>>");
        scanf("%d",&eleccion);
        char* nuevaCadena;
        switch (eleccion){
        case 1:
            printf("introduzca la cantidad de simbolos a eliminar: ");
            scanf("%d",&n);
            if (validacionCadenaTam(cadena,n)){
                nuevaCadena = obtenerPrefijo(cadena,n);
                printf("----El prefijo de %s con %d elementos eliminados es %s\n",cadena,n,nuevaCadena);
            }else{
                printf("----ERROR: el tamanio de la cantidad a eliminar excede el tamanio de la cadena\n");
            }
            
            break;
        case 2:
            printf("introduzca la cantidad de simbolos a eliminar: ");
            scanf("%d",&n);
            if (validacionCadenaTam(cadena,n)){
                nuevaCadena = obtenerSubfijo(cadena,n);
                printf("----El subfijo de %s con %d elementos eliminados es %s\n",cadena,n,nuevaCadena);
            }else{
                printf("----ERROR:el tamanio de la cantidad a eliminar excede el tamanio de la cadena\n");
            }
            break;
        case 3:
            printf("introduzca la cantidad de elementos del prefijo a eliminar: ");
            scanf("%d",&p);
            printf("introduzca la cantidad de elementos del subfijo a eliminar: ");
            scanf("%d",&s);
            if(validacionCadenaTam(cadena,p+s)){
                nuevaCadena = obtenerSubCadena(cadena,p,s);
            printf("----La sucbadena obtenida de %s con %d elementos del Prefijo y %d elementos del Subfijo eliminados es %s\n",cadena,p,s,nuevaCadena);
            }else{
                printf("----ERROR:el tamanio de la cantidad a eliminar excede el tamanio de la cadena\n");
            }
            
            break;
        case 4:
            printf("introduzca la cantidad de indices a eliminar: ");
            scanf("%d", &n);
            int* arregloEliminar = (int*)malloc(n * sizeof(int));
            if (arregloEliminar == NULL) {
                printf("----ERROR: ya no tienes memoria\n");
                break;
            }
            for (int i = 0; i < n; i++) {
                printf("introduzca el indice a eliminar numero %d: ", i + 1);
                scanf("%d", &arregloEliminar[i]);
            }
            nuevaCadena = obtenerSubsecuencia(cadena, arregloEliminar, n);
            printf("La subsecuencia de %s con los indices eliminados es %s\n", cadena, nuevaCadena);
            free(arregloEliminar);
            break;
         case 5:
            printf("introduzca la potencia de su cadena: ");
            scanf("%d",&n);
            nuevaCadena = elevaPotencia(cadena,n);
            printf("la cadena %s con potencia de %d es %s\n",cadena,n,nuevaCadena);
            break;
        default:
            seguir=0;
            break;
        }
        printf("ahora que quieres realizar\n1.-Continuar\n2.-Cambiar Cadena\n3.-Salir>>>>>");
        scanf("%d",&eleccion);
        if(eleccion==1){
            continue;
        }else if(eleccion==2){
            printf("introduzca la nueva cadena a analizar: ");
            scanf("%[^\n]",cadena);
        }else{
            seguir=0;
        }
    }while(seguir);

}

