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
		switch(index_type)
		{
			case INDEX_TYPE_HASH :{
			hash_index_dml_vector.emplace_back(mem_table,field_name,index_type);
			hash_index_vector.emplace_back( (mem_hash_index_t *)addr);
			}
		  case INDEX_TYPE_SKIP :{
			skiplist_index_dml_vector.emplace_back(mem_table,field_name,index_type);
			skiplist_index_vector.emplace_back( (mem_skiplist_index_t *)addr);
			}
							
		}
  	return 0;
  }
  
int insert_into_index(
												record_t * record_ptr,
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
	{
		int ret = 0;
		for(size_t i = 0 ; i< hash_index_dml_vector.size();++i){
			ret = hash_index_dml_vector[i].insert_into_index(
																								hash_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
				if(ret)return ret;
		}
		for(size_t i = 0 ; i< skiplist_index_dml_vector.size();++i){
			ret = skiplist_index_dml_vector[i].insert_into_index(
																								skiplist_index_vector[i],
																								record_ptr,
																								(char *)record_ptr + RECORD_HEAD_SIZE,
																								out_record_ptr,
																								Tn);
			if(ret)return ret;
		}
		
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
		init();  	
}

record_dml_t(
							std::vector<std::string>& _field_names,
							std::vector<std::string>& _field_values):field_names(_field_names),
																											 field_values(_field_values)
{
		init();  	
}

record_dml_t( mem_table_t *_mem_table):mem_table(_mem_table)
{
		init();  	
}

inline void init()
{	
	  int ret = 0 ;
		meta.from_table( mem_table );
		tuple_one.meta = &meta;
		tuple_one.result = &return_record;
		return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);		
		
		field_t field;
		mem_table_lock( &( mem_table->table_locker ) );// 确保 create_index_online 不漏数据
		for( size_t i = 0; i< field_names.size() ;  ++i )
		{
			tuple_one.get_field_desc( mem_table ,field_names[i], field );//获取字段描述
			field_vector.emplace_back(field);
			if( field.relate_index[0] != 0 ){	//有索引就建立索引操纵类
				has_index = true;			                 
				long relate_index = 0;           
				int  index_type = 0;				
				for( int j = 0 ; j< MAX_FIELD_INDEX_NO ; ++j )
				{
					relate_index = field.relate_index[j];
					index_type   = field.index_type[j];
					
					void * addr = NULL;
					ret = get_index_no_addr( relate_index , &addr );
					
					if( addr != NULL && ret == 0 ){
						index_selector.insert_index_dml( index_type , addr,mem_table , field_names[i]  );
					}
				}
			}
		}
		mem_table_unlock( &( mem_table->table_locker ) );// 确保 create_index_online 不漏数据
  	
  	
}

// 把值填充入 tuple 中
inline int fill_record( )
{
	int ret = 0;
  char * addr = NULL;  
	for( size_t i = 0; i< field_names.size() ;  ++i )
  {
  ret = tuple_one.set_field( field_names[i] , (char *)cast_ptr_by_field( field_values[i] , field_vector[i] ) );
  if( ret )return ret;
  
  }
  
  return 0;
}

// 用于实时插入时建索引
//主要适用于 insert into table ( xx,xx,xx ) values (xx,xx,xx);
inline int insert_one_into_table(
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
fill_record();	
long block_no;
int ret  = 0;
int ret1 = 0;
record_t * out_index_record_ptr = NULL;
ret = mem_mvcc_insert_record( mem_table ,
                          out_record_ptr,
                          &block_no, /* in */
                          return_record.get_data(),
                          Tn        //事务ID
                          );
if(ret )return ret;
if(has_index)ret = index_selector.insert_into_index(
												*out_record_ptr,
												&out_index_record_ptr,	
												Tn  );
return ret;


}

// 用于实时删除时删索引
inline int delete_one_from_table(
												record_t * in_record_ptr,	
												unsigned long long Tn  )
{
int ret = 0;
int ret1 = 0;
record_t * out_index_record_ptr = NULL;
ret =  mem_mvcc_delete_record( mem_table ,
																				in_record_ptr,
																				Tn               // 本事务ID
																				);
if(ret )return ret;
if(has_index)ret = index_selector.delete_from_index(
												in_record_ptr,
												&out_index_record_ptr,	
												Tn  );
return ret;
}
// 用于实时更新时更新索引
//主要适用于 //和 update talbe set xx = xx, xx=xx where ;
inline int update_one_from_table(
												record_t * in_record_ptr,	
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
fill_record( );	
int ret = 0;
int ret1 = 0;
record_t * out_index_record_ptr = NULL;
ret =  mem_mvcc_update_record( mem_table ,
															in_record_ptr,
															return_record.get_data(),
															Tn,               // 本事务ID
															out_record_ptr
															);
if(ret )return ret;
if(has_index)ret = index_selector.update_from_index(
												*out_record_ptr,
												&out_index_record_ptr,	
												Tn  );
return ret;
}

};




#endif
