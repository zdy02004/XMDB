#include <emmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "./log/log_util.h"

#ifndef __CAS_RING__
#define __CAS_RING__

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

#define CAS_RING_ERR_QUEUE_ALLOC_FAILED      145014
#define CAS_RING_ERR_QUEUE_FULL 					   145015
#define CAS_RING_ERR_QUEUE_EMPTY 				     145016  
#define CAS_RING_ALLOC_FAILED								 145017
#define CAS_RING_FULL												 145018
#define CAS_RING_EMPTY											 145019
#define CAS             __sync_bool_compare_and_swap          


//暂时改回 不阻塞线程的模式
//满或空直接返回错误码


#define CAS_RING_STRUCT(ItemType)																																														 \
typedef struct cas_ring_##ItemType##_t {																														                         \
    struct {																																												                         \
        uint32_t mask;                                                                   						                         \
        uint32_t size;                                                                   						                         \
        volatile uint32_t first ;                                                        						                         \
        char pad0[CACHE_LINE_SIZE - 3 * sizeof(uint32_t)];                                   						                    \
        volatile uint32_t second;                                                        						                         \
    } head;                                                                              						                         \
    char pad1[CACHE_LINE_SIZE - 1 * sizeof(uint32_t)];                                   						                         \
    struct {                                                                             						                         \
        uint32_t mask;                                                                   						                         \
        uint32_t size;                                                                   						                         \
        volatile uint32_t first;                                                         						                         \
				char pad2[CACHE_LINE_SIZE - 3 * sizeof(uint32_t)];																																	\
        volatile uint32_t second;                                                        						                         \
    } tail;                                                                              						                         \
    char pad3[CACHE_LINE_SIZE - 1 * sizeof(uint32_t)];                                   						                         \
    uint32_t max;                                                                        						                         \
    int                    is_sleeping ;                      										       						                         \
    ItemType               * item      ;                                                					                         \
}cas_ring_##ItemType##_t;                                                                    				                         \
static inline int init_cas_ring_##ItemType   (cas_ring_##ItemType##_t * cas_ring, uint32_t max);                             \
static inline int en_cas_ring_##ItemType     (cas_ring_##ItemType##_t * cas_ring, ItemType* item );                          \
static inline int de_cas_ring_##ItemType     (cas_ring_##ItemType##_t * cas_ring, ItemType * item);                          \
static inline int reinit_cas_ring_##ItemType (cas_ring_##ItemType##_t * cas_ring, uint32_t max);                             \
static inline int destroy_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring);                                           \
static inline int init_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring,uint32_t max)                                  \
{                                                                                        						                         \
    cas_ring->item =(ItemType *)malloc( (max+1) * sizeof(ItemType) );                         		                           \
    cas_ring->max  = max;                                                                                                    \
    if(!cas_ring->item)                                                                 						                         \
    {                                                                                   						                         \
        ERROR("%s\n","Alloc failed,not memory enough");                                  						                         \
        return CAS_RING_ALLOC_FAILED;                                                   						                         \
    }                                                                                   						                         \
    cas_ring->is_sleeping = 0;                                                          						                         \
    cas_ring->head.first = cas_ring->head.second = 0;														\
    cas_ring->tail.first = cas_ring->tail.second = 0;														\
    cas_ring->head.size = cas_ring->tail.size = max  ;                                  						                         \
    cas_ring->head.mask = cas_ring->tail.mask = max-1;                                  						                         \
    return 0;                                                                           						                         \
}                                                                                       						                         \
static inline int en_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring, ItemType* _item)                                 \
{                                                                                       					                           \
if(cas_ring->is_sleeping ==2)return -1;																								  						                         \
    uint32_t head, tail, mask, next;                                                    					 	                         \
    int ok;                                                                             					 	                         \
    mask = cas_ring->head.mask;                                                         					 	                         \
    do {                                                                                					 	                         \
        head = cas_ring->head.first;                                                    					 	                         \
        tail = cas_ring->tail.second;                                                   					 	                         \
        if(((head - tail) > mask) && (!((tail == head) || (tail > head && (head - tail) > mask))))                           \
        	{                                                                              						                         \
        		ERROR("%s\n","The cas_ring_##ItemType##_t is full");                         						                         \
            return CAS_RING_FULL;                                                        						                         \
          }                                                                              						                         \
        next = head + 1;                                                                 						                         \
        ok = CAS(&cas_ring->head.first, head, next);                                     						                         \
    } while (!ok);                                                                       						                         \
    cas_ring->item[head & mask] = *_item;\
    asm volatile ("":::"memory");                                                        						                         \
    while (unlikely((cas_ring->head.second != head)))                                    						                         \
        _mm_pause();                                                                     						                         \
    cas_ring->head.second = next;                                                        						                         \
   	if(cas_ring->is_sleeping!=2)cas_ring->is_sleeping = 0;                               						                         \
    return 0;                                                                            						                         \
}                                                                                        						                         \
static inline int de_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring, ItemType * item)				                         \
{                                                                                       						                         \
    uint32_t tail, head, mask, next;                                                    						                         \
    int ok;                                                                             						                         \
    mask = cas_ring->tail.mask;                                                         						                         \
    do {                                                                                						                         \
        tail = cas_ring->tail.first;                                                    						                         \
        head = cas_ring->head.second;                                                   						                         \
        if ((tail == head) || (tail > head && (head - tail) > mask))                    						                         \
        {																			\
					return   CAS_RING_EMPTY;                                                                          						     \
        }                                                                              						                         \
        next = tail + 1;                                                                						                         \
        ok = CAS(&cas_ring->tail.first, tail, next);                                    						                         \
    } while (!ok);                                                                      						                         \
    memcpy(item,&(cas_ring->item[tail & mask]),sizeof(ItemType));                       						                         \
    asm volatile ("":::"memory");                                                       						                         \
    while (unlikely((cas_ring->tail.second != tail)))                                   						                         \
        _mm_pause();                                                                    						                         \
    cas_ring->tail.second = next;                                                       						                         \
    return 0;                                                                           						                         \
}                                                                                       						                         \
static inline int reinit_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring,uint32_t max)				                         \
{                                                                                										                         \
    free(cas_ring->item);                                                        										                         \
    return init_cas_ring_##ItemType(cas_ring, max);                                         										                         \
}                                                                                										                         \
static inline int stop_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring)											                         \
{                                                                                          					                         \
	 if (cas_ring->is_sleeping == 2)return -1; /*防止两次调用*/                              					                         \
   cas_ring->is_sleeping = 2;                                                              					                         \
   /* 已满 且 非空*/                                                                       					                         \
		return 0;																																												                         \
}																																																		                         \
static inline int destroy_cas_ring_##ItemType(cas_ring_##ItemType##_t * cas_ring)										                         \
{  																																																	                         \
	  cas_ring->is_sleeping = 0;                                                   										                         \
    free(cas_ring->item);                                                                                                    \
    free(cas_ring);                                                                                                          \
    return 0;                                         																																			 \
} 

#define CAS_RING_TYPE(ItemType,x)												\
cas_ring_##ItemType##_t		* (x);                  			
                                                			
#define CAS_RING_INIT(ItemType,cas_ring,max)											\
(cas_ring) = (cas_ring_##ItemType##_t *)malloc(sizeof(cas_ring_##ItemType##_t));								\
init_cas_ring_##ItemType (cas_ring,max); 

#define CAS_RING_EN(ItemType,cas_ring,item)						\
en_cas_ring_##ItemType (cas_ring, item )       			
                                                			
#define CAS_RING_DN(ItemType,cas_ring,item)						\
de_cas_ring_##ItemType  (cas_ring,item)        			
                                                			
#define CAS_RING_REINIT(ItemType,cas_ring,max)				\
reinit_cas_ring_##ItemType (cas_ring,max)      			
                                                			
#define CAS_RING_STOP(ItemType,cas_ring)							\
stop_cas_ring_##ItemType(cas_ring) 							\
                                                			
                                                			
#define CAS_RING_DESTORY(ItemType,cas_ring)						\
destroy_cas_ring_##ItemType(cas_ring)      

#ifdef __cplusplus
}
#endif





//CAS_RING_STRUCT(int)
//                         
//int test(int arc,char *arcv[])
//{
//CAS_RING_TYPE(int,x_int);
//CAS_RING_INIT(int,x_int,2048);
//int in = 1;
//int out;
//CAS_RING_EN(int,x_int,&in);
//CAS_RING_DN(int,x_int,&out);
//printf("out is %ld\n",out);
//CAS_RING_STOP(int,x_int);
//CAS_RING_DESTORY(int,x_int);
//return 0;
//}   

#endif 
