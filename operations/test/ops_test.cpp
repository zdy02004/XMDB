#include "../ops.hpp"
#include "../../mem_date_index_ctl/mem_table_mvcc_op.h"
#include "../../mem_date_index_ctl/mem_index_no_manager.h"
#include<iostream>
#include <algorithm> 

// 线程参数
typedef struct thread_param_test
{
	struct mem_table_t  *  mem_table ;
	mem_table_config_t * mem_config;
// 测试插入数据
struct record_t * record_ptr;
long block_no;
long long  trans_no;
}thread_param_test;

typedef struct test_table_t
{
	FIELD_INT  id;
	FIELD_INT  try_num;
	FIELD_DATE try_time;
}test_table_t;


int create_block(mem_block_t **mb,char * file_name)
{
	DEBUG("in create_block\n");

	//创建块
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//配置块描述符
	mem_block_config( *mb  ,1024*1024*1 , file_name );
	//初始化块
	INIT_MEM_BLOCK(*mb)
	
	DEBUG("fd = %d\n",(*mb)->fd);
	return 0;
}


int create_mem_table_config(mem_table_config_t ** mem_config,mem_block_t *mb,char * table_name)
{
	DEBUG("in create_mem_table_config\n");

	*mem_config = (mem_table_config_t *) malloc(MEM_TABLE_CONFIG_SIZE);

	(*mem_config)->owner_id = 1;
	strcpy((*mem_config)->table_name,table_name);
	
	struct field_t *fields_table  = (struct field_t *) malloc(FIELD_SIZE*3);
	(*mem_config)->fields_table      = fields_table;
	
	fields_table[0].field_type    = FIELD_TYPE_INT;
	strcpy(fields_table[0].field_name,"id\0");
	fields_table[1].field_type   = FIELD_TYPE_INT;
	strcpy(fields_table[1].field_name,"try_num\0");
	fields_table[2].field_type   = FIELD_TYPE_DATE;
	strcpy(fields_table[2].field_name,"try_time\0");
	
	(*mem_config)->field_used_num   = 3;
	(*mem_config)->mem_blocks_table = mb;
	(*mem_config)->mem_block_used   = 1;
	(*mem_config)->auto_extend      = 1;
	(*mem_config)->extend_block_size= 1024*500;
	
	return 0;
}
void init_trans_redo()
{
//初始化 redo_manager  
init_redo_log_manager();
//配置 config_manager
//config_redo_data_log(char * path,off_t file_max_size)  

// 注意在初始化 事务管理器之前，要先初始化系统序列管理器
init_sys_transaction_manager();
//配置 transaction_manager的 序列值 和  回滚空间最大值
config_sys_transaction_manager(1,DEFAULT_FILE_MAX_SIZE);
 
//扩展事务槽
// extend_transaction_manager();

// 初始化数据日志写者线程
init_trans_redo_data_writer(&sys_trans_redo_data_writer,10);
// 开启 writer 线程写日志
start_trans_redo_data_writer();
}

void dest_trans_redo()
{
	 // 关闭 writer 线程写日志
	 stop_trans_redo_data_writer();
}

void init_mem_no_manager()
{
	init_mem_block_no_manager();
	init_mem_table_no_manager();
	init_mem_index_no_manager();
}

void dest_mem_no_manager()
{
  dest_mem_table_no_manager();
  dest_mem_index_no_manager();
	dest_mem_block_no_manager();
}

int cmp_int(int * a,int * b)
{
	DEBUG( "*a = %d , *b = %d \n",*a,*b);
	return *a == *b;
}

void * thread_fun(void * arg)
{

	
struct mem_table_t  *  mem_table = ((thread_param_test*)arg)->mem_table ;
mem_table_config_t * mem_config  = ((thread_param_test*)arg)->mem_config ;
// 测试插入数据
struct record_t * record_ptr     = NULL ;
long block_no = ((thread_param_test*)arg)->block_no ;
long long  trans_no    = ((thread_param_test*)arg)->trans_no ;

DEBUG("tpt.mem_config->auto_extend=%d !!!!\n",mem_table->config.auto_extend);


int err;
char date1[]="20170101120000";

//DEBUG("str_to_time2(date1) is %ld\n",str_to_time2(date1));

test_table_t  bufe ;
bufe.id 		    = 1;
bufe.try_num 	  = 1;
bufe.try_time   =str_to_time2(date1)  ;

DEBUG("bufe.id =  %ld\n",bufe.id );
DEBUG("bufe.try_num =  %ld\n",bufe.try_num );
DEBUG("bufe.try_time =  %ld\n",bufe.try_time );


char buf[sizeof(test_table_t)] = {0};
memcpy(buf,(char *)&bufe,sizeof(test_table_t));

DEBUG("sizeof(buf) is %ld\n",sizeof(buf));
int for_i = 0;
for(;for_i<sizeof(test_table_t);++for_i)
printf("%02X ",buf[for_i]);
printf("\n");

	//填充1事务，并提交给 缓冲区，供 writer 线程 写掉
mem_trans_data_entry_t * out;
long k=0;
//long end = 1000*500*2;
long end = 10;

for(;k<end;++k){
if(0!=(err=mem_mvcc_insert_record(mem_table,&record_ptr,&block_no, buf	,trans_no))){ERROR("mem_mvcc_insert_record err is %d\n",err);}
//if(0!=(err=mem_mvcc_update_record(mem_table,record_ptr,buf,trans_no,&record_ptr ))){ERROR("mem_mvcc_update_record err is %d\n",err);return 0;}
//if(0!=(err=mem_mvcc_delete_record(mem_table,record_ptr,trans_no 			  ))){ERROR("mem_mvcc_update_record err is %d\n",err);}

//if(k>end/2)
//	{
//	}																		
}


	return 0;
}

/*
* 测试 mem_block 基本功能
*
*
*
*/
int main(int arcv,char * arc[])
{
	printf("main begin at %s\n",GetTime());
	int err;
	init_mem_no_manager();
//__________________________________________
	// 初始化事务相关
	init_trans_redo();
	
//   建测试表，并插入数据
//__________________________________________
// 建物理块
mem_block_t *mb = NULL;
create_block(&mb,"./map_table.dat");
//建逻辑表配置
mem_table_config_t * mem_config = NULL;
// 测试插入数据
struct record_t * record_ptr =NULL;
long block_no;




if(0!=(err=create_mem_table_config(&mem_config,mb,"first_table_name\0")))ERROR("create_mem_table_config err is %d\n",err);
//DEBUG("mem_config is %d\n",mem_config);

//建逻辑表
struct mem_table_t  *  mem_table = NULL;

if(0!=(err=mem_table_create(&mem_table,mem_config)))ERROR("mem_table_create err is %d\n",err);
	err = 0;
DEBUG("RECORD_HEAD_SIZE is %d\n",RECORD_HEAD_SIZE);




//____________________________________________
//分配一个事务槽
long long  trans_no;
if(0!=(err=allocate_trans(&trans_no)))ERROR("allocate_trans[%d] failed,trans_no is %d\n",trans_no,err); 
// 开始一个事务
if(0!=(err=start_trans(trans_no)))ERROR("start_trans failed,trans_no is %d\n",err); 

// 事务 trans_no ，对 mem_table 上排它锁
mem_table_rwlock_by_writer(mem_table,trans_no);


//线程数
int tnum = 1	;
pthread_t th[tnum];

thread_param_test tpt;
tpt.mem_table = mem_table;
tpt.mem_config = mem_config;
tpt.record_ptr = record_ptr;
tpt.block_no = block_no;
tpt.trans_no = trans_no;


int i = 0;
for(;i<tnum;++i){
    int ret;  
   
    ret = pthread_create( &(th[i]), NULL, thread_fun, &tpt ); 
	  if( ret != 0 ){  
        ERROR( "Create log writer thread error!\n");  
        return START_TRANS_REDO_DATA_WRITER_ERR;  
    }  
  }
  
int j = 0;
for(;j<tnum;++j){
    int ret;  
   
    ret = pthread_join( (th[j]), NULL);  
  }





// 查询操作
 std::list<test_table_t> ret_vector;
 char field_name[32] = {"id"};
 char field_name2[32] = {"try_num"};
 int  com_value = 1;
 int  try_value = 1;
 DEBUG("Start to full_talbe_scan\n");
// int ret = full_table_scan_with_con(
//														mem_table,    //表
//														field_name,   //字段名
//														cmp_int,      //字段比较函数
//														&com_value,   //比较字段值
//														trans_no,     //事务ID
//														&ret_vector		//原始结果集
//) ;

compare_list cmp1;
compare_list cmp2;

cmp1.mem_table       			= mem_table;
cmp1.field_name      			= field_name;
cmp1.cmp_field_value 			= &com_value;
cmp1.next 					 			= &cmp2;
cmp1.fun 								  = (void *)cmp_int ;

cmp2.mem_table       			= mem_table;
cmp2.field_name      			= field_name2;
cmp2.cmp_field_value 			= &try_value;
cmp2.next 					 			= NULL;
cmp2.fun                  = (void *)cmp_int ;

int ret =full_table_scan_with_conlist(
														 mem_table,       //表
														 &cmp1,           //比较函数链
														 trans_no,			  //事务ID
													 	 &ret_vector  	  //原始结果集
);



//打印结果集 
std::cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++\n"<<std::endl;
std::for_each(ret_vector.begin(),ret_vector.end(),[](test_table_t& x){
	std::cout<<"========================="<<std::endl;
	std::cout<<"id="<<x.id<<std::endl;
	std::cout<<"try_num="<<x.try_num<<std::endl;
	std::cout<<"try_time="<<x.try_time<<std::endl;
	
	});


// 回滚事务
//if(0!=(err=rollback_trans(trans_no)))ERROR("rollback_trans failed,trans_no is %d\n",err);
// 提交事务
if(0!=(err=commit_trans(trans_no)))DEBUG("commit_trans failed,trans_no is %d\n",err); 


// 事务 trans_no ，对 mem_table 解排它锁
mem_table_rwunlock_by_writer(mem_table,trans_no);
//__________________________________________
  
  // 关闭 writer 线程写日志
  dest_trans_redo();
	dest_mem_no_manager();
	
	//关闭表
if(0!=(err=mem_table_close(mem_table)))ERROR("mem_table_close err is %d\n",err);
	printf("main  end  at %s\n",GetTime());
	return 0;
}
