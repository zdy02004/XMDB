#include "../../mem_tree_iterator.h"


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
if(0!=(err=create_mem_rbtree_config(&rbtree_config,2048,"./first_index_name\0")))DEBUG("mem_table_create err is %d\n",err);
//建红黑树索引
mem_rbtree_index_t  			* mem_rbtree_index	= NULL;
if(0!=(err=mem_rbtree_create(&mem_rbtree_index,mem_table,rbtree_config)))DEBUG("mem_table_create err is %d\n",err);



////// 测试插入数据
////struct record_t * record_ptr =NULL;
////long block_no;
////char buf[]="abcd";
////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf)))DEBUG("mem_table_insert_record err is %d\n",err);
////char buf1[]="xyzm";
////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf1)))DEBUG("mem_table_insert_record err is %d\n",err);
//////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf1)))DEBUG("mem_table_insert_record err is %d\n",err);
////
////// 测试修改数据
////char buf2[]="opqw";
////if(0!=(err=mem_table_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
//////if(0!=(err=mem_table_force_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
//////if(0!=(err=mem_table_safe_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
////
////// 测试读取数据
////char buf3[256]={};
////if(0!=(err=mem_table_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
//////if(0!=(err=mem_table_force_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
//////if(0!=(err=mem_table_safe_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
////
////// 测试删除数据
//////if(0!=(err=mem_table_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
//////if(0!=(err=mem_table_force_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
////if(0!=(err=mem_table_safe_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
	//  DEBUG("mem_rbtree_index_table's name is %s, addr is %0x .\n",mem_rbtree_index->heap_space->config.table_name,mem_rbtree_index->heap_space->config);



//插入索引
mem_rbtree_entry_t index1;
index1.rbtree_lkey = 1;
index1.block_no =1;
index1.record_num = 1;

//插入索引
mem_rbtree_entry_t index2;
index2.rbtree_lkey = 2;
index2.block_no =4;
index2.record_num = 4;

//插入索引
mem_rbtree_entry_t index3;
index3.rbtree_lkey = 3;
index3.block_no =3;
index3.record_num = 3;

//插入索引
mem_rbtree_entry_t index5;
index5.rbtree_lkey = 5;
index5.block_no =5;
index5.record_num = 5;

//插入索引
mem_rbtree_entry_t index6;
index6.rbtree_lkey = 6;
index6.block_no =6;
index6.record_num = 6;

if(0!=(err=mem_rbtree_insert(mem_rbtree_index, mem_rbtree_index->root,&index1)))DEBUG("mem_rbtree_insert err is %d\n",err);
if(0!=(err=mem_rbtree_insert(mem_rbtree_index, mem_rbtree_index->root,&index2)))DEBUG("mem_rbtree_insert err is %d\n",err);
if(0!=(err=mem_rbtree_insert(mem_rbtree_index, mem_rbtree_index->root,&index3)))DEBUG("mem_rbtree_insert err is %d\n",err);
if(0!=(err=mem_rbtree_insert(mem_rbtree_index, mem_rbtree_index->root,&index5)))DEBUG("mem_rbtree_insert err is %d\n",err);
if(0!=(err=mem_rbtree_insert(mem_rbtree_index, mem_rbtree_index->root,&index6)))DEBUG("mem_rbtree_insert err is %d\n",err);


//mem_rbtree_entry_t * index4;
//mem_rbtree_entry_t * index11;
//
//if(0!=(err=mem_rbtree_search(mem_rbtree_index, mem_rbtree_index->root,3,&index4)))DEBUG("mem_rbtree_search err is %d\n",err);
//if(0!=(err=mem_rbtree_delete(mem_rbtree_index, mem_rbtree_index->root,   index4)))DEBUG("mem_rbtree_delete err is %d\n",err);
//	if(0!=(err=mem_rbtree_delete(mem_rbtree_index, mem_rbtree_index->root,   index4)))DEBUG("mem_rbtree_delete err is %d\n",err);

//使用此函数查找 >= key 的第一个节点
//if(0!=(err= mem_rbtree_upper_bound(
//																	mem_rbtree_index,
//																	mem_rbtree_index->root,
//																	0,
//																	&index11
//																	)))DEBUG("mem_rbtree_upper_bound err is %d\n",err);;
//
mem_rbtree_entry_t *  right = mem_rbtree_right(mem_rbtree_index,mem_rbtree_index->root);
mem_rbtree_entry_t *  left  = mem_rbtree_left(mem_rbtree_index,mem_rbtree_index->root);
mem_rbtree_entry_t *  left_left  = mem_rbtree_left(mem_rbtree_index,left);
mem_rbtree_entry_t *  left_left_left  = mem_rbtree_left(mem_rbtree_index,left_left);
//
//
DEBUG("(root->rbtree_lkey,root->block_no,root->record_num) = (%d,%d,%d,%d)\n",mem_rbtree_index->root->rbtree_lkey,mem_rbtree_index->root->block_no,mem_rbtree_index->root->record_num,mem_rbtree_index->root->color);
DEBUG("(left->rbtree_lkey,left->block_no,left->record_num) = (%d,%d,%d,%d)\n",left->rbtree_lkey,left->block_no,left->record_num,left->color);
DEBUG("(right->rbtree_lkey,right->block_no,right->record_num) = (%d,%d,%d,%d)\n",right->rbtree_lkey,right->block_no,right->record_num,right->color);
DEBUG("(left_left->rbtree_lkey,left_left->block_no,left_left->record_num) = (%d,%d,%d,%d)\n",left_left->rbtree_lkey,left_left->block_no,left_left->record_num,left_left->color);
DEBUG("( left_left_left->lkey,left_left_left->block_no,left_left_left->record_num) = (%d,%d,%d,%d)\n",left_left_left->rbtree_lkey,left_left_left->block_no,left_left_left->record_num,left_left_left->color);

// 关联中序遍历迭代器-->提供升序排序功能
struct rb_tree_mid_iterator_t it;
rb_tree_mid_iterator_init(&it, mem_rbtree_index);
mem_rbtree_entry_t * result;
while(
			NULL!=
			( result = rb_tree_mid_iterator_next(&it) )
			)
{
			DEBUG(">>>>>>  %ld\n",result->rbtree_lkey);	
};

// 关联降序遍历迭代器-->提供倒序排序功能
struct rb_tree_after_iterator_t it2;
rb_tree_after_iterator_init(&it2, mem_rbtree_index);
while(
			NULL!=
			( result = rb_tree_after_iterator_next(&it2) )
			)
{
			DEBUG(">>>>>>  %ld\n",result->rbtree_lkey);	
};


//DEBUG("( index11->lkey,index11->block_no,index11->record_num) = (%d,%d,%d,%d)\n",index11->rbtree_lkey,index11->block_no,index11->record_num,left_left_left->color);


if(0!=(err=mem_rbtree_index_close(mem_rbtree_index)))DEBUG("mem_rbtree_index_close err is %d\n",err);

if(0!=(err=mem_table_close(mem_table)))DEBUG("mem_table_close err is %d\n",err);

	dest_mem_block_no_manager();
	return 0;
}
