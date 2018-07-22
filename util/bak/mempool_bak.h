#include "./log/log_util.h"
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include "../mem_date_index_ctl/rwlock.h"

#ifndef _SIMPLE_MEMPOOL_H
#define _SIMPLE_MEMPOOL_H
#define CACHE_LINE_SIZE 64

//暂时用自旋锁锁来实现回收链表锁
#define EXTERN_LOCK_T             rwlock_t
#define EXTERN_LOCK(x)            rwlock_wlock(x)
#define EXTERN_UNLOCK(x)          rwlock_wunlock(x)   
//#define EXTERN_TRYLOCK(x)         pthread_spin_trylock(x)   
#define EXTERN_LOCK_INIT(x)       rwlock_init(x)


FILE *stream;  


#ifdef __cplusplus

extern "C" {

#endif


typedef struct unode_t
{
void           * addr;
struct unode_t * next;
//void           * pad[2];//    
}unode_t;

//由于内存分配的次序不受影响 ABA 并不是问题

typedef struct unode_list_t
{
unode_t *            head;
 char pad1[CACHE_LINE_SIZE - 4 * sizeof(unode_t *)];
unode_t *            end;
 char pad2[CACHE_LINE_SIZE - 4 * sizeof(unode_t *)];
 
unode_t *            unode_ptr_array_t;
unsigned int          block_size;
unsigned int          block_num;
void *               space;
struct unode_list_t* next;
EXTERN_LOCK_T        extern_locker;
int                  slot;
}unode_list_t;

int mem_pool_size[] ={1,   2     ,4     ,8     ,16     ,32     ,64     ,128     ,256     , 512     , 1024,
											1024,2*1024,4*1024,8*1024,16*1024,32*1024,64*1024,128*1024,256*1024, 512*1024,1024*1024}; // 大于512K时 会core dump 原因待查

typedef struct mem_pool_t
{
	// 4b 8b 16b 32b 64b 128b 256b  512b  1024b
	// 4k 8k 16k 32k 64k 128k 256k  512k  1024k
	// --4M 8M 16M 32M 64M 128M 256M  512M  1024M
  unode_list_t array[21]; 
}mem_pool_t;


int mem_pool_print(mem_pool_t *,int);
int unode_list_print(unode_list_t *);

//unode_list_t *  unode_list_t_create(unsigned int block_size,unsigned int block_num )
//{
//unode_list_t * ret       = (unode_list_t *) malloc( sizeof(unode_list_t) );
//ret->space				     =                  malloc( block_num*block_size);
//ret->unode_ptr_array_t =      (unode_t*)  malloc( block_num*sizeof(struct unode_t) );

// 初始化链表
//unsigned int i = 0;
//unode_t * tmp   = (unode_t*)(ret->unode_ptr_array_t);
//for(;i<block_num;++i)
//{
//	 tmp->addr = (void *)(((char *)(ret->space))+ block_size*i );
//	 if(i<block_num-1)tmp->next = tmp + 1;
//	 else tmp->next =NULL;
//	 ++tmp;
//}
//--tmp;
//ret->block_size    = block_size;
//ret->block_num     = block_num;
//ret->head          = (unode_t*)(ret->unode_ptr_array_t);
//ret->end           = (unode_t*)(ret->unode_ptr_array_t) + block_num-1;
//ret->next          = NULL;
//return ret;
//}

//不分配空间，只是初始化产数，等到真正用到的时候再分配空间
int  unode_list_t_light_init(unode_list_t * lst,unsigned int block_size,unsigned int block_num,int slot )
{
lst->space				     =   NULL;  
lst->unode_ptr_array_t =   NULL;  
lst->block_size    = block_size;
lst->block_num     = block_num;
lst->head          = NULL;
lst->end           = NULL;
lst->next          = NULL;
lst->slot					 = slot;
return 0;
}

typedef struct mem_pool_virtual_info
{
	int         slot;
	unode_t *	node;
}mem_pool_virtual_info;

int  unode_list_t_init(unode_list_t * lst,unsigned int block_size,unsigned int block_num,int slot )
{
lst->space				     =              malloc( block_num*(block_size+sizeof(mem_pool_virtual_info)));
lst->unode_ptr_array_t =  (unode_t*)  malloc( block_num* sizeof(unode_t) );
  

// 初始化链表
unsigned int i = 0;
unode_t * tmp   = lst->unode_ptr_array_t;
mem_pool_virtual_info * virtual_info;

//if(!stream)stream = fopen( "./fprintf.out", "w" );  

for(;i<block_num;++i)
{
	 tmp->addr = (char *)(lst->space)+ i*(block_size+sizeof(mem_pool_virtual_info)) ;
	 virtual_info = (mem_pool_virtual_info *)(tmp->addr);
	 virtual_info ->slot = slot;
	 virtual_info ->node = tmp;
	 
   //fprintf(stream,"unode_list_t[%ld],tmp = %0x,tmp->addr = %0x\n",block_size/1024,tmp,tmp->addr);
	 //fflush(stream);  
	  
	 if(i<block_num-1)tmp->next = tmp + 1;
	 else tmp->next =NULL;
	 ++tmp;
}

lst->block_size    = block_size;
lst->block_num     = block_num;
lst->head          = (unode_t*)(lst->unode_ptr_array_t);
lst->end           = (unode_t*)(lst->unode_ptr_array_t) + block_num-1;
lst->next          = NULL;
lst->slot					 = slot;
EXTERN_LOCK_INIT(&(lst->extern_locker));

	

return 0;
}

int  unode_list_print(unode_list_t *lst )
{
	unode_list_t * p  =  lst;
	unode_list_t * pre ;
	int i = 0;
	while(p)
	{
		++i;
		pre = p;
		p=p->next;
		if(i!=1)printf("->extended_node[%d] %0x ",i,pre);
		if(i%5 == 0 )printf("\n");

	}
			
	return 0;
}

static inline unode_t *  unode_list_extend(unode_list_t *lst )
{
	unode_list_t * next_lst =  (unode_list_t *)malloc(sizeof(unode_list_t));
  //fprintf(stream,"(lst)->block_num,unode_list_extend, next_lst = %0x\n",(lst)->block_num,next_lst);
  //fflush(stream);
  
  
	unode_list_t_init(next_lst,(lst)->block_size,(lst)->block_num,(lst)->slot );
	
 
	//printf("unode_list(%0x) block_size [%ld] %0x\n",lst,(lst)->block_size,next_lst->head);
	
	unode_list_t *end = lst;
	while(end->next != NULL){end = end->next;}
	
	(end)->next = next_lst;
	(lst)->end  = next_lst->end;
	(lst)->head = next_lst->head;
	return (lst)->head;
}

int  unode_list_destory(unode_list_t *lst )
{
	unode_list_t * p  =  lst;
	unode_list_t * pre ;
	while(p)
	{
		pre = p;
		p=p->next;
		if(pre->space){free(pre->space);pre->space = 0;}
		if(pre->unode_ptr_array_t){free(pre->unode_ptr_array_t);pre->unode_ptr_array_t=0;}
		if(pre == lst)DEBUG("free_head %ld",pre);
		else DEBUG("->free_node %ld",pre);
    if(pre != lst)free(pre);

	}
			
	return 0;
}



static inline unode_t * unode_list_malloc(unode_list_t *lst,int slot)
{
	DEBUG("%d unode_list_malloc \n",__LINE__);
	unode_t * head = NULL;
	unode_t * next = NULL;
	
	do
	{	
			//printf("%d unode_list_malloc0 \n",__LINE__);

	//空间用光就重新分配
	if(lst->head == NULL)
	{
	  EXTERN_LOCK(&(lst->extern_locker));
	  if(lst->head == NULL)
	 {
	 	//printf("%d unode_list_extend ,block_size = %ld,slot = %d \n",__LINE__,lst->block_size,slot);
		unode_list_extend(lst );
	 }
	  EXTERN_UNLOCK(&(lst->extern_locker));
  }
		
	//空间未用光则取出head，并更新lst->head	
	//printf("%d unode_list_malloc \n",__LINE__);
	do
	{
			head = lst->head;
			if( NULL == head )break;
			next = head->next;

  }while(!__sync_bool_compare_and_swap(&(lst->head),head,next));
  }
  while(head == NULL);//取出失败就重试
	//printf("%d unode_list_malloc head = %0x, next = %0x\n",__LINE__,head,next);

	return head;
	
	// 单线程逻辑
	//if(lst->head == NULL)
	//{
  //return unode_list_extend(lst );
  //}
  //unode_t * ret = lst->head;
  //lst->head = lst->head->next;
	//return ret;
}

static inline int unode_list_free(unode_list_t *lst,unode_t * node)
{
	unode_t * end;
	do
	{
	  end     = lst->end;
	  if(end)end->next = node;
  }while(!__sync_bool_compare_and_swap(&lst->end,end,node));
	
	
	// 单线程逻辑
	//if(lst->end)lst->end->next = node;
	//lst->end       = node;
	return 0;
}




mem_pool_t * mem_pool_create(unsigned int  block_num)
{
	mem_pool_t * ret =(mem_pool_t *)malloc(sizeof(mem_pool_t));
	int i = 1; 
	for(;i<21;++i)
	{
	  //if(i<14)unode_list_t_init(&(ret->array[i]),mem_pool_size[i],block_num,i);
	  //else 
	  unode_list_t_light_init(&(ret->array[i]),mem_pool_size[i],block_num,i);
	 // unode_list_t_init(&(ret->array[i]),mem_pool_size[i],block_num,i);


	}
	return ret;
}

int mem_pool_destory(mem_pool_t * pool)
{
	int i = 1; 
	for(;i<21;++i)unode_list_destory(&(pool->array[i]));
	free(pool);
	return 0;
}

int mem_pool_print(mem_pool_t * pool,int n)
{
	int i = 0; 
	for(;i<n;++i)
	{
	 printf("head_node[%d] %0x ",i,&(pool->array[i]));
	 //unode_list_print(pool->array[i]);
	unode_list_t * p  =  &(pool->array[i]);
	unode_list_t * pre ;
	int j = 0;
	while(p)
	{
		++j;
		pre = p;
		p=p->next;
		if(j!=1)printf("->extended_node[%d] %0x ",j,pre);
		if(j%5 == 0 )printf("\n");

	}
	 printf("\n");
	}
	return 0;
}

static inline int mem_pool_choose(int size)
{
	if(size > 1024*512)return -1;
	int half = 0;
	if(size>1024)
		{
			half = 1;
		}
		int tsize = size;
		if(half)tsize>>=10;
		int cnt   = 0;
		while(tsize)
		{
			++cnt;
			tsize/=2;
		}
		
		if(1 == half)
			{
				cnt+=11;
		    //printf("cnt = %ld \n",cnt);
	    }
	    if(cnt == 0)printf("mem_pool_choose(%ld)\n",size);
		return cnt;
}

static inline void * mem_pool_malloc(mem_pool_t * pool,unsigned int size)
{
  if(!pool || size==0)return 0;
	void * ret;
	if(size > 1024*512)
		{
			//ret = malloc(size+sizeof(int)+sizeof(unode_t **));
			//*(int*)(ret) = i;
			//return ret+sizeof(int)+sizeof(unode_t **);
			ret = malloc(size+sizeof(mem_pool_virtual_info));  
      ((mem_pool_virtual_info*)(ret))->slot = -1;                                   
      return ret+sizeof(mem_pool_virtual_info);          

		}
	int slot = mem_pool_choose(size);
	if(slot>21 || slot<1 )
		{
			printf("%d slot>21 || slot<1  slot= %ld,size = %d\n",__LINE__,slot,size);
			return NULL;
		}
	unode_t * ptr = unode_list_malloc(&( pool->array[slot] ),slot);
  //printf("%d mem_pool_malloc  slot= %ld,size = %d,ptr->addr = %0x\n",__LINE__,slot,size,ptr->addr);
	ret = ptr->addr;

	if(slot>21)printf("%d mem_pool_malloc  slot= %ld,size = %d,ptr is %0x,ptr->addr = %0x\n",__LINE__,slot,size,ptr,ptr->addr);

	 return ret+sizeof(mem_pool_virtual_info);    
}

static inline int mem_pool_free(mem_pool_t * pool,void * ptr)
{
	//int       i    = *((int*)(ptr-sizeof(int)-sizeof(unode_t **)));
	//unode_t * node = (*(unode_t **)(ptr-sizeof(unode_t **)));
	mem_pool_virtual_info * info =(mem_pool_virtual_info *) ( ((char *)ptr) - sizeof(mem_pool_virtual_info) );    
	int       slot   = info->slot;
	unode_t * node   = info->node;
	
	if(slot>21 || slot<1 )
		{
		  
			printf("mem_pool_free ptr = %0x,addr = %0x,slot = %ld,node = %0x\n ",ptr,(void *)info,slot,node);
	    return -1;	
	 }
	if(-1 == slot)
		{
			//free( ptr-sizeof(int)-sizeof(unode_t **) );
			free( ((char *)ptr-sizeof(mem_pool_virtual_info) ));
			return 0;
		}
	 
	unode_list_free(&(pool->array[slot]),node );
	return 0;
}

#ifdef __cplusplus
}
#endif

#endif 