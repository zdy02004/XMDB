#include "../mempool.h"
#include<stdio.h>
#include<stdlib.h>

#define BLOCK_NUM (1024*4) // 不要大于 1024*4 
#define MAX_TIMES 1024*128 // 总容量到达  43G 时会core dump 掉

int main(int arc,char * arcv[])
{
mem_pool_t * my_mem_pool = mem_pool_create(BLOCK_NUM);
//mem_pool_print(my_mem_pool,22);

long size ;
void * p;
int i = 0;
long * array        = (long * )malloc(sizeof(long *)*MAX_TIMES );
void ** alloc_array = (void **)malloc(sizeof(void *)*MAX_TIMES );
void ** free_array  = (void **)malloc(sizeof(void *)*MAX_TIMES );
char str[] = "abcdefghi";



for(;i<MAX_TIMES;++i)
{
size= rand()%(1024*512);
if(size == 0)size = 10;
array[i] = size;
}

i = 0;
printf("Old malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
p = malloc(array[i]);
alloc_array[i]=p;
}
printf("Old malloc  end  at %s\n\n",GetTime());

i = 0;
printf("Old free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
free(alloc_array[i]);
}
printf("Old free  end  at %s\n\n",GetTime());


//i = 0;
//printf("cpp new begin at %s\n",GetTime());
//for(;i<MAX_TIMES;++i)
//{
//char *p = new char[array[i]];
//alloc_array[i]=p;
//}
//printf("cpp new  end  at %s\n\n",GetTime());
//
//i = 0;
//printf("cpp delete begin at %s\n",GetTime());
//for(;i<MAX_TIMES;++i)
//{
//char *p=(char *)alloc_array[i];
//delete []p;
//}
//printf("cpp delete  end  at %s\n\n",GetTime());


i = 0;
printf("New malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
p = mem_pool_malloc(my_mem_pool,array[i]);
alloc_array[i]=p;
//	if(i>1735 && i<1750)printf("i = %d, alloc_array[i] = %0x\n",i,alloc_array[i]);
}
printf("New malloc  end  at %s\n\n\n",GetTime());

mem_pool_print(my_mem_pool,21);

i = 0;
printf("New free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
//	if(i>1735)printf("i = %d, alloc_array[i] = %0x\n",i,alloc_array[i]);

mem_pool_free(my_mem_pool,alloc_array[i]);
}
printf("New free  end  at %s\n\n\n",GetTime());

mem_pool_destory(my_mem_pool);

free(array);
free(alloc_array);
free(free_array);
return 0;
}
