#ifndef RECORD_DML
#define RECORD_DML
#include"../mem_date_index_ctl/mem_table_mvcc_op.h"
#include "record_tuple.h"

/*

 g++ -C -w -std=c++11 record_dml_t.h


*/


#define RECORD_PTR_IS_NULL  70000
#define MEMTABL_PTR_IS_NULL 70001

#define RECORD_KEY_INT_TYPE  70003
#define RECORD_KEY_STR_TYPE  70004

struct record_dml_t
{
mem_table_t *mem_table; // 那个表的索引
record_meta       meta;
record_tuple tuple_one;

std::vector<field_t>     field_vector;
std::vector<std::string> field_names; // 建索引的字段名
std::vector<std::string> field_values; // 建索引的字段名

generic_result return_record;

//表指针
//字段名向量
//字段值向量
//主要适用于 insert into table ( xx,xx,xx ) values (xx,xx,xx);
//和 update talbe set xx = xx, xx=xx where ;
record_dml_t( mem_table_t *_mem_table, 
							std::vector<std::string>& _field_names,
							std::vector<std::string>& _field_values):field_names(_field_names),
																											 mem_table(_mem_table),
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
	
		meta.from_table( mem_table );
		tuple_one.meta = &meta;
		tuple_one.result = &return_record;
		return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);		
		
		field_t field;
		for( size_t i = 0; i< field_names.size() ;  ++i )
		{
			tuple_one.get_field_desc( mem_table ,field_names[i], field );
		}
		field_vector.emplace_back(field);
  	
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
return mem_mvcc_insert_record( mem_table ,
                          out_record_ptr,
                          &block_no, /* in */
                          return_record.get_data(),
                          Tn        //事务ID
                          );

}

// 用于实时删除时删索引
inline int delete_one_from_table(
												record_t * in_record_ptr,	
												unsigned long long Tn  )
{
return mem_mvcc_delete_record( mem_table ,
																				in_record_ptr,
																				Tn               // 本事务ID
																				);
}
// 用于实时更新时更新索引
//主要适用于 //和 update talbe set xx = xx, xx=xx where ;
inline int update_one_from_table(
												record_t * in_record_ptr,	
												record_t ** out_record_ptr,	
												unsigned long long Tn  )
{
fill_record( );	
return mem_mvcc_update_record( mem_table ,
															in_record_ptr,
															return_record.get_data(),
															Tn,               // 本事务ID
															out_record_ptr
															);
}

};




#endif