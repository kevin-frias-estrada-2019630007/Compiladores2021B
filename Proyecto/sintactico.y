%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int yylex(void);
int yyerror(char *s);
%}

%token VARIABLE NUMBER STRING_LITERAL 
%token EQ_OP DF_OP LE_OP GE_OP
%token INT STRING CONST CHAR
%token IF WHILE 
%token NEG 
%left '*' '/'
%left '+' '-'

%type <num> NUMBER
%type <var> VARIABLE
%type <var> STRING_LITERAL;
%type <num> expresion_number

%union{
    int num;
    char var[30];
}

%%

input: %empty
| expresion input
;

expresion : declaraciones
| VARIABLE inicializar ';'
| WHILE '(' condicion ')' '{' input '}'     {printf("Hay un loop while \n");}
| IF    '(' condicion ')' '{' input '}'     {printf("Hay un if \n");}
;


declaraciones: declaracion declaraciones
| declaracion
;


declaracion : tipo identificador ';'                            {printf("Hubo una declaracion \n");}
| CONST INT  VARIABLE  '=' expresion_number  ';' {printf("Declaración de un INT   CONSTANTE \n"); }
| CONST CHAR '*' VARIABLE '=' STRING_LITERAL ';'  {printf("Declaración de un STRING CONSTANTE \n"); }
;            


identificador: VARIABLE inicializar
| identificador ',' VARIABLE inicializar
;             

inicializar: %empty
| '=' data {printf("Hubo una asignacion \n");}
;           


condicion: data operador_logico data {printf("Condicion * \n");};


tipo : INT
| STRING
;


operador_logico: '>'
|'<'
| LE_OP
| GE_OP
| DF_OP
| EQ_OP
;


data : expresion_number
| STRING_LITERAL
| CHAR '*' { /*|VARIABLE */}
;


expresion_number: NUMBER {  /*| VARIABLE                              {$$ = sym[$1];} */ }
| '-' expresion_number                  {$$ = -$2; }
| expresion_number '+' expresion_number {$$ = $1 + $3; }
| expresion_number '-' expresion_number {$$ = $1 - $3; }
| expresion_number '*' expresion_number {$$ = $1 * $3; }
| expresion_number '/' expresion_number {$$ = $1 / $3; }
| '(' expresion_number ')'              {$$ = $2; }
;


%%

int yyerror(char *s){
 printf("Syntax Error\n");
 yyparse();
}

int main(void){
    yyparse();
}
