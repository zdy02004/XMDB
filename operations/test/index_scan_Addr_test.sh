#!/bin/sh

rm *201* core.* *.dat *.exe
g++ -w  index_scan_Addr_test.cpp  -I ../../mem_date_index_ctl/ -g   -lpthread -std=c++11 -o  index_scan_Addr_test.exe
./index_scan_Addr_test.exe
