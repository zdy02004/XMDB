#!/bin/sh
rm parser.tab.h
rm *core*
rm parser.tab.c
bison -d parser.y
rm parser.lex.h
rm lex.yy.c

flex -d  parser.l


g++ -g *.c -std=gnu++11 -o main
./main
