//g++ -std=c++11 -g -lpthread func_task_t.hpp  -o func_task_t.exe
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h> 
#include <unistd.h>  
#include <sys/types.h>  
//#include <pthread.h>  
#include <thread>
//#include <condition_variable>
#include <assert.h>  
#include <emmintrin.h>
#include <string.h>
#include <functional>
#include<vector>
#include "log/log_util.h"
#ifndef __CPPFUNC_POOL__
#define __CPPFUNC_POOL__
namespace cpp_func_task_namespace{

#define aligend_2_n(x)  (1<<((32-__builtin_clz(x))))


#ifndef likely
#define likely(x)     __builtin_expect((x), 1)
#endif

#ifndef unlikely
#define unlikely(x)   __builtin_expect((x), 0)
#endif

#define CACHE_LINE_SIZE     64
  
#define FUNC_TASK_ERR_QUEUE_ALLOC_FAILED      45024
#define FUNC_TASK_ERR_QUEUE_FULL 					    45025
#define FUNC_TASK_ERR_QUEUE_EMPTY 				    45026  
//#define THREAD_POOL_IS_STOPED                 45027
 
/* 
* 
* 
*/  
typedef struct func_task_t
{  
    /*回调函数，任务运行时会调用此函数，注意也可声明成其它形式*/  
    std::function<void (void )> process ;  
    func_task_t(){}
    func_task_t(std::function<void (void )>& _process ){
    	process = _process;
    	}
    func_task_t( func_task_t & _move)
    {
    	process = _move.process;
    }
    func_task_t( func_task_t && _move)
    {
    	process = std::move(_move.process);
    }
     void operator =( func_task_t & _move)
    {
    	process = _move.process;
    }
    
    void operator =( func_task_t && _move)
    {
    	process = std::move(_move.process);
    }
} func_task_t;  
  
  
typedef struct func_task_queue_t {
    struct {
        uint32_t mask;
        uint32_t size;
        volatile uint32_t first;
        volatile uint32_t second;
    } head;
    char pad1[CACHE_LINE_SIZE - 4 * sizeof(uint32_t)];

    struct {
        uint32_t mask;
        uint32_t size;
        volatile uint32_t first;
        volatile uint32_t second;
    } tail;
    char pad2[CACHE_LINE_SIZE - 4 * sizeof(uint32_t)];
    
    uint32_t max;
    func_task_t    * item;
}func_task_queue_t;
//__________________________________________________________

inline int init_func_task_queue  (func_task_queue_t * func_task_queue, uint32_t max);
inline int en_func_task_queue    (func_task_queue_t * func_task_queue, func_task_t & item);
inline int de_func_task_queue    (func_task_queue_t * func_task_queue, func_task_t & item);
inline int reinit_func_task_queue(func_task_queue_t * func_task_queue, uint32_t max);  
int destroy_func_queue(func_task_queue_t * func_task_queue) ; 
//___________________________________________________________


inline int init_func_task_queue(func_task_queue_t * func_task_queue,uint32_t max)  
{  
	DEBUG("init_func_task_queue\n");
    //func_task_queue->item = (func_task_t*)malloc((max+1) * sizeof(func_task_t));  

    func_task_queue->item = new  func_task_t[max+1];
    
    func_task_queue->max  = max;
    if(!func_task_queue->item)  
    {  
        //DEBUG("%s\n","Alloc failed,not memory enough");  
        return FUNC_TASK_ERR_QUEUE_ALLOC_FAILED;  
    }  
    
    func_task_queue->head.first = func_task_queue->head.second = 0;
    func_task_queue->tail.first = func_task_queue->tail.second = 0;	
	
    func_task_queue->head.size = func_task_queue->tail.size = max;
    func_task_queue->head.mask = func_task_queue->tail.mask = max-1;
    return 0;  
}  
 // 入队列
inline int en_func_task_queue(func_task_queue_t * func_task_queue, func_task_t& item)  
{  
	 // DEBUG("en_func_task_queue\n"	);	  
    uint32_t head, tail, mask, next;
    int ok;
    mask = func_task_queue->head.mask;
    do {
        head = func_task_queue->head.first;
        tail = func_task_queue->tail.second;
        // 已满 且 非空
        if (((head - tail) > mask) && (!((tail == head) || (tail > head && (head - tail) > mask))))
        	{
        		DEBUG("%ld %s,head=%ld,tail=%ld\n",__LINE__,"The func_task_queue_t is full",head,tail);
            return FUNC_TASK_ERR_QUEUE_FULL;
            //continue;
          }
        next = head + 1;
        ok = __sync_bool_compare_and_swap(&func_task_queue->head.first, head, next);
    } while (!ok);

    func_task_queue->item[head & mask] =  (item);
    asm volatile ("":::"memory");

    while (unlikely((func_task_queue->head.second != head)))
        _mm_pause();

    func_task_queue->head.second = next;

    return 0;  
}  
  // 出队列
inline int de_func_task_queue(func_task_queue_t * func_task_queue, func_task_t & item)  
{     
	   DEBUG("Enter de_func_task_queue\n"	);
     if(NULL == func_task_queue)ERROR("NULL == func_task_queue \n"	);
    uint32_t tail, head, mask, next;
    int ok;
    mask = func_task_queue->tail.mask;
    do {

        tail = func_task_queue->tail.first;
        head = func_task_queue->head.second;
 
        if ((tail == head) || (tail > head && (head - tail) > mask))
        {
        //为空就睡眠
        DEBUG("The func_task_queue_t is empty\n ");
        return FUNC_TASK_ERR_QUEUE_EMPTY;
        }
         
        next = tail + 1;
        ok = __sync_bool_compare_and_swap(&func_task_queue->tail.first, tail, next);
    } while (!ok);
   
     item =  ( func_task_queue->item[tail & mask] );

    asm volatile ("":::"memory");

    while (unlikely((func_task_queue->tail.second != tail)))
        _mm_pause();

    func_task_queue->tail.second = next;
    return 0;
}  
/* 下面是关于循环数组缓冲区的操作相关的操作*/
// 停日志后,重建 缓冲区
inline int reinit_func_task_queue(func_task_queue_t * func_task_queue,uint32_t max)  
{  
    delete func_task_queue->item;  
  
    return init_func_task_queue(func_task_queue, max);  
} 

  //清除日志缓冲队列
int destroy_func_task_queue(func_task_queue_t * func_task_queue)  
{  
    //delete func_task_queue->item ;  //会自动删除
    //delete func_task_queue;
} 

//______________________________________________________________________________
								
//全局就绪队列
class wait_func_queue_t
{
	  func_task_queue_t inner_queue; // 等待队列
public:
	inline  void init(uint32_t size)
	  {
	  	 reinit_func_task_queue( &inner_queue,size );
	  }
	  wait_func_queue_t(){
	  	init_func_task_queue   ( &inner_queue,1024 );
	  	}
	  ~wait_func_queue_t( )
	  {
	   destroy_func_task_queue (&inner_queue );
	  }
	  
	  
  inline  int push(func_task_t&  in)
    {
     if(NULL != &in)
     {
     	DEBUG(" push(func_task_t&  in); \n");
     	int ret = 0;
     	ret = en_func_task_queue( &inner_queue, in  );
     	//inner_queue.push (jmp_buf_temp);   
     	return ret;
     }
     else return -1;
    
    }
    
      inline  int push(std::function<void (void )>&  in)
    {
     if(NULL != &in)
     {
     	DEBUG(" push(func_task_t&  in); \n");
     	int ret = 0;
     	func_task_t func_task(in);
     	ret = en_func_task_queue( &inner_queue, func_task  );
     	//inner_queue.push (jmp_buf_temp);   
     	return ret;
     }
     else return -1;
    
    }
    
  inline  int  pop(func_task_t&  out)
    {  
     	  DEBUG(" pop(func_task_t&  out) \n");
     	  int ret = 0;
        ret =  de_func_task_queue( &inner_queue,out  );
     	  return ret;
    }
    
    //从等待队列中拿出一个执行
    template<class put_once_t>
    int schedule(put_once_t& put_once_func)
    {
    	DEBUG("Enter  wait_func_queue_t::schedule()\n");
    	func_task_t func_task;
    	int ret = 0;
    	while( FUNC_TASK_ERR_QUEUE_EMPTY != ( ret = pop( func_task ) ) )
    		{
    			DEBUG("In ready_queue_t::schedule(),put_once_func() \n");
    				std::function<void* (void* )> this_process=[=](void * a){
									func_task.process();
									return (void*) 0;
									} ;  
					put_once_func(this_process,(void *)0);    			
    		}
      DEBUG("Leave  wait_func_queue_t::schedule()\n");
    	return ret;
    }
        //从等待队列中拿出一个立即执行
    int schedule_one_now( )
    {
    	DEBUG("Enter  wait_func_queue_t::schedule_one_now()\n");
    	func_task_t func_task;
    	int ret = 0;
    	if( FUNC_TASK_ERR_QUEUE_EMPTY != ( ret = pop( func_task ) ) )
    		{
    			DEBUG("In ready_queue_t::schedule_one_now(),run_now() \n");
					(func_task.process)();    			
    		}
      DEBUG("Leave  wait_func_queue_t::schedule_one_now()\n");
    	return ret;
    }
    
    
    wait_func_queue_t (wait_func_queue_t && move)
    {
    	inner_queue = move.inner_queue;
    }
    void operator = (wait_func_queue_t && move)
    {
    	inner_queue = move.inner_queue;
    }
    



};

}
#endif
