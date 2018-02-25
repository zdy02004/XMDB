/*
 g++ -C -w -std=c++11 make_create_table_plan_node.h   
*/

#ifndef MAKE_CREATE_TABLE_PLAN  
#define MAKE_CREATE_TABLE_PLAN

#define MAKE_CREATE_TABLE_PLAN_NULL_QA_PTR  490

#include "create_table_handles.h" 

class make_create_table_plan
{
	CreateTableAnalyser * qa;	
  //最终的执行计划
  std::list<plan_node *>	 plan_node_list;	 	
  mem_table_t		*mem_table;
 
public:  
   ~make_create_table_plan(){ qa = NULL;mem_table = NULL;plan_node_list.clear(); }
  make_create_table_plan(CreateTableAnalyser * _qa) 	:qa(_qa){
  	init();
  	}
int init(){
return handl_create_table(
													/*in*/     *qa,			     //需要扫描的索引条件   
													/*out*/    &mem_table,    //需要创建的表指针        
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