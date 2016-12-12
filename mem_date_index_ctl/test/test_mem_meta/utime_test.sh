#!/bin/sh
clear
rm  utime.exe
rm utime_log.log
gcc utime.c -g  -I ../../  -lpthread -o utime.exe 
./utime.exe  
