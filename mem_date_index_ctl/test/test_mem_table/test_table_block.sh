#!/bin/sh
rm *core*
rm *.exe *.dat
clear
gcc mem_table_test.c  -I ../../  -lpthread -o mem_table_test.exe 
./mem_table_test.exe
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat

gcc mem_table_read_test.c  -I ../../  -lpthread -o mem_table_read_test.exe 
./mem_table_read_test.exe
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
