/*
 g++ -C -w -std=c++11 sql_field.h   
 
 */
#ifndef FIELD_TOOL
#define FIELD_TOOL

#include "../mem_date_index_ctl/mem_table_ctl.h"
#include "../SQL/sql_parser/queryOptimiser.hpp"

#include<string>
#include<set>
#include<map>
#include<list>
#include<vector>
#include <memory>
#include "../util/murmur_hash.h"

#define  EMPTY_TABLE 			79001
#define  FIELD_NAME_EMPTY 79002
#define  NOT_FOUND_FIELD  79003




#define cast_marco_FIELD_TYPE_INT( __ptr )        (reinterpret_cast<FIELD_INT   *		>(__ptr))
#define cast_marco_FIELD_TYPE_SHORT( __ptr )      (reinterpret_cast<FIELD_SHORT *		>(__ptr))
#define cast_marco_FIELD_TYPE_LONG( __ptr )       (reinterpret_cast<FIELD_LONG  *		>(__ptr))
#define cast_marco_FIELD_TYPE_LONGLONG( __ptr )   (reinterpret_cast<FIELD_LONGLONG *>(__ptr))
#define cast_marco_FIELD_TYPE_FLOAT( __ptr )      (reinterpret_cast<FIELD_FLOAT 	 *>(__ptr))
#define cast_marco_FIELD_TYPE_DOUBLE( __ptr )     (reinterpret_cast<FIELD_DOUBLE 	 *>(__ptr))
#define cast_marco_FIELD_TYPE_DATE( __ptr )       (reinterpret_cast<FIELD_DATE 		 *>(__ptr))
#define cast_marco_FIELD_TYPE_STR( __ptr )        (reinterpret_cast<char  				 *>(__ptr))

#define CAST_FIELD_PTR_1( __ptr )    (reinterpret_cast<FIELD_INT   *		>(__ptr))
#define CAST_FIELD_PTR_2( __ptr )    (reinterpret_cast<FIELD_SHORT *		>(__ptr))
#define CAST_FIELD_PTR_3( __ptr )    (reinterpret_cast<FIELD_LONG  *		>(__ptr))
#define CAST_FIELD_PTR_4( __ptr )    (reinterpret_cast<FIELD_LONGLONG * >(__ptr))
#define CAST_FIELD_PTR_5( __ptr )    (reinterpret_cast<FIELD_FLOAT 	 *  >(__ptr))
#define CAST_FIELD_PTR_6( __ptr )    (reinterpret_cast<FIELD_DOUBLE 	 *>(__ptr))
#define CAST_FIELD_PTR_9( __ptr )    (reinterpret_cast<FIELD_DATE 		 *>(__ptr))
#define CAST_FIELD_PTR_7( __ptr )    (reinterpret_cast<char  				   *>(__ptr))

#define CAST_FIELD_PTR( n, __ptr )   CAST_FIELD_PTR_##n( __ptr )  

#define RETURN_CAST_FIELD( n, __ptr )\
if(n == FIELD_TYPE_INT )return *CAST_FIELD_PTR_1( __ptr );\
else if(n == FIELD_TYPE_SHORT )return *CAST_FIELD_PTR_2( __ptr );\
else if(n == FIELD_TYPE_LONG )return *CAST_FIELD_PTR_3( __ptr );\
else if(n == FIELD_TYPE_LONGLONG )return *CAST_FIELD_PTR_4( __ptr );\
else if(n == FIELD_TYPE_FLOAT )return *CAST_FIELD_PTR_5( __ptr );\
else if(n == FIELD_TYPE_DOUBLE )return *CAST_FIELD_PTR_6( __ptr );\
else if(n == FIELD_TYPE_STR )return CAST_FIELD_PTR_7( __ptr ); 

// 表中是否有该字段
inline int has_field(mem_table_t *mem_table ,std::string field_name){  
   
   if( NULL == mem_table        )   return EMPTY_TABLE;
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
   if( err )return err;
   	
   for(int i = 0;i < mem_table->config.field_used_num; ++i  )
   {
   		field_t& field = mem_table->config.fields_table[i];
   	  if (0 == strcmp(field.field_name,field_name.c_str()) ){
   	  	if(field.index_nr > 0 ){
   	  		index_no = field.relate_index[0];
   	  		index_type = field.index_type[0];
   	  		return 1;
   	  	}
   	  	
   	  }
   }
   return 0;

}

// 从表中获得字段
inline int get_field(mem_table_t *mem_table ,std::string field_name,field_t & field){  
   int err = has_field( mem_table , field_name);
   if( err )return err;
   	
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
inline typename get_field_type<T2>::value_type cast_field( T * record , const field_t & field ){  
    
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
inline typename get_field_type<T>::value_type cast_condition( std::string& condition , const field_t & field ){  
    
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


// 将条件常量转化为值指针
// 需要free 值指针
inline void * cast_ptr_by_field( std::string& condition , const field_t & field ){  
	   switch( field.field_type )
    {
    	//case FIELD_TYPE_INT:     {       int *ret =  new int; 	    *ret =  (int)atoi(condition.c_str() );				return (void *)ret;    }
			//case FIELD_TYPE_SHORT:   {     short *ret =  new short;     *ret =  (short)atoi(condition.c_str() );			return (void *)ret;    }
 			//case FIELD_TYPE_LONG:    {      long *ret =  new long; 		  *ret =  (long )atol(condition.c_str() );		  return (void *)ret;    }
			//case FIELD_TYPE_LONGLONG:{ long long *ret =  new long long; *ret =  (long long)atoll(condition.c_str() );	return (void *)ret;    }
			//case FIELD_TYPE_FLOAT:   {    float  *ret =  new float;     *ret =   atof(condition.c_str() );		return (void *)ret;    }
			//case FIELD_TYPE_DOUBLE:  {    double *ret =  new double;    *ret =  (double)atof(condition.c_str() );		return (void *)ret;    }				
 			//case FIELD_TYPE_DATE:    {       FIELD_INT *ret =  new FIELD_INT; *ret =  (FIELD_DATE )atol(condition.c_str() ); 	return (void *)ret; }
 			//case FIELD_TYPE_STR:     {  char *ret =  new char[sizeof(condition.c_str())]; strncpy(ret,condition.c_str(),sizeof(condition.c_str()) ); return (void *)ret; }
    	case FIELD_TYPE_INT:     { std::shared_ptr<int> ret(new int); 	       				 *ret =  (int)atoi(condition.c_str() );				  return (void *)(ret.get()) ;    }
			case FIELD_TYPE_SHORT:   { std::shared_ptr<short> ret(new short);     				 *ret =  (short)atoi(condition.c_str() );			  return (void *)(ret.get()) ;    }
 			case FIELD_TYPE_LONG:    { std::shared_ptr<long> ret(new long); 	  	 				 *ret =  (long )atol(condition.c_str() );		    return (void *)(ret.get()) ;    }
			case FIELD_TYPE_LONGLONG:{ std::shared_ptr<long long> ret(new long long);  		 *ret =  (long long)atoll(condition.c_str() );	return (void *)(ret.get()) ;    }
			case FIELD_TYPE_FLOAT:   { std::shared_ptr<float> ret(new float);          		 *ret =   atof(condition.c_str() );						  return (void *)(ret.get()) ;    }
			case FIELD_TYPE_DOUBLE:  { std::shared_ptr<double> ret(new double);        		 *ret =  (double)atof(condition.c_str() );		  return (void *)(ret.get()) ;    }		
 			case FIELD_TYPE_DATE:    { std::shared_ptr<FIELD_DATE> ret(new FIELD_DATE);		 *ret =  (FIELD_DATE )atol(condition.c_str() ); return (void *)(ret.get()) ;    }
 			case FIELD_TYPE_STR:     { std::shared_ptr<std::string> str(new std::string);  *str = condition;                              return (void *)(str->c_str() ); }
    }	
}


// 字段比较常用函数
// <
inline bool compare_lt_field( const char * a, const char * b , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {      return ((int)(*a))<((int)(*b));    }
			case FIELD_TYPE_SHORT:   {      return ((short)(*a))<((short)(*b));    }
 			case FIELD_TYPE_LONG:    {      return ((long)(*a))<((long)(*b));    }
			case FIELD_TYPE_LONGLONG:{      return ((long long)(*a))<((long long)(*b));    }
			case FIELD_TYPE_FLOAT:   {      return ((float)(*a))<((float)(*b));    }
			case FIELD_TYPE_DOUBLE:  {      return ((double)(*a))<((double)(*b));    }

				
 			case FIELD_TYPE_DATE:    {      return ((long)(*a))<((long)(*b));       }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:      {      return strncmp(a,b,field.field_size)<0;  }
    		
    }
		
}
// >
inline bool compare_gt_field( const char * a, const char * b , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {      return ((int)(*a))>((int)(*b));    }
			case FIELD_TYPE_SHORT:   {      return ((short)(*a))>((short)(*b));    }
 			case FIELD_TYPE_LONG:    {      return ((long)(*a))>((long)(*b));    }
			case FIELD_TYPE_LONGLONG:{      return ((long long)(*a))>((long long)(*b));    }
			case FIELD_TYPE_FLOAT:   {      return ((float)(*a))>((float)(*b));    }
			case FIELD_TYPE_DOUBLE:  {      return ((double)(*a))>((double)(*b));    }

				
 			case FIELD_TYPE_DATE:    {      return ((long)(*a))>((long)(*b));       }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:      {      return strncmp(a,b,field.field_size)>0;  }
    		
    }
		
}
// <=
inline bool compare_le_field( const char * a, const char * b , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {      return ((int)(*a))<=((int)(*b));    }
			case FIELD_TYPE_SHORT:   {      return ((short)(*a))<=((short)(*b));    }
 			case FIELD_TYPE_LONG:    {      return ((long)(*a))<=((long)(*b));    }
			case FIELD_TYPE_LONGLONG:{      return ((long long)(*a))<=((long long)(*b));    }
			case FIELD_TYPE_FLOAT:   {      return ((float)(*a))<=((float)(*b));    }
			case FIELD_TYPE_DOUBLE:  {      return ((double)(*a))<=((double)(*b));    }

				
 			case FIELD_TYPE_DATE:    {      return ((long)(*a))<=((long)(*b));       }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:      {      return strncmp(a,b,field.field_size)<=0;  }
    		
    }
		
}
// >=
inline bool compare_ge_field( const char * a, const char * b , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {      return ((int)(*a))>=((int)(*b));    }
			case FIELD_TYPE_SHORT:   {      return ((short)(*a))>=((short)(*b));    }
 			case FIELD_TYPE_LONG:    {      return ((long)(*a))>=((long)(*b));    }
			case FIELD_TYPE_LONGLONG:{      return ((long long)(*a))>=((long long)(*b));    }
			case FIELD_TYPE_FLOAT:   {      return ((float)(*a))>=((float)(*b));    }
			case FIELD_TYPE_DOUBLE:  {      return ((double)(*a))>=((double)(*b));    }

				
 			case FIELD_TYPE_DATE:    {      return ((long)(*a))>=((long)(*b));       }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:      {      return strncmp(a,b,field.field_size)>=0;  }
    		
    }
		
}

inline bool compare_eq_field( const char * a, const char * b , const field_t & field ){  
	   switch( field.field_type )
    {
    	case FIELD_TYPE_INT:     {      return ((int)(*a))==((int)(*b));    }
			case FIELD_TYPE_SHORT:   {      return ((short)(*a))==((short)(*b));    }
 			case FIELD_TYPE_LONG:    {      return ((long)(*a))==((long)(*b));    }
			case FIELD_TYPE_LONGLONG:{      return ((long long)(*a))==((long long)(*b));    }
			case FIELD_TYPE_FLOAT:   {      return ((float)(*a))==((float)(*b));    }
			case FIELD_TYPE_DOUBLE:  {      return ((double)(*a))==((double)(*b));    }				
 			case FIELD_TYPE_DATE:    {      return ((long)(*a))==((long)(*b));       }
 			//case FIELD_TYPE_HASH_ENTRY:       return *(FIELD_INT *)( (char *)(record)+field.field_dis ); 
 			//case FIELD_TYPE_RBTREE_ENTRY:     return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			//case FIELD_TYPE_SKIPLIST_ENTRY:   return *(FIELD_INT *)( (char *)(record)+field.field_dis );
 			case FIELD_TYPE_STR:      {      return strncmp(a,b,field.field_size)==0;  }
    		
    }
		
}

inline bool compare_uneq_field( const char * a, const char * b , const field_t & field ){  
	  return !compare_eq_field( a, b , field );
		
}

// 字段比较辅助结构
struct compare_field
{
char * buf;
field_t field;
size_t  size;
compare_field(char * _buf,field_t &_field, size_t _size ):buf(_buf),field(_field),size(_size){}
compare_field(const compare_field& a):buf(a.buf),field(a.field),size(a.size){}
// 将复杂的类型比较转化为二进制上的比较，实现万能的 == 比较
bool operator == ( const compare_field &a) const
{
	if(a.field.field_type != field.field_type)return false;
	if(a.size != size)return false;
	if( 0!=strncmp(a.buf,buf,size) )return false;
	return true;
}

bool operator != ( const compare_field &a) const
{
	return !operator == ( a );
}

bool operator < ( const compare_field &a) const
{
	return compare_lt_field( a.buf, a.buf , a.field );
}

bool operator <= ( const compare_field &a) const
{
	return compare_le_field( a.buf, a.buf , a.field );
}

bool operator > ( const compare_field &a) const
{
	return compare_gt_field( a.buf, a.buf , a.field );
}

bool operator >= ( const compare_field &a) const
{
	return compare_ge_field( a.buf, a.buf , a.field );
}

};

// 使 compare_field 支持 unordered_map
namespace std
{
    template<> struct hash<compare_field>
    {
        typedef compare_field argument_type;
        typedef uint64_t result_type;
       inline result_type operator()(argument_type const& s)  const
        {
           return MurmurHash64A()(s.buf); 
          
        }
    };
}


 
// 将一个投影细化
// v 投影
// 从中析出原始字段
inline int get_project_fields( rapidjson::Value  * v, vector<RawTarget> &raw_target_list ){
 	  rapidjson::Value   *v0 ;
		if ( v->HasMember("children") ) v0 = &((*v)["children"]);
		else v0 = v;

		
	if( v0->IsArray() )for (auto& vv : v0->GetArray()  ){ 
		if( vv.IsArray() ){
		CPP_DEBUG <<"vv.IsArray()\n";	
		
		for (auto& vvv : vv.GetArray()  )get_project_fields( &vvv, raw_target_list );
		break;
	  }
			
		if ( vv.HasMember("FUN_TYPE") || vv.HasMember("OP_TYPE")    ) {
				get_project_fields( &vv,raw_target_list );
		}
		
			// raw project column
			if ( vv["tag"] == T_OP_NAME_FIELD  ){
				CPP_DEBUG <<"get field \n";
  	    rapidjson_log( vv );
  	    
				if( vv.HasMember("RELATION_NAME") ) {raw_target_list.emplace_back(  (vv)["RELATION_NAME"]["str_value_"].GetString(),vv["COLUMN_NAME"]["str_value_"].GetString(),0  );	}
				else { raw_target_list.emplace_back(  vv["COLUMN_NAME"]["str_value_"].GetString() ,0 ); }
				
			}
			//if ( vv["tag"].GetInt() >= T_INT && vv["tag"].GetInt() <= T_BOOL   ) return 0;
			
		//	if ( v->HasMember("PROJECT_ALIAS") ){
		//	vv = &(*v)["PROJECT_ALIAS"];
		//	(raw_target_list.end()-1)->project_alias = (*vv)["str_value_"].GetString();
		//	return;
		//  }
		  
		//  if ( (*vv)["tag"] == T_STAR  ){
		//  return;
		//  }
			
}
else
	{
			// raw project column
			if ( (*v0)["tag"] == T_OP_NAME_FIELD  ){
				CPP_DEBUG <<"get field \n";
  	    rapidjson_log( v0 );
  	    
				if( v0->HasMember("RELATION_NAME") ) {raw_target_list.emplace_back(  (*v0)["RELATION_NAME"]["str_value_"].GetString(),(*v0)["COLUMN_NAME"]["str_value_"].GetString(),0  );	}
				else { raw_target_list.emplace_back(  (*v0)["COLUMN_NAME"]["str_value_"].GetString() ,0 ); }
				
			}
	}

return 0;

}

/*
找出每个表中投影用到的字段
*/
inline int get_projection_fields(
													/*in*/  QueryAnalyser * qa,										
													/*out*/ std::map<std::string,std::set<std::string> >&  aggregat_fields ,  //(表名,用于聚合的字段名)
													/*out*/ std::map<std::string,std::set<std::string> >&  raw_fields ,       //(表名,普通字段名)
													/*out*/ std::map<std::string,std::set<std::string> >&  oper_fields ,      //(表名,普通操作字段名)
													/*out*/ std::map<std::string,std::set<std::string> >&  nomal_func_fields,  //(表名,非聚合函数字段名)
												  /*out*/ std::map<std::string,std::set<std::string> >&  projection_fields  //(表名,非聚合函数字段名)
												)
{
	int ret = 0;
	for (size_t i = 0 ;i <qa->tables.size() ;++i )
	{
		mem_table_t *mem_table     = qa->tables[i].mem_table;
		std::string table_name 		 = qa->tables[i].table_name_;
		std::string alias_name 		 = qa->tables[i].alias_name_;
		
		std::set<std::string> raw_list;		
			
		std::set<std::string> aggregat_list;
		std::set<std::string> oper_list;
		std::set<std::string> nomal_func_list;
							
		vector<RawTarget>  agg_raw_target_list;	 // 聚合函数原始字段名
		for(auto &v : qa-> aggregat_funs)	       // 聚合函数字段名
		{
			 get_project_fields(  v,  agg_raw_target_list );
		}
		
		vector<RawTarget>  oper_raw_target_list;	 // 普通操作原始字段名
		for(auto &v : qa-> project_opers)	// 普通操作字段名
		{
			get_project_fields(  v,  oper_raw_target_list );
		}
		
		vector<RawTarget>  normal_raw_target_list;	 // 非聚合函数原始字段名
		for(auto &v : qa-> nomal_funs)	// 非聚合函数字段名
		{
			get_project_fields(  v,  normal_raw_target_list );
		}	
		
		//————————————————————————————————————————————————————————————————————————
		// 开始析出字段
		
		for(auto &v : qa-> raw_target_list)	// 普通字段名
		{
			//没有表名，就到表中找是否有该字段
			if(v.relation_name.empty() && has_field( mem_table , v.column_name ) ){
				 raw_list.insert(v.column_name);
				 projection_fields[table_name].insert(v.column_name);
			}
			//有表名且相等
			else if ( ( v.relation_name == table_name || v.relation_name == alias_name )&& has_field( mem_table , v.column_name ) ) //暂时不考虑子查询
			{
				raw_list.insert(v.column_name);
				projection_fields[table_name].insert(v.column_name);

			}
		}
		
		for(auto &v : agg_raw_target_list)	// 聚合函数字段名
		{
			//没有表名，就到表中找是否有该字段
			if(v.relation_name.empty() && has_field( mem_table , v.column_name ) ){
				 aggregat_fields[table_name].insert(v.column_name);
				 projection_fields[table_name].insert(v.column_name);
				 
			}
			//有表名且相等
			else if ( ( v.relation_name == table_name || v.relation_name == alias_name )&& has_field( mem_table , v.column_name ) ) //暂时不考虑子查询
			{
				aggregat_fields[table_name].insert(v.column_name);
				projection_fields[table_name].insert(v.column_name);
				
			}
		}
		
		for(auto &v :  oper_raw_target_list)	// 普通操作字段名
		{
			//没有表名，就到表中找是否有该字段
			if(v.relation_name.empty() && has_field( mem_table , v.column_name ) ){
				 oper_fields[table_name].insert(v.column_name);
				 projection_fields[table_name].insert(v.column_name);
				 
			}
			//有表名且相等
			else if ( ( v.relation_name == table_name || v.relation_name == alias_name )&& has_field( mem_table , v.column_name ) ) //暂时不考虑子查询
			{
				oper_fields[table_name].insert(v.column_name);
			  projection_fields[table_name].insert(v.column_name);

			}
		}
		
		for(auto &v : normal_raw_target_list)	// 非聚合函数字段名
		{
			//没有表名，就到表中找是否有该字段
			if(v.relation_name.empty() && has_field( mem_table , v.column_name ) ){
				 nomal_func_fields[table_name].insert(v.column_name);
				 projection_fields[table_name].insert(v.column_name);

			}
			//有表名且相等
			else if ( ( v.relation_name == table_name || v.relation_name == alias_name )&& has_field( mem_table , v.column_name ) ) //暂时不考虑子查询
			{
				nomal_func_fields[table_name].insert(v.column_name);
      	projection_fields[table_name].insert(v.column_name);

			}
		}
		
		 //————————————————————————————————————————————————————————————————————
		
		
		aggregat_fields[table_name] 			= aggregat_list;
		raw_fields[table_name]		  			= raw_list;
		oper_fields[table_name]		  			= oper_list;
		nomal_func_fields[table_name]		  = nomal_func_list;
		
	}
	
}


#endif 
