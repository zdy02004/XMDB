#!/bin/sh

rm core*
rm make_query_plan
rm ../../SQL/sql_parser/main.o
  g++ -g test_make_query_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o make_query_plan -w  -lpthread 
./make_query_plan

