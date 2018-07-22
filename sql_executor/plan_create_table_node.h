/*
g++ -C -std=c++11 plan_create_table_node.h -w

*/
#ifndef PLAN_CREATE_TABLE_NODE
#define PLAN_CREATE_TABLE_NODE

#include "plan_node.h"
#include <memory>
\

#define PLAN_TYPE_CREATE_TABLE 								400


#include "../mem_date_index_ctl/mem_table_ctl.h"
#include "../SQL/sql_parser/CreateTableAnalyser.hpp"

inline void transform_field(field_t &field,int field_type)
{
	CPP_DEBUG<<"transform_field field_type is "<<field_type<<std::endl;
	switch(  field_type )
	{
		case T_TYPE_INTEGER:					field.field_type = FIELD_TYPE_INT;CPP_DEBUG<<"FIELD_TYPE_INT "<<std::endl;break;
  	case T_TYPE_FLOAT :						field.field_type = FIELD_TYPE_FLOAT;CPP_DEBUG<<"FIELD_TYPE_FLOAT "<<std::endl;break;
  	case T_TYPE_DOUBLE :					field.field_type = FIELD_TYPE_DOUBLE;CPP_DEBUG<<"FIELD_TYPE_DOUBLE "<<std::endl;break;
  	case T_TYPE_DECIMAL :					field.field_type = FIELD_TYPE_DOUBLE;CPP_DEBUG<<"FIELD_TYPE_DOUBLE "<<std::endl;break;
  	case T_TYPE_BOOLEAN :					field.field_type = FIELD_TYPE_SHORT;CPP_DEBUG<<"FIELD_TYPE_SHORT "<<std::endl;break;
  	case T_TYPE_DATE :					  field.field_type = FIELD_TYPE_LONG;CPP_DEBUG<<"FIELD_TYPE_LONG "<<std::endl;break;
  	case T_TYPE_TIME :break;
  	case T_TYPE_DATETIME :			  field.field_type = FIELD_TYPE_LONG;CPP_DEBUG<<"FIELD_TYPE_LONG "<<std::endl;break;
  	case T_TYPE_TIMESTAMP :break;
  	case T_TYPE_CHARACTER:				field.field_type = FIELD_TYPE_STR;CPP_DEBUG<<"FIELD_TYPE_STR "<<std::endl;break;
  	case T_TYPE_VARCHAR :					field.field_type = FIELD_TYPE_STR;CPP_DEBUG<<"FIELD_TYPE_STR "<<std::endl;break;
  	case T_TYPE_CREATETIME :break;
  	case T_TYPE_MODIFYTIME :break;
    case T_TYPE_SHORT  :          field.field_type = FIELD_TYPE_SHORT;CPP_DEBUG<<"FIELD_TYPE_SHORT "<<std::endl;break;
    case T_TYPE_INT    :          field.field_type = FIELD_TYPE_INT;CPP_DEBUG<<"FIELD_TYPE_INT "<<std::endl;break;
    case T_TYPE_LONG   :					field.field_type = FIELD_TYPE_LONG;CPP_DEBUG<<"FIELD_TYPE_LONG "<<std::endl;break;
    case T_TYPE_LONGLONG :        field.field_type = FIELD_TYPE_LONGLONG;CPP_DEBUG<<"FIELD_TYPE_LONGLONG "<<std::endl;break;
	}
	
}



int create_block(mem_block_t **mb,char * file_name,size_t block_size)
{
	DEBUG("in create_block\n");

	//������
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//���ÿ�������
	mem_block_config( *mb  ,block_size , file_name );
		//��ʼ����
	INIT_MEM_BLOCK(*mb)
	
	DEBUG("fd = %d\n",(*mb)->fd);
	return 0;
}


int create_mem_table_config(mem_table_config_t ** mem_config,mem_block_t *mb,char * table_name, 
														size_t extend_block_size, std::vector<FieldDesc>& field_vector     )
{
	DEBUG("in create_mem_table_config\n");

	*mem_config = (mem_table_config_t *) malloc(MEM_TABLE_CONFIG_SIZE);

	(*mem_config)->owner_id = 1;
	strcpy((*mem_config)->table_name,table_name);
	
	size_t num = field_vector.size();
	CPP_DEBUG<<"num is "<<num<<std::endl;
	struct field_t *fields_table  = (struct field_t *) malloc( FIELD_SIZE*num );
	(*mem_config)->fields_table      = fields_table;
	
	for(size_t i = 0 ; i<num; ++i )
	{
	transform_field(fields_table[i],field_vector[i].field_type );
	strcpy(fields_table[i].field_name,const_cast<char *>(field_vector[i].field_name.c_str() )  );
  }
  
	(*mem_config)->field_used_num   = num;
	(*mem_config)->mem_blocks_table = mb;
	(*mem_config)->mem_block_used   = 1;
	(*mem_config)->auto_extend      = 1;
	(*mem_config)->extend_block_size= extend_block_size;
	
	return 0;
}


//key func ���� ������� record_tuple
struct create_table_node:public plan_node
{
std::string table_name;                //����
std::vector<FieldDesc> field_vector ;  //�ֶ��б�
size_t 	block_size;										 //һ�����С
size_t 	extend_block_size;             //�����չ��С
std::string path;											 //·��
struct mem_table_t*                    mem_table;

create_table_node( 
							std::string& _table_name,
							std::vector<FieldDesc>& _field_vector,
							size_t 	_block_size,
							size_t 	_extend_block_size,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_name(_table_name),
		field_vector(_field_vector),
		block_size(_block_size),
		extend_block_size(_extend_block_size),
		path("./"),
		mem_table(NULL)
		
{
plan_type = PLAN_TYPE_CREATE_TABLE;	
}

void set_path( std::string _path )
{
_path = path;	
}
	
virtual int execute( unsigned long long  trans_no  )
{
// �������
mem_block_t *mb = NULL;
std::string total_path = path + table_name+".dat";

create_block( &mb,const_cast<char *>(total_path.c_str() ),block_size );
//���߼�������
mem_table_config_t * mem_config = NULL;
int err;
if(0!=(err=create_mem_table_config(&mem_config,mb,const_cast<char *>( table_name.c_str() ),extend_block_size, field_vector ) ))
{
		ERROR("create_mem_table_config err is %d\n",err);
		return err;
}


//���߼���

if(0!=(err=mem_table_create(&mem_table,mem_config)))
{
		ERROR("mem_table_create err is %d\n",err);
		return err;
}
MEM_TABLE_LOCK_INIT(&(mem_table->table_locker ));		// ԭ�������ٳ�ʼ��һ��
DEBUG("create_table node : mem_table->record_size is %d\n",mem_table->record_size );
DEBUG("RECORD_HEAD_SIZE is %d\n",RECORD_HEAD_SIZE);
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