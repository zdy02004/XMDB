#ifndef MEM_INDEX_NO_MANAGER_T
#define MEM_INDEX_NO_MANAGER_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>
#include <stdlib.h>  
#include "rwlock.h"
#include<string.h>
#include"mem_block_t.h"
#include"../util/str_num_map.h"


#define MAX_MEM_INDEX_NO  (1024*1024-1)
#define INIT_MEM_INDEX_NO (1024-1     )

//暂时用互斥锁表示块锁
#define MEM_INDEX_NO_LOCK_T             rwlock_t
#define MEM_INDEX_NO_LOCK(x)            rwlock_wlock(x);
#define MEM_INDEX_NO_UNLOCK(x)          rwlock_wunlock(x); 
//#define RBTREE_TRYLOCK(x)         pthread_spin_trylock(x) 
#define MEM_INDEX_NO_RLOCK(x)            rwlock_rlock(x);
#define MEM_INDEX_NO_RUNLOCK(x)          rwlock_runlock(x);   
#define MEM_INDEX_NO_LOCK_INIT(x)        rwlock_init((x));


// 扩展策略
#define    DOUBLE_EXTEND           1

#define ERR_INDEX_NO_LESS_ZERO  42001
#define ERR_INDEX_NOT_EXIST     42002
#define ERR_INDEX_BAD_ADDR      42003
#define ERR_INDEX_NAME_IS_NULL  42004

typedef struct mem_index_no_manager_t
{
	void                  ** mem_index_no_table;  // (块号,地址) 速查表 存储块号对应地址的动态数组
	MEM_INDEX_NO_LOCK_T   locker;              // 互斥锁
	long                  max_num;               // 可以存储的最大地址
	long                  cur_num;               // 当前使用的最大地址
	int                   extend_police;         // 扩展策略，默认使用二倍扩展
	
} __attribute__ ((packed, aligned (64))) mem_index_no_manager_t;

static mem_index_no_manager_t mem_index_no_manager;


int save_index_cur(char * str_path)
{
MEM_INDEX_NO_LOCK  (&(mem_index_no_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
sprintf(buf,"%d",mem_index_no_manager.cur_num);
int ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
int ret2 =  fclose( fp );
MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁

return ret|ret2;
}


int load_index_cur(char * str_path)
{
	int ret=-1;
	int ret2=-1;
if(!access(str_path,0)){
MEM_INDEX_NO_LOCK  (&(mem_index_no_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "rt");  // 以二进制可写方式打开stu.dat文件
ret = !(fscanf(fp,"%d",&(mem_index_no_manager.cur_num)) == 1);
DEBUG("mem_index_no_manager.cur_num is %d\n",mem_block_no_manager.cur_num);
ret2 =  fclose( fp );
MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁
}
return ret|ret2;
}



//初始化速查表
inline int init_mem_index_no_manager()
{
	MEM_INDEX_NO_LOCK_INIT(&(mem_index_no_manager.locker));
	mem_index_no_manager.mem_index_no_table = (void**)malloc(INIT_MEM_INDEX_NO*(sizeof(void *)));
	mem_index_no_manager.max_num            = INIT_MEM_INDEX_NO;
	mem_index_no_manager.cur_num            = 0;
	mem_index_no_manager.extend_police      = DOUBLE_EXTEND;
	return 0;
}

//销毁速查表
inline int dest_mem_index_no_manager()
{
  free(mem_index_no_manager.mem_index_no_table);
  return 0;
}

//扩展速查表
inline int extend_mem_index_no_manager()
{
	MEM_INDEX_NO_LOCK(&(mem_index_no_manager.locker));  //上锁
	
	void   * old =  mem_index_no_manager.mem_index_no_table;
	void   * _new;
	
	//根据策略重新分配速查表内存
	switch(mem_index_no_manager.extend_police)
	{
		case DOUBLE_EXTEND:
	  _new =  malloc( 2*(mem_index_no_manager.max_num)*(sizeof(void *)));
	  break;
	
  }
  memcpy(_new,old,mem_index_no_manager.max_num);
  mem_index_no_manager.max_num            =  2*(mem_index_no_manager.max_num);
	mem_index_no_manager.cur_num            =  mem_index_no_manager.max_num;
	mem_index_no_manager.mem_index_no_table =  (void**)_new;
  free(old );
  
  MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker)); //解锁
  return 0 ;
}


//获取块号对应的地址
inline int get_index_no_addr(long index_no,void ** addr)
{
	if(index_no<0)
		{
			ERROR("ERR_INDEX_NO_LESS_ZERO\n");
			return ERR_INDEX_NO_LESS_ZERO;
		} 
	if(index_no> mem_index_no_manager.cur_num )
		{
			ERROR("ERR_INDEX_NOT_EXIST\n");
			return ERR_INDEX_NOT_EXIST;
		}  
	
	 MEM_INDEX_NO_RLOCK  (&(mem_index_no_manager.locker));  //上锁
	 *addr = (mem_index_no_manager.mem_index_no_table[index_no]);
	 MEM_INDEX_NO_RUNLOCK(&(mem_index_no_manager.locker));  //解锁
	if( 0 == addr )
		{
			ERROR("ERR_INDEX_BAD_ADDR\n");
			return ERR_BLOCK_BAD_ADDR;
		}  
	return 0;
	
}

//设置块号对应的地址
inline int set_index_no_addr(long index_no,void * addr)
{
	if(index_no<0)
		{
			ERROR("ERR_INDEX_NO_LESS_ZERO\n");
			return ERR_INDEX_NO_LESS_ZERO;
		} 
	if(index_no> mem_index_no_manager.cur_num )  return ERR_INDEX_NOT_EXIST;
	
	 MEM_INDEX_NO_LOCK  (&(mem_index_no_manager.locker));  //上锁
	 mem_index_no_manager.mem_index_no_table[index_no] = addr;
	 MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int del_index_no_addr(long index_no)
{
	if(index_no<0) return ERR_INDEX_NO_LESS_ZERO;
	if(index_no> mem_index_no_manager.cur_num )  return ERR_INDEX_NOT_EXIST;
	 MEM_INDEX_NO_LOCK  (&(mem_index_no_manager.locker));  //上锁
	  mem_index_no_manager.mem_index_no_table[index_no]  = 0;
	 MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁
	return 0;
	
}


// 分配唯一索引号
inline int allocate_index_no(long * index_no)
{	
	 MEM_INDEX_NO_LOCK  (&(mem_index_no_manager.locker));  //上锁
	 
	 ++mem_index_no_manager.cur_num;
	 if(mem_index_no_manager.cur_num > mem_index_no_manager.max_num )
	 	{
	 		 MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁
	 		 int err;
	 		 err = extend_mem_index_no_manager();
	 		 if( 0!= err )return err;
	 		
	 	}
	   *index_no =  mem_index_no_manager.cur_num;	 
	   MEM_INDEX_NO_UNLOCK(&(mem_index_no_manager.locker));  //解锁
	   DEBUG("mem_index_no_manager.cur_num is %d\n",mem_index_no_manager.cur_num);

	return 0;
	
}
//////////////////////////////////////////////////////
static str_num_map_t index_name_manager;

// 注册打开的文件
static int regist_opened_index_name(char * index_name,long long no)
{
if(NULL == index_name)
		{
			ERROR("ERR_INDEX_NAME_IS_NULL\n");
			return ERR_INDEX_NAME_IS_NULL;
		}
	if(NULL == index_name_manager.str_num_map_table)init_str_num_map_manager(&index_name_manager);
	str_num_t * fe = (str_num_t *)malloc(STR_NUM_SIZE);
	fe->no   = no;
	strcpy(fe->__str,index_name);
	fe->next = 0;
	return set_str_num_map_addr(&index_name_manager,index_name,fe);
	  return 0;
}

// 注销打开的文件
static int unregist_index_name(char * index_name)
{
if(NULL == index_name)
{
	ERROR("ERR_INDEX_NAME_IS_NULL\n");
	return ERR_INDEX_NAME_IS_NULL;
}
		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&index_name_manager,index_name,&addr,&addr_pre)))
	{
		return err;
	}
	return del_str_num_map_addr(&index_name_manager,index_name);
	return 0;
}


// 查找打开的文件
static int search_index_name(char * index_name,long long * no)
{
if(NULL == index_name)
		{
			ERROR("ERR_INDEX_NAME_IS_NULL\n");
			return ERR_INDEX_NAME_IS_NULL;
		}
		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&index_name_manager,index_name,&addr,&addr_pre)))
	{
		ERROR("Not Found index_name %s\n",index_name);
		return err;
	}
	*no = addr->no;
	return 0;
	
}
#ifdef __cplusplus

}

#endif

#endif 