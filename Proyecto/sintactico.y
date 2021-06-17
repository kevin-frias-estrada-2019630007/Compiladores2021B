%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int yylex(void);
int yyerror(char *s);
%}

%token VARIABLE NUMBER STRING_LITERAL 
%token EQ_OP
%token INT STRING CONST
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

expresion : declaration 
;

declaration:
tipo  asignacion ';' {printf("\n1.- Debemos obtener el tipo de dato con el que estamos trabajando \n");
                      printf("2.- Reservamos un espacio de memoria para poder guardar nuestra variable \n");                 
                     }
;

tipo : INT
| STRING
;

asignacion : VARIABLE
| VARIABLE '=' data
| VARIABLE '=' data ',' asignacion
| VARIABLE '=' VARIABLE
| VARIABLE '=' VARIABLE ',' asignacion
;



data : expresion_number
| STRING_LITERAL
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
}

int main(void){
    yyparse();
}
