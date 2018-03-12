#ifndef _REPLACE_INNER_TYPE_
#define _REPLACE_INNER_TYPE_
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <stack>
#include <queue>
#include <set>
#include <map>
//#include <hash_map>
#include <algorithm> 
#include <unordered_map> 
#include <functional>
#include <memory>
#include <iostream>

using namespace std;
namespace func
{

//  replace_inner_type 用来替换 stl<A> 容器内部的值类型，生成新的 stl<B> 容器类型
//  以下几个 模板元函数用来替换 非管理容器的值容器的
template<typename __whole_type, typename __inner_type,typename  __new_inner_type  >
struct replace_inner_type
{
typedef   void* new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<vector<__inner_type>,__inner_type,__new_inner_type>
{
typedef vector<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<list<__inner_type>,__inner_type,__new_inner_type>
{
typedef list<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<deque<__inner_type>,__inner_type,__new_inner_type>
{
typedef deque<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<stack<__inner_type>,__inner_type,__new_inner_type>
{
typedef stack<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<queue<__inner_type>,__inner_type,__new_inner_type>
{
typedef queue<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<set<__inner_type>,__inner_type,__new_inner_type>
{
typedef set<__new_inner_type> new_type;
};

template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<multiset<__inner_type>,__inner_type,__new_inner_type>
{
typedef multiset<__new_inner_type> new_type;
};

//template<typename __inner_type,typename  __new_inner_type >
//struct replace_inner_type<map<__inner_type>,__inner_type,__new_inner_type>
//{
//typedef map<__new_inner_type> new_type;
//};

//template<typename __inner_type,typename  __new_inner_type >
//struct replace_inner_type<hash_map<__inner_type>,__inner_type,__new_inner_type>
//{
//typedef hash_map<__new_inner_type> new_type;
//};
//
template<typename __inner_type,typename  __new_inner_type >
struct replace_inner_type<priority_queue<__inner_type>,__inner_type,__new_inner_type>
{
typedef priority_queue<__new_inner_type> new_type;
};

//用来判断 类中是否存在某成员函数的模板元函数
#define has_member(s) \
template<typename T>\
struct has_member_##s{\
    template <typename _T>static auto check(_T)->typename std::decay<decltype(_T::s)>::type;\
    static void check(...);\
    using type=decltype(check(std::declval<T>()));\
    enum{value=!std::is_void<type>::value};\
};

//has_reserve
has_member(reserve)


// 有reserve成员函数的要执行，否则不执行
template<class input_type,class T1,bool T2>
struct __stl_reserve__
{
static void __stl_reserve(const input_type & container,T1 ret,int i=1)
{
	return;
}
};

template<class input_type,class T1>
struct __stl_reserve__<input_type,T1,true>
{
static void __stl_reserve(const input_type & container,T1 ret,int i=1)
{
	ret->reserve(i*container.size());
	return;
}
};

// 仿函数式编程中的 map 函数1
// 第二个参数是 function 类型
// 是最终工作的函数
template<class input_type, class ret_type>
shared_ptr<typename replace_inner_type<input_type,
														typename input_type::value_type ,
														ret_type>::new_type > 
__map_stl(const input_type & container, 
				  function<ret_type(typename input_type::value_type )> fun) 
{
typedef  typename replace_inner_type<input_type,typename input_type::value_type ,ret_type>::new_type __map_stl_new_type;

shared_ptr<__map_stl_new_type> ret(make_shared<__map_stl_new_type>());

//针对连续型容器的优化，防止多次申请内存
__stl_reserve__<input_type,shared_ptr<__map_stl_new_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret);

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
	ret->emplace_back(fun(*it));
}

return ret;
}

// 仿函数式编程中的 map map 函数2
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第一个 map 函数1
// 支持显示的函数调用，例如 __map_stl<vector<int>,char>()
template<class input_type,class ret_type,class lambda_type>
shared_ptr<typename replace_inner_type<input_type,
														typename input_type::value_type ,
														ret_type>::new_type  >
__map_stl(const input_type & container, 
				  lambda_type fun) 
{
	return __map_stl(container, 
				  function<ret_type(typename input_type::value_type )>( fun) );
}


// 仿函数式编程中的 map map 函数3
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第 map 函数2
// 减少不必要的显示函数调用，例如 _map_stl<char>()
template<class lambda_type,class input_type>
shared_ptr<typename replace_inner_type<input_type,
														typename input_type::value_type ,
														typename std::result_of<lambda_type(typename input_type::value_type )>::type
														>::new_type >
_map_stl(const input_type & container, 
				  lambda_type fun) 
{
	typedef typename std::result_of<lambda_type(typename input_type::value_type )>::type ret_type; 
	return __map_stl<input_type,ret_type>(container, fun );
}

// 仿函数式编程中的 map map 函数4
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第 map 函数2
// 减少不必要的显示函数调用的 shared_ptr 重载版本
template<class lambda_type,class input_type>
shared_ptr<typename replace_inner_type<input_type,
														typename input_type::value_type ,
														typename std::result_of<lambda_type(typename input_type::value_type )>::type
														>::new_type >
_map_stl(const shared_ptr<input_type> & container, 
				  lambda_type fun) 
{
	typedef typename std::result_of<lambda_type(typename input_type::value_type )>::type ret_type; 
	return __map_stl<input_type,ret_type>(*container, fun );
}
			
			
//___________________________________________________
// 是最终工作的函数
template<class input_type>
shared_ptr<input_type>
__filter_stl(const input_type & container, 
				  function<bool(typename input_type::value_type )> fun) 
{
shared_ptr<input_type> ret(make_shared<input_type>());

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
  if(fun(*it))
  {
	 ret->emplace_back(*it);
	}
}

return ret;
}


// 仿函数式编程中的 filter map 函数2
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第一个 filter 函数1
// 支持显示的函数调用，例如 __map_stl<vector<int>,char>()
template<class input_type,class lambda_type>
shared_ptr<input_type>
_filter_stl(const input_type & container, 
				  lambda_type fun) 
{
	return __filter_stl(container, 
				  function<bool(typename input_type::value_type )>( fun) );
}

// 仿函数式编程中的 filter map 函数2
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第一个 filter 函数1
// 支持显示的函数调用，例如 __map_stl<vector<int>,char>()
template<class input_type,class lambda_type>
shared_ptr<input_type>
_filter_stl(const shared_ptr<input_type> & container, 
				    lambda_type fun) 
{
	return __filter_stl(*container, 
				  function<bool(typename input_type::value_type )>( fun) );
}

//_____________________________________________________

// 分组函数,fun 用于计算 容器中的 key 值
// 是最终工作的函数 group_by_key 1,按 key 
template<typename input_type,typename key_type>
shared_ptr<map<key_type,list<typename input_type::value_type> > >
__group_by_key_stl(const input_type & container, 
				  function<key_type(typename input_type::value_type )> fun) 
{
shared_ptr<map<key_type,list<typename input_type::value_type> > > ret(make_shared<map<key_type,list<typename input_type::value_type> > >());

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
  key_type key = fun(*it);
	(*ret)[key].emplace_back(*it);
}

return ret;
}

// 仿函数式编程中的 group_by_key 函数2
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第一个 group_by_key 函数1
// 支持显示的函数调用，例如 __map_stl<vector<int>,char>()
template<class input_type,class lambda_type>
shared_ptr<map<typename std::result_of<lambda_type(typename input_type::value_type )>::type
							,list<typename input_type::value_type> > >
_group_by_key_stl(const input_type & container, 
				  lambda_type fun) 
{
	typedef typename std::result_of<lambda_type(typename input_type::value_type )>::type key_type; 
	return __group_by_key_stl(container, 
				  function<key_type(typename input_type::value_type )>( fun) );
}

// 仿函数式编程中的 group_by_key 函数2
// 第二个参数是 lambda 或其他泛型
// 用于转发成 第一个 group_by_key 函数1
// 支持显示的函数调用，例如 __map_stl<vector<int>,char>()
template<class input_type,class lambda_type>
shared_ptr<map<typename std::result_of<lambda_type(typename input_type::value_type )>::type
							,list<typename input_type::value_type> > >
_group_by_key_stl(const shared_ptr<input_type> & container, 
				  lambda_type fun) 
{
	typedef typename std::result_of<lambda_type(typename input_type::value_type )>::type key_type; 
	return __group_by_key_stl(*container, 
				  function<key_type(typename input_type::value_type )>( fun) );
}

//_____________________________________________________
template<typename input_type,typename reduce_type>
shared_ptr<map<typename input_type::key_type,reduce_type > >
__reduce_stl(
				 const input_type & container, 
				 function<reduce_type(typename input_type::mapped_type::value_type,reduce_type )> fun
				  	) 
{
shared_ptr<map<typename input_type::key_type,reduce_type > > ret(make_shared<map<typename input_type::key_type,reduce_type > >());

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
	  reduce_type reduce_value ;
  	for(typename input_type::mapped_type::const_iterator	it2 = it->second.begin();it2!=it->second.end();++it2) 
		{

  			if(it2 == it->second.begin())reduce_value = fun(*it2,(reduce_type)0);
  			else reduce_value = fun(*it2,reduce_value);
  				
  	}
	(*ret)[it->first] = reduce_value;
}
return ret;
}

template<typename reduce_type,typename input_type,typename lambda_type>
shared_ptr<map<typename input_type::key_type,
reduce_type	> >
_reduce_stl(
				 const input_type & container, 
				 lambda_type fun
)
{		
		//typedef typename std::result_of<lambda_type(typename input_type::mapped_type::value_type,reduce_type )>::type reduce_type; 
		return __reduce_stl(container,(function<reduce_type(typename input_type::mapped_type::value_type,reduce_type )>) fun);
}

template<typename reduce_type,typename input_type,typename lambda_type>
shared_ptr<map<typename input_type::key_type,
reduce_type	> >
_reduce_stl(
				 const shared_ptr<input_type> & container, 
				 lambda_type fun
)
{		
		//typedef typename std::result_of<lambda_type(typename input_type::mapped_type::value_type,reduce_type )>::type reduce_type; 
		return __reduce_stl(*container,(function<reduce_type(typename input_type::mapped_type::value_type,reduce_type )>) fun);
}
//_____________________________________________________
template<typename reduce_type,class input_type,class lambda_key_type,class lambda_reduce_type>
shared_ptr<map<typename std::result_of<lambda_key_type(typename input_type::value_type )>::type
							,reduce_type
							> >
_reduce_by_key_stl(
									const input_type & container, 
									lambda_key_type key_fun,
									lambda_reduce_type reduce_fun
)
{
	auto f = _group_by_key_stl(container,key_fun);
	return _reduce_stl<reduce_type>( f,reduce_fun);
}

template<typename reduce_type,class input_type,class lambda_key_type,class lambda_reduce_type>
shared_ptr<map<typename std::result_of<lambda_key_type(typename input_type::value_type )>::type
								,reduce_type 
								> >
_reduce_by_key_stl(
									const shared_ptr<input_type> & container, 
									lambda_key_type key_fun,
									lambda_reduce_type reduce_fun
)
{
	auto f = _group_by_key_stl(container,key_fun);
	return _reduce_stl<reduce_type>(f,reduce_fun);
}

//___________________________________________________________

template<class input_type>
shared_ptr<input_type >
_distinct_ctl(const input_type & container)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
  auto f = _group_by_key_stl(container,[](typename input_type::value_type x){
  	return x;
  	});
	for(typename map<typename input_type::value_type,list<typename input_type::value_type> >::const_iterator 	it = f->begin();
		it!=f->end();++it) 
	{
	  ret->emplace_back(it->first);	
	}
	return ret;
}

template<class input_type>
shared_ptr<input_type >
_distinct_ctl(const shared_ptr<input_type> & container)
{
		return _distinct_ctl(*container);
}
//___________________________________________________________
template<class input_type>
shared_ptr<input_type >
_union_all_ctl(const input_type & container,const input_type & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	ret->emplace_back(*it);
}

	return ret;
}

template<class input_type>
shared_ptr<input_type >
_union_all_ctl(const shared_ptr<input_type> & container,const shared_ptr<input_type> & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (*container).begin();it!=(*container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (*container2).begin();it!=(*container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return ret;
}

template<class input_type>
shared_ptr<input_type >
_union_all_ctl(const shared_ptr<input_type> & container,const input_type & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (*container).begin();it!=(*container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (container2).begin();it!=(container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return ret;
}

template<class input_type>
shared_ptr<input_type >
_union_all_ctl(const input_type & container,const shared_ptr<input_type> & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (container).begin();it!=(container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (*container2).begin();it!=(*container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return ret;
}
//___________________________________________________________
template<class input_type>
shared_ptr<input_type >
_union_ctl(const input_type & container,const input_type & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = container.begin();it!=container.end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	ret->emplace_back(*it);
}

	return _distinct_ctl(ret);
}

template<class input_type>
shared_ptr<input_type >
_union_ctl(const shared_ptr<input_type> & container,const shared_ptr<input_type> & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (*container).begin();it!=(*container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (*container2).begin();it!=(*container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return _distinct_ctl(ret);
}

template<class input_type>
shared_ptr<input_type >
_union_ctl(const shared_ptr<input_type> & container,const input_type & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (*container).begin();it!=(*container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (container2).begin();it!=(container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return _distinct_ctl(ret);
}

template<class input_type>
shared_ptr<input_type >
_union_ctl(const input_type & container,const shared_ptr<input_type> & container2)
{
	shared_ptr<input_type > ret(make_shared<input_type>());
	
	//针对连续型容器的优化，防止多次申请内存
	__stl_reserve__<input_type,shared_ptr<input_type>,has_member_reserve<input_type>::value>::__stl_reserve(container,ret,2);

for(typename input_type::const_iterator	it = (container).begin();it!=(container).end();++it) 
{
	ret->emplace_back(*it);
}
for(typename input_type::const_iterator	it = (*container2).begin();it!=(*container2).end();++it) 
{
	ret->emplace_back(*it);
}

	return _distinct_ctl(ret);
}

//___________________________________________________________

// 是最终工作的函数 __hash_inner_join 1 
template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
__hash_inner_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename input_type1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename input_type2::value_type )>::type  key_type2; 
typedef unordered_map<key_type1,vector<typename input_type1::value_type> > hash_map_type;
typedef vector<std::pair<typename input_type1::value_type,typename input_type2::value_type > > ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve(1.6*container1.size());

for(typename input_type1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}

for(typename input_type2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
  	  	ret->emplace_back(make_pair((*it2), (*it)));
   }
}
  return ret;

}

// 由小表驱动
template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_join_ctl(const shared_ptr<input_type1> & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{  
	  if(container1->size()<=container2.size())
	  	{
				return __hash_inner_join_ctl(*container1,container2,key_fun1,key_fun2);
			}
			else
				return __hash_inner_join_ctl(container2,*container1,key_fun2,key_fun1);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_join_ctl(const input_type1 & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
		  if(container1.size()<=container2->size())
	  	{
	      return __hash_inner_join_ctl(container1,*container2,key_fun1,key_fun2);
		  }
		  else
	      return __hash_inner_join_ctl(*container2,container1,key_fun2,key_fun1);

}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_join_ctl(const shared_ptr<input_type1> & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
		  if(container1->size()<=container2->size())
	  	{
	      return __hash_inner_join_ctl(*container1,*container2,key_fun1,key_fun2);
		  }
		  else
	      return __hash_inner_join_ctl(*container2,*container1,key_fun2,key_fun1);
}


template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
		  if(container1.size()<=container2.size())
	  	{
	      return __hash_inner_join_ctl(container1,container2,key_fun1,key_fun2);
		  }
		  else
	      return __hash_inner_join_ctl(container2,container1,key_fun2,key_fun1);
}
//_____________________________________________________________________
// 是最终工作的函数 __hash_inner_anti_join 1 
template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
__hash_inner_anti_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename input_type1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename input_type2::value_type )>::type  key_type2; 
typedef unordered_map<key_type1,vector<typename input_type1::value_type> > hash_map_type;
typedef vector<std::pair<typename input_type1::value_type,typename input_type2::value_type > > ret_type;
        
shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve( container2.size()*container1.size());

for(typename input_type1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key1 = key_fun1(*it);
	 for(typename input_type2::const_iterator	it2 = container2.begin();it2!=container2.end();++it2) 
   {
   			key_type2 key2 = key_fun2(*it2);
   			if(key1 != key2)
  	  	ret->emplace_back(make_pair((*it), (*it2)));
   }
   
}
  return ret;

}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_anti_join_ctl(const shared_ptr<input_type1> & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{  
		return __hash_inner_anti_join_ctl(*container1,container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_anti_join_ctl(const input_type1 & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	  return __hash_inner_anti_join_ctl(container1,*container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_anti_join_ctl(const shared_ptr<input_type1> & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	  return __hash_inner_anti_join_ctl(*container1,*container2,key_fun1,key_fun2);
}


template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<vector<std::pair<typename input_type1::value_type,typename input_type2::value_type> > >
_hash_inner_anti_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	  return __hash_inner_anti_join_ctl(container1,container2,key_fun1,key_fun2);
}

//_____________________________________________________________________
// 是最终工作的函数 __hash_inner_semi_join 1 
template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
__hash_inner_semi_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename input_type1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename input_type2::value_type )>::type  key_type2; 
typedef unordered_map<key_type1,vector<typename input_type1::value_type> > hash_map_type;
typedef unordered_map<key_type2,vector<typename input_type2::value_type> > hash_map_type2;

typedef input_type1 ret_type;
        
shared_ptr<hash_map_type>  hash_container  (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

shared_ptr<input_type1  >  ret (make_shared<input_type1>());

ret->reserve(1*container1.size());

for(typename input_type1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}


for(typename input_type2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 if((*hash_container2)[key].empty())
	 {
	 		(*hash_container2)[key].emplace_back(*it);
	 		for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end() ;++it2) 
   		{
  			  	ret->emplace_back(*it2);
   		}
   }
}
  return ret;

}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_semi_join_ctl(const shared_ptr<input_type1> & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{  
				return __hash_inner_semi_join_ctl(*container1,container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_semi_join_ctl(const input_type1 & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_semi_join_ctl(container1,*container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_semi_join_ctl(const shared_ptr<input_type1> & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_semi_join_ctl(*container1,*container2,key_fun1,key_fun2);
}


template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_semi_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_semi_join_ctl(container1,container2,key_fun1,key_fun2);
}
//_____________________________________________________________________
// 是最终工作的函数 __hash_inner_anti_semi_join 1 
template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
__hash_inner_anti_semi_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename input_type1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename input_type2::value_type )>::type  key_type2; 
typedef unordered_map<key_type1,vector<typename input_type1::value_type> > hash_map_type;
typedef unordered_map<key_type2,vector<typename input_type2::value_type> > hash_map_type2;

typedef input_type1 ret_type;
        
//shared_ptr<hash_map_type>  hash_container  (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

shared_ptr<input_type1  >  ret (make_shared<input_type1>());

ret->reserve(1*container1.size());

for(typename input_type2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
   (*hash_container2)[key].emplace_back(*it);
}
for(typename input_type1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
	 if((*hash_container2)[key].empty())
	 {
  		ret->emplace_back(*it);
   }
   
}
  return ret;

}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_anti_semi_join_ctl(const shared_ptr<input_type1> & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{  
				return __hash_inner_anti_semi_join_ctl(*container1,container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_anti_semi_join_ctl(const input_type1 & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_anti_semi_join_ctl(container1,*container2,key_fun1,key_fun2);
}

template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_anti_semi_join_ctl(const shared_ptr<input_type1> & container1,const shared_ptr<input_type2> & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_anti_semi_join_ctl(*container1,*container2,key_fun1,key_fun2);
}


template<typename input_type1,typename input_type2,typename fun_type1,typename fun_type2>
shared_ptr<input_type1>
_hash_inner_anti_semi_join_ctl(const input_type1 & container1,const input_type2 & container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
	      return __hash_inner_anti_semi_join_ctl(container1,container2,key_fun1,key_fun2);
}
//_____________________________________________________________________
// 算交集
template<class input_type>
shared_ptr<input_type >
__intersect_ctl(const input_type & container,const input_type & container2)
{

typedef unordered_map< typename input_type::value_type,char > hash_map_type;
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<input_type     >  ret (make_shared<input_type>());

ret->reserve(container.size());

for(auto	it = container.begin();it!=container.end();++it) 
{
   if( '1'!=(*hash_container)[*it] )(*hash_container)[*it]='1';
}

for(auto	it = container2.begin();it!=container2.end();++it) 
{
	  if( '1' == (*hash_container)[*it] )
   {
  	  	ret->emplace_back(*it);
   }
}
return ret;
}

template<class input_type>
shared_ptr<input_type >
_intersect_ctl(const input_type & container1,const input_type & container2)
{
			if(container1.size()<=container2.size())
	  	{
	      return __intersect_ctl(container1,container2);
		  }
		  else
	      return __intersect_ctl(container2,container1);
}

template<class input_type>
shared_ptr<input_type >
_intersect_ctl(const shared_ptr<input_type> & container1,const input_type & container2)
{
			if(container1->size()<=container2.size())
	  	{
	      return __intersect_ctl(*container1,container2);
		  }
		  else
	      return __intersect_ctl(container2,*container1);
}

template<class input_type>
shared_ptr<input_type >
_intersect_ctl(const input_type & container1,const shared_ptr<input_type> & container2)
{
			if(container1.size()<=container2->size())
	  	{
	      return __intersect_ctl(container1,*container2);
		  }
		  else
	      return __intersect_ctl(*container2,container1);
}

template<class input_type>
shared_ptr<input_type >
_intersect_ctl(const shared_ptr<input_type> & container1,const shared_ptr<input_type> & container2)
{
			if(container1->size()<=container2->size())
	  	{
	      return __intersect_ctl(*container1,*container2);
		  }
		  else
	      return __intersect_ctl(*container2,*container1);
}
//___________________________________________________________
template<class T>
void test_print(T a)
{
	cout<<a<<" ";
}
//___________________________________________________________
int test_intersect()
{ 
	  cout<<"test_intersect"<<endl;
	  vector<char> a{'a','b','c','d','e'};
    vector<char> b{'a','b','c','z'};
    for_each(a.begin(),a.end(),[](char x){cout<<x<<" ";});
    cout<<endl;
    for_each(b.begin(),b.end(),[](char x){cout<<x<<" ";});
    cout<<endl<<endl;
    auto f = _intersect_ctl(a,b );
    for_each(f->begin(),f->end(),[](char x){cout<<x<<" ";});
	return 0;
}
//_____________________________________________________________________
template<class T>
void test_print_2(T* x)
{
	cout<<" "<<x->first.first<<","<<x->first.second<<" | "<< x->second.first<<","<<x->second.second <<endl;
}

int test_hash_join()
{
	cout<<"test_hash_join"<<endl;
		vector<pair<char,int> > ii2{std::make_pair('a', 1),std::make_pair('b', 2),std::make_pair('b', 3),std::make_pair('d', 4),std::make_pair('c', 13),std::make_pair('c', 19)};
    vector<pair<char,int> > jj2{std::make_pair('a', 2),std::make_pair('b', 4),std::make_pair('c', 6),std::make_pair('e', 8),std::make_pair('c', 26)};
    for_each(ii2.begin(),ii2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl;
    for_each(jj2.begin(),jj2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl<<endl;

    auto f =_hash_inner_join_ctl(ii2,jj2,[](std::pair<char,int> x){return x.first;},[](std::pair<char,int> x){return x.first;});
    for_each(f->begin(),f->end(),[](std::pair<std::pair<char,int>,std::pair<char,int> > x){
	cout<<" "<<x.first.first<<","<<x.first.second<<" | "<< x.second.first<<","<<x.second.second <<endl;
});
	return 0;
}

int test_hash_semi_join()
{
	cout<<"test_hash_semi_join"<<endl;
		vector<pair<char,int> > ii2{std::make_pair('a', 1),std::make_pair('b', 2),std::make_pair('b', 3),std::make_pair('d', 4),std::make_pair('c', 13),std::make_pair('c', 19)};
    vector<pair<char,int> > jj2{std::make_pair('a', 2),std::make_pair('b', 4),std::make_pair('c', 6),std::make_pair('e', 8),std::make_pair('c', 26)};
    for_each(ii2.begin(),ii2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl;
    for_each(jj2.begin(),jj2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl<<endl;

    auto f =_hash_inner_semi_join_ctl(ii2,jj2,[](std::pair<char,int> x){return x.first;},[](std::pair<char,int> x){return x.first;});
    for_each(f->begin(),f->end(),[](std::pair<char,int>  x){
	cout<<" "<<x.first<<","<<x.second<<endl;
});
	return 0;
}


int test_hash_anti_semi_join()
{
	cout<<"test_hash_semi_join"<<endl;
		vector<pair<char,int> > ii2{std::make_pair('a', 1),std::make_pair('b', 2),std::make_pair('b', 3),std::make_pair('d', 4),std::make_pair('c', 13),std::make_pair('c', 19)};
    vector<pair<char,int> > jj2{std::make_pair('a', 2),std::make_pair('b', 4),std::make_pair('c', 6),std::make_pair('e', 8),std::make_pair('c', 26)};
    for_each(ii2.begin(),ii2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl;
    for_each(jj2.begin(),jj2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl<<endl;

    auto f =_hash_inner_anti_semi_join_ctl(ii2,jj2,[](std::pair<char,int> x){return x.first;},[](std::pair<char,int> x){return x.first;});
    for_each(f->begin(),f->end(),[](std::pair<char,int>  x){
	cout<<" "<<x.first<<","<<x.second<<endl;
});
	return 0;
}

int test_hash_anti_join()
{
	cout<<"test_hash_anti_join()"<<endl;
		vector<pair<char,int> > ii2{std::make_pair('a', 1),std::make_pair('b', 2),std::make_pair('b', 3),std::make_pair('d', 4),std::make_pair('c', 13),std::make_pair('c', 19)};
    vector<pair<char,int> > jj2{std::make_pair('a', 2),std::make_pair('b', 4),std::make_pair('c', 6),std::make_pair('e', 8),std::make_pair('c', 26)};
    for_each(ii2.begin(),ii2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl;
    for_each(jj2.begin(),jj2.end(),[](std::pair<char,int> x){	cout<<" "<<x.first<<","<<x.second<<"  ";});cout<<endl<<endl;

    auto f =_hash_inner_anti_join_ctl(ii2,jj2,[](std::pair<char,int> x){return x.first;},[](std::pair<char,int> x){return x.first;});
    for_each(f->begin(),f->end(),[](std::pair<std::pair<char,int>,std::pair<char,int> > x){
	cout<<" "<<x.first.first<<","<<x.first.second<<" | "<< x.second.first<<","<<x.second.second <<endl;
});
	return 0;
}
//___________________________________________________________
int test()
{
  vector<char> a{'a','b','c','d','e'};
	auto b = _map_stl(a,[](char x){ return x+1;});
		 
		 for_each(b->begin(),b->end(),[](int x){
		 	cout<<x<<endl;
		 	});
		 	
		 	auto e = _map_stl(b,[](int x){ return x+1;});
		 	for_each(e->begin(),e->end(),[](int x){
		 	cout<<x<<endl;
		 	});
		 	
		 	
		 auto c = _map_stl(a,[](char x){ return make_pair(x, 1);});
		 for_each(c->begin(),c->end(),[](std::pair<char, int> x){
		 	cout<<x.first <<","<<x.second<<endl;
		 	});

     list<int> aa{'h','i','j','k','l'};
     auto bb = _map_stl(aa,[](int x){ return x+1;});
		 
		 for_each(bb->begin(),bb->end(),[](char x){
		 	cout<<x<<endl;
		 	});
//___________________________________________________
  vector<char> a1{'a','b','c','d','e'};
  auto aa1 = _filter_stl(a1,[](char x){ return x!='a';});
  for_each(aa1->begin(),aa1->end(),[](char x){
		 	cout<<x<<endl;
		 	});
  
  
  list<char> b1{'a','b','c','d','e'};
  auto bb1 = _filter_stl(b1,[](char x){ return x!='b';});
  for_each(bb1->begin(),bb1->end(),[](char x){
		 	cout<<x<<endl;
		 	});
//_______________________________________________________

	cout<<"test_string"<<endl;	 	
	list<string> bc1{"a","b","c","d","e","a"};
	auto bcc1 = _group_by_key_stl(bc1,[](string x){ return x;});
	
	for_each(bcc1->begin(),bcc1->end(),[](std::pair<string,list<string> > x){
		 	for_each(x.second.begin(),x.second.end(),[](string  x){
		 	 	cout<<x<<" ";
		     });
		     cout<<endl;
		 	});	
//___________________________________________________
	cout<<"test_group_by_key_char"<<endl;	
	vector<int> ac1{1,2,3,4,5,6,1};
	auto acc1 = _group_by_key_stl(ac1,[](int x){ return x;});
	for_each(acc1->begin(),acc1->end(),[](std::pair<int,list<int> > x){
		 	for_each(x.second.begin(),x.second.end(),[](int  x){
		 	 	cout<<x<<" ";
		     });
		     cout<<endl;
		 	});	 
	cout<<"test_reduce_char"<<endl;	
	auto acc2 = _reduce_stl<int>(acc1,[](int x,int y){return x+y;});
   
  for_each(acc2->begin(),acc2->end(),[](std::pair<int,int > x){
		 	 	cout<<x.first<<" "<<x.second;
		     cout<<endl;
		 	});	 
//___________________________________________________
	cout<<"test_map_reduce_char"<<endl;	
	vector<char> cc1{'a','b','e','c','f','d','a'};
	auto cc2 = _map_stl(cc1,[](char x){ return make_pair(x, 1);});

  auto ff = _reduce_by_key_stl<int>(cc2,
       [](std::pair<char, int> x){ return x.first;},
       [](std::pair<char, int> x,int y){ return x.second+y;}
  );
  
  for_each(ff->begin(),ff->end(),[](std::pair<char,int > x){
		 	 	cout<<x.first<<" "<<x.second;
		     cout<<endl;
		 	});	
//____________________________________________________
	cout<<"test_distinct_"<<endl;	
	vector<char> dd1{'a','b','e','c','f','d','a','f','d','a'};
	auto dd = _distinct_ctl(dd1);
	 for_each(dd->begin(),dd->end(),[](char x){
		 	 	cout<<x<<endl;
		 	});	
//_____________________________________________________
	cout<<"test_union_all_"<<endl;	
	vector<char> hh1{'a','b','e','c','f','d','a','f','d','a'};
	vector<char> gg1{'a','b','e','c','f','d','a','f','d','a'};

	auto dds = _union_all_ctl(hh1,gg1);
	 for_each(dds->begin(),dds->end(),[](char x){
		 	 	cout<<x<<endl;
		 	});	
//_____________________________________________________
	cout<<"test_union_"<<endl;	
	vector<char> hh2{'a','b','e','c','f','d','a','f','d','a'};
	vector<char> gg2{'a','b','e','c','f','d','a','f','d','a'};

	auto dds1 = _union_ctl(hh2,gg2);
	 for_each(dds1->begin(),dds1->end(),[](char x){
		 	 	cout<<x<<endl;
		 	});
//______________________________________________
test_hash_join();		 		
test_intersect();
return 0;
}


}
#endif
