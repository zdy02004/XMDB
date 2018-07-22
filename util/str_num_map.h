#ifndef STR_NUM_MAP_T
#define STR_NUM_MAP_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>
#include <stdlib.h>  
#include "../mem_date_index_ctl/rwlock.h"
#include<string.h>



#define MAX_NO_MAP  (1024*1024-1)
#define INIT_NO_MAP (1023)

//暂时用互斥锁表示块锁
#define STR_NUM_MAP_LOCK_T              rwlock_t
#define STR_NUM_MAP_LOCK(x)             rwlock_wlock(x);
#define STR_NUM_MAP_UNLOCK(x)           rwlock_wunlock(x);
#define STR_NUM_MAP_RLOCK(x)            rwlock_rlock(x);
#define STR_NUM_MAP_RUNLOCK(x)          rwlock_runlock(x);   
#define STR_NUM_MAP_LOCK_INIT(x)        rwlock_init((x));


// 扩展策略
#define    DOUBLE_EXTEND           1

#define ERR_STR_NUM_IS_NULL     410010
#define ERR_STR_NUM_MAP_NULL 		410020
#define ERR_STR_NUM_BAD_ADDR		410030
#define MAX_IS_ZERO             410040
typedef struct str_num_t
{
char __str[256];
long long  no;
struct str_num_t *next;
	
} __attribute__ ((packed, aligned (64))) str_num_t;

#define STR_NUM_SIZE sizeof(str_num_t)

typedef struct str_num_map_t
{
	str_num_t        ** str_num_map_table;  // (块号,地址) 速查表 存储块号对应地址的动态数组
	STR_NUM_MAP_LOCK_T     locker;                 // 互斥锁
	long                  max_num;               // 可以存储的最大地址
	long                  cur_num;               // 当前使用的最大地址
	int                   extend_police;         // 扩展策略，默认使用二倍扩展
	
} __attribute__ ((packed, aligned (64))) str_num_map_t;

#define STR_NUM_MAP_SIZE sizeof(str_num_map_t)
#define CREATE_STR_NUM_MAP   (str_num_t *)(malloc(STR_NUM_MAP_SIZE));

// BKDR Hash Function
static inline unsigned int ___BKDRHashForFile(char *str)
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
static inline unsigned int ___str_hash_fun_for_file(char * key,long max)
{
	if( NULL == key       )
		{
			ERROR("ERR_STR_NUM_IS_NULL\n");
			return ERR_STR_NUM_IS_NULL;
		}
		if(   0 == max      )
		{
			ERROR("There is no table registed! \n");
			return ERR_STR_NUM_IS_NULL;
		}	

	//先平均分布，再取余数	
	return  ___BKDRHashForFile(key) % ( max ) ;

}

int str_num_map_manager_save_cur(str_num_map_t *str_num_map_manager,char * str_path)
{
STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
sprintf(buf,"%d",str_num_map_manager->cur_num);
int ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
int ret2 =  fclose( fp );
STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁

return ret|ret2;
}


int str_num_map_manager_load_cur(str_num_map_t *str_num_map_manager,char * str_path)
{
	int ret=-1;
	int ret2=-1;
if(!access(str_path,0)){
STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "rt");  // 以二进制可写方式打开stu.dat文件
ret = !(fscanf(fp,"%d",&(str_num_map_manager->cur_num)) == 1);
DEBUG("str_num_map_manager->cur_num is %d\n",str_num_map_manager->cur_num);
ret2 =  fclose( fp );
STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
}
return ret|ret2;
}


//初始化速查表
inline int init_str_num_map_manager(str_num_map_t *str_num_map_manager)
{
	DEBUG("in init_str_num_map_manager()\n");
	STR_NUM_MAP_LOCK_INIT(&(str_num_map_manager->locker));
	str_num_map_manager->str_num_map_table = (str_num_t**)malloc(INIT_NO_MAP*STR_NUM_MAP_SIZE);
	memset(str_num_map_manager->str_num_map_table,0,INIT_NO_MAP*STR_NUM_MAP_SIZE);
	str_num_map_manager->max_num            = INIT_NO_MAP;
	str_num_map_manager->cur_num            = 0;
	str_num_map_manager->extend_police      = DOUBLE_EXTEND;
	return 0;
}

//销毁速查表
inline int dest_str_num_map_manager(str_num_map_t *str_num_map_manager)
{
  free(str_num_map_manager->str_num_map_table);
  return 0;
}


//扩展速查表
inline int extend_str_num_map_manager(str_num_map_t *str_num_map_manager)
{
	STR_NUM_MAP_LOCK(&(str_num_map_manager->locker));  //上锁
	
	void   * old =  str_num_map_manager->str_num_map_table;
	void   * new_;
	
	//根据策略重新分配速查表内存
	switch(str_num_map_manager->extend_police)
	{
		case DOUBLE_EXTEND:
	  new_ =  malloc( 2*(str_num_map_manager->max_num)*STR_NUM_MAP_SIZE);
	  break;
	
  }
  memcpy(new_,old,str_num_map_manager->max_num);
  str_num_map_manager->max_num            =  2*(str_num_map_manager->max_num);
	str_num_map_manager->cur_num            =  str_num_map_manager->max_num;
	str_num_map_manager->str_num_map_table =  (str_num_t**)new_;
  free(old);
  
  STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker)); //解锁
  return 0 ;
}


//获取块号对应的地址
inline int get_str_num_map_addr(str_num_map_t *str_num_map_manager,char * str,str_num_t ** addr,str_num_t ** addr_pre)
{
	DEBUG("str is %s\n",str);
	if( str_num_map_manager == NULL){
		ERROR("ERR_STR_NUM_MAP_NULL\n");
		return ERR_STR_NUM_MAP_NULL;
	} 
	if( str == NULL){
		ERROR("ERR_STR_NUM_IS_NULL\n");
		return ERR_STR_NUM_IS_NULL;
	} 
	if ( 0 == str_num_map_manager->max_num ){
		ERROR("Max is Zero\n");
		return MAX_IS_ZERO;
	
	}
  
  long long str_num_map = ___str_hash_fun_for_file(str,str_num_map_manager->max_num);
 	DEBUG("str_num_map index is %ld\n",str_num_map);

	
	 STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
	 *addr = (str_num_map_manager->str_num_map_table[str_num_map]);
	 *addr_pre = *addr;
	 while(NULL != (*addr) && strcmp((*addr)->__str,str)!=0) 
	 {
	  *addr_pre = *addr;
	 *addr = (*addr)->next;
	 
	 }
	 STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
	 
	if( 0 == addr ){
		 ERROR("ERR_STR_NUM_BAD_ADDR\n");
		 return ERR_STR_NUM_BAD_ADDR;
	} 
	return 0;
	
}

//设置块号对应的地址
inline int set_str_num_map_addr(str_num_map_t *str_num_map_manager,char * str,str_num_t * addr)
{
 if( str_num_map_manager == NULL){
		ERROR("ERR_STR_NUM_MAP_NULL\n");
		return ERR_STR_NUM_MAP_NULL;
	} 
	
	if(str == NULL){
		ERROR("ERR_STR_NUM_IS_NULL\n");
		return ERR_STR_NUM_IS_NULL;
	} 
	//IMPORTANT_INFO("set_str_num_map_addr key %s ,value %d\n",str,addr);

	long long str_num_map = ___str_hash_fun_for_file(str,str_num_map_manager->max_num);
  DEBUG("str_num_map index is %ld\n",str_num_map);

	 STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
	 if(NULL == str_num_map_manager->str_num_map_table[str_num_map]){str_num_map_manager->str_num_map_table[str_num_map]= addr;}
	 else
	 	{
	 		str_num_t * temp = str_num_map_manager->str_num_map_table[str_num_map];
      ERROR("str is %s\n",str);   
	    ERROR("temp->__str is %s\n",temp->__str);
	 			if( 0 == strcmp(str,temp->__str) )
	 			{
	 					STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
						return 0;
	 			}	 	
	 			
	   
	 
	 struct str_num_t * __pre = temp;
	 while(NULL != temp )
	 {
	 	__pre = temp;
	 temp = temp->next;
	 }
	 __pre->next = addr;
	 }
	 
	 STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int del_str_num_map_addr(str_num_map_t *str_num_map_manager,char * str)
{
 if( str_num_map_manager == NULL){
		ERROR("ERR_STR_NUM_MAP_NULL\n");
		return ERR_STR_NUM_MAP_NULL;
	} 
	
	if(str == NULL){
		ERROR("ERR_STR_NUM_IS_NULL\n");
		return ERR_STR_NUM_IS_NULL;
	} 
	
	str_num_t * addr_pre = NULL;
	str_num_t * addr     = NULL;
	int err;
	
	DEBUG("str is %s\n",str);
	err =get_str_num_map_addr(str_num_map_manager, str,&addr,&addr_pre);
	if(!err && addr != addr_pre && addr_pre!=NULL)
	{
		if(addr_pre != NULL && addr!= NULL)
			{
				printf("addr_pre is %s\n",addr_pre->__str);
				printf("addr     is %s\n",addr->__str);

				STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
				addr_pre->next = addr->next;
				STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
			}
		if( addr!= NULL )
			{
				free(addr);
				addr = NULL;
			}
	}
	else if(!err && addr == addr_pre)
	{
	 STR_NUM_MAP_LOCK  (&(str_num_map_manager->locker));  //上锁
	 		if( addr!= NULL )
			{
				free(addr);
				addr = NULL;
			}
			long long str_num_map = ___str_hash_fun_for_file(str,str_num_map_manager->max_num);
	    str_num_map_manager->str_num_map_table[str_num_map] = 0;

	 STR_NUM_MAP_UNLOCK(&(str_num_map_manager->locker));  //解锁
	}
	else
		{
			ERROR("DEL_STR_NUM_MAP_ERR!\n");
			return err;
		}
	return 0;
	
}

#ifdef __cplusplus

}

#endif

#endif 