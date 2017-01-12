#ifndef BASIC_OPS_MAC
#define BASIC_OPS_MAC

#include"../../mem_date_index_ctl/mem_transaction.h"

typedef struct fun_param
{
	void *a;
	void *b;
	void *c;
	void *d;
	void *e;
	void *f;
	int ret;
}fun_param;

typedef struct index_fun_param
{
	void *index;
	unsigned  long long key;
	void *value;
	void *result;
	void *a;
	void *b;
	void *c;
	void *d;
	void *e;
	void *f;
	int ret;
	long                      block_no;    //输出找到的块所在块号
  unsigned  long long       record_num;
}index_fun_param;


mem_rbtree_entry_t * index4;
mem_rbtree_search(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key,mem_rbtree_entry_t ** result);



inline int mem_hash_index_select_long(
                        /* in */struct mem_hash_index_t  * mem_hash_index ,
                        /* in */unsigned  long long        key,
                        /* in */int (*hash_fun)(unsigned  long long key,/*连续空间块*/struct  mem_block_t *,/*返回哈希表的行号*/unsigned  long long *),
                       /* out */long                     * block_no,    //输出找到的块所在块号
                       /* out */unsigned  long long      * record_num,  //输出找到的块所在行号
                       /* out */struct  record_t         ** record_ptr,  /* IF FOUND ,RETURN FOUNDED RECORD  输出找到的块所在记录的指针 */
                       /* out */struct  mem_hash_entry_t ** array_space_entry //输出对应 连续空间的 hash 项索引
                        );




index_param->ret = mem_rbtree_search(
									(mem_rbtree_index_t *)(index_param->index),
									((mem_rbtree_index_t *)(index_param->index))->root,
									index_param->key,
									&(index_param->result)
									);
									
long block_no   = index_param->result ->block_no;	//存数据所在表的块顺序号
struct  mem_block_t * mb; 
get_block_no_addr(block_no,&mb	);         
unsigned  long long     record_num = index_param->result ->record_num;//存数据所在的行号			
get_record_by_record_num(mem_table,mb,record_num,&(index_param->result));
			
									

index_param->ret = mem_hash_index_select_long(
									(mem_rbtree_index_t *)(index_param->index),
									index_param->key,
                  &(index_param->block_no),
                  &(index_param->record_num),
                  &(index_param->result),
                   index_param->a	);

//全表扫描
//fun 遍历函数
//param 函数参数
inline int full_table_scan(
														struct mem_table_t *mem_table,
														void (*fun)(struct record_t *,fun_param* param),
														fun_param* param
) 
{
int __i = 0;											 
struct record_t     * record_ptr;
struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	

	for(;__i<mem_table->config.mem_block_used;++__i)																
	{
			unsigned  long long * __high_level_temp = 0;

				for(;
				__mem_block_temp->space_start_addr + __mem_block_temp->high_level* mem_table->record_size < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__mem_block_temp->high_level) * (mem_table->record_size) );
						//处理每一行记录
						fun(record_ptr,param);
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
	return 0;
}

//带限制的全表扫描
//fun 遍历函数
//param 函数参数
inline int full_table_scan_limit(
														struct mem_table_t *mem_table,
														void (*fun)(struct record_t *,fun_param* param),
														fun_param* param,
														unsigned  long long n
) 
{
int __i = 0;											 
struct record_t     * record_ptr;
struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
unsigned  long long __n = 0;

	for(;__i<mem_table->config.mem_block_used;++__i)																
	{
			unsigned  long long * __high_level_temp = 0;

				for(;
				__mem_block_temp->space_start_addr + __mem_block_temp->high_level* mem_table->record_size < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
						// 找到可用的记录位置
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__mem_block_temp->high_level) * (mem_table->record_size) );
						//处理每一行记录
						fun(record_ptr,param);
						++__n;
						if(__n == n-1)return 0;
				}
			__mem_block_temp = __mem_block_temp->next;      //下一个块
	}
	return 0;
}

index unique scan
index range scan  //  > < <> >= <= between
//在组合索引上，只使用部分列进行查询，导致查询出多行
//对非唯一索引列上进行的任何查询
index full scan
index fast full scan

//1，排序 - - 合并连接（Sort Merge Join， SMJ）
//    2，嵌套循环（Nested Loops， NL）
//    3，哈希连接（Hash Join， HJ）
//    另外，笛卡儿乘积（Cartesian Product）




#endif 
