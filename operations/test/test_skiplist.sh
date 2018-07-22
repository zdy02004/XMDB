#!/bin/sh

rm *201* core.* *.dat skiplist_index_test.exe
g++ -w  skiplist_index_test.cpp  -I ../../mem_date_index_ctl/ -g   -lpthread -std=c++11 -o  skiplist_index_test.exe
./skiplist_index_test.exe
