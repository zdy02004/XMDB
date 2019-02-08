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
	 //����Ƿ��� set_list                                        
	check_and_assign_member(where_list,"SET_CLAUSE");   
	check_and_assign_member(table_name_v,"TABLE_NAME");
	
	if( (*table_name_v).HasMember("TABLE_NAME") && (*table_name_v)["TABLE_NAME"].HasMember("str_value_") )
		{
			 table_name=string((*table_name_v)["TABLE_NAME"]["str_value_"].GetString()); 	// ����   
			 resolve_update_list(set_lists);
		}
}

void resolve_update_list_help( rapidjson::Value  * v,int level = 0 ){

DEBUG("resolve_update_list_help -------- { \n");
					
					std::string column_name;
					rapidjson_log(v);
  				if( (*v).HasMember("COLUNM_NAME") && (*v)["COLUNM_NAME"].HasMember("str_value_")    )  
  				{
  					column_name=string( (*table_name_v)["COLUNM_NAME"]["str_value_"].GetString() ); 	// ����   
  				}
  				
					std::string const_value;
					std::string const_type;
					if( (*v).HasMember("EXPR") && (*v)["EXPR"].HasMember("str_value_")    )  
  				{
  					const_value = string((*table_name_v)["const_type"]["str_value_"].GetString()); 	// ֵ
  					if( (*v)["EXPR"].HasMember("const_type")    )  
  					{
  						const_type = string((*table_name_v)["const_type"]["str_value_"].GetString()); 	// ֵ����   	
  					}  				 
  				}  		
  				set_value sv;
  				sv.const_type  = const_type;
  				  				
  				//ת��Ϊ����
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
  				//ת��Ϊ������	
  				else if( const_type == "APPROXNUM" )
  				{
  					float fval = std::stof(const_value);
  					strncpy( const_cast<char *>( sv.fbuf ) , (char *)(&fval ), sizeof(float)  );
  				}
  				
  				//ת��Ϊ�ַ���
  				else if( const_type== "STRING" )
  				{
  					sv.const_value = const_value;
  				}
  					
 //�����б�  					
 set_map[column_name] = sv;
 DEBUG("resolve_update_list_help -------- } \n");

}


//���� update_list
void resolve_update_list( rapidjson::Value  * updatelist ,int level = 0 ){
   //���� updatelist �����ݱ����� table_names, ���Ӳ�ѯ ���� sub_querys
  	if( updatelist->IsArray() ) {
  		for (auto& v : ( (*updatelist).GetArray() )  ){  				
  				resolve_update_list( &(v),level);
         }//end for
    }
    else if(NULL != updatelist)resolve_update_list_help(updatelist,level);
         
} // end 

};

#endif
