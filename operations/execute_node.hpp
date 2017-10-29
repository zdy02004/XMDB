//  g++ -C execute_node.hpp -std=c++11
#ifndef EXEC_NODE
#define EXEC_NODE

#include <tuple>
#include <type_traits>
#include <utility>
#include <functional>
#include <atomic>
#include <memory>

#include "../util/func_task_t.hpp"
#include "../util/cpp_thread_pool.h"


#define DEFAULT_RING_BUF  1024
#define DEFAULT_READY_BUF 1024*1024*16

//#ifndef _JMP_BUF_
//#define _JMP_BUF_
//typedef jmp_buf *  jmp_buf_type;
//CAS_RING_STRUCT( jmp_buf_type )
//#endif 


// 使用tuple 作为函数参数列表
template<size_t N>
struct Apply {
template<typename F, typename T, typename... A>
static inline auto apply(F && f, T && t, A &&... a)
-> decltype(Apply<N-1>::apply(
::std::forward<F>(f), ::std::forward<T>(t),
::std::get<N-1>(::std::forward<T>(t)), 
::std::forward<A>(a)...
))
{
return Apply<N-1>::apply(::std::forward<F>(f), 
::std::forward<T>(t),
::std::get<N-1>(::std::forward<T>(t)), 
::std::forward<A>(a)...
);
}
};

template<>
struct Apply<0> {
template<typename F, typename T, typename... A>
static inline auto apply(F && f, T &&, A &&... a)
-> decltype(::std::forward<F>(f) 
(::std::forward<A>(a)...))
{
return ::std::forward<F>(f)(::std::forward<A> 
(a)...);
}
};

template<typename F, typename T>
inline auto apply(F && f, T && t)
-> decltype(Apply< ::std::tuple_size<
typename ::std::decay<T>::type
>::value>::apply(::std::forward<F>(f), 
::std::forward<T>(t)))
{
return Apply< ::std::tuple_size<
typename ::std::decay<T>::type
>::value>::apply(::std::forward<F>(f), 
::std::forward<T>(t));
}

//懒执行函数包装器
template<class Funtype,typename ... Args>
struct exec_fun
{
	Funtype  f;
	std::tuple<Args...> _arguments;
	
	exec_fun(Funtype && _f,Args... args ):f(std::forward<Funtype>(_f)),_arguments(std::make_tuple(args...)){}
        exec_fun(){}
  
  
	typedef typename std::result_of<Funtype(Args...)>::type  ret_type;

        void swap(exec_fun< Funtype,Args...> & node)
        {
  	      f = std::move(node.f);
  	     _arguments = 	std::move(node._arguments);
        }
        
  
   exec_fun ( exec_fun<Funtype,Args...> && node )
   {
   	//swap( std::forward< exec_fun<Funtype,Args...> >(move));
   	f = std::move(node.f);
  	 _arguments =std::move(node._arguments);
   }     
   
   void operator = (exec_fun<Funtype,Args...> && node)
   {
   	  //swap( std::forward< exec_fun<Funtype,Args...> >(move));
   	  f = std::move(node.f);
  	 _arguments =std::move(node._arguments);
   }
        

	//inline auto exe() -> decltype(f(std::forward<Arg1>(arg1),std::forward<Arg2>(arg2),std::forward<Arg3>(arg3),std::forward<Arg4>(arg4)))
	inline ret_type exe() 
	{
	   return apply( f, _arguments);
	}
	
};



#define OPERATION_START    1
#define OPERATION_END      2
#define OPERATION_RUNING   3
/*  
定义依赖执行节点

pre_node1    							  <--(依赖)    current_node    <--(依赖)    out_node
   |																																			|
   |brother（上面和下面的节点是并行的关系）																|brother（上面和下面的节点是并行的关系）
   |																																			|
pre_node2																															out_node2
   |																																			|
   |brother																																|brother
   |																																			|
pre_node3      																												out_node3
	 |																																			|
	NULL																																	 NULL
*/

//static ready_queue_t    ready_queue;					//全局就绪队列
	typedef std::function <int( std::function<void * (void *)> &, void *)>  put_once_t ;

// 物理执行计划
// 处理节点
// pre_type     前继节点类型
// brother_type 兄弟节点类型
// OpperType    操作节点类型
template<class pre_type,class brother_type,class OpperType>
struct exec_node_type
{

	typedef pre_type  				pre_type_;
	//typedef out_type  				out_type_;
	typedef brother_type  		brother_type_;
	typedef OpperType  				OpperType_;
	
	 //执行节点返回类型
	typedef typename OpperType::ret_type  ret_type; 
  
         //前继节点类型
	typedef exec_node_type<typename pre_type_::pre_type_ , typename pre_type_::brother_type_,
									  typename pre_type_::OpperType_
								   > input_node_type;		 	

	//后继节点类型							 	
	//typedef exec_node<typename out_type_::FunType_, typename out_type_::Arg1_ , typename out_type_::Arg2_ , 
	//																						 typename out_type_::Arg3_ , typename out_type_::Arg4_ , 
	//							 typename out_type_::pre_type_,typename out_type_::out_type , typename out_type_::brother_type_  > output_node_type;
								 
	
  int    						operation_type;	//操作类型
  short  						is_start_end;		//是否是开始节点 1 开始   2 结束		
  std::atomic<bool> is_done;				//是否结束  0 未结束   1  结束
  OpperType 				exec_node;   		//执行节点
  
  input_node_type		* input_node;//前继依赖节点
  brother_type      * brother;	 //前继依赖兄弟节点 
  ret_type 						ret;			 //执行结果集 默认为指针类型
  cpp_func_task_namespace::wait_func_queue_t   wait_queue;//等待队列	
  std::function<void(void)>    call_once_thread_poll;//线程池一次取任务干活
  put_once_t               put_once_to_thread_poll;  //往线程池一次取任务干活
  
  //jmp_buf_type  *jump_point;                           //  线程上下文
  //jmp_buf_type   jump_loop;
  exec_node_type(int _operation_type ):operation_type(_operation_type),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
  	{
  		is_done.store(0);
  		call_once_thread_poll = [](void){DEBUG("Empty call_once\n");return;};
  		put_once_to_thread_poll = [](std::function<void * (void *)> &,void *){return  0;};
  	}
  	  	//普通 同move	 语义
  	exec_node_type( exec_node_type< pre_type, brother_type, OpperType>& move )
  	{
  		operation_type = move.operation_type;
  		is_start_end   = move.is_start_end;
  		is_done.store(move.is_done.load());
  		exec_node      = std::move(move.exec_node);	
  		input_node     = move.input_node;
  		brother        = move.brother;
  		ret	           = move.ret;	      //默认为指针类型
  		wait_queue     = std::move(wait_queue);	
  		call_once_thread_poll  = std::move(move.call_once_thread_poll);	
  		put_once_to_thread_poll= std::move(move.put_once_to_thread_poll);	
  		//jump_point     = move.jump_point;	 
  	}
  	//move 语义
  	exec_node_type( exec_node_type< pre_type, brother_type, OpperType>&& move )
  	{
  		operation_type = move.operation_type;
  		is_start_end   = move.is_start_end;
  		is_done.store(move.is_done.load());
  		exec_node      = std::move(move.exec_node);	
  		input_node     = move.input_node;
  		brother        = move.brother;
  		ret	           = move.ret;	      //默认为指针类型
  		wait_queue     = std::move(wait_queue);	
  		call_once_thread_poll  = std::move(move.call_once_thread_poll);
  		put_once_to_thread_poll= std::move(move.put_once_to_thread_poll);		
  		//jump_point     = move.jump_point;	 
  	}
  	void operator = ( exec_node_type< pre_type, brother_type, OpperType>&& move )
  	{
  		operation_type = move.operation_type;
  		is_start_end   = move.is_start_end;
  		is_done.store(move.is_done.load());
  		exec_node      = std::move(move.exec_node);	
  		input_node     = move.input_node;
  		brother        = move.brother;
  		ret	           = move.ret;	      //默认为指针类型
  		wait_queue	   = std::move(wait_queue);	
  		call_once_thread_poll = std::move(move.call_once_thread_poll);	
  		put_once_to_thread_poll= std::move(move.put_once_to_thread_poll);		
  		//jump_point     = move.jump_point;	 
  	}
  	
  ~exec_node_type()
  	{
  		//销毁等待队列
  		//CAS_RING_DESTORY(jmp_buf_type,wait_queue);
  	}
   //设置执行函数
  void set_wait_queue_size(uint32_t size)
  {
  		 wait_queue.init( size );
	 
  }
  //设置执行函数
  void set_exec(OpperType & _exec_node)
  {
  	exec_node.swap(_exec_node);
  }
  
   //设置前继节点
  void set_input_node(input_node_type & _input_node )
  {
  	input_node = &_input_node;
  }
  
   //设置兄弟节点
  void set_brother_node(brother_type & _brohter_node )
  {
  	brother = &_brohter_node;
  }
  // 设置调用一次 线程池执行函数，这里规定该函数为 void(void)
  void set_call_once(std::function<void(void)>  _call_once)
  {
  	call_once_thread_poll = std::move(_call_once);
  }
  
  void set_put_once(put_once_t  _put_once)
  {
  	put_once_to_thread_poll = std::move(_put_once);
  }
  
	inline int check( int * pre_brother)
	{
	 return 0;  //退出返回
	}
	
        //递归检查前继节点
	template<class T>
	inline int check( T*  pre_brother)
	{
	 if(pre_brother->brother == NULL)return 0;  //退出返回
	 typename T::brother_type_ * brother_tmp = pre_brother->brother;
	 int ret = check_isdone(brother_tmp);
	 if( ret == 1 )return 1;                    //中断返回
	 if( ret == 0 )return 0;                    //退出返回
	 return check(brother_tmp) ;
	
	}
	  //递归检查前继节点
	template<class T>
	inline int check_isdone( T*  brother_tmp)
	{
		if(brother_tmp->is_done.load()!= true)return 1;       //中断返回
	        else return 2;
  }
  	inline int check_isdone( int*  brother_tmp)
	{
		return 0;
  }
  inline void empty_call_once()
  {
  	return ;
  }

  template<class Funtype,typename ... Args>
inline exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
		   exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
		   exec_fun<Funtype,Args...> > 
	 then(exec_fun<Funtype,Args...> & later_func )
	{
		// then 节点类型
	//std::shared_ptr<
				exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
												exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
												exec_fun<Funtype,Args...> >   
	//									>   
		then_exec_node(OPERATION_RUNING);
		//= std::make_shared<
		//		exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
		//										exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
		//										exec_fun<Funtype,Args...> >   
		//								> 
		
		
		// 设置执行器								
    		then_exec_node.set_exec(later_func);
		// 设置前继依赖项为 this
    		then_exec_node.set_input_node(*this);
    // 传递依赖 线程池的 put_once 函数
    		then_exec_node.set_put_once(this->put_once_to_thread_poll);
    // 传递依赖 线程池的 call_once 函数
    		then_exec_node.set_call_once(this->call_once_thread_poll);
        // 扔进线程池
        //DEBUG("put_once_to_thread_poll() \n");
    		//std::function<void * (void *)> process  =[&](void * a)	 {
    		//	then_exec_node.try_execute();
    		//	return (void *)0;
    		//};    		
    		//put_once_to_thread_poll(process,(void *)0);
    		
    		// 扔进等待队列
    		DEBUG("put_once_to_wait_queue() \n");
    		std::function<void (void )> this_process=[&](){
				this->try_execute();
				} ;  
				input_node->wait_queue.push( this_process );
    		
			  DEBUG("Leave then	() \n");
		return  ( then_exec_node );
	}
	
	template<class Funtype,typename ... Args>
  inline   exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
			   exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
			   exec_fun<Funtype,Args...> >
	 then( Funtype f,Args... args ) 
	{		
		exec_fun<Funtype,Args...> later_func ( std::forward<Funtype>(f) ,args ...);
		return then( later_func  );
	}
  	//执行本节点
	inline int try_execute()
	{
		  //1 所有的前继节点都结束
		  int first_check = 0;
		  do
		  {
		  	//DEBUG(" In Do !\n");
					if( input_node != NULL  )
					{
						DEBUG(" input_node != NULL \n");
						typename input_node_type::brother_type_ * brother_tmp =input_node->brother;
				   	//前继节点或者前继的兄弟节点没执行完，就把自己放到前景节点的等待队列中，然后退出
				   	if ( check(brother_tmp) || false == input_node->is_done.load()  )
					  {
					  	DEBUG(" input_node is working \n");
						//首次调用
						if( first_check  == 0 )
							{
								DEBUG(" First execute !\n");				
							  first_check = 2;
								std::function<void (void )> this_process=[&](){
									this->try_execute();
									} ;  
								input_node->wait_queue.push( this_process );
								
								// 如果首次调用后，依赖项就执行完了，为了不使用锁，这里回滚上一步操作
								if( !( check(brother_tmp) || input_node->is_done.load() == 0 ) )
									{
										DEBUG("ROLL BACK \n");
										input_node->wait_queue.schedule(put_once_to_thread_poll);
									}
									return 0;
							}
					   else 
					   	{
									{
										 // 正常情况不对到达此分支
										 call_once_thread_poll();
									}
					   	}
					  }
					  //依赖节点都执行完就退出
					  else break;
					}
					else break;
			
		  }while( true );
		DEBUG("exec_node.exe() \n");
		//2 执行本节点任务
		ret = exec_node.exe(); 
	  is_done.store(true);	  	
    DEBUG(" Before done ==================================\n");
    wait_queue.schedule(put_once_to_thread_poll);
    DEBUG(" After done ==================================\n");
		
	}
	
}__attribute__ ((packed, aligned (64)));

//空执行节点
template <typename ... Args>
struct exec_fun< int,Args...>
{
	typedef  int  ret_type;
	exec_fun(){}
  	void swap(){}
	inline int exe()
	{
	    return 0;
	}
	
};

// 空执行辅助节点
template<class OpperType>
struct exec_node_type<int,int,OpperType>
{
	typedef int             	pre_type_;
	//typedef int  			out_type_;
	typedef int             	brother_type_;
	typedef int  			OpperType_;
	typedef int  			ret_type; 
	typedef int	            	input_node_type;
	//typedef int 			output_node_type;
	exec_fun< int,OpperType>  exec_node;              //执行节点
	short  				is_start_end;															//是否是开始节点 1 开始   2 结束
	std::atomic<bool>      		is_done;			
	input_node_type      	 *      input_node;  	 //前继依赖节点
	brother_type_		 *      brother;         //前继依赖兄弟节点 
	cpp_func_task_namespace::wait_func_queue_t    wait_queue;					   			  //等待队列

	exec_node_type():input_node(NULL),brother(NULL),is_start_end(OPERATION_END),is_done(1){
		}
	inline int try_execute()
	{
	  return 0;
 	}
 	  ~exec_node_type()
  	{
  		//销毁等待队列
  		//CAS_RING_DESTORY(jmp_buf_type,wait_queue);
  	}
};

#endif 
