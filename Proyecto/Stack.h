// Definimos el tipo de token que estamos ocupando
#include <stdlib.h>
#define UNDEF 0
#define _INT_ 1
#define _STR_ 2
#define _CHR_ 3
#define _LOGIC_ 4

typedef struct StackNode{
    char *data;
    struct StackNode * next;

}STN;

STN *crearNodo(char *entrada);
char *top();
void push(char *entrada);
char *pop();
void imprimir_stack();
