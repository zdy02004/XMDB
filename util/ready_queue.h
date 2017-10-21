#ifndef ALREAD_QUEUE
#define ALREAD_QUEUE

#include "cas_ring.h"


#ifndef _JMP_BUF_
#define _JMP_BUF_
#include <setjmp.h>
typedef jmp_buf *  jmp_buf_ptr;
CAS_RING_STRUCT( jmp_buf_ptr )
#endif 

//全局就绪队列
class ready_queue_t
{
public:
	  void init(uint32_t size)
	  {
	  	 CAS_RING_INIT( jmp_buf_ptr,already_queue,size );
	  }
	  
	  ~ready_queue_t( )
	  {
	  	 CAS_RING_DESTORY(jmp_buf_ptr, already_queue );
	  }
	  
	  
    int push(jmp_buf_ptr * jmp_buf_p)
    {
     if(NULL != jmp_buf_p)
     {
     	return CAS_RING_EN( jmp_buf_ptr,already_queue, jmp_buf_p  );
     }
     else return -1;
    
    }
    
    int  pop( jmp_buf_ptr * jmp_buf_p )
    {
      if(NULL != jmp_buf_p)
      {
     	  return CAS_RING_DN( jmp_buf_ptr,already_queue,jmp_buf_p  );
      }
       else return -1;
    
    }
    
    //从等待队列中拿出一个执行
    int schedule()
    {
    	int ret = 0;
    	jmp_buf_ptr  jmp_buf_p;
    	if( !( ret = pop( &jmp_buf_p ) ) )
    		{
    			longjmp( *jmp_buf_p,2 );
    			return 0;
    		}
    		
    		return ret;
    }
    ready_queue_t (ready_queue_t && move)
    {
    	already_queue = move.already_queue;
    }
    void operator = (ready_queue_t && move)
    {
    	already_queue = move.already_queue;
    }
    
     CAS_RING_TYPE(jmp_buf_ptr,already_queue)            // 等待队列
    



};

#endif




		
  		
  		

