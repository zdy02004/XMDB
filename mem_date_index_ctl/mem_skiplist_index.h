
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#ifdef __cplusplus

extern "C" {

#endif
#include"mem_table_ctl.h"
#include"mem_index_no_manager.h"
#include "../util/util_random.h"


#define CREATE_SKIPLIST_INDEX_ERR_TABLE_PTR      38001
#define CREATE_SKIPLIST_INDEX_ERR_NULL_CONFIG    38002
#define CREATE_SKIPLIST_INDEX_ERR_NO_NAME        38003
#define CREATE_SKIPLIST_INDEX_ERR_NAME_TOO_LONG  38004
#define CREATE_SKIPLIST_INDEX_ERR_NO_TABLE_NO    38005
#define OPEN_MEM_SKIPLIST_ERR_NULL_SKIPLIST_PTR  38006
#define CLOSE_MEM_SKIPLIST_INDEX_ERR_NULL_PTR    38007
#define SKIPLIST_INDEX_ERR_NULL_INDEX_PRT        38008
#define SKIPLIST_INDEX_ERR_NULL_KEY_PRT          38009
#define SKIPLIST_INDEX_ERR_BIG_LEVEL             38010
#define SKIPLIST_INDEX_ERR_DELETE_NOT_FOUND      38011
#define SKIPLIST_INDEX_SEARCH_NOT_FOUND					 38012
#define SKIPLIST_INDEX_ERR_GETDOWN_FAILED        38013
#define SKIPLIST_INDEX_ERR_GETGE_FAILED          38014

//暂时用写锁锁来实现跳表索引锁
#define SKIPLIST_LOCK_T             rwlock_t

//#define SKIPLIST_TRYLOCK(x)         pthread_spin_trylock(x) 
#define SKIPLIST_LOCK(x)            rwlock_wlock(x);  
#define SKIPLIST_UNLOCK(x)          rwlock_wunlock(x);  
#define SKIPLIST_RLOCK(x)           rwlock_rlock(x);
#define SKIPLIST_RUNLOCK(x)         rwlock_runlock(x);   
#define SKIPLIST_LOCK_INIT(x)       rwlock_init((x));



//内存 rbtree 索引描述符_适用于范围快速索引
typedef struct  mem_skiplist_index_config_t
{
long                        index_no;                     //索引号
long                        owner_table_no;               //所属表号
int               *         field_order;                  //联合索引的顺序号
int                         field_num;                    //联合索引关联字段的的个数
char                        index_name[128];              //索引名
long                        owner_id;                     //该索引所属用户的ID
unsigned  long              heap_block_size;              //连续空间块配置大小
int                         max_level;                    //最大层数 //注意 本代码 level 是从 1 开始的
struct mem_random_t         random;
} __attribute__ ((packed, aligned (64))) mem_skiplist_index_config_t;

#define MEM_SKIPLIST_CONFIG_SIZE  sizeof(mem_skiplist_index_config_t)


//内存skiplist索引描述符_适用于范围索引
typedef struct  mem_skiplist_index_t
{
struct mem_skiplist_index_config_t   config;                       //hash 配置
struct mem_table_t                   *heap_space;                	 //堆空间
mem_skiplist_entry_t                 *root;                        //根节点
SKIPLIST_LOCK_T                      locker;                       //锁
struct  mem_skiplist_entry_t				 * nil;                         //空节点
} __attribute__ ((packed, aligned (64))) mem_skiplist_index_t;


#define MEM_SKIPLIST_INDEX_SIZE (sizeof(struct mem_skiplist_index_t))


//建SKIPLIST索引
inline int mem_skiplist_create(
														 mem_skiplist_index_t         **  mem_skiplist_index,	
                             struct mem_table_t           *  mem_table,// 原表
                             struct mem_skiplist_index_config_t  *  mem_index_config
                             )
 {
  if(NULL == mem_table                          )  return CREATE_SKIPLIST_INDEX_ERR_TABLE_PTR;
	if(NULL == mem_index_config                   )  return CREATE_SKIPLIST_INDEX_ERR_NULL_CONFIG;
	if(NULL == mem_index_config->index_name       )  return CREATE_SKIPLIST_INDEX_ERR_NO_NAME;
	if(strlen (mem_index_config->index_name)>=120 )  return CREATE_SKIPLIST_INDEX_ERR_NAME_TOO_LONG;
  if(mem_index_config->owner_table_no<=0        )  return CREATE_SKIPLIST_INDEX_ERR_NO_TABLE_NO;
  int len = strlen(mem_index_config->index_name);
  DEBUG("Enter mem_skiplist_create() \n");
  DEBUG("Max level is %d \n",mem_index_config->max_level);
  	
  		//1.构造 heap_space 的 block
     int i=0;
	   struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;

        //生成块描述符
       mem_block_t *mb = (mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	     DEBUG("create mem_skiplist block %0x\n",*mb);
	 
			 
			 char tem_buf[256]={0};
       strcpy(tem_buf,mem_index_config->index_name);
       strcat(tem_buf,"_skip.dat\0");
       
			 mem_block_config( mb  ,mem_index_config->heap_block_size , tem_buf );
			 
			 //2. 构造 fields_table
			 struct field_t *_fields_table   = (struct field_t *) malloc(FIELD_SIZE);
		   _fields_table[0].field_type     = FIELD_TYPE_SKIPLIST_ENTRY;

			 // 3.构造 mem_table_config_t
		  struct mem_table_config_t * heap_space_config = (struct mem_table_config_t *)malloc(MEM_TABLE_CONFIG_SIZE); 
		  //array_space_config->mem_table_no             = allocat_mem_table_no();
      //array_space_config->owner_id                   = mem_table->owner_id;
      heap_space_config->fields_table               = _fields_table;
      heap_space_config->field_used_num             = 1;
      heap_space_config->mem_block_used             = 1;
      heap_space_config->auto_extend                = 1; //允许自动扩展
      heap_space_config->mem_blocks_table           = mb;
      heap_space_config->mem_blocks_table->next     = 0;
      strcpy(heap_space_config->table_name,mem_index_config->index_name);
      strcat(heap_space_config->table_name,"_skip\0");
      DEBUG(" skip_space_config->table_name is %s \n",heap_space_config->table_name);

		  heap_space_config->extend_block_size   = mem_index_config->heap_block_size; //自动扩展大小

			//4.构造 mem_table_t
			struct mem_table_t      *heap_space_temp ;  		
			int err=0;
      err = mem_table_create(
                             &heap_space_temp,
                             heap_space_config
                             );
      DEBUG(" heap_space_temp is %0x \n",heap_space_temp);

                    
       //5 设置  mem_skiplist_index              
      (*mem_skiplist_index) = (mem_skiplist_index_t  *)malloc(MEM_SKIPLIST_INDEX_SIZE);

      allocate_index_no(&((*mem_skiplist_index) -> config.index_no ));
      set_index_no_addr((*mem_skiplist_index) -> config.index_no,(void *)mem_skiplist_index);
      (*mem_skiplist_index) -> config.owner_table_no   = mem_index_config->owner_table_no;
      (*mem_skiplist_index) -> config.field_order      = mem_index_config->field_order;
      (*mem_skiplist_index) -> config.field_num        = mem_index_config->field_num;
      (*mem_skiplist_index) -> config.owner_id         = mem_index_config->owner_id;
      (*mem_skiplist_index) -> config.heap_block_size  =  heap_space_config->mem_blocks_table->block_size;
      (*mem_skiplist_index) -> config.max_level        =  mem_index_config->max_level;
      strcpy((*mem_skiplist_index) -> config.index_name,mem_index_config->index_name);
      //设置堆内存
       (*mem_skiplist_index)->heap_space = heap_space_temp;
        SKIPLIST_LOCK_INIT(&((*mem_skiplist_index)->locker))
       (*mem_skiplist_index)->root      = NULL;                                       
    //  DEBUG(" mem_skiplist_create() ,mem_skiplist_index is %0x \n",(*mem_skiplist_index));

      return err;
}                 	
                             	
                   

//打开索引                             
inline int mem_skiplist_index_open  (mem_skiplist_index_t *  mem_skiplist_index)
{
	
 if(NULL == mem_skiplist_index    )  return OPEN_MEM_SKIPLIST_ERR_NULL_SKIPLIST_PTR;
  
  int err;
	err = mem_table_open(mem_skiplist_index->heap_space);
	return err;
	
	
}
//关索引
inline	int mem_skiplist_index_close(mem_skiplist_index_t *  mem_skiplist_index)
{
	
		if(NULL == mem_skiplist_index    )  return CLOSE_MEM_SKIPLIST_INDEX_ERR_NULL_PTR;
	  DEBUG("Begin to close a mem_index：%s, addr is %0x .\n",(mem_skiplist_index)->config.index_name,(mem_skiplist_index)->config);
    SKIPLIST_LOCK(&(mem_skiplist_index->locker))
	  int err = 0;
	 //struct mem_table_t *heap_space_temp = mem_skiplist_index->heap_space;
	 //DEBUG("heap_space_temp's name is %s, addr is %0x .\n",heap_space_temp->config.table_name,heap_space_temp);

	  err  = mem_table_close( (mem_skiplist_index)->heap_space);
	  del_index_no_addr(mem_skiplist_index->config.index_no);
	  
    if(mem_skiplist_index)free(mem_skiplist_index);
		SKIPLIST_UNLOCK(&(mem_skiplist_index->locker))
		return err;	
}


/*初始化*/
inline int  mem_skiplist_init(mem_skiplist_index_t *mem_skiplist_index)
{
	DEBUG("Enter mem_skiplist_inint() \n");
	 if(NULL == mem_skiplist_index  )  return SKIPLIST_INDEX_ERR_NULL_INDEX_PRT;   
   
   // 初始化随机数
   mem_random_init(&(mem_skiplist_index->config.random),0xdeadbeef);
   int err;
   //先通过nil是否是第一块的第一行来判断是否是第一次启动
   struct record_t * record_ptr;
   
   get_record_by_record_num(mem_skiplist_index->heap_space,
   													mem_skiplist_index->heap_space->config.mem_blocks_table, 
   													0,&record_ptr);
   // nil 非空，则不再需要初始化
   if(record_ptr->is_used)return;
   
   
   //DEBUG("Enter mem_skiplist_insert(),insert value is %ld ;\n",key->skiplist_lkey);
       char buf[FIELD_SKIPLIST_ENTRY_SIZE];
       
			 long  block_no;
			 // 第一行为 nil
			 err = mem_table_insert_record(mem_skiplist_index->heap_space ,&record_ptr,&block_no,buf);
       mem_skiplist_index->nil = (mem_skiplist_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
			 // 后 max_level 行为 各level 头节点
			 int i = 1;
			 //struct  record_t* prev_record_ptr;
			 // 构造 各 level 头节点
			 for( ;i<mem_skiplist_index->config.max_level+1;++i  )
			 {
			 	DEBUG("Insert level Head Node: %d \n",i);
				err = mem_table_insert_record(mem_skiplist_index->heap_space ,&record_ptr,&block_no,buf);
        if(err)
        	{
        		ERROR("mem_skiplist_insert Err! err is %d\n",err);
        		return err;
        	}
        	        		
        mem_skiplist_entry_t * cur_entry = (mem_skiplist_entry_t *)(((char *)(record_ptr) + RECORD_HEAD_SIZE) );
				cur_entry->right_record_num      =  mem_skiplist_index->nil->record_num;
				cur_entry->right_block_no        =  block_no;
        if( 1 != i)
        	{
        	  //mem_skiplist_entry_t * prev_record_ptr = (mem_skiplist_entry_t *)(((char *)(prev_record_ptr) + RECORD_HEAD_SIZE));
						cur_entry->down_record_num  =  record_ptr->record_num - 1;
        	  cur_entry->down_block_no    =  block_no;
        	  DEBUG("cur_entry->down_record_num is %d,cur_entry->down_block_no  is %d \n ",cur_entry->down_record_num,cur_entry->down_block_no);

        	}	
        	
        //prev_record_ptr = 	record_ptr;
        	
        }
        DEBUG("mem_skiplist_inint end \n");
        return 0;
}

// 获得链表头
inline mem_skiplist_entry_t *  mem_skiplist_getlevel_head(mem_skiplist_index_t *mem_skiplist_index,int head_num)
{

   if(NULL == mem_skiplist_index   ){
   	ERROR("SKIPLIST_INDEX_ERR_NULL_INDEX_PRT\n");
   	 return (mem_skiplist_entry_t *)(-1);
   	} 
   	
   	if( 0 >= head_num   ){
   	ERROR("SKIPLIST_LEVEL_ERR_IS_NEGTIVE\n");
   	 return (mem_skiplist_entry_t *)(-1);
   	} 

   if(head_num > mem_skiplist_index->config.max_level ){
   	ERROR("SKIPLIST_INDEX_ERR_BIG_LEVEL,%d > %d .\n",head_num,mem_skiplist_index->config.max_level );
   	 return (mem_skiplist_entry_t *)(-1);
   } 
   	
   struct record_t * level_head_ptr = (struct record_t *)( ( (char *)(mem_skiplist_index->nil) + FIELD_SKIPLIST_ENTRY_SIZE   )+ (head_num - 1 ) * ( FIELD_SKIPLIST_ENTRY_SIZE + RECORD_HEAD_SIZE )  );
	 DEBUG("level_head_ptr is %0x \n ", level_head_ptr );
   DEBUG("level is %d ,level_head_ptr->record_num is %d\n ", head_num , level_head_ptr->record_num );

	 
	 return (mem_skiplist_entry_t *)( (char *)level_head_ptr + RECORD_HEAD_SIZE );
}

// 生成随机level
int mem_skiplist_randlevel__(mem_skiplist_index_t *mem_skiplist_index) 
{
	// Increase height with probability 1 in kBranching
  static const unsigned int kBranching = 4;
  int height = 1;
  while (height < mem_skiplist_index->config.max_level && ( mem_random_next(&(mem_skiplist_index->config.random) ) % kBranching) == 0 ) {
    height++;
  }
  //assert(height > 0);
  //assert(height <= kMaxHeight);
  return height;
}

int mem_skiplist_randlevel(mem_skiplist_index_t *mem_skiplist_index)  {  
    int level = 1;  
    while ((random()&0xFFFF) < ( (0.25) * 0xFFFF))  
        level += 1;  
    return (level<  mem_skiplist_index->config.max_level ) ? level :  mem_skiplist_index->config.max_level;  
}  

int mem_skiplist_insert(mem_skiplist_index_t *mem_skiplist_index, 
												mem_skiplist_entry_t *in,
 												struct  record_t **  inserted
 												)
{
	int maxLevel = mem_skiplist_index->config.max_level;
	//int level    = mem_random_next(&(mem_skiplist_index->config.random) );
	int err = 0;
	do{
	err = mem_skiplist_insert_help(mem_skiplist_index,
																	NULL,	mem_skiplist_randlevel(mem_skiplist_index) ,
																	in,
																	inserted);
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
	return err;
} 												

// 插入
int mem_skiplist_insert_help__(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, int level,
 												mem_skiplist_entry_t *in,
 												struct  record_t ** last_insert_skiplist_entry 
 											 )
 {
	// 1插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	
	if(NULL == prev)
	{
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,level );
	}
	else //有上层节点加速
	  prev_entry = prev;
	
	DEBUG("prev_entry is %0x\n",prev_entry);	
	//DEBUG("prev_entry->down_record_num is %d ,prev_entry->down_block_no is %d \n ",prev_entry->down_record_num,prev_entry->down_block_no);

		
	//2 从当层，获得下一个 entry
	 record_t * right_record;
	 mem_skiplist_entry_t * right_entry;
	 unsigned  long   right_record_num ;
	 long             right_block_no   ;
	 unsigned  long   down_record_num ;
	 long             down_block_no   ;
	 long mem_table_no = mem_skiplist_index->heap_space->config.mem_table_no;
	 
	  struct  record_t * prev_ptr; 
	 int is_countinue ;
	 int have_insert_next_level = 0;
	 int err = 0 ;
	 do{
	 is_countinue = 0;
	 // 查找当层 >= key 的节点
	

	 do{
   prev_ptr  = (struct  record_t *)((char *)prev_entry - RECORD_HEAD_SIZE );
	
	 SKIPLIST_RLOCK   (  &(prev_ptr->row_lock) );
	 right_record_num = prev_entry->right_record_num;
	 right_block_no   = prev_entry->right_block_no;
	 get_record(mem_skiplist_index->heap_space,right_block_no,right_record_num,&right_record) ;
	 if(right_record->is_used == 0)continue;
	 	
   right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 if( mem_skiplist_index->nil != right_entry && right_entry->lkey < in->lkey)prev_entry = right_entry;;
	 SKIPLIST_RUNLOCK   (  &(prev_ptr->row_lock) );
	 
	}while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	 
	 if ( right_entry == mem_skiplist_index->nil || right_entry->lkey > in->lkey) 
	 	{
	 		 DEBUG("level is %d \n",level);
	 		//非底层除了插入链表，还必须处理 down 节点
	 	if( level > 1 )
	 		{
	 		struct  record_t * down_ptr = NULL;
	 		down_record_num = prev_entry->down_record_num;
	    down_block_no   = prev_entry->down_block_no;
	    DEBUG("down_record_num iS %d ,down_block_no is %d \n ",down_record_num,down_block_no);
	   
	    get_record_by_3NO(mem_table_no,down_block_no, down_record_num,&down_ptr);
	    mem_skiplist_entry_t * down_entry = (mem_skiplist_entry_t *)( (char *)down_ptr +  RECORD_HEAD_SIZE);
	    
	    //递归插入下一层
	    if ( 0 == have_insert_next_level) // 防止重复插入下一层
	    {
	    	err = mem_skiplist_insert_help( mem_skiplist_index, down_entry, level - 1, in , &down_ptr);
	      have_insert_next_level = 1;
	    }
	    
	 		if ( down_ptr != NULL ) 
	 				{
	 					DEBUG("Back from mem_skiplist_insert(),now level is %d \n",level);
	 					
				  	//如果被修改过，则重新循环
	 			    if( mem_skiplist_index->nil != right_entry &&  right_entry->lkey < in->lkey ) 
	 			    	{
	 			    		DEBUG("is_continue =1");
	 			    		is_countinue = 1;
	 			    		continue;
	 			    	}
	 			    // 修改 prev_entry 链表	
	 			    	struct record_t * new_record_ptr;
	 			    	long block_no;
	 			    	
	 			    	prev_ptr = (struct  record_t *)((char *)prev_entry - RECORD_HEAD_SIZE );
	 			    	
	 			    	//1. 新节点的right 指向 prev_entry 的后继节点	 			    	
	 			    	in->right_record_num = prev_entry->right_record_num;
	 			    	in->right_block_no   = prev_entry->right_block_no;
	 			    	// 处理 down 指针
	 			    	in->down_record_num  = down_ptr->record_num;
	 			    	
	 			    	struct  mem_block_t * down_block;
	 			    	get_block_by_record(mem_skiplist_index->heap_space ,down_ptr,&down_block);
	 			    	in->down_block_no   = down_block->block_no;
	 			    	
	 			    	//2. 插入新节点
	 			    	mem_table_insert_record( mem_skiplist_index->heap_space ,
                          &new_record_ptr,
                          &block_no, /* in */
                          (char *)in
                          );
                          
	 			    	//3. prev_entry 的后继 指向 新节点
	 			    	
	 			    	SKIPLIST_LOCK   (  &(prev_ptr->row_lock) );
	 			    	prev_entry->right_record_num = new_record_ptr->record_num;
	 			      prev_entry->right_block_no = block_no;
	 			    	
	 			    	SKIPLIST_UNLOCK   (  &(prev_ptr->row_lock) );
					}
	 		}
	 		
	 		//最底层就插入链表
	 		if( level == 1 )
	 			{
	 			    //如果被修改过，则重新循环
	 			    if(right_entry->lkey < in->lkey && right_entry != mem_skiplist_index->nil )
	 			    	{
	 			    		DEBUG("is_countinue =1");
	 			    		is_countinue = 1;
	 			    		continue;
	 			    	}
	 			    // 修改 prev_entry 链表	
	 			    
	 			    	struct record_t * new_record_ptr;
	 			    	long block_no;
	 			    	//1. 新节点的right 指向 prev_entry 的后继节点	 		
	 			    	prev_ptr = (struct  record_t *)((char *)prev_entry - RECORD_HEAD_SIZE );
	 			    	
	 			    		 			    	
	 			    	in->right_record_num = prev_entry->right_record_num;
	 			    	in->right_block_no   = prev_entry->right_block_no;
	 			    	//2. 插入新节点
	 			    	mem_table_insert_record( mem_skiplist_index->heap_space ,
                          &new_record_ptr,
                          &block_no, /* in */
                          (char *)in
                          );
	 			    	//3. prev_entry 的后继 指向 新节点
	 			    	SKIPLIST_LOCK   (  &(prev_ptr->row_lock) );
	 			    	prev_entry->right_record_num = new_record_ptr->record_num;
	 			      prev_entry->right_block_no = block_no;
	 			    	
	 			    	SKIPLIST_UNLOCK   (  &(prev_ptr->row_lock) );  
	 			}
	 	}
	 	
	  
	}while(is_countinue);
	
	 *last_insert_skiplist_entry = prev_ptr;
	 return err;
} 


inline int mem_skiplist_delete(mem_skiplist_index_t *mem_skiplist_index ,mem_skiplist_entry_t *in )
{
	int err = 0;
	do{
	err = mem_skiplist_delete_help( mem_skiplist_index,NULL,0,in	);
	}while(err == SKIPLIST_INDEX_ERR_GETDOWN_FAILED || err == SKIPLIST_INDEX_ERR_GETGE_FAILED );
  return err;
}

  // 删除指定元素
  // int level = mem_skiplist_index,mem_skiplist_index->config.max_level - 1;

inline int mem_skiplist_delete_help__(mem_skiplist_index_t *mem_skiplist_index, mem_skiplist_entry_t *prev, int level ,mem_skiplist_entry_t *in )
 {
 	DEBUG("Enter mem_skiplist_delete_help()\n");
	// 1插入最高层，无前继节点加速
	mem_skiplist_entry_t * prev_entry;
	int level_tmp  ;
	
	if(NULL == prev)
	{
		DEBUG("NO prenode ， Use Max level！\n");	
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,mem_skiplist_index->config.max_level );
	  level_tmp  = mem_skiplist_index->config.max_level;
	}
	else //有上层节点加速
	  {
	  	prev_entry = prev;
	  	level_tmp = level;
	  }
	
	 DEBUG("prev_entry is %0x\n",prev_entry);	
	//2 从当层，获得下一个 entry
	 record_t * right_record;
	 mem_skiplist_entry_t * right_entry;
	 unsigned  long   right_record_num ;
	 long             right_block_no   ;
	 unsigned  long   down_record_num ;
	 long             down_block_no   ;
	 long mem_table_no = mem_skiplist_index->heap_space->config.mem_table_no;
	 
	 
	 int is_continue ;
	  // 查找当层 >= key 的节点
	 struct  record_t * prev_ptr;
	 
	 do{
	 is_continue = 0;
	 do{
   prev_ptr = (struct  record_t *)((char *)prev_entry - RECORD_HEAD_SIZE );
	
	 SKIPLIST_RLOCK   (  &(prev_ptr->row_lock) );
	 right_record_num = prev_entry->right_record_num;
	 right_block_no   = prev_entry->right_block_no;
	 get_record(mem_skiplist_index->heap_space,right_block_no,right_record_num,&right_record) ;
   if(right_record->is_used == 0)continue;
  
   right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 if( right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey )prev_entry = right_entry;
	 //如果当前层找不到，就转到下一层
	 if( (right_entry == mem_skiplist_index->nil || right_entry->lkey < in->lkey ) && level_tmp != 1 )	
	 	{
	 		struct  record_t * down_ptr = NULL;
	 		down_record_num = prev_entry->down_record_num;
	    down_block_no   = prev_entry->down_block_no;
	    
	    get_record_by_3NO(mem_table_no,down_block_no, down_record_num,&down_ptr);
	    SKIPLIST_RUNLOCK   (  &(prev_ptr->row_lock) );
	    prev_entry = (mem_skiplist_entry_t *)( (char *)down_ptr +  RECORD_HEAD_SIZE);
	  	--level_tmp ;
	  	continue;
	  }
	 SKIPLIST_RUNLOCK   (  &(prev_ptr->row_lock) );
	 
	}while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	 
	 if(right_entry == mem_skiplist_index->nil && level_tmp == 1)
	 {
	 	 DEBUG("SKIPLIST_INDEX_ERR_DELETE_NOT_FOUND\n");
	 	 return SKIPLIST_INDEX_ERR_DELETE_NOT_FOUND;//没找到
	 }
	 
	 //找到的时候就删掉
	 if (  right_entry->lkey == in->lkey) 
	 	{
	 		DEBUG("Found delete target!");
	 		//非底层除了插入链表，还必须处理 down 节点
	 	if( level_tmp >= 1 ) 
	 		{
	 			// 先删上层
	 			SKIPLIST_LOCK   (  &(right_record->row_lock) );
	 			prev_entry->right_record_num = right_entry->right_record_num;
	 			prev_entry->right_block_no   = right_entry->right_block_no;
	 			SKIPLIST_UNLOCK (  &(right_record->row_lock) );
	 			mem_table_del_record(mem_skiplist_index->heap_space ,right_record);
	 		 
	 		
	 					//不是最后一层，是需要继续删除 down 节点的
	 					if( level_tmp > 1 )
	 						{	
	 						struct  record_t * down_ptr = NULL;
	 						SKIPLIST_LOCK   (  &(right_record->row_lock) );
	 						down_record_num = right_entry->down_record_num;
	   					down_block_no   = right_entry->down_block_no;
	   					
	   					get_record_by_3NO(mem_table_no,down_block_no, down_record_num,&down_ptr);
	   					mem_skiplist_entry_t * down_entry = (mem_skiplist_entry_t *)( (char *)down_ptr +  RECORD_HEAD_SIZE);
	   					SKIPLIST_UNLOCK   (  &(right_record->row_lock) );
	   				
	    				return mem_skiplist_delete_help__( mem_skiplist_index, down_entry ,level_tmp, in);
	    			  }
	    			  
	 		
	    }
}
	
} while(is_continue);

 	DEBUG(" mem_skiplist_delete_help() End\n");

return 0;
}

// 查找
inline int mem_skiplist_search(mem_skiplist_index_t *mem_skiplist_index ,mem_skiplist_entry_t *in,mem_skiplist_entry_t ** out,int * level )
 {
 	  DEBUG("Enter mem_skiplist_delete()\n");
	  // 1插入最高层，无前继节点加速
	  mem_skiplist_entry_t * prev_entry;
	  int level_tmp  =  mem_skiplist_index->config.max_level;
   
		DEBUG("Use Max level As prev_entry ！\n");	
	  prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index, level_tmp );

	
	 DEBUG("prev_entry is %0x\n",prev_entry);	
	//2 从当层，获得下一个 entry
	 record_t * right_record;
	 mem_skiplist_entry_t * right_entry;
	 unsigned  long   right_record_num ;
	 long             right_block_no   ;
	 unsigned  long   down_record_num ;
	 long             down_block_no   ;
	 long mem_table_no = mem_skiplist_index->heap_space->config.mem_table_no;
	 
	 
	 int is_continue ;
	  // 查找当层 >= key 的节点
	 struct  record_t * prev_ptr;
	 
	 do{
   prev_ptr = (struct  record_t *)((char *)prev_entry - RECORD_HEAD_SIZE );
	
	 SKIPLIST_RLOCK   (  &(prev_ptr->row_lock) );
	 right_record_num = prev_entry->right_record_num;
	 right_block_no   = prev_entry->right_block_no;
	 get_record(mem_skiplist_index->heap_space,right_block_no,right_record_num,&right_record) ;
   right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 if( right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey )prev_entry = right_entry;
	 //如果当前层找不到，就转到下一层
	 if( (right_entry == mem_skiplist_index->nil || right_entry->lkey < in->lkey) && level_tmp != 1)	
	 	{
	 		struct  record_t * down_ptr = NULL;
	 		down_record_num = prev_entry->down_record_num;
	    down_block_no   = prev_entry->down_block_no;
	    
	    get_record_by_3NO(mem_table_no,down_block_no, down_record_num,&down_ptr);
	    SKIPLIST_RUNLOCK   (  &(prev_ptr->row_lock) );
	    prev_entry = (mem_skiplist_entry_t *)( (char *)down_ptr +  RECORD_HEAD_SIZE);
	  	--level_tmp ;
	  	continue;
	  }
	 SKIPLIST_RUNLOCK   (  &(prev_ptr->row_lock) );
	 
	}while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	
	if(right_entry == mem_skiplist_index->nil && level_tmp == 1)
	 {
	 	 DEBUG("SKIPLIST_INDEX_ERR_DELETE_NOT_FOUND\n");
	 	 return SKIPLIST_INDEX_SEARCH_NOT_FOUND;//没找到
	 }
	 
	 if (  right_entry->lkey == in->lkey) 
	 {
	 	*out   = right_entry;
	 	*level = level_tmp;
	 	 return 0;
	 }
	 return SKIPLIST_INDEX_SEARCH_NOT_FOUND;
	 
	}
//_________________________________________________________________

/*
*insert_after_node0   del_node2  ( ok because node1 is always safe )
*  node0 --> node1 --> node2
*  
*  
*del_next(step 1)  insert(step 2)  (  bad!,must lock node1 ,so del must lock right,and insert must lock prev )
*  node0 --> node1 --> node2
*  
*  
*del_next(step 2)  insert(step 1)  (  ok because node1 is always safe )
*  node0 --> node1 --> node2  
*  
*  
*del_node0(step 1)             del_node2(step 2)  ( ok because node1 is always safe )
*  node0       -->      node1    --> node2 
*/


//  获得本层 == lkey的前继节点
inline int mem_skiplist_find_EQ(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record;
	 mem_skiplist_entry_t * right_entry ;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 DEBUG("Enter mem_skiplist_find_EQ(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 //IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
	 do{
	 				do{
	 					  prev_record = (record_t *)((char *)prev_entry - RECORD_HEAD_SIZE);

	 						SKIPLIST_RLOCK( &(prev_record->row_lock) );
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						SKIPLIST_RUNLOCK( &(prev_record->row_lock) );						
	 												
	 						if(err)return err;
	 					}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %ld \n ",right_entry->lkey);

	 
	 if( mem_skiplist_index->nil != right_entry && 
	 			right_entry->lkey < in->lkey            )prev_entry = right_entry ;
	 
	 }while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	 
	 if(right_entry->lkey == in->lkey && right_entry != mem_skiplist_index->nil){
	 	 *last_find_entry = prev_entry;
	 	 DEBUG(" mem_skiplist_find_EQ end,prev_entry is %0x \n ",prev_entry);

	 	 return 0;
	  }
	 	else
	 		{
	 		return	SKIPLIST_INDEX_SEARCH_NOT_FOUND;
	 		}
	
	 	 
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_entry is %0x \n ",prev_entry);

	  return 0;
}




//  获得本层 >= lkey的前继节点
inline int mem_skiplist_find_GE(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, 
 												mem_skiplist_entry_t *in,
 												mem_skiplist_entry_t **last_find_entry 
 											 )
{
	//右指针 和 它的数据指针 
	 record_t 						* right_record = NULL;
	 mem_skiplist_entry_t * right_entry  = NULL;
	 record_t 						* prev_record = NULL;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int err;
	 DEBUG("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld 	\n ",prev_entry,in->lkey);
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
	 			right_entry->lkey < in->lkey            )prev_entry = right_entry ;
	 
	 }while(right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey);
	 
	 *last_find_entry = prev_entry;
	 	 
	 DEBUG(" mem_skiplist_find_GE end,prev_record is %0x \n ",right_record->record_num );
	 //IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry);

	  return 0;
}

inline int mem_skiplist_get_down(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev_entry, 
 												mem_skiplist_entry_t **last_find_entry 
 											 )
{
		//下指针 和 它的数据指针 
	 record_t 						* down_record;
	 mem_skiplist_entry_t * down_entry ;
	 DEBUG("Enter mem_skiplist_get_down()\n ");
   //IMPORTANT_INFO("Enter mem_skiplist_get_down()\n ");
	 
	 			get_record(mem_skiplist_index->heap_space ,
	 								prev_entry->down_block_no,
	 								prev_entry->down_record_num,
	 								&down_record                   );
	 	if( down_record->is_used == 0 )return SKIPLIST_INDEX_ERR_GETDOWN_FAILED;
	 	
	 down_entry = (mem_skiplist_entry_t *)((char *)(down_record) + RECORD_HEAD_SIZE);
	 
	 *last_find_entry = down_entry;
	 DEBUG(" mem_skiplist_get_down end\n ");
   //IMPORTANT_INFO("End mem_skiplist_get_down \n ");
	 return 0;
}

//
inline int mem_skiplist_insert_one(mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in  ,
 																	mem_skiplist_entry_t **last_insert_entry ,
 																	long              *last_insert_block_no
 											 						)
{	
	DEBUG("Enter mem_skiplist_insert_one()\n");
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
	mem_table_insert_record( mem_skiplist_index->heap_space ,
              &new_record_ptr,
              &new_block_no  , /* in */
              (char *)in
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
 	DEBUG("Enter mem_skiplist_insert_one end\n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}
	 
	 
 // 插入
int mem_skiplist_insert_help(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev, int level,
 												mem_skiplist_entry_t *in,
 												struct  record_t ** last_insert_skiplist_entry 
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
	  err = mem_skiplist_insert_one( mem_skiplist_index, 
 															pre_array[i], 
 															in   ,
 															&cur_insert_entry,
 															&pre_insert_block_no
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


inline int mem_skiplist_cout_to_end(mem_skiplist_index_t *mem_skiplist_index, 
 												mem_skiplist_entry_t *prev
 											 )  
{
//右指针 和 它的数据指针 
	 record_t 						* right_record;
	 mem_skiplist_entry_t * right_entry ;
	 mem_skiplist_entry_t * prev_entry  = prev;
	 int i = 0;
	 int err;
	 DEBUG("Enter mem_skiplist_find_GE(),prev_entry is %0x 	\n ",prev_entry );
	 do{
	 				do{
	 						err = get_record(mem_skiplist_index->heap_space ,
	 												prev_entry->right_block_no,
	 												prev_entry->right_record_num,
	 												&right_record                   );
	 						if(err)return err;
	 					}while( right_record->is_used == 0 );
   
	 right_entry = (mem_skiplist_entry_t *)((char *)(right_record) + RECORD_HEAD_SIZE);
	 DEBUG(" go pass entry %ld \n ",right_entry->lkey);

	 
	 if( mem_skiplist_index->nil != right_entry ){
	 			prev_entry = right_entry ;
	 			++i;
	 			}
	 
	 }while(right_entry != mem_skiplist_index->nil  );
	 return i;
} 							
		
inline void mem_skiplist_print_each_level(mem_skiplist_index_t *mem_skiplist_index )  
{
  int i = 1;
  
  
  for(;i< mem_skiplist_index->config.max_level+1 ;++i){
  int count = 0;
  mem_skiplist_entry_t * prev_entry = mem_skiplist_getlevel_head( mem_skiplist_index,i );  
  TICK 
  count =  mem_skiplist_cout_to_end(mem_skiplist_index,prev_entry); 
  printf("Levle [%d]'s count is %d , used ",i,count);
  TOCK
  
  }
} 		

inline int mem_skiplist_delete_one(mem_skiplist_index_t *mem_skiplist_index, 
 																	mem_skiplist_entry_t  *prev, 
 																	mem_skiplist_entry_t  *in  )
{	
	DEBUG("===Enter mem_skiplist_delete_one()===\n");
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
 				mem_table_del_record(mem_skiplist_index->heap_space ,right_record);
	      //right_entry->right_record_num = right_record->record_num;
	      
 	DEBUG("===End mem_skiplist_delete_one()=== \n");
 	//IMPORTANT_INFO("End mem_skiplist_insert_one()\n");
 	return 0;
}


inline int mem_skiplist_delete_help(mem_skiplist_index_t *mem_skiplist_index, 
																			mem_skiplist_entry_t *prev, 
																			int level ,
																			mem_skiplist_entry_t *in )
 {
 	DEBUG("Enter mem_skiplist_delete_help(),delete level is %d\n",level);	
 	DEBUG("Enter mem_skiplist_delete_help(),delete key is %ld\n",in->lkey);	
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
	  err = mem_skiplist_delete_one( mem_skiplist_index, 
 															pre_array[i], 
 															in 
 											 				);
 		// 没找到就不删本层的节点									 				
 		if(err == SKIPLIST_INDEX_SEARCH_NOT_FOUND){
 			DEBUG("SKIPLIST_INDEX_SEARCH_NOT_FOUND\n");
 			continue;
 		}
 		if(err)return err;	
	}
	 	DEBUG("End mem_skiplist_delete_help()\n");	
    //IMPORTANT_INFO("Enter mem_skiplist_delete_help end\n");	
	return 0;
}


#ifdef __cplusplus

}

#endif

#endif