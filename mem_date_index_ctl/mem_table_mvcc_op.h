#ifndef MVCC_CTL
#define MVCC_CTL
#include "mem_transaction.h"
#define ROLLBACK_STACK_NOT_FOUND 						  50001

#ifdef __cplusplus

extern "C" {

#endif
//__________________________________________________________
//___mvcc__operations_______________________________________
//__________________________________________________________


//支持事务的mvcc读取一个记录的数据
inline int mem_mvcc_read_record(struct mem_table_t *mem_table ,
                                      struct record_t * record_ptr,
                                      char *buf, //读取缓存
                                      unsigned long long  Tn    //当前事务ID
                                      )
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )  return READ_RECORD_ERR_BUF_IS_NULL;	
			
	row_rlock   (  &(record_ptr->row_lock )                                            );

 	//记录未使用
	if( 0 == record_ptr->is_used )
	{
		row_runlock (  &(record_ptr->row_lock )    );
		ERROR("READ_RECORD_UNUSED\n");                                        
		return READ_RECORD_UNUSED;
	}
	
    //如果被其它未提交的事务修改过，不能直接读出,要读最近的一次回滚段
	if( record_ptr->scn !=0 && record_ptr->scn > Tn /*&& Tn is not comminted*/)
	{
		mem_trans_data_entry_t *undo_info_ptr = (mem_trans_data_entry_t *)(record_ptr->undo_info_ptr) ;
		
		//找到本事务的回滚栈
		mem_trans_data_entry_t * rollback_stack_table = transaction_manager.transaction_tables[Tn].rollback_stack.item;
		long end = transaction_manager.transaction_tables[Tn].rollback_stack.end;
		
		//如果该行被改过多次并且修改的多个事务没有提交，可能会发生幻读
		//改回滚info 不在 回滚栈中，则找下一个回滚栈
		while(!(undo_info_ptr>=rollback_stack_table && undo_info_ptr<= rollback_stack_table + TRANS_DATA_ENTRY_SIZE*end))
			{
				if(NULL == undo_info_ptr)
					{
						row_runlock (  &(record_ptr->row_lock ) );
						ERROR("ROLLBACK_STACK_NOT_FOUND\n");
						return ROLLBACK_STACK_NOT_FOUND;
					}
					undo_info_ptr = undo_info_ptr->next;
			}
		DEBUG("find rollback addr !\n");
		row_runlock (  &(record_ptr->row_lock ) );
		memcpy     (    buf,  (char *)(undo_info_ptr->trans.undo_addr_ptr), mem_table->record_size - RECORD_HEAD_SIZE  );
		return 0;
		//return READ_RECORD_SCN_NOT_COMMITED;    // 数据被之前事物写过且之前的事物未提交
	}
	memcpy     (    buf,  (char *)(record_ptr) + RECORD_HEAD_SIZE, mem_table->record_size - RECORD_HEAD_SIZE  );
	row_runlock (  &(record_ptr->row_lock )                                            );
	return 0;
}

//支持事务的mvcc插入一个记录的数据
inline int __mem_mvcc_insert_record(struct mem_table_t *mem_table ,
                          /* out */struct record_t ** record_ptr,
                          long * block_no, /* in */
                          char *buf,
                          unsigned long long Tn ,                       //事务ID
                          short is_lock
                          )
{
	if( NULL == mem_table )  return INSERT_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == buf       )  return INSERT_RECORD_ERR_BUF_IS_NULL;	
  		
  int err;

  //err= mem_table_allocate_record(mem_table ,/* out */ record_ptr,block_no);
  //err= mem_table_allocate_record_with_freelist(mem_table ,/* out */ record_ptr,block_no,Tn);

  err= mem_table_allocate_record_with_rfreelist(mem_table ,/* out */ record_ptr,block_no,Tn);

	if(0!= err)
		{
			ERROR("mvcc allocate_record failed!\n");
			return err;
		}
	DEBUG(" ----- Enter mem_mvcc_insert_record(),record_ptr is %0x ----- \n",*record_ptr);
	

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( Tn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物号
  trans_entry.redo_type             = OPT_DATA_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_DATA_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = mem_table->record_size; // redo 数据长度
  trans_entry.undo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // undo 数据长度	
  trans_entry.block_no              = *block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table->config.mem_table_no;//表或索引的 no      							
  strcpy(trans_entry.name,mem_table->config.table_name );
  
  mem_block_t * mem_block_ptr;
  get_block_no_addr(*block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  
  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;
  
  //修改为本次的事务ID
  (*record_ptr)->scn = Tn;
	memcpy      (  (*record_ptr)->data,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
	if(is_lock)row_wunlock (  &((*record_ptr)->row_lock) );
	return 0;
}

//支持事务的mvcc插入一个记录的数据
inline int mem_mvcc_insert_record(struct mem_table_t *mem_table ,
                          /* out */struct record_t ** record_ptr,
                          long * block_no, /* in */
                          char *buf,
                          unsigned long long Tn                        //事务ID
                          )
{
	return __mem_mvcc_insert_record(mem_table ,
                          record_ptr,
                          block_no, /* in */
                          buf,
                          Tn ,                       //事务ID
                          1
                          );
}

//支持事务的MVCC 修改一个记录的数据
inline int __mem_mvcc_delete_record(struct mem_table_t *mem_table ,
																				struct record_t * record_ptr,
																				unsigned long long  Tn,               // 本事务ID
																				short is_lock
																				)
{
	if( NULL == mem_table )        return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)        return READ_RECORD_ERR_RECORD_IS_NULL;

	DEBUG(" ----- Enter mem_mvcc_delete_record(),record_ptr is %0x ----- \n",record_ptr);
	if(is_lock)row_wlock   (  &(record_ptr->row_lock) );
	
		//记录未使用
	if( 0 == record_ptr->is_used )
	{
		if(is_lock)row_wunlock (  &(record_ptr->row_lock )                                            );
		ERROR("READ_RECORD_UNUSED\n");
		return READ_RECORD_UNUSED;
	}
	
	//事务未释放
	if( Tn < record_ptr->scn )
	{
		if(is_lock)row_wunlock (  &(record_ptr->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n");
		return TRANS_NOT_FREE;
	}
	
	int err;
	mem_block_t * mem_block_temp;
	
	if(0 != (err=get_block_by_record(mem_table ,record_ptr,&mem_block_temp)))
	{
			ERROR("GET_BLOCK_FAILD\n");
			if(is_lock)row_wunlock (  &(record_ptr->row_lock )                                            );
			return err;
	}
  long block_no = mem_block_temp->block_no;
	

	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							  //当前事物号
  trans_entry.redo_type             = OPT_DATA_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_DATA_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void*)((char *)(record_ptr)   + RECORD_HEAD_SIZE);	//原始数据起始地址
  trans_entry.redo_data_length      = mem_table->record_size; // redo 数据长度
  trans_entry.undo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table->config.mem_table_no;//表或索引的 no      							
  strcpy(trans_entry.name,mem_table->config.table_name );

  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  //保留上一次回滚栈信息
  undo_info_ptr->next = (mem_trans_data_entry_t*)((record_ptr)->undo_info_ptr);
    
     // 指向回滚信息
    (record_ptr)->undo_info_ptr = undo_info_ptr;
	

 //修改为本次的事务ID
  record_ptr->scn = Tn;
  
MEM_TABLE_DEL_CODE 
     
	if(is_lock)row_wunlock (  &(record_ptr->row_lock)                 );
	DEBUG(" ----- Enter mem_mvcc_delete_record()end ----- \n");

	return 0;
}
inline int mem_mvcc_delete_record(struct mem_table_t *mem_table ,
																				struct record_t * record_ptr,
																				unsigned long long  Tn               // 本事务ID
																				)
{
	return __mem_mvcc_delete_record(mem_table ,
																	record_ptr,
																	Tn,               // 本事务ID
																	1
																				);
}																				

//_________________________________________________________

//支持事务的MVCC 修改一个记录的数据
inline int mem_mvcc_update_record(struct mem_table_t *mem_table ,
																				struct record_t * record_ptr,
																				char *buf,
																				unsigned long long  Tn,               // 本事务ID
																				/*out*/struct record_t ** record_ptr2
																				)
{
if( NULL == mem_table )        return READ_RECORD_ERR_TABLE_IS_NULL;
if( NULL == record_ptr)        return READ_RECORD_ERR_RECORD_IS_NULL;
if( NULL == buf       )        return READ_RECORD_ERR_BUF_IS_NULL;	
	DEBUG(" ----- Enter mem_mvcc_update_record(),record_ptr is %0x ----- \n",record_ptr);

//row_wlock   (  &(record_ptr->row_lock) );
//
//	//记录未使用
//if( 0 == record_ptr->is_used )
//{
//	row_wunlock (  &(record_ptr->row_lock )                                            );
//	ERROR("READ_RECORD_UNUSED\n");          
//	return READ_RECORD_UNUSED;
//}
//
////事务未释放
//if( Tn< record_ptr->scn )
//{
//	row_wunlock (  &(record_ptr->row_lock )                                            );
//	 ERROR("TRANS_NOT_FREE\n"); 
//	 return TRANS_NOT_FREE;
//}
//
//int err;
//mem_block_t * mem_block;
//
//if(0 != (err=get_block_by_record(mem_table ,record_ptr,&mem_block)))
//{
//	 	row_wunlock (  &(record_ptr->row_lock )                                            );
//		ERROR("GET_BLOCK_FAILD\n");
//		return err;
//}
// long block_no = mem_block->block_no;
//
//
////回滚信息
// mem_trans_data_entry_t * undo_info_ptr;
// //构造一个事务
// mem_transaction_entry_t  trans_entry ;
// 
// trans_entry.trans_no       			 = Tn;       							  //当前事物号
// trans_entry.redo_type             = OPT_DATA_UPDATE;				//redo 操作类型
// trans_entry.undo_type						 = OPT_DATA_UPDATE;				//undo 操作类型 insert update delete truncate index_op
// trans_entry.ori_data_start        = (void *)((char *)(record_ptr)   + RECORD_HEAD_SIZE);	//原始数据起始地址
// trans_entry.redo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // redo 数据长度
// trans_entry.undo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // undo 数据长度	
// trans_entry.block_no              = block_no;
// trans_entry.record_num            = (record_ptr)->record_num; 
// trans_entry.object_no 					   = mem_table->config.mem_table_no;//表或索引的 no      							
// 
// if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
// 
//   //保留上一次回滚栈信息
//   undo_info_ptr->next = (record_ptr)->undo_info_ptr;
//    // 指向回滚信息
//   (record_ptr)->undo_info_ptr = undo_info_ptr;
//
// //修改为本次的事务ID
// record_ptr->scn = Tn;
////修改数据
////memcpy     (   (char *)(record_ptr) + RECORD_HEAD_SIZE,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
//row_wunlock (  &(record_ptr->row_lock) );
row_wlock (  &(record_ptr->row_lock) ); 
int err;

err = __mem_mvcc_delete_record( mem_table ,
																				record_ptr,
																				Tn,               // 本事务ID
																				0);
	  	if(err!=0)
	  	{
	  		ERROR("mem_mvcc_update_record on delete, err is %d\n",err);
	  	}

long  block_no;
err =  __mem_mvcc_insert_record( mem_table ,
                          record_ptr2,
                          &block_no, /* in */
                          buf,
                          Tn,                        //事务ID
                          0);     

	  	if(err!=0)
	  	{
	  		ERROR("mem_mvcc_update_record on insert, err is %d\n",err);
	  	}

	  	if(err!=0)
	  	{
	  		return err;
	  	}
	row_wunlock (  &(record_ptr->row_lock) ); 
	return 0;
}

//__________hash 索引的事务___________________________

//支持事务的mvcc插入一个记录的数据
inline int __mem_hash_index_mvcc_insert_l(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_long * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn,                       //事务ID
                          short is_lock
                          )
{
int err;
	DEBUG(" ----- Enter __mem_hash_index_mvcc_insert_long() ----- \n");
long mem_table_no;
long block_no;
err =  mem_hash_index_insert_l(
                        /* in */mem_hash_index ,
                        				input,
                        /* out */record_ptr,
                         /* out */&block_no,
                        &mem_table_no
                        ) ;  

//get_hash_block_no_by_record_ptr(*record_ptr,block_no);

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( Tn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table_no;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void ** )(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );

  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;
  
  //修改为本次的事务ID
  (*record_ptr)->scn = Tn;

	return 0;
}
//支持事务的mvcc插入一个记录的数据
inline int mem_hash_index_mvcc_insert_l(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_long * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn
                          )
{
	return  __mem_hash_index_mvcc_insert_l(                        
                          mem_hash_index ,
                          input,
                          record_ptr,
                          Tn,                       //事务ID
                          1
                          );
	
}
inline int __mem_hash_index_mvcc_del_l(
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_long * input,
                        /* out */struct    record_t   **  record_ptr,
                         unsigned long long Tn,                       //事务ID
												 short is_lock
                        )   
{
	
	
int err;
	DEBUG(" ----- Enter __mem_hash_index_mvcc_del_l() ----- \n");
long mem_table_no;
long block_no;
err =  mem_hash_index_del_l(
                        /* in */mem_hash_index ,
                        				input,
                        /* out */record_ptr,
                        /* out */&block_no,
                        &mem_table_no
                        ) ;  
//get_hash_block_no_by_record_ptr(*record_ptr,block_no);

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( Tn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物号
  trans_entry.redo_type             = OPT_INDEX_HASH_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table_no;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void **)(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );
  
  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );
  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;
  
  //修改为本次的事务ID
  (*record_ptr)->scn = Tn;

	return 0;
	
	
}

inline int mem_hash_index_mvcc_del_l(
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_long * input,
                        /* out */struct    record_t   **  record_ptr,
                         unsigned long long Tn,                       //事务ID
												 short is_lock
                        )   
{
        return  __mem_hash_index_mvcc_del_l(
                       mem_hash_index ,
                       input,
                       record_ptr,
                       Tn,                       //事务ID
											1
                        );            	
}


inline int __mem_hash_index_mvcc_insert_str(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_str * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn,                       //事务ID
                          short is_lock
                          )
{
int err;
	DEBUG(" ----- Enter __mem_hash_index_mvcc_insert_strong() ----- \n");
long mem_table_no;
long block_no;
err =  mem_hash_index_insert_s(
                        /* in */mem_hash_index ,
                        				input,
                        /* out */record_ptr,
                         /* out */&block_no,
                        &mem_table_no
                        ) ;  

//get_hash_block_no_by_record_ptr(*record_ptr,block_no);

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( Tn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table_no;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void **)(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );
  
  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **) mem_block_ptr);
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;
  
  //修改为本次的事务ID
  (*record_ptr)->scn = Tn;

	return 0;
}

inline int mem_hash_index_mvcc_insert_str(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_str * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn,                       //事务ID
                          short is_lock
                          )
{
	
	return  __mem_hash_index_mvcc_insert_str(                        
                        /* in */ mem_hash_index ,
                        				 input,
                        /* out */record_ptr,
                          Tn,                       //事务ID
                          1
                          );
	
}

inline int __mem_hash_index_mvcc_del_str(
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_str * input,
                        /* out */struct    record_t   **  record_ptr,
                         unsigned long long Tn,                       //事务ID
												 short is_lock
                        )   
{
	
	
int err;
	DEBUG(" ----- Enter __mem_hash_index_mvcc_del_str() ----- \n");
long mem_table_no;
long block_no;
err =  mem_hash_index_del_s(
                        /* in */mem_hash_index ,
                        				input,
                        /* out */record_ptr,
                        /* out */&block_no,
                        &mem_table_no
                        ) ;  
//get_hash_block_no_by_record_ptr(*record_ptr,block_no);

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( Tn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物号
  trans_entry.redo_type             = OPT_INDEX_HASH_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_table_no;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void **)(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );
  
  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;
  
  //修改为本次的事务ID
  (*record_ptr)->scn = Tn;

	return 0;
	
	
}


inline int mem_hash_index_mvcc_del_str(
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_str * input,
                        /* out */struct    record_t   **  record_ptr,
                         unsigned long long Tn
                        ) 
{
return __mem_hash_index_mvcc_del_str(
                        /* in */ mem_hash_index ,
                        				 input,
                        /* out */record_ptr,
                         				Tn,
                         				1
                        );
                        	
                        	
}


/*插入一个结点*/
inline int  __mem_rbtree_mvcc_insert(mem_rbtree_index_t *mem_rbtree_index, 
																			mem_rbtree_entry_t *root,
																			mem_rbtree_entry_t* key,
																			unsigned long long Tn,
																			short is_lock
																			)
{
	 if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
   if(NULL == key               )  return RBTREE_INDEX_ERR_NULL_KEY_PRT;
   
   char buf[MEM_RBTREE_ENTRY_SIZE];
   int err;
   
   //DEBUG("Enter mem_rbtree_insert(),insert value is %ld ;\n",key->rbtree_lkey);

   if(is_lock)RBTREE_LOCK(&(mem_rbtree_index->locker));
   
	     struct  record_t* record_ptr;
			 long  block_no;
			 if( root == NULL  )
			 {
			 	 DEBUG("Insert Root Node: \n");
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
       
        err = mem_mvcc_insert_record(mem_rbtree_index->heap_space ,
                          /* out */&record_ptr,
                          &block_no, /* in */
                          buf,
                          Tn);       
       
        //err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr,&block_no,buf);
        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));
        		return err;
        	}
			 	
			 	// root 是 0号行
			 	root = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
			 	//初始化mem_rbtree_index->nil结点，nil 是 1号行
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	DEBUG("Insert NIl Node: \n");
				struct  record_t* record_ptr2;
				
				
			 	//err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr2,&block_no,buf);
        err = mem_mvcc_insert_record(mem_rbtree_index->heap_space ,
                          /* out */&record_ptr2,
                          &block_no, /* in */
                          buf,
                          Tn);    
        
        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));
        		return err;
        	}
			 	
			 	mem_rbtree_index->nil   = (mem_rbtree_entry_t *)((char *)(record_ptr2) + RECORD_HEAD_SIZE);
			 	mem_rbtree_index->nil->color = BLACK;
			 	// nil 的相关数据都指向自己
			 	mem_rbtree_index->nil->block_no   			 =  block_no;			  
        mem_rbtree_index->nil->record_num 			 =  record_ptr2->record_num; 
			 	mem_rbtree_index->nil->parent_block_no   =  block_no;			  
        mem_rbtree_index->nil->parent_record_num =  record_ptr2->record_num; 			
        mem_rbtree_index->nil->left_block_no     =  block_no;			    
        mem_rbtree_index->nil->left_record_num   =  record_ptr2->record_num;		
        mem_rbtree_index->nil->right_block_no    =  block_no;			    
        mem_rbtree_index->nil->right_record_num  =  record_ptr2->record_num;
        DEBUG("nil->block_no = %d,nil->record_num = %d \n",mem_rbtree_index->nil->block_no,mem_rbtree_index->nil->record_num);

			 	//设置结点的指向
			 	mem_rbtree_set_parent(root,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_left  (root,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_right (root,mem_rbtree_index->nil   );	
			 	
			 	//设置结点属性,key 和color
			  root->rbtree_lkey = key->rbtree_lkey;
			 	root->block_no    = key->block_no;
			 	root->record_num  = key->record_num;
			 	root->color       = key->color;
			 	mem_rbtree_index->root  = root;
			 }else{
			 	mem_rbtree_entry_t* x = root;
			 	mem_rbtree_entry_t* p = mem_rbtree_index->nil;
			 while( x != mem_rbtree_index->nil ){
			 DEBUG("x != mem_rbtree_index->nil,x->rbtree_lkey = %ld ;\n",x->rbtree_lkey);
	 	
			 		p = x;
			 		if     ( key->rbtree_lkey > x->rbtree_lkey  ) x =  mem_rbtree_right(mem_rbtree_index,x);
			 		else if(	key->rbtree_lkey < x->rbtree_lkey ) x =  mem_rbtree_left(mem_rbtree_index,x);
			 			else
			 				{
			 				if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));
			 				DEBUG("mem_rbtree_insert(); end\n");
			 				return 0;
			 			}
			 	}
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	DEBUG("Insert Value Node ,Insert value is %ld ;\n",key->rbtree_lkey);
			 	//err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr,&block_no,buf);
        
        err = mem_mvcc_insert_record(mem_rbtree_index->heap_space ,
                          /* out */&record_ptr,
                          &block_no, /* in */
                          buf,
                          Tn);    
                          

        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));
        		return err;
        	}
			 
			 	//获得数据
			 	x = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
			 	
			 	mem_rbtree_set_parent(x,p   );	
			 	mem_rbtree_set_left  (x,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_right (x,mem_rbtree_index->nil   );	
			 	//设置结点属性,key 和color 			 
			 	x->rbtree_lkey = key->rbtree_lkey;
			 	x->block_no    = key->block_no;
			 	x->record_num  = key->record_num;			 	 
			 	x->color  = RED;
			 	if(key->rbtree_lkey < p->rbtree_lkey) mem_rbtree_set_left(p,x);
			 	else{
			 		mem_rbtree_set_right(p,x);
			 	}
			 		mem_rbtree_insert_fixup  (mem_rbtree_index,root,x);
			 	}
			 	if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));

  	 	  DEBUG("mem_rbtree_insert(); end\n");

return 0;
}

/*插入一个结点*/
inline int  mem_rbtree_mvcc_insert(mem_rbtree_index_t *mem_rbtree_index, 
																			mem_rbtree_entry_t *root,
																			mem_rbtree_entry_t* key,
																			unsigned long long Tn
																			)
{
return  __mem_rbtree_mvcc_insert(mem_rbtree_index, 
																 root,
																 key,
																 Tn,
														  	 1);
																				
}

inline int __mem_rbtree_mvcc_delete(mem_rbtree_index_t *mem_rbtree_index,
																mem_rbtree_entry_t *root,
																mem_rbtree_entry_t* z,	
																unsigned long long Tn,
																short is_lock
																)
{
	  if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
	  if( z==mem_rbtree_index->nil  || z==NULL )return MEM_RBTREE_DELETE_NULL;
	  	
	  DEBUG("Enter mem_rbtree_delete();\n");	
	  if(is_lock)RBTREE_LOCK(&(mem_rbtree_index->locker));

	   mem_rbtree_entry_t* y;
	   mem_rbtree_entry_t* x;
	   if(
	   	mem_rbtree_left(mem_rbtree_index,z) ==mem_rbtree_index->nil || 
	    mem_rbtree_right(mem_rbtree_index,z)==mem_rbtree_index->nil ){
     y = z;
	   }else{
     	y = mem_rbtree_real_delete(mem_rbtree_index,root,z);
	 }
	 	 DEBUG(" Real Delete COLOR IS %d,find key is %ld;\n",y->color,y->rbtree_lkey);	

	 //x指向实际删除结点的子结点
	 if(!(mem_rbtree_left(mem_rbtree_index,z)==mem_rbtree_index->nil)) 
	 	{
	 		DEBUG("!(mem_rbtree_left(mem_rbtree_index,z)==mem_rbtree_index->nil);\n");	
	 	   x = mem_rbtree_left(mem_rbtree_index,y);
	 	 }
	 	else 
	 		{
	 		DEBUG(" x = mem_rbtree_right(mem_rbtree_index,y);\n");	
	 		 x = mem_rbtree_right(mem_rbtree_index,y);
	 	}
	 	mem_rbtree_set_parent(x , mem_rbtree_parent(mem_rbtree_index,y)); //删除结点y
	 	if( (mem_rbtree_parent(mem_rbtree_index,y)==mem_rbtree_index->nil )){
	 		DEBUG("mem_rbtree_parent(mem_rbtree_index,y)==mem_rbtree_index->nil;\n");	
	 		mem_rbtree_index->root = x;
	 	 }else{
	 	if ( y == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,y) ))	
	  {
	  	DEBUG("y->parent->left = x  ;\n");	
	  	mem_rbtree_set_left (mem_rbtree_parent(mem_rbtree_index,y)  , x);
	  }
	 	else
	 		{
	 		DEBUG("y->parent->right = x  ;\n");
	 		mem_rbtree_set_right(mem_rbtree_parent(mem_rbtree_index,y)  , x );		 
	 	  }
	 	}
	 		 if(y!=z){
	 		 	DEBUG("z->(rbtree_lkey,block_no,record_num) = (%ld,%ld,%ld);\n",z->rbtree_lkey,z->block_no,z->record_num);	
	 	    DEBUG("y->(rbtree_lkey,block_no,record_num) = (%ld,%ld,%ld);\n",y->rbtree_lkey,y->block_no,y->record_num);	
	 	    z->rbtree_lkey 	= y->rbtree_lkey;
	 	    z->block_no     = y->block_no;			   		 //right节点索引所在的块号
   			z->record_num  =  y->record_num; 		  		 //right节点索引所在的行号	

	 }

	 //如果删除的结点是黑色,违法了性质5,要进行删除调整
	 if(y->color==BLACK){
	 mem_rbtree_delete_fixup (mem_rbtree_index,mem_rbtree_index->root,x);
	 }
	
	struct record_t * record_ptr =(struct record_t *)((size_t)y - RECORD_HEAD_SIZE);
	int err;
	
	err = mem_mvcc_delete_record(mem_rbtree_index->heap_space,
																				record_ptr,
																				Tn               // 本事务ID
																				);
	
	//err = mem_table_del_record(mem_rbtree_index->heap_space , record_ptr);
	if(is_lock)RBTREE_UNLOCK(&(mem_rbtree_index->locker));
	
  DEBUG("mem_rbtree_delete() end;\n");	
	return err;
}


inline int mem_rbtree_mvcc_delete(mem_rbtree_index_t *mem_rbtree_index,
																mem_rbtree_entry_t *root,
																mem_rbtree_entry_t* z,	
																unsigned long long Tn,
																short is_lock
																)
{
	return __mem_rbtree_mvcc_delete(mem_rbtree_index,
																root,
															  z,	
																Tn,
																1
																);
}

#ifdef __cplusplus

}

#endif

#endif 