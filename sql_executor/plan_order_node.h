/*
g++ -C -std=c++11 plan_order_node.h -w

*/

#ifndef PLAN_ORDERBY_NODE
#define PLAN_ORDERBY_NODE

#include "plan_node.h"
#include <functional>
#include <memory>
#include <vector>
#include <map>

#define PLAN_TYPE_DO_ORDERBY 								40


//record_meta.push 原始值            x
//record_meta.push order by 的值     y
//get -> set
//key func 构造 结果集的 record_tuple
struct do_orderby_node:public plan_node
{
	
std::vector<std::string>    table_names; 
std::vector<std::string>    column_names; 
std::vector<mem_table_t *>  mem_tables; 
std::vector<std::string>    alias_names;
std::map<std::string, off_t > *table_name_dis;
std::vector<field_t> 				fields; 
record_meta                 input_meta; // 输入容器的 元数据描述
record_meta 								meta; 		  // orderby 自己的字段描述

std::list<generic_result>* input ;
shared_ptr<std::list<generic_result> > ret_list;	

record_tuple tuple_input ; //输入 tuple
//是否是单表
int is_original;

// 为了防止循环编译依赖，暂时加的模板
do_orderby_node( 
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
plan_type = PLAN_TYPE_DO_ORDERBY;		

for(int i = 0; i<table_names.size(); ++i){

field_t field;
get_field(mem_tables[i] ,column_names[i], field);
fields.push_back(field);

meta.push_field( mem_tables[i] , column_names[i] );

tuple_input.meta = &_input_meta;
}

}
	
virtual int execute( unsigned long long  trans_no  )
{
	// 原始表无关联，无子查询
			record_tuple in_a,in_b;
			in_a.meta = &input_meta;
			in_b.meta = &input_meta;
			
			record_tuple orderby_a,orderby_b;
			orderby_a.meta = &meta;
			orderby_b.meta = &meta;
      
			
			ret_list->sort([&](const generic_result& a,const generic_result& b)->bool {
			
				
			in_a.result = const_cast<generic_result *>(&a) ; //输入 tuple
			in_b.result = const_cast<generic_result *>(&b) ;  //输出 tuple
			
			//设置 tuple_one
			for(int i = 0; i<table_names.size(); ++i){
			char * addr1;
			char * addr2;
			in_a.get_field ( mem_tables[i] ,column_names[i] ,  &addr1); //从输入 tuple 中析出字段的地址
			in_b.get_field ( mem_tables[i] ,column_names[i] ,  &addr2); //从输入 tuple 中析出字段的地址

			orderby_a.set_field( mem_tables[i] ,column_names[i],   addr1 ); //将字段值copy进输出 tuple 中
		  orderby_b.set_field( mem_tables[i] ,column_names[i],   addr2 ); //将字段值copy进输出 tuple 中

		  }
			return orderby_a < orderby_b;
			});

}


virtual std::list<generic_result>* get_ret_list()
{
  
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