#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * 红黑树的性质
 * 1.每个结点要么红色,要么黑色
 * 2.根结点是黑色的
 * 3.每个叶子结点都是黑色(nil结点)
 * 4.如果一个几点为红色,那么两个子结点都是黑色   (不能有连续两个红色结点)
 * 5.任意一结点到叶子结点每条路径上黑色结点的个数都相等
 */

/**
 *  左旋转规则  假设当前结点为x
 *  1.结点变为右子树的左结点 
 *  	x->parent = x->right;
 *  2.右子树上移变为父亲结点,根据结点的分布来确定,右树变为父亲后,相对于祖父结点的分布
 *  	if(x==x->parent->parent->left){
 *  		x->parent->parent->left = x->right;
 *  	}else{
 *  		x->parent->parent->right = x->right;
 *  	}
 *  	x->right->parent = x->parent;
 *  3.右子树的左结点作为当前结点的右结点
 *  	x->right = x->right->left;
 *
 * 		   5                               7
 * 	        \         结点5左旋转         /  \
 * 	         7       -------------->      5   8
 * 	        / \							   \
 * 	        6  8                            6
 */


/**
 *  右旋转规则  假设当前结点为x
 *  1.结点变为左子树的右结点
 *  	x->parent = x->left;
 *  2.左子树上移变为父亲结点,根据结点的分布来确定父亲相对于祖父结点的分布
 *  	if(x==x->parent->left){
 *  		x->parent->parent->left = x->left;
 *  	}else{
 *  		x->parent->parent->right = x->left;
 *  	}
 *  	x->left->parent = x->parent;
 *  3.左子树的右结点,作为当前结点的左结点
 *  	x->left = x->left->right;
 *
 * 		4                                 2
 * 	   /           节点4右旋转           / \
 * 	   2          ------------->         1  4
 * 	  / \                                   /
 * 	  1  3                                 3
 */


/**
 *   结点的插入规则
 *   1.节点在最底端插入,且节点是红色的 (假设插入节点x)
 *   2.插入后如果父节点是红色的,则要进行调整
 *     1.x的父节点是祖父节点的左子树
 *   	case1 :叔父节点y是红色
 *   			1.将y与x的父亲同时着为黑色
 *   			2.然后把x的祖父变为红色
 *   			3.把x上移为祖父节点
 *   	case2:叔父节点是黑色,x是右节点
 *   			1.将x变为x的parent
 *   			2.左旋转x
 *   	case3:叔父节点是黑色,x是左节点
 *   			1.将x的parent变黑
 *   			2.x的祖父变红
 *   			3.右旋转x的祖父节点
 *     2.x的父节点是祖父节点的右子树(调整同上)
 *   3.如果上升为根节点,则将根节点变黑
 *   			
*/
 
/**
 *   结点的删除规则  假设删除节点为z  实际删除节点y x删除y的唯一子节点(先左后后)
 *   1.如果有一个子树为空,直接删除  y=z   
 *   2.如果右子树不为空则,删除右子树中最左边的节点,如果右子树为空,则删除祖先节点中为左子树的祖先 y
 *   3. if(y->left!=NULL) x=y->left else x= y->right;
 *   4.将原来y的父母设置为x的父母因为y即将被删除  ,x在y父亲中的分布取决与y在父亲中的分布,如果y是左节点,则x也是左节点,如果y是右节点则x也是右节点
 *   5.如果y!=z则把y的值换给z
 *   6.如果y为黑色则,则要进行调整,因为在某条路径上少了一个黑色节点
 *
 * 	 删除调整规则如下:
 * 	 	1.删除的调整是循环的,条件是 x不为根节点且x是一个黑色节点,如果x是一个黑色节点则,直接染红即可
 * 	 	2.分两种情况
 * 	 		x是左子树 假设x的兄弟节点为w
 * 	 			case 1: w为红色
 * 	 					1.w着黑
 * 	 					2.x的parent变红
 * 	 					3.左旋转x的parent
 * 	 					4.重置兄弟节点 w = x->parent->right;
 * 	 			case 2: w黑色 且两个子树都是黑色
 * 	 					1.w 着黑
 * 	 					2.x变为x的parent
 * 	 			case 3: w黑色 w的左子树是红色 w的右子树是黑色
 * 	 					1.w着红
 * 	 					2.w的左子着黑
 * 	 					3.右旋转w
 * 	 					4.重置兄弟节点   w=x->parent->right;
 * 	 			case 4: w的右子树是红色
 * 	 					1.w着色为x父亲的颜色
 * 	 					2.x的parent着黑
 * 	 					3.w的右子树着黑
 * 	 					4.左旋转x的parent
 * 	 			调整完成 x=T  退出
 * 	 		x是右子树 (过程同上)
 * 	 	3.设置根节点的颜色,过程有可能改变了根节点的颜色
 *   
*/


 
/*定义结点的颜色*/
 typedef enum Color{
 		RED   = 1,
 		BLACK = 0
 }Color;
typedef struct Node{
	struct Node *parent;  //父节点
	struct Node *left;    //左子树
	struct Node *right;   //右子树
	int          key;     //key
	/*data 域*/
	Color        color;   //节点颜色
}Node,*RBTree;

/*插入一个结点*/
void  rbInsert(RBTree *T,int key);
/*查找结点*/
Node *rbSearch(RBTree T,int key);
/*删除结点*/
void  rbDelete(RBTree *T,Node *z); 
/*查找最小的结点*/
Node *rbMinKey(RBTree T);
/*查找最大的结点*/
Node *rbMaxKey(RBTree T);
/*打印红黑树*/
void  rbPrint(RBTree T);



/*插入调整*/
static void InsertFixup(RBTree *T,Node *z);
/*删除调整*/
static void DeleteFixup(RBTree *T,Node *x);
static Node *Parent(Node *x);
static Node *Left(Node *x);
static Node *Right(Node *x);
static void LeftRotate(RBTree *T, Node *x);
static void RightRotate(RBTree *T, Node *x);
static Node *RealDeleteNode(RBTree *T,Node *x);

/*定义节点空指针*/
static Node *nil = NULL;


/*获取父亲节点*/
static Node *Parent(Node *x){
	 return x->parent;
}

static Node *Left(Node *x){
	  return x->left;
}

static Node *Right(Node *x){
	  return x->right;
}

static void LeftRotate(RBTree *T, Node *x){     //左旋转：结点x原来的右子树y旋转成为x的父母
	if( x-> right != nil )
	{
		Node *y=Right(x);
		x->right=y->left;
		if(y->left != nil)
		{
			y->left->parent=x;
		}
		y->parent=x->parent;


		if( x->parent == nil )
		{
			*T=y;
		}
		else
		{
			if( x == Left(Parent(x)) )
			{
				x->parent->left=y;
			}
			else
			{
				x->parent->right=y;
			}
		}
		y->left=x;
		x->parent=y;
	}
}



static void RightRotate(RBTree *T, Node *x)   //右旋转：结点x原来的左子树y旋转成为x的父母
{
	if( x->left != nil )
	{
		Node *y=Left(x);
		x->left=y->right;
		if( y->right != nil )
		{
			y->right->parent=x;
		}
		y->parent=x->parent;
		if( x->parent == nil )
		{
			*T=y;
		}
		else
		{
			if(x == Left(Parent(x)) )
			{
				x->parent->left=y;
			}
			else
			{
				x->parent->right=y;
			}
		}
		y->right=x;
		x->parent=y;
	}
}

/*查找实际要删除的结点*/
static Node *RealDeleteNode(RBTree *T,Node *x){
		Node *p=x->right;
		while( p->left != nil )
		{
			p=p->left;
			 
		}
		return p;
}

void rbInsert(RBTree *T,int key){
	 if((*T)==NULL){
	 	*T = (Node*)malloc(sizeof(Node));
	 	//初始化nil结点
	 	nil =(Node*)malloc(sizeof(Node));
	 	nil->color = BLACK;
	 	//设置结点的指向
	 	(*T)->parent = nil;
	 	(*T)->left   = nil;
	 	(*T)->right  = nil;
	 	//设置结点属性,key 和color
	 	(*T)->key  = key;
	 	(*T)->color  = BLACK;
	 }else{
	 	Node *x = *T;
	 	Node *p = nil;
	 	while(x!=nil){
	 		p = x;
	 		if(key>x->key)
	 			x = x->right;
	 		else if(key<x->key)
	 			x = x->left;
	 		else
	 			return ;
	 	}
	 	x = (Node*)malloc(sizeof(Node));
	 	x->parent = p ;
	 	x->left   = nil;
	 	x->right  = nil;

	 	x->key  = key;
	 	x->color  = RED;
	 	if(key<p->key){
	 		p->left = x;
	 	}else{
	 		p->right = x;
	 	}
	 	InsertFixup(T,x);
	 }
}

/*插入调整*/
static void InsertFixup(RBTree *T,Node *z){
	 Node *y;
	 while(Parent(z)->color == RED){
	 	if(Parent(z) == Parent(Parent(z))->left){
	 		y = Parent(Parent(z))->right;  //获取叔父结点
	 		if(y->color==RED){             //case 1  如果叔父结点为红色,则把父节点和叔父结点着黑,祖父结点着红,z上移到祖父结点
	 			y->color  = BLACK;
	 			z->parent->color = BLACK;
	 			z->parent->parent->color = RED;
	 			z = Parent(Parent(z));
	 		}else{
	 			if(z==Parent(z)->right){   //case 2  如果叔父结点为黑色,z右结点,z上移为父亲结点,左旋转z结点,此时变为case3的情况
	 				z = z->parent;
	 				LeftRotate(T,z);
	 			}
	 			z->parent->color         = BLACK;   //case 3 叔父结点为黑色,且z的左结点,z的父亲着着黑,z的祖父着红,然后旋转z的祖父结点
	 			Parent(Parent(z))->color = RED;
	 			RightRotate(T,Parent(Parent(z)));
	 		}
	 	}else{  //对称 调整同上
	 	   y = Parent(Parent(z))->left;
	 	   if(y->color==RED){
	 	   	   y->color  = BLACK;
	 	   	   z->parent->color = BLACK;
	 	   	   z->parent->parent->color = RED;
	 	   	   z = Parent(Parent(z));
	 	   }else{
	 	   	   if(z==Parent(z)->left){
	 	   	   	  z = z ->parent;
	 	   	   	  RightRotate(T,z); 
	 	   	   }
	 	   	   z->parent->color         = BLACK;
	 	   	   Parent(Parent(z))->color = RED;
	 	   	   LeftRotate(T,Parent(Parent(z)));
	 	   }
	 	}
	 }
	 (*T)->color = BLACK;
} 

/**
 *   结点的删除规则  假设删除节点为z  实际删除节点y x删除y的唯一子节点(先左后后)
 *   1.如果有一个子树为空,直接删除  y=z   
 *   2.如果右子树不为空则,删除右子树中最左边的节点,如果右子树为空,则删除祖先节点中为左子树的祖先 y
 *   3. if(y->left!=NULL) x=y->left else x= y->right;
 *   4.将原来y的父母设置为x的父母因为y即将被删除  ,x在y父亲中的分布取决与y在父亲中的分布,如果y是左节点,则x也是左节点,如果y是右节点则x也是右节点
 *   5.如果y!=z则把y的值换给z
 *   6.如果y为黑色则,则要进行调整,因为在某条路径上少了一个黑色节点
 *
 */

void rbDelete(RBTree *T,Node *z){
	 if(z==nil || z==NULL)
	 		return ;
	 Node *y;
	 Node *x;
	 if(z->left==nil || z->right ==nil){
	 	y = z;
	 }else{
	 	y = RealDeleteNode(T,z);
	 }
	 //x指向实际删除结点的子结点
	 if(y->left!=nil) 
	 	x = y->left ;
	 else
	 	x = y->right;   

	 x->parent = y->parent;   //删除结点y
	 if(y->parent==nil){
	 	*T = x;
	 }else{
	 	if(y==Parent(y)->left)
	 		y->parent->left = x;
	 	else
	 		y->parent->right = x;
	 }
	 if(y!=z){
	 	 z->key = y->key;
	 }
	 //如果删除的结点是黑色,违法了性质5,要进行删除调整
	 if(y->color==BLACK){
	 	DeleteFixup(T,x);
	 }
}



/*删除调整*/
static void DeleteFixup(RBTree *T,Node *x){
	 while(x!=(*T) && x->color==BLACK){
	 	if(x==Parent(x)->left){  
	 		Node *w = Parent(x)->right;  //w 为x的兄弟结点
	 		if(w->color ==RED){          //case 1 兄弟结点为红色
	 			w->color = BLACK;
	 			x->parent->color = RED;
	 			LeftRotate(T,Parent(x));
	 			w = Parent(x)->right;
	 		}
	 		if(w==nil) break;
	 		if(Left(w)->color ==BLACK && Right(w)->color==BLACK ){   //case2 兄弟结点的两个子结点都为黑
	 			w->color = RED;
	 			x = Parent(x);
	 		}else if(w->right->color ==BLACK){    //case3 w的左子树为红色,右子树为黑色
	 			w->color = RED;
	 			w->left->color = BLACK;
	 			RightRotate(T,w);
	 			w = Parent(x)->right;
	 		}
	 		w->color = x->parent->color;         //case 4 w的右子树为红色
	 		x->parent->color = BLACK;
	 		w->right->color = BLACK;
	 		LeftRotate(T,Parent(x));
	 	}else{  //对称 调整同上
	 		Node *w= Parent(x)->left;
	 		if(w->color == RED){                 //case 1
	 			w->color = BLACK; 
	 			x->parent->color = RED;
	 			RightRotate(T,Parent(x));
	 			w = Parent(x)->left;
	 		}
	 		if(w==nil) break;
	 		if(Left(w)->color == BLACK && Right(w)->color == BLACK ){  //case 2
	 			w->color = RED;
	 			x = Parent(x);
	 		}else if(w->left->color == BLACK){                       //case 3
	 			w->color = RED;
	 			w->right->color = BLACK;
	 			LeftRotate(T,w);
	 			w = Parent(x)->left;
	 		}
	 		w->color = x->parent->color;
	 		x->parent->color = BLACK;
	 		w->left->color = BLACK;
	 		RightRotate(T,Parent(x));
	 	}
	 	x = *T;
	 }
	 x->color = BLACK;
}



/*查找某个结点*/
Node *rbSearch(RBTree T,int key){
	if(T!=nil){
		if(T->key<key)
			rbSearch(T->right,key);
		else if(T->key>key)
			rbSearch(T->left,key);
		else
			return T==nil ? NULL : T;
	}
}

/*打印结点*/
void rbPrint(RBTree T){
	 if(T!=NULL && T!=nil){
	 	rbPrint(T->left);
	 	printf("%d(%s)\n",T->key,(T->color==RED) ? "红":"黑");
	 	rbPrint(T->right);
	 }
}
/*查找最小最小结点*/
Node *rbMinKey(RBTree T){
	  Node *x=T;
	  Node *p=nil;
	  while(x!=nil){
	  		p = x;
	  		x = x->left;
	  }
	  return p==nil ? NULL : p;
}

/*查找最大结点*/
Node *rbMaxKey(RBTree T){
	  Node *x=T;
	  Node *p=nil;
	  while(x!=nil){
	  		p = x;
	  		x = x->right;
	  }
	  return p==nil ? NULL : p;
}



#endif