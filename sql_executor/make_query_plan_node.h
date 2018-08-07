/*
 g++ -C -w -std=c++11 make_query_plan_node.h   
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
	std::map<std::string,std::list<normal_oper_condition_struct  > > normal_oper_condition_map;  		    //(����,���������б�)
	std::map<std::string,std::list<const_condition_struct        > > const_condition_map;							  //(����,���������б�)	
	std::map<std::string,std::list<join_eq_condition_struct      > > join_eq_condition_map;						  //(����,���������б�)	
	std::map<std::string,std::set<std::string                    > > condition_fields_map;              //(����,�����ֶ��б�)	
	// �ֶλ���															
	std::map<std::string,std::set<std::string                    > > scan_fields_map;                   // ��Ҫɨ����ֶ�  
  std::map<std::string,record_meta>						                     scan_metas_map;										// ��Ҫɨ����ֶ�Ԫ��Ϣ 
 	std::map<std::string,std::set<std::string> >                     result_fields;                     // �������ͶӰ�ֶ� 
 	std::map<std::string,record_meta >                               result_metas_map;                  // ��������ֶ�Ԫ��Ϣ 
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
  std::map<std::string,plan_node * >						                   plan_node_scan_list_map ;        // ɨ��ִ�мƻ�ӳ��,�ֲ�����Ϊ���Դ����Ȳ���  ������ɨ��ִ�мƻ�  
  // ɨ��ִ�мƻ�
  std::list<plan_node *>																					 plan_node_scan_list ;	
  // join_group ��ִ�мƻ����޷������Ȳ���
  std::list<plan_node *>																					 plan_node_join_group_list;	
  				
  //���յ�ִ�мƻ�
  std::list<plan_node *>																					 *final_plan_node_list;	 	
  
  //����ɨ���õ��ĵ�ַ����set
  finded_Addr_t 																					 			    finded_Addr;
public:  
  physical_query_plan(QueryAnalyser * _qa) 	:qa(_qa){
  	if ( 
  	 !init() 
  	//&& !make_scan_plan() 
  	//&& !make_join_plan() &&
  	//!make_group_plan() &&
  	//!make_orderby_plan()  &&
  	//!make_projection_plan()
  	){
  		int err = 0;
  		
  		if( qa->from_list )err = make_scan_plan();
  		else {
  				DEBUG("qa->from_list is NULL\n");
  		}
  		if(err)ERROR("make_scan_plan() err is %d\n",err);
  			  		
  		if(qa->join_conditions.size() > 0 )err = make_join_plan();
  		else {
  				DEBUG("qa->join_conditions.size() = 0 \n");
  		}
  		if(err)ERROR("make_join_plan() err is %d\n",err);
  			
  		if( qa->group_target.size() > 0 )err = make_group_plan();
  		else {
  				DEBUG("group_target.size() = 0 \n");
  		}
  		if(err)ERROR("make_group_plan() err is %d\n",err);  
  			
  		if(qa->order_target.size() > 0 )err = make_orderby_plan();
  		else {
  				DEBUG("order_target.size() = 0 \n");
  		}
  		if(err)ERROR("make_orderby_plan() err is %d\n",err);    	
  		 		
  		if(qa->oper_type != BASIC_OPS_DELETE && qa->oper_type != BASIC_OPS_UPDATE  )
  		{	
  		err = make_projection_plan();
  		if(err)ERROR("make_projection_plan() err is %d\n",err); 	
  		}
  		}
  		
  		
}
  	
 
   	
// ��ʼ������Ա����
int init()
{
	if( NULL == qa )
		{
			ERROR("MAKE_QUERY_PLAN_NULL_QA_PTR\n");
			return MAKE_QUERY_PLAN_NULL_QA_PTR;
		}
	CPP_DEBUG<<"begin init() \n "<<std::endl;
	// normal_oper_condition_map
	//�ҳ������������õ����ֶ�												
	int ret = get_table_conditions(
														/*in*/  qa,										
														/*out*/ mem_table_ptr_map, 	      					//(����,��ָ��)
	  												/*out*/ normal_single_condition_map,				//(����,�������б�)
	  												/*out*/ normal_double_condition_map,				//(����,˫�����б�)
	  												/*out*/ normal_index_double_condition_map,	//(����,����˫�����б�)										
	  												/*out*/ normal_oper_condition_map,					//(����,���������б�)										
														/*out*/ join_eq_condition_map,  				    // ��������
														/*out*/ const_condition_map,							  //(����,���������б�)	
														/*out*/ condition_fields_map	              //(����,�����ֶ��б�)	
	);
    if( ret != 0 && ret != NOT_INDEX_FIELD )
  	{
  		ERROR("end get_single_table_conditions��err is %d \n",ret);
  		return ret;
  	}
	//�ҳ�ÿ������ͶӰ�õ����ֶ�
	ret = get_projection_fields(
														/*in*/  qa,										
														/*out*/ aggregat_fields ,  //(����,���ھۺϵ��ֶ���)
														/*out*/ raw_fields ,       //(����,��ͨ�ֶ���)
														/*out*/ oper_fields ,      //(����,��ͨ�����ֶ���)
														/*out*/ nomal_func_fields, //(����,�ǾۺϺ����ֶ���)
													  /*out*/ projection_fields  //(����,�ǾۺϺ����ֶ���)
													); 
	if( ret!= 0 )
		{
			ERROR("get_projection_fields err is %d \n",ret);
			return ret;
		}	
		// ���һ������Ҫ�����е��ֶΣ� ͶӰ�ֶ� + �����ֶ� ��
	ret = get_table_scan_fields(
																	/*in*/ qa,										
																	/*in*/ projection_fields, 	 // ͶӰ�ֶ�
																	/*in*/ condition_fields_map, // �����ֶ�
																	/*out*/scan_fields_map    	 // ��Ҫɨ����ֶ�
	);
	if( ret!= 0 )
		{
			ERROR("get_table_scan_fields err is %d \n",ret);
			return ret;
		}	

	// ���һ����ɨ�������е��ֶε�Ԫ��������
	ret = get_talbe_scan_meta(
													/*in*/ qa,										
													/*in*/ scan_fields_map,  // ��Ҫɨ����ֶ�
													/*out*/scan_metas_map    // ����ɨ����Ԫ��������
	
	);
		if( ret!= 0 )
		{
			ERROR("get_talbe_scan_meta err is %d \n",ret);
			return ret;
		}	
		
		// ���һ����������ͶӰ�ֶ�
	ret = get_table_result_fields(
																	/*in*/ qa,										
																	/*in*/ projection_fields, 	 // ͶӰ�ֶ�
																	/*out*/result_fields    	   ///�������ͶӰ�ֶ� 
	);
	if( ret!= 0 )
	{
		ERROR("get_table_result_fields err is %d \n",ret);
		return ret;
	}	
	// ���һ���������ĵ�Ԫ��������
	ret = get_talbe_scan_meta(
													/*in*/ qa,										
													/*in*/ result_fields,  // ��Ҫɨ����ֶ�
													/*out*/result_metas_map    // ����ɨ����Ԫ��������
	
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

//����ɨ��ִ�мƻ�	
int make_scan_plan()
{	
CPP_DEBUG<<"begin make_scan_plan() \n "<<std::endl;

	
for(std::map<std::string,mem_table_t * >::iterator iter = mem_table_ptr_map.begin(); iter != mem_table_ptr_map.end();  ++iter  )
{
mem_table_t *mem_table = iter->second;
std::string table_name = iter->first;

CPP_DEBUG<<" for scan_fields_map["<<table_name<<"].size()="<<scan_fields_map[table_name].size()<<std::endl;



CPP_DEBUG<<"handl_const_con() \n "<<std::endl;
// �жϳ���������Ϊ��������ж�
int ret = handl_const_con(
														/*in*/mem_table , 
														/*in*/const_condition_map[table_name] //��Ҫɨ��ķ���������
												 );
if( ret!= 0 )
	{
		ERROR("handl_const_con err is %d \n",ret);
		return ret;
	}

if( !normal_index_double_condition_map[table_name].empty() )
{
CPP_DEBUG<<"handl_double_con_index() \n "<<std::endl;												
// ˫��������ɨ��
ret =  handl_double_con_index(/*in*/mem_table, 												              //��Ҫɨ��ı�
															/*in*/normal_index_double_condition_map[table_name],	//��Ҫɨ�����������
															/*in*/normal_double_condition_map[table_name],   			//��Ҫɨ��ķ���������
															/*in*/condition_fields_map[table_name],               //�����ֶ��б�
															/*in*/finded_Addr,                                    //����ɨ���ݴ�set    
										          /*in&&out*/plan_node_scan_list                        //�����ִ�мƻ�
													  );
}
else
{	
CPP_DEBUG<<"handl_double_con_normal() \n "<<std::endl;																							
// ˫����ԭ��ɨ��
ret =  handl_double_con_normal(
														/*in*/mem_table , 
														/*in*/normal_double_condition_map[table_name],   				//��Ҫɨ��ķ���������
														/*in*/condition_fields_map[table_name],                 //�����ֶ��б�
											/*in&&out*/plan_node_scan_list											       	  //�����ִ�мƻ�
													);
}
if( ret!= 0 )
	{
		ERROR("handl_double_con_ err is %d \n",ret);
		return ret;
	}

plan_node_scan_list_map[table_name] = (*(plan_node_scan_list.rbegin())) ;
table_scan_ret[table_name]          = (*(plan_node_scan_list.rbegin()))->get_ret_list();												

}

CPP_DEBUG<<"end make_scan_plan() \n "<<std::endl;
return 0;


}

int make_join_plan()
{

CPP_DEBUG<<"begin make_join_plan() ------------{ \n "<<std::endl;

	//�Թ��������������򣬲���˳�����ɽڵ�
int ret = handl_join_condtions(
													/*in*/ qa,	
													/*in*/ table_scan_ret,						        		 	// ��Ӧÿ���������ɨ���Ľ����
													/*in*/ scan_metas_map,						        			// ��Ҫɨ������ֶ�Ԫ����
												 /*out*/ join_eq_condition_only_inner_join_list,  // �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
										     /*out*/ join_meta,																// join����ֶ�Ԫ��Ϣ
										 /*in&&out*/ plan_node_join_group_list
												);
if( ret!= 0 )
	{
		ERROR("handl_join_condtions err is %d\n",ret);
		return ret;
	}
CPP_DEBUG<<"end make_join_plan() ------------} \n "<<std::endl;
return 0;
 
}


int make_group_plan()
{
	CPP_DEBUG<<"begin make_join_group_plan() -------- { \n "<<std::endl;
	// ����groupby
int ret = handl_groupby(
									/*in*/  qa,	
									/*in*/	scan_fields_map,       		 								// ��Ҫɨ������ֶ�
									/*in*/  join_eq_condition_only_inner_join_list,   // �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
									/*in*/  scan_metas_map,						        			  // ��Ҫɨ������ֶ�Ԫ����
									/*out*/ &groupby_meta,         				  				  // group_by ���Ԫ��������
									/*out*/	plan_node_join_group_list
								  );
								  
if( ret!= 0 )
	{
		ERROR("handl_groupby err is %d -------- }\n",ret);
		return ret;
	}
								 
	CPP_DEBUG<<"end make_join_group_plan() -------- } \n "<<std::endl;
  return 0;
	
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
									/*in*/  join_meta, // ����ɨ����Ԫ��������
									/*out*/	plan_node_join_group_list
								  );
	}
	else {// ������join_groupby
		
		ret = handl_orderby(
									/*in*/  qa,	
									/*in*/  scan_metas_map.begin()->second,            // ����Ԫ��������
									/*out*/	//plan_node_scan_list_map.begin()->second  // �����ִ�мƻ�
									/*out*/	plan_node_scan_list
								  );
	}

	CPP_DEBUG<<"end make_orderby_plan() \n "<<std::endl;
	return ret;
}


int make_projection_plan()
{
	CPP_DEBUG<<"begin make_projection_plan()--------------{ \n "<<std::endl;
  DEBUG("plan_node_join_group_list.size() is %d; \n", plan_node_join_group_list.size() );

	int ret = 0;
	
	// ����� Ԫ��������������join ��ʱ���� join, ��join��ʱ���� �����ɨ��Ԫ��������
	record_meta  *input_meta;
	if(qa->is_join)
		{
			DEBUG("qa->is_join; \n");
			input_meta = &join_meta;
		}
	else
		{
				DEBUG("qa->is_not_join; \n");
        input_meta = &( result_metas_map.begin()->second );
		} 

  //��ɨ��
  final_plan_node_list = &plan_node_scan_list;
  //���Դ���ɲ���ɨ��

   //if( !plan_node_join_group_list.empty() )DEBUG("final_plan_node_list = &plan_node_join_group_list \n");
	 //else                                    DEBUG("final_plan_node_list = &(plan_node_scan_list_map.begin()->second\n");


	 //if( !plan_node_join_group_list.empty() )final_plan_node_list = &plan_node_join_group_list;
	 //else                                   final_plan_node_list = &(plan_node_scan_list_map.begin()->second);
	  
	  if( !plan_node_join_group_list.empty() ){
      DEBUG("!plan_node_join_group_list.empty()  \n");
	  	//plan_node_scan_list.merge(plan_node_join_group_list);
	  	for( auto &v : plan_node_join_group_list  )
	  	{
	  	 plan_node_scan_list.push_back( v  );
	    }
	  }
	  else
	  	{
	  		DEBUG("plan_node_join_group_list is empty \n");
	  	}
	  
	DEBUG("final_plan_node_list->size() is %d; \n", final_plan_node_list->size() );

	ret = handl_projection(
									/*in*/  qa,	
									/*in*/  *input_meta,	//�������Ԫ��������
									/*out*/ projection_fun_oper_lists ,//ͶӰ oper �б� 
									/*out*/	projection_meta,  					//ͶӰԪ�������� 
									/*out*/	*final_plan_node_list	
									//,std::list<generic_result> & projection_ret_list					 
								  );
	if(ret)
		{
		 CPP_ERROR<<" handl_projection failed! err is "<<ret<<std::endl;	
		 return ret;
		}
	CPP_DEBUG<<"end make_projection_plan() --------------}\n "<<std::endl;
	return 0;
}


int execute( unsigned long long  trans_no  )
{
	DEBUG("physical_query_plan::execute(%d); --------- { \n", trans_no );
	
	int ret = 0;
	DEBUG("final_plan_node_list->size() is %d; \n", final_plan_node_list->size() );
  int i = 0;
	for (auto &v : *final_plan_node_list )
	{
	 if( BASIC_OPS_DELETE == qa->oper_type )v->oper_type = BASIC_OPS_DELETE;
	 DEBUG(" physical_query_plan_node: %d; \n", i );
		ret = v->execute(trans_no);
		if(ret)
			{
				ERROR("execute sql failed !  and err is %d \n",ret);
				return ret;
			}
	}
	DEBUG("physical_query_plan::execute(%d); --------- } \n", trans_no );
	return 0;
}

};


#endif 