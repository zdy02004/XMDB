/*
g++ -C -std=c++11 plan_create_skiplist_index_node.h -w

*/
#ifndef PLAN_CREATE_SKIPLIST_INDEX_NODE
#define PLAN_CREATE_SKIPLIST_INDEX_NODE

#include "plan_node.h"
#include "../mem_date_index_ctl/mem_skiplist_index.h"
#include "../SQL/sql_parser/CreateIndexAnalyser.hpp"
#include "create_index_online.h"

#define PLAN_TYPE_CREATE_SKIPLIST_INDEX 								700
#define CREATE_SKIPLIST_INDEX_NO_FIELD 								  701
#define CREATE_SKIPLIST_INDEX_WRONG_FIELD						    703


int create_mem_skiplist_config(mem_skiplist_index_config_t** skiplist_config,
															unsigned  long long heap_block_size,
															char *index_name,
															int skip_level)
{
	*skiplist_config =(mem_skiplist_index_config_t *)malloc(MEM_SKIPLIST_CONFIG_SIZE);
	(*skiplist_config)->index_no			  = 1;
	(*skiplist_config)->owner_table_no  = 1;
	strcpy((*skiplist_config)->index_name,index_name);
	(*skiplist_config)->heap_block_size = heap_block_size;
	(*skiplist_config)->max_level = skip_level;
	
	return 0;
}


//key func ���� ������� record_tuple
struct create_skiplist_index_node:public plan_node
{
std::string table_name;                //����
std::string index_name;                //����
std::vector<std::string> field_vector ;  //�ֶ��б�
size_t 	block_size;										 //һ�����С
size_t 	extend_block_size;             //�����չ��С
std::string path;											 //·��
struct mem_table_t*                    mem_table;   //��ָ��
mem_skiplist_index_t	*                mem_skiplist_index; //skiplist ����ָ��
int index_type;												// index ����
int skip_level;														//�������,Ĭ��4��

create_skiplist_index_node( 
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
		index_type(INDEX_TYPE_SKIP),
		mem_table(NULL),
		mem_skiplist_index(NULL),skip_level(4)
		
{
plan_type = PLAN_TYPE_CREATE_SKIPLIST_INDEX;	
}

create_skiplist_index_node( 
							std::string& _table_name,
							std::string& _index_name,
							std::vector<std::string>& _field_vector,
							size_t 	_block_size,
							size_t 	_extend_block_size,
							int _skip_level,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_name(_table_name),
		index_name(_index_name),
		field_vector(_field_vector),
		block_size(_block_size),
		extend_block_size(_extend_block_size),
		path("./"),
		index_type(INDEX_TYPE_SKIP),
		mem_table(NULL),
		mem_skiplist_index(NULL),skip_level(_skip_level)
		
{
plan_type = PLAN_TYPE_CREATE_SKIPLIST_INDEX;	
}

create_skiplist_index_node( 
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
		index_type(INDEX_TYPE_SKIP),
		mem_table(NULL),
		mem_skiplist_index(NULL),skip_level(4)
{
plan_type = PLAN_TYPE_CREATE_SKIPLIST_INDEX;	
}



void set_path( std::string _path )
{
_path = path;	
}

int get_table_ptr()
{
	int err = 0;
	// ����ԭʼ����ñ��Ƿ����
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
	
//���ñ����Ƿ����ĳ���ֶ�,���ڱ���ֶ��ϱ������id
int check_field()
{
	if(!field_vector.empty() && mem_table != NULL && mem_skiplist_index != NULL ){
		CPP_DEBUG<<"mem_table_lock "<<" \n";
		mem_table_lock( &( mem_table->table_locker ) );
		for( auto &v : field_vector )
		{
			if( !has_field( mem_table , v ) ){
					CPP_ERROR<<"The Field "<<v<<" Not Exists in Table "<<table_name<<" \n";
					CPP_DEBUG<<"mem_table_unlock "<<" \n";		
 	       	mem_table_unlock( &( mem_table->table_locker ) );
				  return CREATE_SKIPLIST_INDEX_WRONG_FIELD;
				}
				else { // ����������
					 for(int i = 0;i < mem_table->config.field_used_num; ++i  )
 						{
 								field_t& field = mem_table->config.fields_table[i];
 							  if (0 == strcmp(field.field_name,v.c_str()) ){
 							  	
 							  	for(int j = 0; j< MAX_FIELD_INDEX_NO; ++j )
 							  	{
 							  		if(field.relate_index[j]==0 ){
 							  		field.index_type[j] = index_type;
 							  		field.relate_index[j] = mem_skiplist_index->config.index_no; 
 							  		break; 
 							  	  }
 							    }
 							  }
 						}
				}
		}
	CPP_DEBUG<<"mem_table_unlock "<<" \n";		
 	mem_table_unlock( &( mem_table->table_locker ) );
	}
	else {
				CPP_ERROR<<"Field Empty !\n";
				return CREATE_SKIPLIST_INDEX_NO_FIELD;
			}
	return 0;
}
	
virtual int execute( unsigned long long  trans_no  )
{
//  ��ñ�ָ��
int err = get_table_ptr();
if( err )return err;
	
if( path !="./")index_name = path + index_name;

//�� skiplist ��������
mem_skiplist_index_config_t * skiplist_config		= NULL;
//�� skiplist ������Ϣ
if(0!=(err=create_mem_skiplist_config(&skiplist_config, block_size, const_cast<char *>(index_name.c_str())  ,skip_level ) ) )
{
	ERROR("mem_skiplist_index_create err is %d\n",err);
	return err;
}
	
//�� skiplist ����
if(0!=(err=mem_skiplist_create(&mem_skiplist_index,mem_table,skiplist_config)))
	{
		ERROR("mem_skiplist_index_create err is %d\n",err);
		return err;
	}

//���ʧ�ܣ��ع�Ԫ����
if( check_field() )
{
	if(0!=(err=mem_skiplist_index_close(mem_skiplist_index)))
		{
			DEBUG("mem_skiplist_index_close err is %d\n",err);
			return err;
		}
  
}	


//  Ŀǰֻ֧�ֵ���������
if( 0 < field_vector.size() ){
	
	for( auto &v : field_vector  )
	{
	 online_create_index<mem_skiplist_entry_t> online_create_indexer( mem_table , v , index_type );
	 err = online_create_indexer.execute(  mem_skiplist_index );
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