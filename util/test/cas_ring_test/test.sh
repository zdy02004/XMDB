#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *.o
rm *2017*
rm redo*
clear
gcc partion_cas_ring.c -g  -lpthread -o partion_cas_ring_test.exe 
./partion_cas_ring_test.exe 
#gdb partion_cas_ring_test.exe  core.*


#../../mem_date_index_ctl/test/test_mem_mvcc/test/mem_trans_redo.exe  >log.log
