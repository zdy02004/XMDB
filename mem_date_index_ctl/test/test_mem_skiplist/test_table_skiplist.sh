#!/bin/sh
rm *core*
rm *.exe *.dat
rm *201*
clear
gcc mem_table_skiplist.c -g   -I ../../  -lpthread -o mem_table_skiplist.exe 
./mem_table_skiplist.exe >log.log
cat log.log
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_index_name*.dat 
#
#gcc mem_table_read_test.c -g  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
