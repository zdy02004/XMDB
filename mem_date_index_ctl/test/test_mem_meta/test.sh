#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *.o
rm *2016*
rm redo*
rm -rf first_table_name
clear
gcc mem_table_meta.c -g  -I ../../  -lpthread -o mem_table_meta.exe 
./mem_table_meta.exe  >log.log
ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
echo "____________________________________________________________"
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  rollback*
tail -100f log.log
