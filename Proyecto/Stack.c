#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define UNDEF 0
#define _INT_ 1
#define _STR_ 2
#define _CHR_ 3
#define _LOGIC_ 4

STN *head = NULL;

int size_stack = 0;

STN *crearNodo(char *entrada){
    STN *nuevo = (STN *) malloc(sizeof(STN));
    nuevo -> data = entrada;
    nuevo -> next = NULL;

    return nuevo;
}

char *top(){
    return head -> data;
}


void push(char *entrada){
    STN *actual = crearNodo(entrada);

    if (head == NULL) head = actual;
    else{
        STN *temp = head;
        while(temp -> next != NULL) temp = temp -> next;
        temp -> next = actual;
    }

    size_stack ++;
}

char *pop(){
    STN *temp = head;
    head = head -> next;

    size_stack --;

    return temp -> data;
}


void imprimir_stack(){
    STN *temp = head;

    while(temp != NULL) {      
        printf("-- %s \n", temp -> data);
        temp = temp -> next;
    }
}
