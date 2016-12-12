#ifndef MEM_BLOCK_NO_MANAGER_T
#define MEM_BLOCK_NO_MANAGER_T

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include "rwlock.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define ERR_SEQ_NO_LESS_ZERO 	44001
#define ERR_SEQ_NOT_EXIST 		44002
#define ERR_SEQ_FULL_USED     44003


//暂时用CAS来实现序列读写锁
#define seq_lock_t   			 rwlock_t
#define seq_lock_init(x)   rwlock_init((x)); 
#define seq_rlock(x)       rwlock_rlock((x)); 
#define seq_runlock(x)     rwlock_runlock((x)); 
#define seq_wlock(x)       rwlock_wlock((x)); 
#define seq_wunlock(x)     rwlock_wunlock((x)); 


//暂时用互斥锁表示事物锁

#define MEM_SEQ_MANAGER_LOCK_T        pthread_mutex_t
#define MEM_SEQ_MANAGER_LOCK(x)       pthread_mutex_lock(x)
#define MEM_SEQ_MANAGER_UNLOCK(x)     pthread_mutex_unlock(x)   
#define MEM_SEQ_MANAGER_LOCK_INIT(x)  pthread_mutex_init(x,NULL)   
#define MEM_SEQ_MANAGER_LOCK_DEST(x)  pthread_mutex_destroy(x)   



//默认系统
#define DEAULT_SYS_SEQ_NUM    2048
// 扩展策略
#define    DOUBLE_EXTEND      1

//序列最大值
#define ULL_MAX 2^64-1


// 序列类型
typedef struct mem_sequens_t
{
unsigned  long long         cur_num;              	//scn索引
seq_lock_t                  locker;             		//锁
unsigned  long long         max;										//回滚空间最大值
int                         is_used;								//是否在用
} __attribute__ ((packed, aligned (64))) mem_sequens_t;

#define MEM_SEQUENS_SIZE  sizeof(mem_sequens_t)

// 系统序列管理器
typedef struct sys_sequens_manager_t
{
unsigned  long long         seq_cur;              		//scn索引
mem_sequens_t *    				  seq_tables;   						//序列表
long                        seq_num;									//序列表存储个数
MEM_SEQ_MANAGER_LOCK_T      locker;               		//锁
int                   extend_police;                  // 扩展策略，默认使用二倍扩展
} __attribute__ ((packed, aligned (64))) sys_sequens_manager_t;

#define SYS_SEQUENS_MANAGER_SIZE  sizeof(sys_sequens_manager_t)
static sys_sequens_manager_t sys_sequens_manager;

//____________________________________________________________
int save_seq_cur(char * str_path)
{
MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //上锁
FILE *fp;  // 定义一个文件指针fp
fp = fopen(str_path, "wt");  // 以二进制可写方式打开stu.dat文件
char buf[512];
mem_sequens_t * mem_seq ;
int ret;
int i = 0;
for(;i<sys_sequens_manager.seq_num;++i){
mem_seq = &(sys_sequens_manager.seq_tables[i]);
sprintf(buf,"%d,%d|",sys_sequens_manager.seq_tables[i].is_used,mem_seq->cur_num);
ret = !(fwrite(buf, strlen(buf), 1, fp)==1);
}
int ret2 =  fclose( fp );
 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //解锁

return ret|ret2;
}

int load_seq_cur(char * str_path)
{
int ret=-1;
int ret2=-1;
	int fp = open(str_path, O_RDWR, 0666 );
	struct stat sb; 
	/* 取得文件大小 */
	fstat(fp, &sb); 

if((access(str_path,F_OK))!=-1) {
char * buf = malloc(sb.st_size*sizeof(char));
mem_sequens_t * mem_seq ;
int i = 0;
MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //上锁
 
read(fp, buf, sb.st_size);  
//printf("A>>%s\n",buf);

char *p;
char *buf_i = buf;
int len=0;
int a;
unsigned long long b;

while(p = strtok(buf, "|")){
//printf("p is %s\n",p);
sscanf(p,"%d,%ld",&a,&b);
sys_sequens_manager.seq_tables[i].is_used = a;
sys_sequens_manager.seq_tables[i].cur_num = b;
//if(sys_sequens_manager.seq_tables[i].is_used!=0)
//printf("sysa,sysb is %ld,%ld\n",sys_sequens_manager.seq_tables[i].is_used,sys_sequens_manager.seq_tables[i].cur_num);
len=strlen(p)+1;
buf+=len;
++i;
} 

ret2 =  close( fp );
free(buf_i);
MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //解锁
}
return ret|ret2;
}

//初始化 seq_manager 表
inline int init_mem_seq_manager()
{
	MEM_SEQ_MANAGER_LOCK_INIT(&(sys_sequens_manager.locker));
	sys_sequens_manager.seq_num = DEAULT_SYS_SEQ_NUM;
	sys_sequens_manager.seq_tables = malloc(DEAULT_SYS_SEQ_NUM*(MEM_SEQUENS_SIZE));
	long i = 0;
	for(;i<DEAULT_SYS_SEQ_NUM;++i)
	{
		seq_lock_init(&(sys_sequens_manager.seq_tables[i].locker));
		sys_sequens_manager.seq_tables[i].is_used = 0;
		sys_sequens_manager.seq_tables[i].max     = ULL_MAX;
	}
	sys_sequens_manager.extend_police    = DOUBLE_EXTEND;
	return 0;
}

//销毁 seq_manager 表
inline int dest_mem_seq_manager()
{
	MEM_SEQ_MANAGER_LOCK_DEST(&(sys_sequens_manager.locker));
  free(sys_sequens_manager.seq_tables);
  return 0;
}

//扩展序列表
inline int extend_mem_seq_manager()
{
	MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //上锁
	
	void   * old =  sys_sequens_manager.seq_tables;
	void   * _new;
	
	//根据策略重新分配速查表内存
	switch(sys_sequens_manager.extend_police)
	{
		case DOUBLE_EXTEND:
	  _new =  malloc( 2*(sys_sequens_manager.seq_num)*(MEM_SEQUENS_SIZE));
	  break;
	
  }
  memcpy(_new,old,sys_sequens_manager.seq_num);
  sys_sequens_manager.seq_num           =  2*(sys_sequens_manager.seq_num);
	sys_sequens_manager.seq_tables        =  _new;
	
  free(old);
  
  long i = 0;
	for(;i<sys_sequens_manager.seq_num;++i)
	{
		if(i>= sys_sequens_manager.seq_num/2)
			{
		   seq_lock_init(&(sys_sequens_manager.seq_tables[i].locker));
		   sys_sequens_manager.seq_tables[i].max = ULL_MAX;
		 }
	}
  
  MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker)); //解锁
  return 0 ;
}


//获取对应序列的值
inline int get_seqval_by_no(long seq_no,unsigned  long long * val)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);
	
	
	
	 seq_wlock  (&(mem_seq->locker));  //上锁
	 if(mem_seq->cur_num== mem_seq->max)mem_seq->cur_num=0; //超过最大值就回到0
	 	else  ++(mem_seq->cur_num);             // ++
	 *val = (mem_seq->cur_num);
	 seq_wunlock(&(mem_seq->locker));  //解锁

	return 0;
	
}

//设置序列最大值
inline int set_seqmax_by_no(long seq_no,unsigned  long long  max)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);

	 seq_wlock  (&(mem_seq->locker));  //上锁
	 mem_seq->max = max;
	 seq_wunlock(&(mem_seq->locker));  //解锁
	return 0;
	
}

//设置块号对应的地址
inline int set_seqval_by_no(long seq_no,unsigned  long long  val)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);

	 seq_wlock  (&(mem_seq->locker));  //上锁
	 mem_seq->cur_num = val;
	 seq_wunlock(&(mem_seq->locker));  //解锁
	return 0;
	
}

//删除块号对应的地址
inline int clear_seq_by_no(long seq_no)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);
	
	 seq_wlock(&(mem_seq->locker));  //上锁
	 mem_seq->cur_num = 0;
	 seq_wunlock(&(mem_seq->locker));  //解锁
	return 0;
	
}

// 分配唯一序列号
// 当系统使用了上百万的序列时，会影响分配序列的性能，后面再考虑优化
inline int allocate_seq_no(long * seq_no)
{	
	 MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //上锁
	 int i = 0;
	 int err = 0;
	 for(;i<sys_sequens_manager.seq_num;++i)
	 {
	 	//printf("seq_tables[%d].is_used=%d,cur_num=%ld\n",i,sys_sequens_manager.seq_tables[i].is_used,sys_sequens_manager.seq_tables[i].cur_num);
	 	if(sys_sequens_manager.seq_tables[i].is_used == 0)
	 		{
	 			sys_sequens_manager.seq_tables[i].is_used = 1;
	 			*seq_no =  i;	
	 			break;
	 		}
	 	
	}
	 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //解锁
  if(i == sys_sequens_manager.seq_num)
  	{
  		err = extend_mem_seq_manager();
  		if(err!=0)return err;
  		return ERR_SEQ_FULL_USED;
  	}
	return 0;
	
}

// 释放唯一序列号
inline int release_seq_no(long  seq_no)
{	
	 MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //上锁
	 sys_sequens_manager.seq_tables[seq_no].is_used = 0;
	 sys_sequens_manager.seq_tables[seq_no].cur_num = 0;
	 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //解锁
	return 0;
	
}
#endif 