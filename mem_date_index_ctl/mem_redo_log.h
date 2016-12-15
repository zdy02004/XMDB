#ifndef MEM_REDO_H
#define MEM_REDO_H

#ifdef __cplusplus

extern "C" {

#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>  
#include <pthread.h> //引入互斥锁
#include<string.h>
#include"../util/file_entry_map.h"



//日志
//先加全局锁
//再按照申请的起始位置和长度，填充0
//再释放全局锁
//对该片区域加范围锁
//写数据
//释放范围锁

//累加文件大小，超过大小生成新文件
//暂时用互斥锁表示事物锁
//#define REDO_LOG_LOCK_T        pthread_mutex_t
//#define REDO_LOG_LOCK(x)       pthread_mutex_lock(x)
//#define REDO_LOG_UNLOCK(x)     pthread_mutex_unlock(x)   
//#define REDO_LOG_LOCK_INIT(x)  pthread_mutex_init(x,NULL)   

#define REDO_LOG_LOCK_T        pthread_spinlock_t
#define REDO_LOG_LOCK(x)       pthread_spin_lock(x)
#define REDO_LOG_UNLOCK(x)     pthread_spin_unlock(x)   
#define REDO_LOG_LOCK_INIT(x)  pthread_spin_init(x,0)   

//暂时用自旋锁锁来实现回收链表锁
#define SIZE_LOCK_T             pthread_spinlock_t
#define SIZE_LOCK(x)            pthread_spin_lock(x)
#define SIZE_UNLOCK(x)          pthread_spin_unlock(x)   
#define SIZE_TRYLOCK(x)         pthread_spin_trylock(x)   
#define SIZE_LOCK_INIT(x)       pthread_spin_init(x,0)

#define ERR_FILE_NAME_IS_NULL   430001
#define ERR_FILE_PTR_IS_NULL    430002

//用来管理已经打开的 redofile
static file_entry_map_t opened_redo_log_file;

// 注册打开的文件
static int regist_opened_file(char * file_name,FILE * fd)
{
if(NULL == file_name)
		{
			ERROR("ERR_FILE_NAME_IS_NULL\n");
			return ERR_FILE_NAME_IS_NULL;
		}
if(NULL == fd)
		{
			ERROR("ERR_FILE_PTR_IS_NULL\n");
			return ERR_FILE_PTR_IS_NULL;
		}
	if(NULL == opened_redo_log_file.file_entry_map_table)init_file_entry_map_manager(&opened_redo_log_file);
	file_entry_t * fe = (file_entry_t *)malloc(FILE_ENTRY_ENTRY_SIZE);
	fe->fd   = fd;
	strcpy(fe->__str,file_name);
	fe->next = 0;
	return set_file_entry_map_addr(&opened_redo_log_file,file_name,fe);
	  return 0;
}

// 注销打开的文件
static int unregist_opened_file(char * file_name)
{
if(NULL == file_name)
{
	ERROR("ERR_FILE_NAME_IS_NULL\n");
	return ERR_FILE_NAME_IS_NULL;
}
		
		file_entry_t * addr;
		file_entry_t * addr_pre;
int err;
if(0!=(err =  get_file_entry_map_addr(&opened_redo_log_file,file_name,&addr,&addr_pre)))
	{
		return err;
	}
	return del_file_entry_map_addr(&opened_redo_log_file,file_name);
	return 0;
}


// 查找打开的文件
static int search_opened_file(char * file_name,FILE ** fd)
{
if(NULL == file_name)
		{
			ERROR("ERR_FILE_NAME_IS_NULL\n");
			return ERR_FILE_NAME_IS_NULL;
		}
		
		file_entry_t * addr;
		file_entry_t * addr_pre;
int err;
if(0!=(err =  get_file_entry_map_addr(&opened_redo_log_file,file_name,&addr,&addr_pre)))
	{
		IMPORTANT_INFO("Not Found Opened File %s\n",file_name);
		return err;
	}
	*fd = addr->fd;
	return 0;
	
}

// clear打开文件速查表
static int clear_opened_file()
{
  dest_file_entry_map_manager(&opened_redo_log_file);
  init_file_entry_map_manager(&opened_redo_log_file);
	return 0;
	
}

// close 打开文件速查表
static int close_opened_file()
{
  dest_file_entry_map_manager(&opened_redo_log_file);
	return 0;
	
}

//________________________________________________________________-
// 系统redo日志管理器
typedef struct sys_redo_log_manager_t
{
FILE *                      data_fd;                  //当前打开的数据文件
char                        redo_path[128];            //redo 日志路径
FILE *                      index_fd;                  //当前打开的目录文件
char                        index_path[128];           //index 日志路径
char                        path[128];            //redo 日志路径
REDO_LOG_LOCK_T             data_locker;               		//数据文件锁
REDO_LOG_LOCK_T             index_locker;               		//目录文件锁
off_t                   		data_max_size;                 //单个数据文件大小
off_t                   		index_max_size;                 //单个数据文件大小
off_t                       cur_data_size;                 //当前文件大小
SIZE_LOCK_T                 data_size_locker;              //文件大小累加器锁
off_t                       cur_index_size;                 //当前文件大小
SIZE_LOCK_T                 index_size_locker;              //文件大小累加器锁
} __attribute__ ((packed, aligned (64))) sys_redo_log_manager_t;

#define REDO_LOG_MANAGER_SIZE  sizeof(sys_redo_log_manager_t)

//默认 100 M
#define DEFAULT_FILE_MAX_SIZE       1024*1024*100
#define DEFAULT_DATA_FILE_MAX_SIZE  1024*1024*500
#define DEFAULT_INDEX_FILE_MAX_SIZE 1024*1024*500


#define DEFAULT_QUEUE_MAX_SIZE 1024*1024*100
#define DEFAULT_STACK_MAX_SIZE  1024*1024*100

//默认事务个数
#define DEFAULT_MAX_TRANS_NUM  2048  
//默认回滚段大小 10M
#define DEFAULT_ROLLBACK_SPACE_SIZE  1024*1024*500
//#define DEFAULT_ROLLBACK_SPACE_SIZE  1024*1024

static sys_redo_log_manager_t redo_log_manager;

//______________________________________________________
//初始化 redo_manager
inline int init_redo_log_manager()
{
	REDO_LOG_LOCK_INIT(&(redo_log_manager.data_locker) );
  REDO_LOG_LOCK_INIT(&(redo_log_manager.index_locker));

	SIZE_LOCK_INIT(&(redo_log_manager.data_size_locker) );
	SIZE_LOCK_INIT(&(redo_log_manager.index_size_locker));
	
	sprintf(redo_log_manager.path,".\0");
	
	sprintf(redo_log_manager.redo_path,"./redo_data_\0");
  GetTimeForNAME(redo_log_manager.redo_path);
  sprintf(redo_log_manager.index_path,"./redo_index_\0");
  GetTimeForNAME(redo_log_manager.index_path);
  
  redo_log_manager.data_fd  = fopen(redo_log_manager.redo_path,"wb+");
  redo_log_manager.cur_data_size  = 0;
  redo_log_manager.index_fd = fopen(redo_log_manager.index_path,"wb+");
  redo_log_manager.cur_index_size = 0;
  
  regist_opened_file(redo_log_manager.redo_path ,redo_log_manager.data_fd);
  regist_opened_file(redo_log_manager.index_path,redo_log_manager.index_fd);
  
  DEBUG("redo_path is %s, data_fd is %d\n"	,redo_log_manager.redo_path,redo_log_manager.data_fd 	);
  DEBUG("index_path is %s, index_fd is %d\n",redo_log_manager.redo_path,redo_log_manager.index_fd );

  
  redo_log_manager.data_max_size  = DEFAULT_DATA_FILE_MAX_SIZE;
  redo_log_manager.index_max_size = DEFAULT_INDEX_FILE_MAX_SIZE;
	return 0;
}

//配置 config_manager
inline int config_redo_data_log(char * path,off_t file_max_size)
{
	REDO_LOG_LOCK(&(redo_log_manager.data_locker));//数据文件上锁
	strcpy(redo_log_manager.path,path);
	strcpy(redo_log_manager.redo_path,path);
	strcat(redo_log_manager.redo_path,"/redo_data_");
	//拼入时间
  GetTimeForNAME(redo_log_manager.redo_path);
  redo_log_manager.data_max_size = file_max_size;
  REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//数据文件上锁
	return 0;
}

//配置 config_manager
inline int config_redo_index_log(char * path,off_t file_max_size)
{
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//目录文件上锁
	strcpy(redo_log_manager.redo_path,path);
	strcat(redo_log_manager.index_path,"/redo_index_");
	//拼入时间
  GetTimeForNAME(redo_log_manager.index_path);
  redo_log_manager.index_max_size = file_max_size;
  REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//目录文件解锁
	return 0;
}

//关闭 redo_manager
inline int close_redo_log_manager()
{
	REDO_LOG_LOCK(&(redo_log_manager.data_locker));//数据文件上锁
	fclose(redo_log_manager.data_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//数据文件解锁
	
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//目录文件上锁
	fclose(redo_log_manager.index_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//目录文件解锁
	close_opened_file();
	return 0;
}

//刷新 redo_manager
inline int fflush_redo_log_manager()
{
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//目录文件上锁	
	fflush(redo_log_manager.index_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//目录文件解锁

  REDO_LOG_LOCK(&(redo_log_manager.data_locker));//数据文件上锁
	fflush(redo_log_manager.data_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//数据文件解锁	
	return 0;
}

#ifdef __cplusplus

}

#endif

#endif 