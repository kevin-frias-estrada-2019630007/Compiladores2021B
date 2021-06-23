// Tamaño maximo del arreglo para nuestra tabla hash, este tiene que ser un número primo
#define SIZE 499

// Tamaño maximo del nombre de nuestro token
#define SZTOKEN 60

// Definimos el tipo de token que estamos ocupando
#define UNDEF 0
#define INT_TYPE 1
#define STR_TYPE 2
#define LOGIC_TYPE 3

// struct that represents a list node
typedef struct nodo{
    // El nombre de nuestro token, aka, yytext
	char nombre[SZTOKEN];
	// type
    int tipo;

    // valor
    int valor;

}nodo;


// Nuestra tabla hash, ocupamos un arreglo de apuntador a nodo
nodo *hash_table[SIZE];

// ----------------------  Funciones de nuestra tabla hash -------------------------------------------- //

// Funcion para iniciar nuestra tabla hash en valores NULL
void init_hash_table();

// Funcion para conseguir el index donde vamos a trabajar nuesta key
unsigned int hash(char *key);

// Insertamos el valor en la tabla hash
void insert(char *name, int len, int type, int lineno); 

// Funcion para buscar si es que nuestra llave ya existe dentro de la tabla
nodo *buscar(char *name); 


void imprimir();
