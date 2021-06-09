%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
void count();
void comment();
%}

D ([0-9])
L ([a-zA-Z_])
S [ \t\v\b\f]

%%

"/*"					{comment();}
"if"					{count(); return(IF);}
"int"					{count(); return(INT);}
"string"				{count(); return(STRING);}
"while"					{count(); return(WHILE);}
"const"					{count(); return(CONST);}

{L}({L}|{D})*			{count(); strcpy(yylval.var, yytext); return(VARIABLE);}
{D}+					{count(); yylval.num = atoi(yytext); return(NUMBER);}
L?\"(\\.|[^\\"])*\"		{count(); strcpy(yylval.var, yytext); return(STRING_LITERAL); }

";"					    {count(); return(';'); }
"{"       				{count(); return('{'); }
"}"     				{count(); return('}'); }
","				    	{count(); return(','); }
"="			    		{count(); return('='); }
"("			    		{count(); return('('); }
")"		     			{count(); return(')'); }
"-"		    			{count(); return('-'); }
"+"	    				{count(); return('+'); }
"*"		    			{count(); return('*'); }
"/" 					{count(); return('/'); }
"=="					{count(); return(EQ_OP); }
"<"				    	{count(); return('<'); }
">"			    		{count(); return('>'); }
{S}		    			{}
.	    				{}

%%

int yywrap(){
	return (1);
}

void comment() {
/*
	char c, c1;
loop:
	while ((c = input()) != '*' && c != 0) {}//putchar(c);

	if ((c1 = input()) != '/' && c != 0){
//		unput(c1);
		goto loop;
	}
*/
/*
	if (c != 0)
		putchar(c1);
*/
}

int column = 0;

void count(){
/*
	int i;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n') column = 0;
		else if (yytext[i] == '\t') column += 8 - (column % 8);
		else column++;
*/
//	ECHO;
//	printf(" ");
}

