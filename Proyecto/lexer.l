%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symtab.h"
	#include "parser.tab.h"
	
	int lineno = 1;
%}

D ([0-9])
L ([a-zA-Z_])

VARIABLE 	{L}+({L}|{D})*
NUMBER		{D}+
STRINGF		(\"[ -~]*\")
CHARACTER	(\'[ -~](1)\')

%%

"\n"	            	{ lineno += 1; printf("\n"); }


"char"       	        { return CHAR;   }
"int"				    { return INT;    }
"string"	            { return STRING; }
"const"	                { return CONST; }


"if"		    		{ return IF;   }
"else"	    		    { return ELSE; }
"while"		    	    { return WHILE;}
"for"			    	{ return FOR;  }


"||"					{ return OR_OP;   }
"&&"					{ return AND_OP;  }
"=="|"!="				{ return EQ_OP;  }
">"|"<"|">="|"<="		{ return RE_OP;  }


";"					    { return(SEMI); }
"{"       				{ return(OPEN_BR); }
"}"     				{ return(CLOSE_BR); }
","				    	{ return(COMA); }
"="			    		{ return(ASSING); }
"("			    		{ return(OPEN_PR); }
")"		     			{ return(CLOSE_PR); }

"++"                    { return(UN_ADD);}
"--"                    { return(UN_SUB);}


"-"		    			{ return(SUB); }
"+"	    				{ return(ADD); }
"*"		    			{ return(MUL); }
"/" 					{ return(DIV); }



{VARIABLE} 	    	    {  insert(yytext, strlen(yytext), UNDEF, lineno, -1);
                           yylval.st_val = buscar(yytext);
                           return VARIABLE;
				        }

{NUMBER}            	{ yylval.int_val = atoi(yytext); 
                          return IVALUE;
                        }


{STRINGF} 		        { yylval.str_val = malloc(yyleng * sizeof(char));
                          strcpy(yylval.str_val, yytext);
                          return SVALUE;
                        }

{CHARACTER} 	        { yylval.char_val  = yytext[0]; 
                          return CVALUE;
                        }


[ \t\r\f]+	            {}
.			        	{}

%%

int yywrap(){
	return (1);
}
