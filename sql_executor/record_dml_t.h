#ifndef RECORD_DML
#define RECORD_DML
#include"../mem_date_index_ctl/mem_table_mvcc_op.h"
#include "record_tuple.h"
#include "index_dml_t.h"

/*
 g++ -C -w -lpthread  -std=c++11 record_dml_t.h 
*/


#define RECORD_PTR_IS_NULL  70000
#define MEMTABL_PTR_IS_NULL 70001

#define RECORD_KEY_INT_TYPE  70003
#define RECORD_KEY_STR_TYPE  70004

struct index_selector_t
{
	std::vector< index_dml_t<mem_hash_entry_t>     > hash_index_dml_vector;
	std::vector< mem_hash_index_t *                > hash_index_vector;
  std::vector< index_dml_t<mem_skiplist_entry_t> > skiplist_index_dml_vector;
  std::vector< mem_skiplist_index_t *            > skiplist_index_vector;
  	
  int insert_index_dml(int index_type, void * addr,mem_table_t *mem_table, std::string& field_name )
  {	
  	DEBUG("insert_index_dml() begin \n");			
		switch(index_type)
		{
			case INDEX_TYPE_HASH :{
			DEBUG("case INDEX_TYPE_HASH \n");		
			hash_index_dml_vector.emplace_back(mem_table,field_name,index_type);
			hash_index_vector.emplace_back( (mem_hash_index_t *)addr);
			DEBUG("emplace_back INDEX_TYPE_HASH  config!\n");		
			break;
			}
		  case INDEX_TYPE_SKIP :{
		  DEBUG("INDEX_TYPE_SKIP \n");			
			skiplist_index_dml_vector.emplace_back(mem_table,field_name,index_type);
			skiplist_index_vector.emplace_back( (mem_skiplist_index_t *)addr);
			DEBUG("emplace_back INDEX_TYPE_SKIP  config!\n");		
			break;
			}
							
		}
		DEBUG("insert_index_dml() end \n");			
  	return 0;
  }
  
int insert_into_index(
												record_t * record_ptr,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
	DEBUG("insert_into_index begin\n");
	int ret = 0;
	for(size_t i = 0 ; i< hash_index_dml_vector.size();++i){
		
		DEBUG("hash_index_dml_vector[%d].insert_into_index\n",i);
		ret = hash_index_dml_vector[i].insert_into_index(
																							hash_index_vector[i],
																							record_ptr,
																							(char *)record_ptr + RECORD_HEAD_SIZE,
																							out_record_ptr,
																							Tn);
			if(ret)return ret;
	}
	for(size_t i = 0 ; i< skiplist_index_dml_vector.size();++i){
		DEBUG("skiplist_index_dml_vector[%d].insert_into_index\n",i);
		ret = skiplist_index_dml_vector[i].insert_into_index(
																							skiplist_index_vector[i],
																							record_ptr,
																							(char *)record_ptr + RECORD_HEAD_SIZE,
																							out_record_ptr,
																							Tn);
		if(ret)return ret;
	}
		DEBUG("insert_into_index end\n");
		return 0;

}


int delete_from_index(
												record_t * record_ptr,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
	{
		int ret = 0;
		for(size_t i = 0 ; i< hash_index_dml_vector.size();++i){
			ret = hash_index_dml_vector[i].delete_from_index(
																								hash_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
				if(ret)return ret;
		}
		for(size_t i = 0 ; i< skiplist_index_dml_vector.size();++i){
			ret = skiplist_index_dml_vector[i].delete_from_index(
																								skiplist_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
			if(ret)return ret;
		}
		
	}
	
	
int update_from_index(
												record_t * record_ptr,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
	{
		int ret = 0;
		for(size_t i = 0 ; i< hash_index_dml_vector.size();++i){
			ret = hash_index_dml_vector[i].update_from_index(
																								hash_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
				if(ret)return ret;
		}
		for(size_t i = 0 ; i< skiplist_index_dml_vector.size();++i){
			ret = skiplist_index_dml_vector[i].update_from_index(
																								skiplist_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
			if(ret)return ret;
		}
		
	}
};


struct record_dml_t
{
mem_table_t *mem_table; // 那个表的索引
record_meta       meta;
record_tuple tuple_one;

std::vector<field_t>     field_vector;
std::vector<std::string> field_names; // 建索引的字段名
std::vector<std::string> field_values; // 建索引的字段名

generic_result return_record;
index_selector_t index_selector;
bool has_index; 
 
//表指针
//字段名向量
//字段值向量
//主要适用于 insert into table ( xx,xx,xx ) values (xx,xx,xx);
//和 update talbe set xx = xx, xx=xx where ;
record_dml_t( mem_table_t *_mem_table, 
							std::vector<std::string>& _field_names,
							std::vector<std::string>& _field_values):field_names(_field_names),
																											 mem_table(_mem_table),
																											 field_values(_field_values),
																											 has_index(0)
{
		//init();  	
}

record_dml_t(
							std::vector<std::string>& _field_names,
							std::vector<std::string>& _field_values):field_names(_field_names),
																											 field_values(_field_values)
{
		//init();  	
}

inline void set_mem_table( mem_table_t *_mem_table)
																											 
{
		mem_table = _mem_table;
}

inline void change_value(std::vector<std::string>& _field_values)
																											 
{
		field_values = _field_values;
}


record_dml_t( mem_table_t *_mem_table):mem_table(_mem_table)
{
		init();  	
}

inline void init()
{	
	  DEBUG("init() begin\n");
	  int ret = 0 ;
	  if(  NULL != mem_table ){
	  DEBUG(" if(  NULL != mem_table )\n");	
	  DEBUG(" field_names.size() = %d \n",field_names.size() );	
	  
		meta.from_table( mem_table );
		tuple_one.meta = &meta;
		tuple_one.result = &return_record;
		return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);		
		
		field_t field;
		mem_table_lock( &( mem_table->table_locker ) );// 确保 create_index_online 不漏数据
		for( size_t i = 0; i< field_names.size() ;  ++i )
		{
			DEBUG(" for( size_t i = %d )\n",i);	
			tuple_one.get_field_desc( mem_table ,field_names[i], field );//获取字段描述
			field_vector.emplace_back(field);
			if( field.relate_index[0] != 0 ){	//有索引就建立索引操纵类
			  DEBUG("has_index = true;	\n");
				has_index = true;			                 
				long relate_index = 0;           
				int  index_type = 0;				
				for( int j = 0 ; j< MAX_FIELD_INDEX_NO ; ++j )
				{
					relate_index = field.relate_index[j];
					if( 0 !=relate_index )
					{
						  DEBUG("Find index %d and then insert into config!\n",relate_index);
							index_type   = field.index_type[j];					
							void * addr = NULL;
							ret = get_index_no_addr( relate_index , &addr );
							if(ret)
								{
									ERROR("get_index_no_addr err is %d\n",ret);
									return ;
								}
								else DEBUG("index_addr is %0x \n",addr );
							
							if( addr != NULL && ret == 0 ){
							  DEBUG("index_selector.insert_index_dml()	\n");
								index_selector.insert_index_dml( index_type , addr,mem_table , field_names[i]  );
							}
					}
				}
			}
			else  DEBUG("has_index = false;	\n");
		}
		mem_table_unlock( &( mem_table->table_locker ) );// 确保 create_index_online 不漏数据
  	
  	}
DEBUG("init() end\n");

}

// 把值填充入 tuple 中
inline int fill_record( )
{
	DEBUG("fill_record() begin\n");													
	int ret = 0;
  char * addr = NULL;  
	for( size_t i = 0; i< field_names.size() ;  ++i )
  { 
  	int temp = 1;
  	DEBUG(" field_values = %d \n",*((int *)cast_ptr_by_field( field_values[i] , field_vector[i] )) );
  	//ret = tuple_one.set_field( mem_table,field_names[i] , (char *)cast_ptr_by_field( field_values[i] , field_vector[i] ) );
  	ret = tuple_one.set_field( mem_table,field_names[i] , cast_ptr_by_field_to_string( field_values[i] , field_vector[i] ).c_str() );
		
		//ret = tuple_one.set_field( mem_table,field_names[i] , (char *)(&temp) );

		if( ret )
	  {
	    ERROR("tuple_one.set_field err is %d \n",ret);
		  return ret;
	  }
  
  }
  DEBUG("fill_record() end\n");													
  return 0;
}

// 用于实时插入时建索引
//主要适用于 insert into table ( xx,xx,xx ) values (xx,xx,xx);
inline int insert_one_into_table(
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("insert_one_into_table() begin\n");	
fill_record();	
long block_no;
int ret  = 0;
int ret1 = 0;
record_t * out_index_record_ptr = NULL;

CPP_DEBUG<<"mem_table->record_size - RECORD_HEAD_SIZE is "<<mem_table->record_size - RECORD_HEAD_SIZE<<std::endl;


ret = mem_mvcc_insert_record( mem_table ,
                          out_record_ptr,
                          &block_no, /* in */
                          return_record.get_data(),
                          Tn        //事务ID
                          );
DEBUG("mem_mvcc_insert_record() ok\n");	                          
if(ret )
{
	ERROR("mem_mvcc_insert_record err is %d \n",ret);
	return ret;
	
}


//DEBUG( "INSERT VALUE is %d \n" , *((int*)(*out_record_ptr)->data) );

if(has_index)
	{
		DEBUG(" Has index! index_selector.insert_into_index()  \n");		 
		ret = index_selector.insert_into_index(
												*out_record_ptr,
												&out_index_record_ptr,	
												Tn  );
	}
	else DEBUG("Do not has index!  \n");	 	
													
DEBUG("insert_one_into_table() end\n");													
return ret;


}

// 用于实时删除时删索引
inline int delete_one_from_table(
												record_t * in_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("delete_one_from_table() begin\n");													

int ret = 0;
int ret1 = 0;
record_t * out_index_record_ptr = NULL;
ret =  mem_mvcc_delete_record( mem_table ,
																				in_record_ptr,
																				Tn               // 本事务ID
																				);
if(ret )
{
	ERROR("mem_mvcc_delete_record err is %d \n",ret);
	return ret;
}
if(has_index)ret = index_selector.delete_from_index(
												in_record_ptr,
												&out_index_record_ptr,	
												Tn  );
												
DEBUG("delete_one_from_table() end\n");													
return ret;
}
// 用于实时更新时更新索引
//主要适用于 //和 update talbe set xx = xx, xx=xx where ;
inline int update_one_from_table(
												record_t * in_record_ptr,	
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
DEBUG("update_one_from_table() begin\n");													
int ret = 0;
int ret1 = 0;
ret = fill_record( );	
if(ret )
{
	ERROR("fill_record( ) err is %d \n",ret);
	return ret;
}
record_t * out_index_record_ptr = NULL;
ret =  mem_mvcc_update_record( mem_table ,
															in_record_ptr,
															return_record.get_data(),
															Tn,               // 本事务ID
															out_record_ptr
															);
if(ret )
{
	ERROR("update_one_from_table err is %d \n",ret);
	return ret;
}
if(has_index)ret = index_selector.update_from_index(
												*out_record_ptr,
												&out_index_record_ptr,	
												Tn  );
DEBUG("update_one_from_table() end\n");													
return ret;
}

};




#endif