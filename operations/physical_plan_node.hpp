#ifndef PLAN_NODE_HPP  
#define PLAN_NODE_HPP 


/*
g++ -w -lpthread -C -std=c++11 physical_plan_node.hpp 
*/


#define PLAN_TYPE_HASH_INDXE_SCAN   				1
#define PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN		2
#define PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN		3
#define PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN		4
#define PLAN_TYPE_SKIPLIST_LE_INDXE_SCAN		5
#define PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN		6
#define PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN		7
#define PLAN_TYPE_FULL_SCAN									8
#define PLAN_TYPE_SCAN_NORMAL								9
#define PLAN_TYPE_MERGE											10

#define PLAN_TYPE_EQ_FIELTER								11
#define PLAN_TYPE_ET_FIELTER								12
#define PLAN_TYPE_GE_FIELTER								13
#define PLAN_TYPE_GT_FIELTER								14
#define PLAN_TYPE_LE_FIELTER								15
#define PLAN_TYPE_LT_FIELTER								16
#define PLAN_TYPE_NE_FIELTER								17
#define PLAN_TYPE_BTW_FIELTER								18

#define PLAN_TYPE_DO_JOIN										20
#define PLAN_TYPE_DO_SEMI_JOIN							21
#define PLAN_TYPE_DO_ANTI_JOIN							22


#define PHYSICY_PLAN_EMPTY_TABLE 			10501
#define FIELD_NAME_EMPTY 							10502
#define NOT_FOUND_FIELD								10503


#include "../SQL/sql_parser/queryOptimiser.hpp"
#include "ops.hpp"
#include "func_help.hpp"
#include "../mem_date_index_ctl/mem_table_mvcc_op.h"
#include "../mem_date_index_ctl/mem_index_no_manager.h"
#include "index_scan_Addr.hpp"


template<int>
struct get_field_type
{
	
	typedef int value_type;
};

template<>
struct get_field_type<FIELD_TYPE_INT>
{
	
	typedef FIELD_INT value_type;
};

template<>
struct get_field_type<FIELD_TYPE_SHORT>
{
	
	typedef FIELD_SHORT value_type;
};

template<>
struct get_field_type<FIELD_TYPE_LONG>
{
	
	typedef FIELD_LONG value_type;
};

template<>
struct get_field_type<FIELD_TYPE_LONGLONG>
{
	
	typedef FIELD_LONGLONG value_type;
};

template<>
struct get_field_type<FIELD_TYPE_FLOAT>
{
	
	typedef FIELD_FLOAT value_type;
};

template<>
struct get_field_type<FIELD_TYPE_DOUBLE>
{
	
	typedef FIELD_DOUBLE value_type;
};

template<>
struct get_field_type<FIELD_TYPE_DATE>
{
	
	typedef FIELD_DATE value_type;
};

template<>
struct get_field_type<FIELD_TYPE_STR>
{
	
	typedef char* value_type;
};

// 将结果行中的字段析出
template<class T,int T2>
typename get_field_type<T2>::value_type cast_field( T * record , const field_t & field ){  
    
    switch( field.field_type )
    {
    	case FIELD_TYPE_INT:            return *(FIELD_INT *)( (char *)(record)+field.field_dis );
			case FIELD_TYPE_SHORT:          return *(FIELD_SHORT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_LONG:           return *(FIELD_LONG *)( (char *)(record)+field.field_dis );
			case FIELD_TYPE_LONGLONG:       return *(FIELD_LONGLONG *)( (char *)(record)+field.field_dis );
			case FIELD_TYPE_FLOAT:          return *(FIELD_FLOAT *)( (char *)(record)+field.field_dis );
			case FIELD_TYPE_DOUBLE:         return *(FIELD_DOUBLE *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_DATE:           return *(FIELD_DATE *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:            return *(char *)( (char *)(record)+field.field_dis );
    		
    }
   	
   return 0;
}

template<int T>
typename get_field_type<T>::value_type cast_condition( std::string& condition , const field_t & field ){  
    
    switch( field.field_type )
    {
    	case FIELD_TYPE_INT:            return  (FIELD_INT)atoi(condition.c_str() );
			case FIELD_TYPE_SHORT:          return  (FIELD_SHORT)atoi(condition.c_str() );
 			case FIELD_TYPE_LONG:           return  (FIELD_LONG )atol(condition.c_str() );
			case FIELD_TYPE_LONGLONG:       return  (FIELD_LONGLONG)atoll(condition.c_str() );
			case FIELD_TYPE_FLOAT:          return  (FIELD_FLOAT *)atof(condition.c_str() );
			case FIELD_TYPE_DOUBLE:         return  (FIELD_DOUBLE *)atof(condition.c_str() );
				
 			case FIELD_TYPE_DATE:           return  (FIELD_DATE )atol(condition.c_str() );
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:         		return  (char *)(condition.c_str() );
    		
    }
   	
   return 0;
}

void * cast_ptr_by_field( std::string& condition , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {       int *ret =  new int; 	    *ret =  (int)atoi(condition.c_str() );				return (void *)ret;    }
			case FIELD_TYPE_SHORT:   {     short *ret =  new short;     *ret =  (short)atoi(condition.c_str() );			return (void *)ret;    }
 			case FIELD_TYPE_LONG:    {      long *ret =  new long; 		  *ret =  (long )atol(condition.c_str() );		  return (void *)ret;    }
			case FIELD_TYPE_LONGLONG:{ long long *ret =  new long long; *ret =  (long long)atoll(condition.c_str() );	return (void *)ret;    }
			case FIELD_TYPE_FLOAT:   {    float  *ret =  new float;     *ret =   atof(condition.c_str() );		return (void *)ret;    }
			case FIELD_TYPE_DOUBLE:  {    double *ret =  new double;    *ret =  (double)atof(condition.c_str() );		return (void *)ret;    }

				
 			case FIELD_TYPE_DATE:    {       FIELD_INT *ret =  new FIELD_INT; *ret =  (FIELD_DATE )atol(condition.c_str() ); 	return (void *)ret; }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:     {  char *ret =  new char[sizeof(condition.c_str())]; strncpy(ret,condition.c_str(),sizeof(condition.c_str()) ); return (void *)ret; }
    		
    }
		
}

// 字段比较辅助结构
struct field_compare
{
char * buf;
field_t field;
size_t  size;
field_compare(char * _buf,field_t &_field, size_t _size ):buf(_buf),field(_field),size(_size){}
// 将复杂的类型比较转化为二进制上的比较，实现万能的 == 比较
bool operator == ( const field_compare &a)
{
	if(a.field.field_type != field.field_type)return false;
	if(a.size != size)return false;
	if( 0!=strncmp(a.buf,buf,size) )return false;
	return true;
}
};



// 表中是否有该字段
inline int has_field(mem_table_t *mem_table ,std::string field_name){  
   
   if( NULL == mem_table        )   return PHYSICY_PLAN_EMPTY_TABLE;
   if( field_name.empty()       )   return FIELD_NAME_EMPTY;
   for(int i = 0;i < mem_table->config.field_used_num; ++i  )
   {
   		field_t& field = mem_table->config.fields_table[i];
   	  if (0 == strcmp(field.field_name,field_name.c_str()) ){
   	  	return 1;
   	  }
   }
   return 0;

}
// 表中是否有索引
inline int field_has_index(mem_table_t *mem_table ,std::string field_name,long & index_no,int & index_type){  
   int err = has_field( mem_table , field_name);
   if( !err )return err;
   	
   for(int i = 0;i < mem_table->config.field_used_num; ++i  )
   {
   		field_t& field = mem_table->config.fields_table[i];
   	  if (0 == strcmp(field.field_name,field_name.c_str()) ){
   	  	if(field.index_nr > 0 ){
   	  		index_no = field.relate_index[0];
   	  		index_type = field.index_type;
   	  		return 1;
   	  	}
   	  	
   	  }
   }
   return 0;

}

// 从表中获得字段
inline int get_field(mem_table_t *mem_table ,std::string field_name,field_t & field){  
   int err = has_field( mem_table , field_name);
   if( !err )return err;
   	
   for(int i = 0;i < mem_table->config.field_used_num; ++i  )
   {
   		field_t& _field = mem_table->config.fields_table[i];
   	  if (0 == strcmp(_field.field_name,field_name.c_str()) ){
 			 field = _field;
 			 return 0;
   	  	
   	  }
   }
   return NOT_FOUND_FIELD;

}


//通用结果集 
//需要实现 allocate  get_date dealloc 接口
//先使用 malloc 后续考虑换成线程内 内存池
struct generic_result
{
	char* data;
	size_t row_size;
	bool operator == (const generic_result& other) {
	if( row_size == 0 || other.row_size == 0 )return false;
	else if(row_size != other.row_size )return false;
	else {
		return strncmp(data,other.data,row_size); 
	}

  }
  
	int allocate(size_t s){data =(char*)malloc(s); }
	int allocate(){data =(char*)malloc(row_size); }
	int deallocate(){free(data);}
	char * get_data(){return data;};
	void set_row_size( size_t s){row_size =s; }
	size_t get_row_size()const {return row_size; }
}	;	

struct table_field_t
{
	field_t           field;
	mem_table_t      *mem_table;
	
	size_t size(){ return field.field_size;  }
	
  table_field_t(mem_table_t *_mem_table ,std::string _field_name,int _field_order,off_t _field_dis):mem_table(_mem_table)
  {
  		get_field(mem_table ,_field_name,field);
  		field.field_order 		= _field_order;   //字段在记录中排第几个
  		field.field_dis 			= _field_dis;			//该字段距离数据启始地址的距离
  }
       
};

struct record_meta
{
	std::vector<table_field_t>  						table_fields;
	std::unordered_map<std::string,int>			field_index_map; //根据字段名到vector的索引
  off_t																		size;	
	
	record_meta():size(0){}
	
	  //复制元数据
  void operator = (const record_meta & other)
  {
  	table_fields = other.table_fields;
  	field_index_map = other.field_index_map;
  	size = other.size;
  }
  
    //插入字段元信息
  void push_field(mem_table_t *_mem_table ,std::string _field_name)
  {  
  	std::string total_name 		=  std::string( _mem_table->config.table_name ) + std::string(".")+_field_name;	
  	field_index_map[total_name] =  table_fields.size() ;

  	table_fields.emplace_back(_mem_table,_field_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size;  	
  }
  
  
};


// 带描述的 record
// 帮助类，用于赋值,和比较
struct record_tuple
{
  record_meta    *    meta;
  generic_result *		result;	
  
  bool operator ==(const record_tuple & other)
  {
  	return *(result) == *(other.result);
  }
  
  record_tuple(record_meta  * _meta,generic_result *	_result):meta(_meta),result(_result){allocate();}
  int allocate(){return result->allocate(meta->size); }
  
  //插入字段值
  int set_field(mem_table_t *_mem_table ,std::string _field_name,const char * src)
  {
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
     		strncpy( result->data + field.field_dis , src , field.field_size );
    		return 0;
    	}
    	return -1;
    	
  }
  
};

// 带描述的 record 数组
struct record_tuple_array
{
	record_meta    							*    meta;
  std::vector<generic_result>			 result_array;	
};




struct plan_node
{
std::string plan_name;
rapidjson::Value json;
rapidjson::Document  *Doc;

int plan_type;
size_t ret_size;

plan_node(rapidjson::Value& _json,rapidjson::Document * _Doc):Doc(_Doc)
{
		json.CopyFrom( _json,Doc->GetAllocator() );
}

int get_plan_type() {return plan_type;}

virtual void make_json() = 0;
virtual std::string to_sring () = 0;
virtual int execute( unsigned long long  trans_no  ) = 0;
virtual std::list<generic_result>* get_ret_list()
{
	
	return (std::list<generic_result>*)NULL;
}
};

struct scan_hash_index_node:public plan_node
{
long index_no;						  // 索引 id
int  index_type;            // 1 hash 2 skiplist
mem_table_t *mem_table;		  // 表地址
mem_hash_index_t * index;	  // 索引地址
                            
std::string relation_name ; //表名
std::string column_name   ; //列名
std::string const_value   ; //常数值
std::string const_type    ; //常数类型
	
//std::list<finded_Addr_t> ret_list;//结果集
finded_Addr_t   ret_list;	//索引结果集
finded_Addr_t * finded_Addr; //与结果求交集

scan_hash_index_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),index_no(_index_no),
  																					index_type(_index_type),mem_table(_mem_table),
  																					index(_index),relation_name(_relation_name),
  																					column_name(_column_name),const_value(_const_value),
  																					const_type(_const_type),finded_Addr(_finded_Addr)
{
ret_size = mem_table->record_size - RECORD_HEAD_SIZE;
}

virtual void make_json() ;
virtual std::string to_sring () ;
virtual int execute( unsigned long long  trans_no  ) ;
	
};


struct scan_skiplist_index_node:public plan_node
{
long index_no;						  // 索引 id
int  index_type;            // 1 hash 2 skiplist
mem_table_t *mem_table;		  // 表地址
mem_skiplist_index_t * index;	  // 索引地址
                            
std::string relation_name ; //表名
std::string column_name   ; //列名
std::string const_value   ; //常数值
std::string const_type    ; //常数类型
	
//std::list<finded_Addr_t> ret_list;//结果集
finded_Addr_t   ret_list;	//索引结果集
finded_Addr_t * finded_Addr; //与结果求交集

scan_skiplist_index_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),index_no(_index_no),
  																					index_type(_index_type),mem_table(_mem_table),
  																					index(_index),relation_name(_relation_name),
  																					column_name(_column_name),const_value(_const_value),
  																					const_type(_const_type),finded_Addr(_finded_Addr)
{
ret_size = mem_table->record_size - RECORD_HEAD_SIZE;
}

virtual void make_json() ;
virtual std::string to_sring () ;
virtual int execute( unsigned long long  trans_no  ) ;
	
};



struct scan_index_hash_node:public scan_hash_index_node
{
scan_index_hash_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_hash_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_HASH_INDXE_SCAN;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	ret =	mem_hash_index_scanAddr_long (
														mem_table,
														index,
														atoi(const_value.c_str()),
														integer_hash_fun,
														*finded_Addr,
														ret_list
														 );
}

if( const_type == "STRING" )
{
	ret =	mem_hash_index_scanAddr_str (
														mem_table,
														index,
														const_cast<char *>(const_value.c_str() ),
														str_hash_fun,
														*finded_Addr,
														ret_list
														 );
}
			
	return ret;
	
}


};

struct scan_skiplist_eq_node:public scan_skiplist_index_node
{

scan_skiplist_eq_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t* _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){ plan_type = PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN; }

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey, const_value.c_str() );
	
	ret = mem_skiplist_index_scanAddr_str(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};

struct scan_skiplist_ge_node:public scan_skiplist_index_node
{

scan_skiplist_ge_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_GE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str() );
	
	ret = mem_skiplist_index_scanAddr_str_GE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};

struct scan_skiplist_gt_node:public scan_skiplist_index_node
{

scan_skiplist_gt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_G(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_G(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}
	
};


struct scan_skiplist_le_node:public scan_skiplist_index_node
{

scan_skiplist_le_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_LE_INDXE_SCAN;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_LE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_LE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};



struct scan_skiplist_lt_node:public scan_skiplist_index_node
{

scan_skiplist_lt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_L(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_L(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          		*finded_Addr,
								ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};


struct scan_skiplist_btw_node:public scan_skiplist_index_node
{
std::string const_value_array[2];
std::string const_type_array[2];
	
scan_skiplist_btw_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value1,
  								std::string& _const_type1,
  								std::string& _const_value2,
  								std::string& _const_type2,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value1,
  																					_const_type1,_finded_Addr){
  																						const_value_array[0] = _const_value1;
  																						const_value_array[1] = _const_value2;
  																						const_type_array[0]  =  _const_type1;
  																						const_type_array[0]  =  _const_type2;
  																						plan_type =PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN ;}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t min,max;
	min.lkey  = atol(const_value_array[0].c_str());
	max.lkey  = atol(const_value_array[1].c_str());
	
	ret = mem_skiplist_index_scanAddr_long_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,&max,
                                NULL,
                          		*finded_Addr,
															 ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t min,max;
	strcpy(min.ckey  , const_value_array[0].c_str() );
	strcpy(max.ckey  , const_value_array[1].c_str() );
	
	ret = mem_skiplist_index_scanAddr_str_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,&max            ,
                                NULL,
                          		*finded_Addr,
																ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};



struct merg_index_node:public plan_node
{
finded_Addr_t * finded_Addr;
std::list<generic_result> ret_list;
	
mem_table_t *mem_table;
merg_index_node(
  								mem_table_t *_mem_table,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),mem_table(_mem_table),
  																					finded_Addr(_finded_Addr){plan_type =PLAN_TYPE_MERGE;}

virtual int execute( unsigned long long trans_no  )
{
int ret = 0;
ret =  merg_index_result(  
                                mem_table,
								*finded_Addr, 
                 trans_no,                 //当前事务ID
								&ret_list		    //原始结果集
                        );
			
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}



};


// 过滤类节点父类
template<class T>
struct filter_node:public plan_node
{
	std::string relation_name ; //表名
	std::string column_name   ; //列名
	std::string const_value   ; //常数值
	std::string const_type    ; //常数类型
	T* container;
	field_t field;
	
	filter_node( T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):plan_node(_json,_Doc),
  																					container(_container),
  																					field(_field),
  																					relation_name(_relation_name),
  																					column_name(_column_name),
  																					const_value(_const_value),
  																					const_type(_const_type){}

	virtual int execute( unsigned long long  trans_no  );

// 这里不安全 暂时先这么写
virtual std::list<generic_result>* get_ret_list()
{
	return container;
}
	
};


//保留相等的节点
template<class T>
struct filter_eq_node:public filter_node<T>
{
filter_eq_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_EQ_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!( cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) ==  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );
										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};



template<class T>
struct filter_le_node:public filter_node<T>
{
filter_le_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type =PLAN_TYPE_LE_FIELTER ;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) <=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );
										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};


template<class T>
struct filter_lt_node:public filter_node<T>
{
filter_lt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_LT_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) <  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};


template<class T>
struct filter_ge_node:public filter_node<T>
{
filter_ge_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_GE_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) >=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};

template<class T>
struct filter_gt_node:public filter_node<T>
{
filter_gt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_GT_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) >  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};



template<class T>
struct filter_ne_node:public filter_node<T>
{
filter_ne_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type =PLAN_TYPE_GT_FIELTER ;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) !=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};


// 普通全表相等条件 扫描
struct scan_normal_node:public plan_node
{
	
	std::string relation_name;
  std::string column_name;
  std::string const_value;
  std::string const_type;
 	mem_table_t * mem_table;
 	compare_list * pre;
  std::list<generic_result> ret_list;//结果集
									
scan_normal_node(mem_table_t * _mem_table , 
									field_t&  _field,
									compare_list * _pre,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):plan_node(_json,_Doc),
  																					mem_table(_mem_table),
  																					pre(_pre),
  																					relation_name(_relation_name),
  																					column_name(_column_name),
  																					const_value(_const_value),
  																					const_type(_const_type){plan_type = PLAN_TYPE_SCAN_NORMAL;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
  ret = full_table_scan_with_conlist(
														 mem_table,       //表
														 pre,             //比较函数链
														 trans_no,//get_trans_no()                 //当前事务ID
													 	 &ret_list  	  //原始结果集
);
	return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};

// 普通全表扫描
struct full_scan_node:public plan_node
{
	
 	mem_table_t * mem_table;
  std::list<generic_result> ret_list;//结果集
									
full_scan_node(mem_table_t * _mem_table , 
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc
):plan_node(_json,_Doc),mem_table(_mem_table){plan_type = PLAN_TYPE_FULL_SCAN;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
  ret = full_table_scan( mem_table,       //表
												 trans_no,//get_trans_no()                 //当前事务ID
												 &ret_list  	  //原始结果集
);
	return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

};

// 内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
shared_ptr<std::vector<generic_result> >
ret_hash_inner_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename T1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename T2::value_type )>::type  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;
typedef std::vector<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve(1.6*container1.size());

for(typename T1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}

for(typename T2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
   			//auto row = make_pair((*it2), (*it) );
  
  generic_result return_record;
  return_record.set_row_size( it2->get_row_size() + it->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it2)),it2->get_row_size());
  memcpy(return_record.get_data()+it2->get_row_size(),(char *)(&(*it)),it->get_row_size());
  
  ret->push_back(return_record);
   }
}
  return ret;

}


// 半内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
shared_ptr<std::vector<generic_result> >
ret_hash_inner_semi_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename T1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename T2::value_type )>::type  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;
typedef std::unordered_map<key_type2,std::vector<typename T2::value_type> > hash_map_type2;
typedef std::vector<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve(1*container1.size());

for(typename T1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}

for(typename T2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 if((*hash_container2)[key].empty())
	 {
	 (*hash_container2)[key].emplace_back(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
   			//auto row = make_pair((*it2), (*it) );
  
  generic_result return_record;
  return_record.set_row_size( it2->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it2)),it2->get_row_size()); 
  ret->push_back(return_record);
   }
 }
}
  return ret;

}
// 反内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
shared_ptr<std::vector<generic_result> >
ret_hash_inner_anti_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(typename T1::value_type )>::type  key_type1; 
typedef typename std::result_of<fun_type2(typename T2::value_type )>::type  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;
typedef std::unordered_map<key_type2,std::vector<typename T2::value_type> > hash_map_type2;
typedef std::vector<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve(1*container1.size());

for(typename T1::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
   (*hash_container2)[key].emplace_back(*it);
}

for(typename T2::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
key_type1 key = key_fun1(*it);
if((*hash_container2)[key].empty())
{ 
  generic_result return_record;
  return_record.set_row_size( it->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it)),it->get_row_size());
  ret->push_back(return_record);
}

}
  return ret;

}

struct do_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;

std::list<generic_result>* ret_list1 ;
std::list<generic_result>* ret_list2 ;

field_t field1;
field_t field2;
int is_first;
shared_ptr<std::list<generic_result> > pre;
shared_ptr<std::list<generic_result> > ret_list;

// 为了防止循环编译依赖，暂时加的模板
do_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							std::list<generic_result>* _ret_list1,
							std::list<generic_result>* _ret_list2,
							shared_ptr<std::list<generic_result> > _pre,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
pre = _pre;
}
	
virtual int execute( unsigned long long  trans_no  )
{

char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

if(is_first){
	ret_list =ret_hash_inner_join_ctl(*ret_list1,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
	return 0;
		
}
else
{
  ret_list =ret_hash_inner_join_ctl(*pre,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
 return 0;
}

}

virtual std::list<generic_result>* get_ret_list()
{
	return ret_list.get();
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};



struct do_semi_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;

std::list<generic_result>* ret_list1 ;
std::list<generic_result>* ret_list2 ;

field_t field1;
field_t field2;
int is_first;
shared_ptr<std::list<generic_result> > pre;
shared_ptr<std::list<generic_result> > ret_list;

// 为了防止循环编译依赖，暂时加的模板
do_semi_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							std::list<generic_result>* _ret_list1,
							std::list<generic_result>* _ret_list2,
							shared_ptr<std::list<generic_result> > _pre,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_SEMI_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
pre = _pre;
}
	
virtual int execute( unsigned long long  trans_no  )
{

char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

if(is_first){
	ret_list =ret_hash_inner_semi_join_ctl(*ret_list1,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
	return 0;
		
}
else
{
  ret_list =ret_hash_inner_semi_join_ctl(*pre,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
 return 0;
}

}

virtual std::list<generic_result>* get_ret_list()
{
	return ret_list.get();
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};


struct do_anti_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;

std::list<generic_result>* ret_list1 ;
std::list<generic_result>* ret_list2 ;

field_t field1;
field_t field2;
int is_first;
shared_ptr<std::list<generic_result> > pre;
shared_ptr<std::list<generic_result> > ret_list;

// 为了防止循环编译依赖，暂时加的模板
do_anti_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							std::list<generic_result>* _ret_list1,
							std::list<generic_result>* _ret_list2,
							shared_ptr<std::list<generic_result> > _pre,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_ANTI_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
pre = _pre;
}
	
virtual int execute( unsigned long long  trans_no  )
{

char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

if(is_first){
	ret_list =ret_hash_inner_anti_join_ctl(*ret_list1,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
	return 0;
		
}
else
{
  ret_list =ret_hash_inner_anti_join_ctl(*pre,*ret_list2,
	[&](generic_result& x){	
	memcpy(buf1,x.get_data(),field1.field_size);
	//return cast_ptr_by_field<field1_type>( buf1 , field1 );
	return field_compare( buf1 , field1 , field1.field_size );
	},
	[&](generic_result& x){
	memcpy(buf2,x.get_data(),field2.field_size);
	return field_compare( buf2 , field2 , field2.field_size );
	});
 return 0;
}

}

virtual std::list<generic_result>* get_ret_list()
{
	return ret_list.get();
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};
#endif
