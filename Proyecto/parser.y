%{
    #include "symtab.c"
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <ctype.h>

    int yylex(void);
    void yyerror();
    void impS();

    int scope = 0;

%}

%union{
    char  char_val;
	int   int_val;
	char* str_val;
	nodo* st_val;
}

/* Definicion de nuestros tokens */
%token INT STRING CHAR CONST IF ELSE WHILE FOR 

%token OR_OP AND_OP NOT_OP EQ_OP RE_OP
%token UN_ADD UN_SUB

%token OPEN_PR CLOSE_PR OPEN_BR CLOSE_BR
%token MUL DIV ADD SUB ASSING SEMI COMA

%token <st_val>        VARIABLE
%token <int_val>       IVALUE
%token <str_val>       SVALUE
%token <char_val>      CVALUE

%left  OPEN_PR OPEN_BR
%left  MUL DIV
%left  ADD SUB

%left  OR_OP
%left  AND_OP
%left  RE_OP
%left  EQ_OP

%right NOT_OP
%right UN_ADD
%right UN_SUB

%right CLOSE_PR CLOSE_BR

%type <int_val> expresion_number

%start input

%%

input: %empty
| expresion input
;

expresion : declaracion                                                                                               {printf("Hubo una declaracion \n");}
| asignar SEMI                                                                                                        {printf("Hubo una asignacion \n");}

| IF OPEN_PR condicion CLOSE_PR OPEN_BR {scope++;}input CLOSE_BR  opcional_if                                         {printf("Hay un if \n");scope--;}

| WHILE OPEN_PR condicion CLOSE_PR OPEN_BR {scope++;} input CLOSE_BR                                                  {printf("Hay un loop while \n"); scope--;}
| FOR OPEN_PR {scope++;} tipo asignar SEMI condicion SEMI expresion_number CLOSE_PR OPEN_BR input CLOSE_BR            {printf("Hay un loop for \n");   scope--;}
| FOR OPEN_PR {scope++;} asignar SEMI condicion SEMI expresion_number CLOSE_PR OPEN_BR input CLOSE_BR                 {printf("Hay un loop for \n");   scope--;}
;

opcional_if: %empty
|ELSE OPEN_BR {scope++;} input CLOSE_BR {printf("Hubo un else \n");scope--;}
;


declaracion :  tipo identificador SEMI              {impS();}
| CONST INT  VARIABLE  ASSING expresion_number SEMI {impS(); printf("Declaración de un INT   CONSTANTE \n"); }
| CONST CHAR MUL VARIABLE ASSING SVALUE        SEMI {impS(); printf("Declaracion de un STRING CONSTANTE");}
;


identificador: VARIABLE inicializar
| VARIABLE inicializar COMA identificador
;

inicializar: %empty
| ASSING data {printf("Hubo una asignacion \n");}
;

asignar : VARIABLE ASSING data {impS(); printf("Hubo una asignacion \n");}
;

condicion: expresion_number operador_logico expresion_number            {printf("Hubo una condicion \n");}
|  NOT_OP expresion_number  operador_logico expresion_number            {printf("Hubo una condicion \n");}
|  NOT_OP expresion_number  operador_logico  NOT_OP expresion_number    {printf("Hubo una condicion \n");}
|  expresion_number  operador_logico  NOT_OP expresion_number           {printf("Hubo una condicion \n");}
;


tipo : INT
| STRING
| CHAR
;


operador_logico: OR_OP
| AND_OP
| EQ_OP
| RE_OP
;


data : expresion_number
| SVALUE
| CVALUE MUL
;


expresion_number: IVALUE
| VARIABLE                              { 
                                          unsigned int index = hash($1->nombre);
                                          nodo *l = hash_table[index];
                                          if (l -> tipo == 0) $$ = $1 -> valor;
                                          else $$ = 0;
                                        }

| SUB expresion_number                  {$$ = -$2; }
| UN_ADD expresion_number               {$$ = $2 + 1; }
| UN_SUB expresion_number               {$$ = $2 - 1; }
| expresion_number ADD expresion_number {$$ = $1 + $3; }
| expresion_number SUB expresion_number {$$ = $1 - $3; }
| expresion_number MUL expresion_number {$$ = $1 * $3; }
| expresion_number DIV expresion_number {$$ = $1 / $3; }
| OPEN_PR expresion_number CLOSE_PR     {$$ = $2; }
;



%%

void yyerror () {
  printf("Syntax error \n");
  exit(1);
}

void impS(){
    printf("Scope actual : %d \n", scope);
}

int main(int argc, char *argv[]){
    // Inicializamos nuestra hash table
    init_hash_table();

    // Hacemos el parseo
    yyparse();

    imprimir();

    return 0;
}
