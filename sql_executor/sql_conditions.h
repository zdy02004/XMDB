/*
 g++ -C -w -std=c++11 sql_conditions.h   
*/

#ifndef SQL_CONDITIONS  
#define SQL_CONDITIONS  



#include "sql_field.h"

#define INFO_BROCKEN     78001
#define ERR_COLUMN_NULL  78002
#define ERR_PLEASE_MARK_TABLE_COLOUM  78003
#define ERR_NOT_FOUND_COLOUM  78004
#define ERR_UNNOMAL_DOUBLE_CONDITION  78005
#define ERR_NOT_FOUND_TABLE  78006
#define ERR_JOIN_FIELD_TYPE_NOT_EQ 78007
#define GET_SINGLE_TABLE_EMPTY_TABLE 78008
#define GET_SINGLE_TABLE_EMPTY_QA 78009
#define ERR_NOT_FOUND_LINK        78010
#define QueryAnalyserNullPtr      78011
#define NOT_INDEX_FIELD           78012

/*
��Ҫ���������½ṹ��
1.�������������ڿ��ٶ�·
2.������������
3.˫����������
4.������������ between
*/

//#include "ops.hpp"
//#include "func_help.hpp"
//#include "../mem_date_index_ctl/mem_table_mvcc_op.h"
//#include "../mem_date_index_ctl/mem_index_no_manager.h"
//#include "index_scan_Addr.hpp"

//�������������ṹ��
//��Ҫ������������������������
struct const_condition_struct{
	
	int tag;
	std::string const_value;
  std::string const_type;
  rapidjson::Value *  context_ ;
	QueryAnalyser    *  query_plan_;
  
  const_condition_struct(rapidjson::Value *  context, QueryAnalyser * query_plan ):context_(context),query_plan_(query_plan){
		tag = (*context_)["tag"].GetInt();
		//ֱ�ӻ�ó���
		if( (*context_)["children"][0].HasMember("str_value_") ){
			const_value = (*context_)["children"][0]["str_value_"].GetString();
		}
		if( (*context_)["children"][0].HasMember("CONST_TYPE") ){
			const_type = (*context_)["children"][0]["CONST_TYPE"].GetString();
		}
		
	}
	// ����1 ���Ը�����
	// ���� INFO_BROCKEN ���ٶ�·
	// ���� 0 ����
	int is_drop(){
		if(tag == T_BOOL && const_value == "1" )return 1;
		if(tag == T_BOOL && const_value == "0" )return INFO_BROCKEN;
		else return 0;
	}
	
};

//�����������ṹ��
//��Ҫ������������������������
struct normal_single_condition_struct{
	int tag;
	std::string relation_name;
	std::string column_name;
	rapidjson::Value *  context_ ;
	QueryAnalyser    *  query_plan_;
	int has_index;
	int index_type;
	long index_no;
	
	normal_single_condition_struct(rapidjson::Value *  context, QueryAnalyser * query_plan ):context_(context),query_plan_(query_plan),has_index(0){
		tag = (*context_)["tag"].GetInt();
		
		//ֱ�ӻ�ñ���
		if( (*context_)["children"][0].HasMember("RELATION_NAME") ){
			relation_name = (*context_)["children"][0]["RELATION_NAME"]["str_value_"].GetString();
		}
		if( (*context_)["children"][0].HasMember("COLUMN_NAME") ){
			column_name = (*context_)["children"][0]["COLUMN_NAME"]["str_value_"].GetString();
		}
		
	}
	
	bool operator < (const normal_single_condition_struct &a) const
	{
		return has_index < a.has_index;	
	}	
	
int get_name(){	
		if( 0 == column_name.size() ) 
			{
				// δ��ȡ��������
				return ERR_COLUMN_NULL;
			}
			
			mem_table_t *mem_table = NULL;
		
		//ֱ�ӻ�ñ���ʧ��,��tables ���Ҷ�Ӧ��relation_name���Ҳ������ҵ��������
		if( 0 == relation_name.size() ){
			int field_num = 0;
			for(auto & table : query_plan_->tables )
			{
				long long table_no;
				
				int err = 0;
				// ����ԭʼ����ñ��Ƿ����
				if(!table.table_name_.empty()){
					 err = search_table_name(const_cast<char *>(table.table_name_.c_str()),&table_no);
					
					 if( 0 == err){
					 	 err = get_table_no_addr(table_no,(void **)(&mem_table));
					 	 if( 0 == err){
					 	 		if( has_field( mem_table ,column_name ) ){
					 	 			++field_num;
					 	 			relation_name = std::string(mem_table->config.table_name);
					 	 		}
					 		}
					 }
					 
				}
			}
			
			if( 1 < field_num )return ERR_PLEASE_MARK_TABLE_COLOUM;
			if( 0 ==field_num )return ERR_NOT_FOUND_COLOUM; 	
				
			// ֻ�ҵ�1����Ӧ��table��������
			if( 1 == field_num ){
				has_index = field_has_index(mem_table ,column_name,index_no,index_type);
				return 0;
			}
		}
		return 0;
		
		}
		
};

//��Ԫ���������ṹ��
//��Ҫ������������������������
struct normal_double_condition_struct:public normal_single_condition_struct{
  std::string const_value;
  std::string const_type;

		normal_double_condition_struct(rapidjson::Value *  context, QueryAnalyser * query_plan ):normal_single_condition_struct(context,query_plan){
	  }
	  
	 bool operator < (const normal_double_condition_struct &a) const
	{
		return has_index <= a.has_index;	
	}	
	  
int get_name(){	  
	  DEBUG("get_name()\n");
		int i = 0; // ���������������
		int j = 0; // ���������������
		
		// rapidjson_log( context_ );
		
		if( (*context_)["children"][0].HasMember("COLUMN_NAME") && (*context_)["children"][1].HasMember("CONST_TYPE") ) {i = 0; j = 1;}
		else if ( (*context_)["children"][1].HasMember("COLUMN_NAME") &&(*context_)["children"][0].HasMember("CONST_TYPE") ) {i = 1; j = 0;}
		else 
			{
				ERROR("ERR_UNNOMAL_DOUBLE_CONDITION \n");
				return ERR_UNNOMAL_DOUBLE_CONDITION;		
			}
		
		//ֱ�ӻ�ó���
		DEBUG("Get const_value \n");
		if( (*context_)["children"][j].HasMember("str_value_") ){
			DEBUG("HasMember(str_value_) \n");
			const_value = (*context_)["children"][j]["str_value_"].GetString();
		}
		if( (*context_)["children"][j].HasMember("CONST_TYPE") ){
			DEBUG("HasMember(CONST_TYPE) \n");
			const_type = (*context_)["children"][j]["CONST_TYPE"].GetString();
		}
		
		//ֱ�ӻ�ñ���
		DEBUG("Get RELATION_NAME and COLUMN_NAME \n");
		if( (*context_)["children"][i].HasMember("RELATION_NAME") ){
			relation_name = (*context_)["children"][i]["RELATION_NAME"]["str_value_"].GetString();
		}
		if( (*context_)["children"][i].HasMember("COLUMN_NAME") ){
			column_name = (*context_)["children"][i]["COLUMN_NAME"]["str_value_"].GetString();
		}
		
		return normal_single_condition_struct::get_name();	
	}



};

//��Ԫ���������ṹ��
//��Ҫ������������������������
struct normal_btw_condition_struct:public normal_single_condition_struct{
  std::string const_value[2];
  std::string const_type;

		normal_btw_condition_struct(rapidjson::Value *  context, QueryAnalyser * query_plan ):normal_single_condition_struct(context,query_plan){
	  }
	  
	 bool operator < (const normal_double_condition_struct &a) const
	{
		return has_index < a.has_index;	
	}	
	  
int get_name(){	  
		
		int k = 0;
		for(int i = 0;i<3;++i)
		{
			//if( (*context_)["children"][i].HasMember("COLUMN_NAME") && (*context_)["children"][i].HasMember("CONST_TYPE") ) {btw_index[i] = 0;}
			//ֱ�ӻ�ñ���
			if( (*context_)["children"][i].HasMember("RELATION_NAME") ){
				relation_name = (*context_)["children"][i]["RELATION_NAME"]["str_value_"].GetString();
			}
			if( (*context_)["children"][i].HasMember("COLUMN_NAME") ){
				column_name = (*context_)["children"][i]["COLUMN_NAME"]["str_value_"].GetString();
			}
			//ֱ�ӻ�ó���
			if( (*context_)["children"][i].HasMember("str_value_") ){
					const_value[k++] = (*context_)["children"][i]["str_value_"].GetString();
			}
				
		}
		if( const_value[0] > const_value[1] )std:swap(const_value[0],const_value[1]);
		
		return normal_single_condition_struct::get_name();	
	}



};


#define NEED_DELETE -1
// �ȺŹ�������
struct join_eq_condition_struct{
	int tag;
	std::string relation_name[2];
	std::string column_name[2];
	std::string	alias_name[2];
	field_t field[2];
  mem_table_t *mem_table[2];
  
	rapidjson::Value *  context_ ;
	QueryAnalyser    *  query_plan_;
	int has_index[2];
	int index_type[2];
	long index_no[2];
	
	
	join_eq_condition_struct(rapidjson::Value *  context, QueryAnalyser * query_plan ):context_(context),query_plan_(query_plan){
		tag = (*context_)["tag"].GetInt();
		
		//ֱ�ӻ�ñ���
		if( (*context_)["children"][0].HasMember("RELATION_NAME") ){
			relation_name[0] = (*context_)["children"][0]["RELATION_NAME"]["str_value_"].GetString();
		}
		if( (*context_)["children"][0].HasMember("COLUMN_NAME") ){
			column_name[0] = (*context_)["children"][0]["COLUMN_NAME"]["str_value_"].GetString();
		}
				//ֱ�ӻ�ñ���
		if( (*context_)["children"][1].HasMember("RELATION_NAME") ){
			relation_name[1] = (*context_)["children"][1]["RELATION_NAME"]["str_value_"].GetString();
		}
		if( (*context_)["children"][1].HasMember("COLUMN_NAME") ){
			column_name[1] = (*context_)["children"][1]["COLUMN_NAME"]["str_value_"].GetString();
		}
		
	}
	
	// �����ӹ�ϵ���� 1 
	// �ظ��������� NEED_DELETE
	// �޹�ϵ���� 0
	inline int can_link_or_delete( join_eq_condition_struct & linker )
	{
		DEBUG("begin can_link_or_delete() \n");
		int i = 0;
		for(int i = 0; i<2; ++i){
			for(int j = 0; j<2 ; ++j){
				if( relation_name[i] == linker.relation_name[j] && column_name[i] == linker.column_name[j] )++i;
			}
		}
		if ( 1 == i )return 1;
		if ( 2 == i )return NEED_DELETE;
		else return 0;
		
	}
	// ������� ��ţ�self ���Լ��ģ�next���ұߵ�
	inline int get_link_seq( join_eq_condition_struct & linker,int & self, int & next )
	{
		DEBUG("begin get_link_seq() \n");
		int k = 0;
		int i = 0;
		int j = 0;
		for( ; i<2; ++i){
			for( ; j<2 ; ++j){
				if( relation_name[i] == linker.relation_name[j] && column_name[i] == linker.column_name[j] )++k;
			}
		}
		if ( 1 == k ){ self = i; next = j ;return 1;}
		if ( 2 == i )return NEED_DELETE;
		else return 0;
		
	}
	
	bool operator < ( join_eq_condition_struct &a) 
	{
		return get_weight () < a.get_weight ();	
	}	
	
	//���Ȩ�أ�Ȩ��ԽС���ȼ�Խ��
		unsigned long get_weight ()
	{
		return std::min( mem_table_get_used_line( mem_table[0] ) , mem_table_get_used_line( mem_table[1] ) );
	}	
	
int get_name(){	
		if( 0 == column_name[0].size() || 0 == column_name[1].size() || 0 == relation_name[0].size() || 0 == relation_name[1].size() ) 
			{
				// δ��ȡ��������
				return ERR_COLUMN_NULL;
			}
			
			mem_table[0] = NULL;
			mem_table[1] = NULL;

		//ֱ�ӻ�ñ���ʧ��,��tables ���Ҷ�Ӧ��relation_name���Ҳ������ҵ��������
	
			int field_num = 0;
			int finded = 0;
			for(auto & table : query_plan_->tables )
			{
				
				for(int i = 0; i<2; ++i){
					if( relation_name[i] == table.alias_name_ ){relation_name[i] = table.table_name_;}
					if( relation_name[i] == table.table_name_ ) ++finded;
					alias_name[i] = table.alias_name_;
				}
				
			 }
			 if(finded<1)return ERR_NOT_FOUND_TABLE;
		
		  long long table_no;
			int err = 0;
			
		// �����е��ֶ��Ƿ����
				for(int i = 0; i<2; ++i){
					 err = search_table_name(const_cast<char *>(relation_name[i].c_str()),&table_no);
					
					 if( 0 == err){
					 	 err = get_table_no_addr(table_no,(void **)(&(mem_table[i])));
					 	 if( 0 == err){
					 	 		if( !has_field( mem_table[i] ,column_name[i] ) ){
					 	 			return ERR_NOT_FOUND_COLOUM; 	
					 	 		}
					 	 		else
					 	 			get_field( mem_table[i] , column_name[i], field[i] );
					 		}
					 }
					}
					
		if( field[0].field_type != field[1].field_type )return ERR_JOIN_FIELD_TYPE_NOT_EQ;		
		return 0;
		
		}
		
};


// ��õ������ɨ���������
 // ���ϼ��뵽 compare_list ������ normal_single_condition
 // ���ϼ��뵽 compare_list ������ normal_double_condition
 // �ȵ�������� join
 // ���� INFO_BROCKEN ˵�� �ñ���Ҫɨ��
inline int get_single_table_conditions(
											/*in*/  QueryAnalyser * qa,	
											/*in*/  int i,																									// ����Ϣ�е�����
											/*out*/ mem_table_t **mem_table,
  										/*out*/ std::list<normal_single_condition_struct>& normal_single_condition_list,
  										/*out*/ std::list<normal_double_condition_struct>& normal_double_condition_list,
  										/*out*/ std::list<normal_double_condition_struct>& normal_index_double_condition_list,			
  										/*out*/ std::list<join_eq_condition_struct      >& join_eq_condition_list,											
											/*out*/ std::list<const_condition_struct>        & const_condition_list
										)
{
	DEBUG("begin get_single_table_conditions \n");
	if( mem_table == NULL) return GET_SINGLE_TABLE_EMPTY_TABLE;
	if(qa == NULL) return GET_SINGLE_TABLE_EMPTY_QA;
  /*in*/  vector<TableItem> 				& tables 									= qa->tables;                    	// ����Ϣ
	/*in*/  vector<rapidjson::Value *>& const_conditions 				= qa->const_conditions;   				// ���������ٷ�����
	/*in*/	vector<rapidjson::Value *>& nomal_single_conditions = qa->nomal_single_conditions ;  	// �������������ٷ�����
	/*in*/	vector<rapidjson::Value *>& nomal_double_conditions = qa->nomal_double_conditions ;  	// ˫�����������ٷ�����
	/*in*/	vector<rapidjson::Value *>& join_conditions				  = qa->join_conditions;  	     	  // ��������
  
  
  std::string table_name = tables[i].table_name_; 											// ����				
  std::string alias_name = tables[i].alias_name_;												//�����
  std::string sub_select_alias_name = tables[i].sub_select_alias_name_; //�Ӳ�ѯ�����
  
  long long table_no;
  int err = 0;

  // ����ԭʼ����ñ��Ƿ����
  if(!table_name.empty()){
  	 err = search_table_name(const_cast<char *>(table_name.c_str()),&table_no);
  	 if(err){
  	 	CPP_ERROR<<"Table < "<<table_name.c_str()<<" > NOT FOUND!\n";
  	 	return err;
  	 }
  	}
  	else if(!sub_select_alias_name.empty()){
  		// �ݹ鴦���Ӳ�ѯ���߼�
  	}
  	
  	if ( err == 0 ){// �ҵ��ñ��ID
  			
  			err = get_table_no_addr( table_no,(void **)(mem_table) );
  			if( err == 0 ){ // �ҵ��ñ�ĵ�ַ

				tables[i].mem_table = *mem_table;
  				for(auto &nomal_single_condition : nomal_single_conditions ){//���ҵ������б��У�ʹ�øñ��ֶε�һԪ����
  					normal_single_condition_struct nscs(nomal_single_condition,qa);
  					err = nscs.get_name();
  					if( err == 0 && 0 == strcmp( nscs.relation_name.c_str(),(*mem_table)->config.table_name ) ){
  						  normal_single_condition_list.push_back(nscs);
  					}
  				}
  				if(err)
  				{
  					ERROR("end get_single_table_conditions��err is %d \n",err);
  					return err;
  					
  				}
  				//���Ƿ�����������
  				DEBUG("normal_single_condition_list.sort() \n");
  				normal_single_condition_list.sort();
  				
  				for(auto &nomal_double_condition : nomal_double_conditions ){//����˫�����б��У�ʹ�øñ��ֶεĶ�Ԫ����
  					DEBUG(" qa is %0x \n",qa);
  					rapidjson_log( nomal_double_condition );
  					
  					normal_double_condition_struct ndcs(nomal_double_condition,qa);
  					err = ndcs.get_name();
  					if( err == 0 && 0 == strcmp( ndcs.relation_name.c_str(),(*mem_table)->config.table_name ) ){
  						  DEBUG("Find table_name: %s��and try to find column_name:%s \n",ndcs.relation_name.c_str(), ndcs.column_name.c_str() );
  						  
  						  long  index_no;
  						  int   index_type;
  						  
  						  int ret = field_has_index( *mem_table ,ndcs.column_name, index_no, index_type);
								if( ret == 1 ) //�ֶ��������ͼ��뵽 ����˫����list
  						  {
  						 			    DEBUG( "ndcs.column_name��%s is index field!\n" , ndcs.column_name.c_str() ); ;
  					    				DEBUG("Find index double conditions��and push_back it \n");					    				
  						  				normal_index_double_condition_list.push_back(ndcs); 						 		
  						 	}
  						 	else if( ret == 0)//������뵽 ��ͨ˫����list
  						 		{
  						 			DEBUG("ndcs.column_name��%s is not index field!\n" , ndcs.column_name.c_str() ); 
  						 			DEBUG("Find normal double conditions��and push_back it \n");
  						 			normal_double_condition_list.push_back(ndcs);
  						 		  err = NOT_INDEX_FIELD;
  						 		}
  						 		else if( ret == DO_NOT_HAS_FIELD )//�����޸��ֶ�
  						 		{
  					  	 		DEBUG(" table: %s��do not have field :%s \n",ndcs.relation_name.c_str(), ndcs.column_name.c_str() );
  						 		}
  						 		else //��������
  						 			{
  						 			ERROR(" field_has_index err is %d ,and try next!\n",ret );
  						 			err = ret;
  						 			}
  					}
  				}
  				if( err != 0 && err != NOT_INDEX_FIELD )
  				{
  					ERROR("end get_single_table_conditions��err is %d \n",err);
  					return err;
  					
  				}
  				//���Ƿ��й�������
  				DEBUG("normal_double_condition_list.sort() \n");
  				normal_double_condition_list.sort();
  				
  				//
  				for(auto &join_condition : join_conditions ){//���ҹ��������б���
  					join_eq_condition_struct jecs(join_condition,qa);
  					err = jecs.get_name();
  					if( err == 0 &&( 0 == strcmp( jecs.relation_name[0].c_str(),(*mem_table)->config.table_name) || 0 == strcmp( jecs.relation_name[1].c_str(),(*mem_table)->config.table_name ) ) ){
  					DEBUG("Find join conditions��and push_back it \n");
  					join_eq_condition_list.push_back(jecs);
  					}
  				}
  				
  				if( err != 0 && err != NOT_INDEX_FIELD )
  				{
  					ERROR("end get_single_table_conditions��err is %d \n",err);
  					return err;
  					
  				}
  				
  				//	
  				for(auto &const_condition : const_conditions ){//���ҳ��������б��У��ж��Ƿ��·
  					const_condition_struct ccs(const_condition,qa);
  					err = ccs.is_drop();
  					if( err == 0   ){
  						DEBUG("Find const conditions��and push_back it \n");
  						const_condition_list.push_back(ccs);
  					}
  					else if(err == INFO_BROCKEN ){
  					//	qa->is_broken = 1;
  					return INFO_BROCKEN;
  					
  					}
  				}
  				if( err != 0 && err != NOT_INDEX_FIELD )
  				{
  					ERROR("end get_single_table_conditions��err is %d \n",err);
  					return err;
  					
  				}
  			}
  		}
  DEBUG("end get_single_table_conditions \n");
	return err;
  }


inline int get_table_conditions(
													/*in*/  QueryAnalyser * qa,										
													/*out*/ std::map<std::string,mem_table_t *>&       mem_table_ptr_map, 																			  //(����,��ָ��)
  												/*out*/ std::map<std::string,std::list<normal_single_condition_struct> >& normal_single_condition_map,				//(����,�������б�)
  												/*out*/ std::map<std::string,std::list<normal_double_condition_struct> >& normal_double_condition_map,				//(����,˫�����б�)
  												/*out*/ std::map<std::string,std::list<normal_double_condition_struct> >& normal_index_double_condition_map,	//(����,����˫�����б�)										
													/*out*/	std::map<std::string,std::list<join_eq_condition_struct      > >& join_eq_condition_map,  				    // ��������
													/*out*/ std::map<std::string,std::list<const_condition_struct> >        & const_condition_map,							  //(����,���������б�)	
													/*out*/ std::map<std::string,std::set<std::string> >                    & condition_fields                    //(����,�����ֶ��б�)	

)
{
	int ret = 0;
	for (size_t i = 0 ;i <qa->tables.size();++i )
	{
		std::string table_name = qa->tables[i].table_name_;
		mem_table_t * mem_table_ptr = NULL;
		std::list<normal_single_condition_struct>  normal_single_condition_list;
  	std::list<normal_double_condition_struct>  normal_double_condition_list;
  	std::list<normal_double_condition_struct>  normal_index_double_condition_list;		
  	std::list<join_eq_condition_struct> 			 join_eq_condition_list;									
		std::list<const_condition_struct> 				 const_condition_list;
			
	  ret = get_single_table_conditions(qa,
																i,
																&mem_table_ptr,
																normal_single_condition_list,
																normal_double_condition_list,
																normal_index_double_condition_list,
																join_eq_condition_list,
																const_condition_list
																);
     if( ret != 0 && ret != NOT_INDEX_FIELD )
  	{
  		ERROR("end get_single_table_conditions��err is %d \n",ret);
  		return ret;
  	}
																
		mem_table_ptr_map[table_name] 								= mem_table_ptr;
		qa->tables[i].mem_table                       = mem_table_ptr;
		normal_single_condition_map[table_name] 			= normal_single_condition_list;
		normal_double_condition_map[table_name] 			= normal_double_condition_list;
		normal_index_double_condition_map[table_name] = normal_index_double_condition_list;
		join_eq_condition_map[table_name] 					  = join_eq_condition_list;
		const_condition_map[table_name] 							= const_condition_list;
		//_________________________________________________________________________
		// ����ñ�����������ֶ�
		
		for(auto &v : normal_single_condition_list ){
		condition_fields[table_name].insert(v.column_name);
	  }
		for(auto &v : normal_double_condition_list ){
			condition_fields[table_name].insert(v.column_name);
		}
		for(auto &v : normal_index_double_condition_list ){
			condition_fields[table_name].insert(v.column_name);
		}
		for(auto &v : join_eq_condition_list ){
			if(v.relation_name[0] == table_name )condition_fields[table_name].insert(v.column_name[0]);
			if(v.relation_name[1] == table_name )condition_fields[table_name].insert(v.column_name[1]);
		}
		
	}
	return ret;
	
}

// ���һ������Ҫ�����е��ֶΣ� ͶӰ�ֶ� + �����ֶ� ��
inline int get_table_scan_fields(
																/*in*/  QueryAnalyser * qa,										
																/*in*/	std::map<std::string,std::set<std::string> >&  projection_fields, // ͶӰ�ֶ�
																/*in*/  std::map<std::string,std::set<std::string> >&  condition_fields,  // �����ֶ�
																/*out*/ std::map<std::string,std::set<std::string> >&  scan_fields        // ��Ҫɨ����ֶ�
)
{
	DEBUG(" get_table_scan_fields enter \n");
	int ret = 0;
	for (size_t i = 0 ;i <qa->tables.size();++i )
	{
				std::string table_name = qa->tables[i].table_name_;
					
				/*
				std::set<std::string> needed; = condition_fields[table_name];					
				std::set<std::string> needed2  = projection_fields[table_name];
					
				needed.insert( needed2.begin(), needed2.end() );
	      scan_fields[table_name] = needed2;	
	      //scan_fields[table_name] = needed;	
	      */
	      
	     
	      scan_fields[table_name].insert( projection_fields[table_name].begin(), projection_fields[table_name].end() );
	      scan_fields[table_name].insert( condition_fields[table_name].begin(),  condition_fields[table_name].end() );
	      
	}
}
	
	// ���һ����������ͶӰ�ֶ� 
inline int get_table_result_fields(
																/*in*/  QueryAnalyser * qa,										
																/*in*/	std::map<std::string,std::set<std::string> >&  projection_fields, // ͶӰ�ֶ�
																/*out*/ std::map<std::string,std::set<std::string> >&  result_fields        //�������ͶӰ�ֶ� 
)
{
	DEBUG(" get_table_result_fields enter \n");
	int ret = 0;
	for (size_t i = 0 ;i <qa->tables.size();++i )
	{
				std::string table_name = qa->tables[i].table_name_;
					
				/*
				std::set<std::string> needed; = condition_fields[table_name];					
				std::set<std::string> needed2  = projection_fields[table_name];
					
				needed.insert( needed2.begin(), needed2.end() );
	      scan_fields[table_name] = needed2;	
	      //scan_fields[table_name] = needed;	
	      */
	      
	      result_fields[table_name].insert( projection_fields[table_name].begin(), projection_fields[table_name].end() );
	
	DEBUG(" Leave get_table_result_fields \n");
	return ret;
}

}





//  �Թ���������������
//1 �������ٵĹ�����ϵ ȥ���� ʣ�µ��ܹ�������С������ϵ  min(last.filter)
//2 �����ѹ����� �ڶ��ٵĹ�����ϵ ȥ���� ʣ�µ��ܹ�������С������ϵ
//3 �����ѹ����� ��3�ٵĹ�����ϵ ȥ���� ʣ�µ��ܹ�������С������ϵ
//4 ʣ�µĹ���Ϊ0 ���ɹ�������ʧ��

inline int order_join_condtions(
														/*in*/QueryAnalyser * qa,	
														/*out*/std::vector<join_eq_condition_struct> &join_eq_condition_origin)// ԭʼ��������
{	
	DEBUG("begin order_join_condtions() \n ");
	if( NULL == qa ) return QueryAnalyserNullPtr;
		
	vector<rapidjson::Value *>& join_conditions	 = qa->join_conditions;
	
	// ���� ԭʼ��������
	for( auto& v : join_conditions )
	{
		join_eq_condition_struct join_eq_condition( v ,qa );
		
			if( (*v)["tag"].GetInt() == T_OP_EQ )
			{
				join_eq_condition.get_name();
				join_eq_condition_origin.push_back(join_eq_condition);
			}
	}

// �Ȱ���ˮλ������
std::sort (join_eq_condition_origin.begin(),join_eq_condition_origin.end() );
// �������ٵĹ�����ϵ ȥ���� ʣ�µ��ܹ�������С������ϵ  min(last.filter)
for(std::vector<join_eq_condition_struct>::iterator iter= join_eq_condition_origin.begin();
	iter != join_eq_condition_origin.end() && iter+1 != join_eq_condition_origin.end() ;++iter
)
{
	//��������
	int i = 0;
	for(std::vector<join_eq_condition_struct>::iterator iter2 = iter+1;
		iter2!=join_eq_condition_origin.end();++iter2)
		{
			int ret = iter->can_link_or_delete(*iter2);
			switch(ret){
				case NEED_DELETE:continue; //�Ȳ������ظ���
				case 0:continue;
				case 1:{ // ����λ��
					if(iter2 == iter+i)continue;
						else {
						  ++i;	
							std::swap( *(iter+i),*iter2 );
							
						}
					
				}
				
			}
		}
		
		if( 1 != iter->can_link_or_delete( *(iter+1)) )
			{
				ERROR("ERR_NOT_FOUND_LINK\n");
				return ERR_NOT_FOUND_LINK;
			}
		iter += i;

}
	DEBUG("end order_join_condtions() \n ");
return 0;
}

#endif 