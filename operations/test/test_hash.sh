#!/bin/sh

rm *201* core.* *.dat mem_hash_table_test.exe
g++ -w  mem_hash_table_test.cpp  -I ../../mem_date_index_ctl/ -g   -lpthread -std=c++11 -o  mem_hash_table_test.exe
./mem_hash_table_test.exe
