#include "../../mem_block_t.h"

/*
* 测试 mem_block 基本功能
*
*
*
*/
int main(int arcv,char * arc[])
{
	
		init_mem_block_no_manager();

//创建块
mem_block_t *mb =(mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);


//配置块描述符
mem_block_config( mb ,1024 , "./map_file.dat" );
//初始化块
INIT_MEM_BLOCK(mb)
DEBUG("fd = %d\n",mb->fd);
//块从操作系统创建共享内存
mem_block_get_mem_from_os(mb);
// 通过使用 mmap 系统调用将数据加载到内存块
int err;
if(0!=(err=mem_block_mmap(mb)))
{
	 DEBUG("mem_block_mmap err is %d\n",err); 
	
}
char out[]="xyzgg\0";


memcpy(mb->space_start_addr,out,6);  

DEBUG("mb->space_start_addr = %s\n", mb->space_start_addr	);


//通过使用 munmap 系统调用将数据送回给文件
if(0!=(err= mem_block_munmap(mb)))printf("%d\n",err);
	   	 DEBUG("mem_block_munmap end\n");  

// 通过使用 munmap 系统调用将数据送回给文件
mem_block_put_mem_to_os(mb);
//if(0!=(err= mem_block_put_mem_to_os(mb)))printf("%d\n",err);
/// 通过使用 mem_block_msync 系统调用将数据送回给文件
//mem_block_msync(mb);

free(mb);
dest_mem_block_no_manager();	
	return 0;
}
