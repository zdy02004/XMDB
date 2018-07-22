/*
 g++ -C -w -std=c++11 insert_one_table_handles.h   
*/

#ifndef INSERT_ONE_TABLE_HANDLES  
#define INSERT_ONE_TABLE_HANDLES


#include "plan_insert_one_table_node.h"


// �� normal_double_condition_list �л�ù����б�
int handl_insert_one_table(
													/*in*/InsertTableAnalyser 					&ita,			     //��Ҫɨ�����������   
													/*in&&out*/std::list<plan_node *>	&plan_node_list //�����ִ�мƻ�    
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
