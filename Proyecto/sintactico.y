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

expresion : declaration 
;

declaration: tipo  asignacion  ';'               {printf("Declaración de un INT o STRING \n"); }
| CONST INT  VARIABLE  '=' expresion_number  ';' {printf("Declaración de un INT   CONSTANTE \n"); }
| CONST CHAR '*' VARIABLE '=' STRING_LITERAL ';' {printf("Declaración de un STRING CONSTANTE \n"); }
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
| CHAR '*'
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
