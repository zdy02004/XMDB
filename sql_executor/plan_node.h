//g++ -C -std=c++11 plan_node.h -w

#ifndef PLAN_NODE
#define PLAN_NODE

#define PLAN_TYPE_EQ_FIELTER								11
#define PLAN_TYPE_ET_FIELTER								12
#define PLAN_TYPE_GE_FIELTER								13
#define PLAN_TYPE_GT_FIELTER								14
#define PLAN_TYPE_LE_FIELTER								15
#define PLAN_TYPE_LT_FIELTER								16
#define PLAN_TYPE_NE_FIELTER								17
#define PLAN_TYPE_BTW_FIELTER								18


#include "../SQL/sql_parser/rapidjson/document.h"
#include "record_tuple.h"
#include <list>

//#include "ops.hpp"
//#include "func_help.hpp"
//#include "../mem_date_index_ctl/mem_table_mvcc_op.h"
//#include "../mem_date_index_ctl/mem_index_no_manager.h"
//#include "index_scan_Addr.hpp"

struct plan_node
{
std::string plan_name;
rapidjson::Value json;
rapidjson::Document  *Doc;

int plan_type;
int oper_type;
size_t ret_size;

plan_node(rapidjson::Value& _json,rapidjson::Document * _Doc):Doc(_Doc)
{
		json.CopyFrom( _json,Doc->GetAllocator() );
		oper_type = 0;
}

int get_plan_type() {return plan_type;}
int set_oper_type(int _oper_type ) { oper_type =  _oper_type; }

virtual void make_json() = 0;
virtual std::string to_sring () = 0;
virtual int execute( unsigned long long  trans_no  ) = 0;
virtual std::list<generic_result>* get_ret_list() 
{
	
	return (std::list<generic_result>*)NULL;
}
};







#endif 