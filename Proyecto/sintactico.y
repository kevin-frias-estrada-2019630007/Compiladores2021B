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
%left '*' '/'
%left '+' '-'


%type <num> NUMBER
%type <num> expresion_number
%type <var> VARIABLE
%type <var> STRING_LITERAL;

%union{
    int num;
    char var[30];
}

%%

input:
    %empty
    | expresion input
    ;

expresion :
         declaration 
        ;

declaration:
    tipo asignacion_variable ';' {printf("1.- Debemos obtener el tipo de dato con el que estamos trabajando \n");
                                  printf("2.- Checamos si es que tuvo una asignación o simplemente se declaró \n");
                                  printf("3.- Reservamos un espacio de memoria para poder guardar nuestra variable \n");
                                  }
    | CONST tipo asignacion_constante ';'
    | VARIABLE assing ';' {printf("There was an assing \n ");
        
    ;

tipo :
      INT
    | STRING
    ;

asignacion_variable :
      VARIABLE
    | VARIABLE '=' expresion_number
    | VARIABLE '=' STRING_LITERAL

    | VARIABLE ',' asignacion_variable

    | VARIABLE '=' expresion_number ',' asignacion_variable
    | VARIABLE '=' STRING_LITERAL  ',' asignacion_variable
    ;

asignacion_constante :
      VARIABLE '=' expresion_number
    | VARIABLE '=' STRING_LITERAL
    | VARIABLE '=' expresion_number ',' asignacion_constante
    | VARIABLE '=' STRING_LITERAL  ',' asignacion_constante
    ;

assing:
       '=' data
     | '=' data '+' data
     | '=' data assing
    ;

data:
    expresion_number
    | STRING_LITERAL
    | VARIABLE
    ;

expresion_number:
          NUMBER
        | expresion_number '*' expresion_number {$$ = $1 * $3;}
        | expresion_number '/' expresion_number {$$ = $1 / $3;}
        | expresion_number '+' expresion_number {$$ = $1 + $3;}
        | expresion_number '-' expresion_number {$$ = $1 - $3;}
        | '(' expresion_number ')'              {$$ = $2;}
        ;

%%

int yyerror(char *s){
 // printf("Syntax Error on line who knows xp %s\n", s);
}

int main(void){
    yyparse();
}
