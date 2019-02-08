/*
g++ -C -w -std=c++11 update_analyser.hpp

*/

#ifndef UPDATE_TAB_HPP  
#define UPDATE_TAB_HPP  
#include "query_analyser.hpp"
#include "../../util/log/log_util.h"
#include <map>

#define BASIC_OPS_UPDATE  4


typedef struct set_value
{
	char ibuf[sizeof(int)];
  	char lbuf[sizeof(long)];
  	char fbuf[sizeof(float)];
  	std::string const_value;
  	std::string const_type;
}set_value;

class UpdateAnalyser:public QueryAnalyser
{
public:

rapidjson::Value  * set_lists;	
rapidjson::Value  * table_name_v;		
std::string table_name;	
	
std::map< std::string , set_value > set_map;
	
UpdateAnalyser(rapidjson::Value & value ,rapidjson::Document & doc_  ):QueryAnalyser( value , doc_ ),set_lists(NULL),table_name_v(NULL)
{
	oper_type = BASIC_OPS_UPDATE ;
	 //检查是否有 set_list                                        
	check_and_assign_member(where_list,"SET_CLAUSE");   
	check_and_assign_member(table_name_v,"TABLE_NAME");
	
	if( (*table_name_v).HasMember("TABLE_NAME") && (*table_name_v)["TABLE_NAME"].HasMember("str_value_") )
	{
		table_name=string((*table_name_v)["TABLE_NAME"]["str_value_"].GetString()); // 表名   
		// 插入解析后的表
		DEBUG(" tables.emplace_back( TableItem(%s,%s,%s) );\n", table_name.c_str(),table_name.c_str(),table_name.c_str() );
  		tables.emplace_back( TableItem(table_name,table_name,table_name) );
		resolve_update_list(set_lists);
	}
}

void resolve_update_list_help( rapidjson::Value  * v,int level = 0 ){

DEBUG("resolve_update_list_help -------- { \n");
					
				std::string column_name;
				rapidjson_log(v);
  				if( (*v).HasMember("COLUNM_NAME") && (*v)["COLUNM_NAME"].HasMember("str_value_")    )  
  				{
  					column_name=string( (*table_name_v)["COLUNM_NAME"]["str_value_"].GetString() ); 	// 表名   
  				}
  				
					std::string const_value;
					std::string const_type;
					if( (*v).HasMember("EXPR") && (*v)["EXPR"].HasMember("str_value_")    )  
  				{
  					const_value = string((*table_name_v)["const_type"]["str_value_"].GetString()); 	// 值
  					if( (*v)["EXPR"].HasMember("const_type")    )  
  					{
  						const_type = string((*table_name_v)["const_type"]["str_value_"].GetString()); 	// 值类型   	
  					}  				 
  				}  		
  				set_value sv;
  				sv.const_type  = const_type;
  				  				
  				//转换为整型
  				if( const_type== "INTNUM"  )
  				{
  					long lval = std::stol(const_value);
  					int  ival ;
  					if( lval>-65535 && lval<=65535 )
  					{
  						ival =  std::stoi(const_value);
  						strncpy( const_cast<char *>( sv.ibuf ), (char *)(&ival) , sizeof(int)  );
  					}
  					strncpy( const_cast<char *>( sv.lbuf ) ,  (char *)(&lval) , sizeof(long)  );
  				}
  				//转换为浮点型	
  				else if( const_type == "APPROXNUM" )
  				{
  					float fval = std::stof(const_value);
  					strncpy( const_cast<char *>( sv.fbuf ) , (char *)(&fval ), sizeof(float)  );
  				}
  				
  				//转换为字符串
  				else if( const_type== "STRING" )
  				{
  					sv.const_value = const_value;
  				}
  					
 //放入列表  					
 set_map[column_name] = sv;
 DEBUG("resolve_update_list_help -------- } \n");

}


//解析 update_list
void resolve_update_list( rapidjson::Value  * updatelist ,int level = 0 ){
   //遍历 updatelist 将数据表填入 table_names, 将子查询 填入 sub_querys
  	if( updatelist->IsArray() ) {
  		for (auto& v : ( (*updatelist).GetArray() )  ){  				
  				resolve_update_list( &(v),level);
         }//end for
    }
    else if(NULL != updatelist)resolve_update_list_help(updatelist,level);
         
} // end 

};

#endif
