// Tamaño maximo del arreglo para nuestra tabla hash, este tiene que ser un número primo
#define SIZE 499

// Definimos el tipo de token que estamos ocupando
#define UNDEF 0
#define _INT_ 1
#define _STR_ 2
#define _CHR_ 3
#define _LOGIC_ 4

// struct that represents a list node
typedef struct nodo{
    // El nombre de nuestro token, aka, yytext
	char nombre[100];
	// type
    int tipo;

    // valor del token
    int   Ivalue;
    char *Cvalue;

    // scope
    int scope;

}nodo;


// Nuestra tabla hash, ocupamos un arreglo de apuntador a nodo
nodo *hash_table[SIZE];

// ----------------------  Funciones de nuestra tabla hash -------------------------------------------- //

// Funcion para iniciar nuestra tabla hash en valores NULL
void init_hash_table();

// Funcion para conseguir el index donde vamos a trabajar nuesta key
unsigned int hash(char *key);

// Insertamos el valor en la tabla hash
void insert(char *name, int len, int type, int lineno, int scopeI); 

// Funcion para buscar si es que nuestra llave ya existe dentro de la tabla
nodo *buscar(char *name); 

// Con esta funcion imprimimos toda la informacion dentro de la tabla de simbolos
void imprimir();
