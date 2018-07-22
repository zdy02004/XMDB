#include "../../mem_hash_index.h"
#include "../../mem_block_no_manager.h"
#include "../../mem_index_no_manager.h"
#include "../../mem_table_no_manager.h"

int create_block(mem_block_t **mb,char * file_name)
{
	DEBUG("in create_block\n");

	//������
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//���ÿ�������
	mem_block_config( *mb  ,1024 , file_name );
		//��ʼ����
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

int create_mem_hash_config(		mem_hash_index_config_t** hash_config ,
															unsigned  long long array_block_size  ,
															unsigned  long long link_block_size ,
															int                 div               ,
															char *index_name										)
{
	(*hash_config) =(mem_hash_index_config_t *)malloc(MEM_HASH_CONFIG_SIZE);
	//(*hash_config)->index_no			 	 = 1;
	(*hash_config)->owner_table_no 	 = 1;
	strcpy((*hash_config)->index_name,index_name);
	(*hash_config)->array_block_size = array_block_size;
	(*hash_config)->link_block_size  = link_block_size ;
	(*hash_config)->div              = div;
	return 0;
}

/*
* ���� mem_hash ��������
*
*
*
*/
int main(int arcv,char * arc[])
{
	init_mem_block_no_manager();
	init_mem_table_no_manager();
	init_mem_index_no_manager();
// ��ԭ�������
mem_block_t *mb = NULL;
create_block(&mb,"./hash_table.dat");
//��ԭ������
mem_table_config_t * mem_config = NULL;
int err;
if(0!=(err=create_mem_table_config(&mem_config,mb,"./first_table_name\0")))DEBUG("create_mem_table_config err is %d\n",err);
DEBUG("mem_config is %d\n",mem_config);
//��ԭ��
struct mem_table_t  			* mem_table 			= NULL;
if(0!=(err=mem_table_create(&mem_table,mem_config)))DEBUG("mem_table_create err is %d\n",err);
	
	

//�� hash ��������
mem_hash_index_config_t * hash_config		= NULL;
//�� hash ������Ϣ
if(0!=(err=create_mem_hash_config(&hash_config,2048,1024,3,"./first_hash_name\0")))DEBUG("mem_hash_index_create err is %d\n",err);
//�� hash ����
mem_hash_index_t  			* mem_hash_index	= NULL;
if(0!=(err=mem_hash_index_create(&mem_hash_index,mem_table,hash_config)))DEBUG("mem_hash_index_create err is %d\n",err);



////// ���Բ�������
////struct record_t * record_ptr =NULL;
////long block_no;
////char buf[]="abcd";
////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf)))DEBUG("mem_table_insert_record err is %d\n",err);
////char buf1[]="xyzm";
////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf1)))DEBUG("mem_table_insert_record err is %d\n",err);
//////if(0!=(err=mem_table_insert_record(mem_table,&record_ptr,&block_no,buf1)))DEBUG("mem_table_insert_record err is %d\n",err);
////
////// �����޸�����
////char buf2[]="opqw";
////if(0!=(err=mem_table_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
//////if(0!=(err=mem_table_force_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
//////if(0!=(err=mem_table_safe_update_record(mem_table,record_ptr,buf2)))DEBUG("mem_table_update_record err is %d\n",err);
////
////// ���Զ�ȡ����
////char buf3[256]={};
////if(0!=(err=mem_table_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
//////if(0!=(err=mem_table_force_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
//////if(0!=(err=mem_table_safe_read_record(mem_table,record_ptr,buf3)))DEBUG("mem_table_read_record err is %d\n",err);
////
////// ����ɾ������
//////if(0!=(err=mem_table_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
//////if(0!=(err=mem_table_force_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
////if(0!=(err=mem_table_safe_del_record(mem_table,record_ptr)))DEBUG("mem_table_del_record err is %d\n",err);
	//  DEBUG("mem_rbtree_index_table's name is %s, addr is %0x .\n",mem_rbtree_index->heap_space->config.table_name,mem_rbtree_index->heap_space->config);



//��������
struct  mem_hash_entry_t index1;
index1.hash_lkey = 1;
index1.block_no =1;
index1.record_num = 1;
strcpy(index1.hash_ckey,"aa");

char ff[]="aa";
////��������
//mem_rbtree_entry_t index2;
//index2.rbtree_lkey = 2;
//index2.block_no =4;
//index2.record_num = 4;
//
////��������
//mem_rbtree_entry_t index3;
//index3.rbtree_lkey = 3;
//index3.block_no =3;
//index3.record_num = 3;
//
////��������
//mem_rbtree_entry_t index5;
//index5.rbtree_lkey = 5;
//index5.block_no =5;
//index5.record_num = 5;
//
////��������
//mem_rbtree_entry_t index6;
//index6.rbtree_lkey = 6;
//index6.block_no =6;
//index6.record_num = 6;
//

struct    record_t   *  out_record_ptr;
long    mem_block_no;
long    mem_table_no;
if(0!=(err=mem_hash_index_insert_long(mem_hash_index,2,2,2,integer_hash_fun, &out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_long err is %d\n",err);
if(0!=(err=mem_hash_index_insert_long(mem_hash_index,1,1,1,integer_hash_fun, &out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_long err is %d\n",err);
if(0!=(err=mem_hash_index_insert_long(mem_hash_index,1,1,1,integer_hash_fun, &out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_long err is %d\n",err);
if(0!=(err=mem_hash_index_insert_long(mem_hash_index,14,1,1,integer_hash_fun,&out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_long err is %d\n",err);
if(0!=(err=mem_hash_index_del_long(mem_hash_index,1,1,1,integer_hash_fun,&out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_del_long err is %d\n",err);
if(0!=(err=mem_hash_index_del_long(mem_hash_index,1,1,1,integer_hash_fun,&out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_del_long err is %d\n",err);
      
//if(0!=(err=mem_hash_index_insert_str(mem_hash_index,ff,2,2,str_hash_fun, &out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_str err is %d\n",err);
//if(0!=(err=mem_hash_index_insert_str(mem_hash_index,ff,2,2,str_hash_fun, &out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_insert_str err is %d\n",err);
//if(0!=(err=mem_hash_index_del_str(mem_hash_index,ff,2,2,str_hash_fun,&out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_del_str err is %d\n",err);
//if(0!=(err=mem_hash_index_del_str(mem_hash_index,ff,2,2,str_hash_fun,&out_record_ptr,&mem_block_no,&mem_table_no)))DEBUG("mem_hash_index_del_str err is %d\n",err);


if(0!=(err=mem_hash_index_close(mem_hash_index)))DEBUG("mem_hash_index_close err is %d\n",err);

if(0!=(err=mem_table_close(mem_table)))DEBUG("mem_table_close err is %d\n",err);
  dest_mem_table_no_manager();
  dest_mem_index_no_manager();
	dest_mem_block_no_manager();
	return 0;
}
