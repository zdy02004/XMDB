#!/bin/sh
rm *core*
rm *.exe
clear
gcc -g mem_block_test.c  -I ../../ -lpthread  -o mem_block_test.exe 
./mem_block_test.exe
cat *.dat
