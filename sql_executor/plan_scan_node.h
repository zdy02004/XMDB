//g++ -C -std=c++11 plan_scan_node.h -w

#ifndef PLAN_SCAN_NODE
#define PLAN_SCAN_NODE


#include "../operations/ops.hpp"
#include "../operations/index_scan_Addr.hpp"
#include "plan_node.h"


#define PLAN_TYPE_HASH_INDXE_SCAN   				1
#define PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN		2
#define PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN		3
#define PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN		4
#define PLAN_TYPE_SKIPLIST_LE_INDXE_SCAN		5
#define PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN		6
#define PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN		7
#define PLAN_TYPE_FULL_SCAN									8
#define PLAN_TYPE_SCAN_NORMAL								9
#define PLAN_TYPE_SCAN_SFW  								10
#define PLAN_TYPE_MERGE											11
#define PLAN_TYPE_MERGE_SFW									12

// hash index 父类
struct scan_hash_index_node:public plan_node
{
long index_no;						  // 索引 id
int  index_type;            // 1 hash 2 skiplist
mem_table_t *mem_table;		  // 表地址
mem_hash_index_t * index;	  // 索引地址
                            
std::string relation_name ; //表名
std::string column_name   ; //列名
std::string const_value   ; //常数值
std::string const_type    ; //常数类型
	
//std::list<finded_Addr_t> ret_list;//结果集
finded_Addr_t   ret_list;	//索引结果集
finded_Addr_t * finded_Addr; //与结果求交集

scan_hash_index_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),index_no(_index_no),
  																					index_type(_index_type),mem_table(_mem_table),
  																					index(_index),relation_name(_relation_name),
  																					column_name(_column_name),const_value(_const_value),
  																					const_type(_const_type),finded_Addr(_finded_Addr)
{
ret_size = mem_table->record_size - RECORD_HEAD_SIZE;
}

virtual void make_json() = 0;
virtual std::string to_sring ()  = 0;
virtual int execute( unsigned long long  trans_no  ) = 0 ;
	
};

// skiplist index 父类
struct scan_skiplist_index_node:public plan_node
{
long index_no;						  // 索引 id
int  index_type;            // 1 hash 2 skiplist
mem_table_t *mem_table;		  // 表地址
mem_skiplist_index_t * index;	  // 索引地址
                            
std::string relation_name ; //表名
std::string column_name   ; //列名
std::string const_value   ; //常数值
std::string const_type    ; //常数类型
	
//std::list<finded_Addr_t> ret_list;//结果集
finded_Addr_t   ret_list;	//索引结果集
finded_Addr_t * finded_Addr; //与结果求交集


scan_skiplist_index_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),index_no(_index_no),
  																					index_type(_index_type),mem_table(_mem_table),
  																					index(_index),relation_name(_relation_name),
  																					column_name(_column_name),const_value(_const_value),
  																					const_type(_const_type),finded_Addr(_finded_Addr)
{
ret_size = mem_table->record_size - RECORD_HEAD_SIZE;
}

virtual void make_json() = 0;
virtual std::string to_sring () = 0;
virtual int execute( unsigned long long  trans_no  )= 0 ;
	
};


// hash index 扫描节点
struct scan_index_hash_node:public scan_hash_index_node
{
scan_index_hash_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_hash_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_hash_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_HASH_INDXE_SCAN;}

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_index_hash_node execute(%ld）------------- { \n",trans_no);
int ret = 0;
if( const_type == "INTNUM" )
{
	ret =	mem_hash_index_scanAddr_long (
														mem_table,
														index,
														atoi(const_value.c_str()),
														integer_hash_fun,
														trans_no,
														*finded_Addr,
														ret_list,
														oper_type
														 );
}

if( const_type == "STRING" )
{
	ret =	mem_hash_index_scanAddr_str (
														mem_table,
														index,
														const_cast<char *>(const_value.c_str() ),
														str_hash_fun,
														trans_no,
														*finded_Addr,
														ret_list,
														oper_type
														 );
}
  DEBUG("scan_index_hash_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};
// skiplist index eq 扫描节点
struct scan_skiplist_eq_node:public scan_skiplist_index_node
{

scan_skiplist_eq_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t* _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){ plan_type = PLAN_TYPE_SKIPLIST_EQ_INDXE_SCAN; }

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_skiplist_eq_node execute(%ld）------------- { \n",trans_no);
int ret = 0;
mem_skiplist_entry_t *last_find_entry = NULL;

if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	
	ret = mem_skiplist_index_scanAddr_long(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                                (&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
																ret_list,	    //原始结果集
																oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey, const_value.c_str() );
	
	ret = mem_skiplist_index_scanAddr_str(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
								               ret_list	,    //原始结果集
								               oper_type
                        );
}
  
  DEBUG("scan_skiplist_eq_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}


virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};

// skiplist index ge 扫描节点
struct scan_skiplist_ge_node:public scan_skiplist_index_node
{

scan_skiplist_ge_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_GE_INDXE_SCAN;}

virtual int execute( unsigned long long  trans_no )
{
DEBUG("scan_skiplist_ge_node execute(%ld）------------- { \n",trans_no);
int ret = 0;
mem_skiplist_entry_t *last_find_entry = NULL;

if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_GE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
								                ret_list,	    //原始结果集
								                oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str() );
	
	ret = mem_skiplist_index_scanAddr_str_GE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
								                ret_list,	    //原始结果集
								                oper_type
                        );
}
  DEBUG("scan_skiplist_ge_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};

// skiplist index gt 扫描节点
struct scan_skiplist_gt_node:public scan_skiplist_index_node
{

scan_skiplist_gt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_GT_INDXE_SCAN;}

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_skiplist_gt_node execute(%ld）------------- { \n",trans_no);

mem_skiplist_entry_t *last_find_entry = NULL;

int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_G(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
															ret_list,	    //原始结果集
															oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_G(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
																ret_list,	    //原始结果集
																oper_type
                        );
}
  DEBUG("scan_skiplist_gt_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}
	
};

// skiplist index le 扫描节点
struct scan_skiplist_le_node:public scan_skiplist_index_node
{

scan_skiplist_le_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_LE_INDXE_SCAN;}

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_skiplist_le_node execute(%ld）------------- { \n",trans_no);
	
mem_skiplist_entry_t *last_find_entry = NULL;

int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_LE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
							                	ret_list,	    //原始结果集
							                	oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_LE(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                               trans_no,
                          		*finded_Addr,
								               ret_list,    //原始结果集
								               oper_type
                        );
}
  DEBUG("scan_skiplist_le_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};


// skiplist index lt 扫描节点
struct scan_skiplist_lt_node:public scan_skiplist_index_node
{

scan_skiplist_lt_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type,_finded_Addr){plan_type = PLAN_TYPE_SKIPLIST_LT_INDXE_SCAN;}

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_skiplist_lt_node execute(%ld）------------- { \n",trans_no);
	
mem_skiplist_entry_t *last_find_entry = NULL;

int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t in;
	in.lkey  = atol(const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_long_L(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		  *finded_Addr,
								                ret_list,	    //原始结果集
								                oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t in;
	strcpy(in.ckey , const_value.c_str());
	
	ret = mem_skiplist_index_scanAddr_str_L(  
                                mem_table,
                        /* in */index,
                        /* in */&in             ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
							                	ret_list,	    //原始结果集
							                	oper_type
                        );
}
  DEBUG("scan_skiplist_lt_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};

// skiplist index btw 扫描节点
struct scan_skiplist_btw_node:public scan_skiplist_index_node
{
std::string const_value_array[2];
std::string const_type_array[2];
	
scan_skiplist_btw_node(long _index_no,
  								int  _index_type,
  								mem_table_t *_mem_table,
  								mem_skiplist_index_t * _index,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value1,
  								std::string& _const_type1,
  								std::string& _const_value2,
  								std::string& _const_type2,
  								finded_Addr_t * _finded_Addr):scan_skiplist_index_node( _index_no,
  																				  _index_type,
  																					_mem_table,
  																					_index,
  																					_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value1,
  																					_const_type1,_finded_Addr){
  																						const_value_array[0] = _const_value1;
  																						const_value_array[1] = _const_value2;
  																						const_type_array[0]  =  _const_type1;
  																						const_type_array[0]  =  _const_type2;
  																						plan_type =PLAN_TYPE_SKIPLIST_BTW_INDXE_SCAN ;}

virtual int execute(unsigned long long  trans_no  )
{
DEBUG("scan_skiplist_btw_node execute(%ld）------------- { \n",trans_no);
	
mem_skiplist_entry_t *last_find_entry = NULL;

int ret = 0;
if( const_type == "INTNUM" )
{
	mem_skiplist_entry_t min,max;
	min.lkey  = atol(const_value_array[0].c_str());
	max.lkey  = atol(const_value_array[1].c_str());
	
	ret = mem_skiplist_index_scanAddr_long_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,&max,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
															 ret_list,	    //原始结果集
															 oper_type
                        );
}

if( const_type == "STRING" )
{
	mem_skiplist_entry_t min,max;
	strcpy(min.ckey  , const_value_array[0].c_str() );
	strcpy(max.ckey  , const_value_array[1].c_str() );
	
	ret = mem_skiplist_index_scanAddr_str_btw(  
                                mem_table,
                        /* in */index,
                        /* in */&min,&max            ,
                        /* in */(&last_find_entry),  //NULL,
                                trans_no,
                          		*finded_Addr,
																ret_list,	    //原始结果集
																oper_type
                        );
}
  DEBUG("scan_skiplist_btw_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}
virtual std::list<generic_result>* get_ret_list()
{
	return NULL;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};


// skiplist merg 索引节点
struct merg_index_node:public plan_node
{
finded_Addr_t * finded_Addr;
std::list<generic_result> ret_list;
	
mem_table_t *mem_table;
merg_index_node(
  								mem_table_t *_mem_table,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),mem_table(_mem_table),
  																					finded_Addr(_finded_Addr){plan_type =PLAN_TYPE_MERGE;}

virtual int execute( unsigned long long trans_no  )
{
DEBUG("merg_index_node execute(%ld）------------- { \n",trans_no);
	

int ret = 0;
ret =  merg_index_result(  
                                mem_table,
								*finded_Addr, 
                 trans_no,                 //当前事务ID
								&ret_list,		    //原始结果集
								oper_type
                        );
  DEBUG("merg_index_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}



};



//  merg 索引与无索引的融合扫描节点
struct merg_index_sfw_node:public plan_node
{
finded_Addr_t * finded_Addr;
compare_list*com_list;                  //比较函数链
std::set<std::string>   pro_list;				//原始投影字段列表

std::list<generic_result> ret_list;
	
mem_table_t *mem_table;
merg_index_sfw_node(
  								mem_table_t *_mem_table,
  								compare_list*_com_list,
  								std::set<std::string>& _pro_list,
  								rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								finded_Addr_t * _finded_Addr):plan_node(_json,_Doc),mem_table(_mem_table),
  																							com_list(_com_list),pro_list(_pro_list),
  																							finded_Addr(_finded_Addr){plan_type = PLAN_TYPE_MERGE_SFW;}

virtual int execute( unsigned long long trans_no  )
{
DEBUG("merg_index_sfw_node execute(%ld）------------- { \n",trans_no);

int ret = 0;
ret =  merg_index_result_with_prolist_and_conlist(  
                mem_table,
								*finded_Addr,
								com_list, 			 //比较函数链
								pro_list,       //原始投影字段列表
                 trans_no,       //当前事务ID
								&ret_list,		     //原始结果集
								oper_type
                        );
  DEBUG("merg_index_sfw_node execute(%ld）------------- } \n",trans_no);		
	return ret;
	
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}



};

// 普通全表相等条件,带投影和条件 扫描
// select * from where 打包节点 sfw
struct scan_sfw_node:public plan_node
{
	
	//std::string relation_name;
  //std::string column_name;
  //std::string const_value;
  //std::string const_type;
 	mem_table_t * mem_table;
 	compare_list * pre;
 	std::set<std::string>     pro_list;//投影集
  std::list<generic_result> ret_list;//结果集
									
scan_sfw_node(mem_table_t * _mem_table , 
									//field_t&  _field,
									compare_list * _pre,
									std::set<std::string>&  _pro_list,//投影集
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc //,
  								//std::string& _relation_name,
  								//std::string& _column_name,
  								//std::string& _const_value,
  								//std::string& _const_type
  								):plan_node(_json,_Doc),
  																					mem_table(_mem_table),
  																					pre(_pre),
  																					//relation_name(_relation_name),
  																					//column_name(_column_name),
  																					//const_value(_const_value),
  																					//const_type(_const_type),
  																					pro_list(_pro_list)
  																					{plan_type = PLAN_TYPE_SCAN_SFW;
  																					DEBUG("construct pre->field_name is %s \n",pre->field_name);

  																						}
  																					
virtual int execute( unsigned long long  trans_no  )
{
DEBUG("scan_sfw_node execute(%ld）------------- { \n",trans_no);

	DEBUG("pre->field_name is %s \n",pre->field_name);
	int ret = 0;
  ret = full_table_scan_with_prolist_and_conlist(
														 mem_table,       //表
														 pre,             //比较函数链
														 pro_list,				//原始投影字段
														 trans_no,//get_trans_no()                 //当前事务ID
													 	 &ret_list,  	    //原始结果集
													 	 oper_type
);

DEBUG("scan_sfw_node execute(%ld）------------- } \n",trans_no);		
return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};


// 普通全表相等条件 扫描
struct scan_normal_node:public plan_node
{
	
	std::string relation_name;
  std::string column_name;
  std::string const_value;
  std::string const_type;
 	mem_table_t * mem_table;
 	compare_list * pre;
  std::list<generic_result> ret_list;//结果集
									
scan_normal_node(mem_table_t * _mem_table , 
									field_t&  _field,
									compare_list * _pre,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):plan_node(_json,_Doc),
  																					mem_table(_mem_table),
  																					pre(_pre),
  																					relation_name(_relation_name),
  																					column_name(_column_name),
  																					const_value(_const_value),
  																					const_type(_const_type){plan_type = PLAN_TYPE_SCAN_NORMAL;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
DEBUG("scan_normal_node execute(%ld）------------- { \n",trans_no);

	int ret = 0;
  ret = full_table_scan_with_conlist(
														 mem_table,       //表
														 pre,             //比较函数链
														 trans_no,//get_trans_no()                 //当前事务ID
													 	 &ret_list , 	  //原始结果集
													 	 oper_type
);

DEBUG("scan_normal_node execute(%ld）------------- } \n",trans_no);		
	return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};

// 普通全表扫描
struct full_scan_node:public plan_node
{
	
 	mem_table_t * mem_table;
  std::list<generic_result> ret_list;//结果集
									
full_scan_node(mem_table_t * _mem_table , 
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc
):plan_node(_json,_Doc),mem_table(_mem_table){plan_type = PLAN_TYPE_FULL_SCAN;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
DEBUG("full_scan_node execute(%ld）------------- { \n",trans_no);

	int ret = 0;
  ret = full_table_scan( mem_table,       //表
												 trans_no,//get_trans_no()                 //当前事务ID
												 &ret_list , 	  //原始结果集
												 oper_type
);

DEBUG("full_scan_node execute(%ld）------------- } \n",trans_no);		
	return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}

};




#endif 
