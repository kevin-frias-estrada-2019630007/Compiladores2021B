	flex -l lexer.l
	bison -d parser.y
	gcc -o program parser.tab.c lex.yy.c -lfl
	rm lex.yy.c
	more example.c > output.txt
	./program < example.c >> output.txt
	rm program 
	rm parser.tab.h
	rm parser.tab.c
	more output.txt
