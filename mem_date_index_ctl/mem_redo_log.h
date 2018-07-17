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
#include <pthread.h> //���뻥����
#include<string.h>
#include"../util/file_entry_map.h"



//��־
//�ȼ�ȫ����
//�ٰ����������ʼλ�úͳ��ȣ����0
//���ͷ�ȫ����
//�Ը�Ƭ����ӷ�Χ��
//д����
//�ͷŷ�Χ��

//�ۼ��ļ���С��������С�������ļ�
//��ʱ�û�������ʾ������
//#define REDO_LOG_LOCK_T        pthread_mutex_t
//#define REDO_LOG_LOCK(x)       pthread_mutex_lock(x)
//#define REDO_LOG_UNLOCK(x)     pthread_mutex_unlock(x)   
//#define REDO_LOG_LOCK_INIT(x)  pthread_mutex_init(x,NULL)   

#define REDO_LOG_LOCK_T        pthread_spinlock_t
#define REDO_LOG_LOCK(x)       pthread_spin_lock(x)
#define REDO_LOG_UNLOCK(x)     pthread_spin_unlock(x)   
#define REDO_LOG_LOCK_INIT(x)  pthread_spin_init(x,0)   

//��ʱ������������ʵ�ֻ���������
#define SIZE_LOCK_T             pthread_spinlock_t
#define SIZE_LOCK(x)            pthread_spin_lock(x)
#define SIZE_UNLOCK(x)          pthread_spin_unlock(x)   
#define SIZE_TRYLOCK(x)         pthread_spin_trylock(x)   
#define SIZE_LOCK_INIT(x)       pthread_spin_init(x,0)

#define ERR_FILE_NAME_IS_NULL   430001
#define ERR_FILE_PTR_IS_NULL    430002

//���������Ѿ��򿪵� redofile
static file_entry_map_t opened_redo_log_file;

// ע��򿪵��ļ�
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

// ע���򿪵��ļ�
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


// ���Ҵ򿪵��ļ�
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

// clear���ļ��ٲ��
static int clear_opened_file()
{
  dest_file_entry_map_manager(&opened_redo_log_file);
  init_file_entry_map_manager(&opened_redo_log_file);
	return 0;
	
}

// close ���ļ��ٲ��
static int close_opened_file()
{
  dest_file_entry_map_manager(&opened_redo_log_file);
	return 0;
	
}

//________________________________________________________________-
// ϵͳredo��־������
typedef struct sys_redo_log_manager_t
{
FILE *                      data_fd;                  //��ǰ�򿪵������ļ�
char                        redo_path[128];            //redo ��־·��
FILE *                      index_fd;                  //��ǰ�򿪵�Ŀ¼�ļ�
char                        index_path[128];           //index ��־·��
char                        path[128];            //redo ��־·��
REDO_LOG_LOCK_T             data_locker;               		//�����ļ���
REDO_LOG_LOCK_T             index_locker;               		//Ŀ¼�ļ���
off_t                   		data_max_size;                 //���������ļ���С
off_t                   		index_max_size;                 //���������ļ���С
off_t                       cur_data_size;                 //��ǰ�ļ���С
SIZE_LOCK_T                 data_size_locker;              //�ļ���С�ۼ�����
off_t                       cur_index_size;                 //��ǰ�ļ���С
SIZE_LOCK_T                 index_size_locker;              //�ļ���С�ۼ�����
} __attribute__ ((packed, aligned (64))) sys_redo_log_manager_t;

#define REDO_LOG_MANAGER_SIZE  sizeof(sys_redo_log_manager_t)

//Ĭ�� ע��Ϊ2��n����
#define DEFAULT_FILE_MAX_SIZE       1024*1024*128
#define DEFAULT_DATA_FILE_MAX_SIZE  1024*1024*512
#define DEFAULT_INDEX_FILE_MAX_SIZE 1024*1024*512

//Ĭ�� ע��Ϊ2��n����
#define DEFAULT_QUEUE_MAX_SIZE 1024*1024*128
#define DEFAULT_STACK_MAX_SIZE  1024*1024*128

//Ĭ���������
#define DEFAULT_MAX_TRANS_NUM  1024*1024  
//Ĭ�ϻع��δ�С 10M
#define DEFAULT_ROLLBACK_SPACE_SIZE  1024*1024*500
//#define DEFAULT_ROLLBACK_SPACE_SIZE  1024*1024

static sys_redo_log_manager_t redo_log_manager;

//______________________________________________________
//��ʼ�� redo_manager
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

//���� config_manager
inline int config_redo_data_log(char * path,off_t file_max_size)
{
	REDO_LOG_LOCK(&(redo_log_manager.data_locker));//�����ļ�����
	strcpy(redo_log_manager.path,path);
	strcpy(redo_log_manager.redo_path,path);
	strcat(redo_log_manager.redo_path,"/redo_data_");
	//ƴ��ʱ��
  GetTimeForNAME(redo_log_manager.redo_path);
  redo_log_manager.data_max_size = file_max_size;
  REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//�����ļ�����
	return 0;
}

//���� config_manager
inline int config_redo_index_log(char * path,off_t file_max_size)
{
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����
	strcpy(redo_log_manager.redo_path,path);
	strcat(redo_log_manager.index_path,"/redo_index_");
	//ƴ��ʱ��
  GetTimeForNAME(redo_log_manager.index_path);
  redo_log_manager.index_max_size = file_max_size;
  REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����
	return 0;
}

//�ر� redo_manager
inline int close_redo_log_manager()
{
	REDO_LOG_LOCK(&(redo_log_manager.data_locker));//�����ļ�����
	fclose(redo_log_manager.data_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//�����ļ�����
	
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����
	fclose(redo_log_manager.index_fd);
	REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����
	close_opened_file();
	return 0;
}

//ˢ�� redo_manager
inline int fflush_redo_log_manager()
{
	REDO_LOG_LOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����	
        fflush(redo_log_manager.index_fd);
	fsync(fileno(redo_log_manager.index_fd));
	REDO_LOG_UNLOCK(&(redo_log_manager.index_locker));//Ŀ¼�ļ�����

  REDO_LOG_LOCK(&(redo_log_manager.data_locker));//�����ļ�����

	fflush(redo_log_manager.data_fd);
         fsync(fileno(redo_log_manager.data_fd));
	REDO_LOG_UNLOCK(&(redo_log_manager.data_locker));//�����ļ�����	
	return 0;
}

#ifdef __cplusplus

}

#endif

#endif 
