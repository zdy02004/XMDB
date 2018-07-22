#include "../../mem_table_mvcc_op.h"
#include "../../mem_index_no_manager.h"
#include "../../table_meta.h"


int create_block(mem_block_t **mb,char * file_name)
{
	DEBUG("in create_block\n");

	//创建块
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//配置块描述符
	mem_block_config( *mb  ,1024*1024*10 , file_name );
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
	(*mem_config)->extend_block_size= 1024*1024*500;
	
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

//strcat(sys_meta_manager.save_path,".");

getcwd(sys_meta_manager.save_path,sizeof(sys_meta_manager.save_path));   
table_meta_save( mem_table);

struct mem_table_t  *  mem_table2 = (struct mem_table_t  *)malloc(MEM_TABLE_SIZE);

table_meta_load(mem_table2,"first_table_name");

DEBUG("mem_table2->config.table_name is %s\n",mem_table2->config.table_name);

free(mem_table2);


dest_mem_no_manager();
	
	//关闭表
if(0!=(err=mem_table_close(mem_table)))ERROR("mem_table_close err is %d\n",err);
	printf("main  end  at %s\n",GetTime());
	return 0;
}
