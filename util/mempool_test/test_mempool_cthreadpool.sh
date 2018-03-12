#!/bin/sh
rm *core*
rm *.exe *.dat *.log
rm roll* *.out
rm *.o
rm *2017*
rm redo*
clear
gcc mempool_cthreadpool.c -O3 -g -I ../../  -lpthread -o mempool_test.exe 
echo ""
echo ""

./mempool_test.exe
