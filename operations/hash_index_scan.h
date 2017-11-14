#ifndef HASH_INDEX_SCAN
#define HASH_INDEX_SCAN

/*
g++ -w -lpthread -C hash_index_scan.h 
*/


#include"../mem_date_index_ctl/mem_table_mvcc_op.h"
#include<vector>
#include<list>
#include <functional>
#include <cstdlib>

//插入一个整型索引的数据,保证每个桶相同的 val 相邻
template<typename record_type >
inline int mem_hash_index_scan_long(
                                mem_table_t *mem_table,
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */unsigned  long          key              ,
                        /* in */int (*hash_fun)(unsigned  long      ,    /*返回哈希表的行号*/struct  mem_block_t *,unsigned  long      *),
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
	if( NULL == hash_fun  )  return INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	DEBUG("Enter mem_hash_index_scan_long(),key = %ld\n",key);

	//1 array_space 不存在数据，则存入数据
	//2 array_space 存在数据，link_space 不存在数据，插入link_space
	//3 存在数据，link_space  存在数据，插入link_space最近的地方
  unsigned  long          record_num_temp      = 0;
  long                    block_no_temp        = 0;
  long                    mem_table_no         = 0;
  struct    record_t   *  record_ptr           = 0;
  struct    record_t   *  return_record_ptr    = 0;
  struct  mem_hash_entry_t * array_space_entry = 0;
  long                                link_block_no;
  
  char buf[mem_table->record_size - RECORD_HEAD_SIZE];
  record_type return_record;	
  return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);
  
  int ret;
  int ret2;
  ret = mem_hash_index_select_long(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */&block_no_temp,
                       /* out */&record_num_temp,
                       /* out */&record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                &array_space_entry,
                                &mem_table_no
                       );
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);         
   int err;      
   DEBUG("switch(ret)\n");
    
   switch(ret)
   {
   //连续空间内没找到，就不存在
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
   	    {
   	    return ret;
   	    break;
   	  }
   //连续空间内找到
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   			 //通过索引获得最终的数据
   	    //通过索引获得最终的数据
   	    ret2 = get_record( mem_table, entry->block_no,  entry->record_num,  &return_record_ptr);
   	    if(!ret2 && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
					  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in array_space!\n");
						ret_list->emplace_back(return_record );
				}
   //链接空间内找到    
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	    {
   	    DEBUG("case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:\n");
        if(ret != SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) ) 
        {
        		memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in linked space!\n");
						ret_list->emplace_back(return_record );
        }
        while(true)
        {
        link_block_no = ((struct  mem_hash_entry_t *)(((char *)(record_ptr) + RECORD_HEAD_SIZE)))->link_block_no;
        DEBUG("link_block_no is %d !\n",link_block_no );

        if ( link_block_no == -1  ) break;
   	    ret2 = get_record(
   	     mem_hash_index->linked_space,
        link_block_no,
   	    ((struct  mem_hash_entry_t *)(((char *)(record_ptr) + RECORD_HEAD_SIZE)))->link_record_num,
   	    &record_ptr
   	    );
        if( !record_ptr || record_ptr->is_used == 0)break;
        
        row_rlock(&(record_ptr->row_lock));                       //上行锁
        entry = (struct  mem_hash_entry_t *) ((char *)(record_ptr) + RECORD_HEAD_SIZE); //相等就一直找下去
        if(entry->hash_lkey == key) {
        	//通过索引获得最终的数据
   	    ret2 = get_record( mem_table, entry->block_no,  entry->record_num,  &return_record_ptr);
   	    if(!ret2 && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
					  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in array_space!\n");
						ret_list->emplace_back(return_record );
				}
        }
        else																																						 //否则就不找了
        	{
        	row_runlock(&(record_ptr->row_lock));                        //解行锁 
        	break;
          }
   	    row_runlock(&(record_ptr->row_lock));                        //解行锁
        
       }
   	    break;
   	  }
   //链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    {
   	    return ret;
   	    break;
   	    }
   default:
   	    return ret;	
   	
  }
  DEBUG("mem_hash_index_scan_long() END\n");

	return 0;
}


//插入一个整型索引的数据,保证每个桶相同的 val 相邻
template<typename record_type >
inline int mem_hash_index_scan_str(
                                mem_table_t *mem_table,
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */char                    * key              ,
                        /* in */int (*hash_fun)(unsigned  long      ,    /*返回哈希表的行号*/struct  mem_block_t *,unsigned  long      *),
                          			unsigned long long  Tn,                 //当前事务ID
																std::list<record_type>* ret_list		    //原始结果集
                        )
{
	if( NULL == hash_fun  )  return INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	DEBUG("Enter mem_hash_index_scan_str(),key = %s\n",key);

	//1 array_space 不存在数据，则存入数据
	//2 array_space 存在数据，link_space 不存在数据，插入link_space
	//3 存在数据，link_space  存在数据，插入link_space最近的地方
  unsigned  long          record_num_temp = 0;
  long                    block_no_temp   = 0;
  long                    mem_table_no    = 0;
  struct    record_t   *  record_ptr      = 0;
  struct  mem_hash_entry_t * array_space_entry = 0;
  long                                link_block_no;

  
  char buf[mem_table->record_size - RECORD_HEAD_SIZE];
  struct record_t  *return_record_ptr     = 0;
  record_type return_record;	
  return_record.allocate(mem_table->record_size - RECORD_HEAD_SIZE);

  
  int ret;
  int ret2;
  ret = mem_hash_index_select_str(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */&block_no_temp,
                       /* out */&record_num_temp,
                       /* out */&record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                &array_space_entry,
                                &mem_table_no
                       );
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);         
   int err;      
   DEBUG("switch(ret)\n");
    
    switch(ret)
   {
   //连续空间内没找到，就不存在
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
   	    {
   	    return ret;
   	    break;
   	  }
   //连续空间内找到
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   			 //通过索引获得最终的数据
   	    //通过索引获得最终的数据
   	    ret2 = get_record( mem_table, entry->block_no,  entry->record_num,  &return_record_ptr);
   	    if(!ret2 && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
					  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in array_space!\n");
						ret_list->emplace_back(return_record );
				}
   //链接空间内找到    
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	    {
   	    DEBUG("case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:\n");
        if(ret != SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) ) 
        {
        		memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in linked space!\n");
						ret_list->emplace_back(return_record );
        }
        while(true)
        {
        link_block_no = ((struct  mem_hash_entry_t *)(((char *)(record_ptr) + RECORD_HEAD_SIZE)))->link_block_no;
        DEBUG("link_block_no is %d !\n",link_block_no );

       if ( link_block_no == -1  ) break;
   	    ret2 = get_record(
   	     mem_hash_index->linked_space,
        link_block_no,
				((struct  mem_hash_entry_t *)(((char *)(record_ptr) + RECORD_HEAD_SIZE)))->link_record_num,
   	    &record_ptr
   	    );
        if( !record_ptr || record_ptr->is_used == 0)break;
        
        row_rlock(&(record_ptr->row_lock));                       //上行锁
        entry = (struct  mem_hash_entry_t *) ((char *)(record_ptr) + RECORD_HEAD_SIZE); //相等就一直找下去
        if( strcmp( entry->hash_ckey , key) == 0  ) {
        	//通过索引获得最终的数据
   	    ret2 = get_record( mem_table, entry->block_no,  entry->record_num,  &return_record_ptr);
   	    if(!ret2 && !mem_mvcc_read_record(mem_table ,return_record_ptr, (char *)buf,Tn ) )
				{
					  memcpy(&return_record,buf,mem_table->record_size - RECORD_HEAD_SIZE);
						DEBUG("Find one hash record in array_space!\n");
						ret_list->emplace_back(return_record );
				}
        }
        else																																						 //否则就不找了
        	{
        	row_runlock(&(record_ptr->row_lock));                        //解行锁 
        	break;
          }
   	    row_runlock(&(record_ptr->row_lock));                        //解行锁
        
       }
   	    break;
   	  }
   //链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    {
   	    return ret;
   	    break;
   	    }
   default:
   	    return ret;	
   	
  }
  DEBUG("mem_hash_index_scan_str() END\n");
	return 0;
}


#endif 
