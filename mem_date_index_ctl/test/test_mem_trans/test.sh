#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *2016*
rm redo*
clear
gcc mem_trans_test.c -g  -I ../../  -lpthread -o mem_trans_test.exe 
./mem_trans_test.exe  >log.log
ipcs
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
echo "____________________________________________________________"
hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  rollback*
