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
//"create index test_table_inx on test_table USING hash ( id ) SKIP_LEVEL = 4 ";
"create index test_table_inx on test_table (id)  SKIP_LEVEL = 4 ";

const char *sql_str3 = ""
"insert into test_table  ( id , name )  values (1,2) ";

const char *sql_str4 = ""
//"select id from  test_table  where name = 2 ";
"select id from  test_table  where id = 1 ";

const char *sql_str5 = ""
"create table test_table2 ( id INT , name2 BIGINT ) TABLET_BLOCK_SIZE = 16 , EXTERN_SIZE = 4 ";     

const char *sql_str6 = ""
"insert into test_table2  ( id , name2 )  values (1,3) ";

const char *sql_str7 = ""
"select  name,name2 from test_table t join test_table2 t1 on t.id = t1.id ";
//"select  name,name2 from test_table t , test_table2 t1 where t.id = t1.id ";

//const char *sql_str2 = ""
//"create index test_table_inx on test_table ( id ) SKIP_LEVEL = 4 ";

const char *sql_str8 = ""
"delete from test_table ";

CPP_DEBUG<< sql_str <<endl;
CPP_DEBUG<< sql_str2 <<endl;
CPP_DEBUG<< sql_str3 <<endl;
CPP_DEBUG<< sql_str4 <<endl;
CPP_DEBUG<< sql_str5 <<endl;
CPP_DEBUG<< sql_str6 <<endl;
CPP_DEBUG<< sql_str7 <<endl;
CPP_DEBUG<< sql_str8 <<endl;

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

    
 ParseResult result5;
 int ret5 = parse_init(&result5);
 parse_sql(&result5, sql_str5, strlen(sql_str5));

rapidjson::StringBuffer buffer5;
//rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
rapidjson::PrettyWriter<rapidjson::StringBuffer> writer5(buffer5); 	
result4.Doc.Accept(writer5);     
    
    
ParseResult result6;
int ret6 = parse_init(&result6);
parse_sql(&result6, sql_str6, strlen(sql_str6));

rapidjson::StringBuffer buffer6;
//rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
rapidjson::PrettyWriter<rapidjson::StringBuffer> writer6(buffer6); 	
result6.Doc.Accept(writer6);  

 ParseResult result7;
 int ret7 = parse_init(&result7);
 parse_sql(&result7, sql_str7, strlen(sql_str7));

 rapidjson::StringBuffer buffer7;
 //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
 rapidjson::PrettyWriter<rapidjson::StringBuffer> writer7(buffer7); 	
 result7.Doc.Accept(writer7);  


 ParseResult result8;
 int ret8 = parse_init(&result8);
 parse_sql(&result8, sql_str8, strlen(sql_str8));

 rapidjson::StringBuffer buffer8;
 //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
 rapidjson::PrettyWriter<rapidjson::StringBuffer> writer8(buffer8); 	
 result8.Doc.Accept(writer8);  
 
 
CPP_DEBUG <<"create table "<< buffer.GetString() << std::endl;
 for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_TABLE"  ){
  		CreateTableAnalyser qta( &v ,&(result.Doc) );
  		make_create_table_plan mctp(&qta);
  	  mctp.execute();
		}
  }	
  
  CPP_DEBUG <<"create table "<< buffer5.GetString() << std::endl;
 for (auto& v : result5.Doc["ROOT"]["children"].GetArray() ){
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
//分配一个事务槽
long long  trans_no;
if(0!=(err=allocate_trans(&trans_no)))DEBUG("allocate_trans[%d] failed,trans_no is %d\n",trans_no,err); 
// 开始一个事务
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


CPP_DEBUG <<"insert into table "<< buffer6.GetString() << std::endl;
err = 0;
//分配一个事务槽
if(0!=(err=allocate_trans(&trans_no)))DEBUG("allocate_trans[%d] failed,trans_no is %d\n",trans_no,err); 
// 开始一个事务
if(0!=(err=start_trans(trans_no)))DEBUG("start_trans failed,trans_no is %d\n",err); 
	 
   for (auto& v : result6.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "INSERT_TABLE"  ){
  		InsertTableAnalyser ita( &v ,&(result6.Doc) );
  		make_insert_one_table_plan miot(&ita);
  	  miot.execute(trans_no);
		}
  }	
 
if(0!=(err=commit_trans(trans_no)))ERROR("commit_trans failed,trans_no is %d\n",err); 


////////////////////////////////////////////////////////////////////////
 
//构造查询计划
  CPP_DEBUG <<"优化前 json"<< buffer4.GetString() << std::endl;

 for (auto& v : result4.Doc["ROOT"]["children"].GetArray() ){
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "SELECT"  ){
  		QueryAnalyser qa( v ,result4.Doc );
  		
  		for(auto& name : qa.tables){
  			CPP_DEBUG<<"Names: "<<name.table_name_<<" "<<name.alias_name_<<" "<<name.sub_select_alias_name_<<std::endl;
  			
  		}
  		
  		//上拉子链接
  		qa.pull_up_sublinks();
  		//上拉子查询
  		qa.pull_up_subquerys();
  		CPP_DEBUG<<"Begin Optimiser\n "<<std::endl;

  		//逻辑优化器
  		QueryOptimiser qo (qa);

  		CPP_DEBUG<<"优化between\n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_btw,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 in\n "<<std::endl;
	  	qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_in,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 not \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_not,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const 表达式\n "<<std::endl;
  		qo.optimiser_project_template( &(*(qa.project_lists))["children"] , 0 ,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const 条件\n "<<std::endl;
		  qo.optimiser_project_template( (qa.where_list) ,0,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
    //优化后
  		CPP_DEBUG <<"优化后 json\n";
  		rapidjson_log( &result4.Doc["ROOT"] );
    
	 //std::vector<fun_oper *>  projection_fun_oper_lists ;
   //esolve_to_opper_node(   &qa ,  projection_fun_oper_lists	);
		  CPP_DEBUG<<"生成物理执行计划\n "<<std::endl;
		  physical_query_plan phplan( &qa );
		 
				CPP_DEBUG<<"执行SQL\n "<<std::endl;
				//分配一个事务槽
				long long  trans_no2;
				if(0!=(err=allocate_trans(&trans_no2)))DEBUG("allocate_trans[%d] failed,trans_no2 is %d\n",trans_no2,err); 
				// 开始一个事务
				if(0!=(err=start_trans(trans_no2)))DEBUG("start_trans failed,trans_no2 is %d\n",err); 
				err = phplan.execute(trans_no2);
				if(err) //回滚
					{
						if(0!=(err=rollback_trans(trans_no2)))ERROR("rollback_trans failed,trans_no2 is %d\n",err);
					}
				else{//提交
					if(0!=(err=commit_trans(trans_no2)))ERROR("commit_trans failed,trans_no2 is %d\n",err); 		  

				}
		
		}
  }	
////////////////////////////////////////////////////////////////////////  

//构造查询计划
  CPP_DEBUG <<"优化前 json"<< buffer7.GetString() << std::endl;

 for (auto& v : result7.Doc["ROOT"]["children"].GetArray() ){
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "SELECT"  ){
  		QueryAnalyser qa( v ,result7.Doc );
  		
  		for(auto& name : qa.tables){
  			CPP_DEBUG<<"Names: "<<name.table_name_<<" "<<name.alias_name_<<" "<<name.sub_select_alias_name_<<std::endl;
  			
  		}
  		
  		//上拉子链接
  		qa.pull_up_sublinks();
  		//上拉子查询
  		qa.pull_up_subquerys();
  		CPP_DEBUG<<"Begin Optimiser\n "<<std::endl;

  		//逻辑优化器
  		QueryOptimiser qo (qa);

  		CPP_DEBUG<<"优化between\n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_btw,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 in\n "<<std::endl;
	  	qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_in,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 not \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_not,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const 表达式\n "<<std::endl;
  		qo.optimiser_project_template( &(*(qa.project_lists))["children"] , 0 ,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const 条件\n "<<std::endl;
		  qo.optimiser_project_template( (qa.where_list) ,0,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
    //优化后
  		CPP_DEBUG <<"优化后 json\n";
  		rapidjson_log( &result7.Doc["ROOT"] );
    
	 //std::vector<fun_oper *>  projection_fun_oper_lists ;
   //esolve_to_opper_node(   &qa ,  projection_fun_oper_lists	);
		  CPP_DEBUG<<"生成物理执行计划\n "<<std::endl;
		  physical_query_plan phplan( &qa );
		 
				CPP_DEBUG<<"执行SQL\n "<<std::endl;
				//分配一个事务槽
				long long  trans_no2;
				if(0!=(err=allocate_trans(&trans_no2)))DEBUG("allocate_trans[%d] failed,trans_no2 is %d\n",trans_no2,err); 
				// 开始一个事务
				if(0!=(err=start_trans(trans_no2)))DEBUG("start_trans failed,trans_no2 is %d\n",err); 
				err = phplan.execute(trans_no2);
				if(err) //回滚
					{
						if(0!=(err=rollback_trans(trans_no2)))ERROR("rollback_trans failed,trans_no2 is %d\n",err);
					}
				else{//提交
					if(0!=(err=commit_trans(trans_no2)))ERROR("commit_trans failed,trans_no2 is %d\n",err); 		  

				}
		
		}
  }	

////////////////////////////////////////////////////////////////////////  

//构造查询计划
  CPP_DEBUG <<"优化前 json"<< buffer8.GetString() << std::endl;

 for (auto& v : result8.Doc["ROOT"]["children"].GetArray() ){
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "DELETE_STMT"  ){
  		DeleteAnalyser qa( v ,result8.Doc );
  		
  		for(auto& name : qa.tables){
  			CPP_DEBUG<<"Names: "<<name.table_name_<<" "<<name.alias_name_<<" "<<name.sub_select_alias_name_<<std::endl;
  			
  		}
  		
  		//上拉子链接
  		qa.pull_up_sublinks();
  		//上拉子查询
  		qa.pull_up_subquerys();
  		CPP_DEBUG<<"Begin Optimiser\n "<<std::endl;

  		//逻辑优化器
  		QueryOptimiser qo (qa);

  		CPP_DEBUG<<"优化between\n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_btw,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 in\n "<<std::endl;
	  	qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_in,&qo,std::placeholders::_1,std::placeholders::_2) );
  		CPP_DEBUG<<"优化 not \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_not,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const \n "<<std::endl;
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  //CPP_DEBUG<<"优化 const 表达式\n "<<std::endl;
  		//qo.optimiser_project_template( &(*(qa.project_lists))["children"] , 0 ,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		  CPP_DEBUG<<"优化 const 条件\n "<<std::endl;
		  qo.optimiser_project_template( (qa.where_list) ,0,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
    //优化后
  		CPP_DEBUG <<"优化后 json\n";
  		rapidjson_log( &result8.Doc["ROOT"] );
    
	 //std::vector<fun_oper *>  projection_fun_oper_lists ;
   //esolve_to_opper_node(   &qa ,  projection_fun_oper_lists	);
		  CPP_DEBUG<<"生成物理执行计划\n "<<std::endl;
		  physical_query_plan phplan( &qa );
		 
				CPP_DEBUG<<"执行SQL\n "<<std::endl;
				//分配一个事务槽
				long long  trans_no3;
				if(0!=(err=allocate_trans(&trans_no3)))DEBUG("allocate_trans[%d] failed,trans_no3 is %d\n",trans_no3,err); 
				// 开始一个事务
				if(0!=(err=start_trans(trans_no3)))DEBUG("start_trans failed,trans_no3 is %d\n",err); 
				err = phplan.execute(trans_no3);
				if(err) //回滚
					{
						if(0!=(err=rollback_trans(trans_no3)))ERROR("rollback_trans failed,trans_no3 is %d\n",err);
					}
				else{//提交
					if(0!=(err=commit_trans(trans_no3)))ERROR("commit_trans failed,trans_no3 is %d\n",err); 		  

				}
		
		}
  }	
////////////////////////////////////////////////////////////////////////
parse_terminate(&result);
parse_terminate(&result2);
parse_terminate(&result3);
parse_terminate(&result4);
parse_terminate(&result5);
parse_terminate(&result6);
parse_terminate(&result7);
parse_terminate(&result8);

//清理事务槽
dest_trans_redo();
dest_mem_no_manager();

return 0;
}
