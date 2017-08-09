#!/bin/sh

rm *201* core.* *.dat skiplist_range_test.exe
g++ -w  skiplist_range_test.cpp  -I ../../mem_date_index_ctl/ -g   -lpthread -std=c++11 -o  skiplist_range_test.exe
./skiplist_range_test.exe
