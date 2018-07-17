/*
g++ -C -std=c++11 plan_insert_one_table_node.h -w

*/
#ifndef PLAN_	INSERT_ONE_TABLE_NODE
#define PLAN_	INSERT_ONE_TABLE_NODE

#include "plan_node.h"
#include "../SQL/sql_parser/InsertTableAnalyser.hpp"
#include "record_dml_t.h"

#define PLAN_TYPE_INSERT_ONE_TABLE   								800
#define PLAN_INSERT_TABLE_NO_FIELD 								  801
#define PLAN_INSERT_TABLE_WRONG_FIELD						    803
#define PLAN_INSERT_TABLE_INPUT_NUM_NOT_EQA         804


//key func ���� ������� record_tuple
struct plan_insert_one_table_node:public plan_node
{
std::string table_name;                 //����
std::vector<std::string> field_vector ; //�ֶ������б�
std::vector<std::string> value_vector ; //�ֶ�ֵ�б�
struct mem_table_t*      mem_table;     //��ָ��
record_dml_t						 record_dml;		//record_dml ������


plan_insert_one_table_node( 
							std::string& _table_name,
							std::vector<std::string>& _field_vector,
							std::vector<std::string>& _value_vector,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_name(_table_name),
		field_vector(_field_vector),
		value_vector(_value_vector),
		record_dml( _field_vector , _value_vector ),
		mem_table(NULL)
{
plan_type = PLAN_TYPE_INSERT_ONE_TABLE;	
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
					 		if( mem_table &&  !err ) {
					 			record_dml.mem_table = mem_table;
					 			record_dml.init();
					 		}
					 		else
					 			{
					 				CPP_ERROR<<"Get mem_table ptr failed!\n";
					        return err;
					 			}
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
	// �������ֲ�Ϊ��
	if(!field_vector.empty() && mem_table != NULL  ){
		for( auto &v : field_vector )
		{
			if( !has_field( mem_table , v ) ){
					CPP_ERROR<<"The Field "<<v<<" Not Exists in Table "<<table_name<<" \n";
				  return PLAN_INSERT_TABLE_WRONG_FIELD;
				}
		}
		 
		if( field_vector.size() != value_vector.size()  )
		{
			CPP_ERROR<<"Value list num != field list num"<<std::endl;
			return PLAN_INSERT_TABLE_INPUT_NUM_NOT_EQA;
		}
	}
		// ��������Ϊ��
	else if( field_vector.empty() && mem_table != NULL  ){
		 for(int i = 0;i < mem_table->config.field_used_num; ++i  )
		 {
		    field_t& field = mem_table->config.fields_table[i];
		 	  field_vector.emplace_back( std::string(field.field_name ) ); 
		 }
		 if( field_vector.size() !=value_vector.size()  )
		 	{
		 		CPP_ERROR<<"Value list num != field list num"<<std::endl;
		 		return PLAN_INSERT_TABLE_INPUT_NUM_NOT_EQA;
		 	}
		 
		}
	else {
			  if(mem_table == NULL)CPP_ERROR<<"In INSERT TABLE, Table ptr is Empty !\n";
				return PLAN_INSERT_TABLE_NO_FIELD;
			}
	return 0;
}
	
virtual int execute( unsigned long long  Tn  )
{
//  ��ñ�ָ��
int err = get_table_ptr();
if( err )return err;
record_t * out_record_ptr = NULL;
//���ʧ�ܣ��ع�Ԫ����
if( err = check_field() )
{
			ERROR("check_field failed\n");
			return err; 
}	

err = record_dml.insert_one_into_table(
												&out_record_ptr,	
												Tn  );

if(err)
	{
		ERROR("insert_one_into_table err is %d\n",err);
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