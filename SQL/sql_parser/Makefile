EX=flex  
YACC=bison  
CC=g++  
OBJECT=main #生成的目标文件  
  
$(OBJECT): lex.yy.o  parser.tab.o NonReservedKeyword.o
	$(CC) lex.yy.o parser.tab.o NonReservedKeyword.o -o $(OBJECT)  -std=c++11
  
lex.yy.o: lex.yy.c parser.tab.h parser.hh
	$(CC) -c lex.yy.c -std=c++11

NonReservedKeyword.o: NonReservedKeyword.c parser.hh
	$(CC) -c NonReservedKeyword.c -std=c++11
  
parser.tab.o: parser.tab.c  parser.hh
	$(CC) -c parser.tab.c -std=c++11
  
parser.tab.c  parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c  sql_parser.lex.h: parser.l
	$(LEX) -d  parser.l

clean:
	@rm -f $(OBJECT)  *.o parser.tab.c  parser.tab.h lex.yy.c  sql_parser.lex.h *.output
