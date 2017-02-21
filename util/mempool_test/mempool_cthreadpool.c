#include "../mempool.h"
#include "../cthread_pool.h"
#include<stdio.h>
#include<stdlib.h>
 

// 默认为总大小为 1G 的内存池，缓存范围从 4b ~512K ，
// 不建议从中分配大于 512K的内存,适用于 小型数据结构缓存，
// 不宜总量超过20G

#define BLOCK_NUM (1024*32) // 该产数决定了内存池的大小 目前为 64G 不要大于 1024*64 否则启动时间过长，占用内存空间过大
#define MAX_TIMES 1024*1  // 注意是2的n次方
// 9215 8191

void * p;
long * array;       
void ** alloc_array ;
void ** free_array  ;
mem_pool_t * my_mem_pool;


typedef struct param{
	int i;
}param;

void* test_old_malloc(void * ii)
{
int i = ((param*)ii)->i;
//printf("test_old_malloc %ld\n",i);
p = malloc(array[i]);
alloc_array[i]=p;
return (void*)0;
}

void* test_old_free(void * ii)
{
int i = ((param*)ii)->i;
//printf("test_old_free %ld\n",i);
free(alloc_array[i]);
return (void*)0;
}

void* test_new_malloc(void * ii)
{
int i = ((param*)ii)->i;
//printf("test_new_malloc %ld\n",i);
p = mem_pool_malloc(my_mem_pool,array[i]);
alloc_array[i] = p;
return (void*)0;
}

void* test_new_free(void * ii)
{
int i = ((param*)ii)->i;
//printf("test_new_free %ld\n",i);
mem_pool_free(my_mem_pool,alloc_array[i]);
return (void*)0;
}




int main(int arc,char * arcv[])
{
my_mem_pool = mem_pool_create(BLOCK_NUM);
//mem_pool_print(my_mem_pool,22);
printf("mem_pool have created! \n");
CThread_pool_t *executor1 = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));  
CThread_pool_t *executor2 = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));  
CThread_pool_t *executor3 = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));  
CThread_pool_t *executor4 = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));  

thread_pool_init (executor1,20,MAX_TIMES);
thread_pool_init (executor2,20,MAX_TIMES);
thread_pool_init (executor3,20,MAX_TIMES);
thread_pool_init (executor4,20,MAX_TIMES);
                        
 //printf("aligend_2_n = %d \n",aligend_2_n(189));

long size ;

int i = 0;
array        = (long *)malloc(sizeof(long *)*MAX_TIMES );
alloc_array = (void **)malloc(sizeof(void *)*MAX_TIMES );
free_array  = (void **)malloc(sizeof(void *)*MAX_TIMES );
char str[] = "abcdefghi";



for(;i<MAX_TIMES;++i)
{
size= rand()%(1024*512);
array[i] = size>0?size:10;

}

param *param1 = (param *)malloc(sizeof(param)*MAX_TIMES);
param *param2 = (param *)malloc(sizeof(param)*MAX_TIMES);
param *param3 = (param *)malloc(sizeof(param)*MAX_TIMES);
param *param4 = (param *)malloc(sizeof(param)*MAX_TIMES);


i = 0;
printf("Old malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
	param1[i].i=i;
thread_pool_add_task( executor1,test_old_malloc,&(param1[i]) );

}
thread_pool_destroy (executor1); 

printf("Old malloc  end  at %s\n\n",GetTime());

i = 0;
printf("Old free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
param2[i].i=i;
thread_pool_add_task( executor2,test_old_free,&(param2[i]) );
}
thread_pool_destroy (executor2); 
//
printf("Old free  end  at %s\n\n",GetTime());
//
//
i = 0;
printf("New malloc begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
param3[i].i=i;
thread_pool_add_task( executor3,test_new_malloc,&(param3[i]) );

}
thread_pool_destroy (executor3); 
printf("New malloc  end  at %s\n\n\n",GetTime());

mem_pool_print(my_mem_pool,21);

i = 0;
printf("New free begin at %s\n",GetTime());
for(;i<MAX_TIMES;++i)
{
param4[i].i=i;
thread_pool_add_task( executor4,test_new_free,&(param4[i]) );
}
thread_pool_destroy (executor4); 
printf("New free  end  at %s\n\n\n",GetTime());


 /*等待所有任务完成*/  
    
mem_pool_destory(my_mem_pool);
free(array);
free(alloc_array);
free(free_array);

free(param1);
free(param2);
free(param3);
free(param4);

return 0;
}
