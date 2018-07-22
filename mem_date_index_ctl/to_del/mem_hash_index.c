#include"mem_hash_index.h"
#include"mem_index_no_manager.h"

#define CREATE_HASH_INDEX_ERR_TABLE_PTR              33001
#define CREATE_HASH_INDEX_ERR_NULL_CONFIG            33002
#define CREATE_HASH_INDEX_ERR_NO_NAME                33003
#define CREATE_HASH_INDEX_ERR_NAME_TOO_LONG          33004
#define CREATE_HASH_INDEX_ERR_NO_TABLE_NO            33005
#define CREATE_HASH_INDEX_ERR_NO_FIELD_PTR           33006
#define CREATE_HASH_INDEX_ERR_FIELD_NUM_LESS_ZERO    33007
#define OPEN_MEM_HASH_ERR_NULL_HASH_PTR              33008
#define INSERT_MEM_HASH_INDEX_ERR_TABLE_IS_NULL      33009
#define INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL   33010
#define INSERT_MEM_HASH_INDEX_ERR_BLOCK_NO_UNSAFE    33011
#define SELECT_MEM_HASH_INDEX_ERR_INDEX_IS_NULL      33012
#define SELECT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL   33013
#define SELECT_MEM_HASH_INDEX_ERR_BLOCK_NO_UNSAFE    33014
#define SELECT_MEM_HASH_INDEX_ERR_BLOCK_NO_NOT_FOUND 33015
#define SELECT_MEM_HASH_INDEX_NOT_FOUND              33016
#define SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND  33017
#define SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND      33018
#define SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND 33019
#define SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND     33020
#define SELECT_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL    33021
#define INSERT_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL    33022
#define MEM_HASH_ERR_BLOCK_NO_NOT_EXIST              33023
#define DEL_MEM_HASH_INDEX_ERR_TABLE_IS_NULL         33024
#define DEL_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL      33025
#define DEL_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL       33026
#define CLOSE_MEM_HASH_INDEX_ERR_NULL_PTR            33027
#define INTEGER_HASH_FUN_ERR_ARRAY_BLOCK_IS_NULL     33028
#define INTEGER_HASH_FUN_ERR_RECORD_NUM_IS_NULL      33029
#define STR_HASH_FUN_ERR_ARRAY_BLOCK_IS_NULL				 33030
#define STR_HASH_FUN_ERR_RECORD_NUM_IS_NULL          33031
#define STR_HASH_FUN_ERR_KEY_IS_NULL								 33032

// 64bit hash fun
inline unsigned  long long hash64shift(unsigned  long long key) 
{ 
  key = (~key) + (key << 21); // key = (key << 21) - key - 1; 
  key = key ^ (key >> 24); 
  key = (key + (key << 3)) + (key << 8); // key * 265 
  key = key ^ (key >> 14); 
  key = (key + (key << 2)) + (key << 4); // key * 21 
  key = key ^ (key >> 28); 
  key = key + (key << 31); 
  return key; 
}

//暂时取模算 hash
//整型 hash 函数
inline int integer_hash_fun(unsigned  long long key,/*连续空间块*/struct  mem_block_t * array_block,/*返回哈希表的行号*/unsigned  long long * record_num)
{
	if( NULL == array_block)return INTEGER_HASH_FUN_ERR_ARRAY_BLOCK_IS_NULL;
	if( NULL == record_num )return INTEGER_HASH_FUN_ERR_RECORD_NUM_IS_NULL;
	
	//先平均分布，再取余数
	unsigned long long num = hash64shift(key)%( array_block->block_size - MEM_BLOCK_HEAD_SIZE ) ;
	*record_num            =  num;
	return 0;
}

// BKDR Hash Function
inline unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}

//字符串 hash 函数
inline int str_hash_fun(char * key,/*连续空间块*/struct  mem_block_t * array_block,/*返回哈希表的行号*/unsigned  long long * record_num)
{
	if( NULL == array_block)return STR_HASH_FUN_ERR_ARRAY_BLOCK_IS_NULL;
	if( NULL == record_num )return STR_HASH_FUN_ERR_RECORD_NUM_IS_NULL;
	if( NULL == key        )return STR_HASH_FUN_ERR_KEY_IS_NULL;

	//先平均分布，再取余数	
	unsigned long long num = BKDRHash(key) % ( array_block->block_size - MEM_BLOCK_HEAD_SIZE ) ;
	*record_num            =  num;
	return 0;
}


//查找一个整型索引
inline int mem_hash_index_select_long(
                        /* in */struct mem_hash_index_t  * mem_hash_index ,
                        /* in */unsigned  long long        key,
                        /* in */int (*hash_fun)(unsigned  long long key,/*连续空间块*/struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *),
                       /* out */long                     * block_no,    //输出找到的块所在块号
                       /* out */unsigned  long long      * record_num,  //输出找到的块所在行号
                       /* out */struct  record_t         * record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD  输出找到的块所在记录的指针 */
                       /* out */struct  mem_hash_entry_t * array_space_entry //输出对应 连续空间的 hash 项索引
                        )
{
	if( NULL == mem_hash_index )  return SELECT_MEM_HASH_INDEX_ERR_INDEX_IS_NULL;
	if( NULL == hash_fun       )  return SELECT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	
	struct  mem_block_t * array_block_temp   = mem_hash_index->array_space->config.mem_blocks_table;
  struct  mem_block_t * linked_block_temp  = mem_hash_index->linked_space->config.mem_blocks_table;

 //执行hash 函数
  int err;
  err = hash_fun( key,array_block_temp ,record_num );
  if( 0!= err )return err;
  
  //通过recore 找到对应字段的值 和 hash_entry_temp->hash_lkey 比较，不一样的话，顺着link_val 找，找不到说明不存在
  record_ptr = (struct  record_t *)(array_block_temp->space_start_addr + (*record_num)*MEM_HASH_ENTRY_SIZE);
  row_rlock(&(record_ptr->row_lock));                                                            //上行锁
	struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *) record_ptr->data;
	array_space_entry                =  entry;
	
	  //array_space 没找到
  if(record_ptr->is_used == 0)  return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND;
	if(entry->hash_lkey == key)
		{
			//在array_space 中找到
			*record_num = record_ptr->record_num;
			*block_no   = entry->block_no;
			row_runlock(&(record_ptr->row_lock));                                                           //解行锁
			return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND;
		}
	else
		{
			//在array_space 中没找到，在linked_space 找
			//遍历所有的linked_space 块
			while(linked_block_temp)
			{  
			   row_runlock(&(record_ptr->row_lock));                                                             //解行锁
				 record_ptr = (struct record_t *         )(linked_block_temp->space_start_addr + entry->link_record_num*MEM_HASH_ENTRY_SIZE);
			   row_rlock(&(record_ptr->row_lock));                                                             //上行锁
				 entry      = (struct mem_hash_entry_t * )record_ptr->data;

				 //linked_space 中没有就找下一个 linked_space 或者  没找到对应的 entry，就找下一个  entry
				 if(record_ptr->is_used == 0  || entry->link_block_no !=linked_block_temp->block_no)
				 	{
				 		linked_block_temp = linked_block_temp->next;
				 		 continue;
				 	}
				while(entry->link_record_num >= 0)
				{
				  if(entry->hash_lkey == key)
				  {
				  	//在 linked_space 中找到
				  	*record_num = record_ptr->record_num;
				  	*block_no   = entry->link_block_no;
				  	row_runlock(&(record_ptr->row_lock));                                                             //解行锁
				  	return SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND;
				  }	
				 row_runlock(&(record_ptr->row_lock));                                                                //解行锁
				 record_ptr = (struct record_t *         )(linked_block_temp->space_start_addr + entry->link_record_num*MEM_HASH_ENTRY_SIZE);
				 row_rlock(&(record_ptr->row_lock));                                                                 //上行锁
				 if(record_ptr->is_used == 0) 
				 	{
				 		row_runlock(&(record_ptr->row_lock));                                                             //解行锁
				 		return SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
				 	}
				 entry      = (struct mem_hash_entry_t * )record_ptr->data;				
				 }
				 
				linked_block_temp = linked_block_temp->next;
			}
		}
	
	return SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
}


//插入一个整型索引的数据,保证每个桶相同的 val 相邻
inline int mem_hash_index_insert_long(
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */unsigned  long long     key              ,
                        /* in */long                    block_no         ,/*插入数据所在的块号*/
                        /* in */unsigned  long long     record_num       ,/*插入数据的块的行号*/
                        /* in */int (*hash_fun)(unsigned  long long ,/*返回哈希表的行号*/struct  mem_block_t *,unsigned  long long *)
                        )
{
	if( NULL == hash_fun  )  return INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	if( block_no < 0      ) return INSERT_MEM_HASH_INDEX_ERR_BLOCK_NO_UNSAFE;	
	//1 array_space 不存在数据，则存入数据
	//2 array_space 存在数据，link_space 不存在数据，插入link_space
	//3 存在数据，link_space  存在数据，插入link_space最近的地方
  long * block_no_temp                    = 0;
  unsigned  long long  *  record_num_temp = 0;
  struct    record_t   *  record_ptr      = 0;
  struct  mem_hash_entry_t * array_space_entry = 0;
  int ret;
  ret = mem_hash_index_select_long(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */block_no_temp,
                       /* out */record_num_temp,
                       /* out */record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                array_space_entry
                       );
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)record_ptr->data;         
   int err;          
   switch(ret)
   {
   //连续空间内没找到，就覆盖到连续空间,entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
   	    record_ptr->is_used                 =  1;
   	    row_wlock(&(record_ptr->row_lock));                       //上行锁
   	    array_space_entry->hash_lkey        =  key;
   	    //array_space_entry->hash_ckey      =  (char *[32])(0);
   	    array_space_entry->block_no         =  block_no;
   	    array_space_entry->record_num       =  record_num;
   	    array_space_entry->link_block_no    =  -1;
   	    array_space_entry->link_record_num  =   0;
   	    row_wunlock(&(record_ptr->row_lock));                      //解行锁
   	    break;
   //找到相同的值就插到相同的值的后面
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   	    
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	    {
   	    struct  record_t   *   new_record_ptr = 0;
   	    long               *   new_block_no   = 0;
   	    
   	    struct  mem_hash_entry_t hash_entry_temp;
   	    hash_entry_temp.hash_lkey     = key;
   	    //hash_entry_temp.hash_ckey   = (char *)0;
   	    hash_entry_temp.block_no      = block_no;
   	    hash_entry_temp.record_num    = record_num;
        
        row_wlock(&(record_ptr->row_lock));                       //上行锁
        row_wlock(&(new_record_ptr->row_lock));                   //上行锁
        new_record_ptr->is_used                                                = 1;
   	    err = mem_table_insert_record(mem_hash_index->linked_space , &new_record_ptr,new_block_no, (char *)&hash_entry_temp);
   	    if( 0 != err )return err;
   	    //将新节点链入 array_space 后面
   	    ((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_block_no    = ((struct  mem_hash_entry_t *)(record_ptr->data))->link_block_no;    
   	   	((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_record_num  = ((struct  mem_hash_entry_t *)(record_ptr->data))->link_record_num;    
        ((struct  mem_hash_entry_t *)(record_ptr->data))->link_block_no        =  *new_block_no;
   	    ((struct  mem_hash_entry_t *)(record_ptr->data))->link_record_num      =  new_record_ptr->record_num;
   	    row_wunlock(&(new_record_ptr->row_lock));                    //解行锁
   	    row_wunlock(&(record_ptr->row_lock));                        //解行锁
   	    break;
   	  }
   //链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    {
   	    struct  record_t   * new_record_ptr = 0;
   	    long               *   new_block_no = 0;
   	    
   	    struct  mem_hash_entry_t hash_entry_temp;
   	    hash_entry_temp.hash_lkey           = key;
   	    //hash_entry_temp.hash_ckey         = 0;
   	    hash_entry_temp.block_no            = block_no;
   	    hash_entry_temp.record_num          = 0;
        row_wlock(&(record_ptr->row_lock));                       //上行锁
        row_wlock(&(new_record_ptr->row_lock));                   //上行锁
        new_record_ptr->is_used                                                 = 1;
   	    err = mem_table_insert_record(mem_hash_index->linked_space , &new_record_ptr,new_block_no, (char *)&hash_entry_temp);
   	    if( 0 != err )return err;
   	    //将新节点链入 array_space 后面
   	    ((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_block_no     = array_space_entry->link_block_no;    
   	   	((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_record_num   = array_space_entry->link_record_num;    
        array_space_entry->link_block_no                                        = *new_block_no;
   	    array_space_entry->link_record_num                                      = new_record_ptr->record_num;
   	    row_wunlock(&(new_record_ptr->row_lock));                 //解行锁
   	    row_wunlock(&(record_ptr->row_lock));                     //解行锁
   	    break;
   	  }
   default:
   	    return ret;	
   	
  }
  
	return 0;
}

//查找一个字符串索引
inline int mem_hash_index_select_str(
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */char                    * key,
                        /* in */int (*hash_fun)(char *,struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *),
                       /* out */long                    * block_no,
                       /* out */unsigned  long long     * record_num,
                       /* out */struct  record_t        * record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                       /* out */struct  mem_hash_entry_t* array_space_entry
                        )
{
	if( NULL == mem_hash_index )  return SELECT_MEM_HASH_INDEX_ERR_INDEX_IS_NULL;
	if( NULL == hash_fun       )  return SELECT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
  if( NULL == key            )  return SELECT_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL;
	
	struct  mem_block_t * array_block_temp   = mem_hash_index->array_space->config.mem_blocks_table;
  struct  mem_block_t * linked_block_temp  = mem_hash_index->linked_space->config.mem_blocks_table;

 //执行hash 函数
  int err;
  err = hash_fun( key,array_block_temp ,record_num );
  if( 0!= err )return err;
  
  //通过recore 找到对应字段的值 和 hash_entry_temp->hash_ckey 比较，不一样的话，顺着link_record_num 找，找不到说明不存在
  record_ptr = (struct  record_t *)(array_block_temp->space_start_addr + (*record_num)*MEM_HASH_ENTRY_SIZE);
	struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *) record_ptr->data;
	array_space_entry                =  entry;
	
	  //array_space 没找到
  if(record_ptr->is_used == 0)        return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND;
	if( strcmp(entry->hash_ckey, key) == 0 ) 
		{
			row_rlock(&(record_ptr->row_lock));                       //上行锁
			//在array_space 中找到
			*record_num = record_ptr->record_num;
			*block_no   = entry->block_no;
			row_runlock(&(record_ptr->row_lock));                     //解行锁
			return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND;
		}
	else
		{
			//在array_space 中没找到，在linked_space 找
			//遍历所有的linked_space 块
			while(linked_block_temp)
			{
				 
				 record_ptr = (struct record_t *         )(linked_block_temp->space_start_addr + entry->link_record_num*MEM_HASH_ENTRY_SIZE);
				 entry      = (struct mem_hash_entry_t * )record_ptr->data;

				 //linked_space 中没有就找下一个 linked_space 或者  没找到对应的 entry，就找下一个  entry
				 row_rlock(&(record_ptr->row_lock));                         //上行锁
				 if(record_ptr->is_used == 0  || entry->link_block_no !=linked_block_temp->block_no)
				 	{
				 		linked_block_temp = linked_block_temp->next;
				 		row_runlock(&(record_ptr->row_lock));                     //解行锁
				 		continue;
				 	}
				while(entry->link_record_num >= 0)
				{
				  if( strcmp(entry->hash_ckey, key) == 0 ) 
				  {
				  	//在 linked_space 中找到
				  	*record_num = record_ptr->record_num;
				  	*block_no   = entry->link_block_no;
				  	row_runlock(&(record_ptr->row_lock));                     //解行锁
				  	return SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND;
				  }	
				 row_runlock(&(record_ptr->row_lock));                       //解行锁
				 record_ptr = (struct record_t *         )(linked_block_temp->space_start_addr + entry->link_record_num*MEM_HASH_ENTRY_SIZE);
				 row_rlock(&(record_ptr->row_lock));                         //上行锁
				 if(record_ptr->is_used == 0) {
				 	                 row_runlock(&(record_ptr->row_lock));    //解行锁        
				 	                 return     SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
				}
				 entry      = (struct mem_hash_entry_t * )record_ptr->data;				
				 }
				 
				linked_block_temp = linked_block_temp->next;
			}
		}
	
	return SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
}


//插入一个字符串索引的数据,保证每个桶相同的 val 相邻
inline int mem_hash_index_insert_str(
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */char                    * key,
                        /* in */long                      block_no,   /*插入数据的 块号*/
                        /* in */unsigned  long long       record_num ,/*插入数据的块的行号*/
                        /* in */int (*hash_fun)(char *,struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long * )
                        )
{
	if( NULL == hash_fun  )  return INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	if( NULL == key       )  return INSERT_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL;	

	if( block_no < 0      )  return INSERT_MEM_HASH_INDEX_ERR_BLOCK_NO_UNSAFE;	
	//1 array_space 不存在数据，则存入数据
	//2 array_space 存在数据，link_space 不存在数据，插入link_space
	//3 存在数据，link_space  存在数据，插入link_space最近的地方
  long                     * block_no_temp     = 0;
  unsigned  long long      * insert_record_num = 0; 
  unsigned  long long      * record_num_temp   = 0;
  struct  record_t         * record_ptr        = 0;
  struct  mem_hash_entry_t * array_space_entry = 0;
  int ret;
  ret = mem_hash_index_select_str(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */block_no_temp,
                       /* out */insert_record_num,
                       /* out */record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                array_space_entry
                       );
   row_wlock(&(record_ptr->row_lock));                                                        //上行锁
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)record_ptr->data;       
   int err =-1;            
   switch(ret)
   {
   //连续空间内没找到，就覆盖到连续空间,entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
   	    record_ptr->is_used                =  1;
   	    strcpy(array_space_entry->hash_ckey, key);
   	    array_space_entry->hash_lkey       =  0;
   	    array_space_entry->block_no        =  block_no;
   	    array_space_entry->record_num      =  record_num;
   	    array_space_entry->link_block_no   =  -1;
   	    array_space_entry->link_record_num =  0;
   	    break;
   //找到相同的值就插到相同的值的后面
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	    {
   	    struct  record_t   * new_record_ptr = 0;
   	    long               *   new_block_no = 0;
   	    
   	    struct  mem_hash_entry_t hash_entry_temp;
   	    strcpy(hash_entry_temp.hash_ckey,key);
   	    hash_entry_temp.hash_lkey           = 0;
   	    hash_entry_temp.block_no            = block_no;
        hash_entry_temp.record_num          = record_num;
   	    err = mem_table_insert_record(mem_hash_index->linked_space , &new_record_ptr,new_block_no, (char *)&hash_entry_temp);
   	    if( 0 != err )return err;
   	    //将新节点链入 array_space 后面
   	    row_wlock(&(record_ptr->row_lock));                                                             //上行锁
   	    row_wlock(&(new_record_ptr->row_lock));                                                         //上行锁
   	    new_record_ptr->is_used                                               = 1;
   	    ((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_block_no   = ((struct  mem_hash_entry_t *)(record_ptr->data))->link_block_no;    
   	   	((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_record_num = ((struct  mem_hash_entry_t *)(record_ptr->data))->link_record_num;    
        ((struct  mem_hash_entry_t *)(record_ptr->data))->link_block_no       =  *new_block_no;
   	    ((struct  mem_hash_entry_t *)(record_ptr->data))->link_record_num     =  new_record_ptr->record_num;
   	    row_wunlock(&(new_record_ptr->row_lock));                                                        //解行锁
   	    row_wunlock(&(record_ptr->row_lock));                                                           //解行锁
   	    break;
   	  }
   //链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    {
   	   
   	    struct  record_t   * new_record_ptr = 0;
   	    long               * new_block_no   = 0;
   	    
   	    struct  mem_hash_entry_t hash_entry_temp;
   	    strcpy(hash_entry_temp.hash_ckey,key);
   	    hash_entry_temp.hash_lkey           = 0;
   	    hash_entry_temp.block_no            = block_no;
        hash_entry_temp.record_num          = record_num;
   	    err = mem_table_insert_record(mem_hash_index->linked_space , &new_record_ptr,new_block_no,(char *)&hash_entry_temp);
   	    if( 0 != err )return err;
   	    //将新节点链入 array_space 后面
   	    row_wlock(&(new_record_ptr->row_lock));                                                         //上行锁
   	    new_record_ptr->is_used                                                  = 1;
   	    ((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_block_no      = array_space_entry->link_block_no;    
   	   	((struct  mem_hash_entry_t *)(new_record_ptr->data))->link_record_num    = array_space_entry->link_record_num;    
        array_space_entry->link_block_no                                         = *new_block_no;
   	    array_space_entry->link_record_num                                       =  new_record_ptr->record_num;
   	    row_wunlock(&(new_record_ptr->row_lock));                                                     //解行锁
   	    break;
   	  }
   default:
   	    break;
   	
  }
  row_wlock(&(record_ptr->row_lock));                                                                  //解行锁
	return 0;
}

//删除一个整型索引的数据，如果有重复的一次只删第一个
inline int mem_hash_index_del_long(
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */unsigned  long long       key,
                        /* in */long                      block_no_to_del,
                        /* in */unsigned  long long       record_num_to_del,
                        /* in */int (*hash_fun)(unsigned  long long ,struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *)
                        )
{
	if( NULL == hash_fun  )  return DEL_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	

  long                     * block_no_temp      = 0;
  unsigned  long long      * record_num         = 0;
  struct  record_t         * record_ptr         = 0;
  struct  mem_hash_entry_t * array_space_entry  = 0;
  int ret;
  //对于重复的情况 循环找
  do{
  ret = mem_hash_index_select_long(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */block_no_temp,
                       /* out */record_num,
                       /* out */record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                array_space_entry
                       );
         row_rlock(&(record_ptr->row_lock));                                                        //上行锁             
         if(// 找到就退出  
         	(ret == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND ||  
                   ret == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND)
                  && 
                  (*record_num == record_num_to_del && block_no_to_del == *block_no_temp )
            )
            {
            	row_runlock(&(record_ptr->row_lock));                                                   //解行锁                     
            	break; 
            }
         row_runlock(&(record_ptr->row_lock));                                                        //解行锁                         
    }while(   //找到 但没对应上物理位置，就继续找
             (ret == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND || ret == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND)
          );
   row_wlock(&(record_ptr->row_lock));                                                             //上行锁 
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)record_ptr->data;    
   int err =-1;               
   switch(ret)
   {
       //连续空间内没找到
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
        return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND;
   	    break;
      //链接空间内没找到
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    return SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
   	    break;
   //找到的情况
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	     //下一个块号不存在就直接删除
   	    if(entry->link_block_no <= 0)
   	    	{
   	    		 err = mem_table_del_record(mem_hash_index->array_space , record_ptr);
   	    		 entry->link_block_no = 0;
   	    		 entry->link_record_num      = 0;
   	    		 row_wunlock(&(record_ptr->row_lock));                                                        //解行锁 
   	    		 return 0;
   	    	}
   	    //找 entry 的下一个连接所在的块号
   	    int i =0;
   	    struct mem_block_t * mem_block_temp = mem_hash_index->linked_space->config.mem_blocks_table;
   	    for(;i<mem_hash_index->linked_space->config.mem_block_used;++i)
   	    {
   	    	if(mem_block_temp->block_no == entry->link_block_no) break;//找到下一个块号
   	    	mem_block_temp = mem_block_temp->next;
   	    }
   	    // 没找到块号则失败
   	    if(mem_hash_index->linked_space->config.mem_block_used == i)return MEM_HASH_ERR_BLOCK_NO_NOT_EXIST;
   	    // 找到块号,将下一个 entry copy 到 这个 entry,然后将下一个 entry 从链表中删除
   	    struct record_t * next_record_ptr = (struct record_t *)(mem_block_temp->space_start_addr + entry->link_block_no* MEM_HASH_ENTRY_SIZE);
   	    row_wlock(&(next_record_ptr->row_lock));                                                          //上行锁
   	    struct mem_hash_entry_t * next_hash_entry	= (struct mem_hash_entry_t * )next_record_ptr->data;
   	    //将内容copy 到 这个 entry
   	    memcpy(entry,next_hash_entry,MEM_HASH_ENTRY_SIZE);
   	    //删除下个entry
   	    err = mem_table_del_record(mem_hash_index->array_space , next_record_ptr);
   	    next_hash_entry->hash_lkey = 0;
   	    next_hash_entry->link_record_num =  0;
   	    row_wunlock(&(next_record_ptr->row_lock));                                                       //解行锁
   	    break;
   default:
   	    row_wunlock(&(record_ptr->row_lock));                                                             //解行锁 
   	    return ret;
  }
    row_wunlock(&(record_ptr->row_lock));                                                                 //解行锁 
	return 0;
}

//插入一个字符串索引的数据,保证每个桶相同的 val 相邻
inline int mem_hash_index_del_str(
                        /* in */struct mem_hash_index_t * mem_hash_index ,
                        /* in */char                    * key,
                        /* in */long                      block_no_to_del,
                        /* in */unsigned  long long       record_num_to_del,
                        /* in */int (*hash_fun)(char *,struct  mem_block_t *,/*返回哈希表的行号*/unsigned long long *)
                        )
{
	if( NULL == hash_fun  )  return DEL_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL;	
	if( NULL == key       )  return DEL_MEM_HASH_INDEX_ERR_STR_KEY_IS_NULL;	

  long                     * block_no_temp      = 0;
  unsigned  long long      * record_num         = 0;
  struct  record_t         * record_ptr         = 0;
  struct  mem_hash_entry_t * array_space_entry  = 0;
  int ret;
  //对于重复的情况 循环找
  do{
  ret = mem_hash_index_select_str(
                                mem_hash_index ,
                                key,
                                hash_fun,
                       /* out */block_no_temp,
                       /* out */record_num,
                       /* out */record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD   */
                                array_space_entry
                       );
         row_rlock(&(record_ptr->row_lock));                                                            //上行锁               
         if(// 找到就退出  
         	(ret == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND ||  
                   ret == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND)
                  && 
                  (*record_num == record_num_to_del && block_no_to_del == *block_no_temp )
            )
            {
            	row_runlock(&(record_ptr->row_lock));                                                   //解行锁
            	break; 
            }
                       
    }while(   //找到 但没对应上物理位置，就继续找
             (ret == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND || ret == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND)
          );
   row_wlock(&(record_ptr->row_lock));                                                             //上行锁                
   struct  mem_hash_entry_t * entry = (struct  mem_hash_entry_t *)record_ptr->data; 
   int err = -1;                  
   switch(ret)
   {
       //连续空间内没找到
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
        return SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND;
   	    break;
      //链接空间内没找到
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
   	    return SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND;
   	    break;
   //找到的情况
   case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
   case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
   	     //下一个块号不存在就直接删除
   	    if(entry->link_block_no <= 0)
   	    	{
   	    		 err = mem_table_del_record(mem_hash_index->array_space , record_ptr);
   	    		 entry->link_block_no = 0;
   	    		 entry->link_record_num      = 0;
   	    		 row_wunlock(&(record_ptr->row_lock));                                                  //解行锁
   	    		 return 0;
   	    	}
   	    //找 entry 的下一个连接所在的块号
   	    int i =0;
   	    struct mem_block_t * mem_block_temp = mem_hash_index->linked_space->config.mem_blocks_table;
   	    for(;i<mem_hash_index->linked_space->config.mem_block_used;++i)
   	    {
   	    	if(mem_block_temp->block_no == entry->link_block_no) break;//找到下一个块号
   	    	mem_block_temp = mem_block_temp->next;
   	    }
   	    // 没找到块号则失败
   	    if(mem_hash_index->linked_space->config.mem_block_used == i)return MEM_HASH_ERR_BLOCK_NO_NOT_EXIST;
   	    // 找到块号,将下一个 entry copy 到 这个 entry,然后将下一个 entry 从链表中删除
   	    struct record_t * next_record_ptr = ((struct record_t *)(mem_block_temp->space_start_addr + entry->link_block_no* MEM_HASH_ENTRY_SIZE));
   	    row_wlock(&(next_record_ptr->row_lock));                                                      //上行锁 
   	    struct mem_hash_entry_t * next_hash_entry	= (struct mem_hash_entry_t * )next_record_ptr->data;
   	    //将内容copy 到 这个 entry
   	    memcpy(entry,next_hash_entry,MEM_HASH_ENTRY_SIZE);
   	    //删除下个entry
   	    err = mem_table_del_record(mem_hash_index->array_space , next_record_ptr);
   	    //next_hash_entry->hash_ckey = 0;
   	    next_hash_entry->link_record_num  = 0;
   	    row_wunlock(&(next_record_ptr->row_lock));                                                        //解行锁
   	    break;
   default:
   	     row_wunlock(&(record_ptr->row_lock));                                                             //解行锁
   	    return ret;
  }
  row_wunlock(&(record_ptr->row_lock));                                                                    //解行锁

	return 0;
	}
	
	
// 替换hash 索引,先删再插入
 inline int mem_hash_index_update_long (
                        /* in */struct mem_hash_index_t *  mem_hash_index ,
                        /* in */unsigned  long long        key,
                        /* in */int (*hash_fun)(unsigned  long long key,/*连续空间块*/struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *),
                        /* in */long                       block_no, /*插入数据的块号*/
                        /* in */unsigned  long long        record_num ,/*插入数据的块的行号*/
                       /* out */struct  record_t         * record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD  输出找到的块所在记录的指针 */
                       /* out */struct  mem_hash_entry_t * array_space_entry //输出对应 连续空间的 hash 项索引
                                        )             
                        {
                        int                  err1,err2;
                        long                 block_no_to_del;
                        unsigned  long long  record_num_to_del;
                        
                        err1 = mem_hash_index_del_long( 
                        														  mem_hash_index,
                        														  key,
                        														  block_no_to_del,
                        														  record_num_to_del,
                        														  hash_fun);
                       if( 0 != err1 )return err1;
                       err2 = mem_hash_index_insert_long( 
                        														  mem_hash_index,
                        														  key,
                        														  block_no,
                        														  record_num,
                        														  hash_fun);
                      if( 0 != err2 )return err2;
                      return 0;
}
                      
                      
	
// 替换hash 索引,先删再插入
inline int mem_hash_index_update_str (
                                struct mem_hash_index_t *  mem_hash_index ,
                        /* in */char                    *  key,
                        /* in */int (*hash_fun)(char    *  key,/*连续空间块*/struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *),
                        /* in */long                       block_no, /*插入数据的块号*/
                        /* in */unsigned  long long        record_num ,/*插入数据的块的行号*/
                       /* out */struct  record_t         * record_ptr, /* IF FOUND ,RETURN FOUNDED RECORD  输出找到的块所在记录的指针 */
                       /* out */struct  mem_hash_entry_t * array_space_entry //输出对应 连续空间的 hash 项索引
                                        )             
                        {
                        int                  err1,err2;
                        long                 block_no_to_del;
                        unsigned  long long  record_num_to_del;
                        
                        err1 = mem_hash_index_del_str( 
                        														  mem_hash_index,
                        														  key,
                        														  block_no,
                        														  record_num,
                        														  hash_fun);
                       if( 0 != err1 )return err1;
                       err2 = mem_hash_index_insert_str( 
                        														  mem_hash_index,
                        														  key,
                        														  block_no,
                        														  record_num,
                        														  hash_fun);
                      if( 0 != err2 )return err2;
                      return 0;
                      }
                      
//建HASH索引
inline int mem_hash_index_create(
														 struct mem_hash_index_t       **   mem_hash_index,
                             struct mem_table_t              *  mem_table,// 原表
                             struct mem_hash_index_config_t  *  mem_index_config
                             )
{
	
	if(NULL == mem_table                          )  return CREATE_HASH_INDEX_ERR_TABLE_PTR;
	if(NULL == mem_index_config                   )  return CREATE_HASH_INDEX_ERR_NULL_CONFIG;
	if(NULL == mem_index_config->index_name       )  return CREATE_HASH_INDEX_ERR_NO_NAME;
	if(strlen (mem_index_config->index_name)>=120 )  return CREATE_HASH_INDEX_ERR_NAME_TOO_LONG;
  if(mem_index_config->owner_table_no<=0        )  return CREATE_HASH_INDEX_ERR_NO_TABLE_NO;
	if(NULL == mem_index_config->field_order      )  return CREATE_HASH_INDEX_ERR_NO_FIELD_PTR;
  if(mem_index_config->field_num <= 0          )   return CREATE_HASH_INDEX_ERR_FIELD_NUM_LESS_ZERO;

      int len = strlen(mem_index_config->index_name);
			//allocate_index_no(&(mem_index_config->index_no));
      //1.构造 heap_space 的 block
     int i=0;
	   struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	   off_t array_space_size = 0;

     //遍历原表所有块,累加原表哌数据块大小
	   for(;i<mem_table->config.mem_block_used;++i)
	   { 
	   	  //取array块大小
	   	  array_space_size += mem_block_temp->block_size;   
	   		mem_block_temp = mem_block_temp->next;      //下一个块
      }
        //生成块描述符
       mem_block_t *mb = (mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	     DEBUG("create mem_array_hash block %0x\n",*mb);
      
      //配置块描述符 //设置两个 heap_space 块大小,将配置数和数据数比较取最大
       off_t _block_size = (mem_index_config->array_block_size > array_space_size ) ? mem_index_config->array_block_size : array_space_size;      
			 DEBUG("array_space_size is %d\n",_block_size);
			 
			 char tem_buf[256]={0};
       strcpy(tem_buf,mem_index_config->index_name);
       strcat(tem_buf,"_array.dat\0");
       
			 mem_block_config( mb  ,array_space_size , tem_buf );
       
       //2. 构造 array_fields_table
			 struct field_t *_fields_table   = (struct field_t *) malloc(FIELD_SIZE);
		   _fields_table[0].field_type     = FIELD_TYPE_HASH_ENTRY;
		   
		   
		  //构造 array_space_config
		  struct mem_table_config_t * array_space_config = (struct mem_table_config_t *)malloc(MEM_TABLE_CONFIG_SIZE); 
		  //array_space_config->mem_table_no             = allocat_mem_table_no();
      //array_space_config->owner_id                   = mem_table->owner_id;
      array_space_config->fields_table               = _fields_table;
      array_space_config->field_used_num             = 1;
      array_space_config->mem_block_used             = 1;
      array_space_config->field_used_num             = 1;
      array_space_config->auto_extend                = 0; //不允许自动扩展
      array_space_config->mem_blocks_table           = mb;
      array_space_config->mem_blocks_table->next     = 0;
      strcpy(array_space_config->table_name,mem_index_config->index_name);
      strcat(array_space_config->table_name,"_array.dat\0");
      DEBUG("array_space_config->table_name is %s \n",array_space_config->table_name);
      //4.构造 mem_table_t
			struct mem_table_t      *array_space_temp ;  		
			int err=0;
      err = mem_table_create(
                             &array_space_temp,
                             array_space_config
                             );
      DEBUG(" array_space_temp is %0x \n",array_space_temp);

//___________________________________________________________________________________
      //生成块描述符
       mem_block_t *mb2 = (mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	     DEBUG("create mem_array_hash block %0x\n",*mb2);
       off_t link_space_size;
      //取 link 块大小
	    link_space_size = array_space_size/mem_index_config->div;
	    //设置两个space 块大小,将配置数和数据数比较取最大
      //array_space_config->mem_blocks_table->block_size = (mem_index_config->array_block_size > array_block_size ) ? mem_index_config->array_block_size : array_block_size;
      link_space_size= (mem_index_config->link_block_size  > link_space_size  ) ? mem_index_config->link_block_size  : link_space_size;
      //配置块描述符 
      char tem_buf2[256]={0};
      strcpy(tem_buf2,mem_index_config->index_name);
      strcat(tem_buf2,"_link.dat\0");
      mem_block_config( mb2  ,link_space_size , tem_buf2 );
      
      //2. 构造 fields_table
			 struct field_t *_fields_table2   = (struct field_t *) malloc(FIELD_SIZE);
		  _fields_table2[0].field_type      = FIELD_TYPE_HASH_ENTRY;
		  
		  // 3.构造 link_space_config
      
      struct mem_table_config_t * link_space_config = (struct mem_table_config_t *)malloc(MEM_TABLE_CONFIG_SIZE); 
		  //array_space_config->mem_table_no            = allocat_mem_table_no();
      //link_space_config->owner_id                   = mem_table->owner_id;
      link_space_config->fields_table               = _fields_table2;
      link_space_config->field_used_num             = 1;
      link_space_config->mem_block_used             = 1;
      link_space_config->auto_extend                = 1; //允许自动扩展
      link_space_config->mem_blocks_table           = mb2;
      link_space_config->mem_blocks_table->next     = 0;
      strcpy(link_space_config->table_name,mem_index_config->index_name);
      strcat(link_space_config->table_name,"_link.dat\0");
      DEBUG(" link_space_config->table_name is %s \n",link_space_config->table_name);
			
			//4.构造 mem_table_t
			struct mem_table_t      *link_space_temp ;  		
      err = mem_table_create(
                             &link_space_temp,
                             link_space_config
                             );
      DEBUG(" link_space_config is %0x \n",link_space_config);
 			
 			//5 设置  mem_rbtree_index             
      (*mem_hash_index) = (struct mem_hash_index_t  *)malloc(MEM_HASH_INDEX_SIZE);
      (*mem_hash_index) -> config.index_no         = mem_index_config->index_no;
      (*mem_hash_index) -> config.owner_table_no   = mem_index_config->owner_table_no;
      (*mem_hash_index) -> config.field_order      = mem_index_config->field_order;
      (*mem_hash_index) -> config.field_num        = mem_index_config->field_num;
      (*mem_hash_index) -> config.owner_id         = mem_index_config->owner_id;
      (*mem_hash_index) -> config.div              = mem_index_config->div;
      (*mem_hash_index) -> config.array_block_size = array_space_config->mem_blocks_table->block_size;
      (*mem_hash_index) -> config.link_block_size  = link_space_config->mem_blocks_table->block_size ;
       strcpy((*mem_hash_index) -> config.index_name,mem_index_config->index_name);
				//设置堆内存
       (*mem_hash_index)->array_space = array_space_temp;
       (*mem_hash_index)->linked_space = link_space_temp;
             
      
      if(0!=err)return err;
      //对每个项建索引
//___________________________________________________________________________________      
      return 0;
}



//打开索引
inline int mem_hash_index_open(struct mem_hash_index_t *  mem_hash_index)
{
	if(NULL == mem_hash_index    )  return OPEN_MEM_HASH_ERR_NULL_HASH_PTR;
  
  int err;
	err = mem_table_open(mem_hash_index->array_space);
	if( 0!= err )return err;
	err = mem_table_open(mem_hash_index->linked_space);
	if( 0!= err )return err;
	return 0;
}	
//关索引
inline	int mem_hash_index_close(struct mem_hash_index_t *  mem_hash_index)
{
	if(NULL == mem_hash_index    )  return CLOSE_MEM_HASH_INDEX_ERR_NULL_PTR;
	  int err,err1;
	  err  = mem_table_close((mem_hash_index)->array_space);
	  err1 = mem_table_close((mem_hash_index)->linked_space);
	  //del_index_no_addr(mem_hash_index->config.index_no);
	  if(0 != err)return err;
	  if(0 != err1)return err1;
		if(mem_hash_index)free(mem_hash_index);
		return 0;
	}