#!/bin/sh

rm core* *201*
rm *.dat
rm ../../SQL/sql_parser/main.o
rm delete_one_table
  g++ -g test_delete_one_table.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o delete_one_table -w  -lpthread 
./delete_one_table
 hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' test_table.dat
