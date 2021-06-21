%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
void comment();
%}

D ([0-9])
L ([a-zA-Z_])
S [ \t\v\b\f]

%%

"/*"					{comment();}
"if"					{return(IF);}
"int"					{return(INT);}
"string"				{return(STRING);}
"while"					{return(WHILE);}
"const"					{return(CONST);}

{L}({L}|{D})*			{strcpy(yylval.var, yytext); return(VARIABLE);}
{D}+					{yylval.num = atoi(yytext);  return(NUMBER);}
L?\"(\\.|[^\\"])*\"		{strcpy(yylval.var, yytext); return(STRING_LITERAL);}

";"					    {return(';');}
"{"       				{return('{');}
"}"     				{return('}');}
","				    	{return(',');}
"="			    		{return('=');}
"("			    		{return('(');}
")"		     			{return(')');}
"-"		    			{return('-');}
"+"	    				{return('+');}
"*"		    			{return('*');}
"/" 					{return('/');}

"=="					{return(EQ_OP);} 
"!="					{return(DF_OP);} 
">="					{return(GE_OP);} 
"<="					{return(LE_OP);} 
"<"				    	{return('<');}
">"			    		{return('>');}



{S}		    			{}
.	    				{}

%%

int yywrap(){
	return (1);
}

void comment() {
}
