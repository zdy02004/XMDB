// 在用gcc编译的时候要加上选项 -march=i686

#ifndef TABLE_CTL
#define TABLE_CTL
#include "mem_block_t.h"
#include "rwlock.h"
#include "mem_table_no_manager.h"
#include "time_type_t.h"
#ifdef __cplusplus

extern "C" {

#endif

// 字段类型标号
#define FIELD_TYPE_INT        1
#define FIELD_TYPE_SHORT      2
#define FIELD_TYPE_LONG       3
#define FIELD_TYPE_LONGLONG   4
#define FIELD_TYPE_FLOAT      5
#define FIELD_TYPE_DOUBLE     6
#define FIELD_TYPE_STR        7
#define FIELD_TYPE_ANY        8
#define FIELD_TYPE_DATE       9    //date 类型为 str 16 14个值
#define FIELD_TYPE_HASH_ENTRY      10   //date 类型为 str 16 14个值
#define FIELD_TYPE_RBTREE_ENTRY    11   //date 类型为 str 16 14个值
#define FIELD_TYPE_SKIPLIST_ENTRY  12

// 字段类型
 //date 类型为 str 16 14个值
#define FIELD_INT        int
#define FIELD_SHORT      short
#define FIELD_LONG       long
#define FIELD_LONGLONG   long long
#define FIELD_FLOAT      float
#define FIELD_DOUBLE     double
#define FIELD_STR        char *
#define FIELD_ANY        void *
#define FIELD_DATE       time_t 
#define FIELD_HASH_ENTRY	   (struct  mem_hash_entry_t    )
#define FIELD_RBTREE_ENTRY	 (struct  mem_rbtree_entry_t  )
#define FIELD_SKIPLIST_ENTRY (struct  mem_skiplist_entry_t)

// 字段占用空间大小
#define FIELD_INT_SIZE        			sizeof(int)
#define FIELD_SHORT_SIZE      			sizeof(short)
#define FIELD_LONG_SIZE       			sizeof(long)
#define FIELD_LONGLONG_SIZE   			sizeof(long long)
#define FIELD_FLOAT_SIZE      			sizeof(float)
#define FIELD_DOUBLE_SIZE     			sizeof(double)
#define FIELD_DATE_SIZE       			sizeof(time_t)  //使用 linux 的 time_t
		


//错误类型
#define READ_RECORD_ERR_TABLE_IS_NULL                32001
#define READ_RECORD_ERR_RECORD_IS_NULL               32002
#define READ_RECORD_ERR_BUF_IS_NULL                  32003
#define READ_RECORD_UNUSED                           32004
#define INSERT_RECORD_ERR_FULL                       32005   
#define CREATE_MEM_TABLE_ERR_NULL_FIELD_INFO_PTR     32006
#define CREATE_MEM_TABLE_ERR_NULL_MEM_BLOCK          32007 
#define CREATE_MEM_TABLE_ERR_NO_NAME                 32008
#define CREATE_MEM_TABLE_ERR_TOO_LONG                32009
#define CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR          32010
#define OPEN_MEM_TABLE_ERR_NULL_TABLE_PTR            32011
#define CREATE_MEM_TABLE_ERR_NULL_CONFIG_PTR         32012

#define READ_FIELD_ERR_TABLE_IS_NULL                 32013
#define READ_FIELD_ERR_FIELD_NAME_IS_NULL            32014
#define READ_FIELD_ERR_IN_BUF_IS_NULL                32015
#define READ_FIELD_ERR_OUT_BUF_IS_NULL               32016
#define READ_FIELD_ERR_NOT_FOUND_FIELD               32017
#define MEM_TABLE_EXTEND_ERR                         32018
#define GET_BLOCK_ERR_BLOCK_IS_NULL                  32019
#define GET_BLOCK_ERR_RECORD_IS_IN_BLOCK             32020
#define INSERT_RECORD_ERR_TABLE_IS_NULL              32021
#define INSERT_RECORD_ERR_BUF_IS_NULL                32022
#define ALLOCATE_RECORD_ERR_TABLE_IS_NULL            32023
#define ALLOCATE_N_RECORD_ERR_TABLE_IS_NULL          32024
#define ALLOCATE_RECORD_ERR_NUM_IS_ZERO              32025
#define TRY_LOCK                                     32026
#define MEM_TABLE_EXTEND_ERR_NOT_ALLOW_EXTEND        32027
#define READ_RECORD_SCN_CHANGED                      32028
#define READ_RECORD_SCN_NOT_COMMITED			     			 32029
#define TRANS_NOT_FREE			    										 32030
#define UNDO_BLOCK_IS_NULL   									 32031
#define REDO_PTR_IS_NULL   										 32032
#define UNDO_PTR_IS_NULL   										 32033
#define READ_RECORD_ISUSED										 32034
#define GET_BLOCK_FAILD   										 32035
#define MEM_TABLE_EXTEND_ERR_NAME_IS_NULL			 32036
#define MEM_TABLE_EXTEND_FREE_SIZE_ERR         32037
#define ALLOCTE_RECODR_TOO_TIMES               32038
#define HIGH_LEVEL_TRY_LOCK										 32039
#define UNLOCK_FAILED													 32040

//最大字段个数
//1个表最大内存块数
#define MAX_FIELD_NUM        64
#define MAX_BLOCK_NUM        64

//独占锁与共享锁
#define table_rwlock_t        	 pthread_rwlock_t
#define table_rwlock_init(x)     pthread_rwlock_init(x, NULL)
#define table_rwlock_rdlock(x)   pthread_rwlock_rdlock(x)
#define table_rwlock_wrlock(x)   pthread_rwlock_wrlock(x)
#define table_rwlock_unlock(x)   pthread_rwlock_unlock(x)
#define table_rwlock_destroy(x)  pthread_rwlock_destroy(x)


//暂时用CAS来实现行级读写锁
#define row_lock_t    rwlock_t
#define row_lock_init(x)   rwlock_init((x)); 

#define row_rlock(x)       rwlock_rlock((x)); 
#define row_runlock(x)     rwlock_runlock((x)); 

#define row_wlock(x)     \
rwlock_wlock(x); //  \
//__sync_fetch_and_sub(  &(mem_table->lock_manager.row_lock_counter), 1 );  

#define row_wunlock(x)     \
rwlock_wunlock(x);  // \
//__sync_fetch_and_add(  &(mem_table->lock_manager.row_lock_counter), 1 );


//暂时用互斥锁表示表级锁
#define table_lock_t            pthread_mutex_t
#define mem_table_lock_t        pthread_mutex_t
#define mem_table_lock(x)       pthread_mutex_lock(x)
#define mem_table_unlock(x)     pthread_mutex_unlock(x)   
#define mem_table_trylock(x)    pthread_mutex_trylock(x)
#define MEM_TABLE_LOCK_INIT(x)  pthread_mutex_init(x,NULL)
#define mem_table_dest(x)    		pthread_mutex_destroy(x)   


//单链表版本
//#define MEM_TABLE_DEL_CODE																	\
//LIST_LOCK  (  &(mem_block_temp->mem_free_list.list_lock)    );\
//record_ptr->is_used = 0;																			\
//record_ptr->last_free_pos = mem_block_temp->mem_free_list.head;\
//mem_block_temp->mem_free_list.head = record_ptr->record_num;	\
//LIST_UNLOCK    (  &(mem_block_temp->mem_free_list.list_lock)   );

//双链表版本删除语句
#define MEM_TABLE_DEL_CODE																				\
LIST_LOCK  (  &(mem_block_temp->mem_free_list.list_lock)    );		\
record_ptr->is_used = 0;																					\
record_ptr->last_free_pos = mem_block_temp->mem_free_list.head;		\
if( -1 != mem_block_temp->mem_free_list.head )										\
{																																	\
struct record_t * record_ptr2;																		\
get_record_by_record_num(mem_table,mem_block_temp, mem_block_temp->mem_free_list.head,&record_ptr2);\
record_ptr2->next_free_pos = record_ptr->record_num;							\
}																																	\
mem_block_temp->mem_free_list.head = record_ptr->record_num;			\
if( -1 == mem_block_temp->mem_free_list.tail )										\
{																																	\
		mem_block_temp->mem_free_list.tail = record_ptr->record_num;	\
}																																	\
LIST_UNLOCK    (  &(mem_block_temp->mem_free_list.list_lock)   );

struct  mem_hash_entry_t
{
unsigned  long     hash_lkey;						  //整型 hash   key 值
long               block_no;			          //存数据所在的块号
unsigned  long     record_num; 					  //存数据所在的行号
long               link_block_no;          //冲突存储区块号
unsigned  long     link_record_num;        //冲突数据在冲突块的行号
char               hash_ckey[32];          //字符串 hash key 值,暂时支持到32这么长的字符串

} __attribute__ ((packed, aligned (64)));

#define MEM_HASH_ENTRY_SIZE  sizeof(struct  mem_hash_entry_t)


/*定义结点的颜色*/
 typedef enum Color{
 		RED   = 1,
 		BLACK = 0
 }color_t;
typedef struct  mem_rbtree_entry_t
{
unsigned  long     rbtree_lkey;						  //整型 rbtree   key 值
long               block_no;			          //存数据所在表的块顺序号
unsigned  long     record_num; 					  //存数据所在的行号
long               parent_block_no;			  //父节点索引所在的块号
unsigned  long     parent_record_num; 			//父节点索引所在表的块顺序号
long               left_block_no;			    //左节点索引所在的块号
unsigned  long     left_record_num; 				//左节点索引所在的行号
long               right_block_no;			    //右节点索引所表的块顺序号
unsigned  long     right_record_num; 			//右节点索引据所在的行号
color_t            color;
//char                    rbtree_ckey[32];          //字符串 hash key 值,暂时支持到32这么长的字符串

} __attribute__ ((packed, aligned (64))) mem_rbtree_entry_t;

#define MEM_RBTREE_ENTRY_SIZE  sizeof(struct  mem_rbtree_entry_t)


typedef struct  mem_skiplist_entry_t
{
unsigned  long     lkey;						        //整型  key 值
long               block_no;			          //存数据所在表的块顺序号
unsigned  long     record_num; 					    //存数据所在的行号

long               down_block_no;			      //下一层节点索引所在的块号
unsigned  long     down_record_num; 				//下一层节点索引所在的行号
long               right_block_no;			    //右节点索引所表的块顺序号
unsigned  long     right_record_num; 			  //右节点索引据所在的行号
char               ckey[32];                              //字符串 hash key 值,暂时支持到32这么长的字符串

} __attribute__ ((packed, aligned (64))) mem_skiplist_entry_t;


#define FIELD_RBTREE_ENTRY_SIZE  sizeof(struct  mem_rbtree_entry_t)
#define FIELD_HASH_ENTRY_SIZE 			sizeof(struct  mem_hash_entry_t)
#define FIELD_SKIPLIST_ENTRY_SIZE 		sizeof(struct  mem_skiplist_entry_t)

//支持字段值之间的转换
typedef union field_value_def{
 FIELD_INT       int_val;
 FIELD_SHORT     short_val;
 FIELD_LONG      long_val;
 FIELD_LONGLONG  longlong_val;
 FIELD_FLOAT     float_val;
 FIELD_DOUBLE    double_val;
 FIELD_STR       str_val;
 FIELD_ANY       any_val;
 FIELD_DATE      date_val;
}field_value_t;

/*
字段 内存布局

record_t ={ field_t_0,field_t_1,field_t_2,field_3....... }

*/

//字段描述符
struct field_t
{
int                field_type;                //字段类型
char               field_name[32];            //字段名
off_t              field_size;                //一个字段占用空间的大小
int                field_order;               //字段在记录中排第几个
off_t              field_dis;                 //该字段距离数据启始地址的距离
short              index_nr;                  //相关的索引个数，0 表示没有索引，
long               relate_index[8];           //相关的索引id，一个字段最多被8个索引关联
} __attribute__ ((packed, aligned (64)));

#define FIELD_SIZE  sizeof(struct  field_t)



//填充 any 和 str 以外的各种类型的 field_size;
inline void fill_field_info (struct field_t *field)  
{
	switch ( field->field_type )   
{                                 
	case FIELD_TYPE_INT:            (field)->field_size = FIELD_INT_SIZE;              DEBUG("FIELD_TYPE_INT\n");					break; 
	case FIELD_TYPE_SHORT:          (field)->field_size = FIELD_SHORT_SIZE;            DEBUG("FIELD_TYPE_SHORT\n");				break; 
 	case FIELD_TYPE_LONG:           (field)->field_size = FIELD_LONG_SIZE;             DEBUG("FIELD_TYPE_LONG\n");				break; 
	case FIELD_TYPE_LONGLONG:       (field)->field_size = FIELD_LONGLONG_SIZE;         DEBUG("FIELD_TYPE_LONGLONG\n");		break; 
	case FIELD_TYPE_FLOAT:          (field)->field_size = FIELD_FLOAT_SIZE;            DEBUG("FIELD_TYPE_FLOAT\n");				break; 
	case FIELD_TYPE_DOUBLE:         (field)->field_size = FIELD_DOUBLE_SIZE;           DEBUG("FIELD_TYPE_DOUBLE\n");			break; 
  case FIELD_TYPE_DATE:           (field)->field_size = FIELD_DATE_SIZE;             DEBUG("FIELD_TYPE_DATE\n");				break; 
  case FIELD_TYPE_HASH_ENTRY:     (field)->field_size = FIELD_HASH_ENTRY_SIZE;       DEBUG("FIELD_TYPE_HASH_ENTRY\n");	break; 
  case FIELD_TYPE_RBTREE_ENTRY:   (field)->field_size = FIELD_RBTREE_ENTRY_SIZE;     DEBUG("FIELD_TYPE_RBTREE_ENTRY\n");break; 
  case FIELD_TYPE_SKIPLIST_ENTRY:   (field)->field_size = FIELD_SKIPLIST_ENTRY_SIZE;     DEBUG("FIELD_TYPE_RBTREE_ENTRY\n");break; 
  case FIELD_TYPE_STR:                                                               DEBUG("FIELD_TYPE_STR\n");break; //字符串类型需要自己设置长度
  default :                       (field)->field_size = 0;                          DEBUG("error ZERO_TYPE\n");
}
}

/*
记录 内存布局

=====================

struct  mem_block_t

======================
record_t_0 field_0 field_1 field_2 field_3 field_4 field_5 ...
record_t_1
record_t_2
record_t_3
record_t_4
record_t_5
.....
======================
*/

//记录描述符，代表一行数据
//每行记录的内存分布是 record_info+实际数据，record_info 是每行记录的开销
typedef struct record_t
{
long long                   record_num;         // 记录的逻辑ID
short                       is_used;            // 是否在用
row_lock_t                  row_lock;           // 行锁
unsigned long               last_free_pos;      // 用于维护空闲链表的位置信息
unsigned long               next_free_pos;      // 用于维护空闲链表的位置信息
long                        scn;               // 数据版本号用于事务隔离机制
struct undo_record_t*       undo_record_ptr;   //指向undo 的指针 // 后续可以废掉
void*                       undo_info_ptr;     //指向undo 信息的指针
void *                      data;               // 数据起始地址
} __attribute__ ((packed, aligned (64))) record_t;

// 记录描述符的大小
#define RECORD_HEAD_SIZE  sizeof(struct record_t)

#define INIT_RECORD(record_ptr)																					\
		(record_ptr)->data    =  (char *)record_ptr + RECORD_HEAD_SIZE;	\
		 row_lock_init(&((record_ptr)->row_lock)); //行锁初始化

//表锁管理器   
struct mem_lock_manager_t
{
int row_lock_counter;   //行锁计数器
} __attribute__ ((packed, aligned (64)));


//内存表配置信息
typedef struct mem_table_config_t
{  
   char                      table_name[128];        // 表名
   long                      mem_table_no;           // 该表的逻辑ID
   long                      owner_id;               // 该表所属用户的ID
   struct field_t     *      fields_table;           // 该表使用的所有字段
   int                       field_used_num;         // 使用字段的多少
   struct mem_block_t *      mem_blocks_table;       // 该表使用的数据内存块--块表
   int                       mem_block_used;         // 使用数据内存块的多少
   int                       auto_extend;            // 是否自动扩展
   off_t                     extend_block_size;      // 自动扩展块大小
// struct mem_index_t  *     mem_index_table,        // 该表使用的索引内存块记录表
} __attribute__ ((packed, aligned (64))) mem_table_config_t;


// 内存表配置描述符的大小
#define MEM_TABLE_CONFIG_SIZE  sizeof(mem_table_config_t)

/*
  内存表 内存布局
  mem_block_t--->mem_block_t--->mem_block_t--->mem_block_t
*/



//内存表
typedef struct mem_table_t
{
struct mem_table_config_t    config;
table_lock_t                 table_locker;            // 表级锁  
off_t                        record_size;             // 1个记录占用空间的大小
//long long                   record_used_num;       // 使用的记录数
//struct mem_free_list_t      mem_free_list;         // 空闲链表，用于复用已经删除数据记录
struct mem_lock_manager_t    lock_manager;            // 锁管理器 
short                        is_externing;            //是否在扩表                 
table_rwlock_t               rwlocker;
long long                    writer_trans_no;
} __attribute__ ((packed, aligned (64))) mem_table_t;

// 内存表描述符的大小
#define MEM_TABLE_SIZE  sizeof(struct mem_table_t)




//初始化内存表
#define INIT_MEM_TABLE(mem_table)																					\
//allocate_table_no(&((mem_table->config).mem_table_no));										\
//(mem_table)->config.fields_table                 =    0;									\
//(mem_table)->config.field_used_num               =    0;									\
//(mem_table)->config.mem_blocks_table             =    0;									\
(mem_table)->config.mem_block_used                 =    1;									\
MEM_TABLE_LOCK_INIT(&(mem_table->table_locker ));													\
table_rwlock_init(&(mem_table->rwlocker ));																\
(mem_table)->is_externing													=     0;                \
(mem_table)->writer_trans_no											=			-1;								\
//(mem_table)->record_used_num                      =    0;								\
//(mem_table)->config.index_used_num             =    0;									\
(mem_table)->lock_manager.row_lock_counter        =    0;
//(mem_table)-> redo_log             =    0; 


/////////////////////////////////////////////////////////////////////////////////////////////
inline int mem_table_extend( struct mem_table_t * mem_table, struct  mem_block_t ** out_mem_block);


//填充表里的字段信息的大小,和每个字段距离数据开始地址的距离
inline void fill_table_field_size ( struct mem_table_t *mem_table )  
{
	int i = 0;
	mem_table->record_size = RECORD_HEAD_SIZE;
	off_t dis =0;
  for(;i<mem_table->config.field_used_num; ++i)
  {
  	fill_field_info ( &(mem_table->config.fields_table[i]) );  
  	mem_table->config.fields_table[i].field_dis = dis;                       //初始化 field_dis
  	mem_table->record_size += mem_table->config.fields_table[i].field_size;	
  	dis += mem_table->config.fields_table[i].field_size;	
  }
 DEBUG("mem_table->record_size is %ld \n",mem_table->record_size);

}

//通过字段名称、数据地址、表 来获得该数据的 recored 的地址
inline int get_record_by_field_name(
                                struct mem_table_t *mem_table , //表
                                const char *field_name,         //字段名
                                void * addr,                    //字段存储数据启始地址
                                struct record_t * record_ptr           /*对应记录启始地址*/
                              )
{
	int i = 0;
	off_t dff_size = 0;
	//找到对应的字段
  for(;i<mem_table->config.field_used_num; ++i)
	{
		if(strcmp( field_name,	mem_table->config.fields_table[i].field_name    ) == 0 )break;	
		dff_size += mem_table->config.fields_table[i].field_size;
	}
	
	record_ptr =  (record_t*)(addr - dff_size - RECORD_HEAD_SIZE);  //记录启始地址 = 数据地址 - 前面所有字段数据占用的空间 - 记录头占用空间
	return 0;
}


//通过record的指针获得 mem_block_t 指针
inline int get_block_by_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,struct  mem_block_t ** mem_block)
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == mem_block)   return GET_BLOCK_ERR_BLOCK_IS_NULL;
  
  unsigned  long   record_num = record_ptr->record_num;
  if(record_num<0)return GET_BLOCK_ERR_RECORD_IS_IN_BLOCK;
  
  DEBUG("record_ptr is %0x,record_num is %ld,mem_table->record_size =%ld ,MEM_BLOCK_HEAD_SIZE=%d\n",record_ptr,record_num,mem_table->record_size,MEM_BLOCK_HEAD_SIZE);		
  //优化性能，从 O(n) 到 O(1)，record_ptr 通过位置	 record_num 和MEM_BLOCK_HEAD_SIZE 获得 space_start_addr 地址,由于块头拷贝到了这里，把他做块头使用来获得 mem_block_t
  struct  mem_block_t * space_start_addr = ((struct  mem_block_t *) ( (char *)record_ptr - (record_num*(mem_table->record_size))-MEM_BLOCK_HEAD_SIZE ));
  *mem_block = space_start_addr->block_malloc_addr;
  DEBUG("space_start_addr is %0x \n",space_start_addr);	
//  DEBUG("*mem_block is %0x \n",*mem_block);	
  if( 0 == *mem_block)
  	{
  		ERROR("BAD record_ptr is %0x,record_num is %ld,mem_table->record_size =%ld ,MEM_BLOCK_HEAD_SIZE=%d\n",record_ptr,record_num,mem_table->record_size,MEM_BLOCK_HEAD_SIZE);		

  		return GET_BLOCK_ERR_BLOCK_IS_NULL;
  	}
  //struct  mem_block_t * mem_block_temp  = mem_table->config.mem_blocks_table;
  
  //int i=0;
  //void * ptr = (void *) record_ptr;
  //
  //for(;i<mem_table->config.mem_block_used;++i)
	//{ 
	//	//record_ptr 位于数据空间内，则recored属于该块
	//	DEBUG("mem_block_temp->space_start_addr is %0x \n",mem_block_temp->space_start_addr);	
	//	DEBUG("mem_block_temp->space_end_addr is %0x \n",mem_block_temp->space_end_addr);	
  //
	//	if(mem_block_temp->space_start_addr  <= ptr && mem_block_temp->space_end_addr  >= ptr)
	//	   break;
	//	mem_block_temp = mem_block_temp->next;      //下一个块
	//}
	////
	//if( i == mem_table->config.field_used_num ) return GET_BLOCK_ERR_RECORD_IS_IN_BLOCK;
	//*mem_block = mem_block_temp  ;
	
	return 0;
}

//通过record的指针获得 mem_block_t 指针
inline int get_record_by_record_num(struct mem_table_t *mem_table,struct  mem_block_t * mb, unsigned  long   record_num,struct record_t ** record_ptr)
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == mb				)  return GET_BLOCK_ERR_BLOCK_IS_NULL;
  if( record_num<0      )  return GET_BLOCK_ERR_RECORD_IS_IN_BLOCK;
  	
  //优化性能，从 O(n) 到 O(1)，record_ptr 通过位置	 record_num 和 MEM_BLOCK_HEAD_SIZE 获得 mem_block 头地址
  *record_ptr = ((struct  record_t *) ( (char *)(mb->space_start_addr) +(record_num*(mem_table->record_size)) ));
  DEBUG("*record_ptr is %0x \n",*record_ptr);	
	
	return 0;
}

//void get_record(struct mem_table_t *mem_table_ptr, long block_no,long long record_num,record_t * record_ptr)  	

//  DEBUG("get_record(),block_no,record_num=( %ld,%ld ) ;\n",block_no,record_num);										\
//根据 块顺序号和行号快速获得 记录指针
//#define get_record(mem_table_ptr,block_no,record_num,record_ptr) \
//do{  																																																	\
//  int i = 0;																																													\
//	struct  mem_block_t * mem_block_temp = mem_table_ptr->config.mem_blocks_table;        							\
//	for(;i<mem_table_ptr->config.mem_block_used;++i)				/*遍历所有块,查找可以插入数据的内存块	*/		\
//	{																																																		\
//		if(mem_block_temp->space_start_addr + mem_block_temp->high_level* mem_table_ptr->record_size < mem_block_temp->space_end_addr - mem_table_ptr->record_size )break;	\
//			mem_block_temp = mem_block_temp->next;      /*下一个块                   */																																												\
//		if( i == block_no)break;                     /*找到对应的块                */																																												\
//	}																																																		\
//	record_ptr=( record_t *)((char *)(mem_block_temp->space_start_addr) + (record_num)*((mem_table_ptr)->record_size));/*根据找到的块，找到 recored_ptr */								\
//	}while(0);

inline int  get_record(mem_table_t *mem_table,long block_no,unsigned long record_num,struct record_t ** record_ptr) 
{  																																																	
  int err;
  int i = 0;																																													
	struct  mem_block_t * mb ;        
	DEBUG("block_no is %d,record_num is %d \n",block_no,record_num);							
	 err = get_block_no_addr(block_no,(void **)(&mb));
	DEBUG("mb is %0x,space_start_addr is %0x \n",mb,mb->space_start_addr);							
 
	 if(err)
	 	{
	 		ERROR("Get_block_no_addr failed!,err is %d\n",err);
	 		return err;
	 	}
  *record_ptr = ((struct  record_t *) ( (char *)(mb->space_start_addr) +(record_num*(mem_table->record_size)) ));
  DEBUG("*record_ptr is %0x \n",*record_ptr);	
	 return 0;
	}

// 通过3个 no 来获得行地址
inline int get_record_by_3NO(long mem_table_no,long block_no,long long record_num,struct record_t ** record_ptr) 
{  																																																	
		int err;
		mem_table_t *mem_table ;    																																						
		struct  mem_block_t * mb ; 
		
		DEBUG("mem_table_no is %d\n",mem_table_no);							
		err = get_table_no_addr(mem_table_no,(void **)(&mem_table));
		DEBUG("mem_table is %0x \n",mem_table);							
		 
		if(err)
		{
			ERROR("Get_block_no_addr failed!,err is %d\n",err);
			return err;
		}
		   
		   
		DEBUG("block_no is %d,record_num is %d \n",block_no,record_num);							
		err = get_block_no_addr(block_no,(void **)(&mb));
		DEBUG("mb is %0x,space_start_addr is %0x \n",mb,mb->space_start_addr);							
		
		if(err)
		{
			ERROR("Get_block_no_addr failed!,err is %d\n",err);
			return err;
		}
		*record_ptr = ((struct  record_t *) ( (char *)(mb->space_start_addr) +(record_num*(mem_table->record_size)) ));
		DEBUG("*record_ptr is %0x \n",*record_ptr);	
		 return 0;
}

//提交读取一个记录的数据
inline int mem_table_read_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )  return READ_RECORD_ERR_BUF_IS_NULL;	
	//记录未使用
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED;
	DEBUG(" enter mem_table_read_record() \n");	
  //record_ptr->data    = (void *)( (char *)(*record_ptr) + RECORD_HEAD_SIZE);
  
	row_rlock   (  &(record_ptr->row_lock )                                            );
	memcpy     (    buf, (char *)(record_ptr) + RECORD_HEAD_SIZE, mem_table->record_size - RECORD_HEAD_SIZE  );
	row_runlock (  &(record_ptr->row_lock )                                            );
	
	DEBUG("mem_table_read_record is %s \n",buf);	
	return 0;
}

//脏读取一个记录的数据
inline int mem_table_force_read_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )  return READ_RECORD_ERR_BUF_IS_NULL;	
	//记录未使用
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED;
		
	memcpy(    buf,  (char *)(record_ptr) + RECORD_HEAD_SIZE, mem_table->record_size - RECORD_HEAD_SIZE  );
	DEBUG("mem_table_force_read_record, record_ptr is %0x,buf = %s;\n",record_ptr,buf);	

	return 0;
}

//序列化读取一个记录的数据
inline int mem_table_safe_read_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )  return READ_RECORD_ERR_BUF_IS_NULL;	
	//记录未使用
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED;
  DEBUG("mem_table_safe_read_record, record_ptr is %0x;\n",record_ptr);	

	mem_table_lock(&(mem_table->table_locker) );         //表锁		
	memcpy     (    buf,  (char *)(record_ptr) + RECORD_HEAD_SIZE, mem_table->record_size - RECORD_HEAD_SIZE  );
	mem_table_unlock(&(mem_table->table_locker));        //解表锁

	return 0;
}


//读取一个字段的数据
inline int mem_table_read_field(struct mem_table_t *mem_table ,     //表指针
                       const char * field_name,           //字段名
                       void* in_buf,                      //记录数据
                       void* out_buf                      //字段数据
                       )
{
	if( NULL == mem_table )  return READ_FIELD_ERR_TABLE_IS_NULL;
	if( NULL == field_name)  return READ_FIELD_ERR_FIELD_NAME_IS_NULL;
	if( NULL == in_buf    )  return READ_FIELD_ERR_IN_BUF_IS_NULL;	
	if( NULL == out_buf   )  return READ_FIELD_ERR_OUT_BUF_IS_NULL;	
	//记录未使用
	int i = 0;
	off_t dff_size = 0;
	//找到对应的字段
  for(;i<mem_table->config.field_used_num; ++i)
	{
		if(strcmp( field_name,	mem_table->config.fields_table[i].field_name    ) == 0 )break;	
	}
	if(mem_table->config.field_used_num == i)return READ_FIELD_ERR_NOT_FOUND_FIELD;
	memcpy(out_buf,in_buf+(mem_table->config.fields_table[i].field_dis),mem_table->config.fields_table[i].field_size);
	return 0;
}


//更新一个记录的数据
inline int mem_table_update_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )        return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)        return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )        return READ_RECORD_ERR_BUF_IS_NULL;	
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED; //记录未使用
	DEBUG("mem_table_update_record, record_ptr is %0x,buf = %s;\n",record_ptr,buf);	

	row_wlock   (  &(record_ptr->row_lock) );
	memcpy     (   (char *)(record_ptr) + RECORD_HEAD_SIZE,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
	row_wunlock (  &(record_ptr->row_lock) );
	
	return 0;
}

//强制更新一个记录的数据
inline int mem_table_force_update_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )        return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)        return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )        return READ_RECORD_ERR_BUF_IS_NULL;	
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED; //记录未使用
	DEBUG("mem_table_force_update_record, record_ptr is %0x,buf = %s;\n",record_ptr,buf);	
	//redo_log		
	memcpy(   (char *)(record_ptr) + RECORD_HEAD_SIZE,  buf, mem_table->record_size - RECORD_HEAD_SIZE );	
	return 0;
}

//序列化更新一个记录的数据
inline int mem_table_safe_update_record(struct mem_table_t *mem_table ,struct record_t * record_ptr,char *buf)
{
	if( NULL == mem_table )        return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr)        return READ_RECORD_ERR_RECORD_IS_NULL;
	if( NULL == buf       )        return READ_RECORD_ERR_BUF_IS_NULL;	
	if( 0 == record_ptr->is_used ) return READ_RECORD_UNUSED; //记录未使用
	
	DEBUG("mem_table_safe_update_record, record_ptr is %0x;\n",record_ptr);	
	
	//redo_log
	mem_table_lock(&(mem_table->table_locker) );         //表锁				
	memcpy     (   (char *)(record_ptr) + RECORD_HEAD_SIZE,  buf, mem_table->record_size - RECORD_HEAD_SIZE );	
	mem_table_unlock(&(mem_table->table_locker));        //解表锁
	return 0;
}



//删除一个记录的数据
inline int mem_table_del_record(struct mem_table_t *mem_table ,struct record_t * record_ptr)
{
	if( NULL == mem_table        )   return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr       )   return READ_RECORD_ERR_RECORD_IS_NULL;
	if( 0 == record_ptr->is_used )   return READ_RECORD_UNUSED;         //记录未使用
	
	//获得块
	struct mem_block_t * mem_block_temp;
	int err;
  if(0!=(err=get_block_by_record(mem_table ,record_ptr,&mem_block_temp)))return err;
	DEBUG("Begin mem_table_del_record, mem_block_temp is %0x,block_no = %ld,record_num=%ld;\n",mem_block_temp,mem_block_temp->block_no,record_ptr->record_num);	
			
	row_wlock   (  &(record_ptr->row_lock)                  );
  MEM_TABLE_DEL_CODE
	row_wunlock (  &(record_ptr->row_lock)                 );

	return 0;
}

//强制删除一个记录的数据
inline int mem_table_force_del_record(struct mem_table_t *mem_table ,struct record_t * record_ptr)
{
	if( NULL == mem_table        )   return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr       )   return READ_RECORD_ERR_RECORD_IS_NULL;
	if( 0 == record_ptr->is_used )   return READ_RECORD_UNUSED;         //记录未使用
	
	//获得块
	struct mem_block_t * mem_block_temp;
	int err;
  if(0!=(err=get_block_by_record(mem_table ,record_ptr,&mem_block_temp)))return err;
  DEBUG("mem_table_force_del_record, record_ptr is %0x;\n",record_ptr);	

	MEM_TABLE_DEL_CODE
	return 0;
}

//序列化删除一个记录的数据
inline int mem_table_safe_del_record(struct mem_table_t *mem_table ,struct record_t * record_ptr)
{
	if( NULL == mem_table        )   return READ_RECORD_ERR_TABLE_IS_NULL;
	if( NULL == record_ptr       )   return READ_RECORD_ERR_RECORD_IS_NULL;
	if( 0 == record_ptr->is_used )   return READ_RECORD_UNUSED;         //记录未使用
	
	//获得块
	struct mem_block_t * mem_block_temp;
	int err;
  if(0!=(err=get_block_by_record(mem_table ,record_ptr,&mem_block_temp)))return err;
  DEBUG("mem_table_safe_del_record, mem_block_temp is %0x;\n",mem_block_temp);	

  mem_table_lock(&(mem_table->table_locker) );         //表锁		
	MEM_TABLE_DEL_CODE
  mem_table_unlock(&(mem_table->table_locker));        //解表锁

	return 0;
}

//分配一个空闲记录行
inline int mem_table_try_allocate_record(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no)
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
		
		   DEBUG("----- try to allocate record by high level -----\n");
		
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


	//没找到的内存块地址 > 块数据尾地址,则查找回收链表
	//  if (is_need_extern)
	//	{
	//		DEBUG(" ----- Try to find record in free_list -----\n");
	//		 	i=0;
	//    struct  mem_block_t * mem_block_temp2 = mem_table->config.mem_blocks_table;
      //遍历所有块,查找可以插入数据的内存块中的回收链表			
	//    for(;i<mem_table->config.mem_block_used;++i)
	//    {
	//	      	//空闲链表有数据，从链表头取一个地址插入		
 //     if( -1 != mem_block_temp2->mem_free_list.head ) 
	//       {
	//       	//空闲链表上锁
	//       	LIST_LOCK     (  &(mem_block_temp2->mem_free_list.list_lock)  );
	//       	//取得空闲链表的对应record的地址
	//       	(*record_ptr) =  (struct record_t *) ( (mem_block_temp2->mem_free_list.head) * mem_table->record_size + mem_block_temp->space_start_addr );
	//       	DEBUG("Find in Freelist, record_num %ld,record_ptr is %ld,last free pos is %ld\n",mem_block_temp->mem_free_list.head,*record_ptr,(*record_ptr)->last_free_pos);
	//       	high_level_temp = (*record_ptr)->record_num;////////////////////
	//       	//空闲链表的head 为上一个空闲链表的位置
	//       	mem_block_temp2->mem_free_list.head = (*record_ptr)->last_free_pos;
	//       	//空闲链表解锁
	//       	LIST_UNLOCK   (  &(mem_block_temp2->mem_free_list.list_lock)  );
	//       	//返回块的逻辑号
	//       	*block_no = mem_block_temp2->block_no;
	//       	is_need_extern = 0;
	//       	//DEBUG("----- Free record space in free_list finded!  -----\n");
 //       break;
	//       }	
	//       if(i!=mem_table->config.mem_block_used-1 )
	//       	{
	//       	mem_block_temp2 = mem_block_temp2->next;      //下一个块
	//         }
	//    }
	//   
	// }
// 没有空闲空间和回收链表，就自动扩表
	//if (i == mem_table->config.mem_block_used-1)  
	if (is_need_extern)  
{ 
	DEBUG(" ----- Try to externd_table ----- \n");
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
         // check 
				//{
				// int ij = 0;
				// struct  mem_block_t * mem_block_temp1 = mem_table->config.mem_blocks_table;
				// for(;ij<mem_table->config.mem_block_used-1;++ij)
				// {
				// 	mem_block_temp1 = mem_block_temp1->next; 
				// }
				//if( 0!= (err=HIGH_LEVEL_TRYLOCK(&(mem_block_temp1->high_level_lock)) ))
	      // {
        //  IMPORTANT_INFO("Check extern high_leve failed,err is %d ,extern_mem_block is %0x .\n",err,mem_block_temp1);
	      // 	return HIGH_LEVEL_TRY_LOCK;  //高水位线上锁
	      // }
        // else
        // 	{
        // 		IMPORTANT_INFO("Check extern high_leve ok\n");
        // 		HIGH_LEVEL_UNLOCK(&(mem_block_temp1->high_level_lock))
        // 	}
        // } 
                    HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁 	
	     	      			return TRY_LOCK;
	     	      			//if ( (extern_mem_block->space_end_addr-extern_mem_block->space_start_addr)>mem_table->record_size)
	     	      		  //  {
	     	      		  //   
	     	      		  //    //扩展块高水位线递增
                    //        HIGH_LEVEL_LOCK(&(extern_mem_block->high_level_lock));
                    //         (*record_ptr) =(struct record_t *)( extern_mem_block->space_start_addr); 	
                    //        high_level_temp =  extern_mem_block->high_level;
                    //        ++extern_mem_block->high_level;
                    //        HIGH_LEVEL_UNLOCK(&(extern_mem_block->high_level_lock));
                    //        //返回块的逻辑号
	                  //      	*block_no = extern_mem_block->block_no;
	                  //      	IMPORTANT_INFO("Allocate_block >>>record_ptr is %ld, high_level is %ld,block_no is %d\n",*record_ptr,high_level_temp,*block_no);
                    //
                    //  }
	     	      		  //else 
	     	      		  //	{
	     	      		  //		ERROR("MEM_TABLE_EXTEND_FREE_SIZE_ERR\n");
	     	      		  //		ERROR("extern_mem_block->space_end_addr is %0x\n",extern_mem_block->space_end_addr);
	     	      		  //		ERROR("extern_mem_block->space_start_addr is %0x\n",extern_mem_block->space_start_addr);
	     	      		  //		ERROR("mem_table->record_size is %d\n",mem_table->record_size);
	     	      		  //		return  MEM_TABLE_EXTEND_FREE_SIZE_ERR;
	     	      		  //	}
	     	      		  	
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
	     	      	
	DEBUG("----- Try to externd table end -----\n");	     	      	
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
     
     // CHEHCK PTR
     // 修复 多进程下错误的分配指针
    // { 
    // 	  struct  mem_block_t * space_start_addr = ((struct  mem_block_t *) ( (char *)(*record_ptr) - (high_level_temp*(mem_table->record_size))-MEM_BLOCK_HEAD_SIZE ));
    //    if(!space_start_addr)
    //    	{
    //    		ERROR("[check] space_start_addr [%ld] is bad \n",space_start_addr);
    //    		HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
    //    		return GET_BLOCK_ERR_BLOCK_IS_NULL;
    //    	}
    //    
    //    struct  mem_block_t * mem_block = space_start_addr->block_malloc_addr;
    //    //DEBUG("space_start_addr is %0x \n",space_start_addr);	
    //    //DEBUG("*mem_block is %0x \n",*mem_block);	
    //    if( 0 == mem_block)
  	//     {
  	//     	ERROR("[check] record_ptr is %ld,record_num is %ld,mem_table->record_size =%ld ,MEM_BLOCK_HEAD_SIZE=%d\n",record_ptr,high_level_temp,mem_table->record_size,MEM_BLOCK_HEAD_SIZE);		
    //      //(*record_ptr) = (struct record_t *) ( (char *)mem_block_temp->space_start_addr + high_level_temp * (mem_table->record_size) );
    //      //IMPORTANT_INFO("Fix_bad_record >>> %ld \n",*record_ptr);
    //      //
    //      //(*record_ptr)->record_num = high_level_temp;
    //      //(*record_ptr)->is_used    =  1;
    //      //(*record_ptr)->last_free_pos =  0;
    //      //(*record_ptr)->scn           =  0;
    //      //(*record_ptr)->undo_record_ptr= 0;
    //      //(*record_ptr)->data    =  (char *)(*record_ptr) + RECORD_HEAD_SIZE;  
    //      //row_lock_init(&((*record_ptr)->row_lock)); //行锁初始化
  	//      HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁
  	//      return GET_BLOCK_ERR_BLOCK_IS_NULL;
  	//     }
	  //
    //}
     HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //高水位线解锁

     DEBUG(" ----- Allocate_record >>> %0x , high_level is %ld ----- \n",*record_ptr,high_level_temp);
	   return 0;
	
}


//分配一个空闲记录行
inline int mem_table_allocate_record(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no)
{
	if( NULL == mem_table )  return ALLOCATE_RECORD_ERR_TABLE_IS_NULL;
//  DEBUG("Enter mem_table_allocate_record();\n");	
  int err;
  int i = 0;
	do{
		++i;
		err= mem_table_try_allocate_record(mem_table ,/* out */ record_ptr,block_no);
		if(0!= err && TRY_LOCK != err && HIGH_LEVEL_TRY_LOCK !=err)
  	{
  		return err;
  	} 
  	if( 1 == mem_table->is_externing )
  		{
  			i = 0;
  			continue;
  		}
 //	if(i>1000000)
 //		{
 //			ERROR("mem_table_allocate_record too times, err is %d !,mem_block_used is %d .\n",err,mem_table->config.mem_block_used);
 //			// check 
	//			{
	//			 int ij = 0;
	//			 struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	//			 for(;ij<mem_table->config.mem_block_used-1;++ij)
	//			 {
	//			 	mem_block_temp = mem_block_temp->next; 
	//			 }
	//        if ( 0!= (err=HIGH_LEVEL_TRYLOCK(&(mem_block_temp->high_level_lock)) ))
	//       	{
	//       	IMPORTANT_INFO("Check extern high_leve failed,err is %d ,extern_mem_block is %0x .\n",err,mem_block_temp);
	//       	return HIGH_LEVEL_TRY_LOCK;  //高水位线上锁
	//       	}
 //       else 
 //       	{
 //       		IMPORTANT_INFO("Check extern high_leve ok\n");
 //       		HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock))
 //       	}
 //       }           	
 //                   	
 //			return ALLOCTE_RECODR_TOO_TIMES;
 //		}
	}while(TRY_LOCK == err || HIGH_LEVEL_TRY_LOCK ==err );
	//if(0 == err)IMPORTANT_INFO("mem_table_allocate_record IS %ld\n",*record_ptr);
  DEBUG("mem_table_try_allocate END,record_ptr is %0x,record_num is %ld;\n",*record_ptr,(*record_ptr)->record_num);	
//	DEBUG("mem_table_allocate_record() ok;\n");	
	return 0;
	
}

//分配n个连续的空闲记录行，只能在一个块中分配
//inline int mem_table_try_allocate_n_record(struct mem_table_t *mem_table ,long n,/* out */struct record_t ** record_ptr,long * block_no)
//{
//	if( NULL == mem_table )  return ALLOCATE_N_RECORD_ERR_TABLE_IS_NULL;
//	if( n <= 0 ) return ALLOCATE_RECORD_ERR_NUM_IS_ZERO;
//	int i=0;
//	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
//	
//	HIGH_LEVEL_LOCK(&(mem_block_temp->high_level_lock));
//	
//  //遍历所有块,查找可以插入连续n个数据的内存块			
//	for(;i<mem_table->config.mem_block_used;++i)
//	{
//		if(mem_block_temp->space_start_addr + (n + mem_block_temp->high_level)* mem_table->record_size < mem_block_temp->space_end_addr - mem_table->record_size )break;
//			if(i!=mem_table->config.mem_block_used-1 )mem_block_temp = mem_block_temp->next;      //下一个块
//	}
//	
//	  //根据高水位线获取最新插入位置
//    
//   	  
//	// 找到可用的记录位置
//	*record_ptr = (struct record_t *) ( mem_block_temp->space_start_addr + mem_block_temp->high_level * mem_table->record_size );
//	//返回块的逻辑号
//	*block_no = mem_block_temp->block_no;
//	   
//
//       unsigned  long  high_level_temp = mem_block_temp->high_level;
//       // 高水位线未上升过，则上升n-1行,否则上升n行
//      // if ( mem_block_temp->high_level != 0 )  
//  	  // {
//            mem_block_temp->high_level += n;
//      // } 
//      // else
//      // 	    mem_block_temp->high_level += n-1;
//      HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock));
//	
//	// 没有连续的空闲空间，就自动扩表
//	if (i == mem_table->config.mem_block_used)
//{ 
//	     	      //自动扩表
//	     	      struct  mem_block_t * extern_mem_block;
//	     	      int err;
//	     	      err =  mem_table_extend(mem_table,&extern_mem_block);
//	     	      if(0 == err)
//	     	      	{
//	     	      			//自动扩表成功,记录插入扩展块中的第一个位置
//	     	      			if ( (extern_mem_block->space_end_addr-extern_mem_block->space_end_addr)>mem_table->record_size)
//	     	      		    {
//	     	      		      *record_ptr =(struct record_t *) extern_mem_block->space_start_addr; 	
//	     	      		      //扩展块高水位线递增
//                            HIGH_LEVEL_LOCK(&(extern_mem_block->high_level_lock));
//                            high_level_temp =  extern_mem_block->high_level;
//                            extern_mem_block->high_level +=(n-1);
//                            HIGH_LEVEL_UNLOCK(&(extern_mem_block->high_level_lock));
//                            //返回块的逻辑号
//														*block_no = extern_mem_block->block_no;
//                      }
//	     	      		  else return  MEM_TABLE_EXTEND_ERR;
//	     	      	}
//	     	      else if(TRY_LOCK == err)return TRY_LOCK;
//	     	      else return  MEM_TABLE_EXTEND_ERR;
//}
//     //对连续的空间初始化
//     long j = 0;
//     struct record_t ** record_temp = record_ptr;
//     for(;j<n;++j)
//     {
//     (*record_ptr)->record_num= high_level_temp +j ;
//		 (*record_temp)->is_used =  1;
//     (*record_temp)->last_free_pos =  0;
//     (*record_temp)->scn           =  0;
//     (*record_temp)->undo_record_ptr= 0;
//     (*record_temp)->data    =  (char *)(*record_ptr) + RECORD_HEAD_SIZE;  
//     row_lock_init(&((*record_temp)->row_lock)); //行锁初始化
//     *record_temp = (struct record_t *)(((off_t) record_temp + mem_table->record_size));
//     }
//	return 0;
//}
//
////分配一个空闲记录行
//inline int mem_table_allocate_n_record(struct mem_table_t *mem_table ,long n,/* out */struct record_t ** record_ptr,long * block_no)
//{
//	if( NULL == mem_table )  return ALLOCATE_N_RECORD_ERR_TABLE_IS_NULL;
//  int err;
//	do{
//		err= mem_table_try_allocate_n_record(mem_table , n,/* out */ record_ptr, block_no);
//		if(0!= err && TRY_LOCK != err )
//  	{
//  		return err;
//  	} 
//	}while(TRY_LOCK == err );
//	return 0;
//	
//}

//插入一个记录的数据
inline int mem_table_insert_record(struct mem_table_t *mem_table ,/* out */struct record_t ** record_ptr,long * block_no, /* in */char *buf)
{
	if( NULL == mem_table )
		{
			ERROR("INSERT_RECORD_ERR_TABLE_IS_NULL\n");
			return INSERT_RECORD_ERR_TABLE_IS_NULL;
		}  
	if( NULL == buf       )
		{
			ERROR("INSERT_RECORD_ERR_BUF_IS_NULL\n");
			return INSERT_RECORD_ERR_BUF_IS_NULL;	
		}  
	DEBUG("Enter mem_table_insert_record();\n");	
  int err;
  err= mem_table_allocate_record(mem_table ,/* out */ record_ptr,block_no);
  DEBUG("mem_table allocate a record,record_ptr is %0x ;\n",*record_ptr);	
	if(0!= err)
  {
  	ERROR("mem_table_allocate_record err \n");
  	return err;
  } 
  DEBUG("record_ptr->data is %0x ;\n",(*record_ptr)->data);	
	//redo_log .......
	
	row_wlock   (  &((*record_ptr)->row_lock) );
	memcpy      (  (*record_ptr)->data,  buf, mem_table->record_size - RECORD_HEAD_SIZE );
	row_wunlock (  &((*record_ptr)->row_lock) );
	return 0;
}

//删除全部数据
//将全部在用数据连入回收链表
inline int mem_table_delete_all(struct mem_table_t *mem_table )
{
	if( NULL == mem_table        ) return READ_RECORD_ERR_TABLE_IS_NULL;
	
  mem_table_lock(&(mem_table->table_locker) ); //表锁
  // 锁管理器
 	int i=0;
 	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
 	//遍历所有块,查找可以插入数据的内存块			
	for(;i<mem_table->config.mem_block_used;++i)
	{
		int j=0;
		struct record_t * record_temp;
		MEM_BLOCK_LOCK     (&(mem_block_temp->block_lock) ); //块锁
		for(;j<mem_block_temp->high_level ;++j)
		{
			record_temp = (struct record_t *) (mem_block_temp->space_start_addr + j* mem_table->record_size );
			row_wlock   (  &(record_temp->row_lock) );                 // 行锁
			if(record_temp->is_used)
				{   
					  record_temp->is_used = 0;
					    
            LIST_LOCK(&(mem_block_temp->mem_free_list.list_lock));  // 回收链表锁
					    //链入回收表	  
					  record_temp->last_free_pos = mem_block_temp->mem_free_list.head;
            mem_block_temp->mem_free_list.head = record_temp->record_num;
            
            LIST_UNLOCK  (&(mem_block_temp->mem_free_list.list_lock)); // 回收链表锁
				}
			row_wunlock   (  &(record_temp->row_lock) );                // 行锁
			
    }
    MEM_BLOCK_UNLOCK (&(mem_block_temp->block_lock) );//块锁
    mem_block_temp = mem_block_temp->next;           //下一个块
	}
	 //redo_log
	  mem_table_unlock(&(mem_table->table_locker));                    //表锁
	  
	return 0;
}

//删除全部数据
//清零回收链表
inline int mem_table_truncate(struct mem_table_t *mem_table )
{
	if( NULL == mem_table  ) return READ_RECORD_ERR_TABLE_IS_NULL;
	
  mem_table_lock(&(mem_table->table_locker) );         //表锁


  // 锁管理器
 	int i=0;
 	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
 	//遍历所有块,查找可以插入数据的内存块			
	for(;i<mem_table->config.mem_block_used;++i)
	{

		MEM_BLOCK_LOCK     (&(mem_block_temp->block_lock) ); //块锁
		mem_block_temp->high_level = 0;//回收高水位线
		
		LIST_LOCK(&(mem_block_temp->mem_free_list.list_lock));   // 回收链表锁
    mem_block_temp->mem_free_list.head = 0;                  //链表清零
    LIST_UNLOCK  (&(mem_block_temp->mem_free_list.list_lock));  //回收链表锁

		int j=0;
		struct record_t * record_temp;
		struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
		for(;j<mem_block_temp->high_level ;++j)
		{
			record_temp = (struct record_t *) (mem_block_temp->space_start_addr + j*  mem_table->record_size );
			if(record_temp->is_used)
			{
			row_wlock     (  &(record_temp->row_lock) );
			record_temp->is_used = 0;
			row_wunlock   (  &(record_temp->row_lock) );
		  }
    }    
    MEM_BLOCK_UNLOCK (&(mem_block_temp->block_lock) ); //块锁
    mem_block_temp = mem_block_temp->next;            //下一个块
	}		 
		//redo_log
	  mem_table_unlock(&(mem_table->table_locker));        //表锁
	return 0;
}


//强制删除全部数据
inline int mem_table_force_truncate(struct mem_table_t *mem_table )
{
	if( NULL == mem_table  ) return READ_RECORD_ERR_TABLE_IS_NULL;
	

  // 锁管理器
 	int i=0;
 	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
 	//遍历所有块,查找可以插入数据的内存块			
	for(;i<mem_table->config.mem_block_used;++i)
	{

		mem_block_temp->high_level = 0;//回收高水位线
		
    mem_block_temp->mem_free_list.head = 0;                  //链表清零

		int j=0;
		struct record_t * record_temp;
		struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
		for(;j<mem_block_temp->high_level ;++j)
		{
			record_temp = (struct record_t *) (mem_block_temp->space_start_addr + j*  mem_table->record_size );
			if(record_temp->is_used)
			{
			record_temp->is_used = 0;
		  }
    }    
    mem_block_temp = mem_block_temp->next;            //下一个块
	}		 
		//redo_log
	return 0;
}

//打开表
inline int mem_table_open( struct mem_table_t * mem_table)
{
	if(NULL == mem_table    )  return OPEN_MEM_TABLE_ERR_NULL_TABLE_PTR;
  DEBUG("Begin to open a mem_table.\n");
  DEBUG("config.mem_block_used is %d.\n",mem_table->config.mem_block_used);
	//加载共享内存
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	
  DEBUG("mem_block_temp->block_size is %d\n",mem_block_temp->block_size);
  DEBUG("(mem_table)->config.table_name1 is %s\n",(mem_table)->config.table_name );

	int i=0,err;
	for(;i<mem_table->config.mem_block_used;++i)
	{				

		//初始化块文件名		
		//块名= 表名_块号
		char tail_fix[256];
	  if( 0 == strlen(mem_block_temp->file_name))
		{
		sprintf(tail_fix,"%d\0",i);
		strcat(mem_block_temp->file_name,mem_table->config.table_name);
		strcat(mem_block_temp->file_name,"_");
		strcat(mem_block_temp->file_name,tail_fix);
		}
		DEBUG("mem_block_temp is %0x.\n",mem_block_temp);
		DEBUG("mem_block file_name is %s\n",mem_block_temp->file_name);
	  DEBUG("mem_block_temp->block_size is %d\n",mem_block_temp->block_size);

		INIT_MEM_BLOCK           (mem_block_temp);   //块描述符初始化
		if(0!=(err=mem_block_get_mem_from_os(mem_block_temp))){
			DEBUG("mem_block_get_mem_from_os err is %d.\n",err);
			return err;
			}  //分配内存
		DEBUG("mem_block_get_mem_from_os() ok\n");

		err = mem_block_mmap           (mem_block_temp);  //映射文件
		if(err != 0)break;
	  DEBUG("mem_block_mmap() ok\n");

		mem_block_temp = mem_block_temp->next;      //下一个块
	}
	if(err != 0)return err;
	return 0;
}	
	

	
	
//建表
inline int mem_table_create(
                             struct mem_table_t        **  mem_table,
                             struct mem_table_config_t *  mem_table_config
                             )
{
	
	if(NULL == mem_table_config                  )  return CREATE_MEM_TABLE_ERR_NULL_CONFIG_PTR;
	if(NULL == mem_table_config->fields_table    )  return CREATE_MEM_TABLE_ERR_NULL_FIELD_INFO_PTR;
	if(NULL == mem_table_config->mem_blocks_table)  return CREATE_MEM_TABLE_ERR_NULL_MEM_BLOCK;
	if(NULL == mem_table_config->table_name      )  return CREATE_MEM_TABLE_ERR_NO_NAME;
	if(strlen (mem_table_config->table_name)>=120)  return CREATE_MEM_TABLE_ERR_TOO_LONG;
	DEBUG("Begin to greate a mem_table.\n");
  
	DEBUG("mem_table_config->mem_blocks_table->file_name is %s\n",mem_table_config->mem_blocks_table->file_name );
  
	//建表
	(*mem_table) = (struct mem_table_t *)malloc(MEM_TABLE_SIZE);
	
  IMPORTANT_INFO("Create table ,table's addr is %0x \n",*mem_table);
	// 初始化基本信息
	INIT_MEM_TABLE((*mem_table));  
	memcpy(&((*mem_table)->config),mem_table_config,MEM_TABLE_CONFIG_SIZE);
	strcpy((*mem_table)->config.table_name , mem_table_config->table_name );   
	 allocate_table_no(&((*mem_table)->config.mem_table_no));//分配逻辑表号
	 set_table_no_addr((*mem_table)->config.mem_table_no,(void *) (*mem_table)); 
	//(*mem_table)->config.fields_table      = mem_table_config->fields_table;
	//(*mem_table)->config.field_used_num    = mem_table_config->field_used_num;
	//(*mem_table)->config.mem_blocks_table  = mem_table_config->mem_blocks_table;
	//(*mem_table)->config.mem_block_used    = mem_table_config->mem_block_used;
	
	regist_opened_table_name(mem_table_config->table_name,(*mem_table)->config.mem_table_no);
	
	DEBUG("(*mem_table)->config.table_name1 is %s\n",(*mem_table)->config.table_name );

	//填充表里的字段信息的大小
  fill_table_field_size ( *mem_table );  
  
  DEBUG("mem_table_config->mem_blocks_table block_size is %d\n",mem_table_config->mem_blocks_table->block_size );
  DEBUG("(*mem_table)->config.table_name2 is %s\n",(*mem_table)->config.table_name );

	//redo_log
	int err;
	err = mem_table_open(*mem_table);

	return err;
}
//映射回文件
inline int mem_table_msync(struct mem_table_t *  mem_table)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
	mem_table_lock(&(mem_table->table_locker) );       //表锁
  
	int i;
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	for(;i<mem_table->config.mem_block_used;++i)
	{
		MEM_BLOCK_LOCK              (&(mem_block_temp->block_lock));    //块锁
    mem_block_msync        (mem_block_temp);                   //按块同步回文件
		//redo_log....
    MEM_BLOCK_UNLOCK        (&(mem_block_temp->block_lock));    //块锁
    mem_block_temp = mem_block_temp->next;                     //下一个块
	}
	  mem_table_unlock (&(mem_table->table_locker));      //表锁
		if(mem_table)free(mem_table);
		return 0;
	}

//关表
inline int mem_table_close(struct mem_table_t *  mem_table)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
	DEBUG("Begin to close a mem_table：%s.\n",mem_table->config.table_name);

	mem_table_lock(&(mem_table->table_locker) );       //表锁
  			  
	long i = 0;
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	DEBUG("mem_block_temp is %0x.\n",mem_block_temp);
	for(;i<mem_table->config.mem_block_used;++i)
	{
		mem_block_munmap       (mem_block_temp);               		 //映射回文件
		mem_block_put_mem_to_os(mem_block_temp);               		 //释放内存
		//redo_log....
    mem_block_temp = mem_block_temp->next;                     //下一个块
	}

  	del_table_no_addr(mem_table->config.mem_table_no);      ////////////////////////////    
	  mem_table_unlock (&(mem_table->table_locker));      //表锁
	  DEBUG("Free mem_table_ptr.\n");

		mem_table_dest(&(mem_table->table_locker));
    table_rwlock_destroy(&(mem_table->rwlocker));
    
    unregist_table_name(mem_table->config.table_name);
    
	if(mem_table)
		{

			if(mem_table->config.fields_table    )
			{
				DEBUG("free (mem_table->config.fields_table)\n");
				free(mem_table->config.fields_table    );
			  

				mem_table->config.fields_table = NULL;
			}
			if(mem_table->config.mem_blocks_table)
			{
			  DEBUG("free(mem_table->config.mem_blocks_table)\n");
				free(mem_table->config.mem_blocks_table);
				mem_table->config.mem_blocks_table= NULL;
			}
			
			free(mem_table);
			DEBUG("free(mem_table).\n");
			mem_table = NULL;
		}
		DEBUG("mem_table_close() end.\n");

		return 0;
	}

//扩表
inline int mem_table_extend( struct mem_table_t * mem_table, struct  mem_block_t ** out_mem_block)
{
	if(NULL == mem_table )  return OPEN_MEM_TABLE_ERR_NULL_TABLE_PTR;
	if(0 == mem_table->config.auto_extend ) return MEM_TABLE_EXTEND_ERR_NOT_ALLOW_EXTEND;
	if(NULL == mem_table->config.mem_blocks_table->file_name)
		{
			ERROR("MEM_TABLE_EXTEND_ERR_NAME_IS_NULL\n");
			return MEM_TABLE_EXTEND_ERR_NAME_IS_NULL;
		}
	
  if(0!=mem_table_trylock(&(mem_table->table_locker) ))  //表锁
  {
  return TRY_LOCK;
  }
  IMPORTANT_INFO("Try to extend table <%s>\n",mem_table->config.table_name);
  mem_table->is_externing = 1;
	struct  mem_block_t * extend_table = (struct  mem_block_t *)malloc(MEM_BLOCK_HEAD_SIZE);

	//拼入扩展块块大小
	char file_name[256]="";
	//先拼入第一个文件的文件名
	strcpy(file_name,mem_table->config.mem_blocks_table->file_name);
	strcat(file_name,"_");
	//再拼入系统时间
	GetTimeForNAME(file_name)  ;
	//获得扩展块文件名
	DEBUG("extend_table->file_name is %s\n",extend_table->file_name);
	if(extend_table->file_name == NULL)
		{
			ERROR("MEM_TABLE_EXTEND_ERR_NAME_IS_NULL\n");
			mem_table_unlock(&(mem_table->table_locker));  //解表锁
			return MEM_TABLE_EXTEND_ERR_NAME_IS_NULL;
			
		}
	
	mem_block_config( extend_table ,/*long block_no ,*/ mem_table->config.extend_block_size , file_name ) ;
	//初始化扩展块
	INIT_MEM_BLOCK           (extend_table);   //块描述符初始化
	mem_block_get_mem_from_os(extend_table);   //分配内存
	mem_block_mmap           (extend_table);   //映射文件
	
	//找到块表中最后一个块
  struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
  int i = 0;
 // IMPORTANT_INFO("mem_table->config.mem_block_used is %d\n",mem_table->config.mem_block_used);
 // IMPORTANT_INFO("BEFORE Extend table,mem_block_temp is %0x\n",mem_block_temp);
  
  for(;i<mem_table->config.mem_block_used-1;++i)
  {
  	 //IMPORTANT_INFO("mem_table->config.mem_block_used is %d\n",mem_table->config.mem_block_used);
  	 mem_block_temp=mem_block_temp->next; 
  }
  //扩展块链入最后一个块
  mem_block_temp->next = extend_table;
  
//  DEBUG("extend_table->high_level_lock is %0x\n",extend_table->high_level_lock );
  
  //使用块数++
	
	 mem_table->is_externing = 0;
   *out_mem_block = extend_table;                  //出参为新扩的块
   ++(mem_table->config.mem_block_used);
   mem_table_unlock(&(mem_table->table_locker));  //解表锁.
   IMPORTANT_INFO("Extend table ok! mem_table has used [%d] blocks.\n",mem_table->config.mem_block_used);

   //IMPORTANT_INFO("Extend table ok!,Extend table is %0x\n",extend_table);
   
   
	return 0;
}	


// 共享锁
int mem_table_rwlock_by_reader(struct mem_table_t *  mem_table)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
  return table_rwlock_rdlock(&(mem_table->rwlocker));
}

//解共享锁
int mem_table_rwunlock_by_reader(struct mem_table_t *  mem_table)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
  return table_rwlock_wrlock(&(mem_table->rwlocker));
}

//独占锁
int mem_table_rwlock_by_writer(struct mem_table_t *  mem_table, long long  trans_no)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
  int ret;
  mem_table->writer_trans_no = trans_no;
  ret = table_rwlock_wrlock(&(mem_table->rwlocker));
  
  return ret;
}

//解独占锁
int mem_table_rwunlock_by_writer(struct mem_table_t *  mem_table,  long long  trans_no)
{
	if(NULL == mem_table    )  return CREATE_MEM_TABLE_ERR_NULL_TABLE_PTR;
  if(mem_table->writer_trans_no != trans_no)
  	{
  		 ERROR("The Trans %d did not lock table %s ,so it can not unlock it!\n",trans_no,mem_table->config.table_name);
  		 return UNLOCK_FAILED;
  	}
  int ret;
  mem_table->writer_trans_no = -1;
  ret = table_rwlock_wrlock(&(mem_table->rwlocker));
  return ret;
}
#ifdef __cplusplus

}

#endif

#endif 
