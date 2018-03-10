/*
 g++ -C -w -std=c++11 insert_one_table_handles.h   
*/

#ifndef INSERT_ONE_TABLE_HANDLES  
#define INSERT_ONE_TABLE_HANDLES


#include "plan_insert_one_table_node.h"


// 从 normal_double_condition_list 中获得过滤列表
int handl_insert_one_table(
													/*in*/InsertTableAnalyser 					&ita,			     //需要扫描的索引条件   
													/*in&&out*/std::list<plan_node *>	&plan_node_list //输出的执行计划    
													)
{
plan_insert_one_table_node *node = new plan_insert_one_table_node(
  															ita.table_name,
  															ita.elements,
  															ita.values,
	  								            *( ita.root ),
  								              ita.doc);
plan_node_list.push_back(node);

return 0;
}



#endif 
