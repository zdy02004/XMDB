#include "../../cthread_pool.h"
#include "../../cas_ring.h"

CAS_RING_STRUCT(int)
 
 
void *myprocess1 (void *arg)
{  
int in = 1;
int out;
int j = 0;
int err;

for(;j<10	;++j)
{

if(!CAS_RING_EN(int,arg,&j) )
{
	printf("in is %ld\n",j);
	//printf("+ arg->tail.mask is %d ,arg->tail.size is %d ,arg->tail.first is %d , arg->tail.second is %d \n",((cas_ring_int_t *) arg)->tail.mask ,((cas_ring_int_t *) arg)->tail.size ,((cas_ring_int_t *) arg)->tail.first, ((cas_ring_int_t *) arg)->tail.second );\

	if( !(err = CAS_RING_DN(int,arg,&out) ) )
	{
		printf("out is %ld\n",out);

	}
	else printf("err is %ld\n",err);
	}
		//printf("- arg->tail.mask is %d ,arg->tail.size is %d ,arg->tail.first is %d , arg->tail.second is %d \n",((cas_ring_int_t *) arg)->tail.mask ,((cas_ring_int_t *) arg)->tail.size ,((cas_ring_int_t *) arg)->tail.first, ((cas_ring_int_t *) arg)->tail.second );\

}
     return NULL;
}  

void * myprocess2 (void *arg)  
{  
	printf("myprocess2  \n");
	 return NULL;  
	
}

                         
int main(int arc,char *arcv[])
{
	
	
//	test_main( arc,arcv);
CAS_RING_TYPE(int,x_int);
CAS_RING_INIT(int,x_int,1024);
//	
	CThread_pool_t  *pool = (CThread_pool_t *) malloc (sizeof (CThread_pool_t));
  thread_pool_init (pool,10,1024*8);/*线程池中最多三个活动线程*/  

    int i;  
    for (i = 0; i <10; i++)  
    {  
        thread_pool_add_task ( pool,myprocess1, x_int );  
       // myprocess1(x_int);

    }  
    /*等待所有任务完成*/   
 thread_pool_destroy (pool);  
 //
 //必须在线程池结束后才能销毁 cas_ring
CAS_RING_STOP(int,x_int) ;
CAS_RING_DESTORY(int,x_int);



return 0;
}  
