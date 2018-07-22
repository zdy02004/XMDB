cc = gcc 

mem_table_ctl.o :  mem_table_ctl.c  mem_table_ctl.h  mem_block_t.h
                   $(cc) -c mem_table_ctl.c 
main.o          :  main.c
                   $(cc) -c main.c
try             :  main.o mem_table_ctl.o
