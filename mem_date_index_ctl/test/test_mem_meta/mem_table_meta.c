#include "../../mem_table_mvcc_op.h"
#include "../../mem_index_no_manager.h"
#include "../../table_meta.h"


int create_block(mem_block_t **mb,char * file_name)
{
	DEBUG("in create_block\n");

	//������
	*mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	DEBUG("create_block %0x\n",*mb);

	//���ÿ�������
	mem_block_config( *mb  ,1024*1024*10 , file_name );
	//��ʼ����
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
//��ʼ�� redo_manager  
init_redo_log_manager();
//���� config_manager
//config_redo_data_log(char * path,off_t file_max_size)  

// ע���ڳ�ʼ�� ���������֮ǰ��Ҫ�ȳ�ʼ��ϵͳ���й�����
init_sys_transaction_manager();
//���� transaction_manager�� ����ֵ ��  �ع��ռ����ֵ
config_sys_transaction_manager(1,DEFAULT_FILE_MAX_SIZE);
 
//��չ�����
// extend_transaction_manager();

// ��ʼ��������־д���߳�
init_trans_redo_data_writer(&sys_trans_redo_data_writer,10);
// ���� writer �߳�д��־
start_trans_redo_data_writer();
}

void dest_trans_redo()
{
	 // �ر� writer �߳�д��־
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
* ���� mem_block ��������
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
	// ��ʼ���������
	init_trans_redo();
	
//   �����Ա�����������
//__________________________________________
// �������
mem_block_t *mb = NULL;
create_block(&mb,"./map_table.dat");
//���߼�������
mem_table_config_t * mem_config = NULL;
// ���Բ�������
struct record_t * record_ptr =NULL;
long block_no;




if(0!=(err=create_mem_table_config(&mem_config,mb,"first_table_name\0")))ERROR("create_mem_table_config err is %d\n",err);
//DEBUG("mem_config is %d\n",mem_config);

//���߼���
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
	
	//�رձ�
if(0!=(err=mem_table_close(mem_table)))ERROR("mem_table_close err is %d\n",err);
	printf("main  end  at %s\n",GetTime());
	return 0;
}
