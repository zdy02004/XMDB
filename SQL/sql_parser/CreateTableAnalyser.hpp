#ifndef CREATE_TAB_HPP  
#define CREATE_TAB_HPP  
#include "parser.hh"
#include<vector>
#include<string>
#include "../../util/log/log_util.h"

/*
g++ -C -std=c++11 CreateTableAnalyser.hpp 


*/

#define CREATE_TABLE_HAS_NO_TABLE_NAME 61000
#define CREATE_TABLE_HAS_NO_TABLE_FIELDS 61001
#define CREATE_TABLE_FIELD_DEFINATION_FAILED 61002

struct FieldDesc
{
	std::string field_name;
	int field_type;
	FieldDesc(){}
	FieldDesc(std::string &_field_name, int _field_type   ):field_name(_field_name),field_type(_field_type){  }
	//field_t field;
	
	//void fill_field()
	//{
	//	strcpy(field.field_name, const_cast<char *>(field_name.c_str() ) );
	//	switch(  field_type )
	//	{
	//		case T_TYPE_INTEGER:						field.field_type = FIELD_TYPE_INT;break;
  //		case T_TYPE_FLOAT :						field.field_type = FIELD_TYPE_FLOAT;break;
  //		case T_TYPE_DOUBLE :						field.field_type = FIELD_TYPE_DOUBLE;break;
  //		case T_TYPE_DECIMAL :					field.field_type = FIELD_TYPE_DOUBLE;break;
  //		case T_TYPE_BOOLEAN :					field.field_type = FIELD_TYPE_SHORT;break;
  //		case T_TYPE_DATE :					    field.field_type = FIELD_TYPE_LONG;break;
  //		case T_TYPE_TIME :break;
  //		case T_TYPE_DATETIME :					field.field_type = FIELD_TYPE_LONG;break;
  //		case T_TYPE_TIMESTAMP :break;
  //		case T_TYPE_CHARACTER:					field.field_type = FIELD_TYPE_STR;break;
  //		case T_TYPE_VARCHAR :					field.field_type = FIELD_TYPE_STR;break;
  //		case T_TYPE_CREATETIME :break;
  //		case T_TYPE_MODIFYTIME :break;
  //
	//  }
	//  fill_field_info ( &field ) ;
	//}
	
};


class CrateTableAnalyser
{
public:
rapidjson::Value    *root;
rapidjson::Document *doc;

std::string table_name;
vector<FieldDesc> elements; //ËùÓÐ×Ö¶Î

int get_table_name()
{
	if( root->HasMember("TABLE_NAME") )
		{
			table_name = const_cast<char *>( (*root)["TABLE_NAME"].GetString() );
		}
		else
		{
			CPP_ERROR<<"THERE IS NO TABLE NAME!\n";
			return CREATE_TABLE_HAS_NO_TABLE_NAME;
		}
return 0;
}

int get_elemets()
{
	rapidjson::Value    *elemets = NULL;
	if( root->HasMember("TABLE_ELEMENT") )
		{
			elemets =  &(*root)["TABLE_NAME"];
		}
		else
		{
			CPP_ERROR<<"THERE IS NO TABLE FIELDS!\n";
			return CREATE_TABLE_HAS_NO_TABLE_FIELDS;
		}
		
	for( auto &v : elemets->GetArray() )	
		{
		if( v["tag"].GetInt() != T_COLUMN_DEFINITION || !v.HasMember("children") ) 
			{
				CPP_ERROR<<" FIELD DEFINATION FAILED !\n";
				return CREATE_TABLE_FIELD_DEFINATION_FAILED;
			}
		rapidjson::Value * children = &( v["children"] );
			
		std::string field_name;
		int field_type;
			for ( auto &v0 : children->GetArray() )	
				{
					if( v0.HasMember("tag") && v0["tag"].GetInt() == T_IDENT )
						{
							field_name = std::string( v0["str_value_"].GetString() );
						}
						if( v0.HasMember("tag") && v0["tag"].GetInt() == T_IDENT )
						{
							field_type =  v0["tag"].GetInt() ;
						}
				}
		elements.emplace_back( field_name,field_type );
		}
		
return 0;
}


};



#endif