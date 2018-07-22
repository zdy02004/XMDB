#!/bin/sh
rm *core*
rm *.exe *.dat
rm roll*
rm *.o
rm *2016*
rm redo*
clear
gcc file_util_test.c -g  -I ../../  -lpthread -o mem_trans_redo.exe 
cp mem_trans_redo.exe ../../mem_date_index_ctl/test/test_mem_mvcc/test
#../../mem_date_index_ctl/test/test_mem_mvcc/test/mem_trans_redo.exe  >log.log
