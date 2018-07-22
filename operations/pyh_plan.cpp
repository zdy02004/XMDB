/*
执行顺序


语法树转为逻辑计划时各算子存在先后顺序。以select语句为例，执行的顺序为： 

FROM > WHERE > GROUP BY> HAVING > SELECT > DISTINCT > UNION > ORDER BY > LIMIT。 

1.
search_table_name(char * table_name,long long * no)
get_table_no_addr(long table_no,void ** addr); -> mem_table
mem_table->config->fields_table->index_nr【 relate_index	】 判断是否有索引
有索引-> ( mem_skiplist_index_scan_long,mem_hash_index_scan_long )
没索引-> ( compare_list , full_table_scan_with_conlist)

2.
__filter_stl
3.
__group_by_key_stl
4.
__filter_stl
5.
_map_stl
6.
_distinct_ctl
7.
_union_all_ctl or _union_ctl
8.
SORT
9.
暂无


没有优化的逻辑计划应按照上述顺序逐步生成或者逆向生成。转为逻辑计划算子则对应为： 

JOIN –> FILTER -> GROUP -> FILTER(HAVING) -> PROJECTION -> DIST -> UNION -> SORT -> LIMIT。
1.
FROM 1, FROM 2
2.
同上

*/
//  函数表
// _map_stl _filter_stl __group_by_key_stl  __reduce_stl  _distinct_ctl   _union_all_ctl   _union_ctl  __hash_inner_join_ctl   __intersect_ctl   
//    1          2              3                4             5                 6            7                   8                  9

//  g++ -w -std=c++11 -C pyh_plan.hpp 
//  g++ -w -std=c++11  pyh_plan.cpp  -o cc.exe  



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


//万能函数包装器
template<class Funtype,class T ,class... Args>
inline auto FuncWrapper(Funtype && f, Args && ... args) -> decltype(f(std::forward<Args>(args)...))
{
//typedef decltype(f(std::forward<Args>(args)...)) ReturnType;
return f(std::forward<Args>(args)...);
}

template<class Funtype,class Arg1,class Arg2,class Arg3,class Arg4>
struct opper_wrapper
{
	Funtype  f;
	Arg1  arg1;
	Arg1  arg2;
	Arg1  arg3;
	Arg1  arg4;
	opper_wrapper(Funtype && _f, Arg1 && _arg1, Arg2 && _arg2,Arg3 && _arg3,Arg4 && _arg4):f(std::forward<Funtype>(_f)),arg1(std::forward<Arg1>(_arg1)),arg2(std::forward<Arg2>(_arg2)),arg3(std::forward<Arg3>(_arg3)),arg4(std::forward<Arg4>(_arg4)){}
  opper_wrapper(){}
  
	typedef typename std::result_of<Funtype(Arg1,Arg2,Arg3,Arg4)>::type  ret_type;

   void swap(opper_wrapper< Funtype,Arg1,Arg2,Arg3,Arg4> & node)
  {
  	f = std::move(node.f);
  	arg1 = 	std::move(node.arg1);
  	arg2 = 	std::move(node.arg2);
  	arg3 = 	std::move(node.arg3);
    arg4 = 	std::move(node.arg4);
  }

	//inline auto exe() -> decltype(f(std::forward<Arg1>(arg1),std::forward<Arg2>(arg2),std::forward<Arg3>(arg3),std::forward<Arg4>(arg4)))
	inline ret_type exe() 
	{
		return f(arg1,arg2,arg3,arg4 );
	}
	
};

template<class Funtype,class Arg1,class Arg2,class Arg3>
struct opper_wrapper< Funtype, Arg1, Arg2, Arg3,void>
{
	opper_wrapper(Funtype && _f, Arg1 && _arg1, Arg2 && _arg2,Arg3 && _arg3):f(std::forward<Funtype>(_f)),arg1(std::forward<Arg1>(_arg1)),arg2(std::forward<Arg2>(_arg2)),arg3(std::forward<Arg3>(_arg3)){}
  opper_wrapper(){}
	Funtype  f;
	Arg1  arg1;
	Arg1  arg2;
	Arg1  arg3;
	
  typedef typename std::result_of<Funtype(Arg1,Arg2,Arg3)>::type  ret_type;
  
   void swap(opper_wrapper< Funtype,Arg1,Arg2,Arg3,int> & node)
  {
  	f = std::move(node.f);
  	arg1 = 	std::move(node.arg1);
  	arg2 = 	std::move(node.arg2);
  	arg3 = 	std::move(node.arg3);
  }
	
	//inline auto exe() ->decltype(f(std::forward<Arg1>(arg1),std::forward<Arg2>(arg2),std::forward<Arg3>(arg3)))
	inline ret_type exe() 
	{
		return f(std::forward<Arg1, Arg2, Arg3>(arg1,arg2,arg3) );
	}

};


template<class Funtype,class Arg1,class Arg2>
struct opper_wrapper<Funtype,Arg1,Arg2,void,void>
{
	opper_wrapper(Funtype && _f, Arg1 && _arg1, Arg2 && _arg2):f(std::forward<Funtype>(_f)),arg1(std::forward<Arg1>(_arg1)),arg2(std::forward<Arg2>(_arg2)){}
  opper_wrapper(){}
	Funtype f;
	Arg1 arg1;
	Arg1 arg2;
	
	typedef typename std::result_of<Funtype(Arg1,Arg2)>::type  ret_type;
	
	 void swap(opper_wrapper< Funtype,Arg1,Arg2,int,int> & node)
  {
  	f = std::move(node.f);
  	arg1 = 	std::move(node.arg1);
  	arg2 = 	std::move(node.arg2);
  }
	
	//inline auto exe() -> decltype(f(std::forward<Arg1>(arg1),std::forward<Arg2>(arg2)))
	inline ret_type exe() 
	{
		return f(std::forward<Arg1,Arg2>(arg1,arg2) );
	}
	
};

template<class Funtype,class Arg1>
struct opper_wrapper< Funtype,Arg1,void,void,void>
{
	
	opper_wrapper(Funtype && _f, Arg1 && _arg1):f(_f),f(std::forward<Funtype>(_f)),arg1(std::forward<Arg1>(_arg1)){}
  opper_wrapper(){}
  
	Funtype f;
	Arg1  arg1;
	
	typedef typename std::result_of<Funtype(Arg1)>::type  ret_type;

  void swap(opper_wrapper< Funtype,Arg1,int,int,int> & node)
  {
  	f = std::move(node.f);
  	arg1 = 	std::move(node.arg1);
  }

	//inline auto exe() -> decltype(f(std::forward<Arg1>(arg1)))
	inline ret_type exe() 
	{
		return f(std::forward<Arg1>(arg1));
	}
};

#define OPERATION_START 1
#define OPERATION_END   2

//  函数表
// _map_stl _filter_stl __group_by_key_stl  __reduce_stl  _distinct_ctl   _union_all_ctl   _union_ctl  __hash_inner_join_ctl   __intersect_ctl   
//    1          2              3                4             5                 6            7                   8                  9
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
template<class FunType,class Arg1,class Arg2,class Arg3,class Arg4,class pre_type,class brother_type>
struct operation_node
{
	//std::tuple<int> parms;
	// auto tup3 = tuple_cat(tup1, tup2);	
	typedef pre_type  						pre_type_;
	//typedef out_type  						out_type_;
	typedef brother_type  				brother_type_;
	typedef FunType  							FunType_;
	typedef Arg1  								Arg1_;
	typedef Arg2  								Arg2_;
	typedef Arg3  								Arg3_;
	typedef Arg4  								Arg4_;
	
	 //执行节点返回类型
	typedef typename opper_wrapper< FunType,Arg1,Arg2,Arg3,Arg4>::ret_type  ret_type; 
  
  //前继节点类型
	typedef operation_node<typename pre_type_::FunType_, typename pre_type_::Arg1_ , typename pre_type_::Arg2_ , 
																							 typename pre_type_::Arg3_ , typename pre_type_::Arg4_ , 
								 typename pre_type_::pre_type_/*,typename pre_type_::out_type*/ , typename pre_type_::brother_type_  >  input_node_type;		 	
	
	//后继节点类型							 	
	//typedef operation_node<typename out_type_::FunType_, typename out_type_::Arg1_ , typename out_type_::Arg2_ , 
	//																						 typename out_type_::Arg3_ , typename out_type_::Arg4_ , 
	//							 typename out_type_::pre_type_,typename out_type_::out_type , typename out_type_::brother_type_  > output_node_type;
								 	
	
	int    operation_type;																		//操作类型
	short  is_start_end;																			//是否是开始节点 1 开始   2 结束
	char   is_done;																						//是否结束  0 未结束   1  结束
	opper_wrapper< FunType,Arg1,Arg2,Arg3,Arg4> exec_node;    //执行节点
	
	input_node_type				*   input_node;  			 //前继依赖节点
	//output_node_type      *   output_node;       //后继依输出节点
	brother_type          *   brother;  				 //前继依赖兄弟节点 
	ret_type 									ret;							 //执行结果集
 
  operation_node(int _operation_type ):operation_type(_operation_type),is_start_end(OPERATION_START),is_done(0),input_node( NULL ),brother( NULL ){}
  
  //设置执行函数
  void set_exec(opper_wrapper< FunType,Arg1,Arg2,Arg3,Arg4> & _exec_node)
  {
  	exec_node.swap(_exec_node);
  }
  
   //设置前继节点
  void set_input_node(input_node_type * _input_node )
  {
  	input_node = _input_node;
  }
  
   //设置兄弟节点
  void set_input_node(brother_type * _brohter_node )
  {
  	brother = _brohter_node;
  }
  
  // 目前支持两个数据源 容器
  // 必须和 func_help.hpp 配合使用，容器参数必须在前2个
  //设置1源
  void set_source1(Arg1 & _arg1 )
  {
  	exec_node.arg1 = std::move(_arg1);
  }
  
  //设置2源
  void set_source2(Arg2 & _arg2 )
  {
  	exec_node.arg2 = std::move(_arg2);
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
  
  
	 //递归修改后继节点
	template<class T>
	inline int set( T&  pre_brother)
	{
	 
	 if(pre_brother.brother == NULL)return 0;  //退出返回
	 typename T::brother_type_ & brother_tmp =*(pre_brother.brother);
	 brother_tmp.is_start_end = OPERATION_END ;    			    //
	 return set<typename T::brother_type_>(brother_tmp) ;
	
	}
	
	inline int set( int	  pre_brother)
	{
	 return 0;  //退出返回
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
		//if( output_node != NULL  )
		//{
    // 	output_node->is_done = 1;
		//	typename output_node_type::brother_type & brother_tmp =*(output_node->brother);
    //  set<typename output_node_type::brother_type>(brother_tmp) ;
    //
		//}
		
		//4 构造所有的后继节点投入到任务队列
		
		
	}
	
};

//空执行节点
template <>
struct opper_wrapper< int,int,int,int,int>
{
	typedef  int  ret_type;
	opper_wrapper(){}
  void swap()
  {
  }
	inline int exe()
	{
		return 0;
	}
	
};

// 空执行辅助节点
template<class FunType,class Arg1,class Arg2,class Arg3,class Arg4>
struct operation_node<FunType,Arg1,Arg2,Arg3,Arg4,int,int>
{
	//typedef operation_node<void,void,void,void,void,void,void> empty_exe_node_type;
	typedef int             	pre_type_;
	//typedef int  						out_type_;
	typedef int             	brother_type_;
	typedef int  							FunType_;
	typedef int  								Arg1_;
	typedef int  								Arg2_;
	typedef int  								Arg3_;
	typedef int  								Arg4_;
	typedef int  					  	ret_type; 
	typedef int	            	input_node_type;
	//typedef int 			output_node_type;
	opper_wrapper< int,int,int,int,int> exec_node;    //执行节点
	short  is_start_end;															//是否是开始节点 1 开始   2 结束
	char   is_done;			
	input_node_type       *   input_node;  			      //前继依赖节点
	brother_type_			    *   brother;  				      //前继依赖兄弟节点 
	//int 									ret;				   			        //执行结果集
	operation_node():input_node(NULL),brother(NULL),is_start_end(OPERATION_END),is_done(1){}
	inline int try_execute()
	{
		return 0;
  }
};


int fun4(int a,int b ,int c, int d)
{
	
	printf("%d,%d,%d,%d\n",a,b,c,d);
	return 0;
}

int func4(char a,char b ,char c, char d)
{
	
	printf("%c,%c,%c,%c\n",a,b,c,d);
	return 0;
}

int main()
{
	//typedef  std::function< int(int,int,int,int )> int_t;
	typedef int(*int_t)(int,int,int,int );
	typedef int(*char_t)(char,char,char,char );
	
	// 首节点的空前继 空兄弟节点
	typedef operation_node<int_t,int,int,int,int,int,int> empty_exe_node_type1;
  // 首节点类型
  typedef operation_node<int_t,int,int,int,int,empty_exe_node_type1,empty_exe_node_type1> on1_type;
  // 首节点
  on1_type on1(1);
  // 首节执行器
	opper_wrapper< int_t,int,int,int,int> ow1(fun4,1,2,3,4);
	on1.set_exec(ow1);
	//运行首节点
	on1.try_execute();
	
	
	//2 节点的空兄弟节点
	typedef operation_node<char_t,char,char,char,char,int,int> empty_exe_node_type2;
	//2节点类型
  typedef operation_node<char_t,char,char,char,char,on1_type,empty_exe_node_type2> on2_type;
  //2节点
	on2_type on2(2);
	//2节点执行器
	opper_wrapper< char_t,char,char,char,char> ow2(func4,'a','b','c','d');
	on2.set_exec(ow2);
	//2节点前继
	on2.set_input_node(&on1 );
	
	//运行2节点
	on2.try_execute();
	
	return 0;
}


#endif 