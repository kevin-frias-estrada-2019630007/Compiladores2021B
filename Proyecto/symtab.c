#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

// La tabla de simbolos se implemento como un arreglo y cada posicion del arreglo una lista enlazada 

// Funcion para iniciar todas las posiciones del arreglo en un valor NULL haciendo un for
void init_hash_table(){
	for(int i = 0; i < SIZE; i++) hash_table[i] = NULL;
}

// Funcion para conseguir el valor del arreglo dependiendo de la llave de entrada en el parámetro de la función
unsigned int hash(char *key){
	unsigned int index = 0;

	for(; *key; key++) index += *key;
	index += key[0] % 11 + (key[0] << 3) - key[0];

	return index % SIZE;
}

// Insertamos dentro de nuestra tabla de simbolos, pidiendo el nombre del token, su tamaño, el tipo del token y la linea en la que se encontro
void insert(char *name, int len, int type, int lineno, int scopeI){
    // Obtenemos el valor del arreglo en donde ira nuestro dato
	unsigned int index = hash(name);

    // Buscamos si es que se encuentra o no nuestra key en la tabla
    nodo *l = buscar(name);
	
    // Si despues del buscar en nuestra tabla tenemos que el nodo es igual a NULL, significa que el token de entrada todavía no está en la tabla de simbolos
	if (l == NULL){
        // Creamos un nuevo nodo de nuestra lista 
		l = (nodo*) malloc(sizeof(nodo));

        // Le asignamos el nombre del nuestro token, el nombre que le damos a la variable, aka, yytext
        strncpy(l->nombre, name, len);


        // Decimos de que tipo fue el token que recivimos
		l->tipo = type;


        // Le asigamos un valor dummie, nos sirve para despues asignarle un valor a la variable de manera correcta
        l-> Ivalue = 0;
        l-> Cvalue = "";


        // Le asignamos el valor del scope de donde nos encontramos
        l->scope = scopeI;

        // Lo asignamos a la tabla hash
		hash_table[index] = l; 

        // Imprimimos mensaje de insertamos la variable en nuestr tabla hash y el número de la linea donde ocurrio
		//printf("\nInserted %s for the first time with linenumber %d!\n", name, lineno); 
	}
    // Ya esta en la tabla
    //	else printf("\n Found %s again at line %d! \n \n", name, lineno);
}

// Dentro de la funcion, regresamos el simbolo si es que encontramos el token de manera contraria regresamos NULL
nodo *buscar(char *name){
	unsigned int index = hash(name);
	nodo *l = hash_table[index];

    return l;
}

void imprimir(){
    for(int i = 0; i < SIZE; i++){
        if (hash_table[i] != NULL) {
	        nodo *l = hash_table[i];
            printf("Variable : %s  |  Scope : %d \n", l -> nombre, l -> scope);
        }
    }

}
