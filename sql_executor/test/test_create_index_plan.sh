#!/bin/sh

rm core*
rm make_create_index_plan
rm ../../SQL/sql_parser/main.o
  g++ -g test_create_index_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o make_create_index_plan -w  -lpthread 
./make_create_index_plan

