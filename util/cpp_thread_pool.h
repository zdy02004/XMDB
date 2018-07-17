//g++ -std=c++11 -g -lpthread cpp_thread_pool.cpp  -o cpp_thread.exe
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h> 
#include <unistd.h>  
#include <sys/types.h>  
//#include <pthread.h>  
#include <thread>
#include <condition_variable>
#include <assert.h>  
#include <emmintrin.h>
#include <string.h>
#include <functional>
#include<vector>
#include "log/log_util.h"
#ifndef __CPPTHREAD_POOL__
#define __CPPTHREAD_POOL__
namespace cpp_thread_namespace{

#define aligend_2_n(x)  (1<<((32-__builtin_clz(x))))


#ifndef likely
#define likely(x)     __builtin_expect((x), 1)
#endif

#ifndef unlikely
#define unlikely(x)   __builtin_expect((x), 0)
#endif

#define CACHE_LINE_SIZE     64
  
#define THREAD_TASK_ERR_QUEUE_ALLOC_FAILED      45014
#define THREAD_TASK_ERR_QUEUE_FULL 					    45015
#define THREAD_TASK_ERR_QUEUE_EMPTY 				    45016  
#define THREAD_POOL_IS_STOPED                   45017
 
#define PThread_T   pthread_t
#define PTHREAD_CREATE(a,b,c,d)    pthread_create(a,b,c,d)
//��ʱ�û�������ʾ˯����
//#define THREAD_TASK_QUEUE_SLEEP_LOCK_T        std::mutex
//#define THREAD_TASK_QUEUE_SLEEP_LOCK(x)       (x).lock()
//#define THREAD_TASK_QUEUE_SLEEP_UNLOCK(x)     (x).unlock()
//#define THREAD_TASK_QUEUE_SLEEP_LOCK_INIT(x)  
//#define THREAD_TASK_QUEUE_SLEEP_LOCK_DEST(x)  
//
////��ʱ�û�������������
//#define THREAD_TASK_QUEUE_SLEEP_COND_T              std::condition_variable  
//#define THREAD_TASK_QUEUE_SLEEP_COND_INIT(x)        
//#define THREAD_TASK_QUEUE_SLEEP_COND_DEST(x)        
//#define THREAD_TASK_QUEUE_SLEEP_COND_WAIT(x,y)      std::unique_lock <std::mutex> lck((y));\
//																										(x).wait(lck);
//#define THREAD_TASK_QUEUE_SLEEP_COND_SIGN(x)        DEBUG("notify_one()\n");(x).notify_all()
//#define THREAD_TASK_QUEUE_SLEEP_COND_BROADCAST(x)   (x).notify_all()
 
 
//��ʱ�û�������ʾ˯����
#define THREAD_TASK_QUEUE_SLEEP_LOCK_T        pthread_mutex_t
#define THREAD_TASK_QUEUE_SLEEP_LOCK(x)       pthread_mutex_lock(&(x))
#define THREAD_TASK_QUEUE_SLEEP_UNLOCK(x)     pthread_mutex_unlock(&(x))   
#define THREAD_TASK_QUEUE_SLEEP_LOCK_INIT(x)  pthread_mutex_init(&(x),0)
#define THREAD_TASK_QUEUE_SLEEP_LOCK_DEST(x)  pthread_mutex_destroy(&(x)) 

//��ʱ�û�������������
#define THREAD_TASK_QUEUE_SLEEP_COND_T              pthread_cond_t  
#define THREAD_TASK_QUEUE_SLEEP_COND_INIT(x)        pthread_cond_init(&(x), NULL)
#define THREAD_TASK_QUEUE_SLEEP_COND_DEST(x)        pthread_cond_destroy(&(x))
#define THREAD_TASK_QUEUE_SLEEP_COND_WAIT(x,y)      DEBUG("wait()\n");pthread_cond_wait(&(x), &(y))
#define THREAD_TASK_QUEUE_SLEEP_COND_SIGN(x)        pthread_cond_signal(&(x))
#define THREAD_TASK_QUEUE_SLEEP_COND_BROADCAST(x)   pthread_cond_broadcast(&(x))
/* 
*�̳߳����������к͵ȴ���������һ��CThread_worker 
*����ѭ��ring�� 
*/  
typedef struct thread_task_entry_t
{  
    /*�ص���������������ʱ����ô˺�����ע��Ҳ��������������ʽ*/  
    std::function<void * (void *)> process ;  
    void *arg;/*�ص������Ĳ���*/    
    thread_task_entry_t(){}
    thread_task_entry_t( thread_task_entry_t & _move)
    {
    	process = _move.process;
    	arg     = _move.arg;
    }
    thread_task_entry_t( thread_task_entry_t && _move)
    {
    	process = std::move(_move.process);
    	arg     = _move.arg;
    }
     void operator =( thread_task_entry_t & _move)
    {
    	process = _move.process;
    	arg     = _move.arg;
    }
    
    void operator =( thread_task_entry_t && _move)
    {
    	process = std::move(_move.process);
    	arg     = _move.arg;
    }
} thread_task_entry_t;  
  
  
typedef struct thread_task_queue_t {
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
    THREAD_TASK_QUEUE_SLEEP_LOCK_T  sleep_locker; //������˯����
    int                             is_sleeping;  //�Ƿ���˯��
    THREAD_TASK_QUEUE_SLEEP_COND_T  sleep_cond;   //������˯����������
    thread_task_entry_t    * item;
}thread_task_queue_t;
//__________________________________________________________

inline int init_thread_task_queue  (thread_task_queue_t * thread_task_queue, uint32_t max);
inline int en_thread_task_queue    (thread_task_queue_t * thread_task_queue, thread_task_entry_t & item);
inline int de_thread_task_queue    (thread_task_queue_t * thread_task_queue, thread_task_entry_t & item);
inline int reinit_thread_task_queue(thread_task_queue_t * thread_task_queue, uint32_t max);  
int destroy_task_queue(thread_task_queue_t * thread_task_queue) ; 
class  cpp_thread_pool_t;

inline void* thread_routine ( cpp_thread_pool_t * pool);
//inline void thread_routine_once (const cpp_thread_pool_t * pool)  ;
  
//__________________________________________________________
/*�̳߳ؽṹ*/  
class  cpp_thread_pool_t
{  
    /*�Ƿ������̳߳�*/  
    int shutdown;  
    std::vector<std::thread>  thread_vector;
    /*�̳߳�������Ļ�߳���Ŀ*/  
    int max_thread_num;  
    /*��ǰ�ȴ����е�������Ŀ*/  
    int cur_queue_size;  
public:
	/*�������*/  
    thread_task_queue_t task_queue;  
    ~cpp_thread_pool_t()
    {
    	//if(task_queue)free(task_queue);
    	
    }
inline void  
thread_pool_init (int max_thread_num,uint32_t max_task)  
{  
	 // DEBUG("this->task_queue %ld \n",this->task_queue);
    //this->task_queue = new thread_task_queue_t;//(thread_task_queue_t*) malloc (sizeof (thread_task_queue_t));  

    init_thread_task_queue  (&task_queue, max_task);
  
    this->max_thread_num = max_thread_num;  
    this->cur_queue_size = 0;  
    this->shutdown = 0;  
    int i = 0;  
    for (i = 0; i < max_thread_num; ++i)  
    {   
       // thread_vector.emplace_back( std::thread( thread_routine,this) ); 
          thread_vector.emplace_back( std::thread( thread_routine,this) ); 

    }  
}    

/*���̳߳��м�������*/  
inline int  
add_task ( std::function<void * (void *)> &process, void *arg)  
{  

    /*����һ��������*/  
    thread_task_entry_t item;  
    item.process =  process;  
    item.arg = arg;  
  
    /*��������뵽�ȴ�������*/  
    return en_thread_task_queue(&task_queue, item);  
}  
  
/*�����̳߳أ��ȴ������е����񲻻��ٱ�ִ�У������������е��̻߳�һֱ 
����������������˳�
��ʾ����
*/  
inline int  
thread_pool_destroy ()  
{  
    if (this->shutdown)  
        return -1;/*��ֹ���ε���*/  
    this->shutdown = 1;  
   
   THREAD_TASK_QUEUE_SLEEP_LOCK((task_queue.sleep_locker));
   task_queue.is_sleeping = 2;
   THREAD_TASK_QUEUE_SLEEP_UNLOCK((task_queue.sleep_locker));
  
    /*�������еȴ��̣߳��̳߳�Ҫ������*/  
    THREAD_TASK_QUEUE_SLEEP_COND_BROADCAST((task_queue.sleep_cond));  
  
    /*�����ȴ��߳��˳�������ͳɽ�ʬ��*/  
    int i;  
    for (i = 0; i < this->max_thread_num; i++)  
         thread_vector[i].join();  
    thread_vector.clear();
         
    /*���ٵȴ�����*/  
     destroy_task_queue(&task_queue);
    
    /*���������ͻ�����Ҳ����������*/  
    //pthread_mutex_destroy(&(this->task_queue->queue_lock));  
    //pthread_cond_destroy(&(this->task_queue->queue_ready));  
  //  free (this->task_queue);
    /*���ٺ�ָ���ÿ��Ǹ���ϰ��*/  

    return 0;  
}  

  inline void thread_routine_once ( /*cpp_thread_pool_t * pool */ )  
{  
    DEBUG ("In thread_routine_once (),%x \n",&task_queue);  

   thread_task_entry_t item; 
   int ret;
       ret = de_thread_task_queue( &task_queue, item) ;
       if(1 == ret)return ;
       (item.process) (item.arg);  
    /*�������еȴ��̣߳��̳߳�Ҫ������*/  
  //    THREAD_TASK_QUEUE_SLEEP_COND_BROADCAST((task_queue.sleep_cond));  
    return ;
}  

};  



inline void* thread_routine (cpp_thread_pool_t * pool)  
{  
    //DEBUG ("starting thread 0x%x\n", pthread_self ());  
    int ret;
    thread_task_entry_t item; 
    while (1)  
    {  
       //THREAD_TASK_QUEUE_SLEEP_LOCK_T ((this->queue_lock));  
       ///*����ȴ�����Ϊ0���Ҳ������̳߳أ���������״̬; ע�� 
       //pthread_cond_wait��һ��ԭ�Ӳ������ȴ�ǰ����������Ѻ�����*/  
       //while (this->cur_queue_size == 0 && !this->shutdown)  
       //{  
       //    printf ("thread 0x%x is waiting\n", pthread_self ());  
       //    pthread_cond_wait (&(this->queue_ready), &(this->queue_lock));  
       //}  
  
        /*�̳߳�Ҫ������*/  
       // if (((CThread_pool_t *)pool)->shutdown)  
        //{  
            /*����break,continue,return����ת��䣬ǧ��Ҫ�����Ƚ���*/  
       //     pthread_mutex_unlock (&(this->queue_lock));  
            //DEBUG ("thread 0x%x will exit\n", pthread_self ());  
          //  return (void*)0;
        //}  
  
        //printf ("thread 0x%x is starting to work\n", pthread_self ());  
  
        /*assert�ǵ��Եĺð���*/  
       // assert (this->cur_queue_size != 0);  
       // assert (this->queue_head != NULL);  
          
        /*�ȴ����г��ȼ�ȥ1����ȡ�������е�ͷԪ��*/  
        //this->cur_queue_size--; 
       
        ret = de_thread_task_queue( &(pool->task_queue), item) ;
        if(1 == ret)return (void*)0;
        /*���ûص�������ִ������*/  
        //if(!(item.process)){
        //	//int* i = (((struct param *)(item.arg))->i);
        //	printf("bad item is %ld\n",1);
        //	continue;
        //	}
        (item.process) (item.arg);  
    }  
    /*��һ��Ӧ���ǲ��ɴ��*/  
   return (void*)0;  
}


 
//______________________________________________________

inline int init_thread_task_queue(thread_task_queue_t * thread_task_queue,uint32_t max)  
{  
	DEBUG("init_thread_task_queue\n");
    //thread_task_queue->item = (thread_task_entry_t*)malloc((max+1) * sizeof(thread_task_entry_t));  

    thread_task_queue->item = new  thread_task_entry_t[max+1];
    
    thread_task_queue->max  = max;
    if(!thread_task_queue->item)  
    {  
        //DEBUG("%s\n","Alloc failed,not memory enough");  
        return THREAD_TASK_ERR_QUEUE_ALLOC_FAILED;  
    }  
    THREAD_TASK_QUEUE_SLEEP_LOCK_INIT((thread_task_queue->sleep_locker));
    THREAD_TASK_QUEUE_SLEEP_COND_INIT((thread_task_queue->sleep_cond));
    thread_task_queue->is_sleeping = 0;
    
    thread_task_queue->head.first = thread_task_queue->head.second = 0;
    thread_task_queue->tail.first = thread_task_queue->tail.second = 0;	
	
    thread_task_queue->head.size = thread_task_queue->tail.size = max;
    thread_task_queue->head.mask = thread_task_queue->tail.mask = max-1;
    return 0;  
}  
 // �����
inline int en_thread_task_queue(thread_task_queue_t * thread_task_queue, thread_task_entry_t& item)  
{  
	 // DEBUG("en_thread_task_queue\n"	);
	  if(thread_task_queue->is_sleeping == 2)return THREAD_POOL_IS_STOPED;
	  
    uint32_t head, tail, mask, next;
    int ok;
    mask = thread_task_queue->head.mask;
    do {
        head = thread_task_queue->head.first;
        tail = thread_task_queue->tail.second;
        // ���� �� �ǿ�
        if (((head - tail) > mask) && (!((tail == head) || (tail > head && (head - tail) > mask))))
        	{
        		DEBUG("%ld %s,head=%ld,tail=%ld\n",__LINE__,"The thread_task_queue_t is full",head,tail);
            return THREAD_TASK_ERR_QUEUE_FULL;
            //continue;
          }
        next = head + 1;
        ok = __sync_bool_compare_and_swap(&thread_task_queue->head.first, head, next);
    } while (!ok);

  // memcpy(&(thread_task_queue->item[head & mask]),item,sizeof(thread_task_entry_t));
    thread_task_queue->item[head & mask] =  (item);
    asm volatile ("":::"memory");

    while (unlikely((thread_task_queue->head.second != head)))
        _mm_pause();

    thread_task_queue->head.second = next;
    
    
    // ���д����˯�߾ͻ�����
  // if( 1 == thread_task_queue->is_sleeping)
  //{
  // //DEBUG("en_trans TRANS_QUEUE_SLEEP_LOCK\n"	);
  //  THREAD_TASK_QUEUE_SLEEP_LOCK(&(thread_task_queue->sleep_locker));
  //     if( 1 == thread_task_queue->is_sleeping)
  //		{
   			if(thread_task_queue->is_sleeping!=2)thread_task_queue->is_sleeping = 0;
   	//		DEBUG("TRANS_QUEUE_SLEEP_COND_SIGN\n"	);
   			THREAD_TASK_QUEUE_SLEEP_COND_SIGN((thread_task_queue->sleep_cond));
   //	  }
  //  THREAD_TASK_QUEUE_SLEEP_UNLOCK(&(thread_task_queue->sleep_locker));
  //  }
    
    return 0;  
}  
  // ������
inline int de_thread_task_queue(thread_task_queue_t * thread_task_queue, thread_task_entry_t & item)  
{     
	   DEBUG("Enter de_thread_task_queue\n"	);
     if(NULL == thread_task_queue)ERROR("NULL == thread_task_queue \n"	);
    // DEBUG("thread_task_queue->tail is %d \n",thread_task_queue->tail);
    uint32_t tail, head, mask, next;
    int ok;
    mask = thread_task_queue->tail.mask;
   
    
    do {

        tail = thread_task_queue->tail.first;
        head = thread_task_queue->head.second;
 
        if ((tail == head) || (tail > head && (head - tail) > mask))
        {
        
        //Ϊ�վ�˯��
        THREAD_TASK_QUEUE_SLEEP_LOCK((thread_task_queue->sleep_locker));
        if( 0 == thread_task_queue->is_sleeping)
   		  {
   		  	thread_task_queue->is_sleeping = 1;
   		  }
   		   if(2 == thread_task_queue->is_sleeping)
   		   	{
   		   		THREAD_TASK_QUEUE_SLEEP_UNLOCK((thread_task_queue->sleep_locker));
   		   		return 1;
					}
        	//printf("TASK_QUEUE_SLEEP_COND_WAIT,thread_task_queue->is_sleeping = %ld\n",thread_task_queue->is_sleeping	);
   		  	THREAD_TASK_QUEUE_SLEEP_COND_WAIT((thread_task_queue->sleep_cond),(thread_task_queue->sleep_locker));
   	      DEBUG("Wake up! \n");
   	     THREAD_TASK_QUEUE_SLEEP_UNLOCK((thread_task_queue->sleep_locker));
					ok = 0;
					continue;
         }
         
        next = tail + 1;
        ok = __sync_bool_compare_and_swap(&thread_task_queue->tail.first, tail, next);
    } while (!ok);
   
  // printf("tail & mask= %ld \n",tail & mask);
   // memcpy(item,&(thread_task_queue->item[tail & mask]),sizeof(thread_task_entry_t));
     item =  ( thread_task_queue->item[tail & mask] );

    asm volatile ("":::"memory");

    while (unlikely((thread_task_queue->tail.second != tail)))
        _mm_pause();

    thread_task_queue->tail.second = next;
    return 0;
}  
/* �����ǹ���ѭ�����黺�����Ĳ�����صĲ���*/
// ͣ��־��,�ؽ� ������
inline int reinit_thread_task_queue(thread_task_queue_t * thread_task_queue,uint32_t max)  
{  
    delete thread_task_queue->item;  
  
    return init_thread_task_queue(thread_task_queue, max);  
} 

  //�����־�������
int destroy_task_queue(thread_task_queue_t * thread_task_queue)  
{  
	  THREAD_TASK_QUEUE_SLEEP_COND_DEST((thread_task_queue->sleep_cond));
	  thread_task_queue->is_sleeping = 0;
	  THREAD_TASK_QUEUE_SLEEP_LOCK_DEST((thread_task_queue->sleep_locker));
    //delete thread_task_queue->item ;  //���Զ�ɾ��
    //delete thread_task_queue;
} 
//_________________________________________________________ 
 
 
//    �����ǲ��Դ���  
int  
test_cpp_thread_main (int argc, char **argv)  
{  
	cpp_thread_namespace::cpp_thread_pool_t  pool ;  
  pool.thread_pool_init (8,1024);/*�̳߳������������߳�*/  
    
  std::function<void * (void *)> myprocess = [&](void * a){
  	printf ("threadid is 0x%x\n", pthread_self ());  
    sleep (1);/*��Ϣһ�룬�ӳ������ִ��ʱ��*/  
    return (void *)NULL;
    };
      
    /*���������Ͷ��10������*/  
    int i;  
    for (i = 0; i < 10; i++)  
    {  
        pool.add_task (myprocess, (void*)0);  
    }  
    /*�ȴ������������*/  
   
    /*�����̳߳�*/  
    pool.thread_pool_destroy ();  
  
    return 0;  
}  

}


#endif 
