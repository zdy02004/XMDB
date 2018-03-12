#include <emmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "./log/log_util.h"

#ifndef __CAS_SLEEP_RING__
#define __CAS_SLEEP_RING__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef likely
#define likely(x)     __builtin_expect((x), 1)
#endif

#ifndef unlikely
#define unlikely(x)   __builtin_expect((x), 0)
#endif

#define CACHE_LINE_SIZE     64

#define CAS_SLEEP_RING_ERR_QUEUE_ALLOC_FAILED      245014
#define CAS_SLEEP_RING_ERR_QUEUE_FULL 					   245015
#define CAS_SLEEP_RING_ERR_QUEUE_EMPTY 				     245016  
#define CAS_SLEEP_RING_ALLOC_FAILED								 245017
#define CAS_SLEEP_RING_FULL												 245018
#define CAS_SLEEP_RING_EMPTY											 245019
#define CAS             __sync_bool_compare_and_swap          


//暂时改回 不阻塞线程的模式
//满或空直接返回错误码

//暂时用互斥锁表示睡眠锁
#define CAS_SLEEP_RING_SLEEP_LOCK_T        pthread_mutex_t
#define CAS_SLEEP_RING_SLEEP_LOCK(x)       pthread_mutex_lock(x)
#define CAS_SLEEP_RING_SLEEP_UNLOCK(x)     pthread_mutex_unlock(x)   
#define CAS_SLEEP_RING_SLEEP_LOCK_INIT(x)  pthread_mutex_init(x,0)
#define CAS_SLEEP_RING_SLEEP_LOCK_DEST(x)  pthread_mutex_destroy(x) 

//暂时用互斥锁条件变量
#define CAS_SLEEP_RING_SLEEP_COND_T                  pthread_cond_t  
#define CAS_SLEEP_RING_SLEEP_COND_INIT(x)            pthread_cond_init(x, NULL)
#define CAS_SLEEP_RING_SLEEP_COND_DEST(x)            pthread_cond_destroy(x)
#define CAS_SLEEP_RING_SLEEP_COND_WAIT(x,y)          pthread_cond_wait(x, y)
#define CAS_SLEEP_RING_SLEEP_COND_SIGN(x)            pthread_cond_signal(x)
#define CAS_SLEEP_RING_SLEEP_COND_BROADCAST(x)       pthread_cond_broadcast(x)
  
//#define ItemType int

#define CAS_SLEEP_RING_STRUCT(ItemType)																																											\
typedef struct cas_sleep_ring_##ItemType##_t {																														                   \
    struct {																																												                         \
        uint32_t mask;                                                                   						                         \
        uint32_t size;                                                                   						                         \
        volatile uint32_t first ;                                                        						                         \
        char pad0[CACHE_LINE_SIZE - 3 * sizeof(uint32_t)];                                   						                     \
       volatile uint32_t second;                                                        						                         \
    } head;                                                                              						                         \
    char pad1[CACHE_LINE_SIZE - 1 * sizeof(uint32_t)];                                   						                         \
    struct {                                                                             						                         \
        uint32_t mask;                                                                   						                         \
        uint32_t size;                                                                   						                         \
        volatile uint32_t first;                                                         						                         \
        char pad3[CACHE_LINE_SIZE - 3 * sizeof(uint32_t)];                                   						                     \
        volatile uint32_t second;                                                        						                         \
    } tail;                                                                              						                         \
    char pad4[CACHE_LINE_SIZE - 1 * sizeof(uint32_t)];                                   						                         \
                                                                                         						                         \
    uint32_t max;                                                                        						                         \
    CAS_SLEEP_RING_SLEEP_LOCK_T  sleep_locker;                                 								 						                   \
    int                    is_sleeping ;                      										       						                         \
    CAS_SLEEP_RING_SLEEP_COND_T  sleep_cond  ;                      													 						                   \
    ItemType                  * item      ;                                                					                         \
}cas_sleep_ring_##ItemType##_t;                                                                    				                         \
static inline int init_cas_sleep_ring_##ItemType   (cas_sleep_ring_##ItemType##_t * cas_sleep_ring, uint32_t max);                             \
static inline int en_cas_sleep_ring_##ItemType     (cas_sleep_ring_##ItemType##_t * cas_sleep_ring, ItemType* item );                          \
static inline int de_cas_sleep_ring_##ItemType     (cas_sleep_ring_##ItemType##_t * cas_sleep_ring, ItemType * item);                          \
static inline int reinit_cas_sleep_ring_##ItemType (cas_sleep_ring_##ItemType##_t * cas_sleep_ring, uint32_t max);                             \
static inline int destroy_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring);                                           \
static inline int init_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring,uint32_t max)                                  \
{                                                                                        						                         \
    cas_sleep_ring->item = (ItemType*)calloc(1,(max+1) * sizeof(ItemType));                         		                           \
    cas_sleep_ring->max  = max;                                                                                                    \
    if(!cas_sleep_ring->item)                                                                 						                         \
    {                                                                                   						                         \
        ERROR("%s\n","Alloc failed,not memory enough");                                  						                         \
        return CAS_SLEEP_RING_ALLOC_FAILED;                                                   						                         \
    }                                                                                   						                         \
    CAS_SLEEP_RING_SLEEP_LOCK_INIT(&(cas_sleep_ring->sleep_locker));                              							                         \
    CAS_SLEEP_RING_SLEEP_COND_INIT(&(cas_sleep_ring->sleep_cond))  ;                              							                         \
    cas_sleep_ring->is_sleeping = 0;                                                          						                         \
                                                                                        						                         \
    cas_sleep_ring->head.first = cas_sleep_ring->head.second = 0;														\
    cas_sleep_ring->tail.first = cas_sleep_ring->tail.second = 0;														\
    cas_sleep_ring->head.size = cas_sleep_ring->tail.size = max  ;                                  						                         \
    cas_sleep_ring->head.mask = cas_sleep_ring->tail.mask = max-1;                                  						                         \
    return 0;                                                                           						                         \
}                                                                                       						                         \
static inline int en_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring, ItemType* item)                                 \
{                                                                                       					                           \
if(cas_sleep_ring->is_sleeping ==2)return -1;																								  						                         \
    uint32_t head, tail, mask, next;                                                    					 	                         \
    int ok;                                                                             					 	                         \
    mask = cas_sleep_ring->head.mask;                                                         					 	                         \
    do {                                                                                					 	                         \
        head = cas_sleep_ring->head.first;                                                    					 	                         \
        tail = cas_sleep_ring->tail.second;                                                   					 	                         \
        if(((head - tail) > mask) && (!((tail == head) || (tail > head && (head - tail) > mask))))                           \
        	{                                                                              						                         \
        		ERROR("%s\n","The cas_sleep_ring_##ItemType##_t is full");                         						                         \
            return CAS_SLEEP_RING_FULL;                                                        						                         \
          }                                                                              						                         \
        next = head + 1;                                                                 						                         \
        ok = CAS(&cas_sleep_ring->head.first, head, next);                                     						                         \
    } while (!ok);                                                                       						                         \
    memcpy(&(cas_sleep_ring->item[head & mask]),item,sizeof(ItemType));                        						                         \
    asm volatile ("":::"memory");                                                        						                         \
    while (unlikely((cas_sleep_ring->head.second != head)))                                    						                         \
        _mm_pause();                                                                     						                         \
    cas_sleep_ring->head.second = next;                                                        						                         \
   	if(cas_sleep_ring->is_sleeping!=2)cas_sleep_ring->is_sleeping = 0;                               						                         \
    CAS_SLEEP_RING_SLEEP_COND_SIGN(&(cas_sleep_ring->sleep_cond));                                   						                         \
    return 0;                                                                            						                         \
}                                                                                        						                         \
static inline int de_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring, ItemType * item)				                         \
{                                                                                       						                         \
    uint32_t tail, head, mask, next;                                                    						                         \
    int ok;                                                                             						                         \
    mask = cas_sleep_ring->tail.mask;                                                         						                         \
    do {                                                                                						                         \
        tail = cas_sleep_ring->tail.first;                                                    						                         \
        head = cas_sleep_ring->head.second;                                                   						                         \
        if ((tail == head) || (tail > head && (head - tail) > mask))                    						                         \
        {																			\
        CAS_SLEEP_RING_SLEEP_LOCK(&(cas_sleep_ring->sleep_locker));                                 						                         \
        if( 0 == cas_sleep_ring->is_sleeping)                                                 						                         \
   		  {                                      																											                         \
   		  	cas_sleep_ring->is_sleeping = 1;                                                    						                         \
   		  }																																														                         \
   		  if(2 == cas_sleep_ring->is_sleeping)                                                  						                         \
   		   	{                                                                             						                         \
   		   		CAS_SLEEP_RING_SLEEP_UNLOCK(&(cas_sleep_ring->sleep_locker));                           						                         \
   		   		return -1;                                                                  						                         \
					}	                                                                            						                         \
   		  	CAS_SLEEP_RING_SLEEP_COND_WAIT(&(cas_sleep_ring->sleep_cond),&(cas_sleep_ring->sleep_locker));							                         \
   	      CAS_SLEEP_RING_SLEEP_UNLOCK(&(cas_sleep_ring->sleep_locker));																					                         \
         ok =0;																																																							 \
         continue;                               																										                         \
         }                                                                              						                         \
        next = tail + 1;                                                                						                         \
        ok = CAS(&cas_sleep_ring->tail.first, tail, next);                                    						                         \
    } while (!ok);                                                                      						                         \
    memcpy(item,&(cas_sleep_ring->item[tail & mask]),sizeof(ItemType));                       						                         \
    asm volatile ("":::"memory");                                                       						                         \
    while (unlikely((cas_sleep_ring->tail.second != tail)))                                   						                         \
           _mm_pause();                                                                     						                         \
    cas_sleep_ring->tail.second = next;                                                       						                         \
    return 0;                                                                           						                         \
}                                                                                       						                         \
static inline int reinit_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring,uint32_t max)				                         \
{                                                                                										                         \
    free(cas_sleep_ring->item);                                                        										                         \
    return init_cas_sleep_ring_##ItemType(cas_sleep_ring, max);                                         										                         \
}                                                                                										                         \
static inline int stop_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring)											                         \
{                                                                                          					                         \
	 if (cas_sleep_ring->is_sleeping == 2)return -1; /*防止两次调用*/                              					                         \
	 CAS_SLEEP_RING_SLEEP_LOCK  (&(cas_sleep_ring->sleep_locker));                                       					                         \
   cas_sleep_ring->is_sleeping = 2;                                                              					                         \
   CAS_SLEEP_RING_SLEEP_UNLOCK(&(cas_sleep_ring->sleep_locker));                                       					                         \
   /* 已满 且 非空*/                                                                       					                         \
   CAS_SLEEP_RING_SLEEP_COND_BROADCAST(&(cas_sleep_ring->sleep_cond)); 																					                         \
		return 0;																																												                         \
}																																																		                         \
static inline int destroy_cas_sleep_ring_##ItemType(cas_sleep_ring_##ItemType##_t * cas_sleep_ring)										                         \
{  																																																	                         \
	  CAS_SLEEP_RING_SLEEP_COND_DEST(&(cas_sleep_ring->sleep_cond));                           										                         \
	  cas_sleep_ring->is_sleeping = 0;                                                   										                         \
	  CAS_SLEEP_RING_SLEEP_LOCK_DEST(&(cas_sleep_ring->sleep_locker));                         										                         \
    free(cas_sleep_ring->item);                                                                                                    \
    free(cas_sleep_ring);                                                                                                          \
    return 0;                                         																																			 \
} 

#define CAS_SLEEP_RING_TYPE(ItemType,x)												\
cas_sleep_ring_##ItemType##_t		* (x);                  			
                                                			
#define CAS_SLEEP_RING_INIT(ItemType,cas_sleep_ring,max)											\
(cas_sleep_ring) = (cas_sleep_ring_##ItemType##_t *)malloc(sizeof(cas_sleep_ring_##ItemType##_t));								\
init_cas_sleep_ring_##ItemType (cas_sleep_ring,max); 

#define CAS_SLEEP_RING_EN(ItemType,cas_sleep_ring,item)						\
en_cas_sleep_ring_##ItemType (cas_sleep_ring, item )       			
                                                			
#define CAS_SLEEP_RING_DN(ItemType,cas_sleep_ring,item)						\
de_cas_sleep_ring_##ItemType  (cas_sleep_ring,item)        			
                                                			
#define CAS_SLEEP_RING_REINIT(ItemType,cas_sleep_ring,item)				\
reinit_cas_sleep_ring_##ItemType (cas_sleep_ring,max)      			
                                                			
#define CAS_SLEEP_RING_STOP(ItemType,cas_sleep_ring)							\
stop_cas_sleep_ring_##ItemType(cas_sleep_ring) 							\
                                                			
                                                			
#define CAS_SLEEP_RING_DESTORY(ItemType,cas_sleep_ring)						\
destroy_cas_sleep_ring_##ItemType(cas_sleep_ring)      

#ifdef __cplusplus
}
#endif





//CAS_SLEEP_RING_STRUCT(int)
//                         
//int test(int arc,char *arcv[])
//{
//CAS_SLEEP_RING_TYPE(int,x_int);
//CAS_SLEEP_RING_INIT(int,x_int,2048);
//int in = 1;
//int out;
//CAS_SLEEP_RING_EN(int,x_int,&in);
//CAS_SLEEP_RING_DN(int,x_int,&out);
//printf("out is %ld\n",out);
//CAS_SLEEP_RING_STOP(int,x_int);
//CAS_SLEEP_RING_DESTORY(int,x_int);
//return 0;
//}   

#endif 
