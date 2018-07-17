#ifndef MEM_BLOCK_NO_MANAGER_T
#define MEM_BLOCK_NO_MANAGER_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>
#include <stdlib.h>  
#include "rwlock.h"
#include<string.h>
#include"mem_block_t.h"
#include"../util/str_num_map.h"

#define MAX_MEM_BLOCK_NO  (1024*1024-1)
#define INIT_MEM_BLOCK_NO (1023)

//暂时用互斥锁表示块锁
#define MEM_BLOCK_NO_LOCK_T             rwlock_t
#define MEM_BLOCK_NO_LOCK(x)            rwlock_wlock(x);
#define MEM_BLOCK_NO_UNLOCK(x)          rwlock_wunlock(x);
//#define RBTREE_TRYLOCK(x)         pthread_spin_trylock(x) 
#define MEM_BLOCK_NO_RLOCK(x)            rwlock_rlock(x);
#define MEM_BLOCK_NO_RUNLOCK(x)          rwlock_runlock(x);   
#define MEM_BLOCK_NO_LOCK_INIT(x)        rwlock_init((x));


// 扩展策略
#define    DOUBLE_EXTEND           1

#define ERR_BLOCK_NO_LESS_ZERO  41001
#define ERR_BLOCK_NOT_EXIST     41002
#define ERR_BLOCK_BAD_ADDR      41003
#define ERR_BLOCK_NAME_IS_NULL  41004

typedef struct mem_block_no_manager_t
{
	void                  ** mem_block_no_table;  // (块号,地址) 速查表 存储块号对应地址的动态数组
	MEM_BLOCK_NO_LOCK_T   locker;                 // 互斥锁
	long                  max_num;               // 可以存储的最大地址
	long                  cur_num;               // 当前使用的最大地址
	int                   extend_police;         // 扩展策略，默认使用二倍扩展
	
} __attribute__ ((packed, aligned (64))) mem_block_no_manager_t;

static mem_block_no_manager_t mem_block_no_manager;


int save_cur(char * str_path)
{
		 MEM_BLOCK_NO_LOCK  (&(mem_block_no_manager.locker));  //上锁

FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
sprintf(buf,"%d",mem_block_no_manager.cur_num);
int ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
int ret2 =  fclose( fp );
	 MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁

return ret|ret2;
}


int load_cur(char * str_path)
{
	int ret=-1;
	int ret2=-1;
if(!access(str_path,0)){
MEM_BLOCK_NO_LOCK  (&(mem_block_no_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "rt");  // 以二进制可写方式打开stu.dat文件
ret = !(fscanf(fp,"%d",&(mem_block_no_manager.cur_num)) == 1);
DEBUG("mem_block_no_manager.cur_num is %d\n",mem_block_no_manager.cur_num);
ret2 =  fclose( fp );
MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁
}
return ret|ret2;
}


//初始化速查表
inline int init_mem_block_no_manager()
{
	DEBUG("in init_mem_block_no_manager()\n");
	MEM_BLOCK_NO_LOCK_INIT(&(mem_block_no_manager.locker));
	mem_block_no_manager.mem_block_no_table = (void**)malloc(INIT_MEM_BLOCK_NO*(sizeof(void *)));
	mem_block_no_manager.max_num            = INIT_MEM_BLOCK_NO;
	mem_block_no_manager.cur_num            = 0;
	mem_block_no_manager.extend_police      = DOUBLE_EXTEND;
	return 0;
}

//销毁速查表
inline int dest_mem_block_no_manager()
{
  free(mem_block_no_manager.mem_block_no_table);
  return 0;
}


//扩展速查表
inline int extend_mem_block_no_manager()
{
	MEM_BLOCK_NO_LOCK(&(mem_block_no_manager.locker));  //上锁
	
	void   * old =  mem_block_no_manager.mem_block_no_table;
	void   * new_;
	
	//根据策略重新分配速查表内存
	switch(mem_block_no_manager.extend_police)
	{
		case DOUBLE_EXTEND:
	  new_ =  malloc( 2*(mem_block_no_manager.max_num)*(sizeof(void *)));
	  break;
	
  }
  memcpy(new_,old,mem_block_no_manager.max_num);
  mem_block_no_manager.max_num            =  2*(mem_block_no_manager.max_num);
	mem_block_no_manager.cur_num            =  mem_block_no_manager.max_num;
	mem_block_no_manager.mem_block_no_table =  (void**)new_;
  free(old);
  
  MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker)); //解锁
  return 0 ;
}


//获取块号对应的地址
inline int get_block_no_addr(long block_no,void ** addr)
{
	if(block_no<0){
		ERROR("ERR_BLOCK_NO_LESS_ZERO\n");
		return ERR_BLOCK_NO_LESS_ZERO;
	} 
	if(block_no> mem_block_no_manager.cur_num ){
		 ERROR("ERR_BLOCK_NOT_EXIST\n");
		 return ERR_BLOCK_NOT_EXIST;
	} 
	
	 MEM_BLOCK_NO_RLOCK  (&(mem_block_no_manager.locker));  //上锁
	 *addr = (mem_block_no_manager.mem_block_no_table[block_no]);
	 MEM_BLOCK_NO_RUNLOCK(&(mem_block_no_manager.locker));  //解锁
	if( 0 == addr ){
		 ERROR("ERR_BLOCK_BAD_ADDR\n");
		 return ERR_BLOCK_BAD_ADDR;
	} 
	return 0;
	
}

//设置块号对应的地址
inline int set_block_no_addr(long block_no,void * addr)
{
	if(block_no<0){
		ERROR("ERR_BLOCK_NO_LESS_ZERO\n");
		return ERR_BLOCK_NO_LESS_ZERO;
	} 
	if(block_no> mem_block_no_manager.cur_num ){
		ERROR("ERR_BLOCK_NOT_EXIST\n");
		return ERR_BLOCK_NOT_EXIST;
	}  
	
	 MEM_BLOCK_NO_LOCK  (&(mem_block_no_manager.locker));  //上锁
	 mem_block_no_manager.mem_block_no_table[block_no] = addr;
	 MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int del_block_no_addr(long block_no)
{
	if(block_no<0) return ERR_BLOCK_NO_LESS_ZERO;
	if(block_no> mem_block_no_manager.cur_num )  return ERR_BLOCK_NOT_EXIST;
	
	 MEM_BLOCK_NO_LOCK  (&(mem_block_no_manager.locker));  //上锁
	  mem_block_no_manager.mem_block_no_table[block_no]  = 0;
	 MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁
	return 0;
	
}


// 分配唯一块号
inline int allocate_block_no(long * block_no)
{	
	 MEM_BLOCK_NO_LOCK  (&(mem_block_no_manager.locker));  //上锁
	 
	 ++(mem_block_no_manager.cur_num);
	 DEBUG("mem_block_no_manager.cur_num is %d\n",mem_block_no_manager.cur_num);

	 if(mem_block_no_manager.cur_num > mem_block_no_manager.max_num )
	 	{
	 		 MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁
	 		 int err;
	 		 err = extend_mem_block_no_manager();
	 		 if( 0!= err )return err;
	 		
	 	}
	   *block_no =  mem_block_no_manager.cur_num;	 
	   MEM_BLOCK_NO_UNLOCK(&(mem_block_no_manager.locker));  //解锁
	   
	return 0;
	
}
//////////////////////////////////////////////////////
static str_num_map_t block_name_manager;

// 注册打开的文件
static int regist_opened_block_name(char * block_name,long long no)
{
if(NULL == block_name)
		{
			ERROR("ERR_BLOCK_NAME_IS_NULL\n");
			return ERR_BLOCK_NAME_IS_NULL;
		}
	if(NULL == block_name_manager.str_num_map_table)init_str_num_map_manager(&block_name_manager);
	str_num_t * fe = (str_num_t *)malloc(STR_NUM_SIZE);
	fe->no   = no;
	strcpy(fe->__str,block_name);
	fe->next = 0;
	DEBUG("STR IS %s,no is %d\n",block_name,no);
	return set_str_num_map_addr(&block_name_manager,block_name,fe);
	  return 0;
}

// 注销打开的文件
static int unregist_block_name(char * block_name)
{
if(NULL == block_name)
{
	ERROR("ERR_BLOCK_NAME_IS_NULL\n");
	return ERR_BLOCK_NAME_IS_NULL;
}
		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&block_name_manager,block_name,&addr,&addr_pre)))
	{
		return err;
	}
	return del_str_num_map_addr(&block_name_manager,block_name);
	return 0;
}


// 查找打开的文件
static int search_block_name(char * block_name,long long * no)
{
if(NULL == block_name)
		{
			ERROR("ERR_BLOCK_NAME_IS_NULL\n");
			return ERR_BLOCK_NAME_IS_NULL;
		}
DEBUG("search_block_name %s\n",block_name);		
		str_num_t * addr;
		str_num_t * addr_pre;
int err;
if(0!=(err =  get_str_num_map_addr(&block_name_manager,block_name,&addr,&addr_pre)))
	{
		ERROR("Not Found block_name %s\n",block_name);
		return err;
	}
	if( NULL == addr)
		{
					ERROR("Not Found block_name %s\n",block_name);
					return 100;
		}
	*no = addr->no;
	return 0;
	
}
#ifdef __cplusplus

}

#endif

#endif 