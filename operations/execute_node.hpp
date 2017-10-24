//  g++ -C execute_node.hpp -std=c++11
#ifndef EXEC_NODE
#define EXEC_NODE

#include <tuple>
#include <type_traits>
#include <utility>
#include <functional>
#include <atomic>

#include "../util/ready_queue.h"

#define DEFAULT_RING_BUF  1024
#define DEFAULT_READY_BUF 1024*1024*16

#ifndef _JMP_BUF_
#define _JMP_BUF_
typedef jmp_buf *  jmp_buf_ptr;
CAS_RING_STRUCT( jmp_buf_ptr )
#endif 


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
  
   exec_fun ( exec_fun<Funtype,Args...> && move )
   {
   	swap( std::forward< exec_fun<Funtype,Args...> >(move));
   }     
   
   void operator = (exec_fun<Funtype,Args...> && move)
   {
   	  swap( std::forward< exec_fun<Funtype,Args...> >(move));
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

static ready_queue_t    ready_queue;					//全局就绪队列

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
								 
	
	int    									operation_type;	//操作类型
	short  									is_start_end;		//是否是开始节点 1 开始   2 结束		
	std::atomic<bool>       is_done;				//是否结束  0 未结束   1  结束
	OpperType 							exec_node;   		//执行节点
	
	input_node_type				  * input_node;					//前继依赖节点
	brother_type          	* brother;						//前继依赖兄弟节点 
	ret_type 									ret;								//执行结果集
  CAS_RING_TYPE(jmp_buf_ptr,wait_queue);				//等待队列
  std::function<void(void)>    call_once_thread_poll;//线程池一次取任务干活
  jmp_buf jump_point;                           //  线程上下文
  
  exec_node_type(int _operation_type ):operation_type(_operation_type),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
  	{
  		is_done.store(0);
  		//初始化等待队列，由其他 exec_node 插入
  		CAS_RING_INIT( jmp_buf_ptr,wait_queue,DEFAULT_RING_BUF );
  		//在类外初始化
  		//ready_queue.init(DEFAULT_READY_BUF);
  		//设置默认 call_once
  		call_once_thread_poll = [](void){return;};
  	}
  	//move 语义
  	exec_node_type( exec_node_type< pre_type, brother_type, OpperType>&& move )
  	{
  		operation_type = move.operation_type;
  		is_start_end   = move.is_start_end;
  		is_done        = std::move(move.is_done);
  		exec_node      = std::move(move.exec_node);	
  		input_node     = move.input_node;
  		brother        = move.brother;
  		ret	       = std::move(move.ret);	
  		wait_queue     = move.wait_queue;	
  		ready_queue    = std::move(move.ready_queue);	
  		call_once_thread_poll = std::move(move.call_once_thread_poll);	
  	        jump_point     =  std::move(move.jump_point);	
  	}
  	void operator = ( exec_node_type< pre_type, brother_type, OpperType>&& move )
  	{
  		operation_type = move.operation_type;
  		is_start_end   = move.is_start_end;
  		is_done        = std::move(move.is_done);
  		exec_node      = std::move(move.exec_node);	
  		input_node     = move.input_node;
  		brother        = move.brother;
  		ret						 = std::move(move.ret);	
  		wait_queue	   = move.wait_queue;	
  		ready_queue    = std::move(move.ready_queue);	
  		call_once_thread_poll = std::move(move.call_once_thread_poll);	
  		jump_point     =  std::move(move.jump_point);	
  	}
  	
  ~exec_node_type()
  	{
  		//销毁等待队列
  		CAS_RING_DESTORY(jmp_buf_ptr,wait_queue);
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
  void set_call_once(std::function<void(void)> & _call_once)
  {
  	call_once_thread_poll = std::move(_call_once);
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

  	//
  template<class Funtype,typename ... Args>
  inline   exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
			   exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
			   exec_fun<Funtype,Args...> >
	 then(exec_fun<Funtype,Args...> & later_func )
	{
		// then 节点类型
		exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
										exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
										exec_fun<Funtype,Args...> >  then_exec_node(OPERATION_RUNING) ;  //操作节点类型
		// 设置执行器								
		then_exec_node.set_exec(later_func);
		// 设置前继依赖项为 this
		then_exec_node.set_input_node(*this);
		
		//将jmp_buf 放到前继节点的等待队列(普通队列)中
		 jmp_buf * jmp_buf_p = &jump_point; 
			CAS_RING_EN( jmp_buf_ptr,this->wait_queue,&(jmp_buf_p) );
		
		return std::move(then_exec_node);
	}
  	//执行本节点
	inline int try_execute()
	{
		  //1 所有的前继节点都结束
		  int first_check = 0;
		  do
		  {
					if( input_node != NULL  )
					{
						typename input_node_type::brother_type_ * brother_tmp =input_node->brother;
				   	//前继节点或者前继的兄弟节点没执行完，就睡眠
				   	if ( check(brother_tmp) || false == input_node->is_done.load()  )
					  {
						 first_check = 1;
						// lock (is_done)
						// if(is_done == 0){
						// setjmp 并将 jmp_buf 放到前继节点的等待队列(普通队列)中
						// unlock(is_done)
						// 跳转到全局就绪队列中执行 longjmp
						// }
						// else unlock(is_done);
						
						jmp_buf * jmp_buf_p = &jump_point; 
						int setjmp_flag =  0;
						//首次调用
						if( (setjmp_flag = setjmp(jump_point) ) == 0 )
							{
								//首次调用将jmp_buf 放到前继节点的等待队列(普通队列)中
								CAS_RING_EN( jmp_buf_ptr,input_node->wait_queue,&(jmp_buf_p) );
								// 如果首次调用后，依赖项就执行完了，为了不使用锁，这里回滚上一步操作
								if( !( check(brother_tmp) || input_node->is_done.load() == 0 ) )
									{
										jmp_buf_ptr * out_p = NULL; 
										while( CAS_RING_EMPTY != CAS_RING_DN(jmp_buf_ptr,input_node->wait_queue,(out_p)) )
										{
											ready_queue.push(out_p);
										}
										//回滚结束，跳出循环
										break;
									}
								//跳出本执行栈，等待从就绪队列唤醒
							  //shedule()
							  if( CAS_RING_EMPTY == ready_queue.schedule() )
							  	{
							  		 // 如果全局就绪队列为空,跳转到线程池,处理下一个任务
							  		 call_once_thread_poll();
							  	}
							}
							//从 longjmp返回
							else if( 2 == setjmp_flag)
								{
									//睡醒后重新检查依赖节点是否都执行完
						 			continue;
					     	}
					     	//不是从 longjmp返回的死循环再次调用线程池
					     	else 
					     		{
					     			if( CAS_RING_EMPTY == ready_queue.schedule() )
							  		{
							  			 // 如果全局就绪队列为空,跳转到线程池,处理下一个任务
							  			 call_once_thread_poll();
							  		}
					     		}
					  }
					  //依赖节点都执行完就退出
					  else break;
					}
			
		  }while( first_check );
		
		//2 执行本节点任务
		ret = exec_node.exe(); 
		// 不需要lock (is_done)
	  // 将等待队列(普通队列)中的 jmp_buf 放入全局就绪队列中
	    is_done.store(true);
	  	jmp_buf_ptr * out_p = NULL; 
			while( CAS_RING_EMPTY != CAS_RING_DN(jmp_buf_ptr,this->wait_queue,(out_p)) )
			{
				ready_queue.push(out_p);
			}
		   //将就绪队列执行完
			while( CAS_RING_EMPTY != ready_queue.schedule() );
		// 不需要unlock (is_done)
		
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
	CAS_RING_TYPE(jmp_buf_ptr,wait_queue);		 //等待队列

	exec_node_type():input_node(NULL),brother(NULL),is_start_end(OPERATION_END),is_done(1){
		  	CAS_RING_INIT( jmp_buf_ptr,wait_queue,DEFAULT_RING_BUF );
		}
	inline int try_execute()
	{
	  return 0;
 	}
 	  ~exec_node_type()
  	{
  		//销毁等待队列
  		CAS_RING_DESTORY(jmp_buf_ptr,wait_queue);
  	}
};

#endif 
