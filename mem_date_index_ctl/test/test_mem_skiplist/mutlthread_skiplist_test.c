#include "../../mem_skiplist_index.h"
#define START_TRANS_REDO_DATA_WRITER_ERR  90008

// 线程参数
typedef struct thread_param_test
{
	mem_skiplist_index_t *mem_skiplist_index  ;
	mem_table_config_t * mem_config;
// 测试插入数据
struct record_t * record_ptr;
long block_no;
long long  trans_no;
}thread_param_test;



void * thread_fun(void * arg)
{
mem_skiplist_index_t *mem_skiplist_index   = ((thread_param_test*)arg)->mem_skiplist_index ;

long k=0;
//long end = 1000*500*2;
//long end = 10000*2;
long end = 10000*10;
long array[end];

for(;k<end;++k){
   //插入索引
mem_skiplist_entry_t index1;
index1.lkey = random();
index1.block_no =1;
index1.record_num = 1;

array[k] = index1.lkey;
struct  record_t * last_insert_skiplist_entry;
//TICK
mem_skiplist_insert( mem_skiplist_index ,&index1,&last_insert_skiplist_entry );
//TOCK	
}

DEBUG("START DELETE!\n");
k=0;
for(;k<end;++k){
//删除索引
mem_skiplist_entry_t index1;
index1.lkey = array[k];
index1.block_no =1;
index1.record_num = 1;

//mem_skiplist_delete( mem_skiplist_index ,&index1 );										
}

}


int create_block(mem_block_t **mb,char * file_name)
{
	DEBUG("in create_block\n");

	//创建块
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//配置块描述符
	mem_block_config( *mb  ,1024 , file_name );
		//初始化块
	//INIT_MEM_BLOCK(*mb)
	
	DEBUG("fd = %d\n",(*mb)->fd);
	return 0;
}


int create_mem_table_config(mem_table_config_t ** mem_config,mem_block_t *mb,char * table_name)
{
	DEBUG("in create_mem_table_config\n");

	*mem_config = (mem_table_config_t *) malloc(MEM_TABLE_CONFIG_SIZE);

	(*mem_config)->owner_id = 1;
	strcpy((*mem_config)->table_name,table_name);
	
	struct field_t *fields_table  = (struct field_t *) malloc(FIELD_SIZE*2);
	(*mem_config)->fields_table      = fields_table;
	
	fields_table[0].field_type    = FIELD_TYPE_INT;
	strcpy(fields_table[0].field_name,"id\0");
	fields_table[1].field_type   = FIELD_TYPE_INT;
	strcpy(fields_table[1].field_name,"try_num\0");
	
	(*mem_config)->field_used_num   = 2;
	(*mem_config)->mem_blocks_table = mb;
	(*mem_config)->mem_block_used   = 1;
	(*mem_config)->auto_extend      = 1;
	(*mem_config)->extend_block_size= 1024;
	
	return 0;
}

int create_mem_skiplist_config(mem_skiplist_index_config_t** skiplist_config,
															unsigned  long long heap_block_size,
															char *index_name,
															int level)
{
	*skiplist_config =(mem_skiplist_index_config_t *)malloc(MEM_SKIPLIST_CONFIG_SIZE);
	(*skiplist_config)->index_no			  = 1;
	(*skiplist_config)->owner_table_no  = 1;
	strcpy((*skiplist_config)->index_name,index_name);
	(*skiplist_config)->heap_block_size = heap_block_size;
	(*skiplist_config)->max_level = level;
	
	return 0;
}

/*
* 测试 mem_skiplist 基本功能
*
*
*
*/
int main(int arcv,char * arc[])
{
	init_mem_block_no_manager();
	init_mem_table_no_manager();
  init_mem_index_no_manager();
	
// 建原表物理块
mem_block_t *mb = NULL;
create_block(&mb,"./skiplist_table.dat");
//建原表配置
mem_table_config_t * mem_config = NULL;
int err;
if(0!=(err=create_mem_table_config(&mem_config,mb,"./first_table_name\0")))DEBUG("create_mem_table_config err is %d\n",err);
DEBUG("mem_config is %d\n",mem_config);
//建原表
struct mem_table_t  			* mem_table 			= NULL;
if(0!=(err=mem_table_create(&mem_table,mem_config)))DEBUG("mem_table_create err is %d\n",err);
	
	

//建跳表索引配置
mem_skiplist_index_config_t * skiplist_config		= NULL;
//建skiplist配置信息
if(0!=(err=create_mem_skiplist_config(&skiplist_config,2048*102400,"./first_index_name\0",16)))DEBUG("mem_table_create err is %d\n",err);
//建跳表索引
mem_skiplist_index_t  			* mem_skiplist_index	= NULL;
if(0!=(err=mem_skiplist_create(&mem_skiplist_index,mem_table,skiplist_config)))DEBUG("mem_table_create err is %d\n",err);
// 初始化跳表 
if(0!=(err=mem_skiplist_init( mem_skiplist_index)))DEBUG("mem_table_create err is %d\n",err);

DEBUG("mem_skiplist_index is %0x\n",mem_skiplist_index);


//线程数
int tnum = 5;
pthread_t th[tnum];

thread_param_test tpt;
tpt.mem_skiplist_index = mem_skiplist_index;

	

int i = 0;
for(;i<tnum;++i){
    int ret;  
   
    ret = pthread_create( &(th[i]), NULL, thread_fun, &tpt ); 
	  if( ret != 0 ){  
        ERROR( "Create log writer thread error!\n");  
        return START_TRANS_REDO_DATA_WRITER_ERR;  
    }  
  }
  TICK
int j = 0;
for(;j<tnum;++j){
    int ret;  
   
    ret = pthread_join( (th[j]), NULL);  
  }



	printf("main  used " );
	TOCK
 // mem_skiplist_print_each_level(mem_skiplist_index);


if(0!=(err=mem_skiplist_index_close(mem_skiplist_index)))DEBUG("mem_skiplist_index_close err is %d\n",err);

if(0!=(err=mem_table_close(mem_table)))DEBUG("mem_table_close err is %d\n",err);
  dest_mem_table_no_manager();
	dest_mem_block_no_manager();
	dest_mem_index_no_manager();
	return 0;
}
