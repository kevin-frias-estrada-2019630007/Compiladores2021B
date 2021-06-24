#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define UNDEF 0
#define _INT_ 1
#define _STR_ 2
#define _CHR_ 3
#define _LOGIC_ 4

STN *head = NULL;
STN *ref = NULL;

int size_stack = 0;

STN *crearNodo(char *entrada){
    STN *nuevo = (STN *) malloc(sizeof(STN));
    nuevo -> data = entrada;
    nuevo -> next = NULL;
    nuevo -> prev = NULL;

    return nuevo;
}

char *top(){
    return ref -> data;
}


void push(char *entrada){
    STN *actual = crearNodo(entrada);

    if (head == NULL){ head = actual; ref = actual;}
    else{
         STN *temp = head;
         while(temp -> next != NULL) temp = temp -> next;
         temp -> next = actual;
         actual -> prev = temp;
         ref = actual;
      }

    size_stack ++;
}

void pop(){

    if (size_stack != 0) {
        ref = ref -> prev;
        ref -> next = NULL;
    }

    size_stack --;
}


void imprimir_stack(){
    STN *temp = ref;

    while(temp != NULL) {      
        printf("-- %s \n", temp -> data);
        temp = temp -> prev;
    }

}
