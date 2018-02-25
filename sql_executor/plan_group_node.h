/*
g++ -C -std=c++11 plan_group_node.h -w

*/

#ifndef PLAN_GROUP_NODE
#define PLAN_GROUP_NODE

#include "plan_node.h"
#include <functional>
#include <memory>
#include <vector>
#include <map>

#define PLAN_TYPE_DO_GROUPBY 								30

// groupby 函数
template<class T1,class fun_type1,class key_type = record_tuple>
shared_ptr<std::map<key_type,std::list<typename T1::value_type> > >
ret_group_by_key_stl(const T1 & container1,fun_type1 key_fun1)
{
std::shared_ptr<std::map<key_type,std::list<typename T1::value_type> > > ret(std::make_shared<std::map<key_type,std::list<typename T1::value_type> > >());

for(typename T1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type key = key_fun1(*it);
   (*ret)[key].push_back(*it);
}

  return ret;

}

//record_meta.push 原始值            x
//record_meta.push order by 的值     y
//get -> set
//key func 构造 结果集的 record_tuple
struct do_groupby_node:public plan_node
{
	
std::vector<std::string>    table_names; 
std::vector<std::string>    column_names; 
std::vector<mem_table_t *>  mem_tables; 
std::vector<std::string>    alias_names;
std::map<std::string, off_t > *table_name_dis;
std::vector<field_t> 				fields; 
record_meta                 input_meta; // 输入容器的 元数据描述
record_meta 								meta; 		  // groupby 之后自己的字段描述

std::list<generic_result>* input ;
shared_ptr<std::list<generic_result> > ret_list;	

std::shared_ptr<std::map<record_tuple,std::list<generic_result> > > ret_map;
record_tuple tuple_input ; //输入 tuple
record_tuple tuple_output; //输出 tuple
//是否是单表
int is_original;

// 为了防止循环编译依赖，暂时加的模板
do_groupby_node( 
							std::vector<std::string>    &_table_names,
							std::vector<std::string>    &_column_names,
							std::vector<std::string>    &_alias_names,
							std::vector<mem_table_t *>  &_mem_tables,
							//std::map<std::string, off_t > *_table_name_dis,
							record_meta                 &_input_meta,
							std::list<generic_result>* _input ,			
							int	_is_original,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
  									
):plan_node(_json,_Doc),	
		table_names (_table_names), 
		column_names (_column_names),
		alias_names  (_alias_names),
		mem_tables  (_mem_tables),
		//table_name_dis(_table_name_dis),
		input_meta(_input_meta),
		is_original(_is_original),
		input(_input)
{
plan_type = PLAN_TYPE_DO_GROUPBY;		

for(int i = 0; i<table_names.size(); ++i){

field_t field;
get_field(mem_tables[i] ,column_names[i], field);
fields.push_back(field);

meta.push_field( mem_tables[i] , column_names[i] );

tuple_input.meta = &_input_meta;
tuple_output.meta = &meta;
}

}
	
virtual int execute( unsigned long long  trans_no  )
{
	// 原始表无关联，无子查询
//if(is_original)
//{				
		  ret_map = ret_group_by_key_stl(*input, [&](const generic_result& v)->record_tuple {
			std::shared_ptr<generic_result> result(new generic_result);
			result->allocate(meta.size);		
			tuple_input.result = const_cast<generic_result *>(&v) ; //输入 tuple
			tuple_output.result = result.get(); //输出 tuple
			
			//设置 tuple_one
			for(int i = 0; i<table_names.size(); ++i){
			char * addr;
			tuple_input.get_field ( mem_tables[i] ,column_names[i] ,  &addr); //从输入 tuple 中析出字段的地址
			tuple_output.set_field( mem_tables[i] ,column_names[i],   addr ); //将字段值copy进输出 tuple 中
		  }
			return tuple_output;
			});
	
//}
//else{
//	
//		  ret_map = ret_group_by_key_stl(*input, [&](generic_result &v)->record_tuple{
//			std::shared_ptr<generic_result> result(new generic_result);
//			record_tuple tuple_one( &meta, result.get()  );
//			
//			//设置 tuple_one
//			for(int i = 0; i<table_names.size(); ++i){
//			field_t ori_field;
//			get_field( mem_tables[i] , column_names[i] , ori_field );
//			
//			//有别名用别名锁定位置。否则用表名
//			if( !alias_names[i].empty() ) tuple_one.set_field( mem_tables[i] ,column_names[i], v.data + (*table_name_dis)[alias_names[i]]  +ori_field.field_dis );
//			else tuple_one.set_field( mem_tables[i] ,column_names[i], v.data + (*table_name_dis)[table_names[i]]  +ori_field.field_dis );
//		  }
//			return tuple_one;
//			});
//	
//}

}

std::map<record_tuple,std::list<generic_result> >* get_ret_map()
{
	return ret_map.get();
}
virtual std::list<generic_result>* get_ret_list()
{
   if(ret_list->empty()){
		for ( auto& one : *ret_map ){
			std::list<generic_result>::iterator it = ret_list->begin();
			std::advance( it, ret_list->size() );
			ret_list->splice( it  , one.second );
			
		}
  }
  
	return ret_list.get();
}


virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}
};

















#endif 