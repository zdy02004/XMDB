#include "../local_mempool.h"
#include<stdio.h>
#include<stdlib.h>

#define BLOCK_NUM (1024*4) // 不要大于 1024*4 
void * p;

int main(int arc,char * arcv[])
{
//新建全局 内存池
mem_pool_t * glable_mem_pool = mem_pool_create(BLOCK_NUM);

// 新建局部内存池
local_mem_pool_t *local_mem_pool = local_mem_pool_create(glable_mem_pool, BLOCK_NUM);

//pthread_key_t key ;
//pthread_key_create(&key, NULL);   
//pthread_setspecific(key, (void *)local_mem_pool); 
//local_mem_pool = (local_mem_pool_t *)pthread_getspecific(key);
   


p = local_mem_pool_malloc( local_mem_pool,rand()%(1024) );

local_mem_pool_free(local_mem_pool,p);
local_mem_pool_destory(local_mem_pool);

/* 注销一个key */  
//pthread_key_delete(key); 

mem_pool_destory(glable_mem_pool);

}





