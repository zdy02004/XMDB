#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *.o
rm *2017*
rm redo*
clear
gcc mem_trans_mvcc.c -g  -I ../../  -lpthread -o mem_trans_mvcc.exe 
./mem_trans_mvcc.exe  >log.log
ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
echo "____________________________________________________________"
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  rollback*
tail -100f log.log
