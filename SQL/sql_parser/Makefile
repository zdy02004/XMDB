LEX=flex  
YACC=bison  
CC=g++  
STD=gnu++11
OBJECT=main #生成的目标文件  
  
$(OBJECT): lex.yy.o  parser.tab.o NonReservedKeyword.o main.o 
	$(CC) lex.yy.o parser.tab.o NonReservedKeyword.o main.o -o $(OBJECT)  -std=$(STD)

main.o:  main.c  parser.hh query_analyser.hpp
	$(CC) -c main.c  -std=$(STD)

lex.yy.o: lex.yy.c parser.tab.h parser.hh
	$(CC) -c lex.yy.c -std=$(STD)

NonReservedKeyword.o: NonReservedKeyword.c parser.hh
	$(CC) -c NonReservedKeyword.c -std=$(STD)
  
parser.tab.o: parser.tab.c  parser.hh
	$(CC) -c parser.tab.c -std=$(STD)
  
parser.tab.c  parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c  sql_parser.lex.h: parser.l
	$(LEX) -d  parser.l

clean:
	@rm -f $(OBJECT)  *.o parser.tab.c  parser.tab.h lex.yy.c  sql_parser.lex.h *.output *.core.*
