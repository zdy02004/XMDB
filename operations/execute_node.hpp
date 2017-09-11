//  g++ -w -std=c++11  execute_node.cpp  -o cc.exe  
#ifndef EXEC_NODE
#define EXEC_NODE

#include <tuple>
#include <type_traits>
#include <utility>
#include <functional>

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

	//inline auto exe() -> decltype(f(std::forward<Arg1>(arg1),std::forward<Arg2>(arg2),std::forward<Arg3>(arg3),std::forward<Arg4>(arg4)))
	inline ret_type exe() 
	{
		//return f(arg1,arg2,arg3,arg4 );
		return apply( f, _arguments);
	}
	
};


#define OPERATION_START 1
#define OPERATION_END   2
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

// 物理执行计划
// 处理节点
// pre_type     前继节点类型
// brother_type 兄弟节点类型
// OpperType    操作节点类型
template<class pre_type,class brother_type,class OpperType>
struct exec_node_type
{

	typedef pre_type  						pre_type_;
	//typedef out_type  					out_type_;
	typedef brother_type  				brother_type_;
	typedef OpperType  						OpperType_;
	
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
								 	
	
	int    									operation_type;		//操作类型
	short  									is_start_end;			//是否是开始节点 1 开始   2 结束
	char   									is_done;					//是否结束  0 未结束   1  结束
	OpperType 							exec_node;   			//执行节点
	
	input_node_type				* input_node;  			//前继依赖节点
	brother_type          * brother;  				//前继依赖兄弟节点 
	ret_type 								ret;							//执行结果集
 
  exec_node_type(int _operation_type ):operation_type(_operation_type),is_start_end(OPERATION_START),is_done(0),input_node( NULL ),brother( NULL ){}
  
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
	 if( ret == 1 )return 1;       //中断返回
	 if( ret == 0 )return 0;       //退出返回
	 return check(brother_tmp) ;
	
	}
	  //递归检查前继节点
	template<class T>
	inline int check_isdone( T*  brother_tmp)
	{
		if(brother_tmp->is_done!= 1)return 1;       //中断返回
	  else return 2;
  }
  inline int check_isdone( int*  brother_tmp)
	{
		return 0;
  }

  //执行本节点
	inline int try_execute()
	{
		//1 所有的前继节点都结束
		  int first_check = 1;
		  while( first_check )
		  {
		 		  first_check = 0;
					if(first_check && input_node != NULL && input_node->is_done != 1)
					{
						 typename input_node_type::brother_type_ * brother_tmp =input_node->brother;
				   	if ( check(brother_tmp)  )
									{
										//还不能开始
										first_check = 1;
										// 阻塞代码
										continue;
									}
					}
			
		  }
	  	
		
		//2 执行本节点任务
		ret = exec_node.exe();
		
		//3 所有的后继节点可以开始
		is_done = 1;
		
		//4 构造所有的后继节点投入到任务队列

	}
	
}__attribute__ ((packed, aligned (64)));

//空执行节点
template <typename ... Args>
struct exec_fun< int,Args...>
{
	typedef  int  ret_type;
	exec_fun(){}
  void swap()
  {
  }
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
	//typedef int  						out_type_;
	typedef int             	brother_type_;
	typedef int  							OpperType_;
	typedef int  					  	ret_type; 
	typedef int	            	input_node_type;
	//typedef int 			output_node_type;
	exec_fun< int,OpperType>    exec_node;    //执行节点
	short  is_start_end;															//是否是开始节点 1 开始   2 结束
	char   is_done;			
	input_node_type       *   input_node;  			      //前继依赖节点
	brother_type_			    *   brother;  				      //前继依赖兄弟节点 
	//int 									ret;				   			      //执行结果集
	exec_node_type():input_node(NULL),brother(NULL),is_start_end(OPERATION_END),is_done(1){}
	inline int try_execute()
	{
		return 0;
  }
};


#endif 