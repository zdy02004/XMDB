#!/bin/sh

rm rollback* map_table* redo_index* redo_data*
rm core*
rm *.exe
rm *.dat
g++ -w  ops_test.cpp  -I ../../mem_date_index_ctl/ -g   -lpthread -std=c++11 -o  ops_test.exe
./ops_test.exe

