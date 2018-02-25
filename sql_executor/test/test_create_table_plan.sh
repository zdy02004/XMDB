#!/bin/sh

rm core*
rm make_create_table_plan
rm ../../SQL/sql_parser/main.o
  g++ -g test_create_table_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o make_create_table_plan -w  -lpthread 
./make_create_table_plan

