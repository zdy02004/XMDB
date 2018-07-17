#ifndef _LOCAL_MEMPOOL_H
#define _LOCAL_MEMPOOL_H
#include "mempool.h"

#ifdef __cplusplus

extern "C" {

#endif

typedef struct local_mem_pool_t
{
mem_pool_t * glable_mem_pool;
unode_list_t array[MEM_POOL_SLOT_SIZE]; 

}local_mem_pool_t;



//block_num 应为 4的倍数
int  local_unode_list_init(local_mem_pool_t *pool,unode_list_t * lst,unsigned int block_size,unsigned int block_num,int slot )
{
lst->space				     =  mem_pool_malloc(pool->glable_mem_pool ,block_num*(block_size+sizeof(mem_pool_virtual_info)));
lst->unode_ptr_array_t =  (unode_t*)mem_pool_malloc(pool->glable_mem_pool , block_num* sizeof(unode_t) );
  

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

	

return 0;
}


static inline unode_t *  local_unode_list_extend(local_mem_pool_t *pool,unode_list_t *lst )
{
	unode_list_t * next_lst =  (unode_list_t *)mem_pool_malloc(pool->glable_mem_pool ,sizeof(unode_list_t));
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

int  local_unode_list_destory(local_mem_pool_t *pool,unode_list_t *lst )
{
	unode_list_t * p  =  lst;
	unode_list_t * pre ;
	while(p)
	{
		pre = p;
		p=p->next;
		if(pre->space){free(pre->space);pre->space = 0;}
		if(pre->unode_ptr_array_t){mem_pool_free(pool->glable_mem_pool ,pre->unode_ptr_array_t);pre->unode_ptr_array_t=0;}
		if(pre == lst)DEBUG("free_head %ld",pre);
		else DEBUG("->free_node %ld",pre);
    if(pre != lst)free(pre);

	}
			
	return 0;
}



static inline unode_t * local_unode_list_malloc(unode_list_t *lst,int slot)
{
	DEBUG("%d local_unode_list_malloc \n",__LINE__);
	
	// 单线程逻辑
	if(lst->head == NULL)
	{
  return unode_list_extend(lst );
  }
 	unode_t * ret = lst->head;
 	lst->head = lst->head->next;
	return ret;
}

static inline int local_unode_list_free(unode_list_t *lst,unode_t * node)
{
	
	// 单线程逻辑
	if(lst->end)lst->end->next = node;
	lst->end       = node;
	return 0;
}




local_mem_pool_t * local_mem_pool_create(mem_pool_t * pool,unsigned int  block_num)
{
	local_mem_pool_t * ret =(local_mem_pool_t *)mem_pool_malloc(pool,sizeof(local_mem_pool_t));
	int i = 0; 
	//设置 glable_mem_pool
	ret->glable_mem_pool = pool;
	for(;i<MEM_POOL_SLOT_SIZE;++i)
	{
	  unode_list_t_light_init(&(ret->array[i]),mem_pool_size[i],block_num,i);
	  //unode_list_t_init(&(ret->array[i]),mem_pool_size[i],block_num,i);
	}
	return ret;
}

int local_mem_pool_destory(local_mem_pool_t * pool)
{
	int i = 1; 
	for(;i<MEM_POOL_SLOT_SIZE;++i)local_unode_list_destory(pool,(&(pool->array[i])));
	mem_pool_free(pool->glable_mem_pool,pool);
	return 0;
}



static inline void * local_mem_pool_malloc(local_mem_pool_t * pool,unsigned int size)
{
  if(!pool )return 0;
	void * ret;
	if(size > MEM_POOL_MAX_SIZE || size==0)
		{
			//ret = malloc(size+sizeof(int)+sizeof(unode_t **));
			//*(int*)(ret) = i;
			//return ret+sizeof(int)+sizeof(unode_t **);
			ret = malloc(size+sizeof(mem_pool_virtual_info));  
      ((mem_pool_virtual_info*)(ret))->slot = -1;                                   
      return ret+sizeof(mem_pool_virtual_info);          

		}
	int slot = mem_pool_choose(size);
	if(slot>MEM_POOL_SLOT_SIZE || slot<1 )
		{
			printf("%d slot>MEM_POOL_SLOT_SIZE || slot<1  slot= %ld,size = %d\n",__LINE__,slot,size);
			return NULL;
		}
	unode_t * ptr = local_unode_list_malloc(&( pool->array[slot] ),slot);
  //printf("%d mem_pool_malloc  slot= %ld,size = %d,ptr->addr = %0x\n",__LINE__,slot,size,ptr->addr);
	ret = ptr->addr;

	//if(slot>MEM_POOL_SLOT_SIZE)
	//	printf("%d mem_pool_malloc  slot= %ld,size = %d,ptr is %0x,ptr->addr = %0x\n",__LINE__,slot,size,ptr,ptr->addr);
   // printf("%d mem_pool_size[slot]=%d    \n",__LINE__,mem_pool_size[slot]);
	 
	 return ret+sizeof(mem_pool_virtual_info);    
}

static inline int local_mem_pool_free(local_mem_pool_t * pool,void * ptr)
{
	mem_pool_virtual_info * info =(mem_pool_virtual_info *) ( ((char *)ptr) - sizeof(mem_pool_virtual_info) );    
	//printf("%d ptr->addr = %0x\n",__LINE__,info);
	int       slot   = info->slot;
	unode_t * node   = info->node;
	
	if(-1 == slot)
	{
		//free( ptr-sizeof(int)-sizeof(unode_t **) );
		free( ((char *)ptr-sizeof(mem_pool_virtual_info) ));
		return 0;
	}
		
	if(slot>MEM_POOL_SLOT_SIZE || slot<1 )
		{
		  
			printf("mem_pool_free ptr = %0x,addr = %0x,slot = %ld,node = %0x\n ",ptr,(void *)info,slot,node);
	    return -1;	
	 }

	 
	local_unode_list_free(&(pool->array[slot]),node );
	return 0;
}


#ifdef __cplusplus
}
#endif

#endif 
