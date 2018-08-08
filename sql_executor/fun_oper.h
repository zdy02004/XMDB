/*
g++ -C -w -std=c++11 fun_oper.h

表达式模板，用来支持 投影中复杂的 运算和函数
*/

#ifndef SQL_EXPTR
#define SQL_EXPTR

#include <limits>
#include "record_tuple.h"

#define CONST_TYPE 1
#define FIELD_TYPE 2
#define OPER_TYPE  3
#define FUN_TYPE   4
#define TIME_TYPE  5
#define STR_TYPE   6

#define META_PTR_IS_NULL      32100
#define RESULT_PTR_IS_NULL    32101

//类型优先级表
// 											FIELD_TYPE_INT  FIELD_TYPE_SHORT  FIELD_TYPE_LONG FIELD_TYPE_LONGLONG FIELD_TYPE_FLOAT FIELD_TYPE_DOUBLE FIELD_TYPE_STR FIELD_TYPE_DATE  
// FIELD_TYPE_INT		          0                1                 0                  0                  0               0                   0          0
// FIELD_TYPE_SHORT           0                0                 0                  0                  0               0                   0          0 
// FIELD_TYPE_LONG            1                1                 0                  0                  0               0                   0          0
// FIELD_TYPE_LONGLONG        1                1                 1                  1                  0               0                   0          0   
// FIELD_TYPE_FLOAT           1                1                 1                  1                  0               0                   0          1      
// FIELD_TYPE_DOUBLE          1                1                 1                  1                  1               0                   0          1     
// FIELD_TYPE_STR             1                1                 1                  1                  1               1                   0          1        
// any
// FIELD_TYPE_DATE            1                1                 1                  0                  0               0                   0          0        

int field_type_priority[9][9]= { 
0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,1,1,0,0,0,1,
1,1,1,1,1,0,0,1,
1,1,1,1,1,1,0,1,
0,0,0,0,0,0,0,0,
1,1,1,0,0,0,0,0};

//选择优先级高的字段，并返回
int get_max_field_type(int a, int b)
{
	CPP_DEBUG<<"a="<<a<<" b="<<b<<std::endl;
		if( 1 == field_type_priority[a-1][b-1]  )return a;
		else return b;	
}

int get_max_field_type(int a, int b,int c)
{
		return get_max_field_type( get_max_field_type(a,b), c );
}
	

union union_value
{
FIELD_INT       int_value;
FIELD_SHORT     short_value;
FIELD_LONG      long_value;
FIELD_LONGLONG  longlong_value;
FIELD_DOUBLE    double_value;
FIELD_FLOAT     float_value;
FIELD_STR       str_value;
bool            bool_value;

union_value(FIELD_LONGLONG in):longlong_value(in){}
union_value(FIELD_INT in):int_value(in){}
union_value(FIELD_SHORT in):short_value(in){}
union_value(FIELD_LONG in):long_value(in){}
union_value(FIELD_FLOAT in):float_value(in){}
union_value(FIELD_DOUBLE in):double_value(in){}
union_value(FIELD_STR in):str_value(in){}
union_value(bool in):bool_value(in){}



FIELD_DOUBLE operator + (union_value other)
{
		return double_value + other.double_value;
}

FIELD_DOUBLE operator - (union_value other)
{
		return double_value - other.double_value;
}

FIELD_DOUBLE operator * (union_value other)
{
		return double_value * other.double_value;
}

FIELD_DOUBLE operator / (union_value other)
{
		return double_value / other.double_value;
}

FIELD_DOUBLE operator ^ (union_value other)
{
		return long_value ^ other.long_value;
}

FIELD_DOUBLE operator % (union_value other)
{
		return long_value % other.long_value;
}

bool operator < (union_value other)
{
		return double_value < other.double_value;
}

bool operator <= (union_value other)
{
		return double_value <= other.double_value;
}

bool operator > (union_value other)
{
		return double_value > other.double_value;
}

bool operator >= (union_value other)
{
		return double_value >= other.double_value;
}

bool operator == (union_value other)
{
		return double_value == other.double_value;
}

bool operator != (union_value other)
{
		return double_value != other.double_value;
}


};
// 函数和运算的父类
struct fun_oper
{
int tag;
int node_type;
bool is_reduce;
std::string alias_name;
fun_oper * father;	
mem_table_t  * mem_table ;
int set_mem_table(mem_table_t  * _mem_table ){	mem_table = _mem_table;         }


fun_oper():father(NULL),is_reduce(false){}
fun_oper(int tag_ , int node_type_ ):tag(tag_),node_type(node_type_),father(NULL),is_reduce(false){}
int get_tag(){return tag;}
int set_tag(int tag_){ tag = tag_;}
int set_alias_name( std::string  _alias_name ){ alias_name = _alias_name;CPP_DEBUG<<"alias_name=" <<alias_name<<std::endl;}
std::string & get_alias_name(){return alias_name;}
virtual union_value eval(  record_meta * _meta , generic_result * _result ) = 0;  
virtual ~fun_oper(){};  
};

// 运算的值 
// 字段终结符
struct value_element:public fun_oper
{
	record_tuple   record_tuple_;
	std::string    field_name ;
	RawTarget      rt;
	
	value_element(const char * _relation_name,  const char * _column_name,int _index): fun_oper(0,FIELD_TYPE),field_name(_column_name), rt(RawTarget(_relation_name,_column_name,_index)){is_reduce = true;}
	value_element(std::string & _relation_name, std::string & _column_name,int _index):fun_oper(0,FIELD_TYPE),field_name(_column_name),rt(RawTarget(_relation_name,_column_name,_index)){is_reduce = true;}
	value_element(const char * _column_name,int _index ):fun_oper(0,FIELD_TYPE),field_name(_column_name), rt(RawTarget( _column_name,_index) ){is_reduce = true;}

	int set_meta   ( record_meta    * _meta     ){	record_tuple_.meta   = _meta;   }
	int set_field_name(std::string &_field_name ){	field_name = _field_name;       }
  int set_rt     (RawTarget   &_RawTarget    )
  {	
  	rt = _RawTarget; 
  	field_name = rt.column_name; 
  } 
	
	virtual union_value eval(  record_meta * _meta , generic_result * _result ) 
	{
			 DEBUG("enter value_element eval \n");
			 if( NULL == _meta )
			 	{
			 		ERROR("META_PTR_IS_NULL \n");
			 		return META_PTR_IS_NULL;
			 	}
			 	if( NULL == _result )
			 	{
			 		ERROR("RESULT_PTR_IS_NULL \n");
			 		return META_PTR_IS_NULL;
			 	}
			 	
		   record_tuple_.result = _result;
		   record_tuple_.meta   = _meta;
		   field_t field; 
		   int err = record_tuple_.get_field_desc(mem_table ,field_name, field);
		   	if( err )
			 	{
			 		ERROR("record_tuple_.get_field_desc err is %d \n",err);
			 		return err;
			 	}
		   char * addr = NULL;
		   err = record_tuple_.get_field(mem_table ,field_name,&addr);	
		   if( err )
			 	{
			 		ERROR("record_tuple_.get_field err is %d \n",err);
			 		return err;
			 	}	   
       RETURN_CAST_FIELD( field.field_type,  addr ) ;
	}  
	 ~value_element(){}
};


// 值终结符
struct const_element:public fun_oper
{
  union_value value; 
  
	const_element(union_value x):fun_oper(0,CONST_TYPE),value(x){is_reduce = true;}
  	
	virtual union_value eval(  record_meta * _meta , generic_result * _result ) 
	{  
			 DEBUG("enter const_element eval \n");
		   return  value;
	}  
 ~const_element(){}

	
};

// 字符串终结符
struct str_element:public fun_oper
{
  std::string value; 
  
	str_element(const char * x):fun_oper(0,STR_TYPE),value(x){is_reduce = true;}
  	
	virtual union_value eval(  record_meta * _meta , generic_result * _result ) 
	{
		   DEBUG("enter str_element eval \n");

		   return  const_cast<char *>(value.c_str());
	}  
  ~str_element(){}

};


// s时间终结符
struct time_element:public fun_oper
{
  union_value value; 
  time_element():value(0),fun_oper(0,TIME_TYPE){is_reduce = true;}
	virtual union_value eval(  record_meta * _meta , generic_result * _result ) 
	{
			DEBUG("enter time_element eval \n");
		  value.long_value = get_systime();
		  return  value;
	}  
 ~time_element(){}

};

// 运算的父类
// + - * / mod  ^ 
struct oper_element:public fun_oper
{
	fun_oper * left;
	fun_oper * right;
	oper_element():fun_oper(0,OPER_TYPE),left(NULL),right(NULL){}
	oper_element( int tag_ ):fun_oper(tag_,OPER_TYPE),left(NULL),right(NULL){}
  int set_left   ( fun_oper * _left ){	left  = _left; }
	int set_right  ( fun_oper * _right){	right = _right;  }
	
	virtual union_value eval(  record_meta * _meta , generic_result * _result ) = 0;
 ~oper_element(){
			delete left;
			delete right;
			}

};


// 函数的父类
// min max sum count avg
struct fun_element:public fun_oper
{
	fun_oper * children;
	fun_element(int tag_):fun_oper(tag_,FUN_TYPE),children(NULL){}
	fun_element():fun_oper( 0 ,FUN_TYPE),children(NULL){}	
	int set_children  ( fun_oper * _children ){	children = _children;  }
	
	virtual union_value eval(  record_meta * _meta , generic_result * _result )= 0  ;
  ~fun_element(){
	delete children;
	}
};

// +
struct oper_add:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_add eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) + right->eval(_meta,result); 
		 }
};

// -
struct oper_minus:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  { 
		
		 DEBUG("enter oper_minus eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		return left->eval(_meta,result) - right->eval(_meta,result);
		 }
};

// *
struct oper_mul:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  { 
		 DEBUG("enter oper_mul eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		return left->eval(_meta,result) * right->eval(_meta,result); 
		}
};

// /
struct oper_div:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_div eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
		 return left->eval(_meta,result) / right->eval(_meta,result);
		  }
};

// ^
struct oper_pow:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_pow eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) ^ right->eval(_meta,result);
		  }
};

// mod
struct oper_mod:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_mod eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) % right->eval(_meta,result);
		  }
};

//oper max
struct oper_max:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  { 
		 
		 DEBUG("enter oper_max eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		return std::max(left->eval(_meta,result).double_value , right->eval(_meta,result).double_value );
		 }
};

//oper min
struct oper_min:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_min eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return std::max( left->eval(_meta,result).double_value , right->eval(_meta,result).double_value );
		 	
		 	 }
};

// oper <
struct oper_lt:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_lt eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) < right->eval(_meta,result); 
		 }
};

// oper <=
struct oper_le:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_le eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) <= right->eval(_meta,result); 
		 }
};

// oper >
struct oper_gt:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_gt eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) > right->eval(_meta,result); 
		 }
};

// oper >=
struct oper_ge:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_ge eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) >= right->eval(_meta,result); 
		 }
};

// oper ==
struct oper_eq:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_eq eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) == right->eval(_meta,result); 
		 }
};


// oper !=
struct oper_ne:public oper_element
{
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter oper_ne eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			
		 return left->eval(_meta,result) != right->eval(_meta,result); 
		 }
};


// sum
struct fun_sum:public fun_element
{
	double sum_ret;
	fun_sum():sum_ret(0){} 
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter fun_sum eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
		  
		  sum_ret += children->eval(_meta,result).double_value ;
		  return sum_ret;
		   }
};
// max
struct fun_max:public fun_element
{
	union_value max_ret;
	fun_max():max_ret(0){} 
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
		 DEBUG("enter fun_max eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
		  max_ret  = std::max( max_ret.double_value, children->eval(_meta,result).double_value ) ; 
		  return max_ret; 
		  
		  }
};

// min
struct fun_min:public fun_element
{
	union_value min_ret;
	fun_min():min_ret(0){} 
	virtual union_value eval(  record_meta * _meta , generic_result * result )  {
	 	 DEBUG("enter fun_min eval \n");
		 if( NULL == _meta )
			{
				ERROR("META_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			if( NULL == result )
			{
				ERROR("RESULT_PTR_IS_NULL \n");
				return META_PTR_IS_NULL;
			}
			 	 
		  min_ret  = std::min( min_ret.double_value, children->eval(_meta,result).double_value ) ;
		  return min_ret; 
		  
		  }
};

// count
struct fun_count:public fun_element
{
	union_value count;
	fun_count():count(0){} 
	virtual union_value eval(  record_meta * _meta , generic_result * result )  { 
		 DEBUG("enter fun_count eval \n");
		 tag =T_INT ;
		 ++count.longlong_value ;
		 return count.longlong_value; 
		 
		 }
};

// avg
// 这里的实现有问题
struct fun_avg:public fun_element
{
	unsigned long count;
	double sum_ret;
	fun_avg():count(0),sum_ret(0){} 
	virtual union_value eval(  record_meta * _meta , generic_result * result )  { 
		 DEBUG("enter fun_avg eval \n");
		 	 if( NULL == _meta )
			 	{
			 		ERROR("META_PTR_IS_NULL \n");
			 		return META_PTR_IS_NULL;
			 	}
			 	if( NULL == result )
			 	{
			 		ERROR("RESULT_PTR_IS_NULL \n");
			 		return META_PTR_IS_NULL;
			 	}
			 	
		 ++count ; 
		 sum_ret += children->eval(_meta,result).double_value; 
		 return sum_ret/count;
		  }
};



 fun_oper * resolve_project_to_opper_node( QueryAnalyser * qa , rapidjson::Value  * v,int& index  ){
 	
 	  if( v->IsArray() ) {
  	  v= &( (*v)[0] );
 	  }
 	  
 	  rapidjson::Value  * vv ;
		if ( v->HasMember("PROJECT") )
			vv = &(*v)["PROJECT"];
		else vv = v;
			
		rapidjson_log( vv );
	  fun_oper * child_ptr = NULL;
		fun_oper * child_ptr2 = NULL;	
		
		// fun_type 和 oper_type 均采用 自顶向下构造
		if ( vv->HasMember(rapidjson::StringRef("FUN_TYPE") )   ) {
			CPP_DEBUG<< "  HasMember  FUN_TYPE " <<endl;	
			switch( (*vv)["tag"].GetInt() )
			{
				case T_FUN_COUNT:{
					fun_count * node = new fun_count ;
					node->tag = T_FUN_COUNT;
					node->set_children( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"] ,index )  );
					if( 0 == child_ptr )return child_ptr; 
					child_ptr->father = node ;
					node->tag =get_max_field_type(node->tag , child_ptr->tag);
				  if( v->HasMember("PROJECT_ALIAS") ){node->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	node->set_alias_name( temp_name );
			  		
			  	}
			    return node;
				}
				case T_FUN_SUM:{
					CPP_DEBUG<< " T_FUN_SUM " <<endl;

					//std::shared_ptr<fun_sum> node(new fun_sum );
					fun_sum * node = new fun_sum;
					node->tag = T_FUN_SUM;
					fun_sum * ptr = node;
					ptr->set_children(  child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"] ,index )  );
					if( 0 == child_ptr )return child_ptr;
					child_ptr->father = ptr ;
					ptr->tag =get_max_field_type(ptr->tag , child_ptr->tag);
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_FUN_AVG:{
					CPP_DEBUG<< " T_FUN_AVG " <<endl;

					//std::shared_ptr<fun_avg> node(new fun_avg );
					fun_avg *  node = new fun_avg;
					node->tag = T_FUN_AVG;						
					fun_avg * ptr = node;
					ptr->set_children(  child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"] ,index )  );
					if( 0 == child_ptr )return child_ptr; 
					child_ptr->father = ptr ;
					ptr->tag =get_max_field_type(ptr->tag , child_ptr->tag);
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
					case T_FUN_SYS:{
					
					break;
				}
				case T_FUN_MAX:{
					CPP_DEBUG<< " T_FUN_MAX " <<endl;
					if( std::string( (*vv)["FUN_TYPE"].GetString() )  == std::string("MAXX") ){
						CPP_DEBUG<< " T_FUN_MAXX " <<endl;
						//std::shared_ptr<oper_max> node(new oper_max );
						oper_max * node = new oper_max;
						node->tag = T_FUN_MAX;
						oper_max * ptr = node;
				  	//分别向左右节点继续构造				  
				  	ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0][0],index  ) );
				  	ptr->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][0][1],index ) );
				  	if( 0 == child_ptr )return child_ptr; 
				  	child_ptr->father = ptr ;
						if( 0 == child_ptr2 )return child_ptr2;
					  child_ptr2->father = ptr ;
		
			    	if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  		else
			  		{
			  		auto temp_name =to_string(index);
			  	  ptr->set_alias_name( temp_name );
			  			
			  		}
			    	ptr->tag =get_max_field_type(  child_ptr->tag,child_ptr2->tag );
			    	
			    	return ptr;
					}
					
					//std::shared_ptr<fun_max> node(new fun_max );
					fun_max* node = new fun_max;
					node->tag = T_FUN_MAX;
					fun_max * ptr = node;
					ptr->set_children(  child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"] ,index )  );
					if( 0 == child_ptr )return child_ptr; 
					child_ptr->father = ptr ;
					ptr->tag =get_max_field_type(ptr->tag , child_ptr->tag);
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_FUN_MIN:{
					CPP_DEBUG<< " T_FUN_MIN " <<endl;
					if( std::string( (*vv)["FUN_TYPE"].GetString() )  == std::string("MINX") ){
						CPP_DEBUG<< " T_FUN_MINX " <<endl;
						//std::shared_ptr<oper_min> node(new oper_min );
						oper_min * node = new oper_min;
						node->tag = T_FUN_MIN;
						oper_min * ptr = node;
				  	//分别向左右节点继续构造				  
				  	ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0][0],index  ) );
				  	ptr->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][0][1],index ) );
				  	if( 0 == child_ptr )return child_ptr; 
				  	child_ptr->father = ptr ;
						if( 0 == child_ptr2 )return child_ptr2;
						child_ptr2->father = ptr ;		
			    	ptr->tag =get_max_field_type( child_ptr->tag,child_ptr2->tag );
				  	if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  		else
			  		{
			  		auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  			
			  		}
			    	return ptr;
					}
					//std::shared_ptr<fun_min> node(new fun_min );
					fun_min * node = new fun_min;
					node->tag = T_FUN_MIN;						
					fun_min * ptr = node;
					ptr->set_children(  child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"] ,index )  );
					if( 0 == child_ptr )return child_ptr; 
					child_ptr->father = ptr ;
					ptr->tag =get_max_field_type(ptr->tag , child_ptr->tag);
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_CUR_TIME:{
					CPP_DEBUG<< " T_CUR_TIME " <<endl;

					//std::shared_ptr<time_element> node(new time_element );
					time_element * node = new time_element;
					node->tag = T_CUR_TIME;						
					time_element * ptr = node;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_ROW_COUNT:{
					
					break;
				}
				}

			}
	
		
		if ( vv->HasMember("OP_TYPE")   ) {
			
			
			//目标上的运算	
		  CPP_DEBUG<< "  HasMember  OP_TYPE " <<endl;		
			switch( (*vv)["tag"].GetInt() )
			{
				case T_OP_ADD:{
					CPP_DEBUG<< " T_OP_ADD " <<endl;

					//std::shared_ptr<oper_add> node(new oper_add );
					oper_add * node  = new oper_add;
					node->node_type = T_OP_ADD;
					oper_add * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =get_max_field_type(  child_ptr->get_tag(),child_ptr2->get_tag() );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}
				case T_OP_MINUS:{
					CPP_DEBUG<< " T_OP_MINUS " <<endl;

					//std::shared_ptr<oper_minus> node(new oper_minus );
					oper_minus * node = new oper_minus;
					node->node_type = T_OP_MINUS;
					oper_minus * ptr = node;
				  //分别向左右节点继续构造				  
				  ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index ) );
				  ptr->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );
				  if( 0 == child_ptr )return child_ptr;
				  child_ptr->father = ptr ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = ptr ;
			    ptr->tag =get_max_field_type( child_ptr->tag,child_ptr2->tag );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_OP_MUL:{
					CPP_DEBUG<< " T_OP_MUL " <<endl;
					//std::shared_ptr<oper_mul> node(new oper_mul );
					oper_mul * node = new oper_mul;
					node->node_type = T_OP_MUL;
					oper_mul * ptr = node;
				  //分别向左右节点继续构造				  
				  ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index ) );
				  ptr->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );		
				  if( 0 == child_ptr )return child_ptr;
				  child_ptr->father = ptr ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = ptr ;
			    ptr->tag =get_max_field_type(  child_ptr->tag,child_ptr2->tag );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_OP_DIV:{
					CPP_DEBUG<< " T_OP_DIV " <<endl;

					//std::shared_ptr<oper_div> node(new oper_div );
					oper_div * node = new oper_div;
					node->node_type = T_OP_DIV;						
					oper_div * ptr = node;
				  //分别向左右节点继续构造				  
				  ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index ) );
				  ptr->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr;
				  child_ptr->father = ptr ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = ptr ;	
			    ptr->tag =get_max_field_type( child_ptr->tag,child_ptr2->tag );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_OP_REM:{
					break;
				}
				case T_OP_POW:{
					CPP_DEBUG<< " T_OP_POW " <<endl;
					//std::shared_ptr<oper_pow> node(new oper_pow );
					oper_pow * node = new oper_pow;
					node->node_type = T_OP_POW;										
					oper_pow * ptr = node;
				  //分别向左右节点继续构造				  
				  ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index ) );
				  ptr->set_right( child_ptr2 =resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );		
				  if( 0 == child_ptr )return child_ptr;
				  child_ptr->father = ptr ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = ptr ;
			    ptr->tag =get_max_field_type(  child_ptr->tag,child_ptr2->tag );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
			    return ptr;
				}
				case T_OP_MOD:{
					CPP_DEBUG<< " T_OP_MOD " <<endl;

					//std::shared_ptr<oper_mod> node(new oper_mod );
					oper_mod * node = new oper_mod;
					node->node_type = T_OP_MOD;								
					oper_mod * ptr = node;
				  //分别向左右节点继续构造				  
				  ptr->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index ) );
				  ptr->set_right( child_ptr2 =resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr;
				  child_ptr->father = ptr ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = ptr ;		
			    ptr->tag = get_max_field_type(  child_ptr->tag,child_ptr2->tag );
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}
				  //返回自己
			    return ptr;
				}
				
					case T_OP_EQ:{
					CPP_DEBUG<< " T_OP_EQ " <<endl;

					oper_eq * node  = new oper_eq;
					node->node_type = T_OP_EQ;
					oper_eq * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =FIELD_TYPE_INT;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}
				
	case T_OP_LE:{
					CPP_DEBUG<< " T_OP_LE " <<endl;

					oper_le * node  = new oper_le;
					node->node_type = T_OP_LE;
					oper_le * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =FIELD_TYPE_INT;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}				
				
	case T_OP_LT:{
					CPP_DEBUG<< " T_OP_LT " <<endl;

					oper_lt * node  = new oper_lt;
					node->node_type = T_OP_LT;
					oper_lt * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =FIELD_TYPE_INT;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}		
				
	case T_OP_GE:{
					CPP_DEBUG<< " T_OP_GE " <<endl;

					oper_ge * node  = new oper_ge;
					node->node_type = T_OP_GE;
					oper_ge * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =FIELD_TYPE_INT;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}			
				
	case T_OP_GT:{
					CPP_DEBUG<< " T_OP_GT " <<endl;

					oper_gt * node  = new oper_gt;
					node->node_type = T_OP_GT;
					oper_gt * ptr = node;
				  //分别向左右节点继续构造				  
				  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
				  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
				  if( 0 == child_ptr )return child_ptr; 
				  child_ptr->father = node ;
					if( 0 == child_ptr2 )return child_ptr2;
					child_ptr2->father = node ;	
			    node->tag =FIELD_TYPE_INT;
				  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  	else
			  	{
			  	auto temp_name =to_string(index);
			  	ptr->set_alias_name( temp_name );
			  		
			  	}		  
			    return node;
				}				
				
case T_OP_NE:{
	CPP_DEBUG<< " T_OP_NE " <<endl;

	oper_ne * node  = new oper_ne;
	node->node_type = T_OP_NE;
	oper_ne * ptr = node;
  //分别向左右节点继续构造				  
  node->set_left ( child_ptr = resolve_project_to_opper_node(qa, &(*vv)["children"][0],index  ) );
  node->set_right( child_ptr2 = resolve_project_to_opper_node(qa, &(*vv)["children"][1],index ) );	
  if( 0 == child_ptr )return child_ptr; 
  child_ptr->father = node ;
	if( 0 == child_ptr2 )return child_ptr2;
	child_ptr2->father = node ;	
  node->tag =FIELD_TYPE_INT;
  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
	else
	{
	auto temp_name =to_string(index);
	ptr->set_alias_name( temp_name );
		
	}		  
}		
				
				case T_OP_POS:{
					break;
				}
				case T_OP_NEG:{
					
					break;
				}
				case T_CASE:{
								
								break;
							}
				case T_THEN:{
							
							break;
						}
				
			}

		}
       
			// 普通字段构造终结符
			if ( (*vv)["tag"].GetInt() == T_OP_NAME_FIELD  ){
				
			 CPP_DEBUG<< "  T_OP_NAME_FIELD " <<endl;		
			 std::string relation_name;
	     std::string column_name;
	     mem_table_t *mem_table = NULL;	
	     	
					//std::shared_ptr<value_element> node(new value_element );
					value_element * ptr = NULL;
					

					  if( vv->HasMember("RELATION_NAME") ) {
					  	
					  	value_element * node = new value_element(  
					  																		(*vv)["RELATION_NAME"]["str_value_"].GetString(),
					  																		(*vv)["COLUMN_NAME"]["str_value_"].GetString(),
					  																		 0 );
					  								
					  	relation_name = (*vv)["RELATION_NAME"]["str_value_"].GetString();
					  	column_name = (*vv)["COLUMN_NAME"]["str_value_"].GetString();
					  	
					  	
					  	
					    node->node_type = T_OP_NAME_FIELD;
					  	ptr = node;
					  }
			    	else {
					    value_element * node = new value_element(  (*vv)["COLUMN_NAME"]["str_value_"].GetString() , 0 );
					    column_name = (*vv)["COLUMN_NAME"]["str_value_"].GetString();
					    node->node_type = T_OP_NAME_FIELD;
			    	  ptr = node;
			    	 }

				
					
		//直接获得表名失败,从tables 里找对应的 relation_name，找不到或找到多个报错
		if( 0 == relation_name.size() ){
			int field_num = 0;
			for(auto & table : qa->tables )
			{
				long long table_no;
				
				int err = 0;
				// 对于原始表检查该表是否存在
				if(!table.table_name_.empty()){
					 err = search_table_name(const_cast<char *>(table.table_name_.c_str()),&table_no);
					
					 if( 0 == err){
					 	 err = get_table_no_addr(table_no,(void **)(&mem_table));
					 	 if( 0 == err){
					 	 		if( has_field( mem_table ,column_name ) ){
					 	 			++field_num;
					 	 			relation_name = std::string(mem_table->config.table_name);
					 	 			break;
					 	 		}
					 		}
					 }
					 
				}
			}
			
			if( 1 < field_num ){CPP_ERROR<<"ERR_PLEASE_MARK_TABLE_COLOUM"<<endl ;return 0;  }
			if( 0 ==field_num ){CPP_ERROR<<"ERR_NOT_FOUND_COLOUM"<<endl;return 0; 	        }
			}
			else{ // 对于 relation_name 不为空的情况，检查表是否存在，字段是否存在
			int field_num = 0;
			long long table_no;
			int err = search_table_name( const_cast<char *>(relation_name.c_str() ) ,&table_no);		
					 if( 0 == err){
					 	 err = get_table_no_addr(table_no,(void **)(&mem_table));
					 	 if( 0 == err){
					 	 		if( has_field( mem_table ,column_name ) ){
					 	 			++field_num;
					 	 		}
					 		}
					 }
					 else{
					 	CPP_ERROR<<"ERR_NOT_FOUND_TABLE"<<endl;return 0; 	 
					 }
			 if( 0 ==field_num ){CPP_ERROR<<"ERR_NOT_FOUND_COLOUM"<<endl;return 0; 	        }

			}
			field_t field;
			get_field( mem_table , column_name, field );
				
			  ptr->tag = field.field_type;
			 
			  if( v->HasMember("PROJECT_ALIAS") ){ptr->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  else
			  {
			  	ptr->set_alias_name( relation_name + "." + column_name );
			  	
			  }
			  
			if(mem_table)
				{
					ptr->set_mem_table( mem_table );  
					DEBUG( "ptr->set_mem_table( %0x )\n" , mem_table );
				}
			else {
				ERROR("mem_table is NULL\n");
			}
			
			return ptr;
			
			
		}
				
			// 常数字段构造终结符		  
			if ( (*vv)["tag"].GetInt() == T_INT && (*vv)["tag"].GetInt() <= T_BOOL  &&  (*vv)["tag"].GetInt() != T_STRING ) {
				CPP_DEBUG<< " T_CONST " <<endl;
				
				
				auto val_temp = atof( (*vv)["str_value_"].GetString());
				//std::shared_ptr<const_element> node( new const_element( val_temp ) )  ;
			  const_element * node = new const_element( val_temp );
			  int tag = (*vv)["tag"].GetInt();
			  switch(tag)
			  {
			  	case T_INT:  { // 选择最合适的类型
			  		auto val_temp = atoll( (*vv)["str_value_"].GetString());
			  		if( val_temp<= std::numeric_limits<short>::max() && val_temp >= std::numeric_limits<short>::lowest() ){ tag = FIELD_TYPE_SHORT;node->value.short_value = atoi((*vv)["str_value_"].GetString()) ;break; }
			  		else if( val_temp<= std::numeric_limits<int>::max() && val_temp >= std::numeric_limits<int>::lowest() ){ tag = FIELD_TYPE_INT;node->value.int_value = atoi((*vv)["str_value_"].GetString()) ;break; }
			  		else if( val_temp<= std::numeric_limits<long>::max() && val_temp >= std::numeric_limits<long>::lowest() ){ tag = FIELD_TYPE_LONG; node->value.long_value = atol((*vv)["str_value_"].GetString()) ;break; }
			  		else if( val_temp<= std::numeric_limits<long long>::max() && val_temp >= std::numeric_limits<long long>::lowest() ){ tag = FIELD_TYPE_LONGLONG; node->value.longlong_value = atoll((*vv)["str_value_"].GetString()) ;break; }
			  		}
			  	//case T_STRING: tag = FIELD_TYPE_STR; break;
			  	case T_BINARY:tag = FIELD_TYPE_STR; break;
			  	case T_DATE:tag = FIELD_TYPE_DATE; break;
			  	case T_FLOAT:tag = FIELD_TYPE_FLOAT; break;
			  	case T_DOUBLE:tag = FIELD_TYPE_DOUBLE; break;
			  	case T_BOOL: tag = FIELD_TYPE_SHORT;node->value.short_value = atoi((*vv)["str_value_"].GetString()) ;break;


			  }
			  node->tag = tag;
			  CPP_DEBUG<< " node->tag = tag; " <<endl;

			  if( v->HasMember("PROJECT_ALIAS") ){
			  	 CPP_DEBUG<< "  v->HasMember(PROJECT_ALIAS)  " <<std::endl;

			  	node->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  );
			  		
			  		 }
			  else
			  {
			  	CPP_DEBUG<< "  v->HasNoMember(PROJECT_ALIAS),std::endl,index=" <<index<<std::endl;
			  	auto temp_name =  to_string( index );
			  	node->set_alias_name( temp_name );
			  	
			  }
			  CPP_DEBUG<< " T_CONST END" <<endl;
				return node;
				
			}
			
			
			// 常字符串构造终结符		  
			if ( (*vv)["tag"].GetInt() == T_STRING  ) {
				CPP_DEBUG<< " T_STR_CONST " <<endl;
				
				
				
				//std::shared_ptr<str_element> node( new str_element(  
				//	  																			(*vv)["str_value_"].GetString() )
				//	  																		 ) ;
				str_element * node = new str_element(  
					  																			(*vv)["str_value_"].GetString() 
					  																);
			  node->tag = FIELD_TYPE_STR;
			  if( v->HasMember("PROJECT_ALIAS") ){node->set_alias_name( std::string(const_cast<char*>((*v)["PROJECT_ALIAS"]["str_value_"].GetString()))  ); }
			  else
			  {
			  	node->set_alias_name( to_string(index ) );
			  	
			  }
				return node;
				
			}
		  
		 // if ( (*vv)["tag"] == T_STAR  ){
			//return NULL;
		 // }

	}


	// QueryAnalyser * qa ,
	// rapidjson::Value  * projectlist = &((*(qa->project_lists))["children"] );
//解析 project_list 成 oper_fun
inline void resolve_projectlist_to_opper_node( QueryAnalyser * qa , rapidjson::Value  * projectlist,
														   /* out */ std::vector<fun_oper *> & projection_fun_oper_lists
														   				)
{
	  int index = 0;
   	//rapidjson::Value  * projectlist = &((*(qa->project_lists))["children"] );
   	CPP_DEBUG<< " resolve_projectlist_to_opper_node begin() " <<endl;

  	if( projectlist->IsArray() ) {
  	CPP_DEBUG<< "  projectlist->IsArray()  " <<endl;

  		for (auto& v : ( (*projectlist).GetArray() )  ){  				
  		 //projection_fun_oper_lists.push_back( resolve_project_to_opper_node(qa, &v ) );
  		 resolve_projectlist_to_opper_node( qa , &v,projection_fun_oper_lists);
         }//end for
    }
    else if(NULL != projectlist){
    	// 填加投影位置信息
    	CPP_DEBUG<< "  resolve_project_to_opper_node started " <<index<<endl;
    	fun_oper * ptr = resolve_project_to_opper_node( qa , projectlist, index ) ;
    	CPP_DEBUG<< "  resolve_project_to_opper_node finished " <<index<<endl;
    	if(  0 != ptr )
    		{
    			DEBUG("projection_fun_oper_lists.push_back( ptr )\n");
    			projection_fun_oper_lists.push_back( ptr );
    		}
    		else {// 等于 0 应该返回报错
    			ERROR("resolve_project_to_opper_node return ptr is 0 !!\n");
    			return ;
    		}
    	 ++index;
		}

         
}

// 解析 QueryAnalyser 并把 投影解析成 oper 算子
inline void resolve_to_opper_node(  QueryAnalyser * qa ,
														   /* out */ std::vector<fun_oper *> & projection_fun_oper_lists,//投影元的 oper 算子
														   /* out */ record_meta & projection_meta  //投影元数据描述 
														   				)
{
	CPP_DEBUG<< "  resolve_to_opper_node started " <<endl;
	resolve_projectlist_to_opper_node(qa,&((*(qa->project_lists))["children"] ),projection_fun_oper_lists );
	CPP_DEBUG<< "  resolve_projectlist_to_opper_node  end " <<endl;

	for(fun_oper *v : projection_fun_oper_lists)
	{
		if( NULL == v )continue;
		CPP_DEBUG<<"v->alias_name: "<<v->get_alias_name()<<"\n";
		if( v && (v->get_alias_name() ).empty() )continue;
		field_t field;
		strcpy(field.field_name , v->get_alias_name().c_str());
		field.field_type = v->get_tag();
		fill_field_info (&field);
		CPP_DEBUG<<"projection_meta.add_field("<<v->mem_table<<",field); "<<"\n";
		projection_meta.add_field(v->mem_table,field);
		//projection_meta.push_field(v->mem_table ,v->field_name,v->get_alias_name());
		
	}
  CPP_DEBUG<< "  resolve_to_opper_node ended " <<endl;

}

// 解析 QueryAnalyser 并把 条件上的运算解析成 oper 算子
// T = normal_oper_condition_struct
template<class T>
inline void resolve_to_opper_condition(  QueryAnalyser * qa ,
														   /* in */  std::list<T>& lists,
														   /* out */ std::vector<fun_oper *> & fun_oper_condition_lists //条件上的 oper 算子	
														   	)													   				
{
	CPP_DEBUG<< "  resolve_to_opper_condition started " <<endl;
	for(auto &v :lists )resolve_projectlist_to_opper_node(qa,v.context_,fun_oper_condition_lists );
  CPP_DEBUG<< "  resolve_to_opper_condition ended " <<endl;

}


#endif 