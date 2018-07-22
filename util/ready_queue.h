#ifndef ALREAD_QUEUE
#define ALREAD_QUEUE

#include "cas_ring.h"
//#include <setjmp.h>
#include <ucontext.h>
#include <list>
#include <iterator>
#define  WATING  1  
#define  READY   2  

struct jmp_buf_type;
typedef jmp_buf_type* jmp_buf_type_ptr;
//typedef ucontext_t jmp_buf_type;

//针对一个线程的 所以无锁

template<class jmp_buf_type>
struct jmp_buf_type_group
{
	typedef std::list<jmp_buf_type *> listype;
	std::list<jmp_buf_type *> ready_list;
	std::list<jmp_buf_type *> waite_list;
		
	inline  int push(jmp_buf_type *  jmp_buf_temp)
  {
	  if( READY == jmp_buf_temp->state)
	  ready_list.push_back(jmp_buf_temp);
	  else 
	  {
	  waite_list.push_back(jmp_buf_temp);
	  jmp_buf_temp->waite_position  = waite_list.end()-1;
	  }
	
  }
  
  inline int work()
  {

  	jmp_buf_type * one= ready_list.front();
  	ready_list.pop_front();
  	one->set_context();

    return 0;
  }

};

struct jmp_buf_type
{
	typedef jmp_buf_type* pointer;
	typedef  jmp_buf_type_group<jmp_buf_type>::listype::iterator iterator_type;
	iterator_type waite_position;
	int state; //状态  
	ucontext_t  context;
  jmp_buf_type_group<jmp_buf_type> * group;
	jmp_buf_type(jmp_buf_type_group<jmp_buf_type>* _group):group(_group)
	{
		state = READY;
		get_context();
		
	}
	jmp_buf_type(){}
	//jmp_buf    env;  
  inline	int set_context()
	{	
	  return	setcontext(&context);
	  //return setjmp(env);
	}
	inline int get_context()
	{	
	  return	getcontext(&context);
	  //longjmp(env,2);
	  //return 0;
	}
	inline int swap( jmp_buf_type& new_context)
	{
		return swapcontext(&context, &(new_context.context) );
	}
	//要考虑线程安全
	inline void active()
	{
		if( WATING == state)
		{
		state = READY;
		
		group->waite_list.erase(waite_position);
		group->ready_list.push_back(this);
	  }
	  
	  
	}
	
	void yield()
	{
		while(!group->ready_list.empty() )
  	{
		group->work();
	  }
	  
	}
	
};




CAS_RING_STRUCT( jmp_buf_type_ptr )

								
//全局就绪队列
class ready_queue_t
{
	    //std::queue<jmp_buf_type> already_queue;
public:
	inline  void init(uint32_t size)
	  {
	  	 CAS_RING_REINIT( jmp_buf_type_ptr,already_queue,size );
	  }
	  ready_queue_t(){
	  	CAS_RING_INIT( jmp_buf_type_ptr,already_queue,1024 );
	  	}
	  ~ready_queue_t( )
	  {
	   CAS_RING_DESTORY(jmp_buf_type_ptr, already_queue );
	  }
	  
	  
  inline  int push(jmp_buf_type_ptr  jmp_buf_temp)
    {
     if(NULL != &jmp_buf_temp)
     {
     	DEBUG(" push(jmp_buf_type * jmp_buf_p); \n");
     	int ret = 0;
     	ret = CAS_RING_EN( jmp_buf_type_ptr,already_queue, &jmp_buf_temp  );
     	//already_queue.push (jmp_buf_temp);   
     	return ret;
     }
     else return -1;
    
    }
    
  inline  int  pop( jmp_buf_type_ptr  jmp_buf_temp )
    {  
     	DEBUG(" pop(jmp_buf_type * jmp_buf_p); \n");
     	  int ret = 0;
        ret =  CAS_RING_DN( jmp_buf_type_ptr,already_queue, &jmp_buf_temp  );
     	  //jmp_buf_temp = already_queue.front();
     	  //already_queue.pop();
     	  return ret;
    }
    
    //从等待队列中拿出一个执行
    int schedule()
    {
    	DEBUG("Enter  ready_queue_t::schedule()\n");
    	int ret = 0;
    	jmp_buf_type  jmp_buf_temp;
    	jmp_buf_type jmp_buf_temp2;
    	jmp_buf_temp2.get_context();
    	if( !( ret = pop( &jmp_buf_temp ) ) )
    		{
    			DEBUG("In ready_queue_t::schedule(),longjmp() \n");
    			//longjmp( jmp_buf_p,2 );
    			
    		 jmp_buf_temp2.swap(jmp_buf_temp);  
     	   //jmp_buf_temp2.set_context();  	
    			return 0;
    			
    		}
       	DEBUG("Leave  ready_queue_t::schedule()\n");
    		return ret;
    }
        //从等待队列中拿出一个执行
    int schedule_one(jmp_buf_type_ptr  jmp_buf_temp2)
    {
    	DEBUG("Enter  ready_queue_t::schedule_one()\n");
    	int ret = 0;
    	jmp_buf_type  jmp_buf_temp;
    	if( !( ret = pop( &jmp_buf_temp ) ) )
    		{
    			DEBUG("In ready_queue_t::schedule_one(),longjmp() \n");
    			//longjmp( jmp_buf_p,2 );
    			
    		 jmp_buf_temp2->swap(jmp_buf_temp);  
     	   //jmp_buf_temp2.set_context();  	
    			return 0;
    			
    		}
       	DEBUG("Leave  ready_queue_t::schedule_one()\n");
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
    
    CAS_RING_TYPE(jmp_buf_type_ptr,already_queue)            // 等待队列




};

#endif




		
  		
  		

