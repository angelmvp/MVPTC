#include<stdio.h>
#include<stdlib.h>

char* concatenar(char* cadena1,char* cadena2);
int cadenaTam(char*cadena);
int validacionCadenaTam(char* cadena,int n);
void imprimirArreglo(int* arreglo);
int* eliminarRepetidos(int* arreglo, int tam);
char* invertirCadena(char* cadena);
char* copiarCadena(char* cadena);

char* concatenar(char* cadena1,char* cadena2){
    char* nuevaCadena = (char*)malloc(cadenaTam(cadena1)+cadenaTam(cadena2)+1);
    if(nuevaCadena ==NULL){
        puts("----ERROR:ya no hay memoria papspaps");
        return "";
    }
    int i=0,j=0;
    while(*(cadena1+i)){
        *(nuevaCadena+i)=*(cadena1+i);
        i++;
    }
    while(*(cadena2+j)){
        *(nuevaCadena+i+j)=*(cadena2+j);
        j++;
    }
    *(nuevaCadena+i+j)='\0';
    //printf("%s\n",nuevaCadena);
    return nuevaCadena;
}
int cadenaTam(char* cadena){
    int i=0;
    while(*(cadena+i)!='\0'){
        i++;
    }
    return i;
}
int validacionCadenaTam(char* cadena,int n){
    return n<=cadenaTam(cadena);
}
int* eliminarRepetidos(int* arreglo, int tam) {
    int* nuevoArreglo = (int*)malloc(tam * sizeof(int));
    if (nuevoArreglo == NULL) {
        puts("----ERROR: ya no hay memoria paps");
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < tam; i++) {
        int repetido = 0;
        for (int k = 0; k < j; k++) {
            if (arreglo[i] == nuevoArreglo[k]) {
                repetido = 1;
                break;
            }
        }
        if (!repetido) {
            nuevoArreglo[j] = arreglo[i];
            j++;
        }
    }
    nuevoArreglo[j] = -1;
    return nuevoArreglo;
}
char* invertirCadena(char* cadena){    
    int tam=cadenaTam(cadena);
    int i=0;
    char* nuevaCadena= (char *)malloc(tam+1);
    if(nuevaCadena ==NULL){
        puts("----ERROR:ya no hay memoria paps");
        return "";
    }
    while(tam!=0){
        *(nuevaCadena+i)= *(cadena+tam-1);
        tam--;
        i++;
    }
    *(nuevaCadena+i)='\0';
    return nuevaCadena;   
}


char* copiarCadena(char* cadena){
    int tam=cadenaTam(cadena);
    char* nuevaCadena = (char* )malloc(tam+1);
    int i=0;
    while (tam!=0){
        *(nuevaCadena + i) = *(cadena+i);
        tam--;
        i++;
    }
    nuevaCadena[i]='\0';
    //printf("cadnea retornada %s: \n", nuevaCadena);
    return nuevaCadena  ;  
}
int cadenasIguales(char* cadena1,char* cadena2){
    int iguales;
    while (*cadena1 && *cadena2) {
        if (*cadena1 != *cadena2) {
            return 0; 
        }
        cadena1++;
        cadena2++;
    }
    if(*cadena1==*cadena2){
        iguales=1;
    }else{
        iguales=0;
    }
    return iguales;
}



int charToInt(char* num){
    int i=0;
    int numero=0;
    numero=numero*10+(*(num)-'0');
    return numero;
}