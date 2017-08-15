%define api.pure
%parse-param {ParseResult* result}
%locations
%no-lines
%verbose
%lex-param{ yyscan_t scanner}
%parse-param { yyscan_t scanner }
%{  
#include <stdint.h>
#include "parser.hh"

#define YYDEBUG 1
%}



%{
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "sql_parser.lex.h"

// 定义成从结构体的成员进行词法扫描
//#define YYLEX_PARAM result->yyscan_info_

int strcasecmp_(rapidjson::Value * value,const char * ch)
{
	//cout<<"strcasecmp_ "<<value->FindMember("str_value_")->value.GetString()<<endl;
return  strcasecmp( value->FindMember("str_value_")->value.GetString() ,ch ) ;
}

void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s,...);
void yyerror(YYLTYPE* yylloc, ParseResult* p,const char* s,...);
void yyerror(YYLTYPE* yylloc, ParseResult* p,yyscan_t scanner,const char* s,...);

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type ,int node_tag, rapidjson::Value* t1)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  if(t1)val_child.PushBack(*t1, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  if(t1)delete t1;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);

  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
 // type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5,rapidjson::Value* t6)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
    if(t6)val_child.PushBack(*t6, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
  if(t6)delete t6;
}

void malloc_non_terminal_node_with_type(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator,const char * type_name,const char * type_type, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5,rapidjson::Value* t6,rapidjson::Value* t7)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
    if(t6)val_child.PushBack(*t6, Allocator); 
    if(t7)val_child.PushBack(*t7, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator).AddMember(rapidjson::StringRef(type_name), rapidjson::StringRef(type_type), Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
  if(t6)delete t6;
  if(t7)delete t7;
}


void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
 if(t1)val_child.PushBack(*t1, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
 if(t1) delete t1;
}

void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
}

void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);

  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
}
void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
 // type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
}

void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
}


void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5,rapidjson::Value* t6)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
    if(t6)val_child.PushBack(*t6, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
  if(t6)delete t6;
}

void malloc_non_terminal_node(rapidjson::Value **val_father,rapidjson::Document::AllocatorType& Allocator, int node_tag, rapidjson::Value* t1,rapidjson::Value* t2,rapidjson::Value* t3,rapidjson::Value* t4,rapidjson::Value* t5,rapidjson::Value* t6,rapidjson::Value* t7)
{
	*val_father = new rapidjson::Value;
  rapidjson::Value val_tag;
  rapidjson::Value val_child;
  //rapidjson::Value value_;
  //rapidjson::Value type_;

  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_child.SetArray();
  	if(t1)val_child.PushBack(*t1, Allocator); 
  	if(t2)val_child.PushBack(*t2, Allocator); 
  	if(t3)val_child.PushBack(*t3, Allocator); 
  	if(t4)val_child.PushBack(*t4, Allocator); 
    if(t5)val_child.PushBack(*t5, Allocator); 
    if(t6)val_child.PushBack(*t6, Allocator); 
    if(t7)val_child.PushBack(*t7, Allocator); 
  (*val_father)->SetObject().AddMember("tag", val_tag, Allocator);
  (*val_father)->AddMember("children", val_child, Allocator);
  
  if(t1)delete t1;
  if(t2)delete t2;
  if(t3)delete t3;
  if(t4)delete t4;
  if(t5)delete t5;
  if(t6)delete t6;
  if(t7)delete t7;
}

void  malloc_terminal_node_(rapidjson::Value& val_father, rapidjson::Document::AllocatorType& Allocator, int node_tag)
{
	if( NULL == &val_father )return;
  rapidjson::Value val_tag;
  //rapidjson::Value value_;
  //rapidjson::Value type_;
  
  val_tag.SetInt(node_tag);
  //value_.SetInt(0);
  //type_.SetInt(0);
  val_father.SetObject().AddMember("tag", val_tag, Allocator);
}

#define malloc_terminal_node(val_father,Allocator,node_tag)\
do																	  														\
{                                                               	\
	val_father = new rapidjson::Value;                            	\
	malloc_terminal_node_(*(val_father),Allocator,node_tag); 	\
}while(0);


#define merge_nodes(val_father,Allocator,node_tag,node) \
do																											\
{                                                       \
	val_father = new rapidjson::Value;                    \
	merge_nodes_(*(val_father),Allocator,node_tag,node);  \
	                                                      \
}while(0);


void  merge_nodes_(rapidjson::Value& val_father, rapidjson::Document::AllocatorType& Allocator,int node_tag, rapidjson::Value* node)
{
if(&val_father == NULL ||node == NULL )return ;
rapidjson::Value val_tag;
val_tag.SetInt(node_tag);
val_father.SetObject().AddMember("tag", val_tag, Allocator);

rapidjson::Value val_child;
val_child.SetArray();
val_child.PushBack(*node, Allocator); 
val_father.AddMember("children", val_child, Allocator);
}

// printf("SafeAddMember : [%d], %s is not NULL\n",__LINE__,a);  
	//printf("[%d], %s is NULL\n",__LINE__,a);  
#define SafeAddMember(root,a,b,c) \
do{														\
if(b)                         \
{                             \
(root)->AddMember((a),*(b),(c));  \
}                             \
else 														\
	{                             \
	}                             \
}while(0);



void malloc_list_node(rapidjson::Value ** root,rapidjson::Document::AllocatorType& Allocator,int num,...)
{
va_list va;
int i;

va_start(va, num);
rapidjson::Value *first = va_arg(va, rapidjson::Value*);
int j = 1;
while( first == NULL && j < num )
{
	first = va_arg(va, rapidjson::Value*);
	++j;
	if( j == num )return;
}	

	
if( first->IsArray() )
{
		rapidjson::Value * it;
		for( i = j; i < num; ++i)
		{
		  it = va_arg(va, rapidjson::Value*);
		  if(it)first->PushBack(*it, Allocator);
		}
		va_end(va);
}
else 
{
  rapidjson::Value val_child;
  val_child.SetArray();
  val_child.PushBack(*first, Allocator); 
  rapidjson::Value * it;
		for( i = 1; i < num; ++i)
		{
		  it = va_arg(va, rapidjson::Value*);
		  if(it)val_child.PushBack(*it, Allocator);
		}
		va_end(va);
  
  first = new rapidjson::Value;
  first->Swap(val_child);
}
*root = first;
}


%}


%token <node> NAME
%token <node> STRING
%token <node> INTNUM
%token <node> DATE_VALUE
%token <node> HINT_VALUE
%token <node> BOOL
%token <node> APPROXNUM
%token <node> NULLX
%token <node> UNKNOWN
%token <node> QUESTIONMARK
%token <node> SYSTEM_VARIABLE
%token <node> TEMP_VARIABLE

%left	UNION EXCEPT
%left	INTERSECT
%left	OR
%left	AND
%right NOT
%left COMP_LE COMP_LT COMP_EQ COMP_GT COMP_GE COMP_NE
%left CNNOP
%left LIKE
%nonassoc BETWEEN
%nonassoc IN
%nonassoc IS NULLX BOOL UNKNOWN
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%right UMINUS
%left '(' ')'
%left '.'


%token ADD AND ANY ALL ALTER AS ASC
%token BETWEEN BEGI BIGINT BINARY BOOLEAN BOTH BY
%token CASCADE CASE CHARACTER CLUSTER CNNOP COMMENT COMMIT
       CONSISTENT COLUMN COLUMNS CREATE CREATETIME
       CURRENT_USER CHANGE_OBI SWITCH_CLUSTER
%token DATE DATETIME DEALLOCATE DECIMAL DEFAULT DELETE DESC DESCRIBE
       DISTINCT DOUBLE DROP DUAL
%token ELSE END END_P ERROR EXCEPT EXECUTE EXISTS EXPLAIN
%token FLOAT FOR FROM FULL FROZEN FORCE
%token GLOBAL GLOBAL_ALIAS GRANT GROUP
%token HAVING HINT_BEGIN HINT_END HOTSPOT
%token IDENTIFIED IF IN INNER INTEGER INTERSECT INSERT INTO IS
%token JOIN
%token KEY
%token LEADING LEFT LIMIT LIKE LOCAL LOCKED
%token MEDIUMINT MEMORY MOD MODIFYTIME MASTER
%token NOT NUMERIC
%token OFFSET ON OR ORDER OPTION OUTER
%token PARAMETERS PASSWORD PRECISION PREPARE PRIMARY
%token READ_STATIC REAL RENAME REPLACE RESTRICT PRIVILEGES REVOKE RIGHT
       ROLLBACK KILL READ_CONSISTENCY
%token SCHEMA SCOPE SELECT SESSION SESSION_ALIAS
       SET SHOW SMALLINT SNAPSHOT SPFILE START STATIC SYSTEM STRONG SET_MASTER_CLUSTER SET_SLAVE_CLUSTER SLAVE
%token TABLE TABLES THEN TIME TIMESTAMP TINYINT TRAILING TRANSACTION TO
%token UNION  UPDATE USER USING 
%token VALUES VARCHAR VARBINARY
%token WHERE WHEN WITH WORK PROCESSLIST QUERY CONNECTION WEAK 
%token UNIQUE FULLTEXT SPATIAL HASH BTREE INDEX SKIPLIST

%token <non_reserved_keyword>
       AUTO_INCREMENT CHUNKSERVER COMPRESS_METHOD CONSISTENT_MODE
       EXPIRE_INFO GRANTS JOIN_INFO
       MERGESERVER REPLICA_NUM ROOTSERVER ROW_COUNT SERVER SERVER_IP
       SERVER_PORT SERVER_TYPE STATUS TABLE_ID TABLET_BLOCK_SIZE TABLET_MAX_SIZE EXTERN_SIZE
       UNLOCKED UPDATESERVER USE_BLOOM_FILTER VARIABLES VERBOSE WARNINGS

%type <node> sql_stmt stmt_list stmt
%type <node> select_stmt insert_stmt update_stmt delete_stmt
%type <node> create_table_stmt opt_table_option_list table_option
%type <node> drop_table_stmt table_list
%type <node> explain_stmt explainable_stmt kill_stmt
%type <node> expr_list expr expr_const arith_expr simple_expr
%type <node> column_ref
%type <node> case_expr func_expr in_expr
%type <node> case_arg when_clause_list when_clause case_default
%type <node> update_asgn_list update_asgn_factor
%type <node> table_element_list table_element column_definition
%type <node> data_type opt_if_not_exists opt_if_exists
%type <node> replace_or_insert opt_insert_columns column_list
%type <node> insert_vals_list insert_vals
%type <node> select_with_parens select_no_parens select_clause
%type <node> simple_select no_table_select select_limit select_expr_list
%type <node> opt_where opt_groupby opt_order_by order_by opt_having
%type <node> opt_select_limit limit_expr opt_for_update
%type <node> sort_list sort_key opt_asc_desc
%type <node> opt_distinct distinct_or_all projection
%type <node> from_list table_factor relation_factor joined_table
%type <node> join_type join_outer
%type <node> opt_float opt_time_precision opt_char_length opt_decimal
%type <node> opt_equal_mark opt_precision opt_verbose
%type <node> opt_column_attribute_list column_attribute
%type <node> show_stmt opt_show_condition opt_like_condition
%type <node> prepare_stmt stmt_name preparable_stmt
%type <node> variable_set_stmt var_and_val_list var_and_val to_or_eq
%type <node> execute_stmt argument_list argument opt_using_args
%type <node> deallocate_prepare_stmt deallocate_or_drop
%type <ival> opt_scope opt_drop_behavior opt_full
%type <node> create_user_stmt user_specification user_specification_list user password
%type <node> drop_user_stmt user_list
%type <node> set_password_stmt opt_for_user
%type <node> rename_user_stmt rename_info rename_list
%type <node> lock_user_stmt lock_spec
%type <node> grant_stmt priv_type_list priv_type priv_level opt_privilege
%type <node> revoke_stmt opt_on_priv_level
%type <node> opt_limit opt_for_grant_user opt_flag opt_is_global
%type <node> parameterized_trim
%type <ival> opt_with_consistent_snapshot opt_config_scope
%type <node> opt_work begin_stmt commit_stmt rollback_stmt
%type <node> alter_table_stmt alter_column_actions alter_column_action
%type <node> opt_column alter_column_behavior
%type <node> alter_system_stmt alter_system_actions alter_system_action
%type <node> server_type opt_cluster_or_address opt_comment
%type <node> column_name relation_name function_name column_label
%type <node> opt_hint opt_hint_list hint_option opt_force
%type <node> when_func when_func_stmt opt_when when_func_name
%type <non_reserved_keyword> unreserved_keyword
%type <ival> consistency_level
%type <node> opt_comma_list hint_options
%type <node> index_type index_constraint create_index_stmt

%start sql_stmt
%%

sql_stmt:
    stmt_list END_P
    {
      /*merge_nodes($$, result->malloc_pool_, T_STMT_LIST, $1);*/
      merge_nodes($$,result->Doc.GetAllocator(),T_STMT_LIST,$1 );
      result->Doc.SetObject().AddMember("ROOT",*$$ , result->Doc.GetAllocator());
      //result->result_tree_ = $$;
      delete $$;
      YYACCEPT;
    }
  ;
  

stmt_list:
    stmt_list ';' stmt
    {
      if ($3 != NULL)
        /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3 );
        {
        	malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
        }
      else
        $$ = $1;
    }
  | stmt
    {
      $$ = ($1 != NULL) ? $1 : NULL;
    }
  ;



stmt:
    select_stmt       				{ $$ = $1; }
  | insert_stmt       				{ $$ = $1; }
  | create_table_stmt 				{ $$ = $1; }
  | create_index_stmt					{ $$ = $1; }
  | update_stmt       				{ $$ = $1; }
  | delete_stmt       				{ $$ = $1; }
  | drop_table_stmt   				{ $$ = $1; }
  | explain_stmt      				{ $$ = $1; }
  | show_stmt         				{ $$ = $1; }
  | prepare_stmt      				{ $$ = $1; }
  | variable_set_stmt 				{ $$ = $1; }
  | execute_stmt      				{ $$ = $1; }
  | alter_table_stmt  				{ $$ = $1; }
  | alter_system_stmt 				{ $$ = $1; }
  | deallocate_prepare_stmt   { $$ = $1; }
  | create_user_stmt 					{ $$ = $1; }
  | drop_user_stmt 						{ $$ = $1; }
  | set_password_stmt 				{ $$ = $1; }
  | rename_user_stmt 					{ $$ = $1; }
  | lock_user_stmt 						{ $$ = $1; }
  | grant_stmt 								{ $$ = $1; }
  | revoke_stmt							  { $$ = $1; }
  | begin_stmt 								{ $$ = $1; }
  | commit_stmt 							{ $$ = $1; }
  | rollback_stmt							{ $$ = $1; }
  | kill_stmt 								{ $$ = $1; }
  | /*EMPTY*/  							  { $$ = NULL; }
  ;
/*****************************************************************************
 *
 *	expression grammar
 *
 *****************************************************************************/

expr_list:
    expr
    {
      $$ = $1;
    }
  | expr_list ',' expr
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  ;

column_ref:
    column_name
    { //$$ = $1;
     malloc_terminal_node($$,result->Doc.GetAllocator(), T_OP_NAME_FIELD);
		 SafeAddMember($$,"COLUMN_NAME"  ,$1, result->Doc.GetAllocator());

    	 }
  | relation_name '.' column_name
    {
     // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, $3);
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, $3);
				malloc_terminal_node($$,result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember($$,"RELATION_NAME",$1, result->Doc.GetAllocator());
				SafeAddMember($$,"COLUMN_NAME"  ,$3, result->Doc.GetAllocator());
     // dup_expr_string($$->str_value_, result, @3.first_column, @3.last_column);
    }
  |
    relation_name '.' '*'
    {
      // malloc_terminal_node(node, result->malloc_pool_, T_STAR);
      rapidjson::Value* node ;
      malloc_terminal_node(node, result->Doc.GetAllocator(), T_STAR);
      // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, node);
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, node);
				malloc_terminal_node($$,result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember($$,"RELATION_NAME",$1, result->Doc.GetAllocator());
				SafeAddMember($$,"COLUMN_NAME"  ,node, result->Doc.GetAllocator());
    }
  ;

expr_const:
    STRING 					{ $$ = $1; $1->AddMember("CONST_TYPE","STRING", result->Doc.GetAllocator());}
  | DATE_VALUE 			{ $$ = $1; $1->AddMember("CONST_TYPE","DATE_VALUE", result->Doc.GetAllocator());}
  | INTNUM 					{ $$ = $1; $1->AddMember("CONST_TYPE","INTNUM", result->Doc.GetAllocator());}
  | APPROXNUM 			{ $$ = $1; $1->AddMember("CONST_TYPE","APPROXNUM", result->Doc.GetAllocator());}
  | BOOL 						{ $$ = $1; $1->AddMember("CONST_TYPE","BOOL", result->Doc.GetAllocator());}
  | NULLX 					{ $$ = $1; $1->AddMember("CONST_TYPE","NULL", result->Doc.GetAllocator());}
  | QUESTIONMARK 		{ $$ = $1; $1->AddMember("CONST_TYPE","QUESTIONMARK", result->Doc.GetAllocator());}
  | TEMP_VARIABLE		{ $$ = $1; $1->AddMember("CONST_TYPE","TEMP_VARIABLE", result->Doc.GetAllocator());}
  | SYSTEM_VARIABLE { $$ = $1; $1->AddMember("CONST_TYPE","SYSTEM_VARIABLE", result->Doc.GetAllocator());}
  ;
  
simple_expr:
    column_ref      { $$ = $1; }
  | expr_const	  	{ $$ = $1; }
  | '(' expr ')'	 	{ $$ = $2; }
  | '(' expr_list ',' expr ')'
    {
      /*ParseNode *node = NULL;*/
      /*malloc_non_terminal_node(node, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/
      /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, node);*/
      rapidjson::Value* node ;
      //malloc_non_terminal_node(&node, result->Doc.GetAllocator(), T_LINK_NODE, $2, $4);
      malloc_list_node(&node,result->Doc.GetAllocator(),2, $2, $4);
      merge_nodes($$, result->Doc.GetAllocator(),T_EXPR_LIST, node);

    }
  | case_expr
    {
      $$ = $1;
      /*
      yyerror(&@1, result, "CASE expression is not supported yet!");
      YYABORT;
      */
    }
  | func_expr				{  $$ = $1; }
  | when_func       {  $$ = $1; }
  | select_with_parens	    %prec UMINUS
    {	
    	malloc_terminal_node($$,result->Doc.GetAllocator(),T_SUB_SELECT);
      SafeAddMember($$,"SUB_SELECT",$1, result->Doc.GetAllocator());	
    	//$$ = $1; 
    }
  | EXISTS select_with_parens
    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EXISTS, 1, $2);*/
    	//malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_EXISTS, $2);
    	malloc_terminal_node($$,result->Doc.GetAllocator(),T_OP_EXISTS);
    	$$->AddMember("SUB_LINK_TYPE","EXISTS", result->Doc.GetAllocator());
    	SafeAddMember($$,"SUB_LINK_BODY",$2, result->Doc.GetAllocator());
    }
  ;

/* used by the expression that use range value, e.g. between and */
 arith_expr:
    simple_expr   { $$ = $1; }
  | '+' arith_expr %prec UMINUS
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_POS, $2);

    }
  | '-' arith_expr %prec UMINUS
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NEG, $2);

    }
  | arith_expr '+' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","ADDX", T_OP_ADD,  $1, $3);  }
  | arith_expr '-' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS, 2, $1, $3); */ malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MINUSX",T_OP_MINUS,$1, $3);}
  | arith_expr '*' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3); */   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MULX", T_OP_MUL,  $1, $3);}
  | arith_expr '/' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","DIVX", T_OP_DIV,  $1, $3);}
  | arith_expr '%' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","REMX", T_OP_REM,  $1, $3);}
  | arith_expr '^' arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3); */   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","POWX", T_OP_POW,  $1, $3);}
  | arith_expr MOD arith_expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MODX", T_OP_MOD,  $1, $3);}
 

expr:
    simple_expr   { $$ = $1; }
  | '+' expr %prec UMINUS
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","POS", T_OP_POS, $2);
    }
  | '-' expr %prec UMINUS
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","NEG", T_OP_NEG, $2);
    }
  | expr '+' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","ADD", T_OP_ADD, $1,$3);    } 
  | expr '-' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS,2, $1, $3);*/  malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MINUS", T_OP_MINUS, $1,$3);}
  | expr '*' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MUL", T_OP_MUL, $1,$3);   }
  | expr '/' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","DIV", T_OP_DIV, $1,$3);   }
  | expr '%' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","REM", T_OP_REM, $1,$3);   }
  | expr '^' expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","POW", T_OP_POW, $1,$3);   }
  | expr MOD expr     { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","MOD", T_OP_MOD, $1,$3);   }
  | expr COMP_LE expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","LE", T_OP_LE, $1,$3);     }
  | expr COMP_LT expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","LT", T_OP_LT, $1,$3);     }
  | expr COMP_EQ expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EQ, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","EQ", T_OP_EQ, $1,$3);     }
  | expr COMP_GE expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","GE", T_OP_GE, $1,$3);     }
  | expr COMP_GT expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","GT", T_OP_GT, $1,$3);     }
  | expr COMP_NE expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","NE", T_OP_NE, $1,$3);     }
  | expr LIKE expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 2, $1, $3); */    malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","LIKE", T_OP_LIKE, $1,$3); }
  | expr NOT LIKE expr { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_LIKE, 2, $1, $4);*/ }
  | expr AND expr %prec AND
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_AND, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","AND", T_OP_AND, $1,$3);
    }
  | expr OR expr %prec OR
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_OR, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","OR", T_OP_OR, $1,$3);
    }
  | NOT expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT, 1, $2);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","NOT", T_OP_NOT, $2);
    }
  | expr IS NULLX
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, $1,$3);
    }
  | expr IS NOT NULLX
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, $1,$4);
    }
  | expr IS BOOL
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
     malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, $1,$3);
    }
  | expr IS NOT BOOL
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, $1,$4);
    }
  | expr IS UNKNOWN
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, $1,$3);
    }
  | expr IS NOT UNKNOWN
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, $1,$4);

    }
  | expr BETWEEN arith_expr AND arith_expr	    %prec BETWEEN
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_BTW, 3, $1, $3, $5);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","BTW", T_OP_BTW, $1,$3,$5);
    }
  | expr NOT BETWEEN arith_expr AND arith_expr	  %prec BETWEEN
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_BTW, 3, $1, $4, $6);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","NOT_BTW", T_OP_NOT_BTW, $1,$4,$6);
    }
  | expr IN in_expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","IN", T_OP_IN, $1,$3);
    }
  | expr NOT IN in_expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_IN, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","NOT_IN", T_OP_NOT_IN, $1,$4);
    }
  | expr CNNOP expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_CNN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","CNN", T_OP_CNN, $1,$3);
    }
  ;

in_expr:
    select_with_parens
    {
    	$$ = $1;	
    	malloc_terminal_node($$,result->Doc.GetAllocator(),T_OP_IN);
    	$$->AddMember("SUB_LINK_TYPE","IN", result->Doc.GetAllocator());
    	SafeAddMember($$,"SUB_LINK_BODY",$1, result->Doc.GetAllocator());
    }
  | '(' expr_list ')'
    { 
    /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $2);*/ 
      merge_nodes($$, result->Doc.GetAllocator(),T_EXPR_LIST, $2);

    }
  ;
  

case_expr:
    CASE case_arg when_clause_list case_default END
    {
      /*merge_nodes($$, result->malloc_pool_, T_WHEN_LIST, $3);
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_CASE, 3, $2, $$, $4);*/
       // merge_nodes($$, result->Doc.GetAllocator(),T_WHEN_LIST, $3);
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","CASE", T_CASE,  $2, $$, $4);

    }
  ;

case_arg:
    expr                  { $$ = $1; }
  | /*EMPTY*/             { $$ = NULL; }
  ;

when_clause_list:
  	when_clause
    { $$ = $1; }
  | when_clause_list when_clause
    {
     /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,  $1, $2);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $2);

     }
  ;

when_clause:
  	WHEN expr THEN expr
    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_THEN, 2, $2, $4);*/
      malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","THEN", T_THEN,  $2, $4);
    }
  ;

case_default:
  	ELSE expr                { $$ = $2; }
  | /*EMPTY*/                { /*malloc_terminal_node($$, result->malloc_pool_, T_NULL);*/ }
  ;  
  

func_expr:
    function_name '(' '*' ')'
    {
    	
      if (strcasecmp_($1, "count") != 0)
      {
       /* yyerror(&@1, result, "Only COUNT function can be with '*' parameter!");*/
        YYABORT;
      }
      else
      {
        
        /*malloc_terminal_node(node, result->malloc_pool_, T_STAR);*/
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 1, node);*/
      	 rapidjson::Value * node;
      	 malloc_terminal_node(node, result->Doc.GetAllocator(),  T_STAR)
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"OP_TYPE","STAR", T_FUN_COUNT, node);
      }
    }
  | function_name '(' distinct_or_all expr ')'
    {
    	        

      if (strcasecmp_($1, "count") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, $3, $4);

      }
      else if (strcasecmp_($1, "sum") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, $3, $4);*/
        
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, $3, $4);

      }
      else if (strcasecmp_($1, "max") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","MAX", T_FUN_MAX, $3, $4);
      }
      else if (strcasecmp_($1, "min") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","MIN", T_FUN_MIN, $3, $4);
      }
      else if (strcasecmp_($1, "avg") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","AVG", T_FUN_AVG, $3, $4);
      }
      else
      {
        yyerror(&@1, result, "Wrong system function with 'DISTINCT/ALL'!");
        YYABORT;
      }
    }
  | function_name '(' expr_list ')'
    {
      if (strcasecmp_($1, "count") == 0)
      {
       //if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       //{
       //  yyerror(&@1, result, "COUNT function only support 1 parameter!");
       //  YYABORT;
       //}
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, NULL, $3);*/
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, $3);
      }
      else if (strcasecmp_($1, "sum") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "SUM function only support 1 parameter!");
       //   YYABORT;
       // }
       // /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, $3);
      }
      else if (strcasecmp_($1, "max") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "MAX function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, NULL, $3);*/
       malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","MAXX", T_FUN_MAX, $3);
      }
      else if (strcasecmp_($1, "min") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "MIN function only support 1 parameter!");
       //   YYABORT;
       // }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","MINX", T_FUN_MIN, $3);
      }
      else if (strcasecmp_($1, "avg") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "AVG function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","AVGX", T_FUN_AVG, $3);
      }
  //  else if (strcasecmp_($1, "trim") == 0)
  //  {
  //    if ((*$3)["type_"].GetInt() == T_LINK_NODE)
  //    {
  //      /*yyerror(&@1, result, "TRIM function syntax error! TRIM don't take %d params", $3->num_child_);*/
  //      YYABORT;
  //    }
  //    else
  //    {
  //      /*ParseNode* default_type = NULL;*/
  //      /*malloc_terminal_node(default_type, result->/*malloc_pool_, T_INT);*/
  //      /*default_type->value_ = 0;*/
  //      /*ParseNode* default_operand = NULL;*/
  //      /*malloc_terminal_node(default_operand, result->/*malloc_pool_, T_STRING);*/
  //      /*default_operand->str_value_ = " "; /* blank for default */
  //      /*default_operand->value_ = strlen(default_operand->str_value_);*/
  //      /*ParseNode *params = NULL;*/
  //      /*malloc_non_terminal_node(params, result->/*malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, $3);*/
  //      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_FUN_SYS, 2, $1, params);*/
  //    }
  //  }
      else  /* system function */
      {
        /*ParseNode *params = NULL;*/
        /*merge_nodes(params, result->malloc_pool_, T_EXPR_LIST, $3);*/
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, params);*/
         rapidjson::Value * params ;
         merge_nodes(params, result->Doc.GetAllocator(),T_EXPR_LIST, $3);
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUNX", T_FUN_SYS, $1, params);
      
      }
    }
  | function_name '(' expr AS data_type ')'
    {
      if (strcasecmp_($1, "cast") == 0)
      {
        (*$5)["value_"].Swap((*$5)["type_"]);
        rapidjson::Value tmp(T_INT);
        (*$5)["type_"].Swap(tmp);
        /*ParseNode *params = NULL;*/
        /*malloc_non_terminal_node(params, result->malloc_pool_, T_EXPR_LIST, 2, $3, $5);*/
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, params);*/
         rapidjson::Value *params ;
         malloc_non_terminal_node(&params, result->Doc.GetAllocator(), T_EXPR_LIST,$3,$5);
         malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","CAST", T_FUN_SYS, $1, params);
      }
      else
      {
        yyerror(&@1, result, "AS support cast function only!");
        YYABORT;
      }
    }
  | function_name '(' parameterized_trim ')'
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, $1, $3);

    }
  | function_name '(' ')'
    {
      if (strcasecmp_($1, "now") == 0 ||
          strcasecmp_($1, "current_time") == 0 ||
          strcasecmp_($1, "current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME, 1, $1);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME", T_CUR_TIME, $1);

      }
      else if (strcasecmp_($1, "strict_current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME_UPS, 1, $1);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME_UPS", T_CUR_TIME_UPS, $1);

      }
      else
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 1, $1);*/
        malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, $1);

      }
      //yyerror(&@1, result, "system/user-define function is not supported yet!");*/
      //YYABORT;
    }
  ;  
 
when_func:
    when_func_name '(' when_func_stmt ')'
    {
      $$ = $1;
      /*$$->children_[0] = $3;*/
     // $$->PushBack($3, result->Doc.GetAllocator());
       SafeAddMember($$,"WHEN_FUNC_STMT",$3, result->Doc.GetAllocator());
    }
  ;

when_func_name:
    ROW_COUNT
    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ROW_COUNT, 1, NULL);*/
     malloc_non_terminal_node_with_type(&$$, result->Doc.GetAllocator(),"FUN_TYPE","ROW_COUNT", T_ROW_COUNT, NULL);

    }
  ;

when_func_stmt:
    select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  ;

distinct_or_all:
    ALL
    {
       /*malloc_terminal_node($$, result->malloc_pool_, T_ALL);*/
        malloc_terminal_node($$, result->Doc.GetAllocator(), T_ALL);
			  

    }
  | DISTINCT
    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/          
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_DISTINCT);

    }
  ;
/*****************************************************************************
 *
 *	delete grammar
 *
 *****************************************************************************/
delete_stmt:
    DELETE FROM relation_factor opt_where opt_when
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DELETE, 3, $3, $4, $5);*/
      malloc_terminal_node( $$, result->Doc.GetAllocator(), T_DELETE );
      $$->AddMember("OPERATION_NAME","DELETE_STMT", result->Doc.GetAllocator() );
      
     SafeAddMember($$,"TABLE_NAME",$3, result->Doc.GetAllocator());
     SafeAddMember($$,"WHERE_CLAUSE",$4, result->Doc.GetAllocator());
     SafeAddMember($$,"OPT_WHEN",$5, result->Doc.GetAllocator());
    }
  ; 
  
  
/*****************************************************************************
 *
 *	update grammar
 *
 *****************************************************************************/

update_stmt:
    UPDATE opt_hint relation_factor SET update_asgn_list opt_where opt_when
    {
    
         malloc_terminal_node($$, result->Doc.GetAllocator(), T_UPDATE);
         $$->AddMember("OPERATION_NAME","UPDATE_STMT", result->Doc.GetAllocator() );
         SafeAddMember($$,"TABLE_NAME",$3, result->Doc.GetAllocator());
     		 SafeAddMember($$,"SET_LIST",$5, result->Doc.GetAllocator());
     		 SafeAddMember($$,"WHERE_CLAUSE",$6, result->Doc.GetAllocator());
				 SafeAddMember($$,"WHEN_CLAUSE",$7, result->Doc.GetAllocator());
				 SafeAddMember($$,"HINTS",$2, result->Doc.GetAllocator());
    }
  ;


update_asgn_list:
    update_asgn_factor
    {
      $$ = $1;
    }
  | update_asgn_list ',' update_asgn_factor
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1,$3);
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
 
    }
  ;

update_asgn_factor:
    column_name COMP_EQ expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_ASSIGN_ITEM, 2, $1, $3);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_ASSIGN_ITEM);
      SafeAddMember($$,"COLUNM_NAME",$1, result->Doc.GetAllocator());
			SafeAddMember($$,"EXPR",$3, result->Doc.GetAllocator());

    }
  ;
  

/*****************************************************************************
 *
 *	create index
 *  
 *****************************************************************************/
 
create_index_stmt:
		CREATE index_constraint INDEX relation_factor ON relation_factor USING index_type '(' column_list ')' opt_table_option_list
{
  malloc_terminal_node($$, result->Doc.GetAllocator(), T_CREATE_INDEX  );
  $$->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if($2) $$->AddMember("CONSTRAINT_TYPE",*$2, result->Doc.GetAllocator() );
  $$->AddMember("INDEX_NAME",*$4, result->Doc.GetAllocator() );
  $$->AddMember("RELATION_NAME",*$6, result->Doc.GetAllocator() );
  $$->AddMember("INDEX_TYPE",*$8, result->Doc.GetAllocator() ); 
  $$->AddMember("COLUMN_LIST",*$10, result->Doc.GetAllocator() ); 
  if($12)$$->AddMember("OPT_OPITION",*$12, result->Doc.GetAllocator() ); 
   // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_CREATE_INDEX,$2, $4, $6, index_column_list,table_options);
   //malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_UNIQUE);  
   //$$->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
}
|
    CREATE index_constraint INDEX  relation_factor ON relation_factor  '(' column_list ')'  opt_table_option_list
{
	malloc_terminal_node($$, result->Doc.GetAllocator(), T_CREATE_INDEX  );
  $$->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if($2) $$->AddMember("CONSTRAINT_TYPE",*$2, result->Doc.GetAllocator() );
  $$->AddMember("INDEX_NAME",*$4, result->Doc.GetAllocator() );
  $$->AddMember("RELATION_NAME",*$6, result->Doc.GetAllocator() );
  $$->AddMember("COLUMN_LIST",*$8, result->Doc.GetAllocator() ); 
  if($10)$$->AddMember("OPT_OPITION",*$10, result->Doc.GetAllocator() ); 

}
;   

index_constraint:
	UNIQUE
	{
		
		  malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_UNIQUE); 
		  $$->AddMember("str_value_","UNIQUE", result->Doc.GetAllocator() ); 
	}
	|FULLTEXT 			
	{  
		malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_FULLTEXT); 
		$$->AddMember("str_value_","FULLTEXT", result->Doc.GetAllocator() ); 

	}
	|SPATIAL  			
	{  
		malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_SPATIAL); 
		$$->AddMember("str_value_","SPATIAL", result->Doc.GetAllocator() ); 

	}
	|
	{
		$$ = NULL;
	}
	;

     
index_type:
	HASH
	{ 
		 malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_HASH);
		 $$->AddMember("str_value_","HASH", result->Doc.GetAllocator() );
	}
	|BTREE
	{ 
		 malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_BTREE); 
		 $$->AddMember("str_value_","BTREE", result->Doc.GetAllocator() );
	}
	|SKIPLIST
	{ 
		 malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_SKIPLIST); 
		 $$->AddMember("str_value_","SKIPLIST", result->Doc.GetAllocator() );
	}
	| /* EMPTY */
	{ $$ = NULL; }
	;

  
/*****************************************************************************
 *
 *	create grammar
 *
 *****************************************************************************/

create_table_stmt:
    CREATE TABLE opt_if_not_exists relation_factor '(' table_element_list ')'
    opt_table_option_list
    {
     /*
     ParseNode *table_elements = NULL;
      ParseNode *table_options = NULL;
      merge_nodes(table_elements, result->malloc_pool_, T_TABLE_ELEMENT_LIST, $6);
      merge_nodes(table_options, result->malloc_pool_, T_TABLE_OPTION_LIST, $8);
      malloc_non_terminal_node($$, result->/*malloc_pool_, T_CREATE_TABLE, 4, 
              $3,                    if not exists 
              $4,                   table name 
              table_elements,        columns or primary key
              table_options         table option(s) 
              );
     */
     //rapidjson::Value  *table_elements;
     //rapidjson::Value  *table_options;
     //merge_nodes(table_elements, result->Doc.GetAllocator(),T_TABLE_ELEMENT_LIST, $6);
     //merge_nodes(table_options,  result->Doc.GetAllocator(),T_TABLE_OPTION_LIST, $8);
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_CREATE_TABLE, $3, $4,table_elements,table_options);
     //$$->AddMember("OPERATION_NAME","CREATE_TABLE", result->Doc.GetAllocator() );
    
  malloc_terminal_node($$, result->Doc.GetAllocator(), T_CREATE_TABLE  );
  $$->AddMember("OPERATION_NAME","CREATE_TABLE", result->Doc.GetAllocator() );
  if($3) $$->AddMember("IS_EXISTS",*$3, result->Doc.GetAllocator() );
  $$->AddMember("TABLE_NAME",*$4, result->Doc.GetAllocator() );
  $$->AddMember("TABLE_ELEMENT",*$6, result->Doc.GetAllocator() );
  if($8)$$->AddMember("OPT_OPITION",*$8, result->Doc.GetAllocator() ); 
    
    
    }
  ;

opt_if_not_exists:
    IF NOT EXISTS
    { /* malloc_terminal_node($$, result->malloc_pool_, T_IF_NOT_EXISTS);*/ 
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_IF_NOT_EXISTS);
      $$->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    }
  | /* EMPTY */
    { $$ = NULL; }
  ;

table_element_list:
    table_element
    {
      $$ = $1;
    }
  | table_element_list ',' table_element
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
      malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  ;

table_element:
    column_definition
    {
      $$ = $1;
    }
  | PRIMARY KEY '(' column_list ')'
    {
      /*ParseNode* col_list= NULL;*/
      /*merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, $4);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIMARY_KEY, 1, col_list);*/
         rapidjson::Value *col_list ;
         merge_nodes(col_list, result->Doc.GetAllocator(),  T_COLUMN_LIST,$4);
         malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_PRIMARY_KEY, col_list);

    }
  ;

column_definition:
    column_name data_type opt_column_attribute_list
    {
      /*ParseNode *attributes = NULL;*/
      /*merge_nodes(attributes, result->malloc_pool_, T_COLUMN_ATTRIBUTES, $3);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DEFINITION, 3, $1, $2, attributes);*/
 
			   rapidjson::Value *attributes;
			   merge_nodes(attributes, result->Doc.GetAllocator(),  T_COLUMN_ATTRIBUTES,$3);
         malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_COLUMN_DEFINITION, $1, $2, attributes);
    
    }
  ;

data_type:
    TINYINT
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER );*/ 
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_INTEGER);
      $$->AddMember("str_value_","TINYINT", result->Doc.GetAllocator() );

    }
  | SMALLINT
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER);*/ 
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_INTEGER);
      $$->AddMember("str_value_","SMALLINT", result->Doc.GetAllocator() );

    }
  | MEDIUMINT
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER);*/ 
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_INTEGER);
      $$->AddMember("str_value_","MEDIUMINT", result->Doc.GetAllocator() );
    }
  | INTEGER
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER);*/ 
       malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_INTEGER);
       $$->AddMember("str_value_","INTEGER", result->Doc.GetAllocator() );

    }
  | BIGINT
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INTEGER);*/
       malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_INTEGER);
       $$->AddMember("str_value_","BIGINT", result->Doc.GetAllocator() );

     }
  | DECIMAL opt_decimal
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
        malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        $$->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
}
      else{
        /*merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
        malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        $$->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
 }
      yyerror(&@1, result, "DECIMAL type is not supported");
      YYABORT;
    }
  | NUMERIC opt_decimal
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DECIMAL);}
      else{
       /* merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
     merge_nodes($$, result->Doc.GetAllocator(),T_TYPE_DECIMAL, $2);}
     $$->AddMember("str_value_","NUMERIC", result->Doc.GetAllocator() );
       
      yyerror(&@1, result, "NUMERIC type is not supported");
      YYABORT;
    }
  | BOOLEAN
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_BOOLEAN );*/ 
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_BOOLEAN);
    $$->AddMember("str_value_","BOOLEAN", result->Doc.GetAllocator() );

    }
  | FLOAT opt_float
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_FLOAT, 1, $2);*/ 
        malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_FLOAT,$2);
        $$->AddMember("str_value_","FLOAT", result->Doc.GetAllocator() );

    }
  | REAL
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DOUBLE);
    $$->AddMember("str_value_","REAL", result->Doc.GetAllocator() );

     }
  | DOUBLE opt_precision
    {
      (void)($2) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
       malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DOUBLE);
       $$->AddMember("str_value_","DOUBLE", result->Doc.GetAllocator() );
    }
  | TIMESTAMP opt_time_precision
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP, 1, $2);*/
     malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}
     $$->AddMember("str_value_","TIMESTAMP", result->Doc.GetAllocator() );
 
    }
  | DATETIME
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
         malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);
         $$->AddMember("str_value_","DATETIME", result->Doc.GetAllocator() );

     }
  | CHARACTER opt_char_length
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_CHARACTER);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
     malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_CHARACTER,$2);
     }
     $$->AddMember("str_value_","CHARACTER", result->Doc.GetAllocator() );
  
    }
  | BINARY opt_char_length
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_CHARACTER);
      $$->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
      }
   
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
      malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_CHARACTER,$2); 
      $$->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
       }
    }
  | VARCHAR opt_char_length
    {
      if ($2 == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_VARCHAR);
      $$->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
      }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_VARCHAR,$2);
      $$->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
         }
    }
  | VARBINARY opt_char_length
    {
      if ($2 == NULL){
        /* malloc_terminal_node(result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_VARCHAR); 
      $$->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_VARCHAR, $2);
      $$->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         } 
  
    }
  | CREATETIME
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CREATETIME);*/
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_CREATETIME);  
    $$->AddMember("str_value_","CREATETIME", result->Doc.GetAllocator() );  
     }
  | MODIFYTIME
    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_MODIFYTIME);*/ 
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_MODIFYTIME);    
    $$->AddMember("str_value_","MODIFYTIME", result->Doc.GetAllocator() ); 
    }
    
  | DATE
    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DATE);*/
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_DATE);     
    $$->AddMember("str_value_","DATE", result->Doc.GetAllocator() );
      yyerror(&@1, result, "DATE type is not supported");
      YYABORT;
    }
  | TIME opt_time_precision
    {
      if ($2 == NULL){
        /*malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIME);*/
    malloc_terminal_node($$, result->Doc.GetAllocator(), T_TYPE_TIME);    } 
      else{       /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIME, 1, $2);*/
    malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_TYPE_TIME,$2);     }
    $$->AddMember("str_value_","TIME", result->Doc.GetAllocator() );
      yyerror(&@1, result, "TIME type is not supported");
      YYABORT;
    }
    
  ;

opt_decimal:
    '(' INTNUM ',' INTNUM ')'
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,$2, $4);      
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $2, $4);
     $$->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    }
  | '(' INTNUM ')'
    { $$ = $2; }
  | /*EMPTY*/
    { $$ = NULL; }
  ;

opt_float:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_precision:
    PRECISION    { $$ = NULL; }
  | /*EMPTY*/    { $$ = NULL; }
  ;

opt_time_precision:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_char_length:
    '(' INTNUM ')'    { $$ = $2; }
  | /*EMPTY*/         { $$ = NULL; }
  ;

opt_column_attribute_list:
    opt_column_attribute_list column_attribute
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $2);
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $2);
    }
  | /*EMPTY*/
    { $$ = NULL; }
  ;

column_attribute:
    NOT NULLX
    {
      (void)($2) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_CONSTR_NOT_NULL);
    }
  | NULLX
    {
      (void)($1) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_CONSTR_NULL);

    }
  | DEFAULT expr_const
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $2);*/ 
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_CONSTR_DEFAULT,$2);

    }
  | AUTO_INCREMENT
    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_AUTO_INCREMENT);*/ 
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_CONSTR_AUTO_INCREMENT);

    }
  | PRIMARY KEY
    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_PRIMARY_KEY);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_CONSTR_PRIMARY_KEY);
     }
  ;

opt_table_option_list:
    table_option
    {
      $$ = $1;
    }
  | opt_table_option_list ',' table_option
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
   //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE,$1, $3);
   malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  | /*EMPTY*/
    {
      $$ = NULL;
    }
  ;

table_option:
    JOIN_INFO opt_equal_mark STRING
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_JOIN_INFO, 1, $3);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_JOIN_INFO, $3);
   
    }
  | EXPIRE_INFO opt_equal_mark STRING
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXPIRE_INFO, 1, $3);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_EXPIRE_INFO, $3);
  
    }
  | TABLET_MAX_SIZE opt_equal_mark INTNUM
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_TABLET_MAX_SIZE, $3);
 
    }
    | EXTERN_SIZE opt_equal_mark INTNUM
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   		malloc_terminal_node($$,result->Doc.GetAllocator(), T_EXTERN_SIZE);
   		if($3)$$->AddMember("EXTERN_SIZE",*$3, result->Doc.GetAllocator() );
    }
  | TABLET_BLOCK_SIZE opt_equal_mark INTNUM
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_BLOCK_SIZE, 1, $3);*/
     malloc_terminal_node($$,result->Doc.GetAllocator(), T_TABLET_BLOCK_SIZE);
   	 if($3)$$->AddMember("TABLET_BLOCK_SIZE",*$3, result->Doc.GetAllocator() );
    }
  | TABLE_ID opt_equal_mark INTNUM
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_ID, 1, $3);*/
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_TABLET_ID, $3);
 
    }
  | REPLICA_NUM opt_equal_mark INTNUM
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_REPLICA_NUM, 1, $3);*/
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_REPLICA_NUM, $3);
 
    }
  | COMPRESS_METHOD opt_equal_mark STRING
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMPRESS_METHOD, 1, $3);*/
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_COMPRESS_METHOD, $3);
  
    }
  | USE_BLOOM_FILTER opt_equal_mark BOOL
    {
      (void)($2) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_USE_BLOOM_FILTER, 1, $3);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_USE_BLOOM_FILTER, $3);
   
    }
  | CONSISTENT_MODE opt_equal_mark STATIC
    {
      (void)($2) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSISTENT_MODE);*/
       /*$$->value_ = 1;*/
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_CONSISTENT_MODE);
    rapidjson::Value val_val_(1);
    $$->AddMember("value_", val_val_, result->Doc.GetAllocator());
    
    }
  | COMMENT opt_equal_mark STRING
    {
      (void)($2); /*  make bison mute*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMMENT, 1, $3);*/
   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_COMMENT,$3);

    }
  ;

opt_equal_mark:
    COMP_EQ     { $$ = NULL; }
  | /*EMPTY*/   { $$ = NULL; }
  ;


/*****************************************************************************
 *
 *	drop table grammar
 *
 *****************************************************************************/

drop_table_stmt:
    DROP TABLE opt_if_exists table_list
    {
      /*ParseNode *tables = NULL;
      merge_nodes(tables, result->malloc_pool_, T_TABLE_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_DROP_TABLE, 2, $3, tables);
      */
      
      rapidjson::Value *tables ;
      merge_nodes(tables, result->Doc.GetAllocator(),T_TABLE_LIST, $4);
		  malloc_terminal_node($$,result->Doc.GetAllocator(),T_DROP_TABLE);      
      $$->AddMember("OPERATION_NAME","DROP_TABLE", result->Doc.GetAllocator() );
      if($3)$$->AddMember("IF_EXISTS",*$3, result->Doc.GetAllocator() );
			$$->AddMember("TABLE_LIST",*tables, result->Doc.GetAllocator() );
   
    }
  ;

opt_if_exists:
    /* EMPTY */
    { $$ = NULL; }
  | IF EXISTS
    { /*malloc_terminal_node($$, result->malloc_pool_, T_IF_EXISTS);*/ 
   malloc_terminal_node($$,result->Doc.GetAllocator(),T_IF_EXISTS);   }   

  ;

table_list:
    table_factor
    {
      $$ = $1;
    }
  | table_list ',' table_factor
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
  // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);  
  malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);    
  
    }
  ;
/*****************************************************************************
 *
 *	insert grammar
 *
 *****************************************************************************/
insert_stmt:
    replace_or_insert INTO relation_factor opt_insert_columns VALUES insert_vals_list
    opt_when
    {
    	/*
      ParseNode* val_list = NULL;
      merge_nodes(val_list, result->malloc_pool_, T_VALUE_LIST, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           
                              $4,           
                              val_list,     
                              NULL,         
                              $1,           
                              $7            
                              );
      */
      rapidjson::Value  *val_list ;
      merge_nodes(val_list, result->Doc.GetAllocator(),T_VALUE_LIST, $6);
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_INSERT,$3, $4,val_list,NULL,$1,$7);  
         malloc_terminal_node($$,result->Doc.GetAllocator(),T_INSERT);
         $$->AddMember("OPERATION_NAME","INSERT_TABLE", result->Doc.GetAllocator() );
         SafeAddMember($$,"TABLE_NAME",$3, result->Doc.GetAllocator());
         SafeAddMember($$,"OPT_INSERT_COLUMNS",$4, result->Doc.GetAllocator());
         SafeAddMember($$,"VALUE_LIST", val_list, result->Doc.GetAllocator());
         SafeAddMember($$,"REPLACE_OR_INSERT",$1, result->Doc.GetAllocator());
         SafeAddMember($$,"OPT_WHEN",$7, result->Doc.GetAllocator());

    }
  | replace_or_insert INTO relation_factor select_stmt
    {
     /*
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           
                              NULL,         
                              NULL,         
                              $4,           
                              $1,           
                              NULL          
                              );
       */
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_INSERT,$3,           
    //                         NULL,         
    //                         NULL,         
    //                         $4,           
    //                         $1,           
    //                         NULL          
    //                         );
         malloc_terminal_node($$,result->Doc.GetAllocator(),T_INSERT);  
         $$->AddMember("OPERATION_NAME","INSERT_SELECT_STMT", result->Doc.GetAllocator() );
         SafeAddMember($$,"TABLE_NAME",$3, result->Doc.GetAllocator());
         SafeAddMember($$,"SELECT_STMT",$4, result->Doc.GetAllocator());
         SafeAddMember($$,"REPLACE_OR_INSERT",$1, result->Doc.GetAllocator());

    }
  | replace_or_insert INTO relation_factor '(' column_list ')' select_stmt
    {
      /* if opt_when is really needed, use select_with_parens instead */
    /*  ParseNode* col_list = NULL;
      merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, $5);
      malloc_non_terminal_node($$, result->malloc_pool_, T_INSERT, 6,
                              $3,           
                              col_list,     
                              NULL,         
                              $7,           
                              $1,           
                              NULL          
                              );
      */
     
     // 
			//malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_INSERT, $3,           
     //                         col_list,     
     //                         NULL,         
     //                         $7,           
     //                         $1,           
     //                         NULL          
     //                         );
         rapidjson::Value  *col_list ;
         merge_nodes(col_list,result->Doc.GetAllocator(), T_COLUMN_LIST, $5);
         malloc_terminal_node($$,result->Doc.GetAllocator(),T_INSERT);  
         $$->AddMember("OPERATION_NAME","INSERT_SELECT_STMT", result->Doc.GetAllocator() );
         SafeAddMember($$,"TABLE_NAME",$3, result->Doc.GetAllocator());
         SafeAddMember($$,"COLUMNS_LIST",col_list, result->Doc.GetAllocator());
         SafeAddMember($$,"SELECT_STMT",$7, result->Doc.GetAllocator());
         SafeAddMember($$,"REPLACE_OR_INSERT",$1, result->Doc.GetAllocator());
    }
  ;

opt_when:
    /* EMPTY */
    { $$ = NULL; }
  | WHEN expr
    {
      $$ = $2;
    }
  ;

replace_or_insert:
    REPLACE
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;
      */
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
      rapidjson::Value tmp(1);
      SafeAddMember($$,"value_",&tmp, result->Doc.GetAllocator());

    }
  | INSERT
    {
     /*
      malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;
      */
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
      rapidjson::Value tmp(0);      
      SafeAddMember($$,"value_",&tmp, result->Doc.GetAllocator());
    }
  ;

opt_insert_columns:
    '(' column_list ')'
    {
       /* merge_nodes($$, result->malloc_pool_, T_COLUMN_LIST, $2);*/
       merge_nodes($$,result->Doc.GetAllocator(),T_BOOL,$2);
    }
  | /* EMPTY */
    { $$ = NULL; }
  ;

column_list:
    column_name { $$ = $1; }
  | column_list ',' column_name
    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    }
  ;

insert_vals_list:
    '(' insert_vals ')'
    {
    /*  merge_nodes($$, result->malloc_pool_, T_VALUE_VECTOR, $2);*/
    merge_nodes($$,result->Doc.GetAllocator(),T_VALUE_VECTOR,$2);
    }
  | insert_vals_list ',' '(' insert_vals ')' {
  /*  merge_nodes($4, result->malloc_pool_, T_VALUE_VECTOR, $4);*/
  /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $4);*/
  rapidjson::Value  *insert_vals  ;
  merge_nodes(insert_vals,result->Doc.GetAllocator(),T_VALUE_VECTOR,$4);
  //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, insert_vals);
  malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, insert_vals);
  }

insert_vals:
    expr { $$ = $1; }
  | insert_vals ',' expr
    {
   /*   malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
 
    }
  ;
  
  /*****************************************************************************
 *
 *	select grammar
 *
 *****************************************************************************/

select_stmt:
    select_no_parens opt_when    %prec UMINUS
    {
     /* $$ = $1;
      $$->children_[14] = $2;
      if ($$->children_[12] == NULL && $2 != NULL)
      {
        malloc_terminal_node($$->children_[12], result->malloc_pool_, T_BOOL);
        $$->children_[12]->value_ = 1;
      }
      */
       $$ = $1;
       $$->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

       SafeAddMember($$,"HINTS",$2 , result->Doc.GetAllocator());
       if($$->HasMember("limit") && $2 != NULL)
       	{
       		(*$$)["limit"].SetObject().AddMember("value_", rapidjson::Value(1), result->Doc.GetAllocator());
       	}
    }
  | select_with_parens    %prec UMINUS
    { 
    	$$ = $1; 
      $$->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

    	//malloc_terminal_node($$,result->Doc.GetAllocator(),T_SUB_SELECT);
			//SafeAddMember($$,"SUB_SELECT",$1, result->Doc.GetAllocator());	
    }
  ;

select_with_parens:
    '(' select_no_parens ')'      { 
        malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  	SafeAddMember($$,"SUB_SELECT",$2 , result->Doc.GetAllocator());
    	  //$$ = $2; 
    	
    	}
  | '(' select_with_parens ')'    { 
  	  malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  SafeAddMember($$,"SUB_SELECT",$2 , result->Doc.GetAllocator());
  	  //$$ = $2; 
  	
  	}
  ;

select_no_parens:
    no_table_select
    {
      $$= $1;
    }
  | simple_select opt_for_update
    {
      $$ = $1;
      //$$->children_[12] = $2;
      SafeAddMember($$,"limit",$2 , result->Doc.GetAllocator());

    }
  | select_clause order_by opt_for_update
    {
      /* use the new order by to replace old one */
      /*
      ParseNode* select = (ParseNode*)$1;
      if (select->children_[10])
        destroy_tree(select->children_[10]);
      select->children_[10] = $2;
      select->children_[12] = $3;
      $$ = select;
      */
      rapidjson::Value  select;
      	select.CopyFrom(*$1,result->Doc.GetAllocator());
      	if (select.HasMember("ORDER_BY_CLAUSE") && $2 ) {select.RemoveMember("ORDER_BY_CLAUSE");}select.AddMember("ORDER_BY_CLAUSE",*$2,result->Doc.GetAllocator());
      if($3)select.AddMember("limit",*$3,result->Doc.GetAllocator());
     // 	if($3)select.AddMember("ORDER_BY_CLAUSE",*$3,result->Doc.GetAllocator());
      $$->Swap(select);
    }
  | select_clause opt_order_by select_limit opt_for_update
    {
      /* use the new order by to replace old one */
      /*
      ParseNode* select = (ParseNode*)$1;
      if ($2)
      {
        if (select->children_[10])
          destroy_tree(select->children_[10]);
        select->children_[10] = $2;
      }

      // set limit value 
      if (select->children_[11])
        destroy_tree(select->children_[11]);
      select->children_[11] = $3;
      select->children_[12] = $4;
      $$ = select;
      */
      rapidjson::Value select;
      select.CopyFrom(*$1,result->Doc.GetAllocator());

      if ($2)
      {
      	if (select.HasMember("ORDER_BY_CLAUSE") /*&& $2*/) {select.RemoveMember("ORDER_BY_CLAUSE");select.AddMember("ORDER_BY_CLAUSE",*$2,result->Doc.GetAllocator());}
      	else if($2) select.AddMember("ORDER_BY_CLAUSE",*$2,result->Doc.GetAllocator());
      }	
     if ( select.HasMember("limit") /*&& $3*/ ){select.RemoveMember("limit");}
     	select.AddMember("limit",*$3,result->Doc.GetAllocator());
     if ( select.HasMember("for_update") )	{select.RemoveMember("for_update");} 
     if($4)select.AddMember("for_update",*$4,result->Doc.GetAllocator());
     $$->Swap(select);
    }
  ;

no_table_select:
    SELECT opt_hint opt_distinct select_expr_list opt_select_limit
    {
    	/*
      ParseNode* project_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              $3,             /* 1. distinct 
                              project_list,   /* 2. select clause 
                              NULL,           /* 3. from clause 
                              NULL,           /* 4. where 
                              NULL,           /* 5. group by 
                              NULL,           /* 6. having 
                              NULL,           /* 7. set operation 
                              NULL,           /* 8. all specified? 
                              NULL,           /* 9. former select stmt 
                              NULL,           /* 10. later_select stmt 
                              NULL,           /* 11. order_by 
                              $5,             /* 12. limit 
                              NULL,           /* 13. for update 
                              $2,             /* 14 hints 
                              NULL            /* 15 when clause 
                              );
                              */
       rapidjson::Value *project_list;
       merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,$4);
      
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);                   
       SafeAddMember($$,"DISTINCT",$3,result->Doc.GetAllocator());
       SafeAddMember($$,"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
       SafeAddMember($$,"LIMIT",$5,result->Doc.GetAllocator());
       SafeAddMember($$,"HINTS",$2,result->Doc.GetAllocator());
           }
  | SELECT opt_hint opt_distinct select_expr_list
    FROM DUAL opt_where opt_select_limit
    {
    	/*
      ParseNode* project_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              $3,             /* 1. distinct 
                              project_list,   /* 2. select_clause 
                              NULL,           /* 3. from clause 
                              $7,             /* 4. where 
                              NULL,           /* 5. group by 
                              NULL,           /* 6. having 
                              NULL,           /* 7. set operation 
                              NULL,           /* 8. all specified? 
                              NULL,           /* 9. former select stmt 
                              NULL,           /* 10. later select stmt 
                              NULL,           /* 11. order by 
                              $8,             /* 12. limit 
                              NULL,           /* 13. for update 
                              $2,             /* 14 hints 
                              NULL            /* 15 when clause 
                              );
                              */
      rapidjson::Value  *project_list ;
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,$4);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember($$,"DISTINCT",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember($$,"WHERE_CLAUSE",$7,result->Doc.GetAllocator());
      SafeAddMember($$,"LIMIT",$8,result->Doc.GetAllocator());
      SafeAddMember($$,"HINTS",$2,result->Doc.GetAllocator());
    }
  ;

select_clause:
    simple_select	              { $$ = $1; }
  | select_with_parens	        { $$ = $1; }
  ;

simple_select:
    SELECT opt_hint opt_distinct select_expr_list
    FROM from_list
    opt_where opt_groupby opt_having
    {
    	/*
      ParseNode* project_list = NULL;
      ParseNode* from_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, $4);
      merge_nodes(from_list, result->malloc_pool_, T_FROM_LIST, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              $3,             /* 1. distinct 
                              project_list,   /* 2. select clause 
                              from_list,      /* 3. from_clause 
                              $7,             /* 4. where 
                              $8,             /* 5. group_by 
                              $9,             /* 6. having 
                              NULL,           /* 7. set operation 
                              NULL,           /* 8. all specified? 
                              NULL,           /* 9. former select stmt 
                              NULL,           /* 10. later select stmt 
                              NULL,           /* 11. order by 
                              NULL,           /* 12. limit 
                              NULL,           /* 13. for update 
                              $2,             /* 14 hints 
                              NULL            /* 15 when clause 
                              );*/
      rapidjson::Value  *project_list ;
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,$4);
      rapidjson::Value  *from_list    ;
      merge_nodes(from_list,result->Doc.GetAllocator(),T_FROM_LIST   ,$6);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember($$,"DISTINCT",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember($$,"FROM_CLAUSE",from_list,result->Doc.GetAllocator());
			SafeAddMember($$,"WHERE_CLAUSE",$7,result->Doc.GetAllocator());
			SafeAddMember($$,"GROUP_BY_CLAUSE",$8,result->Doc.GetAllocator());
			SafeAddMember($$,"HAVING_CLAUSE",$9,result->Doc.GetAllocator());
			SafeAddMember($$,"HINTS",$2,result->Doc.GetAllocator());
    }
  | select_clause UNION opt_distinct select_clause
    {
    	/*
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_UNION);
	    malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              NULL,           /* 1. distinct
                              NULL,           /* 2. select clause
                              NULL,           /* 3. from clause
                              NULL,           /* 4. where
                              NULL,           /* 5. group by
                              NULL,           /* 6. having
                              set_op,  			  /* 7. set_operation
                              $3,             /* 8. all_specified
                              $1,             /* 9. former_select_stmt
                              $4,             /* 10.later_select_stmt
                              NULL,           /* 11. order by
                              NULL,           /* 12. limit
                              NULL,           /* 13. for update
                              NULL,           /* 14 hints
                              NULL            /* 15 when clause
                              );*/
      rapidjson::Value  *set_op ;
      malloc_terminal_node(set_op,result->Doc.GetAllocator(),T_SET_UNION);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);  
      
      SafeAddMember($$,"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember($$,"ALL_SPECIFIED",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"FORMER_SELECT_STMT",$1,result->Doc.GetAllocator());
			SafeAddMember($$,"LATER_SELECT_STMT",$4,result->Doc.GetAllocator());
    }
  | select_clause INTERSECT opt_distinct select_clause
    {
    	/*
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_INTERSECT);
      malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              NULL,           /* 1. distinct
                              NULL,           /* 2. select clause
                              NULL,           /* 3. from clause
                              NULL,           /* 4. where
                              NULL,           /* 5. group by
                              NULL,           /* 6. having
                              set_op,   			/* 7. set_operation
                              $3,             /* 8. all specified?
                              $1,             /* 9. former select stmt
                              $4,             /* 10. later select stmt
                              NULL,           /* 11. order by
                              NULL,           /* 12. limit
                              NULL,           /* 13. for update
                              NULL,           /* 14 hints
                              NULL            /* 15 when clause
                              );*/
      rapidjson::Value *set_op ;
      malloc_terminal_node(set_op,result->Doc.GetAllocator(),T_SET_INTERSECT);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember($$,"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember($$,"ALL_SPECIFIED",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"FORMER_SELECT_STMT",$1,result->Doc.GetAllocator());
			SafeAddMember($$,"LATER_SELECT_STMT",$4,result->Doc.GetAllocator());
    }
  | select_clause EXCEPT opt_distinct select_clause
    {
    	/*
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_EXCEPT);
	    malloc_non_terminal_node($$, result->malloc_pool_, T_SELECT, 15,
                              NULL,           /* 1. distinct
                              NULL,           /* 2. select clause
                              NULL,           /* 3. from clause
                              NULL,           /* 4. where
                              NULL,           /* 5. group by
                              NULL,           /* 6. having
                              set_op,   /* 7. set operation
                              $3,             /* 8. all specified?
                              $1,             /* 9. former select stmt
                              $4,             /* 10. later select stmt
                              NULL,           /* 11. order by
                              NULL,           /* 12. limit
                              NULL,           /* 13. for update
                              NULL,           /* 14 hints
                              NULL            /* 15 when clause
                              );*/
      rapidjson::Value *set_op ;
      malloc_terminal_node(set_op,result->Doc.GetAllocator(),T_SET_EXCEPT);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember($$,"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember($$,"ALL_SPECIFIED",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"FORMER_SELECT_STMT",$1,result->Doc.GetAllocator());
			SafeAddMember($$,"LATER_SELECT_STMT",$4,result->Doc.GetAllocator());
    }
  ;

opt_where:
    /* EMPTY*/
    {$$ = NULL;}
  | WHERE expr
    {
      $$ = $2;
    }
  | WHERE HINT_VALUE expr
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 2, $3, $2);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_WHERE_CLAUSE, $3, $2);
    }
  ;

select_limit:
  	LIMIT limit_expr OFFSET limit_expr
    {
      if ((*$2)["type_"].GetInt()== T_QUESTIONMARK && (*$4)["type_"].GetInt()== T_QUESTIONMARK)
      {
       /* $4->value_++;*/
       int i = ((*$4)["value_"]).GetInt();++i;
       rapidjson::Value tmp(i);
       (*$4)["value_"].Swap(tmp);
       
      }
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, $4);*/
     	malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_WHERE_CLAUSE, $2, $4);

    }
  | OFFSET limit_expr LIMIT limit_expr
    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
      malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
      if ((*$2)["type_"].GetInt()  == T_QUESTIONMARK && (*$4)["type_"].GetInt() == T_QUESTIONMARK )
      	{
      		int i =(*$4)["value_"].GetInt();
      		rapidjson::Value tmp(++i);
      		(*$4)["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LIMIT_CLAUSE, $4, $2);
	
    }
  | LIMIT limit_expr
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, NULL);*/
   		malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LIMIT_CLAUSE, $2, NULL);
 
    }
  | OFFSET limit_expr
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, NULL, $2);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LIMIT_CLAUSE, NULL, $2);

    }
  | LIMIT limit_expr ',' limit_expr
    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
    	malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
       if ((*$2)["type_"].GetInt()  == T_QUESTIONMARK && (*$4)["type_"].GetInt() == T_QUESTIONMARK )
      	{
      			int i = (*$4)["value_"].GetInt();
      			rapidjson::Value tmp(++i);
      		  (*$4)["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LIMIT_CLAUSE, $4, $2);	
    }
  ;

opt_hint:
    /* EMPTY*/
    {
      $$ = NULL;
    }
  | HINT_BEGIN opt_hint_list HINT_END
    {
     /* if ($2)
      {
        merge_nodes($$, result->malloc_pool_, T_HINT_OPTION_LIST, $2);
      }
      else
      {
        $$ = NULL;
      }*/
      if ($2)
      {
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_HINT_OPTION_LIST, $2);	
      }
      else
      {
        $$ = NULL;
      }
    }
  ;

opt_hint_list:
    hint_options
    {
      $$ = $1;
    }
  | opt_hint_list ',' hint_options
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);	
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
 
    }
  | /*EMPTY*/
    {
      $$ = NULL;
    }
  ;

hint_options:
    hint_option
    {
      $$ = $1;
    }
  | hint_options hint_option
    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $2);	
        malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $2);

    }
  ;

hint_option:
    READ_STATIC
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_READ_STATIC);*/
    malloc_terminal_node($$,result->Doc.GetAllocator(),T_READ_STATIC);	

    }
  | HOTSPOT
    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_HOTSPOT);*/
        malloc_terminal_node($$,result->Doc.GetAllocator(),T_HOTSPOT);	

    }
  | READ_CONSISTENCY '(' consistency_level ')'
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_READ_CONSISTENCY);
      $$->value_ = $3;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_READ_CONSISTENCY);	
      rapidjson::Value tmp;
      	tmp.SetInt($3);
      (*$$)["value_"].Swap(tmp );

    }
  | '(' opt_comma_list ')'
    {
      $$ = $2;
    }
  ;

opt_comma_list:
    opt_comma_list ','
    {
      $$ = $1;
    }
  | /*EMPTY*/
    {
      $$ = NULL;
    }
  ;
 
consistency_level:
  WEAK
  {
    $$ = 3;
  }
| STRONG
  {
    $$ = 4;
  }
| STATIC
  {
    $$ = 1;
  }
| FROZEN
  {
    $$ = 2;
  }
  ;
limit_expr:
    INTNUM
    { $$ = $1; }
  | QUESTIONMARK
    { $$ = $1; }
  ;

opt_select_limit:

    { $$ = NULL; }
  | select_limit
    { $$ = $1; }
  ;

opt_for_update:
    /* EMPTY*/
    { $$ = NULL; }
  | FOR UPDATE
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
    malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
    rapidjson::Value tmp(1);
    (*$$)["value_"].Swap(tmp );
    }
  ;

parameterized_trim:
    expr FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $1, $3);*/
      rapidjson::Value *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(0);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, $1, $3);
    }
  | BOTH expr FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(0);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, $2, $4); 
    }
  | LEADING expr FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 1;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, $2, $4);   
    }
  | TRAILING expr FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 2;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, $2, $4);     
    }
  | BOTH FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, $3);*/
      rapidjson::Value *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(0);
      (*default_type)["value_"].Swap(tmp);
      rapidjson::Value *default_operand ;
      malloc_terminal_node(default_operand,result->Doc.GetAllocator(),T_STRING);
      
      default_operand->AddMember("str_value_", " ", result->Doc.GetAllocator());
      rapidjson::Value tmp1(strlen((*default_operand)["str_value_"].GetString()));
      (*default_operand)["value_"].Swap(tmp1);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, $3);     

    }
  | LEADING FROM expr
    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 1;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, $3);*/
      
      rapidjson::Value *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*default_type)["value_"].Swap(tmp);
      rapidjson::Value * default_operand ;
      malloc_terminal_node(default_operand,result->Doc.GetAllocator(),T_STRING);
      
      default_operand->AddMember("str_value_", " ", result->Doc.GetAllocator());
      rapidjson::Value tmp1(strlen((*default_operand)["str_value_"].GetString()));
      (*default_operand)["value_"].Swap(tmp1);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, $3);     
  
    }
  | TRAILING FROM expr
    {
    /*  ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 2;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, $3);*/
      
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*default_type)["value_"].Swap(tmp);
      rapidjson::Value *default_operand ;
      malloc_terminal_node(default_operand,result->Doc.GetAllocator(),T_STRING);
      
      default_operand->AddMember("str_value_", " ", result->Doc.GetAllocator());
      rapidjson::Value tmp1(strlen((*default_operand)["str_value_"].GetString()));
      (*default_operand)["value_"].Swap(tmp1);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, $3);     
  
    }
  ;

opt_groupby:
    /* EMPTY */
    { $$ = NULL; }
  | GROUP BY expr_list
    {
    /*   merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $3);*/
    merge_nodes($$,result->Doc.GetAllocator(),T_EXPR_LIST,$3);
    }
  ;

opt_order_by:
  	order_by	              { $$ = $1;}
  | /*EMPTY*/             { $$ = NULL; }
  ;

order_by:
  	ORDER BY sort_list
    {
   /*   merge_nodes($$, result->malloc_pool_, T_SORT_LIST, $3);*/
        merge_nodes($$,result->Doc.GetAllocator(),T_SORT_LIST,$3);
     //    malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_LIST);  
      //   SafeAddMember($$,"ORDER_BY_CLAUSE",$3,result->Doc.GetAllocator());
    cout<<"T_SORT_LIST"<<endl;
      }
  ;

sort_list:
  	sort_key
    { $$ = $1; }
  | sort_list ',' sort_key
    { /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    	//   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1,$3);
    	malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    	}
  ;

sort_key:
    expr opt_asc_desc
    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_SORT_KEY, 2, $1, $2);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SORT_KEY, $1,$2);

    }
  ;

opt_asc_desc:
    /* EMPTY */
    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_ASC);
	
    	}
  | ASC
    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_ASC);
	
    	}
  | DESC
    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_DESC); */
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_DESC);
	
    	}
  ;

opt_having:
    /* EMPTY */
    { $$ = 0; }
  | HAVING expr
    {
      $$ = $2;
    }
  ;

opt_distinct:
    /* EMPTY*/
    {
      $$ = NULL;
    }
  | ALL
    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_ALL); */
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_ALL);

    }
  | DISTINCT
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_DISTINCT);

    }
  ;

projection:
    expr
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, $1);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PROJECT_STRING);
      SafeAddMember($$,"PROJECT",       $1 , result->Doc.GetAllocator());
       // dup_expr_string
      
    }
  | expr column_label
    {
    /*  ParseNode* alias_node = NULL;
      malloc_non_terminal_node(alias_node, result->malloc_pool_, T_ALIAS, 2, $1, $2);
      malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, alias_node);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);
      dup_expr_string(alias_node->str_value_, result, @2.first_column, @2.last_column);*/
     //rapidjson::Value *alias_node ;
    // malloc_non_terminal_node(&alias_node,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_PROJECT_STRING,  alias_node);
      
       //malloc_non_terminal_node(&alias_node,result->Doc.GetAllocator(),T_ALIAS,$2);
       malloc_terminal_node($$,result->Doc.GetAllocator(), T_PROJECT_STRING);
       SafeAddMember($$,"PROJECT",       $1 , result->Doc.GetAllocator());
       SafeAddMember($$,"PROJECT_ALIAS", $2, result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    }
  | expr AS column_label
    {
     /* ParseNode* alias_node = NULL;
      malloc_non_terminal_node(alias_node, result->malloc_pool_, T_ALIAS, 2, $1, $3);
      malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, alias_node);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);
      dup_expr_string(alias_node->str_value_, result, @3.first_column, @3.last_column);*/
     // rapidjson::Value *alias_node ;
     // malloc_non_terminal_node(&alias_node,result->Doc.GetAllocator(), T_ALIAS,  $1, $3);
     // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_PROJECT_STRING, alias_node);
     //malloc_non_terminal_node(&alias_node,result->Doc.GetAllocator(),T_ALIAS,$3);
     malloc_terminal_node($$,result->Doc.GetAllocator(), T_PROJECT_STRING);
     SafeAddMember($$,"PROJECT",      $1 , result->Doc.GetAllocator());
     SafeAddMember($$,"PROJECT_ALIAS",$3, result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    }
  | '*'
    {
    /*  ParseNode* star_node = NULL;
      malloc_terminal_node(star_node, result->malloc_pool_, T_STAR);
      malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, star_node);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);*/
      rapidjson::Value *star_node ;
      malloc_terminal_node(star_node,result->Doc.GetAllocator(),T_STAR);
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PROJECT_STRING);
      SafeAddMember($$,"PROJECT",star_node, result->Doc.GetAllocator());

      // dup_expr_string
    }
  ;

select_expr_list:
    projection
    {
      $$ = $1;
    }
  | select_expr_list ',' projection
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
     
    // if( $1 && $3 &&  $1->IsArray() )
    // 	{
    // 	$1->PushBack(*$3, result->Doc.GetAllocator());
    // 	}
    // 	else {
    // 		 //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
		//		 rapidjson::Value val_child;
    // 		 val_child.SetArray();
    // 		 val_child.PushBack(*$1, result->Doc.GetAllocator()); 
    // 		 val_child.PushBack(*$3, result->Doc.GetAllocator());
    // 		 $1 = new rapidjson::Value;
    // 		 $1->Swap(val_child);
    // 	}
    // 	$$ = $1;
    malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    }
  ;

from_list:
  	table_factor
    { $$ = $1; }
  | from_list ',' table_factor
    {/* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
		malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    	}
  ;

table_factor:
    relation_factor
    {
     // $$ = $1;
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
      SafeAddMember($$,"RELATION",$1, result->Doc.GetAllocator());

    }
  | relation_factor AS relation_name
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember($$,"RELATION",$1, result->Doc.GetAllocator());
    SafeAddMember($$,"TABLE_ALIAS",$3, result->Doc.GetAllocator());
    }
  | relation_factor relation_name
    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    //  malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember($$,"RELATION",$1, result->Doc.GetAllocator());
    SafeAddMember($$,"RELATION_ALIAS",$2, result->Doc.GetAllocator());
    }
  | select_with_parens AS relation_name
    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember($$,"RELATION",$1, result->Doc.GetAllocator());
    SafeAddMember($$,"RELATION_ALIAS",$3, result->Doc.GetAllocator());
    }
  | select_with_parens relation_name
    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember($$,"RELATION",$1, result->Doc.GetAllocator());
    SafeAddMember($$,"RELATION_ALIAS",$2, result->Doc.GetAllocator());
    }
  | joined_table
    {
    	$$ = $1;
    }
  | '(' joined_table ')' AS relation_name
    {
    /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $2, $5);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $2, $5);
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember($$,"RELATION",$2, result->Doc.GetAllocator());
    SafeAddMember($$,"RELATION_ALIAS",$5, result->Doc.GetAllocator());    	
    	
    	yyerror(&@1, result, "qualied joined table can not be aliased!");
      YYABORT;
    }
  ;

relation_factor:
    relation_name
    {
    	 $$ = $1;
    }
  ;

joined_table:
  /* we do not support cross join and natural join
    * using clause is not supported either*/
   
    '(' joined_table ')'
    {
    	$$ = $2;
    }
  | table_factor join_type JOIN table_factor ON expr
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, $2, $1, $4, $6);*/
     rapidjson::Value  *node ;
     malloc_terminal_node(node,result->Doc.GetAllocator(), T_JOIN_CONDITION);
     SafeAddMember(node,"JOIN_CONDITION",$6, result->Doc.GetAllocator());
     malloc_non_terminal_node_with_type(&$$,result->Doc.GetAllocator(), "JOIN_TYPE",(*$2)["JOIN_TYPE"].GetString(), T_JOINED_TABLE, $1, $4, node);

    }
  | table_factor JOIN table_factor ON expr
    {
     /* ParseNode* node = NULL;*/
     /* malloc_terminal_node(node, result->malloc_pool_, T_JOIN_INNER);*/
    /*	malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, node, $1, $3, $5);*/
    rapidjson::Value  *node ;
    malloc_terminal_node(node,result->Doc.GetAllocator(), T_JOIN_INNER);
     	rapidjson::Value  *node2 ;
     	malloc_terminal_node(node2,result->Doc.GetAllocator(), T_JOIN_CONDITION);
     	SafeAddMember(node2,"JOIN_CONDITION",$5, result->Doc.GetAllocator());
    malloc_non_terminal_node_with_type(&$$,result->Doc.GetAllocator(), "JOIN_TYPE","INNER_JOIN" ,T_JOINED_TABLE,  node, $1, $3, node2);
    }
  ;

join_type:
    FULL join_outer
    {
      /* make bison mute*/
      (void)($2);
      /*malloc_terminal_node($$, result->malloc_pool_, T_JOIN_FULL);*/
     malloc_terminal_node($$,result->Doc.GetAllocator(), T_JOIN_FULL);
     $$->AddMember("JOIN_TYPE","FULL_JOIN", result->Doc.GetAllocator());    	

    }
  | LEFT join_outer
    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_LEFT);*/
       (void)($2);
       malloc_terminal_node($$,result->Doc.GetAllocator(), T_JOIN_LEFT);
  	 	 $$->AddMember("JOIN_TYPE","LEFT_JOIN", result->Doc.GetAllocator());
    }
  | RIGHT join_outer
    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_RIGHT);*/
       (void)($2);
       malloc_terminal_node($$,result->Doc.GetAllocator(), T_JOIN_RIGHT);
       $$->AddMember("JOIN_TYPE","RIGHT_JOIN", result->Doc.GetAllocator());
    }
  | INNER
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_JOIN_INNER);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_JOIN_INNER);
      $$->AddMember("JOIN_TYPE","INNER_JOIN", result->Doc.GetAllocator());

    }
  ;

join_outer:
    OUTER                    { $$ = NULL; }
  ;
  
/*****************************************************************************
 *
 *	explain grammar
 *
 *****************************************************************************/
explain_stmt:
    EXPLAIN opt_verbose explainable_stmt
    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_EXPLAIN, 1, $3);
      $$->value_ = ($2 ? 1 : 0); positive: verbose */
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_EXPLAIN);
      $$->AddMember("OPERATION_NAME","EXPLAIN", result->Doc.GetAllocator() );
      $$->AddMember("STMT",*$3,result->Doc.GetAllocator());
      //rapidjson::Value tmp($2 ? 1 : 0);
      //(*$$)["value_"].Swap(tmp);
 
    }
  ;

explainable_stmt:
    select_stmt         { $$ = $1; }
  | delete_stmt         { $$ = $1; }
  | insert_stmt         { $$ = $1; }
  | update_stmt         { $$ = $1; }
  ;

opt_verbose:
    VERBOSE             { $$ = (rapidjson::Value*)1; }
  | /*EMPTY*/           { $$ = NULL; }
  ;
  
  
/*****************************************************************************
 *
 *	show grammar
 *
 *****************************************************************************/
show_stmt:
    SHOW TABLES opt_show_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLES, 1, $3malloc_*/ 
    	malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_TABLES, $3);
    	$$->AddMember("OPERATION_NAME","COMMAND", result->Doc.GetAllocator() );
    	}
  | SHOW COLUMNS FROM relation_factor opt_show_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
    	  malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_COLUMNS, $4,$5);
    	}
    
  | SHOW COLUMNS IN relation_factor opt_show_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_COLUMNS, $4,$5);
	
    	}
  | SHOW TABLE STATUS opt_show_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLE_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, $4);

    	
    	}
  | SHOW SERVER STATUS opt_show_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_SERVER_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, $4);
	
    	}
  | SHOW opt_scope VARIABLES opt_show_condition
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_VARIABLES, 1, $4);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_VARIABLES, $4);
      //$$->value_ = $2;
       rapidjson::Value tmp($2);
      (*$$)["value_"].Swap(tmp);
    }
  | SHOW SCHEMA
    { /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_SCHEMA);*/ 
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_SHOW_SCHEMA);	
    	}
  | SHOW CREATE TABLE relation_factor
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_CREATE_TABLE, 1, $4);*/ 
   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_CREATE_TABLE,$4);		
    	}
  | DESCRIBE relation_factor opt_like_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/ 
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_COLUMNS,$2,$3);			
    	}
  | DESC relation_factor opt_like_condition
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_COLUMNS,$2,$3);			
	
    	 }
  | SHOW WARNINGS opt_limit
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_WARNINGS, 1, $3);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SHOW_WARNINGS,$3);			
 
    }
  | SHOW func_expr WARNINGS
    {
      /*
      if ($2->type_ != T_FUN_COUNT)
      {
        yyerror(&@1, result, "Only COUNT(*) function is supported in SHOW WARNINGS statement!"
        YYABORT;
      }
      else
      {
        $$->value_ = 1;
      }*/
      if ((*$2)["type_"].GetInt()!= T_FUN_COUNT)
      {
        yyerror(&@1, result, "Only COUNT(*) function is supported in SHOW WARNINGS statement!");
        YYABORT;  
      }
       else
      {
      	rapidjson::Value tmp(1);
        (*$$)["value_"].Swap(tmp);
      }
    }
  | SHOW GRANTS opt_for_grant_user
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_GRANTS, 1, $3);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_SHOW_GRANTS,$3);
    }
  | SHOW PARAMETERS opt_show_condition
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_PARAMETERS, 1, $3*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_SHOW_PARAMETERS,$3);
  
    }
  | SHOW opt_full PROCESSLIST
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_PROCESSLIST*/
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_SHOW_PROCESSLIST);
      /*$$->value_ = $2;*/
       
       rapidjson::Value tmp($2);
      (*$$)["value_"].Swap(tmp);
      }
    ;

opt_limit:
    LIMIT INTNUM ',' INTNUM
    {
      /*if ($2->value_ < 0 || $4->value_ < 0)
      {
        yyerror(&@1, result, "OFFSET/COUNT must not be less than 0!"
        YYABORT;
      }
      malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, $2, $4malloc_*/
      if ((*$2)["value_"].GetInt()< 0 || (*$4)["value_"].GetInt() < 0)
      {
        yyerror(&@1, result, "OFFSET/COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_SHOW_LIMIT,  $2, $4);
    }
  | LIMIT INTNUM
    {
       /*if ($2->value_ < 0)
      {
        yyerror(&@1, result, "COUNT must not be less than 0!");
        YYABORT;
      }
     malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, NULL, $2);*/
     if ((*$2)["value_"].GetInt()< 0 )
     	{
     		yyerror(&@1, result, "COUNT must not be less than 0!");
        YYABORT;
     	}
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_SHOW_LIMIT,  NULL, $2);
 
    }
  | /* EMPTY */
    { $$ = NULL; }
  ;

opt_for_grant_user:
    opt_for_user
    { $$ = $1; }
  | FOR CURRENT_USER
    { $$ = NULL; }
  | FOR CURRENT_USER '(' ')'
    { $$ = NULL; }
  ;

opt_scope:
    GLOBAL      { $$ = 1; }
  | SESSION     { $$ = 0; }
  | /* EMPTY */ { $$ = 0; }
  ;

opt_show_condition:
    /* EMPTY */
    { $$ = NULL; }
  | LIKE STRING
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $2);*/ 
        malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_LIKE, $2);
	
    	}
  | WHERE expr
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 1, $2);*/
     malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_WHERE_CLAUSE, $2);
	
    }
  ;

opt_like_condition:
    /* EMPTY */
    { $$ = NULL; }
  | STRING
    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $1);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_LIKE, $1);
	
    }
  ;
opt_full:
    /* EMPTY */
    { $$ = 0; }
  | FULL
    { $$ = 1; }
  ;
  
  ;
/*****************************************************************************
 *
 *	create user grammar
 *
 *****************************************************************************/
create_user_stmt:
    CREATE USER user_specification_list
    {
       /* merge_nodes($$, result->malloc_pool_, T_CREATE_USER, $3);*/
      // merge_nodes($$,result->Doc.GetAllocator(),T_CREATE_USER, $3);
      printf("AAAAAAAAAAAAA\n");
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_CREATE_USER,$3);
      $$->AddMember("OPERATION_NAME","CREATE_USER", result->Doc.GetAllocator() );
    }|
    CREATE USER user
    {
    	 printf("CREATE USER\n");
    	
    }
;
user_specification_list:
    user_specification
    {
        $$ = $1;
    }
    | user_specification_list ',' user_specification
    {
       /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
       //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
       malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    }
;
user_specification:
    user IDENTIFIED BY password
    {
      /*  malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_USER_SPEC, 2, $1, $4);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_CREATE_USER_SPEC);
      $$->AddMember("USER_NAME",*$1, result->Doc.GetAllocator() );
      $$->AddMember("PASSWORD", *$4, result->Doc.GetAllocator() );
     
    }
;
user:
    STRING
    {
        $$ = $1;
     // malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
     // SafeAddMember($$,"USER_NAME",$1, result->Doc.GetAllocator());
    }
;
password:
    STRING
    {
        $$ = $1;
    }
;

/*****************************************************************************
 *
 *	drop user grammar
 *
 *****************************************************************************/
drop_user_stmt:
    DROP USER user_list
    {
       /* merge_nodes($$, result->malloc_pool_, T_DROP_USER, $3);*/
        merge_nodes($$,result->Doc.GetAllocator(),T_DROP_USER, $3);
				$$->AddMember("OPERATION_NAME","DROP_USER", result->Doc.GetAllocator() );

    }
;
user_list:
    user
    {
      $$ = $1;
    }
    | user_list ',' user
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
;

/*****************************************************************************
 *
 *	set password grammar
 *
 *****************************************************************************/
set_password_stmt:
    SET PASSWORD opt_for_user COMP_EQ password
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $5);*/
    malloc_terminal_node($$,result->Doc.GetAllocator(),T_SET_PASSWORD);
    $$->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
    $$->AddMember("USER_NAME",*$3, result->Doc.GetAllocator() );
    $$->AddMember("PASSWORD",*$5, result->Doc.GetAllocator() );



    }
    | ALTER USER user IDENTIFIED BY password
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $6);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_SET_PASSWORD);
      $$->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
      $$->AddMember("USER_NAME",*$3, result->Doc.GetAllocator() );
      $$->AddMember("PASSWORD",*$6, result->Doc.GetAllocator() );
      
      

    }
;
opt_for_user:
    FOR user
    {
      $$ = $2;
    }
    | /**/
    {
      $$ = NULL;
    }
;
/*****************************************************************************
 *
 *	rename user grammar
 *
 *****************************************************************************/
rename_user_stmt:
    RENAME USER rename_list
    {
      /*merge_nodes($$, result->malloc_pool_, T_RENAME_USER, $3);*/
     // merge_nodes($$,result->Doc.GetAllocator(),T_RENAME_USER, $3);
      
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_RENAME_USER,$3);
      $$->AddMember("OPERATION_NAME","RENAME_USER", result->Doc.GetAllocator() );

    }
;
rename_info:
    user TO user
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_RENAME_INFO, 2, $1, $3);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_RENAME_INFO);
      $$->AddMember("OLD_NAME",*$1, result->Doc.GetAllocator() );
      $$->AddMember("NEW_NAME",*$3, result->Doc.GetAllocator() );
  
    }
;
rename_list:
    rename_info
    {
      $$ = $1;
    }
    | rename_list ',' rename_info
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
;
/*****************************************************************************
 *
 *	lock user grammar
 *
 *****************************************************************************/
lock_user_stmt:
    ALTER USER user lock_spec
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LOCK_USER, 2, $3, $4);*/
   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LOCK_USER,$3 ,$4);
    }
;
lock_spec:
    LOCKED
    {
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(1);
      (*$$)["value_"].Swap(tmp);
    }
    | UNLOCKED
    {
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(0);
      (*$$)["value_"].Swap(tmp);
    }
;
/*****************************************************************************
*
*  begin/start transaction grammer
*
******************************************************************************/

opt_work:
    WORK
    {
      (void)$$;
    }
    | /*empty*/
    {
    }
opt_with_consistent_snapshot:
    WITH CONSISTENT SNAPSHOT
    {
      $$ = 1;
    }
    |/*empty*/
    {
      $$ = 0;
    }
begin_stmt:
    BEGI opt_work
    {
      (void)$2;
      /*malloc_terminal_node($$, result->malloc_pool_, T_BEGIN);
      $$->value_ = 0;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_BEGIN);
      rapidjson::Value tmp(0);
      (*$$)["value_"].Swap(tmp);
    }
    | START TRANSACTION opt_with_consistent_snapshot
    {
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_BEGIN);
       
       rapidjson::Value tmp($3);
      (*$$)["value_"].Swap(tmp);
    }
/*****************************************************************************
*
*  commit grammer
*
******************************************************************************/
commit_stmt:
    COMMIT opt_work
    {
      (void)$2;
      /*malloc_terminal_node($$, result->malloc_pool_, T_COMMIT);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(), T_COMMIT);
			$$->AddMember("OPERATION_NAME","COMMIT", result->Doc.GetAllocator() );

    }

/*****************************************************************************
*
*  rollback grammer
*
******************************************************************************/
rollback_stmt:
    ROLLBACK opt_work
    {
      (void)$2;
      /*malloc_terminal_node($$, result->malloc_pool_, T_ROLLBACK);*/
       malloc_terminal_node($$,result->Doc.GetAllocator(), T_ROLLBACK);
			 $$->AddMember("OPERATION_NAME","ROLLBACK", result->Doc.GetAllocator() );

    }

/*****************************************************************************
*
*  kill grammer
*
******************************************************************************/
kill_stmt:
    KILL opt_is_global opt_flag INTNUM
    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_KILL, 3, $2, $3, $4);*/
    malloc_terminal_node($$,result->Doc.GetAllocator(), T_KILL );
    $$->AddMember("OPERATION_NAME","KILL", result->Doc.GetAllocator() );
    $$->AddMember("IS_GLOBAL",*$2, result->Doc.GetAllocator() );
    $$->AddMember("OPT_FLAG",*$3, result->Doc.GetAllocator() );
    $$->AddMember("INTNUM",*$4, result->Doc.GetAllocator() );



    }
   ;
opt_is_global:
    /*EMPTY*/
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
    }
    | GLOBAL
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
       $$->value_ = 1;*/
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
       (*$$)["value_"] = rapidjson::Value(-1);
    }
  ;
opt_flag:
    /*EMPTY*/
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
      
    }
    | QUERY
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
       malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
       rapidjson::Value tmp(1);
       (*$$)["value_"].Swap(tmp);
    }
    | CONNECTION
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_BOOL);
     
    }
  ;


/*****************************************************************************
 *
 *	grant grammar
 *
 *****************************************************************************/
grant_stmt:
    GRANT priv_type_list ON priv_level TO user_list
    {
      /*ParseNode *privileges_node = NULL;
      ParseNode *users_node = NULL;
      merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, $2);
      merge_nodes(users_node, result->malloc_pool_, T_USERS, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_GRANT,
                                 3, privileges_node, $4, users_node);*/
      //rapidjson::Value  *privileges_node ; 
      //merge_nodes(privileges_node,result->Doc.GetAllocator(),T_PRIVILEGES,$2);
      //rapidjson::Value  *users_node      ; 
      //merge_nodes(users_node,result->Doc.GetAllocator(),T_USERS,$6);
      
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_GRANT );
			$$->AddMember("OPERATION_NAME","GRANT", result->Doc.GetAllocator() );
    	$$->AddMember("PRIV_LEVEL",*$4, result->Doc.GetAllocator() );
    	$$->AddMember("PRIV_TYPE", *$2, result->Doc.GetAllocator() );
    	$$->AddMember("USER_NODE", *$6, result->Doc.GetAllocator() );
    }
;
priv_type_list:
    priv_type
    {
      $$ = $1;
    }
    | priv_type_list ',' priv_type
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
      malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    }
;
priv_type:
    ALL opt_privilege
    {
      (void)$2;                 /* useless */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALL;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALL);
      (*$$)["value_"].Swap(tmp);
    }
    | ALTER
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALTER;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALTER);
      (*$$)["value_"].Swap(tmp);
    }
    | CREATE
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE);
      (*$$)["value_"].Swap(tmp);
    }
    | CREATE USER
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE_USER;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE_USER);
      (*$$)["value_"].Swap(tmp);
    }
    | DELETE
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DELETE;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DELETE);
      (*$$)["value_"].Swap(tmp);
    }
    | DROP
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DROP;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DROP);
      (*$$)["value_"].Swap(tmp);
    }
    | GRANT OPTION
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_GRANT_OPTION;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_GRANT_OPTION);
      (*$$)["value_"].Swap(tmp);
    }
    | INSERT
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_INSERT;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_INSERT);
      (*$$)["value_"].Swap(tmp );
    }
    | UPDATE
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_UPDATE;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_UPDATE);
      (*$$)["value_"].Swap(tmp);
    }
    | SELECT
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_SELECT;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_SELECT);
      (*$$)["value_"].Swap(tmp);
    }
    | REPLACE
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_REPLACE;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_REPLACE);
      (*$$)["value_"].Swap(tmp);
    }
;
opt_privilege:
    PRIVILEGES
    {
      (void)$$;
    }
    | /*empty*/
    {
      (void)$$;
    }
;
priv_level:
    '*'
    {
      /* means global priv_level */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_PRIV_LEVEL);
     
    }
    | relation_name
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL, 1, $1);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_PRIV_LEVEL,$1);

    }
;
/*****************************************************************************
 *
 *	revoke grammar
 *
 *****************************************************************************/
revoke_stmt:
    REVOKE priv_type_list opt_on_priv_level FROM user_list
    {
      /*ParseNode *privileges_node = NULL;
      ParseNode *priv_level = NULL;
      merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, $2);
      if ($3 == NULL)
      {
        // check privileges: should have and only have ALL PRIVILEGES, GRANT OPTION 
        int check_ok = 0;
        if (2 == privileges_node->num_child_)
        {
          assert(privileges_node->children_[0]->num_child_ == 0);
          assert(privileges_node->children_[0]->type_ == T_PRIV_TYPE);
          assert(privileges_node->children_[1]->num_child_ == 0);
          assert(privileges_node->children_[1]->type_ == T_PRIV_TYPE);
          if ((privileges_node->children_[0]->value_ == OB_PRIV_ALL
               && privileges_node->children_[1]->value_ == OB_PRIV_GRANT_OPTION)
              || (privileges_node->children_[1]->value_ == OB_PRIV_ALL
                  && privileges_node->children_[0]->value_ == OB_PRIV_GRANT_OPTION))
          {
            check_ok = 1;
          }
        }
        if (!check_ok)
        {
          yyerror(&@1, result, "support only ALL PRIVILEGES, GRANT OPTION");
          YYABORT;
        }
      }
      else
      {
        priv_level = $3;
      }
      ParseNode *users_node = NULL;
      merge_nodes(users_node, result->malloc_pool_, T_USERS, $5);
      malloc_non_terminal_node($$, result->malloc_pool_, T_REVOKE,
                                 3, privileges_node, priv_level, users_node);*/
    }
;
opt_on_priv_level:
    ON priv_level
    {
      $$ = $2;
    }
    | /*empty*/
    {
      $$ = NULL;
    }

/*****************************************************************************
 *
 *	prepare grammar
 *
 *****************************************************************************/
prepare_stmt:
    /* PREPARE stmt_name FROM '"' preparable_stmt '"' */
    PREPARE stmt_name FROM preparable_stmt
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PREPARE, 2, $2, $4);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_PREPARE, $2, $4);
    }
  ;

stmt_name:
    column_label
    { $$ = $1; }
  ;

preparable_stmt:
    select_stmt
    { $$ = $1; }
  | insert_stmt
    { $$ = $1; }
  | update_stmt
    { $$ = $1; }
  | delete_stmt
    { $$ = $1; }
  ;


/*****************************************************************************
 *
 *	set grammar
 *
 *****************************************************************************/
variable_set_stmt:
    SET var_and_val_list
    {
     /* merge_nodes($$, result->malloc_pool_, T_VARIABLE_SET, $2);
      $$->value_ = 2;*/
      merge_nodes($$,result->Doc.GetAllocator(),T_VARIABLE_SET, $2);
      rapidjson::Value tmp(2);
      (*$$)["value_"].Swap(tmp);
    }
  ;

var_and_val_list:
    var_and_val
    {
      $$ = $1;
    }
  | var_and_val_list ',' var_and_val
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  ;

var_and_val:
    TEMP_VARIABLE to_or_eq expr
    {
      (void)($2);
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL, $1, $3);
       rapidjson::Value tmp(2);
       (*$$)["value_"].Swap(tmp);

    }
  | column_name to_or_eq expr
    {
      (void)($2);
       /*$1->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
    //(*$1)["type_"].Swap(tmp);
    $1->AddMember("type_", tmp,result->Doc.GetAllocator());
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL, $1, $3);
    }
  | GLOBAL column_name to_or_eq expr
    {
      (void)($3);
     /* $2->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $2, $4);
      $$->value_ = 1;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
    //(*$2)["type_"].Swap(tmp);
    $2->AddMember("type_", tmp,result->Doc.GetAllocator());
    malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL, $2, $4);

    }
  | SESSION column_name to_or_eq expr
    {
      (void)($3);
     /*  $2->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $2, $4);
      $$->value_ = 2;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
      //(*$2)["type_"].Swap(tmp);
      $2->AddMember("type_", tmp,result->Doc.GetAllocator());

      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL,$2, $4);
      rapidjson::Value tmp1(2);
      (*$$)["value_"].Swap(tmp1);
    }
  | GLOBAL_ALIAS '.' column_name to_or_eq expr
    {
      (void)($4);
      /*$3->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $3, $5);
      $$->value_ = 1;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
      //(*$3)["type_"].Swap(tmp);
      $3->AddMember("type_", tmp,result->Doc.GetAllocator());
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL,$3, $5);
      rapidjson::Value tmp1(1);
      (*$3)["value_"].Swap(tmp1);
    }
  | SESSION_ALIAS '.' column_name to_or_eq expr
    {
      (void)($4);
      /*$3->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $3, $5);
      $$->value_ = 2;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
      //(*$3)["type_"].Swap(tmp);
      $3->AddMember("type_", tmp,result->Doc.GetAllocator());

      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL,$3, $5);
      rapidjson::Value tmp1(2);
      (*$$)["value_"].Swap(tmp1);
    }
  | SYSTEM_VARIABLE to_or_eq expr
    {
      (void)($2);
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
       $$->value_ = 2;*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_VAR_VAL,$1, $3);
       rapidjson::Value tmp(2);
       (*$$)["value_"].Swap(tmp);
    }
  ;

to_or_eq:
    TO      { $$ = NULL; }
  | COMP_EQ { $$ = NULL; }
  ;

argument:
    TEMP_VARIABLE
    { $$ = $1; }
  ;


/*****************************************************************************
 *
 *	execute grammar
 *
 *****************************************************************************/
execute_stmt:
    EXECUTE stmt_name opt_using_args
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXECUTE, 2, $2, $3);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_EXECUTE,$2, $3);

    }
  ;

opt_using_args:
    USING argument_list
    {
     /* merge_nodes($$, result->malloc_pool_, T_ARGUMENT_LIST, $2);*/
      merge_nodes($$,result->Doc.GetAllocator(),T_ARGUMENT_LIST,$2);

    }
    | /*empty*/
    {
      $$ = NULL;
    }

argument_list:
    argument
    {
      $$ = $1;
    }
  | argument_list ',' argument
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  ;


/*****************************************************************************
 *
 *	DEALLOCATE grammar
 *
 *****************************************************************************/
deallocate_prepare_stmt:
    deallocate_or_drop PREPARE stmt_name
    {
      (void)($1);
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DEALLOCATE, 1, $3);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_DEALLOCATE,$3);
    }
  ;

deallocate_or_drop:
    DEALLOCATE
    { $$ = NULL; }
  | DROP
    { $$ = NULL; }
  ;


/*****************************************************************************
 *
 *	ALTER TABLE grammar
 *
 *****************************************************************************/
alter_table_stmt:
     ALTER TABLE relation_factor alter_column_actions
    {
      /*ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, alter_actions);*/
      
      rapidjson::Value *alter_actions ;
      merge_nodes(alter_actions,result->Doc.GetAllocator(),T_ALTER_ACTION_LIST, $4);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_ALTER_TABLE,$3, alter_actions);
    }
  | ALTER TABLE relation_factor RENAME TO relation_factor
    {
      yyerror(&@1, result, "Table rename is not supported now");
      YYABORT;
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_TABLE_RENAME, 1, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_ACTION_LIST, 1, $$);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, $$);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_TABLE_RENAME, $6);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_ALTER_TABLE, $3, $$);
    }
  ;

alter_column_actions:
    alter_column_action
    {
      $$ = $1;
    }
  | alter_column_actions ',' alter_column_action
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);
    }
  ;

alter_column_action:
    ADD opt_column column_definition
    {
      (void)($2); /* make bison mute */
      $$ = $3; /* T_COLUMN_DEFINITION */
    }
  | DROP opt_column column_name opt_drop_behavior
    {
      (void)($2); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DROP, 1, $3);
      $$->value_ = $4;*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_COLUMN_DROP, $3);
       rapidjson::Value tmp($4);
      (*$$)["value_"].Swap(tmp);
    }
  | ALTER opt_column column_name alter_column_behavior
    {
      (void)($2); /* make bison mute */
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_ALTER, 2, $3, $4);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_COLUMN_ALTER, $3, $4);

    }
  | RENAME opt_column column_name TO column_label
    {
      (void)($2); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_RENAME, 2, $3, $5);*/
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_COLUMN_RENAME, $3, $5);

    }
  /* we don't have table constraint, so ignore it */
  ;

opt_column:
    COLUMN          { $$ = NULL; }
  | /*EMPTY*/       { $$ = NULL; }
  ;

opt_drop_behavior:
    CASCADE         { $$ = 2; }
  | RESTRICT        { $$ = 1; }
  | /*EMPTY*/       { $$ = 0; }
  ;

alter_column_behavior:
    SET NOT NULLX
    {
      (void)($3); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_CONSTR_NOT_NULL);
    }
  | DROP NOT NULLX
    {
      (void)($3); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_CONSTR_NULL);
    }
  | SET DEFAULT expr_const
    {
       /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $3);*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CONSTR_DEFAULT,$3);
       
    }
  | DROP DEFAULT
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_NULL);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $$);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_NULL);
      malloc_non_terminal_node (&$$,result->Doc.GetAllocator(),T_CONSTR_DEFAULT, node);
    }
  ;


/*****************************************************************************
 *
 *	ALTER SYSTEM grammar
 *
 *****************************************************************************/
alter_system_stmt:
    ALTER SYSTEM SET alter_system_actions
    {
      /*merge_nodes($$, result->malloc_pool_, T_SYTEM_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_SYSTEM, 1, $$);*/
      merge_nodes($$,result->Doc.GetAllocator(),T_SYTEM_ACTION_LIST, $4);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_ALTER_SYSTEM,$$);
    }
    |
    ALTER SYSTEM opt_force CHANGE_OBI MASTER COMP_EQ STRING
    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CHANGE_OBI, node, $7, $3);
    }
    |
    ALTER SYSTEM opt_force SWITCH_CLUSTER MASTER COMP_EQ STRING
    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CHANGE_OBI, node, $7, $3);
      
    }
    |
    ALTER SYSTEM SET_MASTER_CLUSTER MASTER COMP_EQ STRING
    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CHANGE_OBI, node, $6);
 
    }
    |
    ALTER SYSTEM SET_SLAVE_CLUSTER SLAVE COMP_EQ STRING
    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_SLAVE);
      malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CHANGE_OBI, node, $6);

    }
  ;

opt_force:
    /*EMPTY*/
    {
      $$ = NULL;
    }
  | FORCE
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_FORCE);*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_FORCE);
    }
    ;


alter_system_actions:
    alter_system_action
    {
      $$ = $1;
    }
  | alter_system_actions ',' alter_system_action
    {
     /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&$$,result->Doc.GetAllocator(),2, $1, $3);

    }
  ;

alter_system_action:
    column_name COMP_EQ expr_const opt_comment opt_config_scope
    SERVER_TYPE COMP_EQ server_type opt_cluster_or_address
    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SYSTEM_ACTION, 5,
                               $1,    /* param_name 
                               $3,    /* param_value 
                               $4,    /* comment 
                               $8,    /* server type 
                               $9     /* cluster or IP/port 
                               );
      $$->value_ = $5;                 scope */
      SafeAddMember($$,"param_name",$1,result->Doc.GetAllocator());
      SafeAddMember($$,"param_value",$3,result->Doc.GetAllocator());
      SafeAddMember($$,"comment",$4,result->Doc.GetAllocator());
			SafeAddMember($$,"server_type",$8,result->Doc.GetAllocator());
			SafeAddMember($$,"cluster",$9,result->Doc.GetAllocator());
			 rapidjson::Value tmp($5);
			(*$$)["value_"].Swap(tmp);
    }
  ;

opt_comment:
    COMMENT STRING
    { $$ = $2; }
  | /* EMPTY */
    { $$ = NULL; }
  ;

opt_config_scope:
    SCOPE COMP_EQ MEMORY
    { $$ = 0; }   /* same as ObConfigType */
  | SCOPE COMP_EQ SPFILE
    { $$ = 1; }   /* same as ObConfigType */
  | SCOPE COMP_EQ BOTH
    { $$ = 2; }   /* same as ObConfigType */
  | /* EMPTY */
    { $$ = 2; }   /* same as ObConfigType */
  ;

server_type:
    ROOTSERVER
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 1;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*$$)["value_"].Swap(tmp);
    }
  | UPDATESERVER
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 4;*/
     malloc_terminal_node($$,result->Doc.GetAllocator(),T_INT);
     rapidjson::Value tmp(4);
     (*$$)["value_"].Swap( tmp); 
    }
  | CHUNKSERVER
    {
     /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 2;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*$$)["value_"].Swap(tmp); 
    }
  | MERGESERVER
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 3;*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(3);
      (*$$)["value_"].Swap(tmp); 
    }
  ;

opt_cluster_or_address:
    CLUSTER COMP_EQ INTNUM
    {
     /* malloc_non_terminal_node($$ , result->malloc_pool_, T_CLUSTER, 1, $3);*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_CLUSTER,$3);
    }
  | SERVER_IP COMP_EQ STRING SERVER_PORT COMP_EQ INTNUM
    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SERVER_ADDRESS, 2, $3, $6);*/
       malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_SERVER_ADDRESS,$3, $6);
    }
  | /* EMPTY */
    { $$ = NULL; }
  ;


/*===========================================================
 *
 *	Name classification
 *
 *===========================================================*/

column_name:
    NAME
    { $$ = $1; }
  | unreserved_keyword
    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
      $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
      if ($$->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }
      else
      {
        $$->value_ = strlen($$->str_value_);
      }*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_IDENT);
      if($1)$$->AddMember("str_value_",rapidjson::StringRef($1->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*$$)["str_value_"].GetString()));
      (*$$)["value_"].Swap(tmp);
    }
  ;

relation_name:
    NAME
    { $$ = $1; }
  | unreserved_keyword
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_IDENT);

      $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
      if ($$->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }
      else
      {
        $$->value_ = strlen($$->str_value_);
      }*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_IDENT);
      if($1)$$->AddMember("str_value_",rapidjson::StringRef($1->keyword_name),result->Doc.GetAllocator());
			rapidjson::Value tmp(strlen((*$$)["str_value_"].GetString()));
      (*$$)["value_"].Swap(tmp);

    }
  ;

function_name:
    NAME
    { $$ = $1; }
  ;

column_label:
    NAME
    { $$ = $1; }
  | unreserved_keyword
    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
      $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
      if ($$->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }*/
      malloc_terminal_node($$,result->Doc.GetAllocator(),T_IDENT);
      if($1)$$->AddMember("str_value_",rapidjson::StringRef($1->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*$$)["str_value_"].GetString()));
      (*$$)["value_"].Swap(tmp);

    }
  ;  
  
  

unreserved_keyword:
    AUTO_INCREMENT
  | CHUNKSERVER
  | COMPRESS_METHOD
  | CONSISTENT_MODE
  | EXPIRE_INFO
  | GRANTS
  | JOIN_INFO
  | MERGESERVER
  | REPLICA_NUM
  | ROOTSERVER
  | ROW_COUNT
  | SERVER
  | SERVER_IP
  | SERVER_PORT
  | SERVER_TYPE
  | STATUS
  | TABLET_BLOCK_SIZE
  | TABLE_ID
  | TABLET_MAX_SIZE
  | UNLOCKED
  | UPDATESERVER
  | USE_BLOOM_FILTER
  | VARIABLES
  | VERBOSE
  | WARNINGS
  ;
  
  
  
%%
void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s, ...)
{
  if (p != NULL)
  {
    p->result_tree_ = 0;
    va_list ap;
    va_start(ap, s);
    vsnprintf(p->error_msg_, MAX_ERROR_MSG, s, ap);
    if (yylloc != NULL)
    {
      if (p->input_sql_[yylloc->first_column - 1] != '\'')
        p->start_col_ = yylloc->first_column;
      p->end_col_ = yylloc->last_column;
      p->line_ = yylloc->first_line;
    }
  }
}
void yyerror(YYLTYPE* yylloc, ParseResult* p,const char* s, ...)
{
  if (p != NULL)
  {
    p->result_tree_ = 0;
    va_list ap;
    va_start(ap, s);
    vsnprintf(p->error_msg_, MAX_ERROR_MSG, s, ap);
    if (yylloc != NULL)
    {
      if (p->input_sql_[yylloc->first_column - 1] != '\'')
        p->start_col_ = yylloc->first_column;
      p->end_col_ = yylloc->last_column;
      p->line_ = yylloc->first_line;
    }
  }
}

void yyerror(YYLTYPE* yylloc, ParseResult* p,yyscan_t scanner,const char* s,...)
{
  if (p != NULL)
  {
    p->result_tree_ = 0;
    va_list ap;
    va_start(ap, s);
    vsnprintf(p->error_msg_, MAX_ERROR_MSG, s, ap);
    if (yylloc != NULL)
    {
      if (p->input_sql_[yylloc->first_column - 1] != '\'')
        p->start_col_ = yylloc->first_column;
      p->end_col_ = yylloc->last_column;
      p->line_ = yylloc->first_line;
    }
  }
}

int parse_init(ParseResult* p)
{
  int ret = 0;  // can not include C++ file "ob_define.h"
  if (!p )
  {
    ret = -1;
    if (p)
    {
      snprintf(p->error_msg_, MAX_ERROR_MSG, "malloc_pool_ must be set");
    }
  }
  if (ret == 0)
  {
    ret = yylex_init_extra(p, &(p->yyscan_info_));
  }
  return ret;
}

int parse_terminate(ParseResult* p)
{
  return yylex_destroy(p->yyscan_info_);
}

int parse_sql(ParseResult* p, const char* buf, size_t len)
{
  int ret = -1;
  p->result_tree_ = 0;
  p->error_msg_[0] = 0;
  p->input_sql_ = buf;
  p->input_sql_len_ = len;
  p->start_col_ = 1;
  p->end_col_ = 1;
  p->line_ = 1;
  p->yycolumn_ = 1;
  p->yylineno_ = 1;
  p->tmp_literal_ = NULL;

  if (buf == NULL || len <= 0)
  {
    snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be empty");
    return ret;
  }

  while(len > 0 && isspace(buf[len - 1]))
    --len;

  if (len <= 0)
  {
    snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be while space only");
    return ret;
  }

  YY_BUFFER_STATE bp;

  //bp = yy_scan_string(buf, p->yyscan_info_);
  bp = yy_scan_bytes(buf, len, p->yyscan_info_);
  yy_switch_to_buffer(bp, p->yyscan_info_);
  ret = yyparse(p,p->yyscan_info_);
  yy_delete_buffer(bp, p->yyscan_info_);
  return ret;
}


