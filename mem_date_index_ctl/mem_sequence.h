#ifndef MEM_BLOCK_NO_MANAGER_T
#define MEM_BLOCK_NO_MANAGER_T

#ifdef __cplusplus

extern "C" {

#endif

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


//��ʱ��CAS��ʵ�����ж�д��
#define seq_lock_t   			 rwlock_t
#define seq_lock_init(x)   rwlock_init((x)); 
#define seq_rlock(x)       rwlock_rlock((x)); 
#define seq_runlock(x)     rwlock_runlock((x)); 
#define seq_wlock(x)       rwlock_wlock((x)); 
#define seq_wunlock(x)     rwlock_wunlock((x)); 


//��ʱ�û�������ʾ������

#define MEM_SEQ_MANAGER_LOCK_T        pthread_mutex_t
#define MEM_SEQ_MANAGER_LOCK(x)       pthread_mutex_lock(x)
#define MEM_SEQ_MANAGER_UNLOCK(x)     pthread_mutex_unlock(x)   
#define MEM_SEQ_MANAGER_LOCK_INIT(x)  pthread_mutex_init(x,NULL)   
#define MEM_SEQ_MANAGER_LOCK_DEST(x)  pthread_mutex_destroy(x)   



//Ĭ��ϵͳ
#define DEAULT_SYS_SEQ_NUM    2048
// ��չ����
#define    DOUBLE_EXTEND      1

//�������ֵ
#define ULL_MAX 2^64-1


// ��������
typedef struct mem_sequens_t
{
unsigned  long long         cur_num;              	//scn����
seq_lock_t                  locker;             		//��
unsigned  long long         max;										//�ع��ռ����ֵ
int                         is_used;								//�Ƿ�����
} __attribute__ ((packed, aligned (64))) mem_sequens_t;

#define MEM_SEQUENS_SIZE  sizeof(mem_sequens_t)

// ϵͳ���й�����
typedef struct sys_sequens_manager_t
{
unsigned  long long         seq_cur;              		//scn����
mem_sequens_t *    				  seq_tables;   						//���б�
long                        seq_num;									//���б�洢����
MEM_SEQ_MANAGER_LOCK_T      locker;               		//��
int                   extend_police;                  // ��չ���ԣ�Ĭ��ʹ�ö�����չ
} __attribute__ ((packed, aligned (64))) sys_sequens_manager_t;

#define SYS_SEQUENS_MANAGER_SIZE  sizeof(sys_sequens_manager_t)
static sys_sequens_manager_t sys_sequens_manager;

//____________________________________________________________
int save_seq_cur(char * str_path)
{
MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //����
FILE *fp;  // ����һ���ļ�ָ��fp
fp = fopen(str_path, "wt");  // �Զ����ƿ�д��ʽ��stu.dat�ļ�
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
 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //����

return ret|ret2;
}

int load_seq_cur(char * str_path)
{
int ret=-1;
int ret2=-1;
	int fp = open(str_path, O_RDWR, 0666 );
	struct stat sb; 
	/* ȡ���ļ���С */
	fstat(fp, &sb); 

if((access(str_path,F_OK))!=-1) {
char * buf = malloc(sb.st_size*sizeof(char));
mem_sequens_t * mem_seq ;
int i = 0;
MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //����
 
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
MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //����
}
return ret|ret2;
}

//��ʼ�� seq_manager ��
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

//���� seq_manager ��
inline int dest_mem_seq_manager()
{
	MEM_SEQ_MANAGER_LOCK_DEST(&(sys_sequens_manager.locker));
  free(sys_sequens_manager.seq_tables);
  return 0;
}

//��չ���б�
inline int extend_mem_seq_manager()
{
	MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //����
	
	void   * old =  sys_sequens_manager.seq_tables;
	void   * _new;
	
	//���ݲ������·����ٲ���ڴ�
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
  
  MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker)); //����
  return 0 ;
}


//��ȡ��Ӧ���е�ֵ
inline int get_seqval_by_no(long seq_no,unsigned  long long * val)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);
	
	
	
	 seq_wlock  (&(mem_seq->locker));  //����
	 if(mem_seq->cur_num== mem_seq->max)mem_seq->cur_num=0; //�������ֵ�ͻص�0
	 	else  ++(mem_seq->cur_num);             // ++
	 *val = (mem_seq->cur_num);
	 seq_wunlock(&(mem_seq->locker));  //����

	return 0;
	
}

//�����������ֵ
inline int set_seqmax_by_no(long seq_no,unsigned  long long  max)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);

	 seq_wlock  (&(mem_seq->locker));  //����
	 mem_seq->max = max;
	 seq_wunlock(&(mem_seq->locker));  //����
	return 0;
	
}

//���ÿ�Ŷ�Ӧ�ĵ�ַ
inline int set_seqval_by_no(long seq_no,unsigned  long long  val)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);

	 seq_wlock  (&(mem_seq->locker));  //����
	 mem_seq->cur_num = val;
	 seq_wunlock(&(mem_seq->locker));  //����
	return 0;
	
}

//ɾ����Ŷ�Ӧ�ĵ�ַ
inline int clear_seq_by_no(long seq_no)
{
	if(seq_no<0) return ERR_SEQ_NO_LESS_ZERO;
	if(seq_no> sys_sequens_manager.seq_num )  return ERR_SEQ_NOT_EXIST;
	
	mem_sequens_t * mem_seq = &(sys_sequens_manager.seq_tables[seq_no]);
	
	 seq_wlock(&(mem_seq->locker));  //����
	 mem_seq->cur_num = 0;
	 seq_wunlock(&(mem_seq->locker));  //����
	return 0;
	
}

// ����Ψһ���к�
// ��ϵͳʹ�����ϰ��������ʱ����Ӱ��������е����ܣ������ٿ����Ż�
inline int allocate_seq_no(long * seq_no)
{	
	 MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //����
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
	 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //����
  if(i == sys_sequens_manager.seq_num)
  	{
  		err = extend_mem_seq_manager();
  		if(err!=0)return err;
  		return ERR_SEQ_FULL_USED;
  	}
	return 0;
	
}

// �ͷ�Ψһ���к�
inline int release_seq_no(long  seq_no)
{	
	 MEM_SEQ_MANAGER_LOCK(&(sys_sequens_manager.locker));  //����
	 sys_sequens_manager.seq_tables[seq_no].is_used = 0;
	 sys_sequens_manager.seq_tables[seq_no].cur_num = 0;
	 MEM_SEQ_MANAGER_UNLOCK(&(sys_sequens_manager.locker));  //����
	return 0;
	
}

#ifdef __cplusplus

}

#endif

#endif 