/*
g++ -C -w -std=c++11 field_exptr.h   
表达式模板，用来支持 投影中复杂的 运算和函数
*/

#ifndef FIELD_EXPTR
#define FIELD_EXPTR
#include <string>

template <typename ExprT>   
struct exprTraits  
{  
    typedef ExprT expr_type;  
};  
  
template <>   
struct exprTraits<char>  
{  
    typedef char expr_type;  
}; 

template <>   
struct exprTraits<short>  
{  
    typedef short expr_type;  
}; 

template <>   
struct exprTraits<int>  
{  
    typedef int expr_type;  
};  

template <>   
struct exprTraits<float>  
{  
    typedef float expr_type;  
}; 

template <>   
struct exprTraits<double>  
{  
    typedef double expr_type;  
};  
  
template <>   
struct exprTraits<std::string>  
{  
    typedef std::string expr_type;  
};  


template <typename ExprT1, typename ExprT2, typename BinOp>   
class BinaryExpr  
{   
public:  
    BinaryExpr(ExprT1 e1, ExprT2 e2,BinOp op=BinOp()) :  
        _expr1(e1), _expr2(e2), _op(op)  
    {}  
  
    auto eval()->decltype(_op(_expr1.eval(),_expr2.eval()))
    {  
        return _op(_expr1.eval(),_expr2.eval());  
    }  
  
private:  
   typename exprTraits<ExprT1>::expr_type _expr1;  
   typename exprTraits<ExprT2>::expr_type _expr2;  
   BinOp  _op;   
};   
 
template <typename ExprT1, typename ExprT2, typename BinOp>   
BinaryExpr<ExprT1, ExprT2, BinOp> make_BinaryExpr( ExprT1 a, ExprT2 b, BinOp c )
{
	return BinaryExpr<ExprT1, ExprT2, BinOp>(a,b,c);
}
 
template<typename T, typename U>
auto Ag_sum(T&& t, U&& u) -> decltype (std::forward<T>(t) + std::forward<U>(u)) 
{ 
	return std::forward<T>(t) + std::forward<U>(u); 
}

 template<typename T, typename U>
auto Ag_min(T&& t, U&& u) -> decltype (std::forward<T>(t) + std::forward<U>(u)) 
{ 
	return std::min( std::forward<T>(t) , std::forward<U>(u) ); 
}

template<typename T, typename U>
auto Ag_max(T&& t, U&& u) -> decltype (std::forward<T>(t) + std::forward<U>(u)) 
{ 
	return std::max( std::forward<T>(t) , std::forward<U>(u) ); 
}

template<typename T, typename U>
auto Ag_avg(T&& t, U&& u) -> decltype (std::forward<T>(t) + std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) + std::forward<U>(u); 
}
 
 template<typename T, typename U>
auto Oper_add(T&& t, U&& u) -> decltype (std::forward<T>(t) + std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) + std::forward<U>(u); 
}

 template<typename T, typename U>
auto Oper_minus(T&& t, U&& u) -> decltype (std::forward<T>(t) - std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) - std::forward<U>(u); 
}
 
  template<typename T, typename U>
auto Oper_mul(T&& t, U&& u) -> decltype (std::forward<T>(t) * std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) * std::forward<U>(u); 
}
 
template<typename T, typename U>
auto Oper_div(T&& t, U&& u) -> decltype (std::forward<T>(t) / std::forward<U>(u)) 
{ 
	if( u != 0)	return  std::forward<T>(t) / std::forward<U>(u); 
		
} 

template<typename T, typename U>
auto Oper_pow(T&& t, U&& u) -> decltype (std::forward<T>(t) ^ std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) ^ std::forward<U>(u); 
		
} 

template<typename T, typename U>
auto Oper_mod(T&& t, U&& u) -> decltype (std::forward<T>(t) % std::forward<U>(u)) 
{ 
	return  std::forward<T>(t) % std::forward<U>(u); 
		
} 
 
 
#endif 