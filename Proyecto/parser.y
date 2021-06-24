%{
    #include "symtab.c"
    #include "Stack.c"
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #include <ctype.h>

    int yylex(void);
    void yyerror();
    void impS();
    char *to_string(int number);

    int scope = 0;

    // Cuando hacemos un scope--, tenemos que quitar todas esas variables referentes a ese scope

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

%right UN_ADD
%right UN_SUB

%right CLOSE_PR CLOSE_BR

%type <int_val> expresion_number
%type <str_val> tipo

%start input

%%

input: %empty
| expresion input
;

expresion : declaracion                                                                                               {printf("Hubo una declaracion \n");}
| asignar SEMI                                                                                                        {printf("Hubo una asignacion expresion \n");}

| IF OPEN_PR condicion CLOSE_PR OPEN_BR {scope++;} input CLOSE_BR  opcional_if                                         {printf("Hay un if \n");scope--;}

| WHILE OPEN_PR condicion CLOSE_PR OPEN_BR {scope++;} input CLOSE_BR                                                  {printf("Hay un loop while \n"); scope--;}
| FOR OPEN_PR {scope++;} tipo asignar SEMI condicion SEMI expresion_number CLOSE_PR OPEN_BR input CLOSE_BR            {printf("Hay un loop for con decl \n"); scope--;}
| FOR OPEN_PR {scope++;} asignar SEMI condicion SEMI expresion_number CLOSE_PR OPEN_BR input CLOSE_BR                 {printf("Hay un loop for sin decl\n");   scope--;}
;

opcional_if: %empty
|ELSE OPEN_BR {scope++;} input CLOSE_BR {printf("Hubo un else \n");scope--;}
;


declaracion :  tipo identificador SEMI              {push(";");}
| CONST INT  VARIABLE  ASSING expresion_number SEMI {printf("Declaración de un INT   CONSTANTE \n"); }
| CONST CHAR MUL VARIABLE ASSING SVALUE        SEMI {printf("Declaracion de un STRING CONSTANTE");}
;


identificador: VARIABLE inicializar { /*Aquí hay agregar la lógica para saber si ya está definida*/ push($1 -> nombre); $1 -> scope = scope;}
| VARIABLE inicializar COMA identificador {$1->scope = scope;}
;

inicializar: %empty
| ASSING data { push("="); }
;

asignar : VARIABLE ASSING data {push("="); $1 -> scope = scope;}

condicion: data operador_logico data ;


tipo : INT {push("INT");}
| STRING   {push ("STRING");}
| CHAR     {push("CHAR");}
;


operador_logico: OR_OP
| AND_OP              
| EQ_OP              
| RE_OP
;


data : expresion_number {push(to_string($1));}
| SVALUE                {push($1);}
| CVALUE MUL            {  char *temp = $1 + "";
                           push(temp); 
                           push("*");
                        }
;


expresion_number: IVALUE
| VARIABLE                              { 
                                          unsigned int index = hash($1->nombre);
                                          nodo *l = hash_table[index];
                                          if (l -> tipo == 0) $$ = $1 -> Ivalue;
                                          else $$ = 0;
                                            
                                          if (l->scope == -1) l -> scope = scope;
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

int contarI(int n){
    int cont = 0;

    while(n){
        cont ++;
        n /= 10;
    }

    return cont;
}

char *to_string(int number){

 char* s = (char*)malloc(sizeof(char)* (contarI(number) + 3));
 sprintf(s, "%d", number);

 return s;
}

int main(void){
    // Inicializamos nuestra hash table
    init_hash_table();

    // Hacemos el parseo
   yyparse();

  //  imprimir();
    printf("Top -> %s \n", top());
    imprimir_stack();


    return 0;
}
