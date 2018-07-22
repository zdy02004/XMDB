/*
 g++ -C -w -std=c++11 query_handles.h   
*/

#ifndef ELEMENT_HANDLES  
#define ELEMENT_HANDLES

#include "sql_conditions.h"
#include "plan_scan_node.h"
#include "plan_join_node.h"
#include "plan_group_node.h"
#include "plan_order_node.h"
#include "plan_projection_node.h"



// �� normal_double_condition_list �л�ù����б�
int get_complist_from_double_con(
														/*in*/mem_table_t * mem_table , 
														/*in*/std::list<normal_double_condition_struct>& normal_double_condition_list,
														/*out*/compare_list ** first
													)
{
DEBUG("begin get_complist_from_double_con() \n");
int err = 0;
compare_list * pre = NULL;
plan_node * node;  

for(auto& v : normal_double_condition_list)
{
	DEBUG("for(auto& v : normal_double_condition_list) \n");
	
	
  int tag = v.tag;
	std::string relation_name = v.relation_name;
	std::string column_name   = v.column_name;
	std::string const_value   = v.const_value;
  std::string const_type    = v.const_type;
  	
  	CPP_DEBUG<<"tag = "<< tag <<endl;
  	CPP_DEBUG<<"relation_name = "<< relation_name <<endl;
    CPP_DEBUG<<"column_name = "<< column_name <<endl;
    CPP_DEBUG<<"const_value = "<< const_value <<endl;	
    CPP_DEBUG<<"const_type = "<< const_type <<endl;
    
    DEBUG("mem_table is %d \n",mem_table);
    	  	  	
  field_t  field;
  err = get_field(mem_table ,column_name, field);
  if( err != 0 )
  	{
  		ERROR("get_field err is %d \n",err);
  		return err;
  	}
  
  switch(tag)
  {
  case T_OP_EQ :{
	 DEBUG("case T_OP_EQ \n");
	 std::shared_ptr<compare_list> cmp1(new compare_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();
	 	
	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	 
	 break;
}      
  case T_OP_LE :{
   DEBUG("case T_OP_LE \n");
	 std::shared_ptr<compare_list> cmp1(new compare_le_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();

	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	
	 break;
}  
  case T_OP_LT :{
   DEBUG("case T_OP_LT \n");
	 std::shared_ptr<compare_list> cmp1(new compare_lt_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();

	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	
   break;
}  
  case T_OP_GE :{
   DEBUG("case T_OP_GE \n");
	 std::shared_ptr<compare_list> cmp1(new compare_ge_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();
	 	
	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	
	break;
}  
  case T_OP_GT :{
   DEBUG("case T_OP_GT \n");
	 std::shared_ptr<compare_list> cmp1(new compare_gt_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();
	 	
	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	
	 break;
}   
  case T_OP_NE :{
   DEBUG("case T_OP_NE \n");
	 std::shared_ptr<compare_list> cmp1(new compare_ne_list);
	 cmp1->mem_table       			= mem_table;
	 cmp1->field_name      			= field.field_name;	 
	 
	 if(pre)pre->next					 	= cmp1.get();
	 else *first                = cmp1.get();
	 	
	 pre = cmp1.get();
	 cmp1->cmp_field_value 			=  cast_ptr_by_field( const_value ,  field );
	
	 break;
}   
    case T_OP_LIKE :{
    	   DEBUG("case T_OP_LIKE \n");

// ��δʵ��
	
	break;
}  
  	
  default : break;// �������������ȫ��scan
  
  }	
  }
DEBUG("end get_complist_from_double_con() \n");

return 0;
}


// �жϳ���������Ϊ�����ж�
int handl_const_con(
														/*in*/mem_table_t * mem_table , 
														/*in*/std::list<const_condition_struct>& const_list 		 //��Ҫɨ��ķ���������
													)
{
 
 int err  = 0 ;
// ��ù����б�
for(auto &v : const_list)
	{
		if(v.is_drop())return INFO_BROCKEN;
		
	}
return err;

}



// ˫��������ɨ��
int handl_double_con_index( /*in*/mem_table_t *mem_table , 																		//��Ҫɨ��ı�
														/*in*/std::list<normal_double_condition_struct> & index_list,			//��Ҫɨ�����������
														/*in*/std::list<normal_double_condition_struct> & nomal_list,			//��Ҫɨ��ķ���������
														/*in*/std::set<std::string>  									  & pro_list,       //ɨ������ֶ��б�
														/*in&&out*/std::list<plan_node *>								& plan_node_list  //�����ִ�мƻ�
													  )
{
int err = 0;
int first = 1;
std::shared_ptr<finded_Addr_t> finded_Addr (new finded_Addr_t );
finded_Addr_t *pre_Addr = finded_Addr.get();

for(auto& v : index_list)
{
  int tag = v.tag;
  long index_no = v.index_no;
  int  index_type = v.index_type; // 1 hash 2 skiplist
  void * addr;
  
  err = get_index_no_addr( index_no,&addr);
  if(!err)return err;
  	
	std::string relation_name = v.relation_name;
	std::string column_name   = v.column_name;
	std::string const_value   = v.const_value;
  std::string const_type    = v.const_type;

	
if( INDEX_TYPE_HASH == index_type)
{
mem_hash_index_t * index = (mem_hash_index_t *) addr;
switch(tag)
{
case T_OP_EQ :{
scan_index_hash_node *node = new scan_index_hash_node(index_no,
  								               index_type,
  								               mem_table,
  								               index,
  								               *(v.context_),
  								               v.query_plan_->doc,
  								               relation_name,
  								               column_name,
  								               const_value,
  								               const_type,
  								               pre_Addr);
pre_Addr = &(node->ret_list);
plan_node_list.push_back(node);

break;
}   
  default :// hash �����Ե�ֵ����Ĳ�ѯ����������ȫ��scan
  nomal_list.push_back(v);
  }
}

if( INDEX_TYPE_SKIP == index_type)
{
	mem_skiplist_index_t *index = (mem_skiplist_index_t *) addr;
  switch(tag)
  {
  case T_OP_EQ :{
	scan_skiplist_eq_node *node = new scan_skiplist_eq_node(index_no,
	  								              	index_type,
	  								              	mem_table,
	  								              	index,
	  								              	*(v.context_),
	  								              	v.query_plan_->doc,
	  								              	relation_name,
	  								              	column_name,
	  								              	const_value,
	  								              	const_type,
	  								              	pre_Addr);
	pre_Addr = &(node->ret_list);

	plan_node_list.push_back(node);
	
	break;
}      
  case T_OP_LE :{
	scan_skiplist_le_node *node = new scan_skiplist_le_node(index_no,
	  								              	index_type,
	  								              	mem_table,
	  								              	index,
	  								              	*(v.context_),
	  								              	v.query_plan_->doc,
	  								              	relation_name,
	  								              	column_name,
	  								              	const_value,
	  								              	const_type,
	  								              	pre_Addr);
	pre_Addr = &(node->ret_list);
	
	plan_node_list.push_back(node);
	break;
}  
  case T_OP_LT :{
	scan_skiplist_lt_node *node = new scan_skiplist_lt_node(index_no,
	  								              	index_type,
	  								              	mem_table,
	  								              	index,
	  								              	*(v.context_),
	  								              	v.query_plan_->doc,
	  								              	relation_name,
	  								              	column_name,
	  								              	const_value,
	  								              	const_type,
	  								              	pre_Addr);
  pre_Addr = &(node->ret_list);
	plan_node_list.push_back(node);
	break;
}  
  case T_OP_GE :{
	scan_skiplist_ge_node *node = new scan_skiplist_ge_node(index_no,
	  								              	index_type,
	  								              	mem_table,
	  								              	index,
	  								              	*(v.context_),
	  								              	v.query_plan_->doc,
	  								              	relation_name,
	  								              	column_name,
	  								              	const_value,
	  								              	const_type,
	  								              	pre_Addr
	  								              	);
  pre_Addr = &(node->ret_list);
	plan_node_list.push_back(node);
	break;
}  
  case T_OP_GT :{
	scan_skiplist_gt_node *node = new scan_skiplist_gt_node(index_no,
	  								              	index_type,
	  								              	mem_table,
	  								              	index,
	  								              	*(v.context_),
	  								              	v.query_plan_->doc,
	  								              	relation_name,
	  								              	column_name,
	  								              	const_value,
	  								              	const_type,
	  								              	pre_Addr);
	pre_Addr = &(node->ret_list);
	plan_node_list.push_back(node);
	break;
}  
//  case T_OP_BTW: {
//	scan_skiplist_btw_node *node = new scan_skiplist_btw_node(index_no,
//	  								              	index_type,
//	  								              	mem_table,
//	  								              	index_min,
//	  								              	index_max,
//	  								              	v->context_,
//	  								              	&(v->Doc),
//	  								              	relation_name,
//	  								              	column_name,
//	  								              	const_value,
//	  								              	const_type);
//	
//	break;
//}  
  case T_OP_NE :
  	
  default :// �������������ȫ��scan
  nomal_list.push_back(v);
  
  }
}

}

// ��ù����б�
 compare_list *com_list = NULL;
 err = get_complist_from_double_con(
																			 mem_table , 
																	  	 nomal_list,
																/*out*/&com_list
																		);

rapidjson::Value merg_json;
// �ϲ�index �����
merg_index_sfw_node *node = new merg_index_sfw_node( mem_table,
																		com_list,															//�����б�
																		pro_list,       											//ͶӰ�б�
	  								              	merg_json,
	  								              	index_list.begin()->query_plan_->doc,
	  								              	pre_Addr
	  								              	);
plan_node_list.push_back(node);
}					


// ˫����ԭ��ɨ��
int handl_double_con_normal(
														/*in*/mem_table_t * mem_table , 
														/*in*/std::list<normal_double_condition_struct>& nomal_list,		 //��Ҫɨ��ķ���������
														/*in*/std::set<std::string>  									 & pro_list,       //ɨ������ֶ��б�
														/*in&&out*/std::list<plan_node *>							 & plan_node_list  //�����ִ�мƻ�
													)
{
 CPP_DEBUG<<"begin handl_double_con_normal() \n "<<std::endl;
 int err  = 0 ;
// ��ù����б�
 compare_list *com_list = NULL;
 err = get_complist_from_double_con(
																			 mem_table , 
																	  	 nomal_list,
																/*out*/&com_list
																		);

rapidjson::Value normal_json;
// �ϲ�index �����
 DEBUG("mem_table is %ld \n",mem_table);
 DEBUG("com_list is %ld\n ",com_list);
// DEBUG("pro_list %ld \n",pro_list);
// DEBUG("normal_json %ld \n",normal_json );
// DEBUG("nomal_list.begin()->query_plan_->doc %ld \n ",nomal_list.begin()->query_plan_->doc );
scan_sfw_node *node = new scan_sfw_node( mem_table,
																		com_list,															//�����б�
																		pro_list,       											//ͶӰ�б�
	  								              	normal_json,
	  								              	nomal_list.begin()->query_plan_->doc
	  								              	);
plan_node_list.push_back(node);
 CPP_DEBUG<<"end handl_double_con_normal() \n "<<std::endl;
return err;
}



/*
�Թ���������������
����������ڵ�
*/

int handl_join_condtions(
													/*in*/QueryAnalyser * qa,	
													/*in*/std::map<std::string,std::list<generic_result>*  >& table_scan_ret,						 // ��Ӧÿ���������ɨ���Ľ����
													/*in*/std::map<std::string,record_meta>						      & scan_metas_map,						 // ��Ҫɨ����ֶ�Ԫ��Ϣ 
													/*out*/std::vector<join_eq_condition_struct>& join_eq_condition_only_inner_join_list,// �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
													/*out*/record_meta  																		& out_meta,									 // �������meta
													/*in&&out*/std::list<plan_node *>		& plan_node_list
												)
{
	
if( NULL == qa ) return QueryAnalyserNullPtr;
std::vector<rapidjson::Value *>& join_conditions = qa->join_conditions;

// �������������ϵ�ĸ���
std::vector<join_eq_condition_struct>  join_eq_condition_struct_list ;
// ���ݸ���
for(auto v : join_conditions )join_eq_condition_struct_list.emplace_back( v, qa );
// �Ը���������������
int ret = order_join_condtions(qa, join_eq_condition_struct_list );
if(!ret)return ret;

// ��˳�����ɹ�������ڵ�
int is_first = 1;

record_meta *pre_meta;
std::list<generic_result> * pre_ret ;
	
for(auto & v : join_eq_condition_struct_list)
{
	
	  if(is_first)
	  	{
	  		pre_meta = &(scan_metas_map[v.relation_name[0]]);
	  		pre_ret  = table_scan_ret[v.relation_name[0]];
	  		is_first = 0;
	  	}
		if(v.context_->HasMember("SEMI_JOIN_LEVEL")){
		do_semi_join_node *node = new do_semi_join_node(
  															v.relation_name[0],v.relation_name[1],
  															v.column_name[0],v.column_name[1],
  															v.mem_table[0],v.mem_table[1],
  															pre_meta,&(scan_metas_map[v.relation_name[1]]),
  															pre_ret,table_scan_ret[v.relation_name[1]],
	  								            *(v.context_),
  								              v.query_plan_->doc,
  								              is_first);
  	pre_ret  = node->get_ret_list() ;
  	plan_node_list.push_back(node);	
  	pre_meta = &(node->out_meta);
  	}
  	else	if(v.context_->HasMember("ANTI_JOIN_LEVEL")){
		do_anti_join_node *node = new do_anti_join_node(
  															v.relation_name[0],v.relation_name[1],
  															v.column_name[0],v.column_name[1],
  															v.mem_table[0],v.mem_table[1],
  															pre_meta,&(scan_metas_map[v.relation_name[1]]),
  															pre_ret,table_scan_ret[v.relation_name[1]],
	  								            *(v.context_),
  								              v.query_plan_->doc,
  								              is_first);
  	pre_ret  = node->get_ret_list() ;
  	plan_node_list.push_back(node);	
  	 pre_meta = &(node->out_meta);

  	}
  	else {
  	join_eq_condition_only_inner_join_list.push_back(v);	
  	
		do_join_node *node = new do_join_node(
  															v.relation_name[0],v.relation_name[1],
  															v.column_name[0],v.column_name[1],
  															v.mem_table[0],v.mem_table[1],
  															pre_meta,&(scan_metas_map[v.relation_name[1]]),
  															pre_ret,table_scan_ret[v.relation_name[1]],
	  								            *(v.context_),
  								              v.query_plan_->doc,
  								              is_first);
  	pre_ret  = node->get_ret_list() ;
  	plan_node_list.push_back(node);	
  	pre_meta = &(node->out_meta);

		}
  	
  							            
		if( is_first == 1)is_first = 0;
}
		
	
	out_meta = *pre_meta;
}


// ��ù�������ֶ�����
int get_record_meta_from_join_list(
																/*in*/	std::vector<join_eq_condition_struct>		& inner_join_list,				 // �����Ĺ�����ϵ 
																/*in*/	std::map<std::string,std::set<std::string> >&  scan_fields,        // ��Ҫɨ������ֶ�
																/*out*/ record_meta & meta
														  )
{
	bool is_first = true;
	std:string table_name;
	for(auto &v:inner_join_list )
	{
		if(is_first){
			is_first = false;
			table_name = v.relation_name[0];
			meta.append_by_string_list(v.mem_table[0],scan_fields[table_name] );
		}
		else{
			table_name = v.relation_name[1];
			meta.append_by_string_list(v.mem_table[1],scan_fields[table_name] );
		 }

	if(is_first)return -1;
	else return 0;

		}
}


//���� group by �ڵ�
int handl_groupby(
									/*in*/  QueryAnalyser * qa,	
									/*in*/	std::map<std::string,std::set<std::string> >&  scan_fields,        // ��Ҫɨ������ֶ�
									/*in*/  std::vector<join_eq_condition_struct>& join_eq_condition_only_inner_join_list,// �������Ĺ�����ϵ��ȥ�� semi_join �� anti_join �Ľ��
									/*in*/  std::map<std::string,record_meta>						&  scan_metas,          // ����ɨ����Ԫ��������
									/*out*/ record_meta **groupby_result_meta,																	//group_by ���Ԫ��������
									/*out*/	std::list<plan_node *>	& plan_node_list
								  )
{
	if(qa->group_target.empty())return 0;
	
	std::vector<std::string>	table_names; 
	std::vector<std::string>	column_names; 
	std::vector<mem_table_t *>	mem_tables; 
	std::vector<std::string>	alias_names;
	std::list<generic_result>*  input ;	

	// �����������ʵ����
    for(auto &v :qa->group_target){
			auto s  = std::find_if(qa->tables.begin(),qa->tables.end(),[&](TableItem& s){return v.relation_name == s.alias_name_;});
	   	if( qa->tables.end() != s )
	   	{
				v.relation_name = s->table_name_;
				v.alias_name 	= s->alias_name_;			
	   	}

	 		//������
	 		table_names .push_back(v.relation_name);
			column_names.push_back(v.column_name  );
			alias_names .push_back(v.alias_name   );
			mem_tables	.push_back( std::find_if(qa->tables.begin(),qa->tables.end(),[&](TableItem& s){return v.relation_name == s.table_name_;})->mem_table);
    }



	//���� table_name_dis //������ÿ������뿪ͷ�ľ���
	//std::map<std::string, off_t>table_name_dis;
	//off_t dis = 0;
	//bool  is_first_for = true;
	//for(auto &v : (join_eq_condition_only_inner_join_list) ){
	//	 //dis_index.push_back( dis );
	//	 
	//	if(is_first_for){
	//		if( !v.alias_name[0].empty() ) table_name_dis[v.alias_name[0]] = dis;
	//		else table_name_dis[v.relation_name[0]] = dis;
	//		
	//	 	dis += scan_metas[v.relation_name[0]].size;
	//	 	is_first_for = false;
	//	}
	//	else {
	//		if( !v.alias_name[1].empty() ) table_name_dis[v.alias_name[1]] = dis;
	//		else table_name_dis[v.relation_name[1]] = dis;
	//	 	dis += scan_metas[v.relation_name[1]].size;
	//	}
	//}
 
 	//group by ֮ǰ�м�����Ԫ��������
	record_meta  input_meta;
	int err =  0;
	if(qa->is_join)	err = get_record_meta_from_join_list(join_eq_condition_only_inner_join_list,scan_fields, input_meta);
	else {
		err = input_meta.append_by_string_list( qa->tables.begin()->mem_table,scan_fields[table_names[0]] );
	}
	
  rapidjson::Value  order_json;
	do_groupby_node *node = new do_groupby_node(
												table_names,
												column_names,
												alias_names,
												mem_tables,
												//&table_name_dis,
												input_meta,
								   (*(plan_node_list.rbegin()))->get_ret_list(),			
												qa->is_join,
												order_json,
  												qa->doc
												);
												
	plan_node_list.push_back(node); 


												
  *groupby_result_meta = &(node->meta);
	return 0;
}




//����order by �ڵ�
int handl_orderby(
									/*in*/  QueryAnalyser * qa,	
									/*in*/  record_meta	  & input_metas, // ����ɨ����Ԫ��������
									/*out*/	std::list<plan_node *>	& plan_node_list
								  )
{
	if(qa->order_target.empty())return 0;
	
	std::vector<std::string>	table_names; 
	std::vector<std::string>	column_names; 
	std::vector<mem_table_t *>	mem_tables; 
	std::vector<std::string>	alias_names;
	std::list<generic_result>*  input ;	

	// �����������ʵ����
    for(auto &v :qa->order_target){
			auto s  = std::find_if(qa->tables.begin(),qa->tables.end(),[&](TableItem& s){return v.relation_name == s.alias_name_;});
	   	if( qa->tables.end() != s )
	   	{
				v.relation_name = s->table_name_;
				v.alias_name 	= s->alias_name_;			
	   	}

	 		//������
	 		table_names .push_back(v.relation_name);
			column_names.push_back(v.column_name  );
			alias_names .push_back(v.alias_name   );
			mem_tables	.push_back( std::find_if(qa->tables.begin(),qa->tables.end(),[&](TableItem& s){return v.relation_name == s.table_name_;})->mem_table);
    }

	
  rapidjson::Value  order_json;
	do_orderby_node *node = new do_orderby_node(
												table_names,
												column_names,
												alias_names,
												mem_tables,
												//&table_name_dis,
												input_metas,
								   (*(plan_node_list.rbegin()))->get_ret_list(),			
												qa->is_join,
												order_json,
  												qa->doc
												);
												
	plan_node_list.push_back(node); 


	return 0;
}


//����ͶӰ��Ҳ�ǲ�ѯsql�����ս��
int handl_projection(
									/*in*/  QueryAnalyser * qa,	
									/*in*/  record_meta   &input_meta,														//�������Ԫ��������
									/*out*/ std::vector<fun_oper *> &  projection_fun_oper_lists ,//ͶӰ oper �б� 
									/*out*/	record_meta							&  projection_meta,  					//ͶӰԪ�������� 
									/*out*/	std::list<plan_node *>	&  plan_node_list						 
								  )
{
	
	resolve_to_opper_node( qa , projection_fun_oper_lists, projection_meta	);
  
		DEBUG(" resolve_to_opper_node( qa , projection_fun_oper_lists, projection_meta	); \n" );

	if( projection_fun_oper_lists.empty()  )
		{
		  CPP_ERROR<<" projection_fun_oper_lists is empty() !\n"	;
		  return -1;
		}
		
		DEBUG("get_ret_list() is %d \n", (*(plan_node_list.rbegin()))->plan_type );
	//projection_meta = input_meta ;// �����õ��������join
	shared_ptr<std::list<generic_result> > ret_list ( new std::list<generic_result> );
	do_projection_node *node = new do_projection_node(
												input_meta,
												projection_meta,
												projection_fun_oper_lists,
								        (*(plan_node_list.rbegin()))->get_ret_list(),	
								        ret_list,			
												*(qa->project_lists),
  											qa->doc
												);
	CPP_DEBUG<<" plan_node_list.push_back(node);!\n"	;											
	plan_node_list.push_back(node); 
  return 0;
	
}


#endif 
