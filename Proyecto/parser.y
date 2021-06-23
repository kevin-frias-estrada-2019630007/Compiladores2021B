%{
    #include "symtab.c"
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <ctype.h>

    int yylex(void);
    void yyerror();

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
%token '(' ')' '{' '}' 
%token '*' '/' '+' '-' '=' ';' ','

%token <st_val>        VARIABLE
%token <int_val>       IVALUE
%token <str_val>       SVALUE
%token <char_val>      CVALUE

%left  '(' ')'
%left  '*' '/'
%left  '+' '-'

%left  OR_OP
%left  AND_OP
%left  RE_OP
%left  EQ_OP
%right NOT_OP

%type <int_val> expresion_number

%start input

%%

input: %empty
| expresion input
;

expresion : declaracion                 {printf("Hubo una declaracion \n");}
| asignar   ';'                         {printf("Hubo una asignacion \n");}
| WHILE '(' condicion ')' '{' input '}' {printf("Hay un loop while \n");}
| IF    '(' condicion ')' '{' input '}' {printf("Hay un if \n");}
;


declaracion : tipo identificador ';'            
| CONST INT  VARIABLE  '=' expresion_number  ';' {printf("Declaración de un INT   CONSTANTE \n"); }
| CONST CHAR '*' VARIABLE '=' SVALUE         ';' {printf("Declaracion de un STRING CONSTANTE");}
;


identificador: VARIABLE inicializar
| VARIABLE inicializar ',' identificador
;

inicializar:
%empty
| '=' data {printf("Hubo una asignacion \n");}
;

asignar : VARIABLE '=' data
;


condicion: expresion_number operador_logico expresion_number {printf("Dentro de la condicion : %d  %d \n", $1, $3);};


tipo : INT
| STRING
| CHAR
;


operador_logico: OR_OP
| AND_OP
| NOT_OP
| EQ_OP
| RE_OP
;


data : expresion_number
| SVALUE
| CVALUE '*' { /*|VARIABLE */}
;


expresion_number: IVALUE {  /*| VARIABLE                              {$$ = sym[$1];} */ }
| '-' expresion_number                  {$$ = -$2; }
| expresion_number '+' expresion_number {$$ = $1 + $3; }
| expresion_number '-' expresion_number {$$ = $1 - $3; }
| expresion_number '*' expresion_number {$$ = $1 * $3; }
| expresion_number '/' expresion_number {$$ = $1 / $3; }
| '(' expresion_number ')'              {$$ = $2; }
;



%%

void yyerror () {
  printf("Syntax error \n");
  yyparse();
}

int main(int argc, char *argv[]){
    // Inicializamos nuestra hash table
    init_hash_table();

    // Hacemos el parseo
    yyparse();

    return 0;
}
