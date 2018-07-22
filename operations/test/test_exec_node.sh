#!/bin/sh

rm rollback* map_table* redo_index* redo_data*
rm core*
rm *.exe
rm *.dat

g++ -w -std=c++11 -O3 -lpthread exec_node_test.cpp -g -o test_exec_node.exe
./test_exec_node.exe

