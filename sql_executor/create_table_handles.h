/*
 g++ -C -w -std=c++11 crate_table_handles.h   
*/

#ifndef CREATE_TABLE_HANDLES  
#define CREATE_TABLE_HANDLES


#include "plan_create_table_node.h"



// �� normal_double_condition_list �л�ù����б�
int handl_create_table(
													/*in*/CreateTableAnalyser 					&qta,			     //��Ҫɨ�����������   
													/*out*/mem_table_t								**mem_table ,    //��Ҫ�����ı�ָ��        
													/*in&&out*/std::list<plan_node *>	&plan_node_list //�����ִ�мƻ�    
													)
{
create_table_node *node = new create_table_node(
  															qta.table_name,
  															qta.elements,
  															qta.table_block_size,
																qta.extern_size,
	  								            *( qta.root ),
  								              qta.doc);
*mem_table = node->mem_table;
plan_node_list.push_back(node);

return 0;
}



#endif 
