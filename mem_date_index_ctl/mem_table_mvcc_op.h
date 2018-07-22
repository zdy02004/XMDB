#ifndef MVCC_CTL
#define MVCC_CTL
#include "mem_transaction.h"
#define ROLLBACK_STACK_NOT_FOUND 						  50001

#ifdef __cplusplus

extern "C" {

#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//———————————————————— with_freelist ————————————————————
//此函数可以利用回收链表中的空闲空间，优先回收最晚删除的行
//_____________________with_freelist ————————————————————
//分配一个空闲记录行
inline int mem_table_try_allocate_record_with_freelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no,unsigned long long  Tn)
{
	if( NULL == mem_table )  return ALLOCATE_RECORD_ERR_TABLE_IS_NULL;
	DEBUG(" ----- Enter mem_table_try_allocate_record() ----- \n");
  /* 本段逻辑
	* 1. 优先根据高水位线,找空闲record
	* 2. 如果高水位线没有空闲空间,则从回收链表回收空间
	* 3. 回收链表也没有，则自动扩表
	*/
	int i = 0;
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
  
//  DEBUG("mem_block_temp is %0x\n",mem_block_temp);
  //遍历所有块,查找可以插入数据的内存块			
  short is_need_extern = 1;
 
	for(;i<mem_table->config.mem_block_used-1;++i)
	{
		mem_block_temp = mem_block_temp->next; 
	}
	
	if( 0!= (HIGH_LEVEL_TRYLOCK(&(mem_block_temp->high_level_lock))) )
		{
			//IMPORTANT_INFO("HIGH_LEVEL_TRYLOCK =0\n");
			return HIGH_LEVEL_TRY_LOCK;  //高水位线上锁
		}


	unsigned  long  high_level_temp = mem_block_temp->high_level;  
	if(mem_block_temp->space_start_addr + mem_block_temp->high_level* mem_table->record_size < mem_block_temp->space_end_addr - mem_table->record_size )
	{
		is_need_extern = 0;

   DEBUG("----- try to allocate record _with_freelist by high level -----\n");

 //根据高水位线获取最新插入位置    
//   DEBUG("mem_block_temp->high_level is %ld,mem_table->record_size is %ld;\n",high_level_temp,mem_table->record_size);
//   DEBUG("mem_block_temp->space_start_addr is %0x \n",mem_block_temp->space_start_addr);
  
	// 找到可用的记录位置
	(*record_ptr) = (struct record_t *) ( (char *)mem_block_temp->space_start_addr + high_level_temp * (mem_table->record_size) );
   
//   DEBUG("allocate_record_ptr is %0x;\n",*record_ptr);

	//返回块的逻辑号
	 (*block_no) = mem_block_temp->block_no;
//   DEBUG("allocate_record's block_no is %ld ;\n",(*block_no));
    ++(mem_block_temp->high_level);
//    DEBUG(" ----- try to allocate record by high level end -----\n");
	}
	
	//获得事务槽中的 scn
	int t_err= 0;
	long  scn ;
	if( 0!=(t_err = get_trans_scn( Tn, &scn) ) )
		{
			return t_err;
		}

	//没找到的内存块地址 > 块数据尾地址,则查找回收链表
  if (is_need_extern)
	{
		DEBUG(" ----- Try to find record _with_freelist in free_list -----\n");
		 	i=0;
    struct  mem_block_t * mem_block_temp2 = mem_table->config.mem_blocks_table;
  //遍历所有块,查找可以插入数据的内存块中的回收链表			
    for(;i<mem_table->config.mem_block_used;++i)
    {
	      	//空闲链表有数据，从链表头取一个地址插入		
    if( -1 != mem_block_temp2->mem_free_list.head ) 
       {
       	//空闲链表上锁
       	LIST_LOCK     (  &(mem_block_temp2->mem_free_list.list_lock)  );
       	//取得空闲链表的对应record的地址
       	(*record_ptr) =  (struct record_t *) ( (mem_block_temp2->mem_free_list.head) * mem_table->record_size + mem_block_temp->space_start_addr );
       	DEBUG("Find in Freelist, record_num %ld,record_ptr is %ld,last free pos is %ld\n",mem_block_temp->mem_free_list.head,*record_ptr,(*record_ptr)->last_free_pos);
       	high_level_temp = (*record_ptr)->record_num;////////////////////
       	// 不是本事务修改过的行，可以使用
       	if((*record_ptr)->scn < scn)
       	{
       	//空闲链表的head 为上一个空闲链表的位置
       	mem_block_temp2->mem_free_list.head = (*record_ptr)->last_free_pos;
       	//空闲链表解锁
       	LIST_UNLOCK   (  &(mem_block_temp2->mem_free_list.list_lock)  );
       	//返回块的逻辑号
       	*block_no = mem_block_temp2->block_no;
       	is_need_extern = 0;
       	//DEBUG("----- Free record space in free_list finded!  -----\n");
        break;
        }
        LIST_UNLOCK   (  &(mem_block_temp2->mem_free_list.list_lock)  );
       }	
       if(i!=mem_table->config.mem_block_used-1 )
       	{
       	mem_block_temp2 = mem_block_temp2->next;      //下一个块
         }
    }
   
 }
// 没有空闲空间和回收链表，就自动扩表
	//if (i == mem_table->config.mem_block_used-1)  
	if (is_need_extern)  
{ 
	DEBUG(" ----- Try to externd_table _with_freelist ----- \n");
	     	      //自动扩表
	     	      struct  mem_block_t * extern_mem_block;
	     	      int err = 0;
	     	      err =  mem_table_extend(mem_table,&extern_mem_block);
	     	      if(0 == err)
	     	      	{
	     	      			DEBUG("extern_mem_block->space_end_addr is %0x\n",extern_mem_block->space_end_addr);
	     	      		  DEBUG("extern_mem_block->space_start_addr is %0x\n",extern_mem_block->space_start_addr);
	     	      		  DEBUG("mem_table->record_size is %d\n",mem_table->record_size);
	     	      			//自动扩表成功,记录插入扩展块中的第一个位置,重新插入
	     	      			IMPORTANT_INFO("Externd_Block OK and Try Allocate Agian!\n");                   
                    HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁 	
	     	      			return TRY_LOCK;     	      		  	
	     	      	}
	     	      else if(TRY_LOCK== err)
	     	      	{
	     	      		  DEBUG(" TRY again! \n");
	     	      		  HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
	     	      			return TRY_LOCK;
	     	      	}
	     	      
	     	      else 
	     	      	{
	     	      		ERROR("MEM_TABLE_EXTEND_ERR err is %d\n",err);
	     	      		HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
	     	      		return  err;
	     	      	}
	     	      	
	DEBUG("----- Try to externd table_with_freelist end -----\n");	     	      	
}
//			DEBUG("----- init a record ! -----\n");
	   (*record_ptr)->record_num = high_level_temp;
     (*record_ptr)->is_used    =  1;
     (*record_ptr)->last_free_pos =  -1;
     (*record_ptr)->next_free_pos =  -1;
     (*record_ptr)->scn           =  0;
     (*record_ptr)->undo_record_ptr= 0;
     (*record_ptr)->data    =  (char *)(*record_ptr) + RECORD_HEAD_SIZE;  
     row_lock_init(&((*record_ptr)->row_lock)); //行锁初始化
     HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁

     DEBUG(" ----- Allocate_record_with_freelist >>> %0x , high_level is %ld ----- \n",*record_ptr,high_level_temp);
	   return 0;
	
}


//分配一个空闲记录行
inline int mem_table_allocate_record_with_freelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no,unsigned long long  Tn)
{
	if( NULL == mem_table )  return ALLOCATE_RECORD_ERR_TABLE_IS_NULL;
//  DEBUG("Enter mem_table_allocate_record();\n");	
  int err;
  int i = 0;
	do{
		++i;
		err= mem_table_try_allocate_record_with_freelist(mem_table ,/* out */ record_ptr,block_no,Tn);
		if(0!= err && TRY_LOCK != err && HIGH_LEVEL_TRY_LOCK !=err)
  	{
  		return err;
  	} 
  	if( 1 == mem_table->is_externing )
  		{
  			i = 0;
  			continue;
  		}
	}while(TRY_LOCK == err || HIGH_LEVEL_TRY_LOCK ==err );
	//if(0 == err)IMPORTANT_INFO("mem_table_allocate_record IS %ld\n",*record_ptr);
  DEBUG("mem_table_try_allocate_with_freelist END,record_ptr is %0x,record_num is %ld;\n",*record_ptr,(*record_ptr)->record_num);	
//	DEBUG("mem_table_allocate_record() ok;\n");	
	return 0;
	
}


//插入一个记录的数据
inline int mem_table_insert_record_with_freelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no, /* in */char *buf,unsigned long long  Tn)
{
	if( NULL == mem_table )  return INSERT_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == buf       )  return INSERT_RECORD_ERR_BUF_IS_NULL;	
	DEBUG("Enter mem_table_insert_record();\n");	
  int err;
  err= mem_table_allocate_record_with_freelist(mem_table ,/* out */ record_ptr,block_no,Tn);
  DEBUG("mem_table allocate a record,record_ptr is %0x ;\n",*record_ptr);	
	if(0!= err)
  {
  	return err;
  } 
  DEBUG("record_ptr->data is %0x ;\n",(*record_ptr)->data);	
	//redo_log .......
	
	row_wlock   (  &((*record_ptr)->row_lock) );
	memcpy      (  (*record_ptr)->data,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
	row_wunlock (  &((*record_ptr)->row_lock) );
	return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//———————————————————— with_rfreelist ————————————————————
//此函数可以利用回收链表中的空闲空间，优先回收最早删除的行
//_____________________with_rfreelist ————————————————————
//分配一个空闲记录行
inline int mem_table_try_allocate_record_with_rfreelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no,unsigned long long  Tn)
{
	if( NULL == mem_table )  return ALLOCATE_RECORD_ERR_TABLE_IS_NULL;
	DEBUG(" ----- Enter mem_table_try_allocate_record() ----- \n");
  /* 本段逻辑
	* 1. 优先根据高水位线,找空闲record
	* 2. 如果高水位线没有空闲空间,则从回收链表回收空间，优先回收最早删除的行
	* 3. 回收链表也没有，则自动扩表
	*/
	int i = 0;
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
  
//  DEBUG("mem_block_temp is %0x\n",mem_block_temp);
  //遍历所有块,查找可以插入数据的内存块			
  short is_need_extern = 1;
 
		for(;i<mem_table->config.mem_block_used-1;++i)
		{
			mem_block_temp = mem_block_temp->next; 
		}
		
		if( 0!= (HIGH_LEVEL_TRYLOCK(&(mem_block_temp->high_level_lock))) )
			{
				//IMPORTANT_INFO("HIGH_LEVEL_TRYLOCK =0\n");
				return HIGH_LEVEL_TRY_LOCK;  //高水位线上锁
			}


	unsigned  long  high_level_temp = mem_block_temp->high_level;  
	if(mem_block_temp->space_start_addr + mem_block_temp->high_level* mem_table->record_size < mem_block_temp->space_end_addr - mem_table->record_size )
		{
			is_need_extern = 0;
	
	   DEBUG("----- try to allocate record_with_rfreelist by high level -----\n");
	
	 //根据高水位线获取最新插入位置    
	//   DEBUG("mem_block_temp->high_level is %ld,mem_table->record_size is %ld;\n",high_level_temp,mem_table->record_size);
	//   DEBUG("mem_block_temp->space_start_addr is %0x \n",mem_block_temp->space_start_addr);
	  
		// 找到可用的记录位置
		(*record_ptr) = (struct record_t *) ( (char *)mem_block_temp->space_start_addr + high_level_temp * (mem_table->record_size) );
	   
	//   DEBUG("allocate_record_ptr is %0x;\n",*record_ptr);
	
		//返回块的逻辑号
		 (*block_no) = mem_block_temp->block_no;
	//   DEBUG("allocate_record's block_no is %ld ;\n",(*block_no));
	    ++(mem_block_temp->high_level);
	//    DEBUG(" ----- try to allocate record by high level end -----\n");
		}
	
	//获得事务槽中的 scn
	int t_err= 0;
	long  scn ;
	if( 0!=(t_err = get_trans_scn( Tn, &scn) ) )
		{
			return t_err;
		}

	//没找到的内存块地址 > 块数据尾地址,则查找回收链表
  if (is_need_extern)
	{
		DEBUG(" ----- Try to find record _with_rfreelist in free_list -----\n");
		 	i=0;
    struct  mem_block_t * mem_block_temp2 = mem_table->config.mem_blocks_table;
  //遍历所有块,查找可以插入数据的内存块中的回收链表			
    for(;i<mem_table->config.mem_block_used;++i)
    {
	      	//空闲链表有数据，从链表头取一个地址插入		
    if( -1 != mem_block_temp2->mem_free_list.tail ) 
       {
       	//空闲链表上锁
       	LIST_LOCK     (  &(mem_block_temp2->mem_free_list.list_lock)  );
       	//取得空闲链表的对应record的地址
       	long long  next_free_pos = mem_block_temp2->mem_free_list.tail ;
 
       	(*record_ptr) =  (struct record_t *) ( (next_free_pos) * mem_table->record_size + mem_block_temp->space_start_addr );
       	if( (*record_ptr)->scn < scn ) 
				{
       	DEBUG("Find in Freelist, record_num %ld,record_ptr is %ld,last free pos is %ld\n",mem_block_temp->mem_free_list.head,*record_ptr,(*record_ptr)->last_free_pos);
       	high_level_temp = (*record_ptr)->record_num;////////////////////
       	//空闲链表的head 为上一个空闲链表的位置
       	mem_block_temp2->mem_free_list.tail = (*record_ptr)->next_free_pos;
       	//空闲链表解锁
       	LIST_UNLOCK   (  &(mem_block_temp2->mem_free_list.list_lock)  );
       	//返回块的逻辑号
       	*block_no = mem_block_temp2->block_no;

       	is_need_extern = 0;
       	break;
       	}
       	LIST_UNLOCK   (  &(mem_block_temp2->mem_free_list.list_lock)  );

       	//DEBUG("----- Free record space in free_list finded!  -----\n");
      
       }	
       if(i!=mem_table->config.mem_block_used-1 )
       	{
       	mem_block_temp2 = mem_block_temp2->next;      //下一个块
         }
    }
   
 }
// 没有空闲空间和回收链表，就自动扩表
	//if (i == mem_table->config.mem_block_used-1)  
	if (is_need_extern)  
{ 
	DEBUG(" ----- Try to externd_table_with_rfreelist ----- \n");
	     	      //自动扩表
	     	      struct  mem_block_t * extern_mem_block;
	     	      int err = 0;
	     	      err =  mem_table_extend(mem_table,&extern_mem_block);
	     	      if(0 == err)
	     	      	{
	     	      			DEBUG("extern_mem_block->space_end_addr is %0x\n",extern_mem_block->space_end_addr);
	     	      		  DEBUG("extern_mem_block->space_start_addr is %0x\n",extern_mem_block->space_start_addr);
	     	      		  DEBUG("mem_table->record_size is %d\n",mem_table->record_size);
	     	      			//自动扩表成功,记录插入扩展块中的第一个位置,重新插入
	     	      			DEBUG("Externd_Block OK and Try Allocate Agian!\n");                   
                    HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁 	
	     	      			return TRY_LOCK;     	      		  	
	     	      	}
	     	      else if(TRY_LOCK== err)
	     	      	{
	     	      		  DEBUG(" TRY again! \n");
	     	      		  HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
	     	      			return TRY_LOCK;
	     	      	}
	     	      
	     	      else 
	     	      	{
	     	      		ERROR("MEM_TABLE_EXTEND_ERR err is %d\n",err);
	     	      		HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
	     	      		return  err;
	     	      	}
	     	      	
	DEBUG("----- Try to externd table_with_rfreelist end -----\n");	     	      	
}
//			DEBUG("----- init a record ! -----\n");
	   (*record_ptr)->record_num = high_level_temp;
     (*record_ptr)->is_used    =  1;
     (*record_ptr)->last_free_pos =  -1;
     (*record_ptr)->next_free_pos =  -1;
     (*record_ptr)->scn           =  0;
     (*record_ptr)->undo_record_ptr= 0;
     (*record_ptr)->data    =  (char *)(*record_ptr) + RECORD_HEAD_SIZE;  
     row_lock_init(&((*record_ptr)->row_lock)); //行锁初始化
     HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁

     DEBUG(" ----- Allocate_record_with_rfreelist >>> %0x , high_level is [%ld] ----- \n",*record_ptr,high_level_temp);
	   return 0;
	
}


//分配一个空闲记录行
inline int mem_table_allocate_record_with_rfreelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no,unsigned long long  Tn)
{
	if( NULL == mem_table )  return ALLOCATE_RECORD_ERR_TABLE_IS_NULL;
//  DEBUG("Enter mem_table_allocate_record();\n");	
  int err;
  int i = 0;
	do{
		++i;
		err= mem_table_try_allocate_record_with_rfreelist(mem_table ,/* out */ record_ptr,block_no,Tn);
		if(0!= err && TRY_LOCK != err && HIGH_LEVEL_TRY_LOCK !=err)
  	{
  		return err;
  	} 
  	if( 1 == mem_table->is_externing )
  		{
  			i = 0;
  			continue;
  		}
	}while(TRY_LOCK == err || HIGH_LEVEL_TRY_LOCK ==err );
	//if(0 == err)IMPORTANT_INFO("mem_table_allocate_record IS %ld\n",*record_ptr);
  DEBUG("mem_table_try_allocate_with_rfreelist END,record_ptr is %0x,record_num is %ld;\n",*record_ptr,(*record_ptr)->record_num);	
//	DEBUG("mem_table_allocate_record() ok;\n");	
	return 0;
	
}


//插入一个记录的数据
inline int mem_table_insert_record_with_rfreelist(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no, /* in */char *buf,unsigned long long  Tn)
{
	if( NULL == mem_table )  return INSERT_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == buf       )  return INSERT_RECORD_ERR_BUF_IS_NULL;	
  int err;
  err= mem_table_allocate_record_with_rfreelist(mem_table ,/* out */ record_ptr,block_no,Tn);
	if(0!= err)
  {
  	return err;
  } 
  //DEBUG("record_ptr->data is %0x ;\n",(*record_ptr)->data);	
	
	row_wlock   (  &((*record_ptr)->row_lock) );
	memcpy      (  (*record_ptr)->data,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
	row_wunlock (  &((*record_ptr)->row_lock) );
	return 0;
}




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
			
	int err;
			
	row_rlock   (  &(record_ptr->row_lock )                                            );

 	//记录未使用
	if( 0 == record_ptr->is_used )
	{
		row_runlock (  &(record_ptr->row_lock )    );
		ERROR("READ_RECORD_UNUSED\n");                                        
		return READ_RECORD_UNUSED;
	}
	
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
		{
			return err;
		}
		
	
    //如果读到可见版本号之后的行数据，要读最近的一次回滚段，否则不能读
	if( record_ptr->scn !=0  && transaction_manager.transaction_tables[Tn].view_scn < record_ptr->scn )
	{
		DEBUG("view_scn is %d\n",transaction_manager.transaction_tables[Tn].view_scn);
		DEBUG("record_ptr->scn is %d\n",record_ptr->scn  );
		
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
						DEBUG("ROLLBACK_STACK_NOT_FOUND\n");
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
  
  //获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
  
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
	if( scn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_DATA_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_DATA_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // redo 数据长度
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
  (*record_ptr)->scn = scn;
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
	int err;
	   //获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	 
	//事务未释放
	if( scn < record_ptr->scn )
	{
		if(is_lock)row_wunlock (  &(record_ptr->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n");
		return TRANS_NOT_FREE;
	}
	

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
  
  trans_entry.trans_no       			  = Tn;       							  //当前事物槽号
  trans_entry.redo_type             = OPT_DATA_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_DATA_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void*)((char *)(record_ptr)   + RECORD_HEAD_SIZE);	//原始数据起始地址
  trans_entry.redo_data_length      = mem_table->record_size - RECORD_HEAD_SIZE; // redo 数据长度
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
  record_ptr->scn = scn;
  
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
//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
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
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						=  mem_hash_index->config.index_no;//联系空间或连接空间的 no      							
  
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
  (*record_ptr)->scn = scn;
  if(is_lock)row_wunlock   (  &((*record_ptr)->row_lock) );
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
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	
if(err == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND || err == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND )
	{

 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( scn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_hash_index->config.index_no;//联系空间或连接空间的 no      							
  
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
  (*record_ptr)->scn = scn;
  if(is_lock)row_wunlock   (  &((*record_ptr)->row_lock) );
}
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
	
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	


 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( scn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_hash_index->config.index_no;;//联系空间或连接空间的 no      							
  
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
  (*record_ptr)->scn = scn;
  if(is_lock)row_wunlock   (  &((*record_ptr)->row_lock) );

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
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	

if(err == SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND || err == SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND )
{
 	if(is_lock)row_wlock   (  &((*record_ptr)->row_lock) );
	 		//事务未释放
	if( scn< (*record_ptr)->scn )
	{
		if(is_lock)row_wunlock (  &((*record_ptr)->row_lock )                                            );
		ERROR("TRANS_NOT_FREE\n"); 
		return TRANS_NOT_FREE;
	}
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			 = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_DELETE_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_DELETE_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_hash_index->config.index_no;//联系空间或连接空间的 no      							
  
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
  (*record_ptr)->scn = scn;
    if(is_lock)row_wunlock   (  &((*record_ptr)->row_lock) );

}
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


inline int __mem_hash_index_mvcc_update(mem_hash_index_t *mem_hash_index, 
												mem_hash_index_input_long *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn,
 												short is_lock
 												)
{
  int err = 0;
  if( 0 != (err = __mem_hash_index_mvcc_del_l(mem_hash_index ,in,inserted,Tn,is_lock ))){	
	err = __mem_hash_index_mvcc_insert_l(mem_hash_index, 
												  in,
 												  inserted,
 												  Tn,
 												  is_lock
 												);
 	}	
	return err;
} 		


inline int mem_hash_index_mvcc_update(mem_hash_index_t *mem_hash_index, 
												mem_hash_index_input_long *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn
 												)
{
  
	return __mem_hash_index_mvcc_update(mem_hash_index, 
												in,
 												inserted,
 												Tn,
 												1
 												);
} 		



inline int __mem_hash_index_mvcc_update_str(mem_hash_index_t *mem_hash_index, 
												mem_hash_index_input_str *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn,
 												short is_lock
 												)
{
  int err = 0;
  if( 0 != (err = __mem_hash_index_mvcc_del_str(mem_hash_index,in ,inserted,Tn,is_lock ))){	
	err = __mem_hash_index_mvcc_insert_str(mem_hash_index, 
												  in,
 												  inserted,
 												  Tn,
 												  is_lock
 												);
 	}	
	return err;
} 		


inline int mem_hash_index_mvcc_update_str(mem_hash_index_t *mem_hash_index_index, 
												mem_hash_index_input_str *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn
 												)
{
  
	return __mem_hash_index_mvcc_update_str(mem_hash_index_index, 
												in,
 												inserted,
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
   
   //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
  trans_entry.trans_no       			 = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_RBTREE_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_RBTREE_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(key));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_RBTREE_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_RBTREE_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 						= mem_rbtree_index->config.index_no;//联系空间或连接空间的 no      							

  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  int err;
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
   
   char buf[MEM_RBTREE_ENTRY_SIZE];
   
   
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
	  int err;
	  
  
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
  trans_entry.trans_no       			 = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_RBTREE_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_RBTREE_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(z));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_RBTREE_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_RBTREE_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 						= mem_rbtree_index->config.index_no;//联系空间或连接空间的 no      							
  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
	  	
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


//____________________________________________________
inline int mem_skiplist_mvcc_insert_one(
																	mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in  ,
 																	mem_skiplist_entry_t **last_insert_entry ,
 																	long              *last_insert_block_no,
 																	unsigned long long Tn ,
 																	short is_lock
 											 						)
{	
	DEBUG("Enter mem_skiplist_mvcc_insert_one()\n");
	//IMPORTANT_INFO("Enter mem_skiplist_insert_one()\n");
	//要插入的前继节点
	struct  record_t     * insert_node  = NULL;
	mem_skiplist_entry_t * insert_entry = NULL;
	//右指针 
	record_t 						 * right_record = NULL;;
	unsigned long          right_record_num;
	//新插入的节点 
	record_t 						 * new_record_ptr = NULL;
	mem_skiplist_entry_t * new_entry      = NULL;
	long                   new_block_no  ;
	int err = 0;
	
	//1.先分配一个新节点
  __mem_mvcc_insert_record(mem_skiplist_index->heap_space ,
              &new_record_ptr,
              &new_block_no  , /* in */
              (char *)in,
              Tn ,                       //事务ID
              is_lock
              );
          
  new_entry = (mem_skiplist_entry_t *)((char *)(new_record_ptr) + RECORD_HEAD_SIZE);
     
				//2.获得要插入的节点,重找一次，是为了防止更新底层节点时，上层被更新
				err = mem_skiplist_find_GE( mem_skiplist_index, 
 												prev, 
 												in,
 												&insert_entry
 											 );
   
 				if(err)return err;							 
 				insert_node = (struct record_t *)((char *)(insert_entry) - RECORD_HEAD_SIZE);
			 	DEBUG("insert_node -> record_num is %ld \n",insert_node->record_num);
 				
 				//3. 插入的时候锁前继节点，防止 前继节点被删除
 				//SKIPLIST_LOCK   (  &(insert_node->row_lock) ); 
				do{ //cas
						//3.1获得右指针节点
 						//do{
 						if(insert_node) SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
 						SKIPLIST_LOCK   (  &(insert_node->row_lock) ); 
								err = get_record(mem_skiplist_index->heap_space ,
														insert_entry->right_block_no,
														insert_entry->right_record_num,
														&right_record                  );
							  if(err){
							  	//SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
							  	return err;
							  }
						right_record_num = 	right_record->record_num;  
						//	}while( right_record->is_used == 0 );						
 						//3.2将新节点的右节点指向最新的位置 			    	
	 					new_entry->right_record_num = insert_entry->right_record_num;
	 					new_entry->right_block_no   = insert_entry->right_block_no;
						
						//3.3前继节点更新右节点为新节点
						//insert_entry->right_record_num = new_record_ptr->record_num;
				
				}while(!CAS(&(insert_entry->right_record_num),right_record_num,new_record_ptr->record_num ) );
						   insert_entry->right_block_no   = new_block_no;
				
					
				//4 解锁
 				SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
				if(new_block_no<0) ERROR("new_block_no<0 in insert_key = %ld,new_block_no is %d \n",in->lkey,new_block_no);

 	
 	*last_insert_entry    = new_entry;
 	*last_insert_block_no = new_block_no;
 	DEBUG("Enter mem_skiplist_mvcc_insert_one end\n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}



int mem_skiplist_mvcc_insert_help(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, int level,
 												mem_skiplist_entry_t *in,
 												struct  record_t ** last_insert_skiplist_entry ,
 												unsigned long long Tn ,
 												short is_lock
 												
 											 )
 {
 	DEBUG("Enter mem_skiplist_insert_help(),insert level is %d\n",level);	
 	DEBUG("Enter mem_skiplist_insert_help(),insert key is %ld\n",in->lkey);	
  //IMPORTANT_INFO("Enter mem_skiplist_insert_help(),insert key is %ld,level is %ld\n",in->lkey,level);	
	
	//1.插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;
	
	//if(NULL == prev)
	//{
	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	  DEBUG("prev_entry level is %d \n",level );	

	//}
	//else //有上层节点加速
	//  prev_entry = prev;
	
	DEBUG("prev_entry is %0x\n",prev_entry);	
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare Insert one %ld\n",in->lkey );								 	 					




	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Store Insert pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("$$$$$$$$$$$ pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	
  
 
 	if(err)return err;
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
 	  DEBUG("$$$$$$$$$$$ pre_array[%d],down_record  is %ld \n",i,prev_record->record_num );	
   }
   

   
 	if(err)return err;								 	
	}
	

	
	//3. 在所有层上的前继节点后面插入新数据
	//从底层往上层插入数据
	DEBUG("Begin Insert one %ld\n",in->lkey );								 	 					
 
  //IMPORTANT_INFO("Mem_skiplist_insert_help Real insert !\n");	

 
	mem_skiplist_entry_t 		*cur_insert_entry;
	struct record_t 				*cur_record      ;
	mem_skiplist_entry_t 		*pre_insert_entry;
	long    pre_insert_block_no;
	long  long            pre_insert_record_num;
	
	i = 1;
	for(;i< level+1; ++i)
	{
		DEBUG("Begin Insert one level %d\n",i );		
	  err = mem_skiplist_mvcc_insert_one( mem_skiplist_index, 
 															pre_array[i], 
 															in   ,
 															&cur_insert_entry,
 															&pre_insert_block_no,
 															Tn ,
 												      is_lock
 											 				);
 		if(err)return err;	
 		cur_record = (struct record_t *)( (char *)cur_insert_entry - RECORD_HEAD_SIZE);;	

 		// 给 down 节点赋值
 		if(1 !=i )
 		{	
 		DEBUG("%ld set down_record_num is %ld\n",cur_record->record_num,pre_insert_record_num);								 	 					
 		cur_insert_entry->down_record_num = pre_insert_record_num;
 		cur_insert_entry->down_block_no   = pre_insert_block_no;
 	  }
 	  pre_insert_record_num = cur_record->record_num;

	}
	 	DEBUG("Enter mem_skiplist_insert_help end\n");	
    //IMPORTANT_INFO("Enter mem_skiplist_insert_help end\n");	
	return 0;
}



int __mem_skiplist_mvcc_insert(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn ,
 												short is_lock
 												)
{
	int err = 0;
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	
	
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
   mem_trans_data_entry_t * undo_info_ptr;
   
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					  = mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );

  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
  
	int maxLevel = mem_skiplist_index->config.max_level;
	//int level    = mem_random_next(&(mem_skiplist_index->config.random) );
	
	do{
	err = mem_skiplist_mvcc_insert_help(mem_skiplist_index,
																	NULL,	mem_skiplist_randlevel(mem_skiplist_index) ,
																	in,
																	inserted,
																	Tn,
																	is_lock
																	);
	if(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED)ERROR("SKIPLIST_INDEX_ERR_GETDOWN_FAILED\n");	
	if(err == SKIPLIST_INDEX_ERR_GETGE_FAILED  )ERROR("SKIPLIST_INDEX_ERR_GETGE_FAILED\n");	
															
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
	return err;
} 										


int mem_skiplist_mvcc_insert(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn 
 												)		
 												{
return __mem_skiplist_mvcc_insert(mem_skiplist_index, 
	in,
	inserted,
	Tn ,
	1
	);
}


inline int mem_skiplist_mvcc_delete_one(mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in,
 																	unsigned long long Tn,
																	short is_lock 
 																	  )
{	
	DEBUG("===Enter mem_skiplist_mvcc_delete_one()===\n");
	//IMPORTANT_INFO("Enter mem_skiplist_insert_one()\n");
	//要删除的前继节点
	struct  record_t     * prev_delete_node  = NULL;
	mem_skiplist_entry_t * prev_delete_entry = NULL;
	

	//右指针 
	record_t 						 * right_record = NULL;;
	mem_skiplist_entry_t * right_entry;
	unsigned long          right_record_num;
	//要删除的节点
	struct  record_t     * delete_node  = NULL;
	mem_skiplist_entry_t * delete_entry = NULL;
	int err = 0;

				//1.获得要删除的节点的前继,找不到就返回 SKIPLIST_INDEX_SEARCH_NOT_FOUND
				err = mem_skiplist_find_EQ( mem_skiplist_index, 
 												prev, 
 												in,
 												&prev_delete_entry
 											 );
   
 				if(err)return err;							 
 				prev_delete_node = (struct record_t *)((char *)(prev_delete_entry) - RECORD_HEAD_SIZE);
			 	DEBUG("Finded delete_preve_node -> record_num is %ld \n",prev_delete_node->record_num);
 				
				
 						  
 				
				do{ //CAS
						//2获得右指针节点
 						//do{
 						if(right_record)SKIPLIST_UNLOCK (  &(right_record->row_lock   ) ); 
								err = get_record(mem_skiplist_index->heap_space ,
														prev_delete_entry->right_block_no,
														prev_delete_entry->right_record_num,
														&right_record                  );
							  if(err){
							  	return err;
							  }
							//}while( right_record->is_used == 0 );	
						
						//3.删除的时候，锁待删除节点，防止被后续的 表 insert 修改
 				    SKIPLIST_LOCK   (  &(right_record->row_lock) ); 	
							
						right_record_num = right_record->record_num;
						right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);			
 						   		
						//2.2前继节点更新右节点为后后节点
						//prev_delete_entry->right_record_num = right_entry->right_record_num;
					}while( !CAS(&(prev_delete_entry->right_record_num),right_record_num,right_entry->right_record_num) );
						prev_delete_entry->right_block_no   = right_entry->right_block_no;
						
				//4 解锁
 				 SKIPLIST_UNLOCK (  &(right_record->row_lock   ) ); 
 				
 				//5 将需要删除的节点置失效
 				__mem_mvcc_delete_record(mem_skiplist_index->heap_space ,right_record,Tn,is_lock);
	      //right_entry->right_record_num = right_record->record_num;
	      
 	DEBUG("===End mem_skiplist_mvcc_delete_one()=== \n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}


inline int mem_skiplist_mvcc_delete_help(mem_skiplist_index_t *mem_skiplist_index, 
																			mem_skiplist_entry_t *prev, 
																			int level ,
																			mem_skiplist_entry_t *in,
																			unsigned long long Tn,
																			short is_lock 
																			 )
 {
 	DEBUG("Enter mem_skiplist_mvcc_delete_help(),delete level is %d\n",level);	
 	DEBUG("Enter mem_skiplist_mvcc_delete_help(),delete key is %ld\n",in->lkey);	
  //IMPORTANT_INFO("Enter mem_skiplist_delete_help(),delete key is %ld,level is %ld\n",in->lkey,level);	
	
	//1.插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;
	
	//if(NULL == prev)
	//{
	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	  DEBUG("prev_entry level is %d \n",level );	

	//}
	//else //有上层节点加速
	//  prev_entry = prev;
	
	DEBUG("prev_entry is %0x\n",prev_entry);	
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare delete one %ld\n",in->lkey );								 	 					

	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Store Delete pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("$$$$$$$$$$$ pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	
 
 	if(err)return err;
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
 	  DEBUG("$$$$$$$$$$$ pre_array[%d],down_record  is %ld \n",i,prev_record->record_num );	
   }

 	if(err)return err;								 	
	}
	
	//3. 在所有层上的前继节点后面删除数据
	//从底层往上层插入数据
	DEBUG("Begin delete one key = %ld\n",in->lkey );								 	 					
 
  //IMPORTANT_INFO("Mem_skiplist_delete_help Real delete !\n");	
	//从下往上删
	i = 1;
	for(;i > max_level+1; --i)
	{
		DEBUG("Begin delete one level %d\n",i );		
	  err = mem_skiplist_mvcc_delete_one( mem_skiplist_index, 
 															pre_array[i], 
 															in,
 															Tn,
 															is_lock
 											 				);
 		// 没找到就不删本层的节点									 				
 		if(err == SKIPLIST_INDEX_SEARCH_NOT_FOUND){
 			DEBUG("SKIPLIST_INDEX_SEARCH_NOT_FOUND\n");
 			continue;
 		}
 		if(err)return err;	
	}
	 	DEBUG("End mem_skiplist_mvcc_delete_help()\n");	
    //IMPORTANT_INFO("Enter mem_skiplist_delete_help end\n");	
	return 0;
}

inline int __mem_skiplist_mvcc_delete(mem_skiplist_index_t *mem_skiplist_index ,mem_skiplist_entry_t *in,unsigned long long Tn,short is_lock )
{
	int err = 0;
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	
	//构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_DELETE;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_DELETE;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in) );                   ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					= mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );

  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
	
	
	do{
	err = mem_skiplist_mvcc_delete_help( mem_skiplist_index,NULL,0,in,Tn,is_lock	);
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
  return err;
}

inline int mem_skiplist_mvcc_delete(mem_skiplist_index_t *mem_skiplist_index ,
															 mem_skiplist_entry_t *in,
															 unsigned long long Tn
															 )
{
	return __mem_skiplist_mvcc_delete(mem_skiplist_index ,
															 in,
															 Tn,
															 1
															 );
}

inline int __mem_skiplist_mvcc_update(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn,
 												short is_lock
 												)
{
  int err = 0;
  if( 0 != (err = __mem_skiplist_mvcc_delete(mem_skiplist_index ,in,Tn,is_lock ))){	
	err = __mem_skiplist_mvcc_insert(mem_skiplist_index, 
												  in,
 												  inserted,
 												  Tn,
 												  is_lock
 												);
 	}	
	return err;
} 		


inline int mem_skiplist_mvcc_update(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn
 												)
{
  
	return __mem_skiplist_mvcc_update(mem_skiplist_index, 
												in,
 												inserted,
 												Tn,
 												1
 												);
} 		

//////////////////////////////////////////////////////////


inline int mem_skiplist_mvcc_insert_one_str(
																	mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in  ,
 																	mem_skiplist_entry_t **last_insert_entry ,
 																	long              *last_insert_block_no,
 																	unsigned long long Tn ,
 																	short is_lock
 											 						)
{	
	DEBUG("Enter mem_skiplist_mvcc_insert_one_str()\n");
	//IMPORTANT_INFO("Enter mem_skiplist_mvcc_insert_one_str()\n");
	//要插入的前继节点
	struct  record_t     * insert_node  = NULL;
	mem_skiplist_entry_t * insert_entry = NULL;
	//右指针 
	record_t 						 * right_record = NULL;;
	unsigned long          right_record_num;
	//新插入的节点 
	record_t 						 * new_record_ptr = NULL;
	mem_skiplist_entry_t * new_entry      = NULL;
	long                   new_block_no  ;
	int err = 0;
	
	//1.先分配一个新节点
  __mem_mvcc_insert_record(mem_skiplist_index->heap_space ,
              &new_record_ptr,
              &new_block_no  , /* in */
              (char *)in,
              Tn ,                       //事务ID
              is_lock
              );
          
  new_entry = (mem_skiplist_entry_t *)((char *)(new_record_ptr) + RECORD_HEAD_SIZE);
     
				//2.获得要插入的节点,重找一次，是为了防止更新底层节点时，上层被更新
				err = mem_skiplist_find_GE_str( mem_skiplist_index, 
 												prev, 
 												in,
 												&insert_entry
 											 );
   
 				if(err)return err;							 
 				insert_node = (struct record_t *)((char *)(insert_entry) - RECORD_HEAD_SIZE);
			 	DEBUG("insert_node -> record_num is %ld \n",insert_node->record_num);
 				
 				//3. 插入的时候锁前继节点，防止 前继节点被删除
 				//SKIPLIST_LOCK   (  &(insert_node->row_lock) ); 
				do{ //cas
						//3.1获得右指针节点
 						//do{
 						if(insert_node) SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
 						SKIPLIST_LOCK   (  &(insert_node->row_lock) ); 
								err = get_record(mem_skiplist_index->heap_space ,
														insert_entry->right_block_no,
														insert_entry->right_record_num,
														&right_record                  );
							  if(err){
							  	//SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
							  	return err;
							  }
						right_record_num = 	right_record->record_num;  
						//	}while( right_record->is_used == 0 );						
 						//3.2将新节点的右节点指向最新的位置 			    	
	 					new_entry->right_record_num = insert_entry->right_record_num;
	 					new_entry->right_block_no   = insert_entry->right_block_no;
						
						//3.3前继节点更新右节点为新节点
						//insert_entry->right_record_num = new_record_ptr->record_num;
				
				}while(!CAS(&(insert_entry->right_record_num),right_record_num,new_record_ptr->record_num ) );
						   insert_entry->right_block_no   = new_block_no;
				
					
				//4 解锁
 				SKIPLIST_UNLOCK (  &(insert_node->row_lock   ) ); 
				if(new_block_no<0) ERROR("new_block_no<0 in insert_key = %ld,new_block_no is %d \n",in->ckey,new_block_no);

 	
 	*last_insert_entry    = new_entry;
 	*last_insert_block_no = new_block_no;
 	DEBUG("Enter mem_skiplist_mvcc_insert_one_str end\n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}



int mem_skiplist_mvcc_insert_help_str(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, int level,
 												mem_skiplist_entry_t *in,
 												struct  record_t ** last_insert_skiplist_entry ,
 												unsigned long long Tn ,
 												short is_lock
 												
 											 )
 {
 	DEBUG("Enter mem_skiplist_mvcc_insert_help_str(),insert level is %d\n",level);	
 	DEBUG("Enter mem_skiplist_mvcc_insert_help_str(),insert key is %s\n",in->ckey);	
  //IMPORTANT_INFO("Enter mem_skiplist_insert_help(),insert key is %s,level is %ld\n",in->ckey,level);	
	
	//1.插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;
	
	//if(NULL == prev)
	//{
	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	  DEBUG("prev_entry level is %d \n",level );	

	//}
	//else //有上层节点加速
	//  prev_entry = prev;
	
	DEBUG("prev_entry is %0x\n",prev_entry);	
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare Insert one %s\n",in->ckey );								 	 					




	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Store Insert pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE_str( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("$$$$$$$$$$$ pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	
  
 
 	if(err)return err;
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
 	  DEBUG("$$$$$$$$$$$ pre_array[%d],down_record  is %ld \n",i,prev_record->record_num );	
   }
   

   
 	if(err)return err;								 	
	}
	

	
	//3. 在所有层上的前继节点后面插入新数据
	//从底层往上层插入数据
	DEBUG("Begin Insert one %s\n",in->ckey );								 	 					
 
  //IMPORTANT_INFO("Mem_skiplist_insert_help Real insert !\n");	

 
	mem_skiplist_entry_t 		*cur_insert_entry;
	struct record_t 				*cur_record      ;
	mem_skiplist_entry_t 		*pre_insert_entry;
	long    pre_insert_block_no;
	long  long            pre_insert_record_num;
	
	i = 1;
	for(;i< level+1; ++i)
	{
		DEBUG("Begin Insert one level %d\n",i );		
	  err = mem_skiplist_mvcc_insert_one_str( mem_skiplist_index, 
 															pre_array[i], 
 															in   ,
 															&cur_insert_entry,
 															&pre_insert_block_no,
 															Tn ,
 												      is_lock
 											 				);
 		if(err)return err;	
 		cur_record = (struct record_t *)( (char *)cur_insert_entry - RECORD_HEAD_SIZE);;	

 		// 给 down 节点赋值
 		if(1 !=i )
 		{	
 		DEBUG("%ld set down_record_num is %ld\n",cur_record->record_num,pre_insert_record_num);								 	 					
 		cur_insert_entry->down_record_num = pre_insert_record_num;
 		cur_insert_entry->down_block_no   = pre_insert_block_no;
 	  }
 	  pre_insert_record_num = cur_record->record_num;

	}
	 	DEBUG("Enter mem_skiplist_insert_help end\n");	
    //IMPORTANT_INFO("Enter mem_skiplist_insert_help end\n");	
	return 0;
}



int __mem_skiplist_mvcc_insert_str(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn ,
 												short is_lock
 												)
{
	int err = 0;
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	
	
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
   
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_INSERT_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_INSERT_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					  = mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );

  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
  
	int maxLevel = mem_skiplist_index->config.max_level;
	//int level    = mem_random_next(&(mem_skiplist_index->config.random) );
	
	do{
	err = mem_skiplist_mvcc_insert_help_str(mem_skiplist_index,
																	NULL,	mem_skiplist_randlevel(mem_skiplist_index) ,
																	in,
																	inserted,
																	Tn,
																	is_lock
																	);
	if(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED)ERROR("SKIPLIST_INDEX_ERR_GETDOWN_FAILED\n");	
	if(err == SKIPLIST_INDEX_ERR_GETGE_FAILED  )ERROR("SKIPLIST_INDEX_ERR_GETGE_FAILED\n");	
															
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
	return err;
} 										


int mem_skiplist_mvcc_insert_str(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn 
 												)		
 												{
return __mem_skiplist_mvcc_insert_str(mem_skiplist_index, 
	in,
	inserted,
	Tn ,
	1
	);
}


inline int mem_skiplist_mvcc_delete_one_str(mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in,
 																	unsigned long long Tn,
																	short is_lock 
 																	  )
{	
	DEBUG("===Enter mem_skiplist_mvcc_delete_one_str()===\n");
	//IMPORTANT_INFO("Enter mem_skiplist_insert_one()\n");
	//要删除的前继节点
	struct  record_t     * prev_delete_node  = NULL;
	mem_skiplist_entry_t * prev_delete_entry = NULL;
	

	//右指针 
	record_t 						 * right_record = NULL;;
	mem_skiplist_entry_t * right_entry;
	unsigned long          right_record_num;
	//要删除的节点
	struct  record_t     * delete_node  = NULL;
	mem_skiplist_entry_t * delete_entry = NULL;
	int err = 0;

				//1.获得要删除的节点的前继,找不到就返回 SKIPLIST_INDEX_SEARCH_NOT_FOUND
				err = mem_skiplist_find_EQ_str( mem_skiplist_index, 
 												prev, 
 												in,
 												&prev_delete_entry
 											 );
   
 				if(err)return err;							 
 				prev_delete_node = (struct record_t *)((char *)(prev_delete_entry) - RECORD_HEAD_SIZE);
			 	DEBUG("Finded delete_preve_node -> record_num is %ld \n",prev_delete_node->record_num);
 				
				
 						  
 				
				do{ //CAS
						//2获得右指针节点
 						//do{
 						if(right_record)SKIPLIST_UNLOCK (  &(right_record->row_lock   ) ); 
								err = get_record(mem_skiplist_index->heap_space ,
														prev_delete_entry->right_block_no,
														prev_delete_entry->right_record_num,
														&right_record                  );
							  if(err){
							  	return err;
							  }
							//}while( right_record->is_used == 0 );	
						
						//3.删除的时候，锁待删除节点，防止被后续的 表 insert 修改
 				    SKIPLIST_LOCK   (  &(right_record->row_lock) ); 	
							
						right_record_num = right_record->record_num;
						right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);			
 						   		
						//2.2前继节点更新右节点为后后节点
						//prev_delete_entry->right_record_num = right_entry->right_record_num;
					}while( !CAS(&(prev_delete_entry->right_record_num),right_record_num,right_entry->right_record_num) );
						prev_delete_entry->right_block_no   = right_entry->right_block_no;
						
				//4 解锁
 				 SKIPLIST_UNLOCK (  &(right_record->row_lock   ) ); 
 				
 				//5 将需要删除的节点置失效
 				__mem_mvcc_delete_record(mem_skiplist_index->heap_space ,right_record,Tn,is_lock);
	      //right_entry->right_record_num = right_record->record_num;
	      
 	DEBUG("===End mem_skiplist_mvcc_delete_one_str()=== \n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}


inline int mem_skiplist_mvcc_delete_help_str(mem_skiplist_index_t *mem_skiplist_index, 
																			mem_skiplist_entry_t *prev, 
																			int level ,
																			mem_skiplist_entry_t *in,
																			unsigned long long Tn,
																			short is_lock 
																			 )
 {
 	DEBUG("Enter mem_skiplist_mvcc_delete_help_str(),delete level is %d\n",level);	
 	DEBUG("Enter mem_skiplist_mvcc_delete_help_str(),delete key is %s\n",in->ckey);	
  //IMPORTANT_INFO("Enter mem_skiplist_delete_help(),delete key is %ld,level is %ld\n",in->ckey,level);	
	
	//1.插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	struct record_t *      prev_record;
	int err = 0;
	int max_level = mem_skiplist_index->config.max_level;
	
	//if(NULL == prev)
	//{
	//	   //获得当层头节点
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	  DEBUG("prev_entry level is %d \n",level );	

	//}
	//else //有上层节点加速
	//  prev_entry = prev;
	
	DEBUG("prev_entry is %0x\n",prev_entry);	
	
	//2. 存储所有层上的前继节点指针
	DEBUG("Prepare delete one %s\n",in->ckey );								 	 					

	mem_skiplist_entry_t * pre_array[max_level+1];//从1开始计数
	int i = max_level;
	for(;i> 0; --i)
	{
	prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);
	DEBUG("Store Delete pre_array %d,prev_record->record_num is %ld \n",i,prev_record->record_num);	

	//2.1 将每一层的前继节点存入 pre_array
	err =	mem_skiplist_find_GE_str( mem_skiplist_index, 
 												  prev_entry, 
 												  in,
 												&(pre_array[i])  
 											  );
  DEBUG("$$$$$$$$$$$ pre_array[%d],prev_record  is %ld \n",i,prev_record->record_num );	
 
 	if(err)return err;
 	//2.2 将 prev_entry 更新为他的后继节点
 	if(i>1){
 		err = mem_skiplist_get_down( mem_skiplist_index, 
 												 pre_array[i], 
 												 &prev_entry 
 											 );	
 											 
 		prev_record = (struct record_t *)( (char *)prev_entry - RECORD_HEAD_SIZE);									 
 	  DEBUG("$$$$$$$$$$$ pre_array[%d],down_record  is %ld \n",i,prev_record->record_num );	
   }

 	if(err)return err;								 	
	}
	
	//3. 在所有层上的前继节点后面删除数据
	//从底层往上层插入数据
	DEBUG("Begin delete one key = %s\n",in->ckey );								 	 					
 
  //IMPORTANT_INFO("Mem_skiplist_delete_help Real delete !\n");	
	//从下往上删
	i = 1;
	for(;i > max_level+1; --i)
	{
		DEBUG("Begin delete one level %d\n",i );		
	  err = mem_skiplist_mvcc_delete_one_str( mem_skiplist_index, 
 															pre_array[i], 
 															in,
 															Tn,
 															is_lock
 											 				);
 		// 没找到就不删本层的节点									 				
 		if(err == SKIPLIST_INDEX_SEARCH_NOT_FOUND){
 			DEBUG("SKIPLIST_INDEX_SEARCH_NOT_FOUND\n");
 			continue;
 		}
 		if(err)return err;	
	}
	 	DEBUG("End mem_skiplist_mvcc_delete_help_str()\n");	
    //IMPORTANT_INFO("Enter mem_skiplist_delete_help end\n");	
	return 0;
}

inline int __mem_skiplist_mvcc_delete_str(mem_skiplist_index_t *mem_skiplist_index ,mem_skiplist_entry_t *in,unsigned long long Tn,short is_lock )
{
	int err = 0;
	//获得事务槽中的 scn
	long  scn ;
	if( 0!=(err = get_trans_scn( Tn, &scn) ) )
	{
		return err;
	}
	
	//构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_DELETE_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_DELETE_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in) );                   ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					= mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );

  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
	
	
	do{
	err = mem_skiplist_mvcc_delete_help_str( mem_skiplist_index,NULL,0,in,Tn,is_lock	);
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
  return err;
}

inline int mem_skiplist_mvcc_delete_str(mem_skiplist_index_t *mem_skiplist_index ,
															 mem_skiplist_entry_t *in,
															 unsigned long long Tn
															 )
{
	return __mem_skiplist_mvcc_delete_str(mem_skiplist_index ,
															 in,
															 Tn,
															 1
															 );
}

inline int __mem_skiplist_mvcc_update_str(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn,
 												short is_lock
 												)
{
  int err = 0;
  if( 0 != (err = __mem_skiplist_mvcc_delete_str(mem_skiplist_index ,in,Tn,is_lock ))){	
	err = __mem_skiplist_mvcc_insert_str(mem_skiplist_index, 
												  in,
 												  inserted,
 												  Tn,
 												  is_lock
 												);
 	}	
	return err;
} 		


inline int mem_skiplist_mvcc_update_str(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn
 												)
{
  
	return __mem_skiplist_mvcc_update_str(mem_skiplist_index, 
												in,
 												inserted,
 												Tn,
 												1
 												);
} 		

/////下面的代码，主要用于 ceate_index_online 时 调用

//支持事务的mvcc插入一个记录的数据
inline int mem_hash_index_mvcc_insert_l_scn(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_long * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn,                       //事务ID
                          unsigned long long scn                       //事务ID
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

 	row_wlock   (  &((*record_ptr)->row_lock) );

	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						=  mem_hash_index->config.index_no;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void ** )(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );

  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **)(&mem_block_ptr));
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
    //修改为本次的事务ID
  (*record_ptr)->scn = scn;
  //保留上一次回滚栈信息
  undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
   // 指向回滚信息
  (*record_ptr)->undo_info_ptr = undo_info_ptr;
  row_wunlock   (  &((*record_ptr)->row_lock) );
	return 0;
}

inline int mem_hash_index_mvcc_insert_str_scn(                        
                        /* in */ struct mem_hash_index_t * mem_hash_index ,
                        				 struct mem_hash_index_input_str * input,
                        /* out */struct    record_t   **  record_ptr,
                          unsigned long long Tn,                       //事务ID
                          unsigned long long scn
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
	


 	row_wlock   (  &((*record_ptr)->row_lock) );
	//回滚信息
  mem_trans_data_entry_t * undo_info_ptr;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_HASH_INSERT_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_HASH_INSERT_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(*record_ptr) + RECORD_HEAD_SIZE)                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = MEM_HASH_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = MEM_HASH_ENTRY_SIZE; // undo 数据长度	
  trans_entry.block_no              = block_no;
  trans_entry.record_num            = (*record_ptr)->record_num; 
  trans_entry.object_no 						= mem_hash_index->config.index_no;;//联系空间或连接空间的 no      							
  
  mem_table_t * mem_table;
  get_table_no_addr(mem_table_no,(void **)(&mem_table));
  strcpy(trans_entry.name,mem_table->config.table_name );
  
  mem_block_t * mem_block_ptr;
  get_block_no_addr(block_no,(void **) mem_block_ptr);
  strcpy(trans_entry.block_name,mem_block_ptr->file_name );

  
  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
    //修改为本次的事务ID
  (*record_ptr)->scn = scn;
  
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
  
    //保留上一次回滚栈信息
    undo_info_ptr->next = (mem_trans_data_entry_t*)((*record_ptr)->undo_info_ptr);
     // 指向回滚信息
    (*record_ptr)->undo_info_ptr = undo_info_ptr;

  row_wunlock   (  &((*record_ptr)->row_lock) );

	return 0;
}


int mem_skiplist_mvcc_insert_scn(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn ,
 												unsigned long long scn 
 												)
{
	int err = 0;
	
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
   mem_trans_data_entry_t * undo_info_ptr;
   
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_INSERT;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_INSERT;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					  = mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

	int maxLevel = mem_skiplist_index->config.max_level;
	//int level    = mem_random_next(&(mem_skiplist_index->config.random) );
	
	do{
	err = mem_skiplist_mvcc_insert_help(mem_skiplist_index,
																	NULL,	mem_skiplist_randlevel(mem_skiplist_index) ,
																	in,
																	inserted,
																	Tn,
																	1
																	);
	if(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED)ERROR("SKIPLIST_INDEX_ERR_GETDOWN_FAILED\n");	
	if(err == SKIPLIST_INDEX_ERR_GETGE_FAILED  )ERROR("SKIPLIST_INDEX_ERR_GETGE_FAILED\n");	
															
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
	if(*inserted)(*inserted)->scn = scn;
	  DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
  if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
 
	return err;
} 										

int mem_skiplist_mvcc_insert_str_scn(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted,
 												unsigned long long Tn ,
 												unsigned long long scn
 												)
{
	int err = 0;
  //构造一个事务
  mem_transaction_entry_t  trans_entry ;
  mem_trans_data_entry_t * undo_info_ptr;
   
  trans_entry.trans_no       			  = Tn;       							//当前事物槽号
  trans_entry.redo_type             = OPT_INDEX_SKIPLIST_INSERT_STR;				//redo 操作类型
  trans_entry.undo_type						  = OPT_INDEX_SKIPLIST_INSERT_STR;				//undo 操作类型 insert update delete truncate index_op
  trans_entry.ori_data_start        = (void *)((char *)(in));                    ;	//原始数据起始地址
  trans_entry.redo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // redo 数据长度
  trans_entry.undo_data_length      = FIELD_SKIPLIST_ENTRY_SIZE; // undo 数据长度	
  trans_entry.object_no 					  = mem_skiplist_index->config.index_no;//联系空间或连接空间的 no      							

	int maxLevel = mem_skiplist_index->config.max_level;
	//int level    = mem_random_next(&(mem_skiplist_index->config.random) );
	
	do{
	err = mem_skiplist_mvcc_insert_help_str(mem_skiplist_index,
																	NULL,	mem_skiplist_randlevel(mem_skiplist_index) ,
																	in,
																	inserted,
																	Tn,
																	1
																	);
	if(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED)ERROR("SKIPLIST_INDEX_ERR_GETDOWN_FAILED\n");	
	if(err == SKIPLIST_INDEX_ERR_GETGE_FAILED  )ERROR("SKIPLIST_INDEX_ERR_GETGE_FAILED\n");	
															
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
	if(*inserted)(*inserted)->scn = scn;
	DEBUG("mem_transaction_entry_t ori_data_start is %0x \n",trans_entry.ori_data_start );
	if(0!=(err=fill_trans_entry_to_write(&trans_entry,&undo_info_ptr)))ERROR("fill_trans_entry_to_write failed,trans_no is %d\n",err);
	return err;
} 				


#ifdef __cplusplus

}

#endif

#endif 
