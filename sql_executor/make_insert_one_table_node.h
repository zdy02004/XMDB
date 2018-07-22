/*
 g++ -C -w -std=c++11 make_insert_one_table_node.h   
*/

#ifndef MAKE_INSERT_ONE_TABLE_PLAN  
#define MAKE_INSERT_ONE_TABLE_PLAN

#define MAKE_INSERT_ONE_TABLE_PLAN_NULL_QA_PTR  890

#include "insert_one_table_handles.h" 

class make_insert_one_table_plan
{
	InsertTableAnalyser * ita;	
  // ���յ�ִ�мƻ�
  std::list<plan_node *>	 plan_node_list;	 	

   
 
public:  
   ~make_insert_one_table_plan(){ ita = NULL;plan_node_list.clear(); }
   make_insert_one_table_plan(InsertTableAnalyser * _ita) :ita(_ita){
  	init();
  	}
int init(){
return handl_insert_one_table(
													/*in*/*ita,			     //��Ҫɨ�����������   
													/*in&&out*/plan_node_list //�����ִ�мƻ�    
													);
												}
												
void execute( unsigned long long  Tn )
{
	
	for(auto &v : plan_node_list )
	{
		v->execute(Tn);
	}
		
}

};


#endif 