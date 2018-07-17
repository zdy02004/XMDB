#!/bin/sh
rm *core*
rm *.exe *.dat
rm *2017*
clear
gcc mutlthread_skiplist_test.c -g   -I ../../  -lpthread -o mutlthread_skiplist.exe 
./mutlthread_skiplist.exe > log.log
tail -1000f log.log
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_index_name_heap.dat 
#
#gcc mem_table_read_test.c -g  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_index_name_skip.dat
