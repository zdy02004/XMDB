#ifndef CREATE_INDEX_HPP  
#define CREATE_INDEX_HPP  
#include "parser.hh"

#include<vector>
#include<string>
#include "../../util/log/log_util.h"

/*
g++ -C  -std=c++11 CreateIndexAnalyser.hpp


*/

#define CREATE_INDEX_HAS_NO_TABLE_NAME 62000
#define CREATE_INDEX_HAS_NO_TABLE_FIELDS 62001
#define CREATE_INDEX_FIELD_DEFINATION_FAILED 62002
#define CREATE_INDEX_HAS_NO_OPT_OPITION 62003
#define CREATE_INDEX_HAS_NO_INDEX_NAME 62004



class CreateIndexAnalyser
{
public:
rapidjson::Value    *root;
rapidjson::Document *doc;
size_t table_block_size;  //TABLET_BLOCK_SIZE
size_t extern_size;       //EXTERN_SIZE

std::string index_name;  //索引名
std::string table_name;  //索引所在的表名
std::vector<std::string> elements; //所有字段
int index_type;					 //索引类型
int constraint_type;		 //约束类型
int skip_level;					 //跳表层级
// 默认 16M
CreateIndexAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc):root(_root),doc(_doc),index_type(0),constraint_type(0),table_block_size(16*1024*1024),extern_size(16*1024*1024),skip_level(4){get_all();}
CreateIndexAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc,int _index_type,int _constraint_type,size_t _table_block_size,size_t _extern_size):root(_root),doc(_doc),index_type(_index_type),skip_level(4),constraint_type(_constraint_type),table_block_size(_table_block_size),extern_size(_extern_size){get_all();}

int get_table_name()
{
	if(root->HasMember("children") )root = &(((*root)["children"].GetArray())[0]);
	 
	 CPP_DEBUG <<"before get_table_name \n";
   rapidjson_log( root );
   
	 if( root->HasMember("RELATION_NAME") )
		{
			table_name = const_cast<char *>( (*root)["RELATION_NAME"]["str_value_"].GetString() );

		}
		else
		{
			CPP_ERROR<<"THERE IS NO TABLE NAME!\n";
			return CREATE_INDEX_HAS_NO_TABLE_NAME;
		}
return 0;
}

int get_index_name()
{
   	 CPP_DEBUG <<"before int get_index_name() \n";

	if( root->HasMember("INDEX_NAME") )
		{
			index_name = const_cast<char *>( (*root)["INDEX_NAME"]["str_value_"].GetString() );
		}
		else
		{
			CPP_ERROR<<"THERE IS NO INDEX NAME!\n";
			return CREATE_INDEX_HAS_NO_INDEX_NAME;
		}
return 0;
}

int get_elemets()
{
	CPP_DEBUG<<" get_elemets \n";

	rapidjson::Value    *field_list = NULL;
	if( root->HasMember("COLUMN_LIST") )
		{
			field_list =  &(*root)["COLUMN_LIST"];
		}
		else
		{
			CPP_ERROR<<"THERE IS NO TABLE FIELDS!\n";
			return CREATE_INDEX_HAS_NO_TABLE_FIELDS;
		}
	
	std::string _field_name;

	if(field_list->IsArray())
	{
	for( auto &v : field_list->GetArray() )	
		{

		if( !v.IsObject() )continue;
		if( v["tag"].GetInt() != T_IDENT  ) 
			{
				CPP_ERROR<<" FIELD DEFINATION FAILED !\n";
				return CREATE_INDEX_FIELD_DEFINATION_FAILED;
			}
		else
			{
				_field_name = const_cast<char *>( (v)["str_value_"].GetString() );
				CPP_DEBUG<<" field_name " << _field_name <<endl;
			}
		elements.emplace_back( _field_name );
		}
	}
	else 
		{
		if( (*field_list)["tag"].GetInt() != T_COLUMN_DEFINITION  ) 
			{
				CPP_ERROR<<" FIELD DEFINATION FAILED !\n";
				return CREATE_INDEX_FIELD_DEFINATION_FAILED;
			}
		else
			{
				_field_name = std::string( (*field_list)["str_value_"].GetString() );
				CPP_DEBUG<<" field_name " << _field_name <<endl;
			}
		elements.emplace_back( _field_name );
			}
		
		
return 0;
}


// 获得索引类型
// 暂时不支持约束
int get_constraint_type()
{
	return 0;
}

// 获得索引类型
int get_index_type()
{
	CPP_DEBUG <<"before get_index_type() \n";

	if( root->HasMember("INDEX_TYPE") )
		{
			int tag =  (*root)["INDEX_TYPE"]["tag"].GetInt();
			
			if( tag == T_INDEX_HASH ) index_type= T_INDEX_HASH;//INDEX_TYPE_HASH;
			else	if( tag == T_INDEX_SKIPLIST ) index_type= T_INDEX_SKIPLIST;//	INDEX_TYPE_SKIP;
		}
		else index_type= T_INDEX_SKIPLIST;//	INDEX_TYPE_SKIP;
		return 0;
}


int get_create_info()
{
	CPP_DEBUG <<"before get_create_info() \n";

	rapidjson::Value    *elemets = NULL;
	if( root->HasMember("OPT_OPITION") )
		{
			elemets =  &(*root)["OPT_OPITION"];
		}
		else
		{
			CPP_ERROR<<"THERE IS NO OPT_OPITION!\n";
			return CREATE_INDEX_HAS_NO_OPT_OPITION;
		}
		
		rapidjson_log( elemets );

		if(elemets->IsArray() )for( auto &v : elemets->GetArray() )	
		{
		  if( v["tag"].GetInt() == T_TABLET_BLOCK_SIZE && v.HasMember("TABLET_BLOCK_SIZE") ) 
			{
				table_block_size = atol( v["TABLET_BLOCK_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( v["tag"].GetInt() == T_EXTERN_SIZE && v.HasMember("EXTERN_SIZE") ) 
			{
				extern_size = atol( v["EXTERN_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( v["tag"].GetInt() == T_SKIP_LEVEL && v.HasMember("SKIP_LEVEL") ) 
			{
				skip_level = atoi( v["SKIP_LEVEL"]["str_value_"].GetString() ); // 默认是兆
			}
			
			
		}
		else
			{
				
			if( (*elemets)["tag"].GetInt() == T_TABLET_BLOCK_SIZE && (*elemets).HasMember("TABLET_BLOCK_SIZE") ) 
			{
				table_block_size = atol( (*elemets)["TABLET_BLOCK_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( (*elemets)["tag"].GetInt() == T_EXTERN_SIZE && (*elemets).HasMember("EXTERN_SIZE") ) 
			{
				extern_size = atol( (*elemets)["EXTERN_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( (*elemets)["tag"].GetInt() == T_SKIP_LEVEL && (*elemets).HasMember("SKIP_LEVEL") ) 
			{
				skip_level = atoi( (*elemets)["SKIP_LEVEL"]["str_value_"].GetString() ); // 默认是兆
			}
				
			}
		
		
}

int get_all()
{
	int ret = 0;
	ret =get_table_name() ;
	if( ret )return ret;
	ret =get_index_name() ;
	if( ret )return ret;
	ret =get_index_type() ;
	if( ret )return ret;
	ret = get_constraint_type();
	if( ret )return ret;
	ret =get_elemets() ;
	if( ret )return ret;
	ret =get_create_info() ;
	if( ret )return ret;
	return 0;

}


};



#endif
