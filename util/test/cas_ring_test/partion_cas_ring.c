#include "../../patition_cas_ring.h"
#include "../../cthread_pool.h"

PARTION_CAS_RING_STRUCT(int)
 
 
void *  
myprocess1 (void *arg)  
{  
int in = 1;
int out;
int j = 0;
	
for(;j<10;++j){
PARTION_CAS_RING_EN(int,arg,&j)
PARTION_CAS_RING_DN(int,arg,&out)
printf("out is %ld\n",out);
}
    return NULL;  
}  

void *  
myprocess2 (void *arg)  
{  
	printf("myprocess2  \n");
	 return NULL;  
	
}

                         
int main(int arc,char *arcv[])
{
	
	
	
PARTION_CAS_RING_TYPE(int,x_int);
PARTION_CAS_RING_INIT(int,x_int,1024,8);
	
	CThread_pool_t  *pool = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));
  thread_pool_init (pool,10,1024);/*线程池中最多三个活动线程*/  
  
   int i;  
    for (i = 0; i <10; i++)  
    {  
        thread_pool_add_task ( pool,myprocess1, x_int );  
    }  
    /*等待所有任务完成*/  
 thread_pool_destroy (pool);  
 //
 //必须在线程池结束后才能销毁 cas_ring
 PARTION_CAS_RING_STOP(int,x_int) 
 PARTION_CAS_RING_DESTORY(int,x_int)



return 0;
}  
