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
#define CREATE_TABLE_HAS_NO_OPT_OPITION 61003

struct FieldDesc
{
	std::string field_name;
	int field_type;
	FieldDesc(){}
	FieldDesc(std::string &_field_name, int _field_type   ):field_name(_field_name),field_type(_field_type){  }
	
};


class CreateTableAnalyser
{
public:
rapidjson::Value    *root;
rapidjson::Document *doc;
size_t table_block_size;  //TABLET_BLOCK_SIZE
size_t extern_size;       //EXTERN_SIZE

std::string table_name;
std::vector<FieldDesc> elements; //所有字段

// 默认 16M
CreateTableAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc):root(_root),doc(_doc),table_block_size(16*1024*1024),extern_size(16*1024*1024){get_all();}
CreateTableAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc,size_t _table_block_size,size_t _extern_size):root(_root),doc(_doc),table_block_size(_table_block_size),extern_size(_extern_size){get_all();}

int get_table_name()
{
	 CPP_DEBUG <<"before get_name \n";
   rapidjson_log( root );
	if( root->HasMember("TABLE_NAME") )
		{
			table_name = const_cast<char *>( (*root)["TABLE_NAME"]["str_value_"].GetString() );
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
	CPP_DEBUG<<" get_elemets \n";

	rapidjson::Value    *elemets = NULL;
	if( root->HasMember("TABLE_ELEMENT") )
		{
			elemets =  &(*root)["TABLE_ELEMENT"];
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
		
		CPP_DEBUG<<" for( auto &v : elemets->GetArray() )	 !\n";
	  

		std::string field_name;
		int field_type;
			for ( auto &v0 : children->GetArray() )	
				{
					if( !v0.IsObject() )continue;
					if( v0.HasMember("tag") && v0["tag"].GetInt() == T_IDENT )
						{
							field_name = std::string( v0["str_value_"].GetString() );
							CPP_DEBUG<<" field_name " << field_name <<endl;

						}
						if( v0.HasMember("tag") && v0["tag"].GetInt() >= T_TYPE_INTEGER &&  v0["tag"].GetInt() <= T_TYPE_LONGLONG )
						{
							field_type =  v0["tag"].GetInt() ;
							CPP_DEBUG<<" field_type " << field_type <<endl;

						}
				}
		elements.emplace_back( field_name,field_type );
		}
		
return 0;
}


int get_create_info()
{
	rapidjson::Value    *info = NULL;
	if( root->HasMember("OPT_OPITION") )
		{
			info =  &(*root)["OPT_OPITION"];
		}
		else
		{
			CPP_ERROR<<"THERE IS NO OPT_OPITION!\n";
			return CREATE_TABLE_HAS_NO_OPT_OPITION;
		}
		
		for( auto &v : info->GetArray() )	
		{
			rapidjson_log( v );

		  if( v["tag"].GetInt() == T_TABLET_BLOCK_SIZE && v.HasMember("TABLET_BLOCK_SIZE") ) 
			{
				table_block_size = atol( v["TABLET_BLOCK_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( v["tag"].GetInt() == T_EXTERN_SIZE && v.HasMember("EXTERN_SIZE") ) 
			{
				extern_size = atol( v["EXTERN_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			
		}
		
		
}

int get_all()
{
	int ret = 0;
	ret =get_table_name() ;
	CPP_DEBUG<<"get_table_name ret "<<ret<<endl;
	if( ret )return ret;
	ret =get_elemets() ;
	if( ret )return ret;
	ret =get_create_info() ;
	if( ret )return ret;
	return 0;

}


};



#endif
