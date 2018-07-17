#!/bin/sh
#��ӹؼ���ʱ����Ҫͬʱȷ����3���ط�һ��
#parser.hh:195:     SKIPLIST = 433,
#parser.tab.c:754:     SKIPLIST = 433,
#parser.tab.h:217:     SKIPLIST = 433,

rm parser.tab.h
rm *core*
rm parser.tab.c
rm *.o
rm main
bison -d parser.y
rm parser.lex.h
rm lex.yy.c

flex -d  parser.l


g++ -g *.c -std=gnu++11 -o main
./main
