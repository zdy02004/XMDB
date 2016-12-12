#ifndef _RBTREE_ITERATOR_H_
#define _RBTREE_ITERATOR_H_

#include"mem_rbtree_index.h"

#define ITERATOR_ERR_NOT_INIT  360001

// mem_rbtree_index 中序遍历迭代器
struct rb_tree_mid_iterator_t
{
mem_rbtree_entry_t                 *it;	         //当前结点
mem_rbtree_entry_t                 *root;        //根结点
mem_rbtree_entry_t                 *nil;         //空节点
mem_rbtree_index_t                 *index;
int                                top;          // 堆栈头结点
mem_rbtree_entry_t                 *__stack[64]; // 目前支持万亿级别
short                              staus;        //状态
mem_rbtree_entry_t *               maxkey;
};


inline void rb_tree_mid_iterator_init(struct rb_tree_mid_iterator_t * iter, struct  mem_rbtree_index_t  *rb_tree)
{
	iter->index  = rb_tree;
	iter->root   = rb_tree->root;
	iter->nil    = rb_tree->nil;
	iter->it     = iter->root;
	iter->top    = 0;
	iter->staus  = 1;
	iter->maxkey = mem_rbtree_maxkey(rb_tree,
	rb_tree->root);
}

inline mem_rbtree_entry_t * rb_tree_mid_iterator_next1(struct rb_tree_mid_iterator_t * iter)
{
	//结束条件
	//if (iter->top==0 && iter->it !=iter->root) return iter->nil;
	if(iter->it == NULL) return (mem_rbtree_entry_t *)NULL;
	if(iter->it == iter->maxkey)
		{
		iter->it = (mem_rbtree_entry_t *)NULL;
		return iter->maxkey;
	}
		
	mem_rbtree_entry_t * nil = iter->nil;
	// 状态1 
	while (iter->it!=nil) 
	{ 
	iter->__stack[(iter->top)++]=iter->it; 
	iter->it = mem_rbtree_left(iter->index,iter->it);
	} 
	iter->it=iter->__stack[--(iter->top)]; 
  iter->staus = 2;//调到状态 2
	return iter->it;
}


inline mem_rbtree_entry_t * rb_tree_mid_iterator_next2(struct rb_tree_mid_iterator_t * iter)
{
	//结束条件
//	if (iter->top==0 && iter->it !=iter->root) return iter->nil;
	if(iter->it == NULL) return (mem_rbtree_entry_t *)NULL;
	if(iter->it == iter->maxkey)
		{
		iter->it = (mem_rbtree_entry_t *)NULL;
		return iter->maxkey;
	  }		
	mem_rbtree_entry_t * nil = iter->nil;
	// 状态2
	iter->it = mem_rbtree_right(iter->index,iter->it);
	return rb_tree_mid_iterator_next1(iter);
}

inline mem_rbtree_entry_t * rb_tree_mid_iterator_next(struct rb_tree_mid_iterator_t * iter)
{
	if(iter->staus ==1 )return rb_tree_mid_iterator_next1(iter);
	if(iter->staus ==2 )return rb_tree_mid_iterator_next2(iter);
	return (mem_rbtree_entry_t *)ITERATOR_ERR_NOT_INIT;
}


//---------------------------------------------------------------------


// mem_rbtree_index 中序遍历迭代器
struct rb_tree_after_iterator_t
{
mem_rbtree_entry_t                 *it;	         //当前结点
mem_rbtree_entry_t                 *root;        //根结点
mem_rbtree_entry_t                 *nil;         //空节点
mem_rbtree_index_t                 *index;
int                                top;          // 堆栈头结点
mem_rbtree_entry_t                 *__stack[64]; // 目前支持万亿级别
short                              staus;        //状态
mem_rbtree_entry_t *               minkey;
};


inline void rb_tree_after_iterator_init(struct rb_tree_after_iterator_t * iter, struct  mem_rbtree_index_t  *rb_tree)
{
	iter->index  = rb_tree;
	iter->root   = rb_tree->root;
	iter->nil    = rb_tree->nil;
	iter->it     = iter->root;
	iter->top    = 0;
	iter->staus  = 1;
	iter->minkey = mem_rbtree_minkey(rb_tree,iter->root);
}

inline mem_rbtree_entry_t * rb_tree_after_iterator_next1(struct rb_tree_after_iterator_t * iter)
{
	//结束条件
	//if (iter->top==0 && iter->it !=iter->root) return iter->nil;
	if(iter->it == NULL) return (mem_rbtree_entry_t *)NULL;
	if(iter->it == iter->minkey)
		{
		iter->it = (mem_rbtree_entry_t *)NULL;
		return iter->minkey;
	}
		
	mem_rbtree_entry_t * nil = iter->nil;
	// 状态1 
	while (iter->it!=nil) 
	{ 
	iter->__stack[(iter->top)++]=iter->it; 
	iter->it = mem_rbtree_right(iter->index,iter->it);
	} 
	iter->it=iter->__stack[--(iter->top)]; 
  iter->staus = 2;//调到状态 2
	return iter->it;
}


inline mem_rbtree_entry_t * rb_tree_after_iterator_next2(struct rb_tree_after_iterator_t * iter)
{
	//结束条件
//	if (iter->top==0 && iter->it !=iter->root) return iter->nil;
	if(iter->it == NULL) return (mem_rbtree_entry_t *)NULL;
	if(iter->it == iter->minkey)
		{
		iter->it = (mem_rbtree_entry_t *)NULL;
		return iter->minkey;
	  }		
	mem_rbtree_entry_t * nil = iter->nil;
	// 状态2
	iter->it = mem_rbtree_left(iter->index,iter->it);
	return rb_tree_after_iterator_next1(iter);
}

inline mem_rbtree_entry_t * rb_tree_after_iterator_next(struct rb_tree_after_iterator_t * iter)
{
	if(iter->staus ==1 )return rb_tree_after_iterator_next1(iter);
	if(iter->staus ==2 )return rb_tree_after_iterator_next2(iter);
	return (mem_rbtree_entry_t *)ITERATOR_ERR_NOT_INIT;
}









#endif
