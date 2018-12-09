//g++ -w -C   ops.hpp   -g   -lpthread -std=c++11 
/*修改了部分代码支持    条件下推*/

#ifndef BASIC_OPS
#define BASIC_OPS

#define BASIC_OPS_SCAN    0
#define BASIC_OPS_DELETE  1
#define BASIC_OPS_UPDATE  2

#include"../mem_date_index_ctl/mem_table_mvcc_op.h"
#include"../sql_executor/record_tuple.h"
#include<vector>
#include<list>
#include<functional>
#include<cstdlib>
#include<iostream>

template<int size>
struct selection_obj
{
	char data[size];
	
	selection_obj( char *buf )
	{
		memcpy(data,buf,size);
	}
	selection_obj( selection_obj<size> & selection )
	{
		memcpy(data,selection->data,size);
	}
	
	selection_obj<size> & operator = ( selection_obj<size> & selection )
	{
		memcpy(data,selection->data,size);	
		return * this;			
	}
	
};

template<int v>  
struct Int2Type  
{  
  enum{value=v};  
};  

template<int v>
struct get_field_by_index
{
	static void get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ;	
	}
};

template<>
struct get_field_by_index<1>
{
	static FIELD_INT* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_INT*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};

template<>
struct get_field_by_index<2>
{
	static FIELD_SHORT* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_SHORT*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};

template<>
struct get_field_by_index<3>
{
	 static FIELD_LONG* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_LONG*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};

template<>
struct get_field_by_index<4>
{
	static FIELD_LONGLONG* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_LONGLONG*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};
template<>
struct get_field_by_index<5>
{
	static FIELD_FLOAT* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_FLOAT*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};
template<>
struct get_field_by_index<6>
{
	static FIELD_DOUBLE* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_DOUBLE*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};
template<>
struct get_field_by_index<7>
{
	static FIELD_DATE* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_DATE*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};
//template<>
//struct get_field_by_index<8>
//{
//	static mem_hash_entry_t* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
//	{
//	  return ( mem_hash_entry_t*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
//	}
//};
//template<>
//struct get_field_by_index<9>
//{
//	static mem_rbtree_entry_t* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
//	{
//	  return ( mem_rbtree_entry_t*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
//	}
//};
//
//template<>
//struct get_field_by_index<10>
//{
//	static mem_skiplist_entry_t* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
//	{
//	  return ( mem_skiplist_entry_t*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
//	}
//};

template<>
struct get_field_by_index<11>
{
	static FIELD_STR* get(struct mem_table_t *mem_table,struct record_t * record_ptr, int j)
	{
	  return ( FIELD_STR*)((char *)(record_ptr) + RECORD_HEAD_SIZE + mem_table->config.fields_table[j].field_dis );	
	}
};


	

inline int get_field_index(char * field_name,struct mem_table_t *mem_table/*,field_type * field*/ )//表
{
	int j = 0;
	int  field_used_num = 0;
	struct field_t  * fields_table;
	if(NULL != field_name)
	{
	DEBUG("get filed name is :%s \n",field_name);
	
	fields_table   =  mem_table->config.fields_table;
	field_used_num =  mem_table->config.field_used_num;
	for(;j< field_used_num;++j)
	{
		if(  strcmp( fields_table[j].field_name,field_name ) == 0 )
		{
			  DEBUG("FOUND field_name:%s,and index is %d \n",field_name,j);
				return j;//找到字段就退出，j就是对应的字段顺序号
		}
	}
  }
  ERROR("NOT FOUND field_name:%s\n",field_name);
	return -1;
}


struct compare_list
{
	
	struct mem_table_t *mem_table; // 表
	char   field_name[32];    				 //字段名
	std::string cmp_field_value;        //比较字段值
	void * fun;                    //比较函数
	struct compare_list * next;
	//switch_fun_class switch_fun;
	
	public:
	compare_list(){}
	~compare_list(){}
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)(cmp_field_value.c_str()) ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) == (*b) );
	}
} __attribute__ ((packed, aligned (64)));

struct full_scan_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		return true;
	}
} __attribute__ ((packed, aligned (64)));


struct compare_le_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)cmp_field_value ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) <= (*b) );
	}
} __attribute__ ((packed, aligned (64)));

struct compare_lt_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)cmp_field_value ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) < (*b) );
	}
} __attribute__ ((packed, aligned (64)));


struct compare_ge_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)cmp_field_value ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) >= (*b) );
	}
} __attribute__ ((packed, aligned (64)));

struct compare_gt_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)cmp_field_value ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) > (*b) );
	}
} __attribute__ ((packed, aligned (64)));

struct compare_ne_list:public compare_list
{

public:
	// 对于特殊情况，请重载该函数	
	template< typename field_type1 > 
	int cmp_fun(field_type1* a)
	{
		//int j = -1;
		//j = get_field_index(  field_name,mem_table ) ;
		field_type1* b = (field_type1*)cmp_field_value ;
		DEBUG("cmp_fun\n");
		CPP_DEBUG<<"record_value is "<<*a<<std::endl;
		CPP_DEBUG<<"cmp_field_value is "<<*b<<std::endl;
		return !( (*a) != (*b) );
	}
} __attribute__ ((packed, aligned (64)));


#define __get_field_help__(field_type_nr) case field_type_nr: return cmp_list->cmp_fun( get_field_by_index<field_type_nr>::get(mem_table, record_ptr, j ) );


int get_field_by_index_help(struct compare_list * cmp_list,struct mem_table_t *mem_table,struct record_t * record_ptr, int j,int field_type_nr)
{
	DEBUG("field_type_nr is %d\n",field_type_nr);
switch (field_type_nr)
{
__get_field_help__(1)
__get_field_help__(2)
__get_field_help__(3)
__get_field_help__(4)
__get_field_help__(5)
__get_field_help__(6)
__get_field_help__(7)
//__get_field_help__(8)
//__get_field_help__(9)
//__get_field_help__(10)
__get_field_help__(11)
}
return -1;
}


//fun 遍历函数
//param 函数参数
template<typename record_type,typename field_list_type,typename oper_list_type >
inline int full_table_scan_with_prolist_and_conlist(
														struct mem_table_t *mem_table,    //表
														compare_list*com_list,            //比较函数链
														field_list_type& field_list,      //原始投影字段
														oper_list_type&  oper_condition_lists,//运算列表
														unsigned long long  Tn,           //当前事务ID
														std::list<record_type>* ret,	    //原始结果集
														int oper_type = BASIC_OPS_SCAN    //操作类型默认是扫描
														
) 
{
	  DEBUG("enter full_table_scan_with_prolist_and_conlist ---------------{ \n");
	  //如果原始投影字段为空则走全表全字段扫描
	  if(field_list.empty() && com_list == NULL ){
	  	return full_table_scan_with_conlist(
														mem_table,    //表
														com_list,     //比较函数链
														Tn,           //当前事务ID
														ret		        //原始结果集
														);
	  	
	  }
	  
	  
	  //条件字段需要的变量
   	int j = -1;
	  int is_ok = 0;
	  compare_list * com_list_iter = com_list;
  
	  struct field_t  *fields_table =  mem_table->config.fields_table;
	  int  field_used_num = 0;
	  field_used_num =  mem_table->config.field_used_num;

    //抽取字段需要的变量
     DEBUG("get pro_fields and pro_size \n");

    //构造抽取字段列表
    std::list<field_t> pro_fields;
    //抽取字段总长度
    size_t  pro_size = 0;
    int k;
    for(auto &one : field_list){
    	
    	k = get_field_index(const_cast<char *>(one.c_str() ) , mem_table );
    	DEBUG("get_field_index(%s) return %d\n",one.c_str(),k);
			if( k>=0 && k< field_used_num ){
				 //field = ( field_type * )( (char *)(record_ptr) + RECORD_HEAD_SIZE + fields_table[k].field_dis );
				 pro_fields.push_back(fields_table[k]);
				 pro_size += fields_table[k].field_size;
			}
    	
    }
    
    DEBUG(" pro_size is %ld \n",pro_size);

   //
    char buf[mem_table->record_size - RECORD_HEAD_SIZE];
    
    record_type return_record;
		return_record.set_row_size(pro_size);	
    return_record.allocate(pro_size);
    
    int __i = 0;									 
    struct record_t     * record_ptr = NULL;
    struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	

	struct record_meta  one_meta;
	one_meta.from_table(mem_table);
    struct generic_result result_temp;
	result_temp.set_data(buf);
	result_temp.set_row_size(mem_table->record_size - RECORD_HEAD_SIZE);
	
	for(;__i<mem_table->config.mem_block_used;++__i)//遍历所有块																
	{
		  DEBUG(" Scan mem_table block[%ld] \n",__i);
			unsigned  long  __high_level_temp = 0;

				for(; //遍历所有行
				__mem_block_temp->space_start_addr + (__high_level_temp)* (mem_table->record_size) < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
					  //DEBUG(" Scan mem_table.block[%ld].record[%ld] \n",__i,__high_level_temp);
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__high_level_temp) * (mem_table->record_size) );
						// 已经删除的行不处理
						if(record_ptr->is_used != 1)continue;
					  DEBUG("record_ptr addr is %0x,record_ptr->is_used = %d\n",record_ptr,record_ptr->is_used);

						is_ok = 1;	
						while(com_list_iter)
						{
						//获得字段在字段表中的排序位置
						j = -1;
	          j = get_field_index(com_list_iter->field_name,mem_table/*,field*/ );
						DEBUG("get_field_index is %d \n",j);
						//处理每一行记录
						if( -1 != j && field_used_num != j )//条件判断
						{		
							  int field_type_nr = fields_table[j].field_type;
							  //int const field_type_const_nr = const_cast<int >(field_type_nr);
							  //auto field = get_field_by_index<field_type_nr>::get(mem_table, record_ptr, j,field_type_nr ) ;
							  int get_field_ret = get_field_by_index_help(com_list_iter,mem_table, record_ptr, j,field_type_nr );
							  DEBUG("get_field_ret is %d \n",get_field_ret);

							  if( get_field_ret != 0 )
									{
										DEBUG("is_ok = 0  \n");
									  is_ok = 0 ;
										break;
									}
						}
		
						if(com_list_iter)
							{
								com_list_iter = com_list_iter->next;
								DEBUG("com_list_iter = com_list_iter->next; \n");
							}
					}
					com_list_iter = com_list;
					
					 DEBUG("Try to read  \n");
					 if( is_ok && !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn )/*!mem_table_read_record(mem_table , record_ptr, (char *)buf )*/ )
						{
							 DEBUG("if( is_ok && !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn )! \n");
							 for( auto &one_oper_condition : oper_condition_lists )
							 {
								 if( 0 == one_oper_condition.eval(&one_meta , &result_temp ).int_value )
								 {
									 continue;
								 }
							 }


							 if( BASIC_OPS_SCAN == oper_type )
							 {
								 size_t pos = 0;
								 for(auto &one_field : pro_fields){
								 	memcpy(return_record.get_data()+pos,buf+one_field.field_dis,one_field.field_size );
								 	pos += one_field.field_size;
								 }
									
									DEBUG("Find one record!\n");
									ret->emplace_back( return_record );
							 }
							 
							 if( BASIC_OPS_DELETE == oper_type )
							 {
							 	int err = 0;
							 	err = mem_mvcc_delete_record(mem_table ,
																				record_ptr,
																				Tn               // 本事务ID
																				);
								if( 0 != err)	{
									ERROR("mem_mvcc_delete_record err is %d\n",err);
									return err;
								}											
							 }
							 
						}
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
  DEBUG("leave full_table_scan_with_prolist_and_conlist ---------------} \n");
	return 0;
}


//全表扫描
//fun 遍历函数
//param 函数参数
template<typename record_type >
inline int full_table_scan_with_conlist(
														struct mem_table_t *mem_table,       //表
														compare_list*com_list,               //比较函数链
														unsigned long long  Tn,              //当前事务ID
														std::list<record_type>* ret	,  	     //原始结果集
														int oper_type = BASIC_OPS_SCAN    //操作类型默认是扫描
														
) 
{
   	int j = -1;
	  int is_ok = 0;
	  compare_list * com_list_iter = com_list;
 
	  struct field_t  *fields_table =  mem_table->config.fields_table;
	  int  field_used_num = 0;
	  field_used_num =  mem_table->config.field_used_num;

    char buf[mem_table->record_size - RECORD_HEAD_SIZE];
    record_type return_record;
		return_record.set_row_size(mem_table->record_size - RECORD_HEAD_SIZE);	
    return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);
    
    int __i = 0;									 
    struct record_t     * record_ptr = NULL;
    struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
     
	for(;__i<mem_table->config.mem_block_used;++__i)//遍历所有块																
	{
			unsigned  long  __high_level_temp = 0;

				for(; //遍历所有行
				__mem_block_temp->space_start_addr + (__high_level_temp)* (mem_table->record_size) < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
					//DEBUG("__high_level_temp = %ld\n",__high_level_temp);
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__high_level_temp) * (mem_table->record_size) );
						// 已经删除的行不处理
						if(record_ptr->is_used != 1)continue;
					  DEBUG("record_ptr addr is %0x,record_ptr->is_used = %d\n",record_ptr,record_ptr->is_used);

						is_ok = 1;	
						while(com_list_iter)
						{
						//获得字段在字段表中的排序位置
						j = -1;
	          j = get_field_index(com_list_iter->field_name,mem_table/*,field*/ );
						DEBUG("get_field_index is %d \n",j);
						//处理每一行记录
						if( -1 != j && field_used_num != j )//条件判断
						{		
							  int field_type_nr = fields_table[j].field_type;
							  //int const field_type_const_nr = const_cast<int >(field_type_nr);
							  //auto field = get_field_by_index<field_type_nr>::get(mem_table, record_ptr, j,field_type_nr ) ;
							  int get_field_ret = get_field_by_index_help(com_list_iter,mem_table, record_ptr, j,field_type_nr );
							  DEBUG("get_field_ret is %d \n",get_field_ret);

							  if( get_field_ret != 0 )
									{
									  is_ok = 0 ;
										break;
									}
						}
		
						if(com_list_iter)com_list_iter = com_list_iter->next;
					}
					com_list_iter = com_list;
					
					 if( is_ok && !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn )/*!mem_table_read_record(mem_table , record_ptr, (char *)buf )*/ )
						{
							 if( BASIC_OPS_SCAN == oper_type )
							 {
							  //int size = mem_table->record_size ;
							  memcpy(return_record.get_data(),buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("Find one record!\n");
								ret->emplace_back( return_record );
							 }
							 
							 if( BASIC_OPS_DELETE == oper_type )
							 {
							 	int err = 0;
							 	err = mem_mvcc_delete_record(mem_table ,
																				record_ptr,
																				Tn               // 本事务ID
																				);
								if( 0 != err)	{
									ERROR("mem_mvcc_delete_record err is %d\n",err);
									return err;
								}		
							}
							
						
						}
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
	return 0;
}
 
 //表扫描
//un 遍历函数
//aram 函数参数
//template<>  typename record_type,  typename record_type
template<typename field_type,typename record_type >
inline int full_table_scan_with_con(
														struct mem_table_t *mem_table,       //表
														char * field_name,                   //字段名
														int (*compare_func)(field_type * field_name1,field_type * field_name2),//字段比较函数
														field_type * cmp_field_value,       //比较字段值
														unsigned long long  Tn,             //当前事务ID
														std::list<record_type>* ret,		    //原始结果集
														int oper_type = BASIC_OPS_SCAN      //操作类型默认是扫描
) 
{
   	int j = -1;
	  int  field_used_num = 0;
	  field_type * field;
	  struct field_t  * fields_table;
	//if(NULL != field_name)
	//{
	  fields_table        =  mem_table->config.fields_table;
	  field_used_num =  mem_table->config.field_used_num;
	//for(;j< field_used_num;++j)
	//{
	//	if(  strcmp( fields_table[j].field_name,field_name ) == 0 )
	//	{
	//			break;//找到字段就退出，j就是对应的字段顺序号
	//	}
	//}
 //}
 j = get_field_index(field_name, mem_table/*, field */ );
	
char buf[mem_table->record_size - RECORD_HEAD_SIZE];
record_type return_record;
return_record.set_row_size(mem_table->record_size - RECORD_HEAD_SIZE);	
return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);


int __i = 0;											 
struct record_t     * record_ptr;
struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
 
	for(;__i<mem_table->config.mem_block_used;++__i)//遍历所有块																
	{
			unsigned  long  __high_level_temp = 0;

				for(; //遍历所有行
				__mem_block_temp->space_start_addr + (__high_level_temp)* (mem_table->record_size) < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
					//DEBUG("__high_level_temp = %ld\n",__high_level_temp);
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__high_level_temp) * (mem_table->record_size) );
						// 已经删除的行不处理
						if(record_ptr->is_used != 1)continue;
					  DEBUG("record_ptr addr is %0x,record_ptr->is_used = %d\n",record_ptr,record_ptr->is_used);

	
						//处理每一行记录
						if( -1 != j && field_used_num != j )//条件判断
						{
							  field = ( field_type * )( (char *)(record_ptr) + RECORD_HEAD_SIZE + fields_table[j].field_dis );
								if( compare_func( field , cmp_field_value) != 0 )
									{
										continue;
									}
						}
						if( !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn) )
						{
							
							 if( BASIC_OPS_SCAN == oper_type )
							 {
							  memcpy(return_record.get_data(),buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("find one record!\n");
								ret->emplace_back( return_record );
							 }
							 
							 if( BASIC_OPS_DELETE == oper_type )
							 {
							 	int err = 0;
							 	err = mem_mvcc_delete_record(mem_table ,
																				record_ptr,
																				Tn               // 本事务ID
																				);
								if( 0 != err)	{
									ERROR("mem_mvcc_delete_record err is %d\n",err);
									return err;
								}		
							}
						}
						
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
	return 0;
}


 //表扫描
//un 遍历函数
//aram 函数参数
//template<>  typename record_type,  typename record_type,
template<typename record_type >
inline int full_table_scan(
														struct mem_table_t *mem_table,       //表
														unsigned long long  Tn,             //当前事务ID
														std::list<record_type>* ret	, 	    //原始结果集
														int oper_type = BASIC_OPS_SCAN    //操作类型默认是扫描
) 
{

char buf[mem_table->record_size - RECORD_HEAD_SIZE];
record_type return_record;
return_record.set_row_size(mem_table->record_size - RECORD_HEAD_SIZE);	
return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);


int __i = 0;											 
struct record_t     * record_ptr;
struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
 
	for(;__i<mem_table->config.mem_block_used;++__i)//遍历所有块																
	{
			unsigned  long  __high_level_temp = 0;

				for(; //遍历所有行
				__mem_block_temp->space_start_addr + (__high_level_temp)* (mem_table->record_size) < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
					//DEBUG("__high_level_temp = %ld\n",__high_level_temp);
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__high_level_temp) * (mem_table->record_size) );
						// 已经删除的行不处理
						if(record_ptr->is_used != 1)continue;
					  DEBUG("record_ptr addr is %0x,record_ptr->is_used = %d\n",record_ptr,record_ptr->is_used);

						if( !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn) )
						{
							 if( BASIC_OPS_SCAN == oper_type )
							 {
							  memcpy(return_record.get_data(),buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("find one record!\n");
								ret->emplace_back( return_record );
							 }
							 
							 if( BASIC_OPS_DELETE == oper_type )
							 {
							 	int err = 0;
							 	err = mem_mvcc_delete_record(mem_table ,
																				record_ptr,
																				Tn               // 本事务ID
																				);
								if( 0 != err)	{
									ERROR("mem_mvcc_delete_record err is %d\n",err);
									return err;
								}		
							}
						}
						
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
	return 0;
}


//////带限制的全表扫描
//////fun 遍历函数
//////param 函数参数
////inline int full_table_scan_limit(
////														struct mem_table_t *mem_table,
////														void (*fun)(struct record_t *,fun_param* param),
////														fun_param* param,
////														unsigned  long long n
////) 
////{
////int __i = 0;											 
////struct record_t     * record_ptr;
////struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
////unsigned  long long __n = 0;
////
////	for(;__i<mem_table->config.mem_block_used;++__i)																
////	{
////			unsigned  long long * __high_level_temp = 0;
////
////				for(;
////				__mem_block_temp->space_start_addr + __mem_block_temp->high_level* mem_table->record_size < __mem_block_temp->space_end_addr - mem_table->record_size ;
////				++__high_level_temp
////				   )		 															
////				{
////						// 找到可用的记录位置
////						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__mem_block_temp->high_level) * (mem_table->record_size) );
////						//处理每一行记录
////						fun(record_ptr,param);
////						++__n;
////						if(__n == n-1)return 0;
////				}
////			__mem_block_temp = __mem_block_temp->next;      //下一个块
////	}
////	return 0;
////}
////
////index unique scan
////index range scan  //  > < <> >= <= between
//////在组合索引上，只使用部分列进行查询，导致查询出多行
//////对非唯一索引列上进行的任何查询
////index full scan
////index fast full scan
////
//////1，排序 - - 合并连接（Sort Merge Join， SMJ）
//////    2，嵌套循环（Nested Loops， NL）
//////    3，哈希连接（Hash Join， HJ）
//////    另外，笛卡儿乘积（Cartesian Product）
////



#endif 
