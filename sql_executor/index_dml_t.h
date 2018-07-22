#ifndef INDEX_DML
#define INDEX_DML
#include"../mem_date_index_ctl/mem_table_mvcc_op.h"
#include "record_tuple.h"

/*

 g++ -C -w -std=c++11 index_dml_t.h


*/


#define RECORD_PTR_IS_NULL  60000
#define MEMTABL_PTR_IS_NULL 60001

#define INDEX_KEY_INT_TYPE  60003
#define INDEX_KEY_STR_TYPE  60004
#define FIELD_OUT_OF_32     60005
#define INDEX_PTR_IS_NULL   60006

int get_index_entry_key_type(const field_t & field)
{
	switch( field.field_type )
    {
    	case FIELD_TYPE_INT:              
			case FIELD_TYPE_SHORT:            
 			case FIELD_TYPE_LONG:             
			case FIELD_TYPE_LONGLONG:         
			case FIELD_TYPE_DATE:             return INDEX_KEY_INT_TYPE;
      case FIELD_TYPE_STR: 
			case FIELD_TYPE_FLOAT:            
			case FIELD_TYPE_DOUBLE:           return INDEX_KEY_STR_TYPE;
    }  	
}



// 工具函数
// 获得索引key
inline int set_index_entry_key( char * addr , const field_t & field ,mem_hash_entry_t& out ){  
    DEBUG("set_index_entry_key begin \n");  
    switch( field.field_type )
    {
    	case FIELD_TYPE_INT:             {DEBUG("case FIELD_TYPE_INT\n"); out.hash_lkey = (FIELD_INT)(*addr );CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; return 0;      }
			case FIELD_TYPE_SHORT:           {DEBUG("case FIELD_TYPE_SHORT\n"); out.hash_lkey = (FIELD_SHORT)(*addr );CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; return 0;     }
 			case FIELD_TYPE_LONG:            {DEBUG("case FIELD_TYPE_LONG\n"); out.hash_lkey = (FIELD_LONG )(*addr );CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; return 0;     }
			case FIELD_TYPE_LONGLONG:        {DEBUG("case FIELD_TYPE_LONGLONG\n"); out.hash_lkey = (FIELD_LONGLONG)(*addr );CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; return 0;  }
			case FIELD_TYPE_DATE:            {DEBUG("case FIELD_TYPE_DATE\n"); out.hash_lkey = (FIELD_DATE )(*addr );CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; return 0;     }
      case FIELD_TYPE_STR: 							{ 
      																	DEBUG("case FIELD_TYPE_STR:\n");
																				std::string str = std::to_string( *((addr )) );  
																				if( str.size() <=32 ){
																					CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; 
																					strcpy(out.hash_ckey  ,str.c_str()  ); 
																				}
																				else {
																					ERROR("FIELD_OUT_OF_32\n");
																					return FIELD_OUT_OF_32;
																				}
																			  } 
			case FIELD_TYPE_FLOAT:            { 
																				DEBUG("case FIELD_TYPE_STR:\n");
																				std::string str = std::to_string( *((FIELD_FLOAT *)(addr )) );  
																				if( str.size() <=32 ){
																					strcpy(out.hash_ckey  ,str.c_str()  ); 
																					CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; 
																				}
																				else {
																					ERROR("FIELD_OUT_OF_32\n");
																					return FIELD_OUT_OF_32;
																				}
																			  } 
			case FIELD_TYPE_DOUBLE:           { 
																				DEBUG("case FIELD_TYPE_STR:\n");
																				std::string str = std::to_string( *((FIELD_DOUBLE *)(addr )) );  
																				if( str.size() <=32 ){
																					
																					strcpy(out.hash_ckey  ,str.c_str()  ); 
																					CPP_DEBUG<<"out.hash_lkey="<<out.hash_lkey<<std::endl; 
																				}
																				else {
																					ERROR("FIELD_OUT_OF_32\n");
																					return FIELD_OUT_OF_32;
																				}
																			  } 		
    }  	
   DEBUG("set_index_entry_key end \n");  
   return 0;
}


// 工具函数
// 获得索引key
inline int set_index_entry_key( char * addr , const field_t & field ,mem_skiplist_entry_t& out ){  
    DEBUG("set_index_entry_key begin \n"); 
    switch( field.field_type )
    {
    	case FIELD_TYPE_INT:              {DEBUG("case FIELD_TYPE_INT:\n"); out.lkey = (FIELD_INT)(*addr ); return 0;           }
			case FIELD_TYPE_SHORT:            {DEBUG("case FIELD_TYPE_SHORT:\n"); out.lkey = (FIELD_SHORT)(*addr );return 0;          }
 			case FIELD_TYPE_LONG:             {DEBUG("case FIELD_TYPE_LONG:\n"); out.lkey = (FIELD_LONG )(*addr );return 0;          }
			case FIELD_TYPE_LONGLONG:         {DEBUG("case FIELD_TYPE_LONGLONG:\n"); out.lkey = (FIELD_LONGLONG)(*addr );return 0;       }
			case FIELD_TYPE_DATE:             {DEBUG("case FIELD_TYPE_DATE:\n"); out.lkey = (FIELD_DATE )(*addr );return 0;          }
      case FIELD_TYPE_STR: 							{ 
      																	DEBUG("case FIELD_TYPE_STR:\n");
																				std::string str = std::to_string( *((addr )) );  
																				if( str.size() <=32 )strcpy(out.ckey  ,str.c_str()  ); 
																				else return FIELD_OUT_OF_32;
																			  } 
			case FIELD_TYPE_FLOAT:            { 
				                                DEBUG("case FIELD_TYPE_FLOAT:\n");
																				std::string str = std::to_string( *((FIELD_FLOAT *)(addr )) );  
																				if( str.size() <=32 )strcpy(out.ckey  ,str.c_str()  ); 
																				else return FIELD_OUT_OF_32;
																			  } 
			case FIELD_TYPE_DOUBLE:           { 
																				DEBUG("case FIELD_TYPE_DOUBLE:\n");
																				std::string str = std::to_string( *((FIELD_DOUBLE *)(addr )) );  
																				if( str.size() <=32 )strcpy(out.ckey  ,str.c_str()  ); 
																				else return FIELD_OUT_OF_32;
																			  } 		
    }  	
   DEBUG("set_index_entry_key end \n"); 
   return 0;
}

// 给索引项赋值
inline int set_index_entry_value(mem_table_t *mem_table, record_t * record_ptr ,mem_hash_entry_t& out ){  
  DEBUG("	set_index_entry_value() begin\n");													

  mem_block_t *mem_block = NULL;
  if(NULL == record_ptr){
  	ERROR("RECORD_PTR_IS_NULL\n");
  	return RECORD_PTR_IS_NULL;
  }
  if(NULL == mem_table ){
  	ERROR("MEMTABL_PTR_IS_NULL\n");
  	return MEMTABL_PTR_IS_NULL;
  }
  get_block_by_record( mem_table ,record_ptr,&mem_block);

  out.record_num = record_ptr->record_num;
  out.block_no = mem_block->block_no;
	DEBUG("	set_index_entry_value() end\n");													
  return 0;
}

// 给索引项赋值
inline int set_index_entry_value(mem_table_t *mem_table, record_t * record_ptr ,mem_skiplist_entry_t& out ){  
 	DEBUG("	set_index_entry_value() begin\n");													

  mem_block_t *mem_block = NULL;
  if(NULL == record_ptr){
  	ERROR("RECORD_PTR_IS_NULL\n");
  	return RECORD_PTR_IS_NULL;
  }
  if(NULL == mem_table ){
  	ERROR("MEMTABL_PTR_IS_NULL\n");
  	return MEMTABL_PTR_IS_NULL;
  }
  get_block_by_record( mem_table ,record_ptr,&mem_block);

  out.record_num = record_ptr->record_num;
  out.block_no = mem_block->block_no;
	DEBUG("	set_index_entry_value() end\n");													
  return 0;
}

// insert_xxx_scn 用于 online 建索引系列
int insert_index_scn(mem_hash_index_t * mem_index_prt, //索引指针
										    mem_hash_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn ,
 												unsigned long long scn  )
{
	DEBUG("	insert_index_scn() begin\n");													
	
//if( INDEX_TYPE_HASH == index_type )
//{

	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type  \n");					
		mem_hash_index_input_long input;
		input.key = index_entry.hash_lkey;
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = integer_hash_fun;
		
		return  mem_hash_index_mvcc_insert_l_scn(                        
                            mem_index_prt ,
                        		&input,
                           out_record_ptr,
                           Tn,                       //事务ID
                           scn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{
	  DEBUG("INDEX_KEY_STR_TYPE == index_key_type  \n");						
		mem_hash_index_input_str input;
		strcpy( input.key , index_entry.hash_ckey );
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = str_hash_fun;
    
	return mem_hash_index_mvcc_insert_str_scn(                        
                           mem_index_prt ,
                           &input,
                           out_record_ptr,
                           Tn,                       //事务ID
                           scn
                          );
//  }
	
}
ERROR("insert_index_scn() END\n");									
return -1;
}


int insert_index_scn(mem_skiplist_index_t * mem_index_prt, //索引指针
										    mem_skiplist_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn ,
 												unsigned long long scn  )
{
	DEBUG("	insert_index_scn() begin\n");													

//if( INDEX_TYPE_SKIP == index_type )
//{
	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type  \n");					
		return  mem_skiplist_mvcc_insert_scn(                        
                           mem_index_prt ,
                        	 &index_entry,
                           out_record_ptr,
                           Tn,                       //事务ID
                           scn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{ 
	DEBUG("INDEX_KEY_STR_TYPE == index_key_type  \n");						
	return mem_skiplist_mvcc_insert_str_scn(                        
                           mem_index_prt ,
                        	 &index_entry,
                           	out_record_ptr,
                           Tn,                       //事务ID
                           scn                       //事务ID
                          );
  }
	
//}
ERROR("insert_index_scn() END\n");									

return -1;
}




// insert_xxx 用于 insert 时触发建索引
int insert_index(mem_hash_index_t * mem_index_prt, //索引指针
										    mem_hash_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn )
{
	if( mem_index_prt == NULL )
		{
			ERROR("mem_index_prt == NULL\n");
			return INDEX_PTR_IS_NULL;
		}
	DEBUG("	insert_index() begin,mem_index_prt is %0x \n",mem_index_prt);													
	
//if( INDEX_TYPE_HASH == index_type )
//{

	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type  \n");					
		mem_hash_index_input_long input;
		input.key = index_entry.hash_lkey;
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = integer_hash_fun;
		
		return  mem_hash_index_mvcc_insert_l(                        
                            mem_index_prt ,
                        		&input,
                           out_record_ptr,
                           Tn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{
	  DEBUG("INDEX_KEY_STR_TYPE == index_key_type  \n");						
		mem_hash_index_input_str input;
		strcpy( input.key , index_entry.hash_ckey );
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = str_hash_fun;
    
	return mem_hash_index_mvcc_insert_str(                        
                           mem_index_prt ,
                           &input,
                           out_record_ptr,
                           Tn,
                           1
                          );
//  }
	
}
ERROR("insert_index() END\n");									

return -1;
}


int insert_index(mem_skiplist_index_t * mem_index_prt, //索引指针
										    mem_skiplist_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
	DEBUG("	insert_index() begin\n");													
//if( INDEX_TYPE_SKIP == index_type )
//{
	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type  \n");					
		return  mem_skiplist_mvcc_insert(                        
                           mem_index_prt ,
                        	 &index_entry,
                           out_record_ptr,
                           Tn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{ 
	DEBUG("INDEX_KEY_STR_TYPE == index_key_type  \n");						
	return mem_skiplist_mvcc_insert_str(                        
                           mem_index_prt ,
                        	 &index_entry,
                           	out_record_ptr,
                           Tn                       //事务ID
                          );
  }
	
//}
ERROR("insert_index() END\n");									
return -1;
}


// del_xxx 用于 del 时触发建索引
int del_index(mem_hash_index_t * mem_index_prt, //索引指针
										    mem_hash_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn )
{
	DEBUG("del_index() begin\n");													

//if( INDEX_TYPE_HASH == index_type )
//{

	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type \n");					
		mem_hash_index_input_long input;
		input.key = index_entry.hash_lkey;
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = integer_hash_fun;
		
		return  mem_hash_index_mvcc_del_l(                        
                            mem_index_prt ,
                        		&input,
                           out_record_ptr,
                           Tn,                       //事务ID
                           1
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_STR_TYPE == index_key_type \n");						
		mem_hash_index_input_str input;
		strcpy( input.key , index_entry.hash_ckey );
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = str_hash_fun;
    
	return mem_hash_index_mvcc_del_str(                        
                           mem_index_prt ,
                           &input,
                           out_record_ptr,
                           Tn
                          );
//  }
	
}
ERROR("del_index() END\n");									

return -1;
}


int del_index(mem_skiplist_index_t * mem_index_prt, //索引指针
										    mem_skiplist_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
	DEBUG("del_index() begin\n");													
//if( INDEX_TYPE_SKIP == index_type )
//{
	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type \n");					
		return  mem_skiplist_mvcc_delete(                        
                           mem_index_prt ,
                        	 &index_entry,
                           Tn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{ 
	DEBUG("INDEX_KEY_STR_TYPE == index_key_type \n");						
	return mem_skiplist_mvcc_delete_str(                        
                           mem_index_prt ,
                        	 &index_entry,
                           Tn                       //事务ID
                          );
  }
	
//}
ERROR("del_index() END\n");									
return -1;
}

// del_xxx 用于 del 时触发建索引
int update_index(mem_hash_index_t * mem_index_prt, //索引指针
										    mem_hash_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn )
{
//if( INDEX_TYPE_HASH == index_type )
//{
	DEBUG("update_index() begin\n");													

	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type\n");													
		mem_hash_index_input_long input;
		input.key = index_entry.hash_lkey;
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = integer_hash_fun;
		
		return  mem_hash_index_mvcc_update(                        
                            mem_index_prt ,
                        		&input,
                           out_record_ptr,
                           Tn                       //事务ID                           
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_STR_TYPE == index_key_type\n");													
		mem_hash_index_input_str input;
		strcpy( input.key , index_entry.hash_ckey );
		input.block_no = index_entry.block_no;
		input.record_num = index_entry.record_num;
    input.hash_fun = str_hash_fun;
    
	return mem_hash_index_mvcc_update_str(                        
                           mem_index_prt ,
                           &input,
                           out_record_ptr,
                           Tn
                          );
//  }
	
}
ERROR("update_index() END\n");									

return -1;
}


int update_index(mem_skiplist_index_t * mem_index_prt, //索引指针
										    mem_skiplist_entry_t &index_entry, 
												field_t &  field,
												record_t * record_ptr,       //对应表上的原始数据 行指针
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
	DEBUG("update_index() begin\n");													

//if( INDEX_TYPE_SKIP == index_type )
//{
	int index_key_type = get_index_entry_key_type( field ) ;
	
	if( INDEX_KEY_INT_TYPE == index_key_type )
	{
		DEBUG("INDEX_KEY_INT_TYPE == index_key_type\n");													
		return  mem_skiplist_mvcc_update(                        
                           mem_index_prt ,
                        	 &index_entry,
                        	 out_record_ptr,
                           Tn                       //事务ID
                          );
   }
   
	if( INDEX_KEY_STR_TYPE == index_key_type )
	{ 
	DEBUG("INDEX_KEY_STR_TYPE == index_key_type\n");													
	return mem_skiplist_mvcc_update_str(                        
                           mem_index_prt ,
                        	 &index_entry,
                        	 out_record_ptr,
                           Tn                       //事务ID
                          );
  }
	
//}
ERROR("update_index() END\n");									
return -1;
}


template<class INDEX_ENTERY_TYPE>
struct index_dml_t
{
mem_table_t *mem_table; // 那个表的索引
std::string field_name;  // 建索引的字段名
record_meta       meta;
record_tuple tuple_one;
field_t          field;
int              index_type;
//mem_hash_entry_t hash_index;
//mem_skiplist_entry_t skiplist_index;
INDEX_ENTERY_TYPE     index_entry; // 索引项
bool is_init;
generic_result return_record;

index_dml_t( mem_table_t *_mem_table, std::string _field_name , int _index_type ):field_name(_field_name),mem_table(_mem_table),index_type( _index_type ),is_init(0)
{
		meta.from_table(_mem_table);
		DEBUG("meta.from_table(_mem_table)\n");
		tuple_one.meta = &meta;
		DEBUG("tuple_one.meta = &meta\n");
		tuple_one.result = &return_record;
		DEBUG("tuple_one.result = &return_record;\n");
		return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);
		
  	
}

//	if( INDEX_TYPE_HASH == index_type )ret = set_hash_index_entry_key( addr ,field , hash_index );
//  if( INDEX_TYPE_SKIP == index_type )ret = set_skiplist_entry_key  ( addr ,field , skiplist_index );

inline int fill_index_help( record_t * record_ptr,char * buf  )
{
	if(!buf)
		{
			ERROR("fill_index_help begin,buf  is NULL\n");
    	return -1;
		}
	DEBUG("fill_index_help begin ,buf is %0x \n",buf);
	//DEBUG("fill_index_help begin ,buf is %d \n", *( (int*)buf) = 1 );
	if(NULL == record_ptr)
		{
			ERROR("RECORD_PTR_IS_NULL! \n");
			return RECORD_PTR_IS_NULL;
		}
	int ret = 0;
	//tuple_one.result = record_ptr;
	memcpy(return_record.get_data(),buf,mem_table->record_size - RECORD_HEAD_SIZE);
	
  char * addr = NULL;
  //mem_hash_entry_t out; 
  
  ret = tuple_one.get_field( mem_table , field_name, &addr);
  if( ret ){
  	ERROR("tuple_one.get_field err is %d\n",ret);
  	return ret;
  }
  
  if( addr == NULL ){
  	ERROR("tuple_one.get_field( mem_table , field_name, &addr), addr= NULL\n");
  	return ret;
  }
  else DEBUG("addr is %0x \n", addr);
  	
	ret = set_index_entry_key( addr ,field , index_entry );
	if( ret ){
  	ERROR("set_index_entry_key err is %d\n",ret);
  	return ret;
  }
	ret = set_index_entry_value(mem_table,  record_ptr ,index_entry );

 if( ret ){
  	ERROR("set_index_entry_value is %d\n",ret);
  	return ret;
  }
	
	DEBUG("fill_index_help end \n");
  return 0;
}


int init()
{
		
  if(NULL == mem_table )return MEMTABL_PTR_IS_NULL;
	return get_field( mem_table , field_name, field );
}



int fill_index( record_t * record_ptr,char * buf   )
{
DEBUG("fill_index() begin\n");													
int ret = 0;
if( !is_init ){
	ret = init();
	if(ret)return ret;
	is_init = !is_init;
}
DEBUG("fill_index() end\n");															
return fill_index_help(  record_ptr, buf  );
ERROR("fill_index() end\n");															
return -1;
}


// 用于online 建索引
template<class MEM_INDEX_TYPE>
int insert_into_index_scn(MEM_INDEX_TYPE * mem_index_prt, //索引指针
												record_t * record_ptr,       //对应表上的原始数据 行指针
												char * buf,
												record_t ** out_record_ptr,	
												unsigned long long Tn ,
 												unsigned long long scn  )
{
	DEBUG("insert_into_index_scn() begin\n");													

fill_index(  record_ptr,buf  );	
return  insert_index_scn( mem_index_prt, //索引指针
												 index_entry,
												field,
												 record_ptr,       //对应表上的原始数据 行指针
												 out_record_ptr,	
												 Tn ,
 												 scn  );

}

// 用于实时插入时建索引

template<class MEM_INDEX_TYPE>
int insert_into_index(MEM_INDEX_TYPE * mem_index_prt,
												record_t * record_ptr,
												char * buf,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("insert_into_index() begin\n");													
fill_index(  record_ptr,buf  );	
return insert_index(mem_index_prt, //索引指针
												 index_entry,
												field,
												 record_ptr,       //对应表上的原始数据 行指针
												 out_record_ptr,	
												 Tn  );
return 0;

}

// 用于实时删除时删索引
template<class MEM_INDEX_TYPE>
int delete_from_index(MEM_INDEX_TYPE * mem_index_prt,
												record_t * record_ptr,
												char * buf,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("delete_from_index() begin\n");													
	
fill_index(  record_ptr,buf  );	
return del_index(mem_index_prt, //索引指针
												 index_entry,
												field,
												 record_ptr,       //对应表上的原始数据 行指针
												 out_record_ptr,	
												 Tn   );
return 0;

}
// 用于实时更新时更新索引
template<class MEM_INDEX_TYPE>
int update_from_index(MEM_INDEX_TYPE * mem_index_prt,
												record_t * record_ptr,
												char * buf,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("update_from_index() begin\n");														
fill_index(  record_ptr,buf  );	
return update_index(mem_index_prt, //索引指针
												 index_entry,
												field,
												 record_ptr,       //对应表上的原始数据 行指针
												 out_record_ptr,	
												 Tn   );
return 0;

}

};




#endif