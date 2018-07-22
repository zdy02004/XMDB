#!/bin/sh
rm *core*
rm *.exe *.dat
rm -rf first_rbtree_name*
rm roll*
rm *.o *.log
rm *2016*
rm redo*
rm -rf first_index_name*
clear
gcc mem_rbtree_meta.c -g  -I ../../  -lpthread -o mem_rbtree_meta.exe 
./mem_rbtree_meta.exe  >log.log
ipcs
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  map_table.dat
echo "____________________________________________________________"
#hexdump -e '16/1 "%02X " " | "' -e '16/1 "%_p" "\n"'  rollback*
tail -100f log.log
