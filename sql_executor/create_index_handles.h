/*
 g++ -C -w -std=c++11 create_index_handls.h   
*/

#ifndef CREATE_INDEX_HANDLES  
#define CREATE_INDEX_HANDLES


#include "plan_create_hash_index_node.h"
#include "plan_create_skiplist_index_node.h"



// 从 normal_double_condition_list 中获得过滤列表
int handle_create_index(
													/*in*/CreateIndexAnalyser 			  *qia,			      //需要扫描的索引条件       
													/*in&&out*/std::list<plan_node *>	&plan_node_list //输出的执行计划    
													)
{
CPP_DEBUG<<"handle_create_index() \n"<<"qia->index_type is "<<qia->index_type<<endl;

switch(qia->index_type)
{
case T_INDEX_SKIPLIST:{
	qia->index_type = INDEX_TYPE_SKIP;
	CPP_DEBUG<<"INDEX_TYPE_SKIP \n";
	create_skiplist_index_node *node = new create_skiplist_index_node(
  															qia->table_name,qia->index_name,
  															qia->elements,
  															qia->table_block_size,
																qia->extern_size,
																qia->skip_level,
	  								            *( qia->root ),
  								              qia->doc);
plan_node_list.push_back(node);
break;
}
case T_INDEX_HASH:{
	  qia->index_type = INDEX_TYPE_HASH;
		CPP_DEBUG<<"INDEX_TYPE_HASH \n";

		create_hash_index_node *node = new create_hash_index_node(
  															qia->table_name,qia->index_name,
  															qia->elements,
  															qia->table_block_size,
																qia->extern_size,
	  								            *( qia->root ),
  								              qia->doc);
plan_node_list.push_back(node);
break;

	
	
}


}
return 0;
}



#endif 
