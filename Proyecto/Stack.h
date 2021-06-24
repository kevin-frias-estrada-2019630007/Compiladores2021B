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
    struct StackNode * prev;

}STN;

STN *crearNodo(char *entrada);
char *top();
void push(char *entrada);
void pop();
void imprimir_stack();
