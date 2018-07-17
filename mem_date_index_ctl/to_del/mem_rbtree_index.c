#ifndef _RBTREE_C_
#define _RBTREE_C_
#include"mem_rbtree_index.h"

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

/*定义节点空指针*/
static mem_rbtree_entry_t *nil;

/*插入一个结点*/
inline int  mem_rbtree_insert(mem_rbtree_index_t *mem_rbtree_index, mem_rbtree_entry_t *root,mem_rbtree_entry_t* key)
{
	 if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
   if(NULL == key               )  return RBTREE_INDEX_ERR_NULL_KEY_PRT;
   RBTREE_LOCK(&(mem_rbtree_index->locker))
   
	        struct  record_t* record_ptr;
			  	long * block_no;
			 if( root==NULL  )
			 	{
			 	mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, block_no);
			 	root = (mem_rbtree_entry_t *)(record_ptr->data);
			 	//初始化nil结点
			 	mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, block_no);
			 	nil   = (mem_rbtree_entry_t *)(record_ptr->data);
			 	nil->color = BLACK;
			 	//设置结点的指向
			 	mem_rbtree_set_parent(root,nil   );	
			 	mem_rbtree_set_left  (root,nil   );	
			 	mem_rbtree_set_right (root,nil   );	
			 		 	//设置结点属性,key 和color
			 	root->block_no   = key->block_no;
			 	root->record_num = key->record_num;
			 	root->color      = key->color;
			 }else{
			 	mem_rbtree_entry_t* x = root;
			 	mem_rbtree_entry_t* p = nil;
			 while( x != nil ){	 	
			 		p = x;
			 		if     ( key->rbtree_lkey > x->rbtree_lkey  ) x =  mem_rbtree_right(mem_rbtree_index,x);
			 		else if(	key->rbtree_lkey < x->rbtree_lkey ) x =  mem_rbtree_left(mem_rbtree_index,x);
			 			else
			 				{
			 				RBTREE_UNLOCK(&(mem_rbtree_index->locker))
			 				return 0;
			 			}
			 	}
			 	mem_table_allocate_record(mem_rbtree_index->heap_space , &record_ptr, block_no);
			 	x = (mem_rbtree_entry_t *)record_ptr->data;
			 	
			 	mem_rbtree_set_parent(x,p   );	
			 	mem_rbtree_set_left  (x,nil   );	
			 	mem_rbtree_set_right (x,nil   );	
			 	x->rbtree_lkey = key->rbtree_lkey;
			 	x->color  = RED;
			 	if(key->rbtree_lkey < p->rbtree_lkey) mem_rbtree_set_left(p,x);
			 	else
			 		mem_rbtree_set_right(p,x);
			 		mem_rbtree_insert_fixup  (mem_rbtree_index,root,x);
			 	}
			 	RBTREE_UNLOCK(&(mem_rbtree_index->locker))
return 0;
}

/*查找结点帮助函数*/
inline mem_rbtree_entry_t * mem_rbtree_search_help(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key)
{
	  RBTREE_RLOCK(&(mem_rbtree_index->locker))
	  if(root!=nil){
	  if(	root->rbtree_lkey < key)
	  	mem_rbtree_search_help(mem_rbtree_index,mem_rbtree_right(mem_rbtree_index,root),key);
	  else if(root->rbtree_lkey>key)	
	  	 if(	root->rbtree_lkey < key)
	    mem_rbtree_search_help(mem_rbtree_index,mem_rbtree_left (mem_rbtree_index,root),key);
		else
			{
			RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
			return (root==nil) ? NULL : root;
			}
	}
	
	RBTREE_RUNLOCK(&(mem_rbtree_index->locker))
}/*查找实际要删除的结点*/


inline mem_rbtree_entry_t *mem_rbtree_real_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *x){
		mem_rbtree_entry_t *p=mem_rbtree_right(mem_rbtree_index,x);
		
		while( mem_rbtree_left(mem_rbtree_index,p)!=nil )
		{
			mem_rbtree_left(mem_rbtree_index,p);
			 
		}
		return p;
}
/*删除结点*/
inline int mem_rbtree_delete(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t* z)
{
	  if(NULL == mem_rbtree_index  )  return RBTREE_INDEX_ERR_NULL_INDEX_PRT;
	   if( z==nil  || z==NULL )return ;
	   	RBTREE_LOCK(&(mem_rbtree_index->locker))

	   mem_rbtree_entry_t* y;
	   mem_rbtree_entry_t* x;
	   if(
	   	mem_rbtree_left(mem_rbtree_index,z) ==nil || 
	    mem_rbtree_right(mem_rbtree_index,z)==nil ){
     y = z;
	   }else{
     	y = mem_rbtree_real_delete(mem_rbtree_index,root,z);
	 }
	 //x指向实际删除结点的子结点
	 if(!(mem_rbtree_left(mem_rbtree_index,z)==nil)) 
	 	   x = mem_rbtree_left(mem_rbtree_index,y);
	 	else 
	 		 x = mem_rbtree_right(mem_rbtree_index,y);
	 	
	 	mem_rbtree_set_self(mem_rbtree_parent(mem_rbtree_index,x) , mem_rbtree_parent(mem_rbtree_index,y)); //删除结点y
	 	if( (mem_rbtree_parent(mem_rbtree_index,y)==nil )){
	 		root = x;
	 	 }else{
	 	if (mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,y) ))	
	  	mem_rbtree_set_self(mem_rbtree_left(mem_rbtree_index, mem_rbtree_parent(mem_rbtree_index,y) ) , x);
	 	else
	 		mem_rbtree_set_self(mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,y) ) , x );		 
	 	}
	 		 if(y!=z){
	 	    z->rbtree_lkey = y->rbtree_lkey;
	 }

	 //如果删除的结点是黑色,违法了性质5,要进行删除调整
	 if(y->color==BLACK){
	 mem_rbtree_delete_fixup (mem_rbtree_index,root,x);
	 }
	
	struct record_t * record_ptr =(struct record_t *)((size_t)y - RECORD_HEAD_SIZE);
	int err;
	err = mem_table_del_record(mem_rbtree_index->heap_space , record_ptr);
	RBTREE_UNLOCK(&(mem_rbtree_index->locker))
	return err;
}


/*删除调整*/                                         
inline int mem_rbtree_delete_fixup (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *x)
{
	////一至到黑色，才结束
	 while(x!=(root) && x->color==BLACK){
	 	// x==x->parent->left
	 		if(x == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ))){  
	 		mem_rbtree_entry_t* w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));//w 为x的兄弟结点
	 			if(w->color ==RED){          //case 1 兄弟结点为红色
	 			w->color = BLACK;
	 			mem_rbtree_parent(mem_rbtree_index,x )->color = RED;
	 		  mem_rbtree_left_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
	 		  w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
	 		  }
	 		  if((w==nil ))break;
        if(mem_rbtree_left(mem_rbtree_index,x)->color ==BLACK && mem_rbtree_right(mem_rbtree_index,x)->color ==BLACK ){   //case2 兄弟结点的两个子结点都为黑
        w->color = RED;
        x = mem_rbtree_parent(mem_rbtree_index,x );
        }else if(mem_rbtree_right(mem_rbtree_index,w)->color ==BLACK){    //case3 w的左子树为红色,右子树为黑色
        w->color = RED;
        mem_rbtree_left(mem_rbtree_index,w)->color = BLACK;
        mem_rbtree_left_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,w ));
        w = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
        }
       w->color = mem_rbtree_parent(mem_rbtree_index,x )->color;         //case 4 w的右子树为红色
       mem_rbtree_parent(mem_rbtree_index,x )->color = BLACK;
       mem_rbtree_right (mem_rbtree_index,x )->color = BLACK;
	 	   mem_rbtree_left_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
       }else{  //对称 调整同上
       mem_rbtree_entry_t* w = mem_rbtree_left(	mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ) );
       if(w->color == RED){                 //case 1
       w->color = BLACK; 
       mem_rbtree_parent(mem_rbtree_index,x )->color = RED;
       mem_rbtree_right_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
       w = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
       }
       if((w==nil ))break;
       if(mem_rbtree_left(mem_rbtree_index,w)->color == BLACK && mem_rbtree_right(mem_rbtree_index,w)->color == BLACK ){  //case 2
       w->color = RED;
       x = mem_rbtree_parent(mem_rbtree_index,x );
       }else if(mem_rbtree_left(mem_rbtree_index,w)->color == BLACK){                       //case 3
       	w->color = RED;
       	mem_rbtree_right(mem_rbtree_index,w)->color = BLACK;
       	mem_rbtree_left_rotate(mem_rbtree_index,root, w);
       	
       	w = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ));
       	}
       	
       	 w->color = mem_rbtree_parent(mem_rbtree_index,x )->color;
       	 mem_rbtree_parent(mem_rbtree_index,x )->color = BLACK;
       	 mem_rbtree_left  (mem_rbtree_index,w )->color = BLACK;
       	 mem_rbtree_right_rotate(mem_rbtree_index,root, mem_rbtree_parent(mem_rbtree_index,x ));
	 	}
	 	x = root;
	 }
	 x->color = BLACK;
	
	
}


/*查找最小的结点*/
inline mem_rbtree_entry_t * mem_rbtree_minkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key)
{
RBTREE_LOCK(&(mem_rbtree_index->locker))
		  mem_rbtree_entry_t *x=root;
	    mem_rbtree_entry_t *p=nil;
	  while(x!=nil){
	  		p = x;
	  		x = mem_rbtree_left  (mem_rbtree_index,x );
	  }
	  RBTREE_UNLOCK(&(mem_rbtree_index->locker))

	  return p==nil ? NULL : p;
	
	
	
}
/*查找最大的结点*/
inline mem_rbtree_entry_t * mem_rbtree_maxkey(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,unsigned  long long key)
{
RBTREE_LOCK(&(mem_rbtree_index->locker))
		  mem_rbtree_entry_t *x=root;
	  mem_rbtree_entry_t *p=nil;
	  while(x!=nil){
	  		p = x;
	  			x = mem_rbtree_right  (mem_rbtree_index,x );
	  }
	  	  RBTREE_UNLOCK(&(mem_rbtree_index->locker))
	  return p==nil ? NULL : p;
	
	
	
}


/*插入调整*/
inline int mem_rbtree_insert_fixup  (mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root,mem_rbtree_entry_t *z)
{
	mem_rbtree_entry_t * y;
	//一至到父节点是红色，才结束
	while(mem_rbtree_parent(mem_rbtree_index,z )->color == RED){
		// z->parent = z->parent->parent->left
		if(mem_rbtree_parent(mem_rbtree_index,z ) == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z )))){
			// y = z->parent->right;
			y = mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z )) ; //获取叔父结点
				if(y->color==RED){             //case 1  如果叔父结点为红色,则把父节点和叔父结点着黑,祖父结点着红,z上移到祖父结点
					y->color  = BLACK;
					mem_rbtree_parent(mem_rbtree_index,z )->color = BLACK;
					mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z ))->color = RED; 	
					z = mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z ));
				}else{
				if(z==mem_rbtree_right(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))){   //case 2  如果叔父结点为黑色,z右结点,z上移为父亲结点,左旋转z结点,此时变为case3的情况
	        z = mem_rbtree_parent(mem_rbtree_index,z);
	        mem_rbtree_left_rotate	(mem_rbtree_index,root,z);
        }
          mem_rbtree_parent(mem_rbtree_index,z)->color                                       = BLACK;   //case 3 叔父结点为黑色,且z的左结点,z的父亲着着黑,z的祖父着红,然后旋转z的祖父结点
          mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color   = RED;
          mem_rbtree_right_rotate	(mem_rbtree_index,root,z);
        }
     // z = z->parent->parent->right
	 	}else{  //对称 调整同上
	 		
	 		   y = mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z)));
	 		   if(y->color==RED){
	 		   		 	y->color  = BLACK;
	 		   		 	mem_rbtree_parent(mem_rbtree_index,z)->color = BLACK;
	 		   		 	mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color = RED;
	 		   		 	z = mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z));
	 		   }else{
	 		   	if( z == mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))){
	 		   		  z = mem_rbtree_parent(mem_rbtree_index,z);
	 		   		  mem_rbtree_right_rotate	(mem_rbtree_index,root,z);
           }
              mem_rbtree_parent(mem_rbtree_index,z)->color = BLACK;
              mem_rbtree_parent(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,z))->color = RED;
              mem_rbtree_left_rotate	(mem_rbtree_index,root,z);
	 	   }
	 	}
	 }
	 root->color = BLACK;

}



//返回父节点指针                                                     
inline mem_rbtree_entry_t * mem_rbtree_parent(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x )
{
  //if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	
	long                    parent_block_no   = x->parent_block_no;			    //父节点数据所在的块号
  unsigned  long long     parent_record_num = x->parent_record_num; 			//父节点所在的行号
  struct record_t * record_ptr;
  get_record(mem_rbtree_index->heap_space,parent_block_no,parent_record_num,record_ptr);  
  mem_rbtree_entry_t *parent;
  parent = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return parent;
	
}
//返回左节点指针   
inline mem_rbtree_entry_t * mem_rbtree_left(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x)
{
  //if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	
	long                    left_block_no   = x->left_block_no;			    //父节点数据所在的块号
  unsigned  long long     left_record_num = x->left_record_num; 			//父节点所在的行号
  struct record_t * record_ptr;
   get_record(mem_rbtree_index->heap_space,left_block_no,left_record_num,record_ptr);  
  mem_rbtree_entry_t *left;
  left = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return left;	
}
//返回右节点指针 
inline mem_rbtree_entry_t * mem_rbtree_right(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *x)
{
	//if(NULL == x)return RBTREE_INDEX_ERR_LEFT_IS_NULL_PRT;
	
	long                    right_block_no    = x->right_block_no;			    //父节点数据所在的块号
  unsigned  long long     right_record_num  = x->right_record_num; 			//父节点所在的行号
  struct record_t * record_ptr;
   get_record(mem_rbtree_index->heap_space,right_block_no,right_record_num,record_ptr);  
   mem_rbtree_entry_t *right;
  right = (mem_rbtree_entry_t *)((char *)(record_ptr) + RECORD_HEAD_SIZE);
	return right;	
	
}
//设置节点指针                                                     
inline int mem_rbtree_compare_self(mem_rbtree_entry_t *x,mem_rbtree_entry_t *y )
{	
	return (x->parent_block_no    == y->block_no) && (x->parent_record_num  == y->record_num); 		 
}

//设置节点指针                                                     
inline void mem_rbtree_set_self(mem_rbtree_entry_t *x,mem_rbtree_entry_t *y )
{	
	 //x->parent_block_no    = y->block_no;			    //父节点数据所在的块号
  // x->parent_record_num  = y->record_num; 		  	//父节点所在的行号	
     x = y;
}

//设置父节点指针                                                     
inline void mem_rbtree_set_parent(mem_rbtree_entry_t *x,mem_rbtree_entry_t *parent )
{	
	 x->parent_block_no    = parent->block_no;			    //父节点数据所在的块号
   x->parent_record_num  = parent->record_num; 		  	//父节点所在的行号	
}
//设置左节点指针   
inline void mem_rbtree_set_left(mem_rbtree_entry_t *x,mem_rbtree_entry_t *left)
{
	 x->left_block_no    = left->block_no;			    //左节点数据所在的块号
   x->left_record_num  = left->record_num; 		  	//左节点所在的行号	
}
//设置右节点指针 
inline void mem_rbtree_set_right(mem_rbtree_entry_t *x,mem_rbtree_entry_t *right)
{
	 x->right_block_no    = right->block_no;			    //左节点数据所在的块号
   x->right_record_num  = right->record_num; 		  	//左节点所在的行号	
	
}


/*左旋*/         
//左旋转：结点x原来的右子树y旋转成为x的父母                                    
inline int mem_rbtree_left_rotate	(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root, mem_rbtree_entry_t *x)
{
		if(NULL == x               )return RBTREE_INDEX_ERR_ENTRY_IS_NULL_PRT;
    if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
    if(NULL == mem_rbtree_index)return CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR;
    
    if(mem_rbtree_right(mem_rbtree_index,x)!=NULL)
    {
    mem_rbtree_entry_t *y;
    mem_rbtree_set_self (y, mem_rbtree_right(mem_rbtree_index,x)     ); 
    mem_rbtree_set_right(x   , mem_rbtree_left (mem_rbtree_index,y)     ); 
    if( mem_rbtree_left (mem_rbtree_index,y)!= NULL)
    {
    	mem_rbtree_set_parent(mem_rbtree_left   (mem_rbtree_index,y),  x);
    }
     mem_rbtree_set_parent(y,mem_rbtree_parent(mem_rbtree_index,x )   );	
    	
    	
    if( mem_rbtree_parent(mem_rbtree_index,x )== NULL)
    	{
    		mem_rbtree_set_self (root, y ); 
    	}	
    	else
    		{
    		if(mem_rbtree_compare_self(x,
    			                         mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ))
    			                         ))
    			{
    			   	mem_rbtree_set_left( mem_rbtree_parent(mem_rbtree_index,x ),  y  );	
    			}
    			else
    				{
    					mem_rbtree_set_right(mem_rbtree_parent(mem_rbtree_index,x ),  y );
    				}
    			}
    	mem_rbtree_set_left  ( y,  x  );				
    	mem_rbtree_set_parent( x,  y  );		
    }
	
	
}
/*右旋*/
//右旋转：结点x原来的左子树y旋转成为x的父母                                             
inline int mem_rbtree_right_rotate(mem_rbtree_index_t *mem_rbtree_index,mem_rbtree_entry_t *root, mem_rbtree_entry_t *x)
{
		if(NULL == x               )return RBTREE_INDEX_ERR_ENTRY_IS_NULL_PRT;
    if(NULL == root            )return RBTREE_INDEX_ERR_ROOT_IS_NULL_PRT;
    if(NULL == mem_rbtree_index)return CLOSE_MEM_RBTREE_INDEX_ERR_NULL_PTR;
    	
    if(mem_rbtree_left(mem_rbtree_index,x)!=NULL)
    {	
       mem_rbtree_entry_t *y;
       y = mem_rbtree_left(mem_rbtree_index,x),mem_rbtree_right(mem_rbtree_index,y) ; 
       if( mem_rbtree_left (mem_rbtree_index,y)!= NULL)
       	{
       		 mem_rbtree_set_parent(mem_rbtree_right(mem_rbtree_index,y),     x);
        }
           mem_rbtree_set_parent(y,mem_rbtree_parent(mem_rbtree_index,x )   );	
       
       if(mem_rbtree_parent(mem_rbtree_index,x)!=NULL)
       {
       	  mem_rbtree_set_self (root, y ); 
       }
       else
       	{
       		if(mem_rbtree_compare_self(x,
    			                         mem_rbtree_left(mem_rbtree_index,mem_rbtree_parent(mem_rbtree_index,x ))
    			                         ))
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
	if(NULL == mem_index_config->field_order      )  return CREATE_RBTREE_INDEX_ERR_NO_FIELD_PTR;
  if(mem_index_config->field_num <= 0          )   return CREATE_RBTREE_INDEX_ERR_FIELD_NUM_LESS_ZERO;                          	
  int len = strlen(mem_index_config->index_name);
  
  allocate_index_no(&(mem_index_config->index_no));

		  //构造 array_space_config
		  struct mem_table_config_t * heap_space_config = (struct mem_table_config_t *)malloc(sizeof(MEM_TABLE_CONFIG_SIZE)); 
		  //array_space_config->mem_table_no             = allocat_mem_table_no();
      //array_space_config->owner_id                   = mem_table->owner_id;
      heap_space_config->fields_table               = (struct field_t *)malloc(sizeof(FIELD_SIZE));
      heap_space_config->fields_table->field_type   = FIELD_TYPE_HASH_ENTRY;
      heap_space_config->fields_table->field_order  = 0;
      heap_space_config->field_used_num             = 1;
      heap_space_config->mem_block_used             = 1;
      heap_space_config->field_used_num             = 1;
      heap_space_config->auto_extend                = 1; //允许自动扩展
      heap_space_config->mem_blocks_table           = (struct mem_block_t *)malloc(sizeof(MEM_BLOCK_HEAD_SIZE));
      heap_space_config->mem_blocks_table->next     = 0;
      strcpy(heap_space_config->table_name,mem_index_config->index_name);
      strcpy(heap_space_config->mem_blocks_table->file_name, mem_index_config->index_name);
      strcpy(heap_space_config->mem_blocks_table->file_name+len,"_heap");
		  heap_space_config->mem_blocks_table->file_name[len+5]='\0';                          	
                             	
     	int i=0;
	   struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	   off_t heap_space_size;

  //遍历所有块,累加数据块大小
	   for(;i<mem_table->config.mem_block_used;++i)
	   { 
	   	  //取array块大小
	   	  heap_space_size += mem_block_temp->block_size;   
	   		mem_block_temp = mem_block_temp->next;      //下一个块
      }
     
       //设置两个 heap_space 块大小,将配置数和数据数比较取最大
      heap_space_config->mem_blocks_table->block_size = (mem_index_config->heap_block_size > heap_space_size ) ? mem_index_config->heap_block_size : heap_space_size;      
      
      (*mem_rbtree_index) = (struct mem_rbtree_index_t  *)malloc(MEM_RBTREE_INDEX_SIZE);
      (*mem_rbtree_index) -> config.index_no         = mem_index_config->index_no;
      (*mem_rbtree_index) -> config.owner_table_no   = mem_index_config->owner_table_no;
      (*mem_rbtree_index) -> config.field_order      = mem_index_config->field_order;
      (*mem_rbtree_index) -> config.field_num        = mem_index_config->field_num;
      (*mem_rbtree_index) -> config.owner_id         = mem_index_config->owner_id;
      (*mem_rbtree_index) -> config.heap_block_size =  heap_space_config->mem_blocks_table->block_size;

      RBTREE_LOCK_INIT(&((*mem_rbtree_index)->locker))
      
      return mem_table_create(
                             &((*mem_rbtree_index)->heap_space),
                             heap_space_config
                             );
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
	  int err;
	  err  = mem_table_close((mem_rbtree_index)->heap_space);
	  del_index_no_addr(mem_rbtree_index->config.index_no);
	  if(0 != err)return err;
		if(mem_rbtree_index)free(mem_rbtree_index);
		return 0;	
}

#endif