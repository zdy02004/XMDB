#include "../../mem_block_no_manager.h"
#include "../../mem_index_no_manager.h"
#include "../../mem_table_no_manager.h"

int test_block_no_manager()
{
 init_mem_block_no_manager();
//
 load_cur("./a.txt");
 long a;
 allocate_block_no(&a);
  	printf("SAVE");
//
 save_cur("./a.txt");
//
dest_mem_block_no_manager();
return 0;
}


int test_table_no_manager()
{
 init_mem_table_no_manager();
//
 load_table_cur("./table_no.txt");
 long a;
 allocate_table_no(&a);
 printf("table_no_SAVE\n");
//
 save_table_cur("./table_no.txt");
//
dest_mem_table_no_manager();
return 0;
}

int test_index_no_manager()
{
 init_mem_index_no_manager();
//
 load_index_cur("./index_no.txt");
 long a;
 allocate_block_no(&a);
 printf("index_no_SAVE\n");
//
 save_index_cur("./index_no.txt");
//
dest_mem_index_no_manager();
return 0;
}


int main(int arc,char * arcvp[])
{
	
	test_block_no_manager();
	DEBUG("test table no\n");
	test_table_no_manager();
	DEBUG("test index no\n");
	test_index_no_manager();
//	
	return 0;
}