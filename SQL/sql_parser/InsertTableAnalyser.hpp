#ifndef INSERT_TAB_HPP  
#define INSERT_TAB_HPP  
#include "parser.hh"
#include<vector>
#include<string>
#include "../../util/log/log_util.h"

/*
g++ -C -std=c++11 InsertTableAnalyser.hpp 


*/

#define INSERT_TABLE_HAS_NO_TABLE_NAME 63000
#define INSERT_TABLE_HAS_NO_TABLE_VALUES 63001
#define INSERT_TABLE_FIELD_FAILED 63002
#define INSERT_TABLE_HAS_NO_OPT_OPITION 63003
#define INSERT_TABLES_NUM_NOT_EQA 63004

class InsertTableAnalyser
{
public:
rapidjson::Value    *root;
rapidjson::Document *doc;
int                  is_replace;
std::string table_name;
std::vector<std::string> elements; //所有字段名称
std::vector<std::string> values;   //所有字段值


InsertTableAnalyser(rapidjson::Value *_root,rapidjson::Document *_doc):root(_root),doc(_doc),is_replace(0){get_all();}

int get_table_name()
{
	 CPP_DEBUG <<"before get_name \n";
   //rapidjson_log( root );
	if( root->HasMember("TABLE_NAME") )
		{
			table_name = const_cast<char *>( (*root)["TABLE_NAME"]["str_value_"].GetString() );
		}
		else
		{
			CPP_ERROR<<"THERE IS NO TABLE NAME!\n";
			return INSERT_TABLE_HAS_NO_TABLE_NAME;
		}
return 0;
}

int get_elemets()
{
	CPP_DEBUG<<" get_elemets \n";

	rapidjson::Value    *elemets = NULL;
	if( root->HasMember("OPT_INSERT_COLUMNS") )
		{
			elemets =  &(*root)["OPT_INSERT_COLUMNS"]["children"];
		}
		else
		{
			CPP_DEBUG<<"THERE IS NO TABLE FIELDS!\n";
			return 0;
		}
		

		std::string field_name;
			for ( auto &v0 : elemets->GetArray() )	
			{
				if( !v0.IsObject() )continue;
				if( v0.HasMember("tag") && v0["tag"].GetInt() == T_IDENT )
					{
						field_name = std::string( v0["str_value_"].GetString() );
						CPP_DEBUG<<" field_name " << field_name <<endl;

					}
				elements.emplace_back( field_name );

			}
	
		
return 0;
}


int get_values()
{
	CPP_DEBUG<<" get_elemets \n";

	rapidjson::Value    *valus = NULL;
	if( root->HasMember("VALUE_LIST") )
		{
			valus =  &(*root)["VALUE_LIST"]["children"];
		}
		else
		{
			CPP_DEBUG<<"THERE IS NO TABLE Values!\n";
			return INSERT_TABLE_HAS_NO_TABLE_VALUES;
		}
		

		std::string value_str;
			for ( auto &v0 : valus->GetArray() )	
			{
				if( !v0.IsObject() )continue;
				if( v0.HasMember("tag") && v0["tag"].GetInt() == T_OP_NAME_FIELD )
					{
						value_str = std::string( v0["str_value_"].GetString() );
						CPP_DEBUG<<" value_str " << value_str <<std::endl;

					}
				values.emplace_back( value_str );

			}
	
		
return 0;
}


int get_insert_info()
{
	rapidjson::Value    *info = NULL;
	if( root->HasMember("REPLACE_OR_INSERT") )
		{
			info =  &(*root)["REPLACE_OR_INSERT"];
		}
		else
		{
			return 0;
		}
		
		std::string is_replace_str = (*info)["value_"].GetString();
		if( is_replace_str == "1" )is_replace = 1;
		
		
}

int check_values_num()
{
	if( !elements.empty() ){
		if( elements.size() != values.size() )ERROR("fields.size %d != values.size $d ,elements.size(),values.size()\n ");
			return INSERT_TABLES_NUM_NOT_EQA;
	}
	return 0;
		
}

int get_all()
{
	int ret = 0;
	ret =get_table_name() ;
	CPP_DEBUG<<"get_table_name ret "<<ret<<endl;
	if( ret )return ret;
	ret =get_elemets() ;
	if( ret )return ret;
	ret =get_values() ;
	if( ret )return ret;
	ret =get_insert_info() ;
	if( ret )return ret;
	return 0;

}


};



#endif