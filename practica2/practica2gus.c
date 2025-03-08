#include<stdio.h>
#include<stdlib.h>

#define TAM 100

typedef struct nodo{
	char* cadena;
	//unsigned long hash;
	struct nodo* next;
} Item;

typedef struct {
	Item* inicio;
	Item* final;
	int sizeCola;
} Cola;

//Funciones auxiliares
//unsigned long hash_cadena(char*);
void addItems(char*,Cola*);
char* string(char*,int,int);
int contarCadena(char*);
char* concatenar(char*,char*);
//Posibles funciones del hash
//int existeHash(Cola*,unsigned long hash);

//Funcines de la cola
void init(Cola*);
int isEmpy(Cola*);
void push(Cola*,char*);
Item *pop(Cola*);
void imprimir(Cola*);

//Operaciones con lenguajes
void imprimirLenguaje(Cola*);
Cola* unionLen(Cola*,Cola*);
Cola* concaLenguaje(Cola*,Cola*);
Cola* reflexion(Cola*);
Cola* potenciaLenguaje(Cola*,int);

int main(){
	char L1[TAM];
	char L2[TAM];
	Cola* resuld = NULL;
	int opc = 0;
	int potencia = 0;
	Cola* colaL1 = (Cola*)malloc(sizeof(Cola));
	Cola* colaL2 = (Cola*)malloc(sizeof(Cola));
	init(colaL1);
	init(colaL2);
	printf("Dijite el lenguaje L1: ");
	scanf("%[^\n]",L1);
	getchar();
	printf("Dijite el lenguaje L2: ");	
	scanf("%[^\n]",L2);
	system("clear");
	addItems(L1,colaL1);
	addItems(L2,colaL2);
	//imprimir(colaL1);
	do{
		printf("---PRACTICA 2 OPERACIONES ENTRE LENGUAJES---\n");unsigned long hash;
		printf("El lenguaje L1 es: [%s] \n",L1);
		printf("El lenguaje L2 es: [%s] \n",L2);
		printf("1. Union\n");
		printf("2. Concatenacion\n");
		printf("3. Potencia\n");
		printf("4. Reflexion\n");
		printf("5. Salir\n");
		printf("Elija una opcion: ");
		scanf("%d",&opc);
		switch(opc){
			case 1:
				resuld = unionLen(colaL1,colaL2);
				printf("El resultado de la union de L1 con L2 es: ");
				imprimirLenguaje(resuld);
				//printf("Se imprime toda la cola\n");
				//imprimir(resuld);
				//printf("El resultado de la union de L1 y L2 es: [%s]\n",resuld);
				break;
			case 2:
				printf("1. Concatenar L1 con L2\n");
				printf("2. Concatenar L2 con L1\n");
				printf("Eiga uno de los dos lenguajes: ");
				scanf("%d",&opc);
				if(opc==1){
					resuld = concaLenguaje(colaL1,colaL2);
				} else {
					resuld = concaLenguaje(colaL2,colaL1);
				}
				printf("El resultado de la concatenacion es: ");
				imprimirLenguaje(resuld);
				break;
			case 3:
				printf("1. Potencia para L1\n");
				printf("2. Potencia para L2\n");
				printf("Eiga uno de los dos lenguajes: ");
				scanf("%d",&opc);

				printf("Potencia: ");
				scanf("%d",&potencia);
				if(opc==1){
					resuld = potenciaLenguaje(colaL1,potencia);
				} else {
					resuld = potenciaLenguaje(colaL2,potencia);
				}
				printf("El resultado de la potencia es: ");
				imprimirLenguaje(resuld);
				break;
			case 4:
				printf("1. Reflexion para L1\n");
				printf("2. Reflexion para L2\n");
				printf("Eiga uno de los dos lenguajes: ");
				scanf("%d",&opc);
				if(opc==1){
					resuld = reflexion(colaL1);
				} else {
					resuld = reflexion(colaL2);
				}
				printf("El resultado de la reflexion es: ");
				imprimirLenguaje(resuld);
				break;
		}
	}while(opc!=5);
}

//Funciones auxiliares
unsigned long hash_cadena(char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

char* string(char* lenguaje,int inicio,int final){
	int aux = (final-inicio) + 1;
	char* resuld = (char*)malloc((aux+1));
	for(int i = 0;i < aux;i++){
		//printf("El caracer es: %c\n",lenguaje[inicio+i]);
		resuld[i] = lenguaje[inicio+i];
	}
	resuld[aux] = '\0';
	return resuld;
}

char* inversa(char* cadena){
	int tam = contarCadena(cadena);
	char* resuld = (char*)malloc((tam+1));
	int aux = tam - 1;
	for(int i=0;i<tam;i++){
		resuld[i] = cadena[aux - i];
	}
	resuld[tam] = '\0';
	return resuld;
}

char* concatenar(char* cadena1,char* cadena2){
	int tamCadena1 = contarCadena(cadena1);	
	int tamCadena2 = contarCadena(cadena2);
	int totalCadena = tamCadena1+tamCadena2;
	char *apt = (char*)malloc((totalCadena+1));
	
	for(int i=0;i<tamCadena1;i++){
		*(apt+i) = *(cadena1+i);
	}

	for(int i=0;i < tamCadena2;i++){
		*(apt+tamCadena1+i) = *(cadena2+i);
	}

	*(apt + totalCadena) = '\0';

	return apt;
}

void addItems(char* lenguaje,Cola* cola){
	int i=0;
	int inicio=0;
	int final=0;
	char* aux = lenguaje;
	Item* nodo;
	while(lenguaje[i]){
		if(lenguaje[i]==',' || lenguaje[i+1] == '\0'){
			if (lenguaje[i+1] == '\0') {
                final++;
            }
			aux = string(lenguaje,inicio,final-1);
			//nodo->hash = hash_cadena(aux);
			push(cola,aux);
			//printf("El elemento es: %s\n",aux);
			inicio = final+1;
		}
		final++;
		i++;
	}
}

int comparar_cadenas(char* str1, char* str2) {
	const char* p1 = str1;
    const char* p2 = str2;
	
	//printf("Comparando '%s' con '%s'\n", str1, str2);
    while (*p1 && (*p1 == *p2)) {
        p1++;
        p2++;
    }
	int resultado = *(unsigned char*)p1 - *(unsigned char*)p2;
	//printf("Resultado de la comparación: %d\n", resultado);
	return resultado;
}

int existe_en_cola(Cola* cola, char* cadena) {
    Item* actual = cola->inicio;
    while (actual != NULL) {
		//printf("Verificando si '%s' existe en la cola: comparando con '%s'\n", cadena, actual->cadena);
        if (comparar_cadenas(actual->cadena, cadena) == 0) {
			//printf("La cadena '%s' ya existe en la cola\n", cadena);
            return 1;
        }
        actual = actual->next;
    }
	//printf("La cadena '%s' no existe en la cola\n", cadena);
    return 0;
}

//Posible funciones del hash
//int existeHash(Cola* cola,unsigned long hash){
//	Item* aux = cola->inicio;
//	while(aux!=NULL){
//		if(hash==aux->hash){
//			return 1;
//		}
//		aux = aux->next;
//	}
//	return 0;
//}

//Operaciones de la cola
void init(Cola* cola){
	cola->sizeCola = 0;
	cola->inicio = NULL;
	cola->final = NULL;
}

int isEmpy(Cola* cola){
	return cola->sizeCola==0;
}

void push(Cola* cola,char* cadena){
	Item* item = (Item*)malloc(sizeof(Item));
	item->next = NULL;
	item->cadena = cadena;
	if(isEmpy(cola)){
		cola->inicio = item;
		cola->final = item;
	} else {
		cola->final->next = item;
		cola->final = item;
	}
	cola->sizeCola++;
}

Item* pop(Cola* cola){
	Item* item = NULL;	
	if(!isEmpy(cola)){
		item = cola->inicio;
		cola->inicio = item->next;
		item->next = NULL;
	}
	return item;
}

void imprimir(Cola* cola){
	Item* aux = cola->inicio;
	while(aux!=NULL){
		printf("----\n");
		printf("Cadena: %s\n",aux->cadena);
		//printf("Cadena: %s Clave:%lu\n",aux->cadena,aux->hash);
		aux = aux->next;
	}
	printf("----\n");
}

int contarCadena(char* cadena){
	int i=0;
	while(cadena[i]){
		i++;
	}
	return i;
}

void imprimirLenguaje(Cola* cola){
	Item* aux = cola->inicio;
	printf("[");
	while(aux->next){
		printf("%s,",aux->cadena);
		aux = aux->next;
	}
	printf("%s]\n",aux->cadena);
}

Cola* unionLen(Cola* len1,Cola* len2){
	Cola* resuld = (Cola*)malloc(sizeof(Cola));
	init(resuld);
	Item* aux = len1->inicio;
	while(aux!=NULL){
		push(resuld,aux->cadena);
		aux = aux->next;
	}
	aux = len2->inicio;
	while(aux!=NULL){
		if(!existe_en_cola(resuld,aux->cadena)){
			push(resuld,aux->cadena);
			//printf("Entro a la condicion hago push");
		} else {
			//printf("No agregado, ya existe en resuld: %s\n", aux->cadena);
		}
		aux = aux->next;
	}
	return resuld;
}


Cola* concaLenguaje(Cola* len1,Cola* len2){
	Cola* result = (Cola*)malloc(sizeof(Cola));
	init(result);
	Item* aux = len1->inicio;
	Item* aux2 = len2->inicio;
	char* cadena;
	if (comparar_cadenas(len1->inicio->cadena, " ") == 0) {
        push(result, " ");
		return result;
    }

	if (comparar_cadenas(len2->inicio->cadena, " ") == 0) {
        push(result, " ");
		return result;
    }

	while(aux!=NULL){
		aux2 = len2->inicio;
		while(aux2!=NULL){
			cadena = concatenar(aux->cadena,aux2->cadena);
			//printf("La cadena a meter es: %s\n",cadena);
			if(!existe_en_cola(result,cadena)){
				push(result,cadena);
			} else {
				//printf("No agregado, ya existe en resuld: %s\n", aux->cadena);
			}
			aux2 = aux2->next;
		}
		aux = aux->next;
	}
	return result;
}

Cola* reflexion(Cola* len){
	Cola* result = (Cola*)malloc(sizeof(Cola));
	init(result);
	Item* aux = len->inicio;
	char* cadena;
	while(aux!=NULL){
		cadena = inversa(aux->cadena);
		push(result,cadena);
		aux = aux->next;
	}
	return result;
}

Cola* potenciaLenguaje(Cola* len,int potencia){
	Cola* result = len;
	Cola* aux = len;
	if(potencia > 0){
		for(int i=1;i < potencia;i++){
			result = concaLenguaje(aux,len);
			aux = result;
			//printf("Potencia %d",i+1);
		}
	} else if(potencia == 0){
		result = (Cola*)malloc(sizeof(Cola));
		push(result,"Lamba");
	} else {
		int potenciaPositiva = potencia*-1;
		printf("%d\n",potenciaPositiva);
		for(int i=1;i < potenciaPositiva;i++){
			result = concaLenguaje(aux,len);
			aux = result;
		}
		result = reflexion(aux);
	}

	return result;
}

//optimizacion
