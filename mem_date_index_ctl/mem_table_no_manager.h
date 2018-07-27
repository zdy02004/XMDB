#ifndef MEM_TABLE_NO_MANAGER_T
#define MEM_TABLE_NO_MANAGER_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>
#include <stdlib.h>  
#include "rwlock.h"
#include<string.h>
#include"mem_block_t.h"
#include"../util/str_num_map.h"

#define MAX_MEM_TABLE_NO  (1024*1024-1)
#define INIT_MEM_TABLE_NO (1024-1     )

//暂时用互斥锁表示块锁
#define MEM_TABLE_NO_LOCK_T             rwlock_t
#define MEM_TABLE_NO_LOCK(x)            rwlock_wlock(x);
#define MEM_TABLE_NO_UNLOCK(x)          rwlock_wunlock(x); 
//#define RBTREE_TRYLOCK(x)         pthread_spin_trylock(x) 
#define MEM_TABLE_NO_RLOCK(x)            rwlock_rlock(x);
#define MEM_TABLE_NO_RUNLOCK(x)          rwlock_runlock(x);   
#define MEM_TABLE_NO_LOCK_INIT(x)        rwlock_init((x));


// 扩展策略
#define    DOUBLE_EXTEND           1

#define ERR_TABLE_NO_LESS_ZERO  43001
#define ERR_TABLE_NOT_EXIST     43002
#define ERR_TABLE_BAD_ADDR      43003
#define ERR_TABLE_NAME_IS_NULL  43004

typedef struct mem_table_no_manager_t
{
	void                  ** mem_table_no_table;  // (块号,地址) 速查表 存储块号对应地址的动态数组
	MEM_TABLE_NO_LOCK_T   locker;              // 互斥锁
	long                  max_num;               // 可以存储的最大地址
	long                  cur_num;               // 当前使用的最大地址
	int                   extend_police;         // 扩展策略，默认使用二倍扩展
	
} __attribute__ ((packed, aligned (64))) mem_table_no_manager_t;

static mem_table_no_manager_t mem_table_no_manager;


int save_table_cur(char * str_path)
{
MEM_TABLE_NO_LOCK  (&(mem_table_no_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
sprintf(buf,"%d",mem_table_no_manager.cur_num);
int ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
int ret2 =  fclose( fp );
MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁

return ret|ret2;
}


int load_table_cur(char * str_path)
{
int ret=-1;
int ret2=-1;
if(!access(str_path,0)){
MEM_TABLE_NO_LOCK  (&(mem_table_no_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
DEBUG("fopen(str_path %s\n",str_path);
fp = fopen(str_path, "rt");  // 以二进制可写方式打开stu.dat文件
ret = !(fscanf(fp,"%d",&(mem_table_no_manager.cur_num)) == 1);
DEBUG("mem_table_no_manager.cur_num is %d\n",mem_table_no_manager.cur_num);
ret2 =  fclose( fp );
MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁
}
return ret|ret2;
}

//初始化速查表
inline int init_mem_table_no_manager()
{
	MEM_TABLE_NO_LOCK_INIT(&(mem_table_no_manager.locker));
	mem_table_no_manager.mem_table_no_table = (void**)malloc(INIT_MEM_TABLE_NO*(sizeof(void *)));
	mem_table_no_manager.max_num            = INIT_MEM_TABLE_NO;
	mem_table_no_manager.cur_num            = 0;
	mem_table_no_manager.extend_police      = DOUBLE_EXTEND;
	return 0;
}

//销毁速查表
inline int dest_mem_table_no_manager()
{
  free(mem_table_no_manager.mem_table_no_table);
  return 0;
}

//扩展速查表
inline int extend_mem_table_no_manager()
{
	MEM_TABLE_NO_LOCK(&(mem_table_no_manager.locker));  //上锁
	
	void   * old =  mem_table_no_manager.mem_table_no_table;
	void   * _new;
	
	//根据策略重新分配速查表内存
	switch(mem_table_no_manager.extend_police)
	{
		case DOUBLE_EXTEND:
	  _new =  malloc( 2*(mem_table_no_manager.max_num)*(sizeof(void *)));
	  break;
	
  }
  memcpy(_new,old,mem_table_no_manager.max_num);
  mem_table_no_manager.max_num            =  2*(mem_table_no_manager.max_num);
	mem_table_no_manager.cur_num            =  mem_table_no_manager.max_num;
	mem_table_no_manager.mem_table_no_table = (void**)_new;
  free(old);
  
  MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker)); //解锁
  return 0 ;
}


//获取块号对应的地址
inline int get_table_no_addr(long table_no,void ** addr)
{
	DEBUG( "get_table_no_addr(%ld)\n",table_no );
	if(table_no<0)
		{
			ERROR("ERR_TABLE_NO_LESS_ZERO\n");
			return ERR_TABLE_NO_LESS_ZERO;
		} 
	if(table_no> mem_table_no_manager.cur_num ){
		ERROR("ERR_TABLE_NO_LESS_ZERO\n");
		return ERR_TABLE_NOT_EXIST;
	}  
	
	 MEM_TABLE_NO_RLOCK  (&(mem_table_no_manager.locker));  //上锁
	 *addr = (mem_table_no_manager.mem_table_no_table[table_no]);
	 MEM_TABLE_NO_RUNLOCK(&(mem_table_no_manager.locker));  //解锁
 	if( 0 == addr ){
		ERROR("ERR_BLOCK_BAD_ADDR\n");
		return ERR_BLOCK_BAD_ADDR;
	}  
	
	DEBUG( "Leave get_table_no_addr()\n" );
	return 0;
	
}

//设置块号对应的地址
inline int set_table_no_addr(long table_no,void * addr)
{
	if(table_no<0){
		ERROR("ERR_TABLE_NO_LESS_ZERO\n");
		return ERR_TABLE_NO_LESS_ZERO;
	} 
	if(table_no> mem_table_no_manager.cur_num )
		{
			ERROR("ERR_TABLE_NOT_EXIST\n");
			return ERR_TABLE_NOT_EXIST;
		}  
	 DEBUG("mem_table save addr is (%ld,%0x)\n",table_no,addr);
	 MEM_TABLE_NO_LOCK  (&(mem_table_no_manager.locker));  //上锁
	 mem_table_no_manager.mem_table_no_table[table_no] = addr;
	 MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int del_table_no_addr(long table_no)
{
	if(table_no<0){
		ERROR("ERR_TABLE_NO_LESS_ZERO\n");
		return ERR_TABLE_NO_LESS_ZERO;
	} 
	if(table_no> mem_table_no_manager.cur_num ){
		 ERROR("ERR_TABLE_NOT_EXIST\n");
		 return ERR_TABLE_NOT_EXIST;
	} 
	
	 MEM_TABLE_NO_LOCK  (&(mem_table_no_manager.locker));  //上锁
	  mem_table_no_manager.mem_table_no_table[table_no]  = 0;
	 MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁
	return 0;
	
}


// 分配唯一块号
inline int allocate_table_no(long * table_no)
{	
	 MEM_TABLE_NO_LOCK(&(mem_table_no_manager.locker));  //上锁
	 
	 ++mem_table_no_manager.cur_num;
	 if(mem_table_no_manager.cur_num > mem_table_no_manager.max_num )
	 	{
	 		 MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁
	 		 int err;
	 		 err = extend_mem_table_no_manager();
	 		 if( 0!= err ){
		    ERROR("extend_mem_table_no_manager err is %ld\n",err );
	 		 	return err;
	 		}
	 	}
	 	   *table_no =  mem_table_no_manager.cur_num;	 
	   MEM_TABLE_NO_UNLOCK(&(mem_table_no_manager.locker));  //解锁
	DEBUG("mem_table_no_manager.cur_num is %d\n",mem_table_no_manager.cur_num);
   
	return 0;
	
}


static str_num_map_t table_name_manager;

// 注册打开的文件
static int regist_opened_table_name(char * table_name,long long no)
{
if(NULL == table_name)
		{
			ERROR("ERR_TABLE_NAME_IS_NULL\n");
			return ERR_TABLE_NAME_IS_NULL;
		}
	if(NULL == table_name_manager.str_num_map_table)init_str_num_map_manager(&table_name_manager);
	str_num_t * fe = (str_num_t *)malloc(STR_NUM_SIZE);
	fe->no   = no;
	strcpy(fe->__str,table_name);
	fe->next = 0;
	return set_str_num_map_addr(&table_name_manager,table_name,fe);
	  return 0;
}

// 注销打开的文件
static int unregist_table_name(char * table_name)
{
if(NULL == table_name)
{
	ERROR("ERR_TABLE_NAME_IS_NULL\n");
	return ERR_TABLE_NAME_IS_NULL;
}
		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&table_name_manager,table_name,&addr,&addr_pre)))
	{
		return err;
	}
	return del_str_num_map_addr(&table_name_manager,table_name);
	return 0;
}


// 查找打开的文件
static int search_table_name(char * table_name,long long * no)
{
if(NULL == table_name)
		{
			ERROR("ERR_TABLE_NAME_IS_NULL\n");
			return ERR_TABLE_NAME_IS_NULL;
		}
		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&table_name_manager,table_name,&addr,&addr_pre)))
	{
		ERROR("Not Found table_name %s\n",table_name);
		return err;
	}
	*no = addr->no;
	return 0;
	
}


#ifdef __cplusplus

}

#endif

#endif 