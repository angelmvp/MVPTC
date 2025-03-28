#include <stdio.h>
#include <stdlib.h>
#include "MVPstring.h"

char* obtenerPrefijo(char* cadena,int n);
char* obtenerSubfijo(char* cadena,int n);
char* obtenerSubCadena(char* cadena,int p,int s);
char* obtenerSubsecuencia(char* cadena,int* indices,int tamIndices); 
char* elevaPotencia(char* cadena,int potencia);

char* obtenerPrefijo(char* cadena, int n){
    puts("obteneidneod prefijo........");
    char* nuevaCadena;
    int tamCadena = cadenaTam(cadena);
    if(n==tamCadena){
        nuevaCadena="λ";
    }else if(n==0){
        nuevaCadena=cadena;
    }else{
        int i=0;
        int totales= tamCadena-n;
        nuevaCadena= (char *)malloc(sizeof(char)* (totales+1));
        if(nuevaCadena ==NULL){
            puts("----ERROR:ya no hay memoria paps");
            return "";
        }
        // puts("ya no se obtuvo la totales");
        // printf("totales %d\n", totales);
        while(totales!=0){
            *(nuevaCadena+i)= *(cadena+i);
            totales--;
            i++;
        }
        *(nuevaCadena+i)='\0';
        
    }
    return nuevaCadena;
}
char* obtenerSubfijo(char* cadena,int n){
    puts("obteneidneod subfijo........");
    char* nuevaCadena;
    int tamCadena = cadenaTam(cadena);
    if(n==tamCadena){
        nuevaCadena="λ";
    }else if(n==0){
        nuevaCadena=cadena;
    }else{
        int totales= tamCadena-n;
        nuevaCadena=(char*)malloc(totales);
        int i=0;
        if(nuevaCadena ==NULL){
            puts("----ERROR:ya no hay memoria paps");
            return "";
        }
        // printf("totales %d\n", totales);
        while(totales!=0){
            *(nuevaCadena+i)= *(cadena+i+n);
            totales--;
            i++;
        }
        *(nuevaCadena+i)='\0';
        
    }
    return nuevaCadena;
}
char* obtenerSubCadena(char* cadena,int p,int s){
    // printf("se recibio la cadena %s con  p %d  y s  %d",cadena,p,s);
    char* nuevaCadena;
    char* nuevaCadena1;
    int tamCadena= cadenaTam(cadena);
    // printf("el tamanio de la cadena es %d \n",tamCadena);
    if(p==0 && s==0){
        nuevaCadena=cadena;
    }else if(p==0){
        nuevaCadena=obtenerPrefijo(cadena,s);
    }else if (s==0){
        nuevaCadena=obtenerSubfijo(cadena,p);
    }else if (p+s==tamCadena){
        nuevaCadena="λ";
    }else{
        nuevaCadena= obtenerSubfijo(obtenerPrefijo(cadena,s),p);
    }
    return nuevaCadena;
}
char* obtenerSubsecuencia(char* cadena, int* indices, int tamIndices) {
    puts("obteneidneod subsecuencia........");
    int tamCadena = cadenaTam(cadena);

    int* indicesSinRepetidos = eliminarRepetidos(indices, tamIndices);
    int tamIndicesSinRepetidos = 0;
    while (indicesSinRepetidos[tamIndicesSinRepetidos] != -1) {
        tamIndicesSinRepetidos++;
    }

    char* nuevaCadena = (char*)malloc((tamCadena - tamIndicesSinRepetidos + 1) * sizeof(char));
    if (nuevaCadena == NULL) {
        puts("----ERROR: No hay memoria disponible");
        return "";
    }

    int j = 0;
    if(tamIndicesSinRepetidos==0){
        nuevaCadena= cadena;
    }else if(tamIndicesSinRepetidos==tamCadena){
        puts("lamda");
        nuevaCadena= "λ";
    }else{
        for (int i = 0; i < tamCadena; i++) {
            int eliminar = 0;
            for (int k = 0; k < tamIndicesSinRepetidos; k++) {
                if (i == indicesSinRepetidos[k]) {
                    eliminar = 1;
                    break;
                }
            }
            if (!eliminar) {
                *(nuevaCadena+j) = *(cadena+i);
                j++;
            }
        }
        nuevaCadena[j] = '\0';
    }
    return nuevaCadena;
}

char* elevaPotencia(char* cadena, int potencia) {
    int tamCadena = cadenaTam(cadena);
    char * aRetornar;
    if (potencia == 0) {
        char* nuevaCadena;
        if (nuevaCadena == NULL) {
            puts("----ERROR: No hay memoria disponible");
            return "";
        }
        aRetornar = "λ";
    }else{  
        char* cadenaAcopiar = cadena;
        if (potencia < 0) {
            cadenaAcopiar = invertirCadena(cadena);
            potencia = -potencia;
        }
        int nuevoTam = tamCadena * potencia;
        char* nuevaCadena = (char*)malloc(nuevoTam + 1);
        if (nuevaCadena == NULL) {
            puts("----ERROR: No hay memoria disponible");
            return "";
        }
        for (int i = 0; i < potencia; i++) {
            for (int j = 0; j < tamCadena; j++) {
                *(nuevaCadena+i * tamCadena + j) = *(cadenaAcopiar +j);
            }
        }
        
        *(nuevaCadena + nuevoTam) = '\0';
        aRetornar= nuevaCadena;
    }
    return aRetornar;
}

