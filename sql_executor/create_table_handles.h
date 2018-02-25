/*
 g++ -C -w -std=c++11 crate_table_handles.h   
*/

#ifndef CREATE_TABLE_HANDLES  
#define CREATE_TABLE_HANDLES


#include "plan_create_table_node.h"



// 从 normal_double_condition_list 中获得过滤列表
int handl_create_table(
													/*in*/CreateTableAnalyser 					&qta,			     //需要扫描的索引条件   
													/*out*/mem_table_t								**mem_table ,    //需要创建的表指针        
													/*in&&out*/std::list<plan_node *>	&plan_node_list //输出的执行计划    
													)
{
create_table_node *node = new create_table_node(
  															qta.table_name,
  															qta.elements,
  															qta.table_block_size,
																qta.extern_size,
	  								            *( qta.root ),
  								              qta.doc);
plan_node_list.push_back(node);

return 0;
}



#endif 
