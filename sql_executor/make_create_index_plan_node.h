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
  // 最终的执行计划
  std::list<plan_node *>	 plan_node_list;	 	

   
 
public:  
   ~make_create_index_plan(){ qia = NULL;plan_node_list.clear(); }
   make_create_index_plan(CreateIndexAnalyser * _qia) :qia(_qia){
  	init();
  	}
int init(){
return handle_create_index(
													/*in*/qia,			     //需要扫描的索引条件   
													/*in&&out*/plan_node_list //输出的执行计划    
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