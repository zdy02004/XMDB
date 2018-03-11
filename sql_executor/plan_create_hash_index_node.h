/*
g++ -C -std=c++11 plan_create_hash_index_node.h -w

*/
#ifndef PLAN_CREATE_HASH_INDEX_NODE
#define PLAN_CREATE_HASH_INDEX_NODE

#include "plan_node.h"
#include "../mem_date_index_ctl/mem_hash_index.h"
#include "../SQL/sql_parser/CreateIndexAnalyser.hpp"
#include "create_index_online.h"

#define PLAN_TYPE_CREATE_HASH_INDEX 								600
#define CREATE_HASH_INDEX_NO_FIELD 								  601
#define CREATE_HASH_INDEX_WRONG_FIELD						    603


int create_mem_hash_config(		mem_hash_index_config_t** hash_config ,
															unsigned  long long array_block_size  ,
															unsigned  long long link_block_size ,
															int                 div               ,
															char *index_name										)
{
	(*hash_config) =(mem_hash_index_config_t *)malloc(MEM_HASH_CONFIG_SIZE);
	//(*hash_config)->index_no			 	 = 1;
	(*hash_config)->owner_table_no 	 = 1;
	strcpy((*hash_config)->index_name,index_name);
	(*hash_config)->array_block_size = array_block_size;
	(*hash_config)->link_block_size  = link_block_size ;
	(*hash_config)->div              = div;
	return 0;
}


//key func 构造 结果集的 record_tuple
struct create_hash_index_node:public plan_node
{
std::string table_name;                //表名
std::string index_name;                //表名
std::vector<std::string> field_vector ;  //字段列表
size_t 	block_size;										 //一个块大小
size_t 	extend_block_size;             //块的扩展大小
std::string path;											 //路径
struct mem_table_t*                    mem_table;   //表指针
mem_hash_index_t	*                    mem_hash_index; //HASH 索引指针
int index_type;												// index 类型
int div;
create_hash_index_node( 
							std::string& _table_name,
							std::string& _index_name,
							std::vector<std::string>& _field_vector,
							size_t 	_block_size,
							size_t 	_extend_block_size,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_name(_table_name),
		index_name(_index_name),
		field_vector(_field_vector),
		block_size(_block_size),
		extend_block_size(_extend_block_size),
		path("./"),
		index_type(INDEX_TYPE_HASH),
		mem_table(NULL),
		mem_hash_index(NULL),
		div(3)
		
{
plan_type = PLAN_TYPE_CREATE_HASH_INDEX;	
}

create_hash_index_node( 
							std::string& _table_name,
							std::string& _index_name,
							std::vector<std::string>& _field_vector,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_name(_table_name),
		index_name(_index_name),
		field_vector(_field_vector),
		block_size(0),
		extend_block_size(0),
		path("./"),
		index_type(INDEX_TYPE_HASH),
		mem_table(NULL),
		mem_hash_index(NULL),
		div(3)
{
plan_type = PLAN_TYPE_CREATE_HASH_INDEX;	
}

void set_div(int _div)
{
	if( _div!=0 )	div = _div;
}

void set_path( std::string _path )
{
_path = path;	
}

int get_table_ptr()
{
	int err = 0;
	// 对于原始表检查该表是否存在
				if(!table_name.empty()){
					long long table_no;
					 err = search_table_name( const_cast<char *>(table_name.c_str()) , &table_no);
					
					 if( 0 == err){
					 	 err = get_table_no_addr(table_no,(void **)(&mem_table));
					 	 //if( 0 == err){
					 	 //	if( has_field( mem_table ,column_name ) ){
					 	 //		++field_num;
					 	 //		relation_name = std::string(mem_table->config.table_name);
					 	 //	}
					 		//}
					 }
					 
				}
				else {
					CPP_ERROR<<"Get table name failed!\n";
					return err;
				}
	return err;
}
	
//检查该表中是否存在某个字段,并在表的字段上标记索引id
int check_field()
{
	if(!field_vector.empty() && mem_table != NULL && mem_hash_index != NULL ){
		for( auto &v : field_vector )
		{
			if( !has_field( mem_table , v ) ){
					CPP_ERROR<<"The Field "<<v<<" Not Exists in Table "<<table_name<<" \n";
				  return CREATE_HASH_INDEX_WRONG_FIELD;
				}
				else { // 添加索引标记
					mem_table_lock( &( mem_table->table_locker ) );
					 for(int i = 0;i < mem_table->config.field_used_num; ++i  )
 						{
 								field_t& field = mem_table->config.fields_table[i];
 							  if (0 == strcmp(field.field_name,v.c_str()) ){
 							  	
 							  	for(int j = 0; j< 8; ++j )
 							  	{
 							  		if(field.relate_index[j]!=0 ){
 							  		field.index_type[j] = index_type;
 							  		field.relate_index[j] = mem_hash_index->config.index_no;  
 							  	  }
 							    }
 							  }
 						}
 				 mem_table_unlock( &( mem_table->table_locker ) );

				}
		}
	}
	else {
				if(!field_vector.empty() )CPP_ERROR<<"In Create Index Statment, Fields is Empty !\n";
				else if(mem_table == NULL)CPP_ERROR<<"In Create Index, Table ptr is Empty !\n";
				else if(mem_hash_index == NULL)CPP_ERROR<<"In Create Index, Index ptr is Empty !\n";
				return CREATE_HASH_INDEX_NO_FIELD;
			}
	return 0;
}
	
virtual int execute( unsigned long long  trans_no  )
{
//  获得表指针
int err = get_table_ptr();
if( err )return err;
	
if( path !="./")index_name = path + index_name;

//建 hash 索引配置
mem_hash_index_config_t * hash_config		= NULL;
//建 hash 配置信息
if(0!=(err=create_mem_hash_config(&hash_config, block_size ,extend_block_size , div , const_cast<char *>(index_name.c_str()) )))
{
	ERROR("mem_hash_index_create err is %d\n",err);
	return err;
}
	
//建 hash 索引
if(0!=(err=mem_hash_index_create(&mem_hash_index,mem_table,hash_config)))
	{
		ERROR("mem_hash_index_create err is %d\n",err);
		return err;
	}

//检查失败，回滚元数据
if( check_field() )
{
	if(0!=(err=mem_hash_index_close(mem_hash_index)))
		{
			DEBUG("mem_hash_index_close err is %d\n",err);
			return err;
		}
  
}	

//  目前只支持单读建索引
if( 0 < field_vector.size() ){
	
	for( auto &v : field_vector  )
	{
	 online_create_index<mem_hash_entry_t> online_create_indexer( mem_table , v , index_type );
	 err = online_create_indexer.execute(  mem_hash_index );
	}
}
else
	{
	  ERROR("has no filed name to create index on \n");		
	}
if(err)
	{
		ERROR("online_create_index err is %d\n",err);
		return err;
		
	}

return 0;

}


virtual std::list<generic_result>* get_ret_list()
{
  
	return NULL;
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
