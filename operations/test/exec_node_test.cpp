//  g++ -w -std=c++11  execute_node.cpp  -o cc.exe  
#include"../execute_node.hpp"

int fun4(int a,int b ,int c )
{
	
	printf("%d,%d,%d\n",a,b,c);
	return 0;
}

int func4(char a,char b ,char c, char d)
{
	
	printf("%c,%c,%c,%c\n",a,b,c,d);
	sleep(3);
	return 0;
}

int func2(int a,int b)
{
	printf("%d,%d\n",a,b);
	return 0;
}

class void_func_helper_t
{
typedef void * (*fun_type)(void *);
std::function<void * (void *)> __process ;

public:
fun_type process;

void * help_process (void *)
{
__process((void *)0);
return (void *)(0);
}

void set_func(std::function<void * (void *)> & _process )
{
  __process = std::move( _process ) ;

}

};

int main()
{
		// 初始化线程池
	  cpp_thread_namespace::cpp_thread_pool_t  pool ;  
    pool.thread_pool_init (2,1024);/*线程池中最多三个活动线程*/ 
	
	//typedef  std::function< int(int,int,int,int )> int_fun;
	typedef int(*int_fun)(int,int,int );
	typedef int(*char_fun)(char,char,char,char );
	typedef int(*int2_fun)(int,int );
	

  // 首节执行器类型
  typedef exec_fun < int_fun,int,int,int    >  ew1_type;
  // 首节点的空前继空兄弟节点类型
	typedef exec_node_type<int,int,ew1_type   >  empty_node_type1;
  // 首节点类型
  typedef exec_node_type<empty_node_type1,empty_node_type1,ew1_type> en_type1;
  // 首节点
  en_type1 enode1(1);
  // 首节执行器
	ew1_type ewraper1(fun4,1,2,3);
	enode1.set_exec(ewraper1);
	//运行首节点
	enode1.try_execute();
	
	
	//2 节点的空兄弟节点
	// 首节执行器类型
  typedef exec_fun < char_fun,char,char,char,char> ew2_type;
	// 2节点的空兄弟节点类型
	typedef exec_node_type<int,int,ew2_type> empty_node_type2;
	//2节点类型
  typedef exec_node_type<en_type1,empty_node_type2,ew2_type> en2_type;
  //2节点
	en2_type enode2(2);
	//2节点执行器
	ew2_type ewraper2(func4,'a','b','c','d');
	enode2.set_exec(ewraper2);
	//设置2节点前继的前继节点
	enode2.set_input_node(enode1 );
	   
	enode2.set_put_once(
	[&](std::function<void * (void *)> &process, void *arg)->int{
	return	pool.add_task(process,arg);
	}
	 );
	 
	 enode2.set_call_once(
	[&](){
	   //cpp_thread_namespace::thread_routine_once(&pool);
	   pool.thread_routine_once();
			 }
	 );
	// then 函数	
	//std::function<void * (void *)> process=[&](void * a){
	//			enode2.then(func2,7,8);
	//		return (void *)0;
	//	};
	//pool.add_task(process,(void *)0);

	enode2.then(func2,7,8);
	//运行2节点
	enode2.try_execute();
	
	//std::function<void * (void *)> process2=[&](void * a){
	//		enode2.try_execute();
	//		return (void *)0;
	//	};
	//pool.add_task(process2,(void *)0);
	
	/*销毁线程池 不要忘记*/  
    pool.thread_pool_destroy ();
	
	return 0;
}
