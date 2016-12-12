#ifndef FILE_ENTRY_MAP_T
#define FILE_ENTRY_MAP_T

#include <stdio.h>
#include <stdlib.h>  
#include "../mem_date_index_ctl/rwlock.h"
#include<string.h>



#define MAX_FILE_NO_MAP  (1024*1024-1)
#define INIT_FILE_NO_MAP (1023)

//暂时用互斥锁表示块锁
#define FILE_ENTRY_MAP_LOCK_T              rwlock_t
#define FILE_ENTRY_MAP_LOCK(x)             rwlock_wlock(x);
#define FILE_ENTRY_MAP_UNLOCK(x)           rwlock_wunlock(x);
#define FILE_ENTRY_MAP_RLOCK(x)            rwlock_rlock(x);
#define FILE_ENTRY_MAP_RUNLOCK(x)          rwlock_runlock(x);   
#define FILE_ENTRY_MAP_LOCK_INIT(x)        rwlock_init((x));


// 扩展策略
#define    DOUBLE_EXTEND           1

#define ERR_STR_IS_NULL         420010
#define ERR_FILE_ENTRY_MAP_NULL 420020
#define ERR_BAD_ADDR			      420030

typedef struct file_entry_t
{
char __str[256];
FILE *  fd     ;
struct file_entry_t *next;
	
} __attribute__ ((packed, aligned (64))) file_entry_t;

#define FILE_ENTRY_ENTRY_SIZE sizeof(file_entry_t)
#define CREATE_FILE_ENTRY(x,str)  ( file_entry_t * (x) = (file_entry_t *)(malloc(FILE_ENTRY_ENTRY_SIZE)) );\
strcpy((x)->__str,str);

typedef struct file_entry_map_t
{
	file_entry_t        ** file_entry_map_table;  // (块号,地址) 速查表 存储块号对应地址的动态数组
	FILE_ENTRY_MAP_LOCK_T     locker;                 // 互斥锁
	long                  max_num;               // 可以存储的最大地址
	long                  cur_num;               // 当前使用的最大地址
	int                   extend_police;         // 扩展策略，默认使用二倍扩展
	
} __attribute__ ((packed, aligned (64))) file_entry_map_t;

#define FILE_ENTRY_MAP_SIZE sizeof(file_entry_map_t)
#define CREATE_FILE_ENTRY_MAP   (file_entry_t *)(malloc(FILE_ENTRY_MAP_SIZE));

// BKDR Hash Function
inline unsigned int __BKDRHashForFile(char *str)
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
inline unsigned int __str_hash_fun_for_file(char * key,long max)
{
	if( NULL == key        )
		{
			ERROR("ERR_STR_IS_NULL\n");
			return ERR_STR_IS_NULL;
		}
   //DEBUG("__BKDRHashForFile(key) %ld \n",__BKDRHashForFile(key));
   //DEBUG("max %ld \n",max);
	//先平均分布，再取余数	
	return  __BKDRHashForFile(key) % ( max ) ;

}

int file_entry_map_manager_save_cur(file_entry_map_t *file_entry_map_manager,char * str_path)
{
FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
sprintf(buf,"%d",file_entry_map_manager->cur_num);
int ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
int ret2 =  fclose( fp );
FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁

return ret|ret2;
}


int file_entry_map_manager_load_cur(file_entry_map_t *file_entry_map_manager,char * str_path)
{
	int ret=-1;
	int ret2=-1;
if(!access(str_path,0)){
FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "rt");  // 以二进制可写方式打开stu.dat文件
ret = !(fscanf(fp,"%d",&(file_entry_map_manager->cur_num)) == 1);
DEBUG("file_entry_map_manager->cur_num is %d\n",file_entry_map_manager->cur_num);
ret2 =  fclose( fp );
FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
}
return ret|ret2;
}


//初始化速查表
inline int init_file_entry_map_manager(file_entry_map_t *file_entry_map_manager)
{
	DEBUG("in init_file_entry_map_manager()\n");
	FILE_ENTRY_MAP_LOCK_INIT(&(file_entry_map_manager->locker));
	file_entry_map_manager->file_entry_map_table = malloc(INIT_FILE_NO_MAP*FILE_ENTRY_MAP_SIZE);
	file_entry_map_manager->max_num            = INIT_FILE_NO_MAP;
	file_entry_map_manager->cur_num            = 0;
	file_entry_map_manager->extend_police      = DOUBLE_EXTEND;
	return 0;
}

//销毁速查表
inline int dest_file_entry_map_manager(file_entry_map_t *file_entry_map_manager)
{
  free(file_entry_map_manager->file_entry_map_table);
  return 0;
}


//扩展速查表
inline int extend_file_entry_map_manager(file_entry_map_t *file_entry_map_manager)
{
	FILE_ENTRY_MAP_LOCK(&(file_entry_map_manager->locker));  //上锁
	
	void   * old =  file_entry_map_manager->file_entry_map_table;
	void   * new_;
	
	//根据策略重新分配速查表内存
	switch(file_entry_map_manager->extend_police)
	{
		case DOUBLE_EXTEND:
	  new_ =  malloc( 2*(file_entry_map_manager->max_num)*FILE_ENTRY_MAP_SIZE);
	  break;
	
  }
  memcpy(new_,old,file_entry_map_manager->max_num);
  file_entry_map_manager->max_num            =  2*(file_entry_map_manager->max_num);
	file_entry_map_manager->cur_num            =  file_entry_map_manager->max_num;
	file_entry_map_manager->file_entry_map_table =  new_;
  free(old);
  
  FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker)); //解锁
  return 0 ;
}


//获取块号对应的地址
inline int get_file_entry_map_addr(file_entry_map_t *file_entry_map_manager,char * str,file_entry_t ** addr,file_entry_t ** addr_pre)
{
	if( file_entry_map_manager == NULL){
		ERROR("ERR_FILE_ENTRY_MAP_NULL\n");
		return ERR_FILE_ENTRY_MAP_NULL;
	} 
	if( str == NULL){
		ERROR("ERR_STR_IS_NULL\n");
		return ERR_STR_IS_NULL;
	} 
  
  DEBUG("GET_FiLE_ENTRY_MAP_ADDR\n");
  
  long long file_entry_map = __str_hash_fun_for_file(str,file_entry_map_manager->max_num);

	
	 FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
	 *addr = (file_entry_map_manager->file_entry_map_table[file_entry_map]);
	 *addr_pre = *addr;
	 while(NULL != (*addr) && strcmp((*addr)->__str,str)!=0) 
	 {
	  *addr_pre = *addr;
	 *addr = (*addr)->next;
	 
	 }
	 FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
	 
	if( 0 == *addr ){
		 ERROR("ERR_BAD_ADDR\n");
		 return ERR_BAD_ADDR;
	} 
	DEBUG("Find file %s\n",(*addr)->__str);
	return 0;
	
}

//设置块号对应的地址
inline int set_file_entry_map_addr(file_entry_map_t *file_entry_map_manager,char * str,file_entry_t * addr)
{
 if( file_entry_map_manager == NULL){
		ERROR("ERR_FILE_ENTRY_MAP_NULL\n");
		return ERR_FILE_ENTRY_MAP_NULL;
	} 
	
	if(str == NULL){
		ERROR("ERR_STR_IS_NULL\n");
		return ERR_STR_IS_NULL;
	} 
	IMPORTANT_INFO("set_file_entry_map_addr key %s ,value %d\n",str,addr);

	
	long long file_entry_map = __str_hash_fun_for_file(str,file_entry_map_manager->max_num);

	 FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
	 if(NULL == file_entry_map_manager->file_entry_map_table[file_entry_map]){file_entry_map_manager->file_entry_map_table[file_entry_map]= addr;}
	 else
	 	{
	 		file_entry_t * temp = file_entry_map_manager->file_entry_map_table[file_entry_map];
	 		if( 0 == strcmp(str,temp->__str) )
	 			{
	 					FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
						return 0;
	 			}	 		
	 		
	    ERROR("str is %s\n",str);   
	    ERROR("temp->__str is %s\n",temp->__str);
	 
	 struct file_entry_t * __pre = temp;
	 while(NULL != temp )
	 {
	 	__pre = temp;
	 temp = temp->next;
	 }
	 __pre->next = addr;
	 }
	 
	 FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int del_file_entry_map_addr(file_entry_map_t *file_entry_map_manager,char * str)
{
 if( file_entry_map_manager == NULL){
		ERROR("ERR_FILE_ENTRY_MAP_NULL\n");
		return ERR_FILE_ENTRY_MAP_NULL;
	} 
	
	if(str == NULL){
		ERROR("ERR_STR_IS_NULL\n");
		return ERR_STR_IS_NULL;
	} 
	IMPORTANT_INFO("del_file_entry_map_addr key %s \n",str);

	file_entry_t * addr_pre = NULL;
	file_entry_t * addr     = NULL;
	int err;
	err =get_file_entry_map_addr(file_entry_map_manager, str,&addr,&addr_pre);
	if(!err && addr != addr_pre && addr_pre!=NULL)
	{
		if(addr_pre != NULL && addr!= NULL)
			{
				DEBUG("addr_pre is %s\n",addr_pre->__str);
				DEBUG("addr     is %s\n",addr->__str);

				FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
				addr_pre->next = addr->next;
				FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
			}
		if( addr!= NULL )
			{
				free(addr);
				addr = NULL;
			}
	}
	else if(!err && addr == addr_pre)
	{
	 FILE_ENTRY_MAP_LOCK  (&(file_entry_map_manager->locker));  //上锁
			if( addr!= NULL )
			{
				free(addr);
				addr = NULL;
			}
			
	 long long file_entry_map = __str_hash_fun_for_file(str,file_entry_map_manager->max_num);
	 file_entry_map_manager->file_entry_map_table[file_entry_map] = 0;

	 FILE_ENTRY_MAP_UNLOCK(&(file_entry_map_manager->locker));  //解锁
	}
	else
		{
			ERROR("DEL_FILE_ENTRY_MAP_ERR!\n");
			return err;
		}
	return 0;
	
}

#endif 