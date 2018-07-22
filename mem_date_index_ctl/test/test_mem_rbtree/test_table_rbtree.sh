#!/bin/sh
rm *core*
rm *.exe *.dat
rm *2016*
clear
gcc mem_table_rbtree.c -g   -I ../../  -lpthread -o mem_table_rbtree.exe 
./mem_table_rbtree.exe >log.log
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_index_name_heap.dat 
#
#gcc mem_table_read_test.c -g  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
