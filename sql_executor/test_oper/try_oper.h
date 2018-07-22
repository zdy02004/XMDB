// g++ -C -std=c++11 try_oper.h 
// 先用虚函数 生成 一版
// 在从虚函数生成 静态的模板表达式树
 
template<class T>
struct single_oper
{
typedef  T innertype;

};

template<class T,class T1>
struct double_oper
{
typedef  T left_type;
typedef  T right_type;

};


template<class T>
struct fun_sum:public single_oper<T>
{
typedef typename single_oper<T>::innertype innertype;
innertype ret; 
innertype *child;

fun_sum(innertype child_):ret(0),child(child_){};

innertype operator()()
{
ret += (*child)();
return ret;
}

};
template<class T>
 fun_sum<T> make_fun_sum(T a)
{
	return fun_sum<T>(a);
}



template<class T,class T1>
struct oper_add:public double_oper<T,T1>
{
typedef typename double_oper<T,T1>::left_type left_type;
typedef typename double_oper<T,T1>::right_type right_type;
left_type  *left; 
right_type *right;
	
using innertype = decltype( (*left)() +(*right)()  );

oper_add(T* left_,T1* right_):left(left_),right(right_){};

auto operator()()->decltype( (*left)() +(*left)()  )
{
return (*left)() +(*left)() ;

}

};


template<class T,class T1>
oper_add<T,T1> make_oper_add(T a, T1 b)
{
	return oper_add<T,T1>(a,b);
	
}