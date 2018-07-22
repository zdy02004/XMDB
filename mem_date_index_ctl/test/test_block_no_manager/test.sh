#!/bin/sh
rm *core*
rm *.exe *.dat
clear
gcc test_block_no_manager.c  -I ../../  -lpthread -o test_block_no_manager.exe 
./test_block_no_manager.exe

#cat a.txt
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
#
#gcc mem_table_read_test.c  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
