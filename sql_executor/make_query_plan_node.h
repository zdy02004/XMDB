/*
 g++ -C -w -std=c++11 make_plan_node.h   
*/

#ifndef MAKE_QUERY_PLAN  
#define MAKE_QUERY_PLAN

#define MAKE_QUERY_PLAN_NULL_QA_PTR  480

#include "query_handles.h" 

class physical_query_plan
{
	QueryAnalyser * qa;	
	// 字段描述
	std::map<std::string,std::set<std::string> > aggregat_fields;   //(表名,用于聚合的字段名)
	std::map<std::string,std::set<std::string> > raw_fields;        //(表名,普通字段名)
	std::map<std::string,std::set<std::string> > oper_fields;       //(表名,普通操作字段名)
	std::map<std::string,std::set<std::string> > nomal_func_fields; //(表名,非聚合函数字段名)
	std::map<std::string,std::set<std::string> > projection_fields; //(表名,投影字段名)
	std::map<std::string,mem_table_t *         > mem_table_ptr_map;	//(表名,表指针)
	// 条件描述
  std::map<std::string,std::list<normal_single_condition_struct> > normal_single_condition_map;				//(表名,单条件列表)
  std::map<std::string,std::list<normal_double_condition_struct> > normal_double_condition_map;				//(表名,双条件列表)
  std::map<std::string,std::list<normal_double_condition_struct> > normal_index_double_condition_map;	//(表名,索引双条件列表)										
	std::map<std::string,std::list<join_eq_condition_struct      > > join_eq_condition_map;  				    // 关联条件
	std::map<std::string,std::list<const_condition_struct        > > const_condition_map;							  //(表名,常数条件列表)	
	std::map<std::string,std::set<std::string                    > > condition_fields_map;              //(表名,条件字段列表)	
	// 字段汇总															
	std::map<std::string,std::set<std::string                    > > scan_fields_map;                   // 需要扫描的字段  
  std::map<std::string,record_meta>						                     scan_metas_map;										// 需要扫描的字段元信息 
 	std::map<std::string,std::set<std::string> >                     result_fields;                     // 结果集的投影字段 
 	std::map<std::string,record_meta >                               result_metas_map;                  // 结果集的字段元信息 
	//扫描结果集
 	std::map<std::string,std::list<generic_result>*                > table_scan_ret;                   // 对应每个单表初步扫描后的结果集
 
  // join 和 group by 中间数据结构
  std::vector<join_eq_condition_struct>                            join_eq_condition_only_inner_join_list;// 对排序后的关联关系，去除 semi_join 和 anti_join 的结果  	  
  record_meta                                                      join_meta;	                            //join 后的元数据描述  	
  record_meta                                                      *groupby_meta;                         //group_by 后的元数据描述  	
  
  //投影用到的数据结构
 	std::vector<fun_oper *>                                          projection_fun_oper_lists; 				// 投影 oper 列表 
	record_meta							                                         projection_meta;  									// 投影元数据描述 
	
  // 分阶段执行计划    
  std::map<std::string,std::list<plan_node *> >						         plan_node_scan_list_map ;        // 扫描执行计划映射,分拆是因为可以大粒度并行  表名，扫描执行计划  
  std::list<plan_node *>																					 plan_node_join_group_list;				// join_group 的执行计划，无法大粒度并行
  //最终的执行计划
  std::list<plan_node *>																					 *final_plan_node_list;	 	

public:  
  physical_query_plan(QueryAnalyser * _qa) 	:qa(_qa){
  	if ( 
  	!init() && 
  	!make_scan_plan() &&
  	!make_join_group_plan() &&
  	!make_orderby_plan()  &&
  	!make_projection_plan()
  	){}
  	
  	}
   	
// 初始化各成员变量
int init()
{
	if( NULL == qa )
		{
			ERROR("MAKE_QUERY_PLAN_NULL_QA_PTR\n");
			return MAKE_QUERY_PLAN_NULL_QA_PTR;
		}
	CPP_DEBUG<<"begin init() \n "<<std::endl;
	
	//找出单表中条件用到的字段												
	int ret = get_table_conditions(
														/*in*/  qa,										
														/*out*/ mem_table_ptr_map, 	      					//(表名,表指针)
	  												/*out*/ normal_single_condition_map,				//(表名,单条件列表)
	  												/*out*/ normal_double_condition_map,				//(表名,双条件列表)
	  												/*out*/ normal_index_double_condition_map,	//(表名,索引双条件列表)										
														/*out*/ join_eq_condition_map,  				    // 关联条件
														/*out*/ const_condition_map,							  //(表名,常数条件列表)	
														/*out*/ condition_fields_map	              //(表名,条件字段列表)	
	);
    if( ret != 0 && ret != NOT_INDEX_FIELD )
  	{
  		ERROR("end get_single_table_conditions，err is %d \n",ret);
  		return ret;
  	}
	//找出每个表中投影用到的字段
	ret = get_projection_fields(
														/*in*/  qa,										
														/*out*/ aggregat_fields ,  //(表名,用于聚合的字段名)
														/*out*/ raw_fields ,       //(表名,普通字段名)
														/*out*/ oper_fields ,      //(表名,普通操作字段名)
														/*out*/ nomal_func_fields, //(表名,非聚合函数字段名)
													  /*out*/ projection_fields  //(表名,非聚合函数字段名)
													); 
	if( ret!= 0 )
		{
			ERROR("get_projection_fields err is %d \n",ret);
			return ret;
		}	
		// 获得一个表需要的所有的字段（ 投影字段 + 条件字段 ）
	ret = get_table_scan_fields(
																	/*in*/ qa,										
																	/*in*/ projection_fields, 	 // 投影字段
																	/*in*/ condition_fields_map, // 条件字段
																	/*out*/scan_fields_map    	 // 需要扫描的字段
	);
	if( ret!= 0 )
		{
			ERROR("get_table_scan_fields err is %d \n",ret);
			return ret;
		}	

	// 获得一个表扫描后的所有的字段的元数据描述
	ret = get_talbe_scan_meta(
													/*in*/ qa,										
													/*in*/ scan_fields_map,  // 需要扫描的字段
													/*out*/scan_metas_map    // 各表扫描后的元数据描述
	
	);
		if( ret!= 0 )
		{
			ERROR("get_talbe_scan_meta err is %d \n",ret);
			return ret;
		}	
		
		// 获得一个表结果集的投影字段
	ret = get_table_result_fields(
																	/*in*/ qa,										
																	/*in*/ projection_fields, 	 // 投影字段
																	/*out*/result_fields    	   ///结果集的投影字段 
	);
	if( ret!= 0 )
	{
		ERROR("get_table_result_fields err is %d \n",ret);
		return ret;
	}	
	// 获得一个表结果集的的元数据描述
	ret = get_talbe_scan_meta(
													/*in*/ qa,										
													/*in*/ result_fields,  // 需要扫描的字段
													/*out*/result_metas_map    // 各表扫描后的元数据描述
	
	);
		if( ret!= 0 )
		{
			ERROR("get_talbe_scan_meta err is %d \n",ret);
			return ret;
		}	
	
	CPP_DEBUG<<"end init() \n "<<std::endl;

	if( ret!= 0 )return ret;
	return 0;
}

//构造扫描执行计划	
int make_scan_plan()
{	
CPP_DEBUG<<"begin make_scan_plan() \n "<<std::endl;
for(std::map<std::string,mem_table_t * >::iterator iter = mem_table_ptr_map.begin(); iter != mem_table_ptr_map.end();  ++iter  )
{
mem_table_t *mem_table = iter->second;
std::string table_name = iter->first;

CPP_DEBUG<<" for scan_fields_map["<<table_name<<"].size()="<<scan_fields_map[table_name].size()<<std::endl;

// 扫描执行计划
std::list<plan_node *>	plan_node_scan_list ;	

CPP_DEBUG<<"handl_const_con() \n "<<std::endl;
// 判断常量条件，为假则快速中断
int ret = handl_const_con(
														/*in*/mem_table , 
														/*in*/const_condition_map[table_name] //需要扫描的非索引条件
												 );
if( ret!= 0 )
	{
		ERROR("handl_const_con err is %d \n",ret);
		return ret;
	}

if( !normal_index_double_condition_map[table_name].empty() )
{
CPP_DEBUG<<"handl_double_con_index() \n "<<std::endl;												
// 双条件索引扫描
ret =  handl_double_con_index(/*in*/mem_table, 												              //需要扫描的表
															/*in*/normal_index_double_condition_map[table_name],	//需要扫描的索引条件
															/*in*/normal_double_condition_map[table_name],   			//需要扫描的非索引条件
															/*in*/condition_fields_map[table_name],               //条件字段列表
										     /*in&&out*/plan_node_scan_list                             //输出的执行计划
													  );
}
else
{	
CPP_DEBUG<<"handl_double_con_normal() \n "<<std::endl;																							
// 双条件原表扫描
ret =  handl_double_con_normal(
														/*in*/mem_table , 
														/*in*/normal_double_condition_map[table_name],   				//需要扫描的非索引条件
														/*in*/condition_fields_map[table_name],                 //条件字段列表
											/*in&&out*/plan_node_scan_list											       	  //输出的执行计划
													);
}
if( ret!= 0 )
	{
		ERROR("handl_double_con_ err is %d \n",ret);
		return ret;
	}

plan_node_scan_list_map[table_name] = plan_node_scan_list ;
table_scan_ret[table_name]          = (*(plan_node_scan_list.rbegin()))->get_ret_list();												

}

CPP_DEBUG<<"end make_scan_plan() \n "<<std::endl;
return 0;


}

int make_join_group_plan()
{
	CPP_DEBUG<<"begin make_join_group_plan() \n "<<std::endl;

	//对关联条件进行排序，并按顺序生成节点
int ret = handl_join_condtions(
													/*in*/ qa,	
													/*in*/ table_scan_ret,						        		 	// 对应每个单表初步扫描后的结果集
													/*in*/ scan_metas_map,						        			// 需要扫描出的字段元数据
												 /*out*/ join_eq_condition_only_inner_join_list,  // 对排序后的关联关系，去除 semi_join 和 anti_join 的结果
										     /*out*/ join_meta,																// join后的字段元信息
										 /*in&&out*/ plan_node_join_group_list
												);
if( ret!= 0 )
	{
		ERROR("handl_join_condtions err is %d\n",ret);
		return ret;
	}
CPP_DEBUG<<"end make_join_group_plan() \n "<<std::endl;
	
// 处理groupby
ret = handl_groupby(
									/*in*/  qa,	
									/*in*/	scan_fields_map,       		 								// 需要扫描出的字段
									/*in*/  join_eq_condition_only_inner_join_list,   // 对排序后的关联关系，去除 semi_join 和 anti_join 的结果
									/*in*/  scan_metas_map,						        			  // 需要扫描出的字段元数据
									/*out*/ &groupby_meta,         				  				  // group_by 后的元数据描述
									/*out*/	plan_node_join_group_list
								  );
CPP_DEBUG<<"end make_join_group_plan() \n "<<std::endl;
								  
if( ret!= 0 )
	{
		ERROR("handl_groupby err is %d\n",ret);
		return ret;
	}return 0;
								  
}

int make_orderby_plan()
{

	CPP_DEBUG<<"begin make_orderby_plan() \n "<<std::endl;

	int ret = 0 ;
	int has_join_goupby = 0;
	
	if( !qa->order_target.empty()   ){has_join_goupby = 1;}
  else if( !qa->join_conditions.empty() ){has_join_goupby = 1;}
	
	if(has_join_goupby){
	ret = handl_orderby(
									/*in*/  qa,	
									/*in*/  join_meta, // 各表扫描后的元数据描述
									/*out*/	plan_node_join_group_list
								  );
	}
	else {// 单表无join_groupby
		
		ret = handl_orderby(
									/*in*/  qa,	
									/*in*/  scan_metas_map.begin()->second,         // 单表元数据描述
									/*out*/	plan_node_scan_list_map.begin()->second // 单表的执行计划
								  );
	}

	CPP_DEBUG<<"end make_orderby_plan() \n "<<std::endl;
	return ret;
}


int make_projection_plan()
{
	CPP_DEBUG<<"begin make_projection_plan() \n "<<std::endl;

	int ret = 0;
	
	// 结果集 元数据描述，在有join 的时候是 join, 无join的时候是 单表的扫描元数据描述
	record_meta  *input_meta;
	if(qa->is_join)input_meta = &join_meta;
	else input_meta = &( result_metas_map.begin()->second );

   if( !plan_node_join_group_list.empty() )DEBUG("final_plan_node_list = &plan_node_join_group_list \n");
	 else                                    DEBUG("final_plan_node_list = &(plan_node_scan_list_map.begin()->second\n");


	 if( !plan_node_join_group_list.empty() )final_plan_node_list = &plan_node_join_group_list;
	 else                                   final_plan_node_list = &(plan_node_scan_list_map.begin()->second);
	
	ret = handl_projection(
									/*in*/  qa,	
									/*in*/  *input_meta,	//结果集的元数据描述
									/*out*/ projection_fun_oper_lists ,//投影 oper 列表 
									/*out*/	projection_meta,  					//投影元数据描述 
									/*out*/	*final_plan_node_list						 
								  );
	if(ret)
		{
		 CPP_ERROR<<" handl_projection failed! err is "<<ret<<std::endl;	
		 return ret;
		}
	CPP_DEBUG<<"end make_projection_plan() \n "<<std::endl;
	return 0;
}


int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	for (auto &v : *final_plan_node_list )
	{
		ret = v->execute(trans_no);
		if(ret)
			{
				ERROR("execute sql failed !  and err is %d \n",ret);
				return ret;
			}
	}
	return 0;
}

};


#endif 