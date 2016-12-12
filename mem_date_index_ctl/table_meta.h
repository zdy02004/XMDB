#ifndef TABLE_META
#define TABLE_META
#include "mem_hash_index.h"
#include "mem_rbtree_index.h"

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include "rwlock.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TABLE_META_PATH_NULL 440001
#define OPENED_FAILED				 440002


//对每个表建3个文件来存储表的元信息
//这3个文件存储在同一个文件夹下
typedef struct  meta_manager
{
char            save_path[512];          //存储文件夹地址 save_path_table_info  save_path_field_info  save_path_block_info

}meta_manager;

static meta_manager sys_meta_manager;



// 检查路径是否合法
int table_meta_check_path(char * path)
{
	if(NULL == path){
		ERROR("TABLE_META_PATH_NULL\n");
		return TABLE_META_PATH_NULL;
	}
	
	if((access(path,F_OK))!=-1) {
		return 0;
	}
	else
		{
			DEBUG("mkdir %s\n",path);
			return mkdir( path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			
		}
}

int table_meta_save(mem_table_t * mem_table)
{
	DEBUG("table_meta_save \n");
char path[512];
char table_info_path[512];
char field_info_path[512];
char block_info_path[512];

memset(table_info_path,0,512);
memset(field_info_path,0,512);
memset(block_info_path,0,512);


//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,mem_table->config.table_name);



	DEBUG("path is %s \n",path);

//新建目录
int err = table_meta_check_path(path);
if(err)return err;

strcat(path,"/");
strcat(path,mem_table->config.table_name);

strcat(table_info_path,path);
strcat(table_info_path,"_table_info");

strcat(field_info_path,path);
strcat(field_info_path,"_field_info");

strcat(block_info_path,path);
strcat(block_info_path,"_block_info");
	
FILE * table_info_fd;
FILE * field_info_fd;
FILE * block_info_fd;

	DEBUG("table_info_path is %s \n",table_info_path);
	DEBUG("field_info_path is %s \n",field_info_path);
	DEBUG("block_info_path is %s \n",block_info_path);

table_info_fd = fopen(table_info_path, "wt");
field_info_fd = fopen(field_info_path, "wt");
block_info_fd = fopen(block_info_path, "wt");

if(table_info_fd<=0)
{
	ERROR("%s opened failed! \n",table_info_path);
	err = -1;
}

if(field_info_fd<=0)
{
	ERROR("%s opened failed! \n",field_info_fd);
	err = -1;
}

if(block_info_fd<=0)
{
	ERROR("%s block_info_fd failed! \n",block_info_fd);
	err = -1;
}
	
	mem_table_config_t *config = &(mem_table->config);
	
	int ret1,ret2,ret3;
	ret1 = !(fwrite(&(mem_table->config), MEM_TABLE_CONFIG_SIZE, 1, table_info_fd)==1);
   
	int field_used_num = config->field_used_num;
	struct field_t * fields_table = config->fields_table;
	int i = 0;
	for(;i<field_used_num;++i)
	{
		ret2 = !(fwrite(&(fields_table[i]), FIELD_SIZE, 1, field_info_fd)==1);
	}
	
	int mem_block_used = config->mem_block_used;
	struct mem_block_t * block_table = config->mem_blocks_table;

	int j = 0;
	for(;j<mem_block_used;++j)
	{
		ret3 = !(fwrite(&(block_table[j]), MEM_BLOCK_HEAD_SIZE, 1, block_info_fd)==1);
	}
	
	 fclose( table_info_fd );
	 fclose( field_info_fd );
	 fclose( block_info_fd );
   
   return err&ret1&ret2&ret3;
}


int table_meta_load(mem_table_t * mem_table,char * table_name)
{

char path[512];
memset(path,0,512);

//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,table_name);
strcat(path,"/");
strcat(path,table_name);

DEBUG("path is %s \n",path);

char table_info_path[512];
char field_info_path[512];
char block_info_path[512];

memset(table_info_path,0,512);
memset(field_info_path,0,512);
memset(block_info_path,0,512);


strcat(table_info_path,path);
strcat(table_info_path,"_table_info");

strcat(field_info_path,path);
strcat(field_info_path,"_field_info");

strcat(block_info_path,path);
strcat(block_info_path,"_block_info");
	
FILE * table_info_fd;
FILE * field_info_fd;
FILE * block_info_fd;

int err;

table_info_fd = fopen(table_info_path, "rt");
field_info_fd = fopen(field_info_path, "rt");
block_info_fd = fopen(block_info_path, "rt");

if(table_info_fd<=0)
{
	ERROR("%s opened failed! \n",table_info_path);
	err = -1;
}

if(field_info_fd<=0)
{
	ERROR("%s opened failed! \n",field_info_fd);
	err = -1;
}

if(block_info_fd<=0)
{
	ERROR("%s block_info_fd failed! \n",block_info_fd);
	err = -1;
}
	
	mem_table_config_t *config = &(mem_table->config);
	
	int ret1,ret2,ret3;
	ret1 = !(fread(&(mem_table->config), MEM_TABLE_CONFIG_SIZE, 1, table_info_fd)==1);
   
	int field_used_num = config->field_used_num;
	struct field_t * fields_table = config->fields_table;
	int i = 0;
	for(;i<field_used_num;++i)
	{
		ret2 = !(fread(&(fields_table[i]), FIELD_SIZE, 1, field_info_fd)==1);
	}
	
	int mem_block_used = config->mem_block_used;
	struct mem_block_t * block_table = config->mem_blocks_table;

	int j = 0;
	for(;j<mem_block_used;++j)
	{
		ret3 = !(fread(&(block_table[j]), MEM_BLOCK_HEAD_SIZE, 1, block_info_fd)==1);
	}
	
	 fclose( table_info_fd );
	 fclose( field_info_fd );
	 fclose( block_info_fd );
   
   return err&ret1&ret2&ret3;
}

/////////////////////////////////////////

int hash_index_meta_save(mem_hash_index_t * index)
{
char path[512];

memset(path,0,512);

//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,index->config.index_name);
strcat(path,"/");

int err;
//新建目录
err = table_meta_check_path(path);
if(err)return err;

FILE * index_fd;
strcat(path,index->config.index_name);
strcat(path,"_index_info");

index_fd = fopen(path, "wt");


if(index_fd<=0)
{
	ERROR("%s opened failed! \n",path);
	err = -1;
}

	mem_hash_index_config_t *config = &(index->config);
	
	int ret1,ret2,ret3;
	ret1 = !(fwrite(&(index->config), MEM_HASH_CONFIG_SIZE, 1, index_fd)==1);

	ret2 = table_meta_save(index->array_space);
	ret3 = table_meta_save(index->linked_space);

	fclose( index_fd );
   
  return err&ret1&ret2&ret3;

}

int hash_index_meta_load(mem_hash_index_t * index,char * index_name)
{
	char path[512];
	memset(path,0,512);

//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,index_name);
strcat(path,"/");
strcat(path,index_name);
strcat(path,"_index_info");

	
FILE * index_fd;
int err;
index_fd = fopen(path, "rt");


if(index_fd<=0)
{
	ERROR("%s opened failed! \n",path);
	err = -1;
}

	mem_hash_index_config_t *config = &(index->config);
	
	int ret1,ret2,ret3;
	ret1 = !(fread(&(index->config), MEM_HASH_CONFIG_SIZE, 1, index_fd)==1);

char array_space_path[512];
char linked_space_path[512];

strcpy(array_space_path,config->index_name);
strcpy(linked_space_path,config->index_name);
strcat(array_space_path,"_array");
strcat(linked_space_path,"_link");

	ret2 = table_meta_load(index->array_space,array_space_path);
	ret3 = table_meta_load(index->linked_space,linked_space_path);

	fclose( index_fd );
   
  return err&ret1&ret2&ret3;
}

///////////////////////////////////////////////////////
int rbtree_index_meta_save(mem_rbtree_index_t * index)
{
char path[512];
char heap_space_path[512];

memset(path,0,512);
memset(heap_space_path,0,512);


//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,index->config.index_name);
strcat(path,"/");

int err;
//新建目录
err = table_meta_check_path(path);
if(err)return err;
	
strcat(heap_space_path,path);
strcat(path,index->config.index_name);
strcat(heap_space_path,"_heap_info");

FILE * heap_info_fd;
FILE * index_fd;


index_fd = fopen(path, "wt");

if(index_fd<=0)
{
	ERROR("%s opened failed! \n",path);
	err = -1;
}
	int ret1,ret2;
	ret1 = !(fwrite(&(index->config), MEM_RBTREE_INDEX_SIZE, 1, index_fd)==1);

	ret2 = table_meta_save(index->heap_space);

	fclose( index_fd );
   
  return err&ret1&ret2;




	return 0;
}

int rbtree_index_meta_load(mem_rbtree_index_t * index,char * index_name)
{
char path[512];
char heap_space_path[512];

memset(path,0,512);
memset(heap_space_path,0,512);


//将表名拼入路径
strcpy(path,sys_meta_manager.save_path);
strcat(path,"/");
strcat(path,index_name);
strcat(heap_space_path,index_name);
strcat(heap_space_path,"_heap");
strcat(path,"/");
strcat(path,index_name);

FILE * index_fd;



index_fd = fopen(path, "rt");

int err;
if(index_fd<=0)
{
	ERROR("%s opened failed! \n",path);	
	err = -1;
}

 	int ret1,ret2;
	ret1 = !(fread(&(index->config), MEM_RBTREE_INDEX_SIZE, 1, index_fd)==1);
	ret2 = table_meta_load(index->heap_space,heap_space_path);

	fclose( index_fd );
   
  return ret1&ret2;



	return 0;
}


int index_meta_save(void * index,int index_class)
{
	if(index_class == 1)return hash_index_meta_save(index);
		
	if(index_class == 2)return rbtree_index_meta_save(index);
}


int index_meta_load(void * index,char *path ,int index_class)
{
	if(index_class == 1)return hash_index_meta_load(index,path);
		
	if(index_class == 2)return rbtree_index_meta_load(index,path);
}



#endif 