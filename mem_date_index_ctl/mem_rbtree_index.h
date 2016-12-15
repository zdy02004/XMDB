//rbtree.h
#ifndef _RBTREE_H_
#define _RBTREE_H_
#ifdef __cplusplus

extern "C" {

#endif
#include"mem_table_ctl.h"
#include"mem_index_no_manager.h"

#define CREATE_RBTREE_INDEX_ERR_TABLE_PTR               34001         
#define CREATE_RBTREE_INDEX_ERR_NULL_CONFIG             34002
#define CREATE_RBTREE_INDEX_ERR_NO_NAME         				34003
#define CREATE_RBTREE_INDEX_ERR_NAME_TOO_LONG           34004
#define CREATE_RBTREE_INDEX_ERR_NO_TABLE_NO             34005
#define CREATE_RBTREE_INDEX_ERR_NO_FIELD_PTR            34006
#define CREATE_RBTREE_INDEX_ERR_FIELD_NUM_LESS_ZERO     34007
#define OPEN_MEM_RBTREE_ERR_NULL_HASH_PTR               34008
#define CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR             34009
#define RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT               34010
#define RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT               34011
#define RBTREE_INDEX_ERR_ENTRY_IS_NULL_PRT              34012
#define RBTREE_INDEX_ERR_NULL_INDEX_PRT                 34013
#define RBTREE_INDEX_ERR_NULL_KEY_PRT                   34014
#define MEM_RBTREE_ERR_OUT_PTR_IS_NULL									34015
#define MEM_RBTREE_ERR_SEARCH_NOT_FOUND                 34016
#define MEM_RBTREE_DELETE_NULL													34017

//暂时用写锁锁来实现红黑树索引锁
#define RBTREE_LOCK_T             rwlock_t
#define RBTREE_LOCK(x)            rwlock_wlock(x); \
   DEBUG(" RBTREE_LOCK() \n");

#define RBTREE_UNLOCK(x)          rwlock_wunlock(x); \
   DEBUG("RBTREE_UNLOCK \n");

//#define RBTREE_TRYLOCK(x)         pthread_spin_trylock(x) 
#define RBTREE_RLOCK(x)            rwlock_rlock(x);
#define RBTREE_RUNLOCK(x)          rwlock_runlock(x);   
#define RBTREE_LOCK_INIT(x)       rwlock_init((x));


/*定义节点空指针*/
//static mem_rbtree_entry_t *nil;

//内存 rbtree 索引描述符_适用于范围快速索引
typedef struct  mem_rbtree_index_config_t
{
long                        index_no;                     //索引号
long                        owner_table_no;               //所属表号
int               *         field_order;                  //联合索引的顺序号
int                         field_num;                    //联合索引关联字段的的个数
char                        index_name[128];              //索引名
long                        owner_id;                     //该索引所属用户的ID
unsigned  long long         heap_block_size;             //连续空间块配置大小

} __attribute__ ((packed, aligned (64))) mem_rbtree_index_config_t;

#define MEM_RBTREE_CONFIG_SIZE  sizeof(mem_rbtree_index_config_t)

//内存rbtree索引描述符_适用于范围索引
typedef struct  mem_rbtree_index_t
{
struct mem_rbtree_index_config_t  config;                       //hash 配置
struct mem_table_t                *heap_space;                	 //堆空间
long                               root_block_num;               //root 块号
unsigned  long long                root_record_num;              //root 行号
mem_rbtree_entry_t                 *root;                        //根节点
RBTREE_LOCK_T                      locker;                       //锁
struct  mem_rbtree_entry_t				 * nil;                         //空节点
// redo_log  日志，暂未想好如何实现.
} __attribute__ ((packed, aligned (64))) mem_rbtree_index_t;


#define MEM_RBTREE_INDEX_SIZE  sizeof(struct  mem_rbtree_index_t)

#define get_rbtree_root(t,rb_root)                                  \
get_record(t->heap_space,root_block_num,root_record_num,rb_root);   \
rb_root = ( mem_rbtree_entry_t * ) (rb_root)                        



/*插入一个结点*/
inline int  mem_rbtree_insert(mem_rbtree_index_t *mem_rbtree_index, mem_rbtree_entry_t *T,mem_rbtree_entry_t* key);
/*查找结点*/
inline int mem_rbtree_search(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key,mem_rbtree_entry_t ** result);

inline mem_rbtree_entry_t * mem_rbtree_upper_bound_help(
																	mem_rbtree_index_t *mem_rbtree_index,
																	mem_rbtree_entry_t *root,
																	unsigned  long long key
																	);

//使用此函数查找 >= key 的第一个节点，此函数用于范围查找
inline int mem_rbtree_upper_bound(
																	mem_rbtree_index_t *mem_rbtree_index,
																	mem_rbtree_entry_t *root,
																	unsigned  long long _key,
																	mem_rbtree_entry_t ** result
																	);

inline mem_rbtree_entry_t * mem_rbtree_search_help(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key);
/*删除结点帮助函数*/
inline mem_rbtree_entry_t *mem_rbtree_real_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *x);

/*删除结点*/
inline int mem_rbtree_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t* z);
/*查找最小的结点*/
inline mem_rbtree_entry_t * mem_rbtree_minkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root);
/*查找最大的结点*/
inline mem_rbtree_entry_t * mem_rbtree_maxkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root);
/*打印红黑树*/
inline int rbPrint(mem_rbtree_index_t T);


/*插入调整*/
inline int mem_rbtree_insert_fixup                   (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *T,mem_rbtree_entry_t *z);
/*删除调整*/                                         
inline int mem_rbtree_delete_fixup                   (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *T,mem_rbtree_entry_t *x);
                                                     
inline mem_rbtree_entry_t * mem_rbtree_parent     (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x );
inline mem_rbtree_entry_t * mem_rbtree_left       (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x);
inline mem_rbtree_entry_t * mem_rbtree_right      (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x);

//设置父节点指针                                                     
inline void mem_rbtree_set_parent(mem_rbtree_entry_t *x,mem_rbtree_entry_t *parent );
//设置左节点指针   
inline void mem_rbtree_set_left(mem_rbtree_entry_t *x,mem_rbtree_entry_t *left);
//设置右节点指针 
inline void mem_rbtree_set_right(mem_rbtree_entry_t *x,mem_rbtree_entry_t *right);
//设置节点指针    
inline void mem_rbtree_set_self(mem_rbtree_entry_t *x,mem_rbtree_entry_t *y );

/*左旋*/                                             
inline int mem_rbtree_left_rotate								     (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *T, mem_rbtree_entry_t *x);
/*右旋*/                                             
inline int mem_rbtree_right_rotate							     (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *T, mem_rbtree_entry_t *x);
//inline int mem_rbtree_entry_t *mem_rbtree_real_delete(mem_rbtree_entry_t *T, mem_rbtree_entry_t *x);

//建红黑树索引
inline int mem_rbtree_create(
                             mem_rbtree_index_t         ** mem_rbtree_index,
                             struct mem_table_t         *  mem_table,
                             struct mem_rbtree_index_config_t  *  mem_index_config
                             );

//打开索引                             
inline int mem_rbtree_index_open  (mem_rbtree_index_t *  mem_hash_index);
//关索引
inline	int mem_rbtree_index_close(mem_rbtree_index_t *  mem_hash_index);	


////通过record的指针获得 mem_block_t 指针
//inline int get_record_by_record_num(struct mem_table_t *mem_table,struct  mem_block_t * mb, unsigned  long long   record_num,struct record_t ** record_ptr)
//{
//	if( NULL == mem_table )  return READ_RECORD_ERR_TABLE_IS_NULL;
//	if( NULL == record_ptr)  return READ_RECORD_ERR_RECORD_IS_NULL;
//	if( NULL == mb				)  return GET_BLOCK_ERR_BLOCK_IS_NULL;
//  if( record_num<0      )  return GET_BLOCK_ERR_RECORD_IS_IN_BLOCK;
//  	
//  //优化性能，从 O(n) 到 O(1)，record_ptr 通过位置	 record_num 和 MEM_BLOCK_HEAD_SIZE 获得 mem_block 头地址
//  *record_ptr = ((struct  record_t *) ( (char *)(mb->space_start_addr) +(record_num*(mem_table->record_size)) ));
//  DEBUG("*record_ptr is %0x \n",*record_ptr);	
//	
//	return 0;
//}

//_________________________________________________________________________________________________

/*插入一个结点*/
inline int  mem_rbtree_insert(mem_rbtree_index_t *mem_rbtree_index, mem_rbtree_entry_t *root,mem_rbtree_entry_t* key)
{
	 if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
   if(NULL == key               )  return RBTREE_INDEX_ERR_NULL_KEY_PRT;
   
   char buf[MEM_RBTREE_ENTRY_SIZE];
   int err;
   
   //DEBUG("Enter mem_rbtree_insert(),insert value is %ld ;\n",key->rbtree_lkey);

   RBTREE_LOCK(&(mem_rbtree_index->locker))
   
	     struct  record_t* record_ptr;
			 long  block_no;
			 if( root == NULL  )
			 {
			 	 DEBUG("Insert Root Node: \n");
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
        err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr,&block_no,buf);
        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		return err;
        	}
			 	
			 	// root 是 0号行
			 	root = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
			 	//初始化mem_rbtree_index->nil结点，nil 是 1号行
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	DEBUG("Insert NIl Node: \n");
				struct  record_t* record_ptr2;
			 	err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr2,&block_no,buf);
        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		return err;
        	}
			 	
			 	mem_rbtree_index->nil   = (mem_rbtree_entry_t *)((char *)(record_ptr2) + RECORD_HEAD_SIZE);
			 	mem_rbtree_index->nil->color = BLACK;
			 	// nil 的相关数据都指向自己
			 	mem_rbtree_index->nil->block_no   			 =  block_no;			  
        mem_rbtree_index->nil->record_num 			 =  record_ptr2->record_num; 
			 	mem_rbtree_index->nil->parent_block_no   =  block_no;			  
        mem_rbtree_index->nil->parent_record_num =  record_ptr2->record_num; 			
        mem_rbtree_index->nil->left_block_no     =  block_no;			    
        mem_rbtree_index->nil->left_record_num   =  record_ptr2->record_num;		
        mem_rbtree_index->nil->right_block_no    =  block_no;			    
        mem_rbtree_index->nil->right_record_num  =  record_ptr2->record_num;
        DEBUG("nil->block_no = %d,nil->record_num = %d \n",mem_rbtree_index->nil->block_no,mem_rbtree_index->nil->record_num);

			 	//设置结点的指向
			 	mem_rbtree_set_parent(root,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_left  (root,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_right (root,mem_rbtree_index->nil   );	
			 	
			 	//设置结点属性,key 和color
			  root->rbtree_lkey = key->rbtree_lkey;
			 	root->block_no    = key->block_no;
			 	root->record_num  = key->record_num;
			 	root->color       = key->color;
			 	mem_rbtree_index->root  = root;
			 }else{
			 	mem_rbtree_entry_t* x = root;
			 	mem_rbtree_entry_t* p = mem_rbtree_index->nil;
			 while( x != mem_rbtree_index->nil ){
			 DEBUG("x != mem_rbtree_index->nil,x->rbtree_lkey = %ld ;\n",x->rbtree_lkey);
	 	
			 		p = x;
			 		if     ( key->rbtree_lkey > x->rbtree_lkey  ) x =  mem_rbtree_right(mem_rbtree_index,x);
			 		else if(	key->rbtree_lkey < x->rbtree_lkey ) x =  mem_rbtree_left(mem_rbtree_index,x);
			 			else
			 				{
			 				RBTREE_UNLOCK(&(mem_rbtree_index->locker))
			 				DEBUG("mem_rbtree_insert(); end\n");
			 				return 0;
			 			}
			 	}
			 	//mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, &block_no);
			 	DEBUG("Insert Value Node ,Insert value is %ld ;\n",key->rbtree_lkey);
			 	err = mem_table_insert_record(mem_rbtree_index->heap_space ,&record_ptr,&block_no,buf);
        if(err)
        	{
        		ERROR("mem_rbtree_insert Err! err is %d\n",err);
        		return err;
        	}
			 
			 	//获得数据
			 	x = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
			 	
			 	mem_rbtree_set_parent(x,p   );	
			 	mem_rbtree_set_left  (x,mem_rbtree_index->nil   );	
			 	mem_rbtree_set_right (x,mem_rbtree_index->nil   );	
			 	//设置结点属性,key 和color 			 
			 	x->rbtree_lkey = key->rbtree_lkey;
			 	x->block_no    = key->block_no;
			 	x->record_num  = key->record_num;			 	 
			 	x->color  = RED;
			 	if(key->rbtree_lkey < p->rbtree_lkey) mem_rbtree_set_left(p,x);
			 	else{
			 		mem_rbtree_set_right(p,x);
			 	}
			 		mem_rbtree_insert_fixup  (mem_rbtree_index,root,x);
			 	}
			 	RBTREE_UNLOCK(&(mem_rbtree_index->locker))

  	 	  DEBUG("mem_rbtree_insert(); end\n");

return 0;
}

inline int mem_rbtree_search(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key,mem_rbtree_entry_t ** result)
{
	
	if(NULL == mem_rbtree_index)return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
	if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
	
	(*result) = mem_rbtree_search_help(mem_rbtree_index,root,key);
	if( NULL == (*result))return MEM_RBTREE_ERR_SEARCH_NOT_FOUND;
	else return 0;
	
}

/*查找结点帮助函数*/
//使用此函数时，在此函数外加锁
inline mem_rbtree_entry_t * mem_rbtree_search_help(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key)
{
	RBTREE_RLOCK(&(mem_rbtree_index->locker))
	mem_rbtree_entry_t * it = root;
	while(it != mem_rbtree_index->nil)
	{
		if(	it->rbtree_lkey < key)
			{
				DEBUG("it->rbtree_lkey < key,%ld < %ld \n",it->rbtree_lkey , key);
				it = mem_rbtree_right(mem_rbtree_index,it);
			}
		else if (	it->rbtree_lkey > key)
			{
				DEBUG("it->rbtree_lkey > key,%ld > %ld \n",it->rbtree_lkey , key);
			   it = mem_rbtree_left(mem_rbtree_index,it);
			}
		else
			{
				DEBUG("it->rbtree_lkey == key (%ld)\n",it->rbtree_lkey);
				RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
				return (it == mem_rbtree_index->nil) ? NULL : it;
			}
	}
  RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
	return NULL;
}

//使用此函数时，查找值小于 key 的的离根最近的节点
inline int mem_rbtree_upper_bound(
																	mem_rbtree_index_t *mem_rbtree_index,
																	mem_rbtree_entry_t *root,
																	unsigned  long long _key,
																	mem_rbtree_entry_t ** result
																	)
{
	
	if(NULL == mem_rbtree_index)return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
	if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
	
	(*result) = mem_rbtree_upper_bound_help(mem_rbtree_index,
																										root,
																										_key);
	if( NULL == (*result))return MEM_RBTREE_ERR_SEARCH_NOT_FOUND;
	else return 0;
	
}

/*查找结点帮助函数*/
//使用此函数时，查找值小于 key 的边界节点
inline mem_rbtree_entry_t * mem_rbtree_upper_bound_help(
																	mem_rbtree_index_t *mem_rbtree_index,
																	mem_rbtree_entry_t *root,
																	unsigned  long long key
																	)
{
	RBTREE_RLOCK(&(mem_rbtree_index->locker))
	mem_rbtree_entry_t * it = root;
	mem_rbtree_entry_t * parent;
	while(it != mem_rbtree_index->nil)
	{
		if(	it->rbtree_lkey < key) // 当前节点小于查找值，向右找,
			{
				DEBUG("it->rbtree_lkey < key,%ld < %ld \n",it->rbtree_lkey , key);
				parent = it;
				it = mem_rbtree_right(mem_rbtree_index,it);
				if( parent->rbtree_lkey < key && it->rbtree_lkey > key)
				{
					RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
					return it;
				}
				//极大值仍然小于key的话，返回不存在
				if (it == mem_rbtree_index->nil){
					RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
					return NULL;
					
				}
			}
		else if (	it->rbtree_lkey > key)// 当前节点小于查找值，向左找,
			{
				DEBUG("it->rbtree_lkey > key,%ld > %ld \n",it->rbtree_lkey , key);
				parent = it;
			  it = mem_rbtree_left(mem_rbtree_index,it);
			  if( parent->rbtree_lkey > key && it->rbtree_lkey < key)
			  	{
			  		RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
			  		return parent;
			  	}
			  //极小值的情况是有值的（最小值）
		   	if (it == mem_rbtree_index->nil){
					RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
					return parent;
					
				}
			}
			else {// 当前节点等于查找值返回,
				RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
				return it;
			}
			

	}
  RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
	return (mem_rbtree_entry_t *)NULL;
}


/*查找实际要删除的结点*/
//找到中序遍历的前继
inline mem_rbtree_entry_t *mem_rbtree_real_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *x){
		mem_rbtree_entry_t *p=mem_rbtree_right(mem_rbtree_index,x);
		
		while( mem_rbtree_left(mem_rbtree_index,p)!=mem_rbtree_index->nil )
		{
			mem_rbtree_left(mem_rbtree_index,p);
			 
		}
		return p;
}
/*删除结点*/
inline int mem_rbtree_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t* z)
{
	  if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
	  if( z==mem_rbtree_index->nil  || z==NULL )return MEM_RBTREE_DELETE_NULL;
	  	
	  DEBUG("Enter mem_rbtree_delete();\n");	
	  RBTREE_LOCK(&(mem_rbtree_index->locker))

	   mem_rbtree_entry_t* y;
	   mem_rbtree_entry_t* x;
	   if(
	   	mem_rbtree_left(mem_rbtree_index,z) ==mem_rbtree_index->nil || 
	    mem_rbtree_right(mem_rbtree_index,z)==mem_rbtree_index->nil ){
     y = z;
	   }else{
     	y = mem_rbtree_real_delete(mem_rbtree_index,root,z);
	 }
	 	 DEBUG(" Real Delete COLOR IS %d,find key is %ld;\n",y->color,y->rbtree_lkey);	

	 //x指向实际删除结点的子结点
	 if(!(mem_rbtree_left(mem_rbtree_index,z)==mem_rbtree_index->nil)) 
	 	{
	 		DEBUG("!(mem_rbtree_left(mem_rbtree_index,z)==mem_rbtree_index->nil);\n");	
	 	   x = mem_rbtree_left(mem_rbtree_index,y);
	 	 }
	 	else 
	 		{
	 		DEBUG(" x = mem_rbtree_right(mem_rbtree_index,y);\n");	
	 		 x = mem_rbtree_right(mem_rbtree_index,y);
	 	}
	 	mem_rbtree_set_parent(x , mem_rbtree_parent(mem_rbtree_index,y)); //删除结点y
	 	if( (mem_rbtree_parent(mem_rbtree_index,y)==mem_rbtree_index->nil )){
	 		DEBUG("mem_rbtree_parent(mem_rbtree_index,y)==mem_rbtree_index->nil;\n");	
	 		mem_rbtree_index->root = x;
	 	 }else{
	 	if ( y == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,y) ))	
	  {
	  	DEBUG("y->parent->left = x  ;\n");	
	  	mem_rbtree_set_left (mem_rbtree_parent(mem_rbtree_index,y)  , x);
	  }
	 	else
	 		{
	 		DEBUG("y->parent->right = x  ;\n");
	 		mem_rbtree_set_right(mem_rbtree_parent(mem_rbtree_index,y)  , x );		 
	 	  }
	 	}
	 		 if(y!=z){
	 		 	DEBUG("z->(rbtree_lkey,block_no,record_num) = (%ld,%ld,%ld);\n",z->rbtree_lkey,z->block_no,z->record_num);	
	 	    DEBUG("y->(rbtree_lkey,block_no,record_num) = (%ld,%ld,%ld);\n",y->rbtree_lkey,y->block_no,y->record_num);	
	 	    z->rbtree_lkey 	= y->rbtree_lkey;
	 	    z->block_no     = y->block_no;			   		 //right节点索引所在的块号
   			z->record_num  =  y->record_num; 		  		 //right节点索引所在的行号	

	 }

	 //如果删除的结点是黑色,违法了性质5,要进行删除调整
	 if(y->color==BLACK){
	 mem_rbtree_delete_fixup (mem_rbtree_index,mem_rbtree_index->root,x);
	 }
	
	struct record_t * record_ptr =(struct record_t *)((size_t)y - RECORD_HEAD_SIZE);
	int err;
	err = mem_table_del_record(mem_rbtree_index->heap_space , record_ptr);
	RBTREE_UNLOCK(&(mem_rbtree_index->locker))
	
  DEBUG("mem_rbtree_delete() end;\n");	
	return err;
}


/*删除调整*/                                         
inline int mem_rbtree_delete_fixup (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *x)
{
	DEBUG("ENTER mem_rbtree_delete_fixup() ;\n");	

	////一至到黑色，才结束
	 while(x!=(root) && x->color==BLACK){
	 	// x==x->parent->left
	 		if(x == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ))){  
	 		mem_rbtree_entry_t* w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));//w 为x的兄弟结点
	 			if(w->color ==RED){          //case 1 兄弟结点为红色
	 			DEBUG("case 1 left 兄弟结点为红色\n");
	 			w->color = BLACK;
	 			mem_rbtree_parent(mem_rbtree_index,x )->color = RED;
	 		  mem_rbtree_left_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
	 		  w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
	 		  }
	 		  if((w==mem_rbtree_index->nil ))break;
        if(mem_rbtree_left(mem_rbtree_index,x)->color ==BLACK && mem_rbtree_right(mem_rbtree_index,x)->color ==BLACK ){   //case2 兄弟结点的两个子结点都为黑
        DEBUG("case2 兄弟结点的两个子结点都为黑\n");
        w->color = RED;
        x = mem_rbtree_parent(mem_rbtree_index,x );
        }else if(mem_rbtree_right(mem_rbtree_index,w)->color ==BLACK){    //case3 w的左子树为红色,右子树为黑色
        DEBUG("case3 w的左子树为红色,右子树为黑色\n");
        w->color = RED;
        mem_rbtree_left(mem_rbtree_index,w)->color = BLACK;
        mem_rbtree_right_rotate(mem_rbtree_index,root, w );
        w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
        }
       DEBUG("case 4 w的右子树为红色\n");
       w->color = mem_rbtree_parent(mem_rbtree_index,x )->color;         //case 4 w的右子树为红色
       mem_rbtree_parent(mem_rbtree_index,x )->color = BLACK;
       mem_rbtree_right (mem_rbtree_index,x )->color = BLACK;
	 	   mem_rbtree_left_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
       }else{  //对称 调整同上
       	;
       mem_rbtree_entry_t* w = mem_rbtree_left(	mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ) );
       if(w->color == RED){                 //case 1
       DEBUG("case 1 right 兄弟结点为红色\n");
       w->color = BLACK; 
       mem_rbtree_parent(mem_rbtree_index,x )->color = RED;
       mem_rbtree_right_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
       w = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
       }
       if((w==mem_rbtree_index->nil ))break;
       if(mem_rbtree_left(mem_rbtree_index,w)->color == BLACK && mem_rbtree_right(mem_rbtree_index,w)->color == BLACK ){  //case 2
       DEBUG("case2 right 兄弟结点的两个子结点都为黑\n");
       w->color = RED;
       x = mem_rbtree_parent(mem_rbtree_index,x );
       }else if(mem_rbtree_left(mem_rbtree_index,w)->color == BLACK){                       //case 3
       	DEBUG("case3 right w的左子树为红色,右子树为黑色\n");
       	w->color = RED;
       	mem_rbtree_right(mem_rbtree_index,w)->color = BLACK;
       	mem_rbtree_left_rotate(mem_rbtree_index,root, w);
       	
       	w = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
       	}
       	 DEBUG("case 4 right w的右子树为红色\n");
       	 w->color = mem_rbtree_parent(mem_rbtree_index,x )->color;
       	 mem_rbtree_parent(mem_rbtree_index,x )->color = BLACK;
       	 mem_rbtree_left  (mem_rbtree_index,w )->color = BLACK;
       	 mem_rbtree_right_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
	 	}
	 	x = root;
	 }
	 x->color = BLACK;
	
	 DEBUG("mem_rbtree_delete() end;\n");	

}


/*查找最小的结点*/
inline mem_rbtree_entry_t * mem_rbtree_minkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root)
{
RBTREE_LOCK(&(mem_rbtree_index->locker))
		  mem_rbtree_entry_t *x=root;
	    mem_rbtree_entry_t *p=mem_rbtree_index->nil;
	  while(x!=mem_rbtree_index->nil){
	  		p = x;
	  		x = mem_rbtree_left  (mem_rbtree_index,x );
	  }
	  RBTREE_UNLOCK(&(mem_rbtree_index->locker))

	  return p==mem_rbtree_index->nil ? NULL : p;
	
	
	
}
/*查找最大的结点*/
inline mem_rbtree_entry_t * mem_rbtree_maxkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root)
{
RBTREE_LOCK(&(mem_rbtree_index->locker))
		  mem_rbtree_entry_t *x=root;
	  mem_rbtree_entry_t *p=mem_rbtree_index->nil;
	  while(x!=mem_rbtree_index->nil){
	  		p = x;
	  			x = mem_rbtree_right  (mem_rbtree_index,x );
	  }
	  	  RBTREE_UNLOCK(&(mem_rbtree_index->locker))
	  return p==mem_rbtree_index->nil ? NULL : p;
	
	
	
}


/*插入调整*/
inline int mem_rbtree_insert_fixup  (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *z)
{
	DEBUG("Enter mem_rbtree_insert_fixup();\n");

	mem_rbtree_entry_t * y;
	//一至到父节点是红色，才结束
	while(mem_rbtree_parent(mem_rbtree_index,z )->color == RED){
		// z->parent = z->parent->parent->left
		if(mem_rbtree_parent(mem_rbtree_index,z ) == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z )))){
			DEBUG("z->parent = z->parent->parent->left\n");
			// y = z->parent->right;
			y = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z ))) ; //获取叔父结点
				if(y->color==RED){             //case 1  如果叔父结点为红色,则把父节点和叔父结点着黑,祖父结点着红,z上移到祖父结点
			    DEBUG("case 1  如果叔父结点为红色,则把父节点和叔父结点着黑,祖父结点着红,z上移到祖父结点\n");		
					y->color  = BLACK;
					mem_rbtree_parent(mem_rbtree_index,z )->color = BLACK;
					mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z ))->color = RED; 	
					z = mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z ));
				}else{
				if(z==mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))){   //case 2  如果叔父结点为黑色,z右结点,z上移为父亲结点,左旋转z结点,此时变为case3的情况
	        DEBUG("case 2  如果叔父结点为黑色,z右结点,z上移为父亲结点,左旋转z结点,此时变为case3的情况\n");		
	        z = mem_rbtree_parent(mem_rbtree_index,z);
	        mem_rbtree_left_rotate	(mem_rbtree_index,root,z);
        }
          DEBUG("case 3 叔父结点为黑色,且z的左结点,z的父亲着着黑,z的祖父着红,然后右旋转z的祖父结点\n");		
          mem_rbtree_parent(mem_rbtree_index,z)->color                                       = BLACK;   //case 3 叔父结点为黑色,且z的左结点,z的父亲着着黑,z的祖父着红,然后旋转z的祖父结点
          mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color   = RED;
          mem_rbtree_right_rotate	(mem_rbtree_index,root,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z)));
        }
     // z = z->parent->parent->right
	 	}else{  //对称 调整同上
				DEBUG("z = z->parent->parent->right\n");
	 		   y = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z)));
	 		   if(y->color==RED){
	 		   	DEBUG("case 1 right 如果叔父结点为红色,则把父节点和叔父结点着黑,祖父结点着红,z上移到祖父结点\n");		
	 		   		 	y->color  = BLACK;
	 		   		 	mem_rbtree_parent(mem_rbtree_index,z)->color = BLACK;
	 		   		 	mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color = RED;
	 		   		 	z = mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z));
	 		   }else{
	 		   	if( z == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))){
	 		   		 	 DEBUG("case 2  right 如果叔父结点为黑色,z是右结点,z上移为父亲结点,左旋转z结点,此时变为case3的情况\n");		
	 		   		  z = mem_rbtree_parent(mem_rbtree_index,z);
	 		   		  mem_rbtree_right_rotate	(mem_rbtree_index,root,z);
           }
              DEBUG("case 3 right 叔父结点为黑色,且z是右结点,z的父亲着着黑,z的祖父着红,然后左旋转z的祖父结点\n");		
              mem_rbtree_parent(mem_rbtree_index,z)->color = BLACK;
              mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color = RED;
              //mem_rbtree_left_rotate	(mem_rbtree_index,root,z);
              mem_rbtree_left_rotate	(mem_rbtree_index,root,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z)));

	 	   }
	 	}
	 }
	 root->color = BLACK;
	DEBUG("mem_rbtree_insert_fixup() end\n");

}



//返回父节点指针                                                     
inline mem_rbtree_entry_t * mem_rbtree_parent(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x )
{
  //if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	DEBUG("mem_rbtree_parent(),block_no,record_num=( %ld,%ld,%ld );\n",x->rbtree_lkey,x->parent_block_no,x->parent_record_num);										

	long                    parent_block_no   = x->parent_block_no;			    //父节点数据所在的块号
  unsigned  long long     parent_record_num = x->parent_record_num; 			//父节点所在的行号
  
  struct record_t * record_ptr;
  get_record(mem_rbtree_index->heap_space,parent_block_no,parent_record_num,&record_ptr);
  
  //record_ptr = get_record(mem_rbtree_index->heap_space,parent_block_no,parent_record_num);

  mem_rbtree_entry_t *parent;
  parent = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return parent;
	
}
//返回左节点指针   
inline mem_rbtree_entry_t * mem_rbtree_left(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x)
{
  //if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	DEBUG("mem_rbtree_left(),block_no,record_num=( %ld,%ld,%ld );\n",x->rbtree_lkey,x->left_block_no,x->left_record_num);										

	long                    left_block_no   = x->left_block_no;			    //父节点索引所在的块号
  unsigned  long long     left_record_num = x->left_record_num; 			//父节点所在的行号
  struct record_t * record_ptr;
   get_record(mem_rbtree_index->heap_space,left_block_no,left_record_num,&record_ptr);  
  mem_rbtree_entry_t *left;
  left = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return left;	
}
//返回右节点指针 
inline mem_rbtree_entry_t * mem_rbtree_right(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x)
{
	//if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	DEBUG("mem_rbtree_right(),block_no,record_num=( %ld,%ld,%ld );\n",x->rbtree_lkey,x->right_block_no,x->right_record_num);										

	long                    right_block_no    = x->right_block_no;			    //父节点索引所在的块号
  unsigned  long long     right_record_num  = x->right_record_num; 			//父节点所在的行号
  struct record_t * record_ptr;
   get_record(mem_rbtree_index->heap_space,right_block_no,right_record_num,&record_ptr);  
   mem_rbtree_entry_t *right;
  right = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return right;	
	
}
//设置节点指针                                                     
inline int mem_rbtree_compare_self(mem_rbtree_entry_t *x,mem_rbtree_entry_t *y )
{	
  //return (x->parent_block_no    == y->block_no) && (x->parent_record_num  == y->record_num); 	
	return x==y;	 
}


//DEBUG("block_no is %d \n",_block_no);																										\
// 根据 rbtree数据指针获得块号和行号
#define get_rbtree_record_num_block_no(data,_block_no,_record_num)				do{				\
struct record_t * record_ptr = (struct record_t *)((char *)(data) - RECORD_HEAD_SIZE ) ;	\
(_record_num) = record_ptr->record_num;																										\
struct  mem_block_t * mem_block = ((struct  mem_block_t *) ( (char *)record_ptr - (record_num*(RECORD_HEAD_SIZE + FIELD_RBTREE_ENTRY_SIZE)) - MEM_BLOCK_HEAD_SIZE ))->block_malloc_addr; \
(_block_no) = mem_block->block_no; 																											\
}while(0);																												

//设置节点指针                                                     
inline void mem_rbtree_set_self(mem_rbtree_entry_t *x,mem_rbtree_entry_t *y )
{	
  //   x = y;
	DEBUG("mem_rbtree_set_self();\n");										
	 x->parent_block_no    = 	y->block_no;			    	//y节点索引所在的块号
   x->parent_record_num  =  y->record_num; 		  		//y节点索引所在的行号	
   x->rbtree_lkey        =  y->rbtree_lkey;					//y节点key 
}

//设置父节点指针                                                     
inline void mem_rbtree_set_parent(mem_rbtree_entry_t *x,mem_rbtree_entry_t *parent )
{	
	long                    block_no   ;			    //父节点索引所在的块号
  unsigned  long long     record_num ; 	    		//父节点索引所在的行号
	get_rbtree_record_num_block_no(parent,block_no,record_num);
	DEBUG("mem_rbtree_set_parent,(parent's (block_no,record_num) =( %ld,%ld );\n",block_no,record_num);										

	 x->parent_block_no    = block_no;			    	//父节点索引所在的块号
   x->parent_record_num  = record_num; 		  		//父节点索引所在的行号	
   //x->rbtree_lkey        = parent->rbtree_lkey;

}
//设置左节点指针   
inline void mem_rbtree_set_left(mem_rbtree_entry_t *x,mem_rbtree_entry_t *left)
{
 long                    block_no   ;			    //left节点索引所在的块号
 unsigned  long long     record_num ; 	    		//left节点索引所在的行号
 get_rbtree_record_num_block_no(left,block_no,record_num);
 DEBUG("mem_rbtree_set_left,(left's (block_no,record_num) =( %ld,%ld );\n",block_no,record_num);										
	 
	 x->left_block_no    = block_no;			    		//left节点索引所在的块号
   x->left_record_num  = record_num; 		  			//left节点索引所在的行号	
   //x->rbtree_lkey      = left->rbtree_lkey;
}
//设置右节点指针 
inline void mem_rbtree_set_right(mem_rbtree_entry_t *x,mem_rbtree_entry_t *right)
{
  	long                    block_no   ;			    //right节点索引所在的块号
  	unsigned  long long     record_num ; 	    		//right节点索引所在的行号
		get_rbtree_record_num_block_no(right,block_no,record_num);
		DEBUG("mem_rbtree_set_right,(right's (block_no,record_num) =( %ld,%ld );\n",block_no,record_num);										
	 
	 x->right_block_no    = block_no;			   		 //right节点索引所在的块号
   x->right_record_num  = record_num; 		  	 //right节点索引所在的行号	
   //x->rbtree_lkey      =  right->rbtree_lkey;
	
}


/*左旋*/         
//左旋转：结点x原来的右子树y旋转成为x的父母                                    
inline int mem_rbtree_left_rotate	(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root, mem_rbtree_entry_t *x)
{
		if(NULL == x               )return RBTREE_INDEX_ERR_ENTRY_IS_NULL_PRT;
    if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
    if(NULL == mem_rbtree_index)return CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR;
    DEBUG("enter mem_rbtree_left_rotate() \n");										

    if(mem_rbtree_right(mem_rbtree_index,x)!= mem_rbtree_index->nil )
    {
    DEBUG("mem_rbtree_right(mem_rbtree_index,x)!=NULL \n");
    mem_rbtree_entry_t *y =  mem_rbtree_right(mem_rbtree_index,x);
    mem_rbtree_set_right(x   , mem_rbtree_left (mem_rbtree_index,y)     );
    if( mem_rbtree_left (mem_rbtree_index,y)!= mem_rbtree_index->nil )
    {
    	DEBUG(" mem_rbtree_left (mem_rbtree_index,y)!= NULL \n");
    	mem_rbtree_set_parent(mem_rbtree_left   (mem_rbtree_index,y),  x);
    }
     mem_rbtree_set_parent(y,mem_rbtree_parent(mem_rbtree_index,x )   );	
    	
    	
    if( mem_rbtree_parent(mem_rbtree_index,x )==  mem_rbtree_index->nil )
    	{
    	 DEBUG(" mem_rbtree_parent(mem_rbtree_index,x )== NULL \n");
    		//mem_rbtree_set_self (root, y ); 
    		mem_rbtree_index->root = y;
    	}	
    	else
    		{
    		if( x == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ))
    			                         )
    			{
    				 DEBUG(" if1 \n");
    			   	mem_rbtree_set_left( mem_rbtree_parent(mem_rbtree_index,x ),  y  );	
    			}
    			else
    				{
    					DEBUG(" if2 \n");
    					mem_rbtree_set_right(mem_rbtree_parent(mem_rbtree_index,x ),  y );
    				}
    			}
    	mem_rbtree_set_left  ( y,  x  );				
    	mem_rbtree_set_parent( x,  y  );		
    }
	
	    DEBUG("mem_rbtree_left_rotate() end\n");										

}
/*右旋*/
//右旋转：结点x原来的左子树y旋转成为x的父母                                             
inline int mem_rbtree_right_rotate(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root, mem_rbtree_entry_t *x)
{
		if(NULL == x               )return RBTREE_INDEX_ERR_ENTRY_IS_NULL_PRT;
    if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
    if(NULL == mem_rbtree_index)return CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR;
    DEBUG("enter mem_rbtree_right_rotate(),(x->rbtree_lkey,x->block_no,x->record_num)=(%ld,%ld,%ld) \n",x->rbtree_lkey,x->block_no,x->record_num);										
	
    if(mem_rbtree_left(mem_rbtree_index,x)!= mem_rbtree_index->nil)
    {	
       mem_rbtree_entry_t *y = mem_rbtree_left(mem_rbtree_index,x);
       mem_rbtree_set_left(x   , mem_rbtree_right (mem_rbtree_index,y)     );
       if( mem_rbtree_left (mem_rbtree_index,y)!= mem_rbtree_index->nil )
       	{
       		 mem_rbtree_set_parent(mem_rbtree_right(mem_rbtree_index,y),     x);
        }
           mem_rbtree_set_parent(y,mem_rbtree_parent(mem_rbtree_index,x )   );	
       
       if(mem_rbtree_parent(mem_rbtree_index,x)== mem_rbtree_index->nil )
       {
       	  //mem_rbtree_set_self (root, y ); 
       	  mem_rbtree_index->root = y;
       }
       else
       	{
       		if( x== mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x )))
    			{
    				 	mem_rbtree_set_left( mem_rbtree_parent(mem_rbtree_index,x ),  y  );	
    			}
    			else
    				{
    					mem_rbtree_set_right( mem_rbtree_parent(mem_rbtree_index,x ),  y  );	
    				}
    		}
    	mem_rbtree_set_right  ( y,  x  );				
    	mem_rbtree_set_parent ( x,  y  );	

	}
		  DEBUG("mem_rbtree_right_rotate() end\n");										

}
//inline int mem_rbtree_entry_t *mem_rbtree_real_delete(mem_rbtree_entry_t *T, mem_rbtree_entry_t *x);

//建HASH索引
inline int mem_rbtree_create(
														 mem_rbtree_index_t         **  mem_rbtree_index,	
                             struct mem_table_t         *  mem_table,// 原表
                             struct mem_rbtree_index_config_t  *  mem_index_config
                             )
 {
  if(NULL == mem_table                          )  return CREATE_RBTREE_INDEX_ERR_TABLE_PTR;
	if(NULL == mem_index_config                   )  return CREATE_RBTREE_INDEX_ERR_NULL_CONFIG;
	if(NULL == mem_index_config->index_name       )  return CREATE_RBTREE_INDEX_ERR_NO_NAME;
	if(strlen (mem_index_config->index_name)>=120 )  return CREATE_RBTREE_INDEX_ERR_NAME_TOO_LONG;
  if(mem_index_config->owner_table_no<=0        )  return CREATE_RBTREE_INDEX_ERR_NO_TABLE_NO;
	//if(NULL == mem_index_config->field_order      )  return CREATE_RBTREE_INDEX_ERR_NO_FIELD_PTR;   //暂时不考虑 字段顺序
  //if(mem_index_config->field_num <= 0          )   return CREATE_RBTREE_INDEX_ERR_FIELD_NUM_LESS_ZERO; //暂时不考虑 联合索引                         	
  int len = strlen(mem_index_config->index_name);
  DEBUG("Enter mem_rbtree_create() \n");
  	
  		//1.构造 heap_space 的 block
     int i=0;
	   struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	   off_t heap_space_size = 0;

     //遍历原表所有块,累加原表哌数据块大小
	   for(;i<mem_table->config.mem_block_used;++i)
	   { 
	   	  //取array块大小
	   	  heap_space_size += mem_block_temp->block_size;   
	   		mem_block_temp = mem_block_temp->next;      //下一个块
      }
        //生成块描述符
       mem_block_t *mb = (mem_block_t *) malloc(MEM_BLOCK_HEAD_SIZE);
	     DEBUG("create mem_rbtree block %0x\n",*mb);
	     
	     //配置块描述符 //设置两个 heap_space 块大小,将配置数和数据数比较取最大
       off_t _block_size = (mem_index_config->heap_block_size > heap_space_size ) ? mem_index_config->heap_block_size : heap_space_size;      
			 DEBUG("_block_size is %d\n",_block_size);
			 
			 char tem_buf[256]={0};
       strcpy(tem_buf,mem_index_config->index_name);
       strcat(tem_buf,"_heap.dat\0");
       
			 mem_block_config( mb  ,_block_size , tem_buf );
			 
			 //2. 构造 fields_table
			 struct field_t *_fields_table   = (struct field_t *) malloc(FIELD_SIZE);
		   _fields_table[0].field_type     = FIELD_TYPE_RBTREE_ENTRY;

			 // 3.构造 mem_table_config_t
		  struct mem_table_config_t * heap_space_config = (struct mem_table_config_t *)malloc(MEM_TABLE_CONFIG_SIZE); 
		  //array_space_config->mem_table_no             = allocat_mem_table_no();
      //array_space_config->owner_id                   = mem_table->owner_id;
      heap_space_config->fields_table               = _fields_table;
      heap_space_config->field_used_num             = 1;
      heap_space_config->mem_block_used             = 1;
      heap_space_config->auto_extend                = 1; //允许自动扩展
      heap_space_config->mem_blocks_table           = mb;
      heap_space_config->mem_blocks_table->next     = 0;
      strcpy(heap_space_config->table_name,mem_index_config->index_name);
      strcat(heap_space_config->table_name,"_heap\0");
      DEBUG(" heap_space_config->table_name is %s \n",heap_space_config->table_name);

		  heap_space_config->extend_block_size   = _block_size; //自动扩展大小

			//4.构造 mem_table_t
			struct mem_table_t      *heap_space_temp ;  		
			int err=0;
      err = mem_table_create(
                             &heap_space_temp,
                             heap_space_config
                             );
      DEBUG(" heap_space_temp is %0x \n",heap_space_temp);

                    
       //5 设置  mem_rbtree_index              
      (*mem_rbtree_index) = (mem_rbtree_index_t  *)malloc(MEM_RBTREE_INDEX_SIZE);
      //allocate_index_no(&(mem_index_config->index_no));
      //(*mem_rbtree_index) -> config.index_no         = mem_index_config->index_no;
      allocate_index_no(&((*mem_rbtree_index) -> config.index_no ));
      set_index_no_addr((*mem_rbtree_index) -> config.index_no,(void *)mem_rbtree_index);
      (*mem_rbtree_index) -> config.owner_table_no   = mem_index_config->owner_table_no;
      (*mem_rbtree_index) -> config.field_order      = mem_index_config->field_order;
      (*mem_rbtree_index) -> config.field_num        = mem_index_config->field_num;
      (*mem_rbtree_index) -> config.owner_id         = mem_index_config->owner_id;
      (*mem_rbtree_index) -> config.heap_block_size =  heap_space_config->mem_blocks_table->block_size;
      strcpy((*mem_rbtree_index) -> config.index_name,mem_index_config->index_name);
      //设置堆内存
       (*mem_rbtree_index)->heap_space = heap_space_temp;
       RBTREE_LOCK_INIT(&((*mem_rbtree_index)->locker))
       (*mem_rbtree_index)->root      = NULL;                                       
    //  DEBUG(" mem_rbtree_create() ,mem_rbtree_index is %0x \n",(*mem_rbtree_index));
   //   DEBUG(" mem_rbtree_index->heap_space.config.table_name is %s,addr is %0x \n",(*mem_rbtree_index)->heap_space->config.table_name,(*mem_rbtree_index)->heap_space);

      return err;
}                 	
                             	
                   

//打开索引                             
inline int mem_rbtree_index_open  (mem_rbtree_index_t *  mem_rbtree_index)
{
	
 if(NULL == mem_rbtree_index    )  return OPEN_MEM_RBTREE_ERR_NULL_HASH_PTR;
  
  int err;
	err = mem_table_open(mem_rbtree_index->heap_space);
	return err;
	
	
}
//关索引
inline	int mem_rbtree_index_close(mem_rbtree_index_t *  mem_rbtree_index)
{
	
		if(NULL == mem_rbtree_index    )  return CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR;
	  DEBUG("Begin to close a mem_index：%s, addr is %0x .\n",(mem_rbtree_index)->config.index_name,(mem_rbtree_index)->config);
    RBTREE_LOCK(&(mem_rbtree_index->locker))
	  int err = 0;
	 //struct mem_table_t *heap_space_temp = mem_rbtree_index->heap_space;
	 //DEBUG("heap_space_temp's name is %s, addr is %0x .\n",heap_space_temp->config.table_name,heap_space_temp);

	  err  = mem_table_close( (mem_rbtree_index)->heap_space);
	  del_index_no_addr(mem_rbtree_index->config.index_no);
	  
    if(mem_rbtree_index)free(mem_rbtree_index);
		RBTREE_UNLOCK(&(mem_rbtree_index->locker))
		return err;	
}

#ifdef __cplusplus

}

#endif

#endif