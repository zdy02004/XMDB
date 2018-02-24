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



class CrateIndexAnalyser
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
CrateIndexAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc):root(_root),doc(_doc),index_type(0),constraint_type(0),table_block_size(16*1024*1024),extern_size(16*1024*1024),skip_level(4){get_all();}
CrateIndexAnalyser(rapidjson::Value    *_root,rapidjson::Document *_doc,int _index_type,int _constraint_type,size_t _table_block_size,size_t _extern_size):root(_root),doc(_doc),index_type(_index_type),skip_level(4),constraint_type(_constraint_type),table_block_size(_table_block_size),extern_size(_extern_size){get_all();}

int get_table_name()
{
	if(root->HasMember("children") )root = &(((*root)["children"].GetArray())[0]);
	 
	 CPP_DEBUG <<"before get_table_name \n";
   //rapidjson_log( root );
   
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
	rapidjson::Value    *elemets = NULL;
	if( root->HasMember("COLUMN_LIST") )
		{
			elemets =  &(*root)["COLUMN_LIST"];
		}
		else
		{
			CPP_ERROR<<"THERE IS NO INDEX FIELDS!\n";
			return CREATE_INDEX_HAS_NO_TABLE_FIELDS;
		}
		
	for( auto &v : elemets->GetArray() )	
		{
		if( v["tag"].GetInt() != T_COLUMN_DEFINITION || !v.HasMember("children") ) 
			{
				CPP_ERROR<<" FIELD DEFINATION FAILED !\n";
				return CREATE_INDEX_FIELD_DEFINATION_FAILED;
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
				}
		elements.emplace_back( field_name );
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
		
		for( auto &v : elemets->GetArray() )	
		{
		  if( v["tag"].GetInt() != T_TABLET_BLOCK_SIZE || !v.HasMember("TABLET_BLOCK_SIZE") ) 
			{
				table_block_size = atol( v["TABLET_BLOCK_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( v["tag"].GetInt() != T_TABLET_BLOCK_SIZE || !v.HasMember("EXTERN_SIZE") ) 
			{
				extern_size = atol( v["EXTERN_SIZE"]["str_value_"].GetString() )*1024*1024; // 默认是兆
			}
			if( v["tag"].GetInt() != T_SKIP_LEVEL || !v.HasMember("SKIP_LEVEL") ) 
			{
				extern_size = atoi( v["EXTERN_SIZE"]["str_value_"].GetString() ); // 默认是兆
			}
			
			
		}
		
		
}

int get_all()
{
	int ret = 0;
	ret =get_table_name() ;
	if( !ret )return ret;
	ret =get_index_name() ;
	if( !ret )return ret;
	ret =get_index_type() ;
	if( !ret )return ret;
	ret = get_constraint_type();
	if( !ret )return ret;
	ret =get_elemets() ;
	if( !ret )return ret;
	ret =get_create_info() ;
	if( !ret )return ret;
	return 0;

}


};



#endif
