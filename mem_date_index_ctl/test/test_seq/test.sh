#!/bin/sh
rm *core*
rm *.exe 
clear
gcc -g test_seq.c  -I ../../  -lpthread -o test_seq.exe 
./test_seq.exe

#cat a.txt
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
#
#gcc mem_table_read_test.c  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
