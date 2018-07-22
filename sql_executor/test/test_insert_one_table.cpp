#include "../../SQL/sql_parser/parser.hh"
#include "../../SQL/sql_parser/queryOptimiser.hpp"
#include "../make_create_index_plan_node.h"
#include "../make_create_table_plan_node.h"
#include "../make_insert_one_table_node.h"
#include "../../SQL/sql_parser/queryOptimiser.hpp"
#include "../fun_oper.h"
#include "../make_query_plan_node.h"

/*
  g++ -g test_insert_one_table.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o main -w  -lpthread 
*/

void init_trans_redo()
{
//��ʼ�� redo_manager  
init_redo_log_manager();
//���� config_manager
//config_redo_data_log(char * path,off_t file_max_size)  

// ע���ڳ�ʼ�� ���������֮ǰ��Ҫ�ȳ�ʼ��ϵͳ���й�����
init_sys_transaction_manager();
//���� transaction_manager�� ����ֵ ��  �ع��ռ����ֵ
config_sys_transaction_manager(1,DEFAULT_FILE_MAX_SIZE);
 
//��չ�����
// extend_transaction_manager();

// ��ʼ��������־д���߳�
init_trans_redo_data_writer(&sys_trans_redo_data_writer,10);
// ���� writer �߳�д��־
start_trans_redo_data_writer();
}

void dest_trans_redo()
{
	 // �ر� writer �߳�д��־
	 stop_trans_redo_data_writer();
}


void init_mem_no_manager()
{
	init_mem_block_no_manager();
	init_mem_table_no_manager();
	init_mem_index_no_manager();
}

void dest_mem_no_manager()
{
  dest_mem_table_no_manager();
  dest_mem_index_no_manager();
	dest_mem_block_no_manager();
}

int main()
{
	init_mem_no_manager();
	//__________________________________________
	// ��ʼ���������
	init_trans_redo();
	
	
const char *sql_str = ""
"create table test_table ( id INT , name BIGINT ) TABLET_BLOCK_SIZE = 16 , EXTERN_SIZE = 4 ";     

const char *sql_str2 = ""
//"create index test_table_inx on test_table USING hash ( id ) SKIP_LEVEL = 4 ";
"create index test_table_inx on test_table (id)  SKIP_LEVEL = 4 ";

const char *sql_str3 = ""
"insert into test_table  ( id , name )  values (1,2) ";

const char *sql_str4 = ""
//"select id from  test_table  where name = 2 ";
"select id from  test_table  where id = 1 ";


//const char *sql_str2 = ""
//"create index test_table_inx on test_table ( id ) SKIP_LEVEL = 4 ";


CPP_DEBUG<< sql_str <<endl;
CPP_DEBUG<< sql_str2 <<endl;
CPP_DEBUG<< sql_str3 <<endl;
CPP_DEBUG<< sql_str4 <<endl;

ParseResult result;
int ret = parse_init(&result);
  parse_sql(&result, sql_str, strlen(sql_str));

    rapidjson::StringBuffer buffer;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer); 	
    result.Doc.Accept(writer);


 ParseResult result2;
int ret2 = parse_init(&result2);
  parse_sql(&result2, sql_str2, strlen(sql_str2));

    rapidjson::StringBuffer buffer2;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer2(buffer2); 	
    result2.Doc.Accept(writer2);
       

 ParseResult result3;
 int ret3 = parse_init(&result3);
  parse_sql(&result3, sql_str3, strlen(sql_str3));

    rapidjson::StringBuffer buffer3;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer3(buffer3); 	
    result3.Doc.Accept(writer3);       
       
 ParseResult result4;
 int ret4 = parse_init(&result4);
 parse_sql(&result4, sql_str4, strlen(sql_str4));

    rapidjson::StringBuffer buffer4;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer4(buffer4); 	
    result4.Doc.Accept(writer4);   
 
CPP_DEBUG <<"create table "<< buffer.GetString() << std::endl;
 for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_TABLE"  ){
  		CreateTableAnalyser qta( &v ,&(result.Doc) );
  		make_create_table_plan mctp(&qta);
  	  mctp.execute();
		}
  }	

CPP_DEBUG <<"create index "<< buffer2.GetString() << std::endl;
   for (auto& v : result2.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_INDEX"  ){
  		CreateIndexAnalyser qia( &v ,&(result2.Doc) );
  		make_create_index_plan mcip(&qia);
  	  mcip.execute();
		}
  }	


 CPP_DEBUG <<"insert into table "<< buffer3.GetString() << std::endl;
int err = 0;
//����һ�������
long long  trans_no;
if(0!=(err=allocate_trans(&trans_no)))DEBUG("allocate_trans[%d] failed,trans_no is %d\n",trans_no,err); 
// ��ʼһ������
if(0!=(err=start_trans(trans_no)))DEBUG("start_trans failed,trans_no is %d\n",err); 
	 
   for (auto& v : result3.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "INSERT_TABLE"  ){
  		InsertTableAnalyser ita( &v ,&(result3.Doc) );
  		make_insert_one_table_plan miot(&ita);
  	  miot.execute(trans_no);
		}
  }	
 
if(0!=(err=commit_trans(trans_no)))ERROR("commit_trans failed,trans_no is %d\n",err); 


 
//�����ѯ�ƻ�
  CPP_DEBUG <<"�Ż�ǰ json"<< buffer4.GetString() << std::endl;

 for (auto& v : result4.Doc["ROOT"]["children"].GetArray() ){
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "SELECT"  ){
  		QueryAnalyser qa( v ,result4.Doc );
  		
  		for(auto& name : qa.tables){
  			CPP_DEBUG<<"Names: "<<name.table_name_<<" "<<name.alias_name_<<" "<<name.sub_select_alias_name_<<std::endl;
  			
  		}
  		
  		//����������
  		qa.pull_up_sublinks();
  		//�����Ӳ�ѯ
  		qa.pull_up_subquerys();
  		CPP_DEBUG<<"Begin Optimiser\n "<<std::endl;

  		//�߼��Ż���
  		QueryOptimiser qo (qa);

  		CPP_DEBUG<<"�Ż�between\n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_btw,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"�Ż� in\n "<<std::endl;
	  	qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_in,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"�Ż� not \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_not,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"�Ż� const \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"�Ż� const ���ʽ\n "<<std::endl;
  		qo.optimiser_project_template( &(*(qa.project_lists))["children"] , 0 ,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"�Ż� const ����\n "<<std::endl;
		  qo.optimiser_project_template( (qa.where_list) ,0,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
    //�Ż���
  		CPP_DEBUG <<"�Ż��� json\n";
  		rapidjson_log( &result4.Doc["ROOT"] );
    
	 //std::vector<fun_oper *>  projection_fun_oper_lists ;
   //esolve_to_opper_node(   &qa ,  projection_fun_oper_lists	);
		  CPP_DEBUG<<"��������ִ�мƻ�\n "<<std::endl;
		  physical_query_plan phplan( &qa );
		 
				CPP_DEBUG<<"ִ��SQL\n "<<std::endl;
				//����һ�������
				long long  trans_no2;
				if(0!=(err=allocate_trans(&trans_no2)))DEBUG("allocate_trans[%d] failed,trans_no2 is %d\n",trans_no2,err); 
				// ��ʼһ������
				if(0!=(err=start_trans(trans_no2)))DEBUG("start_trans failed,trans_no2 is %d\n",err); 
				err = phplan.execute(trans_no2);
				if(err) //�ع�
					{
						if(0!=(err=rollback_trans(trans_no2)))ERROR("rollback_trans failed,trans_no2 is %d\n",err);
					}
				else{//�ύ
					if(0!=(err=commit_trans(trans_no2)))ERROR("commit_trans failed,trans_no2 is %d\n",err); 		  

				}
		
		}
  }	
  
  		
  
parse_terminate(&result);
parse_terminate(&result2);
parse_terminate(&result3);

//���������
dest_trans_redo();
dest_mem_no_manager();

return 0;
}
