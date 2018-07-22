/*
 g++ -C -w -std=c++11 make_create_index_plan_node.h   
*/

#ifndef MAKE_CREATE_INDEX_PLAN  
#define MAKE_CREATE_INDEX_PLAN

#define MAKE_CREATE_INDEX_PLAN_NULL_QA_PTR  590

#include "create_index_handles.h" 

class make_create_index_plan
{
	CreateIndexAnalyser * qia;	
  // ���յ�ִ�мƻ�
  std::list<plan_node *>	 plan_node_list;	 	

   
 
public:  
   ~make_create_index_plan(){ qia = NULL;plan_node_list.clear(); }
   make_create_index_plan(CreateIndexAnalyser * _qia) :qia(_qia){
  	init();
  	}
int init(){
return handle_create_index(
													/*in*/qia,			     //��Ҫɨ�����������   
													/*in&&out*/plan_node_list //�����ִ�мƻ�    
													);
												}
												
void execute()
{
	
	for(auto &v : plan_node_list )
	{
		v->execute(1);
	}
		
}

};


#endif 