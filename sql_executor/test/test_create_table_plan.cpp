#include "../../SQL/sql_parser/parser.hh"
#include "../../SQL/sql_parser/queryOptimiser.hpp"
#include "../fun_oper.h"
#include "../make_create_table_plan_node.h"

/*
 
  g++ -g test_create_table_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o main -w  -lpthread 
*/


void init_mem_no_manager()
{
	init_mem_block_no_manager();
	init_mem_table_no_manager();
	//init_mem_index_no_manager();
}

void dest_mem_no_manager()
{
  dest_mem_table_no_manager();
  //dest_mem_index_no_manager();
	dest_mem_block_no_manager();
}

int main()
{
	init_mem_no_manager();
	
const char *sql_str = ""
"create table test_table ( id INT , name BIGINT ) TABLET_BLOCK_SIZE = 16 , EXTERN_SIZE = 4 ";     


CPP_DEBUG<< sql_str <<endl;

ParseResult result;
 int ret = parse_init(&result);
  parse_sql(&result, sql_str, strlen(sql_str));
  //ASSERT_NE(result.result_tree_, (ParseNode*)NULL);

   
    rapidjson::StringBuffer buffer;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    	
    	
    result.Doc.Accept(writer);
    
 
//优化前
  CPP_DEBUG <<"优化前 json"<< buffer.GetString() << std::endl;

 for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "CREATE_TABLE"  ){
  		CreateTableAnalyser qta( &v ,&(result.Doc) );
  		make_create_table_plan mctp(&qta);
  	  mctp.execute();

		
		}
  }	
  
  //优化后
  //CPP_DEBUG <<"优化后 json\n";
  //rapidjson_log( &result.Doc["ROOT"] );
  
   
  
parse_terminate(&result);

dest_mem_no_manager();

return 0;
}
