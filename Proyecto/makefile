default:
	clear
	flex -l lexico.l
	bison -dy sintactico.y 
	gcc y.tab.c lex.yy.c -lfl
    more test.c
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
    
    ./a.out < test.c
