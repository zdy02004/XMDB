#include "../../mem_hash_index.h"
#include "../../mem_block_no_manager.h"
#include "../../mem_index_no_manager.h"
#include "../../mem_table_no_manager.h"
#include "../../table_meta.h"
#include "../../mem_rbtree_index.h"


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

int create_mem_rbtree_config(mem_rbtree_index_config_t** rbtree_config,unsigned  long long heap_block_size,char *index_name)
{
	*rbtree_config =(mem_rbtree_index_config_t *)malloc(MEM_RBTREE_CONFIG_SIZE);
	(*rbtree_config)->index_no			  = 1;
	(*rbtree_config)->owner_table_no  = 1;
	strcpy((*rbtree_config)->index_name,index_name);
	(*rbtree_config)->heap_block_size = heap_block_size;
	
	return 0;
}

/*
* 测试 mem_rbtree 基本功能
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
create_block(&mb,"./rbtree_table.dat");
//建原表配置
mem_table_config_t * mem_config = NULL;
int err;
if(0!=(err=create_mem_table_config(&mem_config,mb,"./first_table_name\0")))DEBUG("create_mem_table_config err is %d\n",err);
DEBUG("mem_config is %d\n",mem_config);
//建原表
struct mem_table_t  			* mem_table 			= NULL;
if(0!=(err=mem_table_create(&mem_table,mem_config)))DEBUG("mem_table_create err is %d\n",err);
	
	

//建红黑树索引配置
mem_rbtree_index_config_t * rbtree_config		= NULL;
//建rbtree配置信息
if(0!=(err=create_mem_rbtree_config(&rbtree_config,2048,"first_index_name")))DEBUG("mem_table_create err is %d\n",err);
//建红黑树索引
mem_rbtree_index_t  			* mem_rbtree_index	= NULL;
if(0!=(err=mem_rbtree_create(&mem_rbtree_index,mem_table,rbtree_config)))DEBUG("mem_table_create err is %d\n",err);

DEBUG("mem_rbtree_index is %0x\n",mem_rbtree_index);


getcwd(sys_meta_manager.save_path,sizeof(sys_meta_manager.save_path));   
rbtree_index_meta_save(mem_rbtree_index);



mem_rbtree_index_t  			* mem_rbtree2 = (mem_rbtree_index_t  *)malloc(MEM_RBTREE_INDEX_SIZE);
mem_rbtree2->heap_space  =  (struct mem_table_t  *)malloc(MEM_TABLE_SIZE);

rbtree_index_meta_load(mem_rbtree2,"first_index_name");

DEBUG("mem_rbtree2->config.index_name is %s\n",mem_rbtree2->config.index_name);


//free(mem_rbtree2->heap_space );
free(mem_rbtree2);



if(0!=(err=mem_rbtree_index_close(mem_rbtree_index)))DEBUG("mem_rbtree_index err is %d\n",err);

if(0!=(err=mem_table_close(mem_table)))DEBUG("mem_table_close err is %d\n",err);
  dest_mem_table_no_manager();
  dest_mem_index_no_manager();
	dest_mem_block_no_manager();
	return 0;
}
