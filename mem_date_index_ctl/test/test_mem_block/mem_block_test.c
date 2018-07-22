#include "../../mem_block_t.h"

/*
* ���� mem_block ��������
*
*
*
*/
int main(int arcv,char * arc[])
{
	
		init_mem_block_no_manager();

//������
mem_block_t *mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);


//���ÿ�������
mem_block_config( mb ,1024 , "./map_file.dat" );
//��ʼ����
INIT_MEM_BLOCK(mb)
DEBUG("fd = %d\n",mb->fd);
//��Ӳ���ϵͳ���������ڴ�
mem_block_get_mem_from_os(mb);
// ͨ��ʹ�� mmap ϵͳ���ý����ݼ��ص��ڴ��
int err;
if(0!=(err=mem_block_mmap(mb)))
{
	 DEBUG("mem_block_mmap err is %d\n",err); 
	
}
char out[]="xyzgg\0";


memcpy(mb->space_start_addr,out,6);  

DEBUG("mb->space_start_addr = %s\n", mb->space_start_addr	);


//ͨ��ʹ�� munmap ϵͳ���ý������ͻظ��ļ�
if(0!=(err= mem_block_munmap(mb)))printf("%d\n",err);
	   	 DEBUG("mem_block_munmap end\n");  

// ͨ��ʹ�� munmap ϵͳ���ý������ͻظ��ļ�
mem_block_put_mem_to_os(mb);
//if(0!=(err= mem_block_put_mem_to_os(mb)))printf("%d\n",err);
/// ͨ��ʹ�� mem_block_msync ϵͳ���ý������ͻظ��ļ�
//mem_block_msync(mb);

free(mb);
dest_mem_block_no_manager();	
	return 0;
}
