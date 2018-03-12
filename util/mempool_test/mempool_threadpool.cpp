#include "../mempool.h"
#include "../thread_pool.hpp"
#include<stdio.h>
#include<stdlib.h>

#define BLOCK_NUM 1024
#define MAX_TIMES 64

void * p;
long * array;       
void ** alloc_array ;
void ** free_array  ;
mem_pool_t * my_mem_pool;

void test_old_malloc(int i)
{
p = malloc(array[i]);
alloc_array[i]=p;
}

void test_old_free(int i)
{
free(alloc_array[i]);
}

void test_new_malloc(int i)
{
p = mem_pool_malloc(my_mem_pool,array[i]);
alloc_array[i] = p;
}

void test_new_free(int i)
{
mem_pool_free(my_mem_pool,alloc_array[i]);
}


int main(int arc,char * arcv[])
{
my_mem_pool = mem_pool_create(BLOCK_NUM);
//mem_pool_print(my_mem_pool,22);

task_executor executor1 (4);
task_executor executor2 (4);
task_executor executor3 (4);
task_executor executor4 (4);


long size ;

int i = 0;
array        = (long *)malloc(sizeof(long *)*MAX_TIMES );
alloc_array = (void **)malloc(sizeof(void *)*MAX_TIMES );
free_array  = (void **)malloc(sizeof(void *)*MAX_TIMES );
char str[] = "abcdefghi";




for(;i<MAX_TIMES;++i)
{
size= rand()%(1024);
if(size == 0)size = 10;
array[i] = size;
}

i = 0;
printf("Old malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
executor1.commit([=](){test_old_malloc(i);});
}
printf("Old malloc  end  at %s\n\n",GetTime());

i = 0;
printf("Old free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
executor2.commit([=](){test_old_free(i);});
}
printf("Old free  end  at %s\n\n",GetTime());


i = 0;
printf("New malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
executor3.commit([=](){test_new_malloc(i);});

}
printf("New malloc  end  at %s\n\n\n",GetTime());

//mem_pool_print(my_mem_pool,22);

i = 0;
printf("New free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
executor4.commit([=](){test_new_free(i);});
}
printf("New free  end  at %s\n\n\n",GetTime());


mem_pool_destory(my_mem_pool);
executor1.shutdown();
executor2.shutdown();
executor3.shutdown();
executor4.shutdown();

free(array);
free(alloc_array);
free(free_array);
return 0;
}
