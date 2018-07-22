#!/bin/sh
rm *core*
rm *.exe *.dat *.log *.out
rm roll*
rm *.o
rm *2017*
rm redo*
clear
gcc local_mempool_test.c -O3 -g -I ../../mempool_test.h  -lpthread -o mempool_test.exe 
echo ""
echo ""

./mempool_test.exe
