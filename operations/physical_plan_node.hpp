#ifndef PLAN_NODE_HPP  
#define PLAN_NODE_HPP 

#define PLAN_TYPE_HASH_INDXE_SCAN   				1
#define PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN		2
#define PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN		3
#define PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN		4
#define PLAN_TYPE_SKIPLIST_LQ_INDXE_SCAN		5
#define PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN		6
#define PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN		7
#define PLAN_TYPE_FULL_SCAN									8
#define PLAN_TYPE_SCAN_NORMAL								9
#define PLAN_TYPE_MERGE											10

#define PLAN_TYPE_EQ_FIELTER								11
#define PLAN_TYPE_ET_FIELTER								12
#define PLAN_TYPE_GQ_FIELTER								13
#define PLAN_TYPE_GT_FIELTER								14
#define PLAN_TYPE_NE_FIELTER								15
#define PLAN_TYPE_BTW_FIELTER								16

#define PLAN_TYPE_DO_JOIN										17


//通用结果集 
//需要实现 allocate  get_date dealloc 接口
//先使用 malloc 后续考虑换成线程内 内存池
struct generic_result
{
	char* data;
	size_t row_size;
	int allocate(size_t s){data =(char*)malloc(s); }
	int allocate(){data =(char*)malloc(row_size); }
	int deallocate(free(data););
	char * get_date(){return data};
	void set_row_size(size_t s){row_size =s; }
	size_t get_row_size(){return row_size; }
}	;	




struct plan_node
{
std::string plan_name;
rapidjson::Value json;
rapidjson::Document  *Doc;

int plan_type;
size_t ret_size;

plan_node(rapidjson::Value& _json,rapidjson::Document * _Doc):Doc(_Doc)
{
		json.CopyFrom( _json,Doc.GetAllocator() );
}

virtual void make_json() = 0;
virtual std::string to_sring () = 0;
virtual int execute() = 0;
};

struct scan_index_node:public plan_node
{
long index_no;						  // 索引 id
int  index_type;            // 1 hash 2 skiplist
mem_table_t *mem_table;		  // 表地址
mem_hash_index_t * index;	  // 索引地址
                            
std::string relation_name ; //表名
std::string column_name   ; //列名
std::string const_value   ; //常数值
std::string const_type    ; //常数类型
	
std::list<finded_Addr_t> ret_list;//结果集
finded_Addr_t * finded_Addr;      //与结果求交集

scan_index_node(long _index_no,
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
virtual int execute() ;
	
};


struct scan_index_hash_node:public scan_index_node
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
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_HASH_INDXE_SCAN){}

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
														trans_no,// get_trans_no()
														*finded_Addr,
														&ret_list
														 );
}

if( const_type == "STRING" )
{
	ret =	mem_hash_index_scanAddr_str (
														mem_table,
														index,
														const_value.c_str(),
														str_hash_fun,
														trans_no,//get_trans_no()
														*finded_Addr,
														&ret_list
														 );
}
			
	return ret;
	
}


};

struct scan_skiplist_eq_node:public scan_index_node
{

scan_skiplist_eq_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN){}

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
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	in.ckey  = const_value.c_str();
	
	ret = mem_skiplist_index_scanAddr_str(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};

struct scan_skiplist_ge_node:public scan_index_node
{

scan_skiplist_ge_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN){}

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
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	in.ckey  = const_value.c_str();
	
	ret = mem_skiplist_index_scanAddr_str_GE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};

struct scan_skiplist_gt_node:public scan_index_node
{

scan_skiplist_gt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN){}

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
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	in.ckey  = const_value.c_str();
	
	ret = mem_skiplist_index_scanAddr_str_G(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


struct scan_skiplist_le_node:public scan_index_node
{

scan_skiplist_le_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_LE_INDXE_SCAN){}

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
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	in.ckey  = const_value.c_str();
	
	ret = mem_skiplist_index_scanAddr_str_LE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};



struct scan_skiplist_lt_node:public scan_index_node
{

scan_skiplist_lt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN){}

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
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	in.ckey  = const_value.c_str();
	
	ret = mem_skiplist_index_scanAddr_str_L(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};


struct scan_skiplist_btw_node:public scan_index_node
{

scan_skiplist_btw_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_index_node(long _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr),
  																					plan_type(PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN){}

virtual int execute( )
{
int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t min,max;
	min.lkey  = atol(const_value[0].c_str());
	max.lkey  = atol(const_value[1].c_str());
	
	ret = mem_skiplist_index_scanAddr_long_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,max,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t min,max;
	min.ckey  = const_value[0].c_str();
	max.ckey  = const_value[1].c_str();
	
	ret = mem_skiplist_index_scanAddr_str_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,max            ,
                                NULL,
                          			trans_no,//get_trans_no()                 //当前事务ID
                          			*finded_Addr,
																&ret_list	    //原始结果集
                        );
}
			
	return ret;
	
}


};



struct merg_index_node:public plan_node
{
finded_Addr_t * finded_Addr;
std::list<generic_result>* ret_list;
	
mem_table_t *mem_table;
scan_skiplist_lt_node(
  								mem_table_t *_mem_table,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								finded_Addr_t * _finded_Addr)::plan_node(_json,_Doc),mem_table(_mem_table),
  																					finded_Addr(_finded_Addr),
  																					plan_type(PLAN_TYPE_MERGE){}

virtual int execute( )
{
int ret = 0;
ret =  merg_index_result(  
                                mem_table,
																*finded_Addr, 
                          			Tn,                 //当前事务ID
																ret_list		    //原始结果集
                        );
			
	return ret;
	
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

	virtual int execute();
	
};


//保留相等的节点
template<class T>
struct filter_eq_node:public filter_node
{
filter_eq_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_EQ_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!( cast_field<T::value_type,field.field_type>( &one , field ) ==  cast_condition<field.field_type>( _const_value , field ) );
										} ), 
									 container->end()); 
	return 0;
}

};


//保留相等的节点
template<class T>
struct filter_eq_node:public filter_node
{
filter_eq_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_EQ_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
								  return	!(cast_field<T::value_type,field.field_type>( &one , field ) ==  cast_condition<field.field_type>( _const_value , field ) );

										} ), 
									 container->end()); 
	return 0;
}

};


template<class T>
struct filter_le_node:public filter_node
{
filter_le_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_LE_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,field.field_type>( &one , field ) <=  cast_condition<field.field_type>( _const_value , field ) );
										} ), 
									 container->end()); 
	return 0;
}

};


template<class T>
struct filter_lt_node:public filter_node
{
filter_lt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_LT_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,field.field_type>( &one , field ) <  cast_condition<field.field_type>( _const_value , field ) );

										} ), 
									 container->end()); 
	return 0;
}

};


template<class T>
struct filter_ge_node:public filter_node
{
filter_ge_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_GE_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,field.field_type>( &one , field ) >=  cast_condition<field.field_type>( _const_value , field ) );

										} ), 
									 container->end()); 
	return 0;
}

};

template<class T>
struct filter_gt_node:public filter_node
{
filter_gt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_GT_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,field.field_type>( &one , field ) >  cast_condition<field.field_type>( _const_value , field ) );

										} ), 
									 container->end()); 
	return 0;
}

};



template<class T>
struct filter_ne_node:public filter_node
{
filter_ne_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type),
  																					plan_type(PLAN_TYPE_GT_FIELTER){}
  																					
virtual int execute()
{
	int ret = 0;
	container->erase(std::remove_if(container->begin(),  container->end(),
		 [&](T::value_type & one ){
		 							// 不相等就删掉，保留相等的
									return	!(cast_field<T::value_type,field.field_type>( &one , field ) !=  cast_condition<field.field_type>( _const_value , field ) );

										} ), 
									 container->end()); 
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
  																					const_type(_const_type),
  																					plan_type(PLAN_TYPE_SCAN_NORMAL){}
  																					
virtual int execute()
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

};

// 普通全表扫描
struct full_scan_node:public plan_node
{
	
 	mem_table_t * mem_table;
  std::list<generic_result> ret_list;//结果集
									
scan_normal_node(mem_table_t * _mem_table , 
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
):plan_node(_json,_Doc),mem_table(_mem_table),plan_type(PLAN_TYPE_FULL_SCAN){}
  																					
virtual int execute()
{
	int ret = 0;
  ret = full_table_scan( mem_table,       //表
												 trans_no,//get_trans_no()                 //当前事务ID
												 &ret_list  	  //原始结果集
);
	return ret;
}

};

// 是最终工作的函数 __hash_inner_join 1 
template<typename fun_type1,typename fun_type2>
shared_ptr<std::list<generic_result> >
ret_hash_inner_join_ctl( std::list<generic_result> & container1, std::list<generic_result> &container2,fun_type1 key_fun1,fun_type2 key_fun2)
{
typedef typename std::result_of<fun_type1(generic_result )>::type  key_type1; 
typedef typename std::result_of<fun_type2(generic_result )>::type  key_type2; 
typedef unordered_map<key_type1,vector<generic_result > hash_map_type;
typedef std::list<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<ret_type     >  ret (make_shared<ret_type>());

ret->reserve(1.6*container1.size());

for(typename std::list<generic_result>::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}

for(typename std::list<generic_result>::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
   			auto row = make_pair((*it2), (*it);
  
  generic_result return_record;
  return_record.set_row_size( it2->get_row_size() + it->get_row_size() );
  return_record.allocate();
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

scan_normal_node( join_eq_condition_struct & _join_eq_condition_struct, 
									shared_ptr<std::list<generic_result> > _pre,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								int _is_first
  									
):plan_node(_json,_Doc),	
		table_name1(join_eq_condition_origin.relation_name[0]),
		table_name2(join_eq_condition_origin.relation_name[1]),
		column_name1(join_eq_condition_origin.column_name[0]),
		column_name2(join_eq_condition_origin.column_name[1]),
		mem_table1(join_eq_condition_origin.mem_table[0]),
		mem_table2(join_eq_condition_origin.mem_table[1]),
		ret_list1(table_ret_map[table_name1]),
		ret_list2(table_ret_map[table_name2]),
		is_first(_is_first),
		plan_type(PLAN_TYPE_DO_JOIN){
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
pre = _pre;
}

	
virtual int execute()
{

char buf[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf[field2.field_size+1];
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

if(is_first){
	ret_list =ret_hash_inner_join_ctl(*ret_list1,*ret_list2,
	[&](record_type& x){	
	memcpy(buf1,x.get_date(),field1.field_size);
	return *cast_ptr_by_field<field1.field_no>( buf1 , field1 );
	},
	[&](record_type& x){
	memcpy(buf2,x.get_date(),field2.field_size);
	return *cast_ptr_by_field<field2.field_no>( buf2 , field2 );
	});
		
}
else
{
  ret_list =ret_hash_inner_join_ctl(*pre,*ret_list2,
	[&](record_type& x){	
	memcpy(buf1,x.get_date()+x.get_row_size() - mem_table1->record_size + field1.field_dis,field1.field_size);
	return *cast_ptr_by_field<field1.field_no>( buf1 , field1 );
	},
	[&](record_type& x){
	memcpy(buf2,x.get_date(),field2.field_size);
	return *cast_ptr_by_field<field2.field_no>( buf2 , field2 );
	});

}

}

};
	
};
#endif
