#include "../../SQL/sql_parser/parser.hh"
#include "../../SQL/sql_parser/queryOptimiser.hpp"
#include "../make_create_index_plan_node.h"
#include "../make_create_table_plan_node.h"
#include "../make_insert_one_table_node.h"


/*
  g++ -g test_insert_one_table.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o main -w  -lpthread 
*/

void init_trans_redo()
{
//初始化 redo_manager  
init_redo_log_manager();
//配置 config_manager
//config_redo_data_log(char * path,off_t file_max_size)  

// 注意在初始化 事务管理器之前，要先初始化系统序列管理器
init_sys_transaction_manager();
//配置 transaction_manager的 序列值 和  回滚空间最大值
config_sys_transaction_manager(1,DEFAULT_FILE_MAX_SIZE);
 
//扩展事务槽
// extend_transaction_manager();

// 初始化数据日志写者线程
init_trans_redo_data_writer(&sys_trans_redo_data_writer,10);
// 开启 writer 线程写日志
start_trans_redo_data_writer();
}

void dest_trans_redo()
{
	 // 关闭 writer 线程写日志
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
	// 初始化事务相关
	init_trans_redo();
	
	
const char *sql_str = ""
"create table test_table ( id INT , name BIGINT ) TABLET_BLOCK_SIZE = 16 , EXTERN_SIZE = 4 ";     

const char *sql_str2 = ""
"create index test_table_inx on test_table USING hash ( id ) SKIP_LEVEL = 4 ";

const char *sql_str3 = ""
"insert into test_table  ( id , name )  values (1,2) ";

//const char *sql_str2 = ""
//"create index test_table_inx on test_table ( id ) SKIP_LEVEL = 4 ";


CPP_DEBUG<< sql_str <<endl;
 CPP_DEBUG<< sql_str2 <<endl;
  CPP_DEBUG<< sql_str3 <<endl;

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
       
 
//优化前
  CPP_DEBUG <<"create table "<< buffer.GetString() << std::endl;
  

 for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_TABLE"  ){
  		CreateTableAnalyser qta( &v ,&(result.Doc) );
  		make_create_table_plan mctp(&qta);
  	  mctp.execute();
		}
  }	
  	//优化前
  CPP_DEBUG <<"create index "<< buffer2.GetString() << std::endl;
   for (auto& v : result2.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_INDEX"  ){
  		CreateIndexAnalyser qia( &v ,&(result2.Doc) );
  		make_create_index_plan mcip(&qia);
  	  mcip.execute();
		}
  }	



int err = 0;
//分配一个事务槽
long long  trans_no;
if(0!=(err=allocate_trans(&trans_no)))DEBUG("allocate_trans[%d] failed,trans_no is %d\n",trans_no,err); 
// 开始一个事务
if(0!=(err=start_trans(trans_no)))DEBUG("start_trans failed,trans_no is %d\n",err); 
	 
    	//优化前
  CPP_DEBUG <<"insert into table "<< buffer3.GetString() << std::endl;
   for (auto& v : result3.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "INSERT_TABLE"  ){
  		InsertTableAnalyser ita( &v ,&(result3.Doc) );
  		make_insert_one_table_plan miot(&ita);
  	  miot.execute(trans_no);
		}
  }	
 
if(0!=(err=commit_trans(trans_no)))ERROR("commit_trans failed,trans_no is %d\n",err); 

  
  //优化后
  //CPP_DEBUG <<"优化后 json\n";
  //rapidjson_log( &result.Doc["ROOT"] );
  
   
  
parse_terminate(&result);
parse_terminate(&result2);
parse_terminate(&result3);

//清理事务槽
dest_trans_redo();
dest_mem_no_manager();

return 0;
}
