#!/bin/sh
rm *core*
rm *.exe *.dat
clear
gcc mem_rbtree_iterator.c    -I ../../  -lpthread -o mem_rbtree_iterator.exe 
./mem_rbtree_iterator.exe
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_index_name_heap.dat 
#
#gcc mem_table_read_test.c  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
