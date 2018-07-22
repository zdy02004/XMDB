#!/bin/sh

rm core*
rm oper_fun
rm ../../SQL/sql_parser/main.o
 g++ -g test_fun_oper.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o oper_fun -w  -lpthread 
./oper_fun
