#!/bin/sh
rm *core*
rm *.exe *.dat
clear
gcc mem_hash_table.c   -I ../../  -lpthread -o mem_hash_table.exe 
./mem_hash_table.exe
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_hash_name_array.dat
echo "--------------------------------------------------------------------------"
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"' ./first_hash_name_link.dat

#
#gcc mem_table_read_test.c  -I ../../  -lpthread -o mem_table_read_test.exe 
#./mem_table_read_test.exe
#ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
