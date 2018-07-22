#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *.o
rm *201*
rm redo*
clear
gcc mem_trans_redo.c -g  -I ../../  -lpthread -o mem_trans_redo.exe 
./mem_trans_redo.exe  >log.log
ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
echo "____________________________________________________________"
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  rollback*
tail -100f log.log
