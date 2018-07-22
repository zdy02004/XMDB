/*
g++ -C -std=c++11 plan_projection_node.h -w

*/
#ifndef PLAN_PROJECTION_NODE
#define PLAN_PROJECTION_NODE

#include "fun_oper.h"
#include "plan_node.h"

#include <memory>


#define PLAN_TYPE_DO_PROJECTION							60


struct do_projection_node:public plan_node
{
// 工具类	
record_tuple input_tuple;
record_tuple output_tuple;

record_meta  input_meta;
record_meta  projection_meta;

std::vector<fun_oper *>  projection_fun_oper_lists ;//投影 oper 列表 

std::list<generic_result>*  input_list ;
shared_ptr<std::list<generic_result> > ret_list;


// 为了防止循环编译依赖，暂时加的模板
do_projection_node( 
							record_meta&  _input_meta ,
							record_meta&  _projection_meta , //投影元数据描述
							std::vector<fun_oper *>&  _projection_fun_oper_lists, //投影算子结构vector
							std::list<generic_result>*  _input_list ,							//结果集
							shared_ptr<std::list<generic_result> > _ret_list,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc
):plan_node(_json,_Doc),	
		input_meta (_input_meta), 
		projection_meta (_projection_meta),
		projection_fun_oper_lists(_projection_fun_oper_lists),
		input_list(_input_list),
		ret_list( _ret_list )
{
	
plan_type = PLAN_TYPE_DO_PROJECTION;		
input_tuple.meta = &input_meta;
output_tuple.meta = &projection_meta;
}
	
virtual int execute( unsigned long long  trans_no  )
{
 DEBUG("do_projection_node execute begin ============={ \n");
 for(auto &row : *input_list ){			
			generic_result result;
			DEBUG("result.allocate( %ld ) \n", projection_meta.size );

			result.allocate( projection_meta.size );
			
			input_tuple.result = &row ;
			output_tuple.result = &result ;
			
			for( auto &v: projection_fun_oper_lists )
			{
				  union_value uv= v->eval( &input_meta , &row );;
					switch(v->tag)
					{
					case FIELD_TYPE_LONGLONG: {
					DEBUG("case FIELD_TYPE_LONGLONG \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.longlong_value)) );
					break;
					}
					
					case FIELD_TYPE_FLOAT: {
					DEBUG("case FIELD_TYPE_FLOAT \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.float_value)) );
					break;
					}
					
					case FIELD_TYPE_DOUBLE: {
					DEBUG("case FIELD_TYPE_DOUBLE \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.double_value)) );
					break;
					}
					
					case FIELD_TYPE_DATE: {
					DEBUG("case FIELD_TYPE_DATE \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.long_value)) );
					break;
					}
					
					case FIELD_TYPE_SHORT: {
					DEBUG("case FIELD_TYPE_SHORT \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.short_value)) );
					break;
					}
					
					case FIELD_TYPE_STR: {
					DEBUG("case FIELD_TYPE_STR \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.str_value)) );
					break;
					}
					
					case FIELD_TYPE_INT: {
					DEBUG("case FIELD_TYPE_INT \n");
					output_tuple.set_field(  v->alias_name, (char *)(&(uv.int_value)) );
					break;
					}
					}
			}
			
			DEBUG("ret_list->push_back(result) \n");
			ret_list->push_back(result);
		}
		
 DEBUG("do_projection_node execute end =============} \n");
 return 0;
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