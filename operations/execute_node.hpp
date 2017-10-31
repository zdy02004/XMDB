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

// 用于 特化 指针函数的返回值
template<class T,bool T2,typename ... Args>
struct is_functional
{
typedef typename std::result_of<T(Args...)>::type  ret_type;

};
// 用于 特化 std::function 的返回值
template<class T,typename ... Args>
struct is_functional<T,true,Args...>
{
typedef typename T::result_type  ret_type;

};

//template<class T,bool T2,typename ... Args>
//struct is_functional_arg
//{
//typedef typename Args...  argument_type;
//
//};
//
//template<class T,typename ... Args>
//struct is_functional_arg<T,true,Args...>
//{
//typedef typename T::argument_type  argument_type;
//
//};


//懒执行函数包装器
template<class Funtype,typename ... Args>
struct exec_fun
{
	
	Funtype  f;
	std::tuple<Args...> _arguments;
	
	//exec_fun( Funtype && _f, Args &&... args ):f(std::forward<Funtype>(_f)),_arguments(std::make_tuple(std::forward<Args>(args)...)){}
	exec_fun( Funtype && _f, Args ... args ):f(std::forward<Funtype>(_f)),_arguments(std::forward_as_tuple((args)...)){}
  exec_fun(){}
  
  typedef exec_fun<Funtype,Args...>  this_type;
	typedef typename is_functional<Funtype,std::is_function<Funtype>::value, Args ...>::ret_type  ret_type;	  
		  
  void swap(exec_fun< Funtype,Args...> & node)
  {
    f = std::move(node.f);
   _arguments = 	std::move(node._arguments);
  }
  
   exec_fun ( exec_fun<Funtype,Args...> && node )
   {
   	f = std::move(node.f);
  	 _arguments =std::move(node._arguments);
   } 
  
   exec_fun ( exec_fun<Funtype,Args...> & node ):f(std::move(node.f) ),_arguments(node._arguments){}   
   exec_fun (const exec_fun<Funtype,Args...> & node ):f(node.f),_arguments(node._arguments){}  
   
   void operator = (exec_fun<Funtype,Args...> && node)
   {
   	  f = std::move(node.f);
  	 _arguments =std::move(node._arguments);
   }
   
   void operator = ( exec_fun<Funtype,Args...> & node)
   {
   	  f = (node.f);
  	 _arguments =(node._arguments);
   }
        
	inline ret_type exe() 
	{
	   return apply( f, _arguments);
	}
		
	inline ret_type operator()()
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

typedef std::function <int( std::function<void * (void *)> &, void *)>  put_once_t ;

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
  put_once_t         put_once_to_thread_poll;  //往线程池一次取任务干活
  
inline exec_node_type(int _operation_type ):operation_type(_operation_type),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
{  		
	is_done.store(1);
	call_once_thread_poll = [](void){DEBUG("Empty call_once\n");return;};
	put_once_to_thread_poll = [](std::function<void * (void *)> &,void *){DEBUG("Empty put_once\n");return  0;};
}

exec_node_type( ):operation_type(OPERATION_RUNING),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
{
	is_done.store(1);
	call_once_thread_poll = [](void){DEBUG("Empty call_once\n");return;};
	put_once_to_thread_poll = [](std::function<void * (void *)> &,void *){DEBUG("Empty put_once\n");return  0;};

}

//普通同 move语义
inline exec_node_type( exec_node_type< pre_type, brother_type, OpperType>& move ):operation_type(move.operation_type),is_start_end(move.is_start_end),exec_node(move.exec_node),input_node(move.input_node),brother(move.brother),ret(move.ret),wait_queue(std::move(wait_queue)),call_once_thread_poll(std::move(move.call_once_thread_poll)),put_once_to_thread_poll(move.put_once_to_thread_poll){is_done.store(move.is_done.load());}

//move 语义
inline exec_node_type( exec_node_type< pre_type, brother_type, OpperType>&& move )
{
	operation_type = move.operation_type;
	is_start_end   = move.is_start_end;
	is_done.store(move.is_done.load());
	exec_node      = std::move(move.exec_node);	
	input_node     = move.input_node;
	brother        = move.brother;
	ret	       = move.ret;		//默认为指针类型
	wait_queue     = std::move(wait_queue);	
	call_once_thread_poll  = std::move(move.call_once_thread_poll);
	put_once_to_thread_poll= std::move(move.put_once_to_thread_poll);		
}
 inline	void operator = ( exec_node_type< pre_type, brother_type, OpperType>&& move )
{
	operation_type = move.operation_type;
	is_start_end   = move.is_start_end;
	is_done.store(move.is_done.load());
	exec_node      = std::move(move.exec_node);	
	input_node     = move.input_node;
	brother        = move.brother;
	ret	           = move.ret;	//默认为指针类型
	wait_queue	   = std::move(wait_queue);	
	call_once_thread_poll = std::move(move.call_once_thread_poll);	
	put_once_to_thread_poll= std::move(move.put_once_to_thread_poll);		
}
  	
~exec_node_type()
{
	//销毁等待队列
	//CAS_RING_DESTORY(jmp_buf_type,wait_queue);
}
  	
//设置执行函数
inline  void set_wait_queue_size(uint32_t size)
{
	wait_queue.init( size );
 
}
//设置执行函数
inline void set_exec(OpperType & _exec_node)
{
	exec_node.swap(_exec_node);
}
//设置前继节点
inline  void set_input_node(input_node_type & _input_node )
{
	input_node = &_input_node;
}
//设置兄弟节点
inline  void set_brother_node(brother_type & _brohter_node )
{
	brother = &_brohter_node;
}
 // 设置调用一次 线程池执行函数，这里规定该函数为 void(void)
inline  void set_call_once(std::function<void(void)>  _call_once)
{
	call_once_thread_poll = std::move(_call_once);
}
inline  void set_put_once(put_once_t  _put_once)
{
	put_once_to_thread_poll = (_put_once);
}
template<class pool_type>
inline   
exec_node_type<pre_type,brother_type,OpperType> &
set_pool(pool_type&  pool)
{
	set_put_once(
	[&](std::function<void * (void *)> &process, void *arg)->int{
	return	pool.add_task(process,arg);
	}
	 );
	 
	set_call_once(
	[&](){
	   pool.thread_routine_once();
			 }
	 );
	 return std::ref(*this);
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
	if(brother_tmp->is_done.load()!= 1)return 1;       //中断返回
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
inline exec_node_type(Funtype & _f,Args... args ):operation_type(OPERATION_RUNING),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
{
	is_done.store(1);
	call_once_thread_poll = [](void){DEBUG("Empty call_once\n");return;};
	put_once_to_thread_poll = [](std::function<void * (void *)> &,void *){DEBUG("Empty put_once\n");return  0;};
	OpperType node(std::forward<Funtype>(_f),std::forward<Args>(args)...);
	exec_node.swap(node); 			
}

template<class Funtype,typename ... Args>
inline exec_node_type(exec_fun<Funtype,Args...> & later_func ):exec_node(later_func),operation_type(OPERATION_RUNING),is_start_end(OPERATION_START),input_node( NULL ),brother( NULL )
{
	is_done.store(1);
	call_once_thread_poll = [](void){DEBUG("Empty call_once\n");return;};
	put_once_to_thread_poll = [](std::function<void * (void *)> &,void *){DEBUG("Empty put_once\n");return  0;};			
}

template<class Funtype,typename ... Args>
inline 
exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
   exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
   exec_fun<Funtype,Args...> > &
then(exec_fun<Funtype,Args...> & later_func )
{
// then 节点类型
std::shared_ptr<
exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
								exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
								exec_fun<Funtype,Args...> >  
						>   then_exec_node ( new
exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
								exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
								exec_fun<Funtype,Args...> >(later_func)		);					 
// 设置执行器								
 	//	then_exec_node->set_exec(later_func);
// 设置前继依赖项为 this
 		then_exec_node->set_input_node(*this);
// 传递依赖 线程池的 put_once 函数
 		then_exec_node->set_put_once(this->put_once_to_thread_poll);
// 传递依赖 线程池的 call_once 函数
 		then_exec_node->set_call_once(this->call_once_thread_poll);
// 扔进线程池
 		std::function<void * (void *)> process  =[=](void * a)	 {
 	  then_exec_node->try_execute();
 		return (void *)0;
 		}; 
 		 
 		DEBUG("put_once_to_thread_poll() \n");  		
 		put_once_to_thread_poll(process,(void *)0);
  	//扔进等待队列
  	//DEBUG("put_once_to_wait_queue() \n");
  	//std::function<void (void )> this_process=[=](){
		//then_exec_node->try_execute();
		//} ;  
		//wait_queue.push( this_process );
  	//
		 DEBUG("Leave then	() \n");
		return  ( *then_exec_node );

}

template<class Funtype,typename ... Args>
inline   
exec_node_type< exec_node_type<pre_type,brother_type,OpperType>, // 前继节点类型
		   exec_node_type< int,int,exec_node_type< int,int,exec_fun<Funtype,Args...> > >, //兄弟节点类型
		   exec_fun<Funtype,Args...> >  &
then( Funtype f,Args... args ) 
{		
	exec_fun<Funtype,Args...> later_func ( std::forward<Funtype>(f),std::forward<Args>(args)...);
	return then( later_func  );
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
			DEBUG(" input_node != NULL \n");
			typename input_node_type::brother_type_ * brother_tmp =input_node->brother;
		 	//前继节点或者前继的兄弟节点没执行完，就把自己放到前景节点的等待队列中，然后退出
		 	if ( check(brother_tmp) || 0 == input_node->is_done.load()/*get_stat()*/  )
		  {
		  	DEBUG(" input_node is working \n");
				//首次调用
				if( first_check  == 0 )
				{
					DEBUG(" First execute !\n");				
					first_check = 2;
					std::function<void (void )> this_process=[&](){
					this->try_execute();
					};
					  
					input_node->wait_queue.push( this_process );
					
					// 如果首次调用后，依赖项就执行完了,这里回滚上一步操作
					if( !( check(brother_tmp) || 0 == input_node->is_done.load()/*get_stat()*/ ) )
					{
						DEBUG("ROLL BACK \n");
						input_node->wait_queue.schedule(put_once_to_thread_poll);
					}
					return 0;
				}
		   	else 
		   	{
					// 正常情况不对到达此分支
					DEBUG(" first check = %d \n",first_check);
					call_once_thread_poll();
		   	}
		  }
		  //依赖节点都执行完就退出
		  else break;
		}
		else break;
	
	}while( true );
	
	DEBUG("exec_node.exe() \n");
	//2 执行本节点任务
	//ret = exec_node.exe();
	ret =  exec_node();

  is_done.store(1);	  	
  DEBUG(" Before done ============================\n");
  wait_queue.schedule(put_once_to_thread_poll);
  //wait_queue.schedule_now(); //立即执行
  DEBUG(" After done  ============================\n");
}

}__attribute__ ((packed, aligned (64)));

//创建默认空节点
template<class Funtype,typename ... Args>
inline 
exec_node_type<exec_node_type<int,int,exec_fun < Funtype,Args... > >,exec_node_type<int,int,exec_fun < Funtype,Args... > >,exec_fun < Funtype,Args... > >
make_exec_node(Funtype _f,Args... args )
{
  return	exec_node_type<exec_node_type<int,int,exec_fun < Funtype,Args... > >,exec_node_type<int,int,exec_fun < Funtype,Args... > >,exec_fun < Funtype,Args... > > ( _f,args... );	
}

void empty_func(void)
{
	return;
}

//空执行节点
template <typename ... Args>
struct exec_fun< int,Args...>
{
	typedef  int  ret_type;
	typedef   std::function <void(void )>   Funtype;
	Funtype  f;
	
	std::tuple<Args...> _arguments;
	exec_fun(){}
	exec_fun ( exec_fun< int,Args...> 		&& node ){f = empty_func;} 
  exec_fun ( exec_fun< int,Args...> 		& node  ){f = empty_func;}   
  exec_fun (const exec_fun< int,Args...> & node ){f = empty_func;} 
   
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
	typedef int pre_type_;
	typedef int brother_type_;
	typedef int OpperType_;
	typedef int ret_type; 
	typedef int	input_node_type;
	
	short										is_start_end;			//是否是开始节点 1 开始   2 结束
	std::atomic<bool>				is_done;			
	input_node_type      	 *input_node;		//前继依赖节点
	brother_type_					 *brother;			//前继依赖兄弟节点 
	cpp_func_task_namespace::wait_func_queue_t    wait_queue;		 //等待队列
	exec_fun< int,OpperType>  exec_node;              					 //执行节点

exec_node_type():input_node(NULL),brother(NULL),is_start_end(OPERATION_END)
{
	is_done.store(1);
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
