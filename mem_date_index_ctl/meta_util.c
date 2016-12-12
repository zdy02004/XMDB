#include <stdio.h>
#include "../util/cJSON/cJSON.h"
#include "mem_table_ctl.h"

#ifndef TABLE_CTL
#define TABLE_CTL

//支持大文件
#define _FILE_OFFSET_BITS 64
#define __USE_FILE_OFFSET64
#define __USE_LARGEFILE64
#define _LARGEFILE64_SOURCE

#include "mem_table_ctl.h"

#define CREATE_MEM_TABLE_ERR_NULL_CONFIG_PTR         350001
#define INPUT_JSON_IS_NULL									         350002
#define MEM_CONFIG_TABLE_CREATE_FAILED						   350003
#define CREATE_MEM_TABLE_ERR_NULL_CONFIG             350004
#define CREATE_MEM_TABLE_ERR_NULL_FILE               350005
#define FILE_ERR_NULL_PTR														 350006
#define DDL_ERR_STR_NULL_PTR												 350007
#define DDL_ERR_RECORD_NUM_LESS_ZERO								 350008
#define DDL_ERR_LENGTH_LESS_ZERO										 350009
#define FILE_ERR_OPEN_FAILD													 350010


int mem_table_config_2_json(struct mem_table_config_t *mem_table_config,cJSON* root )
{
	if(mem_table_config == root)return MEM_TABLE_2_	JSON_ERR_NULL_CONFIG_PTR;

	//字段列表
  cJSON  *field_array;
  //内存块列表
  cJSON  *block_array;  
	
	root=cJSON_CreateObject();
	field_array=cJSON_CreateArray();
	block_array=cJSON_CreateArray();
	
	//装入非字段,非内存块信息
	cJSON_AddItemToObject(root, "mem_table_no",   cJSON_CreateNumber(mem_table_config->mem_table_no));
 	cJSON_AddItemToObject(root, "table_name",     cJSON_CreateString(mem_table_config->table_name));
 	cJSON_AddItemToObject(root, "owner_id",       cJSON_CreateNumber(mem_table_config->owner_id));
	cJSON_AddItemToObject(root, "field_used_num", cJSON_CreateNumber(mem_table_config->field_used_num));
  cJSON_AddItemToObject(root, "mem_block_used", cJSON_CreateNumber(mem_table_config->mem_block_used));
  cJSON_AddItemToObject(root, "auto_extend",    cJSON_CreateNumber(mem_table_config->auto_extend));
  cJSON_AddItemToObject(root, "extend_block_size",    cJSON_CreateNumber(mem_table_config->extend_block_size));
  //装入内存块信息
    int i=0;
    struct  mem_block_t * mem_block_temp  = mem_table_config->mem_blocks_table;
    for(;i<mmem_table_config->mem_block_used;++i)
    {
    	  cJSON  *block_array_one = cJSON_CreateObject(); 
    	 	cJSON_AddItemToObject(block_array_one,"file_name",cJSON_CreateString(mem_block_temp->file_name));
    	 	cJSON_AddItemToObject(block_array_one,"block_no",cJSON_CreateNumber(mem_block_temp->block_no));
    	 	cJSON_AddItemToObject(block_array_one,"block_size",cJSON_CreateNumber(mem_block_temp->block_size));
    	 	cJSON_AddItemToObject(block_array_one,"space_size",cJSON_CreateNumber(mem_block_temp->space_size));
    	 	cJSON_AddItemToObject(block_array_one,"high_level",cJSON_CreateNumber(mem_block_temp->high_level));
    	 	cJSON_AddItemToObject(block_array_one,"free_list_head",cJSON_CreateNumber(mem_block_temp->mem_free_list.head));
        
        cJSON_AddItemToArray(block_array,  block_array_one);
    	 	mem_block_temp =  mem_block_temp->next;  	
    }
     		cJSON_AddItemToObject(root,"mem_blocks",block_array);
 		//装入字段信息
 		int j=0;
    struct  struct field_t  * fields_table  = mem_table_config->fields_table;
    for(;j<mem_table_config->field_used_num;++j)
    {
    	 	cJSON* field_one=cJSON_CreateObject();
    	 	//构造一个field
    	 	cJSON_AddItemToObject(field_one, "field_type", cJSON_CreateNumber(fields_table->field_type));    	
    	 	cJSON_AddItemToObject(field_one, "field_name", cJSON_CreateString(fields_table->field_name));    	
    	 	cJSON_AddItemToObject(field_one, "field_size", cJSON_CreateNumber(fields_table->field_size));    	
    	 	cJSON_AddItemToObject(field_one, "field_order", cJSON_CreateNumber(fields_table->field_order));    	
    	 	cJSON_AddItemToObject(field_one, "field_dis", cJSON_CreateNumber(fields_table->field_dis));    	
    	 	cJSON_AddItemToObject(field_one, "has_hash", cJSON_CreateNumber(fields_table->has_hash));    	
    	 	cJSON_AddItemToObject(field_one, "hash_no", cJSON_CreateNumber(fields_table->hash_no));    	    	 	
    	 	cJSON_AddItemToArray(field_array, "field", field_one);    	
    		fields_table++;
    }
        //字段数组装入root
     		cJSON_AddItemToObject(root,"fields",field_array);
  return 0;
}

int json_2_mem_table_config(cJSON* root,struct mem_table_config_t *mem_table_config )
{
	if(NULL == root)return INPUT_JSON_IS_NULL;
		
	//字段列表
  cJSON  *field_array;
  //内存块列表
  cJSON  *block_array;  
	field_array=cJSON_GetObjectItem(root,"fields");
	block_array=cJSON_GetObjectItem(root,"mem_blocks");
	
	struct  mem_block_t * mem_block_temp = (struct  mem_block_t *)malloc(MEM_BLOCK_HEAD_SIZE);
	mem_block_temp->file_name = cJSON_GetObjectItem(block_array,"file_name");

	mem_table_config = (struct mem_table_t *)malloc(MEM_TABLE_SIZE);
	struct field_t      * field_temp     = (struct field_t      *)malloc(FIELD_SIZE);
	
	//读出非字段,非内存块信息
	mem_table_config->mem_table_no 		   =  cJSON_GetObjectItem(root,"mem_table_no");
  mem_table_config->table_name  		   =  cJSON_GetObjectItem(root,"table_name");
  mem_table_config->owner_id  			   =  cJSON_GetObjectItem(root,"owner_id");
  mem_table_config->field_used_num     =  cJSON_GetObjectItem(root,"field_used_num");
  mem_table_config->mem_block_used     =  cJSON_GetObjectItem(root,"mem_block_used");
  mem_table_config->auto_extend 		   =  cJSON_GetObjectItem(root,"auto_extend");
  mem_table_config->extend_block_size  =  cJSON_GetObjectItem(root,"extend_block_size");
	//读出第1个内存块信息
	mem_table_config->mem_blocks_table   =  cJSON_GetObjectItem(root,"mem_blocks");
	//读出第1个字段信息
		
  //读出内存块信息，有待完善
    int i = 1;
    struct  mem_block_t *  mem_block_pre = mem_block_temp;
    for(;i<mmem_table_config->mem_block_used;++i)
    {
				struct  mem_block_t * mem_block_next = (struct  mem_block_t *)malloc(MEM_BLOCK_HEAD_SIZE);
				cJSON* block_one = cJSON_GetArrayItem(block_array,i);
				
				mem_block_next->file_name   = cJSON_GetObjectItem(block_one,"file_name" );
				mem_block_next->block_no    = cJSON_GetObjectItem(block_one,"block_no"  );
				mem_block_next->block_size  = cJSON_GetObjectItem(block_one,"block_size");
				mem_block_next->space_size  = cJSON_GetObjectItem(block_one,"space_size");
				mem_block_next->high_level  = cJSON_GetObjectItem(block_one,"high_level");
				mem_block_next->mem_free_list.head = cJSON_GetObjectItem(block_one,"free_list_head");
			
				//构造 next 链
				mem_block_pre->next = mem_block_next;
				mem_block_pre       = mem_block_next;
    }
 				mem_table_config->mem_blocks_table = mem_block_temp;


 		//读入字段信息
 		struct field_t * fields = (struct field_t * )malloc(FIELD_SIZE*mem_table_config->field_used_num);
 		int j=0;
    for(;j<mem_table_config->field_used_num;++j)
    {
    		cJSON* field_one= cJSON_GetArrayItem(field_array,j);
    		
    	 	//构造一个field
    	 	fields[j]->field_type  = cJSON_GetObjectItem(field_one,"field_type");
    	 	fields[j]->field_name  = cJSON_GetObjectItem(field_one,"field_name");
    	 	fields[j]->field_size  = cJSON_GetObjectItem(field_one,"field_size");
    	 	fields[j]->field_order = cJSON_GetObjectItem(field_one,"field_order");
    	 	fields[j]->field_dis   = cJSON_GetObjectItem(field_one,"field_dis");
    	 	fields[j]->has_hash    = cJSON_GetObjectItem(field_one,"has_hash");
    	 	fields[j]->hash_no     = cJSON_GetObjectItem(field_one,"hash_no");
    	 	
    }
        //字段数组装入 mem_table_config
        mem_table_config->fields_table = fields;
     		
  return 0;
}

//建表
inline int mem_config_table_create(struct mem_table_t * mem_table)
{
//构造2个字段
struct field_t * field_tables = (struct field_t *)malloc(sizeof(2*FIELD_SIZE));

field_tables[0]->field_type = FIELD_TYPE_LONGLONG;
strcpy(field_tables[0]->field_name,"id");
field_tables[0]->field_order = 0;
field_tables[1]->field_size = 4;

field_tables[1]->field_type = FIELD_TYPE_STR;
strcpy(field_tables[1]->field_name,"content");
field_tables[1]->field_order = 1;
field_tables[1]->field_size = 1020;

//构造元数据内存块
struct  mem_block_t * mem_block = (struct  mem_block_t *)malloc(MEM_BLOCK_HEAD_SIZE);

strcpy(mem_block->file_name,"meta_table.dat");
INIT_MEM_BLOCK(mem_block)

//配置接入
mem_table_config->fields_table = field_tables;
mem_table_config->mem_blocks_table = mem_block;


//元数据内存块配置表信息
struct mem_table_config_t * mem_table_config = (struct mem_table_config_t * )malloc(MEM_TABLE_CONFIG_SIZE);


//建表
if( mem_table_create(  mem_table,  mem_table_config ) )
	{
		return  MEM_CONFIG_TABLE_CREATE_FAILED;
	}
                     
	return 0;
}



// 找到文件对应的行写入
inline int
mem_config_table_get_record(const struct mem_table_t * mem_config_table,
																														 long mem_table_no,
																														 struct record_t * record_ptr /*  */
																														 )
{
	if(NULL == mem_config_table) return CREATE_MEM_TABLE_ERR_NULL_CONFIG;
	if(NULL == fp							 ) return CREATE_MEM_TABLE_ERR_NULL_FILE  ;
	mem_tablee->record_size = 1024;  
	//这里应该找第一个块 	
	record_ptr = (struct record_t *) ( mem_config_table->mem_blocks_table->space_start_addr + mem_table_no * mem_config_table->mem_blocks_table->record_size );
	
	return 0;
}

//插入和修改都使用这个函数，ddl 不支持事务
inline int 
mem_config_table_update_record( const struct mem_table_t * mem_config_table,
																cJSON* root, /*  */	
																struct record_t * record_ptr,
																FILE *file
															)
{
	if(NULL == mem_config_table) return CREATE_MEM_TABLE_ERR_NULL_CONFIG;
	if(NULL == fp							 ) return CREATE_MEM_TABLE_ERR_NULL_FILE  ;

	
	int ret =  mem_table_update_record(mem_config_table ,record_ptr,(void *)(cJSON_Print(root)));
	if( ret!=0  )return ret;
	int ret2 =  ddl_write_file(file,record_ptr->record_num,1024+RECORD_HEAD_SIZE,(void *)(cJSON_Print(root)); //// 要定义
	if( ret2!=0 )return ret2;
	cJSON_Delete(root);
	return 0;
}

//删除表，ddl 不支持事务
inline int 
mem_config_table_delete_record( const struct mem_table_t * mem_config_table,
																cJSON* root, /*  */	
																struct record_t * record_ptr,
																FILE *file
															)
{
	if(NULL == mem_config_table) return CREATE_MEM_TABLE_ERR_NULL_CONFIG;
	if(NULL == fp							 ) return CREATE_MEM_TABLE_ERR_NULL_FILE  ;

	
	int ret =  mem_table_delete_record(mem_config_table ， record_ptr,(void *)(cJSON_Print(root)));
	if( ret!=0  )return ret;
	int ret2 =  ddl_delete_file(file,record_ptr->record_num,1024+RECORD_HEAD_SIZE,(void *)(cJSON_Print(root)); //// 要定义
	if( ret2!=0 )return ret2;
	cJSON_Delete(root);
	return 0;
}

inline int 
ddl_write_file(FILE *fp,
								unsigned  long long record_num,
								long length,
								void *str)
{	

	  if(NULL ==  fp )	return  FILE_ERR_NULL_PTR;
	  if(NULL == str )	return  DDL_ERR_STR_NULL_PTR;
	  if(record_num<0)  return	DDL_ERR_RECORD_NUM_LESS_ZERO;
	  if(length<=0   )  return	DDL_ERR_LENGTH_LESS_ZERO;
	  	
	  fseeko(fp, record_num*length+sizeof(unsigned  long long), SEEK_SET);
		fwrite("1", 1, 1, fp);
		
	  fseeko(fp, record_num*length+RECORD_HEAD_SIZE, SEEK_SET);
    return fwrite(str, 1024, 1, fp);
	
}
								
								

inline int 
ddl_delete_file(FILE *fp,
								unsigned  long long record_num,
								long length
								)
{
		if(NULL ==  fp )	return  FILE_ERR_NULL_PTR;
	  if(NULL == str )	return 	DDL_ERR_STR_NULL_PTR;
	  if(record_num<0)  return	DDL_ERR_RECORD_NUM_LESS_ZERO;
	  if(length<=0   )  return	DDL_ERR_LENGTH_LESS_ZERO;
	  	
	//行是否使用 开关——关
	fseeko(fp, record_num*length+sizeof(unsigned  long long), SEEK_SET);
	return fwrite("0", 1, 1, fp);
	
}

//刷入磁盘
inline int 
ddl_commit(FILE *fp)
{
	//刷入磁盘
	if(NULL ==  fp )	return FILE_ERR_NULL_PTR;
	return fflush(fp);
}

//打开 ddl 文件
inline int 
open_ddl_file(char *file_name,FILE *fp )
{
	//刷入磁盘
	if(NULL ==  fp )	return FILE_ERR_NULL_PTR;
	if(NULL !=(fp= fopen(fp,"r+"))) 
		return 0;
	else return FILE_ERR_OPEN_FAILD;
}

inline int 
close_ddl_file(FILE *fp )
{
	//刷入磁盘,并关闭文件
	return fclose(  fp );
}

#endif 