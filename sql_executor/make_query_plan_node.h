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
	// �ֶ�����
	std::map<std::string,std::set<std::string> > aggregat_fields;   //(����,���ھۺϵ��ֶ���)
	std::map<std::string,std::set<std::string> > raw_fields;        //(����,��ͨ�ֶ���)
	std::map<std::string,std::set<std::string> > oper_fields;       //(����,��ͨ�����ֶ���)
	std::map<std::string,std::set<std::string> > nomal_func_fields; //(����,�ǾۺϺ����ֶ���)
	std::map<std::string,std::set<std::string> > projection_fields; //(����,ͶӰ�ֶ���)
	std::map<std::string,mem_table_t *         > mem_table_ptr_map;	//(����,��ָ��)
	// ��������
  std::map<std::string,std::list<normal_single_condition_struct> > normal_single_condition_map;				//(����,�������б�)
  std::map<std::string,std::list<normal_double_condition_struct> > normal_double_condition_map;				//(����,˫�����б�)
  std::map<std::string,std::list<normal_double_condition_struct> > normal_index_double_condition_map;	//(����,����˫�����б�)										
	std::map<std::string,std::list<join_eq_condition_struct      > > join_eq_condition_map;  				    // ��������
	std::map<std::string,std::list<const_condition_struct        > > const_condition_map;							  //(����,���������б�)	
	std::map<std::string,std::set<std::string                    > > condition_fields_map;              //(����,�����ֶ��б�)	
	// �ֶλ���															
	std::map<std::string,std::set<std::string                    > > scan_fields_map;                   // ��Ҫɨ����ֶ�  
  std::map<std::string,record_meta>						                     scan_metas_map;										// ��Ҫɨ����ֶ�Ԫ��Ϣ 
 	
	//ɨ������
 	std::map<std::string,std::list<generic_result>*                > table_scan_ret;                   // ��Ӧÿ���������ɨ���Ľ����
 
  // join �� group by �м����ݽṹ
  std::vector<join_eq_condition_struct>                            join_eq_condition_only_inner_join_list;// �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��  	  
  record_meta                                                      join_meta;	                            //join ���Ԫ��������  	
  record_meta                                                      *groupby_meta;                         //group_by ���Ԫ��������  	
  
  //ͶӰ�õ������ݽṹ
 	std::vector<fun_oper *>                                          projection_fun_oper_lists; 				// ͶӰ oper �б� 
	record_meta							                                         projection_meta;  									// ͶӰԪ�������� 
	
  // �ֽ׶�ִ�мƻ�    
  std::map<std::string,std::list<plan_node *> >						         plan_node_scan_list_map ;        // ɨ��ִ�мƻ�ӳ��,�ֲ�����Ϊ���Դ����Ȳ���  ������ɨ��ִ�мƻ�  
  std::list<plan_node *>																					 plan_node_join_group_list;				// join_group ��ִ�мƻ����޷������Ȳ���
  //���յ�ִ�мƻ�
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
   	
// ��ʼ������Ա����
int init()
{
	if( NULL == qa )return MAKE_QUERY_PLAN_NULL_QA_PTR;
	//�ҳ�ÿ������ͶӰ�õ����ֶ�
	int ret = get_projection_fields(
														/*in*/  qa,										
														/*out*/ aggregat_fields ,  //(����,���ھۺϵ��ֶ���)
														/*out*/ raw_fields ,       //(����,��ͨ�ֶ���)
														/*out*/ oper_fields ,      //(����,��ͨ�����ֶ���)
														/*out*/ nomal_func_fields, //(����,�ǾۺϺ����ֶ���)
													  /*out*/ projection_fields  //(����,�ǾۺϺ����ֶ���)
													); 
	if( ret!= 0 )return ret;
	//�ҳ������������õ����ֶ�												
	ret = get_table_conditions(
														/*in*/  qa,										
														/*out*/ mem_table_ptr_map, 	      					//(����,��ָ��)
	  												/*out*/ normal_single_condition_map,				//(����,�������б�)
	  												/*out*/ normal_double_condition_map,				//(����,˫�����б�)
	  												/*out*/ normal_index_double_condition_map,	//(����,����˫�����б�)										
														/*out*/ join_eq_condition_map,  				    // ��������
														/*out*/ const_condition_map,							  //(����,���������б�)	
														/*out*/ condition_fields_map	              //(����,�����ֶ��б�)	
	);
	if( ret!= 0 )return ret;
	// ���һ������Ҫ�����е��ֶΣ� ͶӰ�ֶ� + �����ֶ� ��
	ret = get_talbe_scan_fields(
																	/*in*/ qa,										
																	/*in*/ projection_fields, 	 // ͶӰ�ֶ�
																	/*in*/ condition_fields_map, // �����ֶ�
																	/*out*/scan_fields_map    	 // ��Ҫɨ����ֶ�
	);
	if( ret!= 0 )return ret;
	// ���һ����ɨ�������е��ֶε�Ԫ��������
	ret = get_talbe_scan_meta(
													/*in*/ qa,										
													/*in*/ scan_fields_map,  // ��Ҫɨ����ֶ�
													/*out*/scan_metas_map    // ����ɨ����Ԫ��������
	
	);
	if( ret!= 0 )return ret;
	return 0;
}

//����ɨ��ִ�мƻ�	
int make_scan_plan()
{	

for(std::map<std::string,mem_table_t * >::iterator iter = mem_table_ptr_map.begin(); iter != mem_table_ptr_map.end();  ++iter  )
{

mem_table_t *mem_table = iter->second;
std::string table_name = iter->first;

// ɨ��ִ�мƻ�
std::list<plan_node *>	plan_node_scan_list ;	
	
// �жϳ���������Ϊ��������ж�
int ret = handl_const_con(
														/*in*/mem_table , 
														/*in*/const_condition_map[table_name] //��Ҫɨ��ķ���������
												 );
if( ret!= 0 )return ret;

if( !normal_index_double_condition_map[table_name].empty() )
{											
// ˫��������ɨ��
ret =  handl_double_con_index(/*in*/mem_table, 												              //��Ҫɨ��ı�
															/*in*/normal_index_double_condition_map[table_name],	//��Ҫɨ�����������
															/*in*/normal_double_condition_map[table_name],   			//��Ҫɨ��ķ���������
															/*in*/scan_fields_map[table_name],                    //ɨ������ֶ��б�
										     /*in&&out*/plan_node_scan_list                             //�����ִ�мƻ�
													  );
}
else
{												
// ˫����ԭ��ɨ��
ret =  handl_double_con_normal(
														/*in*/mem_table , 
														/*in*/normal_double_condition_map[table_name],   				//��Ҫɨ��ķ���������
														/*in*/scan_fields_map[table_name],                      //ɨ������ֶ��б�
											/*in&&out*/plan_node_scan_list											       	  //�����ִ�мƻ�
													);
}
if( ret!= 0 )return ret;

													
plan_node_scan_list_map[table_name] = plan_node_scan_list ;
table_scan_ret[table_name]          = (*(plan_node_scan_list.rbegin()))->get_ret_list();
return 0;
}

}

int make_join_group_plan()
{
	//�Թ��������������򣬲���˳�����ɽڵ�
int ret = handl_join_condtions(
													/*in*/ qa,	
													/*in*/ table_scan_ret,						        			// ��Ӧÿ���������ɨ���Ľ����
													/*in*/ scan_metas_map,						        			// ��Ҫɨ����ֶ�Ԫ��Ϣ
												 /*out*/ join_eq_condition_only_inner_join_list,  // �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
										     /*out*/ join_meta,																// join����ֶ�Ԫ��Ϣ
										 /*in&&out*/ plan_node_join_group_list
												);
if( ret!= 0 )return ret;
	
// ����groupby
ret = handl_groupby(
									/*in*/  qa,	
									/*in*/	scan_fields_map,       		 								// ��Ҫɨ������ֶ�
									/*in*/  join_eq_condition_only_inner_join_list,   // �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
									/*in*/  scan_metas_map,         				  				// ����ɨ����Ԫ��������
									/*out*/ &groupby_meta,         				  				  //group_by ���Ԫ��������
									/*out*/	plan_node_join_group_list
								  );
if( ret!= 0 )return ret;
return 0;
								  
}

int make_orderby_plan()
{
	int ret = 0 ;
	int has_join_goupby = 0;
	
	if( !qa->order_target.empty()   ){has_join_goupby = 1;}
  else if( !qa->join_conditions.empty() ){has_join_goupby = 1;}
	
	if(has_join_goupby){
	ret = handl_orderby(
									/*in*/  qa,	
									/*in*/  join_meta, // ����ɨ����Ԫ��������
									/*out*/	plan_node_join_group_list
								  );
	}
	else {// ������join_groupby
		
		ret = handl_orderby(
									/*in*/  qa,	
									/*in*/  scan_metas_map.begin()->second, // ����Ԫ��������
									/*out*/	plan_node_scan_list_map.begin()->second // �����ִ�мƻ�
								  );
	}
	
	return ret;
}


int make_projection_plan()
{
	int ret = 0;
	
	// ����� Ԫ��������������join ��ʱ���� join, ��join��ʱ���� �����ɨ��Ԫ��������
	record_meta  *input_meta;
	if(qa->is_join)input_meta = &join_meta;
	else input_meta = &( scan_metas_map.begin()->second );

	 if( plan_node_join_group_list.empty() )final_plan_node_list = &plan_node_join_group_list;
	 else                                   final_plan_node_list = &(plan_node_scan_list_map.begin()->second);
	
	ret = handl_projection(
									/*in*/  qa,	
									/*in*/  *input_meta,	//�������Ԫ��������
									/*out*/ projection_fun_oper_lists ,//ͶӰ oper �б� 
									/*out*/	projection_meta,  					//ͶӰԪ�������� 
									/*out*/	*final_plan_node_list						 
								  );
	if(!ret)
		{
		 CPP_ERROR<<" handl_projection failed! \n";	
		 return ret;
		}
	return 0;
}

};


#endif 