#!/bin/sh

rm core* *201*
rm make_create_index_plan test_table test_table_inx_array.dat test_table_inx_link.dat
rm ../../SQL/sql_parser/main.o
  g++ -g test_create_index_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o make_create_index_plan -w  -lpthread 
./make_create_index_plan

