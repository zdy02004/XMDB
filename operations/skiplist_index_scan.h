#ifndef SKIPLIST_INDEX_SCAN
#define SKIPLIST_INDEX_SCAN

/*
g++ -w -lpthread -C -std=c++11 skiplist_index_scan.h 
*/


#include"../mem_date_index_ctl/mem_table_mvcc_op.h"

#include<vector>
#include<list>
#include <functional>
#include <cstdlib>

#ifdef __cplusplus
extern "C" {
#endif

int mem_skiplist_find_one_at_lowest( mem_skiplist_index_t *mem_skiplist_index,
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t ** finded_entry 
 											 )
 {
 	DEBUG("Enter mem_skiplist_find_one_at_lowest(),Search key is %ld\n",in->lkey);	
	
	//1.从最高层开始找
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;

	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare Serach one %ld\n",in->lkey );								 	 					

	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Search pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("Find Search pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	

 	if(err)return err;
 
 
 
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1 && prev_entry->lkey != in->lkey ){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
   }


}
//在最后一层 找到要找的节点并返回 0
err =	mem_skiplist_find_EQO( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												 finded_entry  
 											  );
 	DEBUG("Enter mem_skiplist_find_one_at_lowest() end,ret is %d\n",err );	

 	return err;								 	
	}

int mem_skiplist_find_one_at_lowest_str( mem_skiplist_index_t *mem_skiplist_index,
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t ** finded_entry 
 											 )
 {
 	DEBUG("Enter mem_skiplist_find_one_at_lowest_str(),Search key is %s\n",in->ckey);	
	
	//1.从最高层开始找
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;

	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare Serach one %s\n",in->ckey );								 	 					

	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Search pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE_str( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("Find Search pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	

 	if(err)return err;
 
 
 
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1 && strcmp(prev_entry->ckey , in->ckey ) != 0 ){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
   }


}
//在最后一层 找到要找的节点并返回 0
err =	mem_skiplist_find_EQO_str( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												 finded_entry  
 											  );
 	DEBUG("Enter mem_skiplist_find_one_at_lowest_str() end,ret is %d\n",err );	

 	return err;								 	
	}


#ifdef __cplusplus
   }
#endif


//插入一个整型索引的数据,保证每个桶相同的 val 相邻
template<typename record_type >
inline int mem_skiplist_index_scan_long(  
                                mem_table_t *mem_table,
                        /* in */struct mem_skiplist_index_t * mem_skiplist_index ,
                        /* in */mem_skiplist_entry_t *in             ,
                                mem_skiplist_entry_t **last_find_entry,
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
  DEBUG("mem_skiplist_index_scan_long() start!\n");
  int ret ;
  struct    record_t   *  return_record_ptr    = 0;
  char buf[mem_table->record_size - RECORD_HEAD_SIZE];
  record_type return_record;
  return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);
	
  
  mem_skiplist_entry_t * finded_entry  =  0;
  if(!mem_skiplist_find_one_at_lowest(mem_skiplist_index,
 												  						in,
 												 							&finded_entry))
 	{
 		DEBUG("Pass in lowest level in skiplist_space!\n");
 		//插入结果集
 		ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num,  &return_record_ptr);
   	if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
		{
				  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
					DEBUG("Find one skiplist record in skiplist_space!\n");
					ret_list->emplace_back(return_record );
					*last_find_entry = finded_entry;
		}
 		//
 		while(!mem_skiplist_find_EQO( 
 		  mem_skiplist_index, 
 			finded_entry,
 			in,
 			&finded_entry ))
 			{
 				//插入结果集
 				ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num,  &return_record_ptr);
   			if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
						  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
							DEBUG("Find one skiplist record in skiplist_space next link!\n");
							ret_list->emplace_back(return_record );
							*last_find_entry = finded_entry;
							DEBUG("*last_find_entry is %0x !\n",*last_find_entry );
				}
 				
 			}
 	}
 	  DEBUG("mem_skiplist_index_scan_long() end!\n");
	return 0;
}




//插入一个整型索引的数据,保证每个桶相同的 val 相邻
template<typename record_type >
inline int mem_skiplist_index_scan_str(  
                                mem_table_t *mem_table,
                        /* in */struct mem_skiplist_index_t * mem_skiplist_index ,
                        /* in */mem_skiplist_entry_t *in             ,
                        		    mem_skiplist_entry_t **last_find_entry,
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
  DEBUG("mem_skiplist_index_scan_str() start!\n");
  int ret ;
  struct    record_t   *  return_record_ptr    = 0;
  char buf[mem_table->record_size - RECORD_HEAD_SIZE];
  record_type return_record;	
  return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);

  
  mem_skiplist_entry_t * finded_entry  =  0;
  if(!mem_skiplist_find_one_at_lowest_str(mem_skiplist_index,
 												  						in,
 												 							&finded_entry))
 	{
 		DEBUG("Pass in lowest level in skiplist_space!\n");
 		//插入结果集
 		ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num,  &return_record_ptr);
   	if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
		{
				  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
					DEBUG("Find one skiplist record in skiplist_space!\n");
					ret_list->emplace_back(return_record );
					*last_find_entry = finded_entry;
		}
 		//
 		while(!mem_skiplist_find_EQO_str( 
 		  mem_skiplist_index, 
 			finded_entry,
 			in,
 			&finded_entry ))
 			{
 				//插入结果集
 				ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num,  &return_record_ptr);
   			if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
						  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
							DEBUG("Find one skiplist record in skiplist_space next link!\n");
							ret_list->emplace_back(return_record );
							*last_find_entry = finded_entry;
				}
 				
 			}
 	}
 	  DEBUG("mem_skiplist_index_scan_str() end!\n");
	return 0;
}

//  将本层 prev到  <= in->lkey 的节点，扫描出来
template<typename record_type >
inline int mem_skiplist_LE_scan(
												mem_table_t *mem_table,
												mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry,
 												unsigned long long  Tn,                 //当前事务ID
												std::list<record_type>* ret_list		    //原始结果集 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record = NULL;
	 mem_skiplist_entry_t * right_entry  = NULL;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 int ret;
	 
	 struct    record_t   *  return_record_ptr    = 0;
   char buf[mem_table->record_size - RECORD_HEAD_SIZE];
   record_type return_record;	
	 return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);

	 
	 DEBUG("Enter mem_skiplist_LE_scan(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 //IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 do{
	 			//	do{
	 					  if( right_record &&right_record->is_used == 0)printf("right_record->is_used == 0 \n");
	 						prev_record = (record_t *)((char *)prev_entry - RECORD_HEAD_SIZE);
	 						
	 						SKIPLIST_RLOCK( &(prev_record->row_lock) );
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	 						if( right_record->is_used == 0 )return SKIPLIST_INDEX_ERR_GETGE_FAILED;

	 						if(err)return err;
	 			//	}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %ld \n ",right_entry->lkey);

	 
	 if( mem_skiplist_index->nil != right_entry && 
	 			right_entry->lkey <= in->lkey            )
	 			{
	 				prev_entry = right_entry ;
	 					//插入结果集
 					ret = get_record( mem_table, right_entry->block_no, right_entry->record_num,  &return_record_ptr);
   				if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
					{
							  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("Find one skiplist record in skiplist_space next link!\n");
								ret_list->emplace_back(return_record );
					}
	 			}
	 
	 }while(right_entry != mem_skiplist_index->nil && right_entry->lkey <= in->lkey);
	 
	 *last_find_entry = prev_entry;
	 	 
	 DEBUG(" mem_skiplist_LE_scan end,prev_record is %0x \n ",right_record->record_num );
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry);

	  return 0;
}


//  将本层 prev到  <= in->lkey 的节点，扫描出来
template<typename record_type >
inline int mem_skiplist_LE_scan_str(
												mem_table_t *mem_table,
												mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry,
 												unsigned long long  Tn,                 //当前事务ID
												std::list<record_type>* ret_list		    //原始结果集 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record = NULL;
	 mem_skiplist_entry_t * right_entry  = NULL;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 int ret;
	 
	 struct    record_t   *  return_record_ptr    = 0;
   char buf[mem_table->record_size - RECORD_HEAD_SIZE];
   record_type return_record;	
	 return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);

	 DEBUG("Enter mem_skiplist_LE_scan_str(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 //IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 do{
	 			//	do{
	 					  if( right_record && right_record->is_used == 0)printf("right_record->is_used == 0 \n");
	 						prev_record = (record_t *)((char *)prev_entry - RECORD_HEAD_SIZE);
	 						
	 						SKIPLIST_RLOCK( &(prev_record->row_lock) );
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	 						if( right_record->is_used == 0 )return SKIPLIST_INDEX_ERR_GETGE_FAILED;

	 						if(err)return err;
	 			//	}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %s \n ",right_entry->ckey);

	 
	 if( mem_skiplist_index->nil != right_entry && 
	 			strcmp( right_entry->ckey,in->ckey ) <= 0            )
	 			{
	 				prev_entry = right_entry ;
	 					//插入结果集
 					ret = get_record( mem_table, right_entry->block_no, right_entry->record_num,  &return_record_ptr);
   				if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
					{
							  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("Find one skiplist record in skiplist_space next link!\n");
								ret_list->emplace_back(return_record );
					}
	 			}
	 
	 }while(right_entry != mem_skiplist_index->nil && strcmp(right_entry->ckey , in->ckey) <= 0 );
	 
	 *last_find_entry = prev_entry;
	 	 
	 DEBUG(" mem_skiplist_LE_scan_str end,prev_record is %0x \n ",right_record->record_num );
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry);

	  return 0;
}


//  将本层 prev到  < in->lkey 的节点，扫描出来
template<typename record_type >
inline int mem_skiplist_L_scan(
												mem_table_t *mem_table,
												mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry,
 												unsigned long long  Tn,                 //当前事务ID
												std::list<record_type>* ret_list		    //原始结果集 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record = NULL;
	 mem_skiplist_entry_t * right_entry  = NULL;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 int ret;
	 
	 struct    record_t   *  return_record_ptr    = 0;
   char buf[mem_table->record_size - RECORD_HEAD_SIZE];
   record_type return_record;	
	 return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);

	 DEBUG("Enter mem_skiplist_L_scan(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 //IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 do{
	 			//	do{
	 					  if( right_record &&right_record->is_used == 0)printf("right_record->is_used == 0 \n");
	 						prev_record = (record_t *)((char *)prev_entry - RECORD_HEAD_SIZE);
	 						
	 						SKIPLIST_RLOCK( &(prev_record->row_lock) );
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	 						if( right_record->is_used == 0 )return SKIPLIST_INDEX_ERR_GETGE_FAILED;

	 						if(err)return err;
	 			//	}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %ld \n ",right_entry->lkey);

	 
	 if( mem_skiplist_index->nil != right_entry && 
	 			right_entry->lkey < in->lkey            )
	 			{
	 				prev_entry = right_entry ;
	 					//插入结果集
 					ret = get_record( mem_table, right_entry->block_no, right_entry->record_num,  &return_record_ptr);
   				if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
					{
							  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("Find one skiplist record in skiplist_space next link!\n");
								ret_list->emplace_back(return_record );
					}
	 			}
	 
	 }while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	 
	 *last_find_entry = prev_entry;
	 	 
	 DEBUG(" mem_skiplist_L_scan end,prev_record is %0x \n ",right_record->record_num );
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry);

	  return 0;
}


//  将本层 prev到  < in->ckey 的节点，扫描出来
template<typename record_type >
inline int mem_skiplist_L_scan_str(
												mem_table_t *mem_table,
												mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry,
 												unsigned long long  Tn,                 //当前事务ID
												std::list<record_type>* ret_list		    //原始结果集 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record = NULL;
	 mem_skiplist_entry_t * right_entry  = NULL;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 int ret;
	 
	 struct    record_t   *  return_record_ptr    = 0;
   char buf[mem_table->record_size - RECORD_HEAD_SIZE];
   record_type return_record;	
   return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);
	 
	 DEBUG("Enter mem_skiplist_L_scan_str(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 //IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 do{
	 			//	do{
	 					  if( right_record &&right_record->is_used == 0)printf("right_record->is_used == 0 \n");
	 						prev_record = (record_t *)((char *)prev_entry - RECORD_HEAD_SIZE);
	 						
	 						SKIPLIST_RLOCK( &(prev_record->row_lock) );
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	 						if( right_record->is_used == 0 )return SKIPLIST_INDEX_ERR_GETGE_FAILED;

	 						if(err)return err;
	 			//	}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %s \n ",right_entry->ckey);

	 
	 if( mem_skiplist_index->nil != right_entry && 
	 			strcmp( right_entry->ckey,in->ckey ) < 0            )
	 			{
	 				prev_entry = right_entry ;
	 					//插入结果集
 					ret = get_record( mem_table, right_entry->block_no, right_entry->record_num,  &return_record_ptr);
   				if( !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
					{
							  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
								DEBUG("Find one skiplist record in skiplist_space next link!\n");
								ret_list->emplace_back(return_record );
					}
	 			}
	 
	 }while(right_entry != mem_skiplist_index->nil && strcmp(right_entry->ckey , in->ckey) < 0 );
	 
	 *last_find_entry = prev_entry;
	 	 
	 DEBUG(" mem_skiplist_L_scan_str end,prev_record is %0x \n ",right_record->record_num );
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry);

	  return 0;
}

template<typename record_type >
inline int mem_skiplist_index_btw_scan_long(  
                                mem_table_t *mem_table,
                        /* in */struct mem_skiplist_index_t * mem_skiplist_index ,
                        /* in */mem_skiplist_entry_t *min             ,
                        /* in */mem_skiplist_entry_t *max             ,
                          			mem_skiplist_entry_t **last_find_entry,
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
if(!mem_skiplist_index_scan_long(  
                                 mem_table,
                         				 mem_skiplist_index ,
                        				 min             ,
                        				 last_find_entry,
                          			 Tn,                 										//当前事务ID
																 ret_list		    //原始结果集
                        )
){
		DEBUG("return  mem_skiplist_LE_scan,last_find_entry is %0x \n",*last_find_entry	);
		return  mem_skiplist_LE_scan(
											mem_table,
										  mem_skiplist_index, 
											*last_find_entry,
										  max,
										  last_find_entry,
										  Tn,                 //当前事务ID
										  ret_list		    //原始结果集 
									 );
}

}


template<typename record_type >
inline int mem_skiplist_index_btw_scan_str(  
                                mem_table_t *mem_table,
                        /* in */struct mem_skiplist_index_t * mem_skiplist_index ,
                        /* in */mem_skiplist_entry_t *min             ,
                        /* in */mem_skiplist_entry_t *max             ,
                          			mem_skiplist_entry_t **last_find_entry,
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
if(!mem_skiplist_index_scan_str(  
                                 mem_table,
                         				 mem_skiplist_index ,
                        				 min             ,
                        				 last_find_entry,
                          			 Tn,                 										//当前事务ID
																 ret_list		    //原始结果集
                        )
){
		return  mem_skiplist_LE_scan_str(
											mem_table,
										  mem_skiplist_index, 
											*last_find_entry,
										  max,
										  last_find_entry,
										  Tn,                 //当前事务ID
										  ret_list		    //原始结果集 
									 );
}

}


#endif 
