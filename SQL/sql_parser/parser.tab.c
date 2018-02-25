/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

  
#include <stdint.h>
#include "parser.hh"

#define YYDEBUG 1


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





# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    STRING = 259,
    INTNUM = 260,
    DATE_VALUE = 261,
    HINT_VALUE = 262,
    BOOL = 263,
    APPROXNUM = 264,
    NULLX = 265,
    UNKNOWN = 266,
    QUESTIONMARK = 267,
    SYSTEM_VARIABLE = 268,
    TEMP_VARIABLE = 269,
    UNION = 270,
    EXCEPT = 271,
    INTERSECT = 272,
    OR = 273,
    AND = 274,
    NOT = 275,
    COMP_LE = 276,
    COMP_LT = 277,
    COMP_EQ = 278,
    COMP_GT = 279,
    COMP_GE = 280,
    COMP_NE = 281,
    CNNOP = 282,
    LIKE = 283,
    BETWEEN = 284,
    IN = 285,
    IS = 286,
    MOD = 287,
    UMINUS = 288,
    ADD = 289,
    ANY = 290,
    ALL = 291,
    ALTER = 292,
    AS = 293,
    ASC = 294,
    BEGI = 295,
    BIGINT = 296,
    BINARY = 297,
    BOOLEAN = 298,
    BOTH = 299,
    BY = 300,
    CASCADE = 301,
    CASE = 302,
    CHARACTER = 303,
    CLUSTER = 304,
    COMMENT = 305,
    COMMIT = 306,
    CONSISTENT = 307,
    COLUMN = 308,
    COLUMNS = 309,
    CREATE = 310,
    CREATETIME = 311,
    CURRENT_USER = 312,
    CHANGE_OBI = 313,
    SWITCH_CLUSTER = 314,
    DATE = 315,
    DATETIME = 316,
    DEALLOCATE = 317,
    DECIMAL = 318,
    DEFAULT = 319,
    DELETE = 320,
    DESC = 321,
    DESCRIBE = 322,
    DISTINCT = 323,
    DOUBLE = 324,
    DROP = 325,
    DUAL = 326,
    ELSE = 327,
    END = 328,
    END_P = 329,
    ERROR = 330,
    EXECUTE = 331,
    EXISTS = 332,
    EXPLAIN = 333,
    FLOAT = 334,
    FOR = 335,
    FROM = 336,
    FULL = 337,
    FROZEN = 338,
    FORCE = 339,
    GLOBAL = 340,
    GLOBAL_ALIAS = 341,
    GRANT = 342,
    GROUP = 343,
    HAVING = 344,
    HINT_BEGIN = 345,
    HINT_END = 346,
    HOTSPOT = 347,
    IDENTIFIED = 348,
    IF = 349,
    INNER = 350,
    INTEGER = 351,
    INSERT = 352,
    INTO = 353,
    JOIN = 354,
    KEY = 355,
    LEADING = 356,
    LEFT = 357,
    LIMIT = 358,
    LOCAL = 359,
    LOCKED = 360,
    MEDIUMINT = 361,
    MEMORY = 362,
    MODIFYTIME = 363,
    MASTER = 364,
    NUMERIC = 365,
    OFFSET = 366,
    ON = 367,
    ORDER = 368,
    OPTION = 369,
    OUTER = 370,
    PARAMETERS = 371,
    PASSWORD = 372,
    PRECISION = 373,
    PREPARE = 374,
    PRIMARY = 375,
    READ_STATIC = 376,
    REAL = 377,
    RENAME = 378,
    REPLACE = 379,
    RESTRICT = 380,
    PRIVILEGES = 381,
    REVOKE = 382,
    RIGHT = 383,
    ROLLBACK = 384,
    KILL = 385,
    READ_CONSISTENCY = 386,
    SCHEMA = 387,
    SCOPE = 388,
    SELECT = 389,
    SESSION = 390,
    SESSION_ALIAS = 391,
    SET = 392,
    SHOW = 393,
    SMALLINT = 394,
    SNAPSHOT = 395,
    SPFILE = 396,
    START = 397,
    STATIC = 398,
    SYSTEM = 399,
    STRONG = 400,
    SET_MASTER_CLUSTER = 401,
    SET_SLAVE_CLUSTER = 402,
    SLAVE = 403,
    TABLE = 404,
    TABLES = 405,
    THEN = 406,
    TIME = 407,
    TIMESTAMP = 408,
    TINYINT = 409,
    TRAILING = 410,
    TRANSACTION = 411,
    TO = 412,
    UPDATE = 413,
    USER = 414,
    USING = 415,
    VALUES = 416,
    VARCHAR = 417,
    VARBINARY = 418,
    WHERE = 419,
    WHEN = 420,
    WITH = 421,
    WORK = 422,
    PROCESSLIST = 423,
    QUERY = 424,
    CONNECTION = 425,
    WEAK = 426,
    UNIQUE = 427,
    FULLTEXT = 428,
    SPATIAL = 429,
    HASH = 430,
    BTREE = 431,
    INDEX = 432,
    SKIPLIST = 433,
    AUTO_INCREMENT = 434,
    CHUNKSERVER = 435,
    COMPRESS_METHOD = 436,
    CONSISTENT_MODE = 437,
    EXPIRE_INFO = 438,
    GRANTS = 439,
    JOIN_INFO = 440,
    MERGESERVER = 441,
    REPLICA_NUM = 442,
    ROOTSERVER = 443,
    ROW_COUNT = 444,
    SERVER = 445,
    SERVER_IP = 446,
    SERVER_PORT = 447,
    SERVER_TYPE = 448,
    STATUS = 449,
    TABLE_ID = 450,
    TABLET_BLOCK_SIZE = 451,
    TABLET_MAX_SIZE = 452,
    EXTERN_SIZE = 453,
    SKIP_LEVEL = 454,
    UNLOCKED = 455,
    UPDATESERVER = 456,
    USE_BLOOM_FILTER = 457,
    VARIABLES = 458,
    VERBOSE = 459,
    WARNINGS = 460
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (ParseResult* result, yyscan_t scanner);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  166
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2615

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  217
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  159
/* YYNRULES -- Number of rules.  */
#define YYNRULES  506
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  897

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   460

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      40,    41,    34,    32,   216,    33,    42,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   215,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    37,    39,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   621,   621,   634,   645,   654,   655,   656,   657,   658,
     659,   660,   661,   662,   663,   664,   665,   666,   667,   668,
     669,   670,   671,   672,   673,   674,   675,   676,   677,   678,
     679,   680,   689,   693,   703,   709,   719,   733,   734,   735,
     736,   737,   738,   739,   740,   741,   745,   746,   747,   748,
     759,   767,   768,   769,   775,   787,   788,   794,   800,   801,
     802,   803,   804,   805,   806,   810,   811,   816,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   841,   846,   851,   856,   861,   866,
     871,   876,   882,   887,   892,   897,   902,   910,   917,   927,
     938,   939,   943,   945,   955,   963,   964,   969,   987,  1025,
    1109,  1129,  1135,  1163,  1173,  1182,  1183,  1184,  1185,  1189,
    1196,  1209,  1229,  1244,  1248,  1258,  1276,  1291,  1305,  1311,
    1317,  1324,  1331,  1336,  1341,  1347,  1358,  1392,  1398,  1402,
    1406,  1416,  1420,  1433,  1447,  1453,  1459,  1464,  1470,  1476,
    1491,  1504,  1510,  1516,  1522,  1529,  1541,  1547,  1560,  1574,
    1587,  1601,  1606,  1612,  1620,  1635,  1641,  1644,  1648,  1649,
    1653,  1654,  1658,  1659,  1663,  1664,  1668,  1674,  1678,  1684,
    1691,  1696,  1701,  1708,  1712,  1720,  1726,  1733,  1740,  1747,
    1754,  1761,  1768,  1775,  1782,  1789,  1796,  1807,  1817,  1818,
    1829,  1848,  1849,  1856,  1860,  1874,  1901,  1927,  1963,  1964,
    1971,  1981,  1994,  2000,  2004,  2005,  2014,  2019,  2029,  2030,
    2046,  2065,  2076,  2082,  2091,  2095,  2102,  2120,  2156,  2188,
    2224,  2225,  2229,  2268,  2299,  2329,  2363,  2364,  2368,  2376,
    2390,  2406,  2412,  2418,  2437,  2440,  2462,  2466,  2474,  2480,
    2484,  2494,  2500,  2506,  2516,  2523,  2528,  2534,  2538,  2542,
    2546,  2552,  2554,  2560,  2561,  2567,  2568,  2579,  2591,  2603,
    2615,  2627,  2650,  2674,  2702,  2703,  2711,  2712,  2716,  2727,
    2729,  2737,  2747,  2751,  2756,  2765,  2766,  2774,  2777,  2783,
    2792,  2801,  2820,  2838,  2854,  2858,  2882,  2884,  2892,  2899,
    2907,  2915,  2923,  2931,  2935,  2949,  2959,  2963,  2972,  2987,
    2996,  3005,  3014,  3024,  3033,  3047,  3048,  3049,  3050,  3054,
    3055,  3065,  3070,  3075,  3080,  3086,  3091,  3099,  3103,  3107,
    3111,  3116,  3122,  3145,  3150,  3156,  3168,  3183,  3200,  3204,
    3206,  3208,  3213,  3214,  3215,  3220,  3221,  3226,  3235,  3236,
    3244,  3245,  3256,  3263,  3271,  3275,  3283,  3293,  3301,  3313,
    3322,  3327,  3342,  3353,  3366,  3371,  3381,  3392,  3402,  3406,
    3420,  3427,  3433,  3447,  3452,  3455,  3460,  3464,  3473,  3486,
    3501,  3516,  3531,  3536,  3546,  3552,  3560,  3576,  3597,  3602,
    3610,  3621,  3629,  3638,  3646,  3655,  3664,  3673,  3682,  3691,
    3700,  3711,  3717,  3723,  3730,  3745,  3790,  3795,  3806,  3818,
    3823,  3825,  3827,  3829,  3840,  3851,  3855,  3865,  3875,  3888,
    3901,  3915,  3929,  3944,  3958,  3962,  3966,  3977,  3986,  3993,
    3998,  4002,  4018,  4027,  4029,  4040,  4054,  4072,  4076,  4085,
    4090,  4099,  4106,  4117,  4118,  4122,  4123,  4124,  4128,  4134,
    4140,  4146,  4163,  4171,  4181,  4192,  4203,  4217,  4220,  4229,
    4233,  4243,  4265,  4268,  4272,  4274,  4276,  4279,  4283,  4291,
    4299,  4307,  4318,  4323,  4329,  4340,  4342,  4363,  4365,  4388,
    4393,  4395,  4415,  4416,  4417,  4418,  4419,  4420,  4421,  4422,
    4423,  4424,  4425,  4426,  4427,  4428,  4429,  4430,  4431,  4432,
    4433,  4434,  4435,  4436,  4437,  4438,  4439
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "DATE_VALUE",
  "HINT_VALUE", "BOOL", "APPROXNUM", "NULLX", "UNKNOWN", "QUESTIONMARK",
  "SYSTEM_VARIABLE", "TEMP_VARIABLE", "UNION", "EXCEPT", "INTERSECT", "OR",
  "AND", "NOT", "COMP_LE", "COMP_LT", "COMP_EQ", "COMP_GT", "COMP_GE",
  "COMP_NE", "CNNOP", "LIKE", "BETWEEN", "IN", "IS", "'+'", "'-'", "'*'",
  "'/'", "'%'", "MOD", "'^'", "UMINUS", "'('", "')'", "'.'", "ADD", "ANY",
  "ALL", "ALTER", "AS", "ASC", "BEGI", "BIGINT", "BINARY", "BOOLEAN",
  "BOTH", "BY", "CASCADE", "CASE", "CHARACTER", "CLUSTER", "COMMENT",
  "COMMIT", "CONSISTENT", "COLUMN", "COLUMNS", "CREATE", "CREATETIME",
  "CURRENT_USER", "CHANGE_OBI", "SWITCH_CLUSTER", "DATE", "DATETIME",
  "DEALLOCATE", "DECIMAL", "DEFAULT", "DELETE", "DESC", "DESCRIBE",
  "DISTINCT", "DOUBLE", "DROP", "DUAL", "ELSE", "END", "END_P", "ERROR",
  "EXECUTE", "EXISTS", "EXPLAIN", "FLOAT", "FOR", "FROM", "FULL", "FROZEN",
  "FORCE", "GLOBAL", "GLOBAL_ALIAS", "GRANT", "GROUP", "HAVING",
  "HINT_BEGIN", "HINT_END", "HOTSPOT", "IDENTIFIED", "IF", "INNER",
  "INTEGER", "INSERT", "INTO", "JOIN", "KEY", "LEADING", "LEFT", "LIMIT",
  "LOCAL", "LOCKED", "MEDIUMINT", "MEMORY", "MODIFYTIME", "MASTER",
  "NUMERIC", "OFFSET", "ON", "ORDER", "OPTION", "OUTER", "PARAMETERS",
  "PASSWORD", "PRECISION", "PREPARE", "PRIMARY", "READ_STATIC", "REAL",
  "RENAME", "REPLACE", "RESTRICT", "PRIVILEGES", "REVOKE", "RIGHT",
  "ROLLBACK", "KILL", "READ_CONSISTENCY", "SCHEMA", "SCOPE", "SELECT",
  "SESSION", "SESSION_ALIAS", "SET", "SHOW", "SMALLINT", "SNAPSHOT",
  "SPFILE", "START", "STATIC", "SYSTEM", "STRONG", "SET_MASTER_CLUSTER",
  "SET_SLAVE_CLUSTER", "SLAVE", "TABLE", "TABLES", "THEN", "TIME",
  "TIMESTAMP", "TINYINT", "TRAILING", "TRANSACTION", "TO", "UPDATE",
  "USER", "USING", "VALUES", "VARCHAR", "VARBINARY", "WHERE", "WHEN",
  "WITH", "WORK", "PROCESSLIST", "QUERY", "CONNECTION", "WEAK", "UNIQUE",
  "FULLTEXT", "SPATIAL", "HASH", "BTREE", "INDEX", "SKIPLIST",
  "AUTO_INCREMENT", "CHUNKSERVER", "COMPRESS_METHOD", "CONSISTENT_MODE",
  "EXPIRE_INFO", "GRANTS", "JOIN_INFO", "MERGESERVER", "REPLICA_NUM",
  "ROOTSERVER", "ROW_COUNT", "SERVER", "SERVER_IP", "SERVER_PORT",
  "SERVER_TYPE", "STATUS", "TABLE_ID", "TABLET_BLOCK_SIZE",
  "TABLET_MAX_SIZE", "EXTERN_SIZE", "SKIP_LEVEL", "UNLOCKED",
  "UPDATESERVER", "USE_BLOOM_FILTER", "VARIABLES", "VERBOSE", "WARNINGS",
  "';'", "','", "$accept", "sql_stmt", "stmt_list", "stmt", "expr_list",
  "column_ref", "expr_const", "simple_expr", "arith_expr", "expr",
  "in_expr", "case_expr", "case_arg", "when_clause_list", "when_clause",
  "case_default", "func_expr", "when_func", "when_func_name",
  "when_func_stmt", "distinct_or_all", "delete_stmt", "update_stmt",
  "update_asgn_list", "update_asgn_factor", "create_index_stmt",
  "index_constraint", "index_type", "create_table_stmt",
  "opt_if_not_exists", "table_element_list", "table_element",
  "column_definition", "data_type", "opt_decimal", "opt_float",
  "opt_precision", "opt_time_precision", "opt_char_length",
  "opt_column_attribute_list", "column_attribute", "opt_table_option_list",
  "table_option", "opt_equal_mark", "drop_table_stmt", "opt_if_exists",
  "table_list", "insert_stmt", "opt_when", "replace_or_insert",
  "opt_insert_columns", "column_list", "insert_vals_list", "insert_vals",
  "select_stmt", "select_with_parens", "select_no_parens",
  "no_table_select", "select_clause", "simple_select", "opt_where",
  "select_limit", "opt_hint", "opt_hint_list", "hint_options",
  "hint_option", "opt_comma_list", "consistency_level", "limit_expr",
  "opt_select_limit", "opt_for_update", "parameterized_trim",
  "opt_groupby", "opt_order_by", "order_by", "sort_list", "sort_key",
  "opt_asc_desc", "opt_having", "opt_distinct", "projection",
  "select_expr_list", "from_list", "table_factor", "relation_factor",
  "joined_table", "join_type", "join_outer", "explain_stmt",
  "explainable_stmt", "opt_verbose", "show_stmt", "opt_limit",
  "opt_for_grant_user", "opt_scope", "opt_show_condition",
  "opt_like_condition", "opt_full", "create_user_stmt",
  "user_specification_list", "user_specification", "user", "password",
  "drop_user_stmt", "user_list", "set_password_stmt", "opt_for_user",
  "rename_user_stmt", "rename_info", "rename_list", "lock_user_stmt",
  "lock_spec", "opt_work", "opt_with_consistent_snapshot", "begin_stmt",
  "commit_stmt", "rollback_stmt", "kill_stmt", "opt_is_global", "opt_flag",
  "grant_stmt", "priv_type_list", "priv_type", "opt_privilege",
  "priv_level", "revoke_stmt", "opt_on_priv_level", "prepare_stmt",
  "stmt_name", "preparable_stmt", "variable_set_stmt", "var_and_val_list",
  "var_and_val", "to_or_eq", "argument", "execute_stmt", "opt_using_args",
  "argument_list", "deallocate_prepare_stmt", "deallocate_or_drop",
  "alter_table_stmt", "alter_column_actions", "alter_column_action",
  "opt_column", "opt_drop_behavior", "alter_column_behavior",
  "alter_system_stmt", "opt_force", "alter_system_actions",
  "alter_system_action", "opt_comment", "opt_config_scope", "server_type",
  "opt_cluster_or_address", "column_name", "relation_name",
  "function_name", "column_label", "unreserved_keyword", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    43,    45,    42,    47,    37,   287,    94,   288,
      40,    41,    46,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,    59,    44
};
# endif

#define YYPACT_NINF -747

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-747)))

#define YYTABLE_NINF -480

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2173,    31,   245,  -100,  -100,   202,  -747,     5,  1886,  1886,
     -46,  1915,  -102,   436,  -747,  1915,   -60,  -747,   436,  -100,
      53,    61,  1226,   408,    70,    61,   196,   -53,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,   123,  -747,     1,    81,  -747,
      65,    62,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,   141,
    -747,  -747,   234,   255,   241,  1886,   296,  -747,  -747,  -747,
     211,   296,  -747,  -747,  -747,   139,  1886,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   339,  -747,  -747,   339,   242,   296,  -747,
     193,  -747,  -747,  -747,   267,   237,  -747,   201,  -747,  -747,
     263,  -747,  -747,  -747,  -747,   -24,  -747,   290,   296,   -23,
    -747,  -747,   113,    67,    43,  -747,    23,    23,  1977,   349,
     306,  1977,   357,   207,  -747,    23,  -747,  -747,    56,   259,
    -747,  -747,    -2,  -747,  -747,   226,    -2,   336,   227,   315,
     219,   223,   260,   401,   269,  1886,  -747,  -747,  2173,  1886,
    1569,  -747,    43,    43,    43,   395,    -7,    -6,   288,  -747,
    1915,  -747,  -747,  -747,  1977,   338,   300,   341,   203,  -747,
     -27,   440,  1886,   243,  -747,   363,  1886,   294,  -747,  -747,
    -747,   382,  1773,  -747,   261,   462,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  1682,   436,   267,   313,
    -747,   264,  1682,   393,  -747,  -747,   480,  -747,  -747,  -747,
     446,   -63,    67,  -747,  -747,  -747,   941,  -747,  -747,  1569,
    1569,    23,  1977,   296,   465,    23,  1977,  1655,  1569,  1886,
    1886,  1886,   485,  1569,  -747,    -2,  -747,    60,  -747,  -747,
      -2,   486,  -747,  -747,    -2,  -747,   586,   432,  -747,   351,
    -747,    32,   289,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  1569,  1569,  1569,  1198,  1569,   455,   458,  -747,
    -747,  -747,  2577,  -747,  -747,  -747,   461,  -747,  -747,   469,
     470,    38,    38,    38,  1569,   104,   104,   438,  -747,  -747,
    -747,   305,  -747,   508,   523,   524,   430,   433,   488,   488,
     488,   -10,   344,  -747,   507,  -747,  -747,  -747,   478,   525,
     296,   514,   457,  1253,    81,  -747,   686,   364,   847,   310,
    1947,  -747,   296,  -747,  -747,   365,  -747,   416,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,   296,   296,  -747,   296,  -747,
     -21,   -25,  -747,    67,  -747,  -747,   983,  -747,   -43,  2577,
    2577,  1569,    23,  -747,   579,  1569,    23,  -747,  2577,    -2,
      -2,  -747,  -747,  2577,  -747,   544,  -747,   370,  -747,   546,
    -747,  -747,  1286,  -747,  1498,  1531,    -3,  2371,  1569,   547,
     444,  1977,   890,   427,  -747,   891,  -747,  -747,   386,  2005,
     235,  2577,   431,  -747,  1569,  1569,   257,  1569,  1569,  1569,
    1569,  1569,  1569,  1569,  1569,  1627,   564,   453,  1569,  1569,
    1569,  1569,  1569,  1569,  1569,   267,  1808,    61,  -747,   591,
    -747,   591,  -747,  2495,   394,  -747,  -747,  -747,   -67,   500,
    -747,  1977,   531,   609,   610,   592,   593,  -747,  1977,  1977,
    1977,  1886,  1977,   247,   579,  -747,  1859,  -747,   363,   579,
    1886,  1569,  2577,  -747,  1743,   310,   576,  1773,  1886,  -747,
     497,  -747,  1773,   497,   497,   515,  1886,  -747,  -747,   462,
     296,  -747,  -747,   261,  -747,  -747,  -747,  -747,  -747,  -747,
     583,    67,  1915,  -747,  1711,   941,  -747,  -747,  2577,  1569,
    -747,  -747,  2577,  1569,  -747,  -747,   584,   623,  -747,  1569,
    2401,  1569,  2422,  1569,  2444,  -747,  1569,  2216,  1569,  2526,
    -747,  -747,   -82,  -747,   607,     2,  -747,   601,  1569,  -747,
    1569,   -26,  -747,  2473,   891,  1569,  1627,   564,   811,   811,
     811,   811,   811,   811,   704,   727,  1627,  1627,  -747,   471,
    1198,  -747,  -747,  -747,  -747,  -747,   396,   224,   224,   602,
     602,   602,   602,  -747,   604,  -747,  -747,  -747,  -747,  -747,
    -747,    43,  -747,  -747,  -747,  1569,   104,   104,   104,  -747,
     587,  -747,  -747,   639,   643,  -747,  2216,    20,   103,  -747,
     483,   488,  -747,  -747,   541,     4,  -747,  -747,  -747,    -4,
    2577,   605,   310,  -747,  -747,  -747,   162,  -747,  -747,  1773,
    -747,  -747,   261,  -747,  -747,   294,   -81,   310,  -747,  2577,
    2577,  -747,  -747,  2577,  1569,  2577,  1569,  2577,  1569,  2577,
    -747,   611,  -747,   611,  -747,  -747,  -747,   613,   527,   615,
    -747,  -747,  -747,   613,  -747,  -747,   617,   617,  -747,   611,
     611,   618,  2577,  -747,  1977,    81,  1569,    31,  1977,  1569,
     -74,  2553,  2174,  1569,  -747,   580,   727,   539,  -747,  -747,
    -747,  1627,  1627,  1627,  1627,  1627,  1627,  1627,  1627,     7,
    2577,  -747,  -747,  -747,  -747,   941,  -747,  -747,  -747,  -747,
     654,   519,  -747,  -747,  -747,    42,    46,  -747,  -747,  -747,
    -747,  1915,   624,   160,  1859,  1977,   191,  1886,  1569,   311,
      -7,  1773,   568,  2577,  2577,  2577,   661,  -747,  -747,   662,
    -747,  -747,  -747,   663,  -747,  -747,   664,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  2577,  -747,  -747,  2577,     8,   630,
    -747,  -747,  1569,  2577,  -747,  1627,   600,   482,   482,   635,
     635,   635,   635,  -747,  -747,   -39,  -747,   651,   473,    21,
     666,  -747,   670,   531,  -747,  1977,   658,   658,   658,   658,
     658,   658,   658,   658,   658,   658,   658,   658,   466,  -747,
    -747,    13,  -747,  -747,  -747,   644,  -747,  2577,  1569,  -747,
     310,   629,   588,   647,    15,   649,   650,  -747,  1569,  1569,
    2577,   600,  1773,    36,   674,  -747,   675,   531,   589,  -747,
    -747,  -747,  -747,  -747,    17,  -747,   689,   695,   548,   697,
     698,   699,   703,   705,   706,   707,   709,   708,   160,   160,
    1977,  2577,  1569,  1569,  -747,  -747,  -747,   710,  -747,  -747,
    2577,    24,  -747,  -747,  -747,   164,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,  -747,   466,    29,   501,  2577,   677,  -747,  -747,
    -747,  -747,  -747,   -30,   160,  -747,   696,   721,  -747,   466,
     715,   723,  -747,   528,   722,   725,  -747
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      31,     0,     0,   374,   374,   131,   433,     0,     0,     0,
     434,     0,   320,     0,   211,     0,     0,   210,     0,   374,
     382,   244,     0,   344,     0,   244,     0,     0,     4,    10,
       9,     8,     7,    11,     6,     0,     5,   231,   208,   224,
     277,   230,    12,    13,    20,    21,    22,    23,    24,    27,
      28,    29,    30,    25,    26,    14,    15,    16,    19,     0,
      17,    18,   231,     0,   457,     0,     0,   373,   377,   379,
     138,     0,   128,   129,   130,     0,     0,   477,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   499,   498,   500,   501,   502,   503,
     504,   505,   506,   348,   305,   478,   348,   201,     0,   480,
     429,   409,   481,   319,     0,   402,   391,   392,   394,   395,
       0,   397,   400,   399,   398,     0,   388,     0,     0,   407,
     380,   383,   384,   248,   287,   475,     0,     0,     0,     0,
     365,     0,     0,   414,   415,     0,   476,   479,     0,     0,
     351,   342,   345,   327,   343,     0,   345,   365,     0,   338,
       0,     0,     0,     0,   376,     0,     1,     2,    31,     0,
       0,   220,   287,   287,   287,     0,     0,   265,     0,   225,
       0,   223,   222,   458,     0,     0,     0,     0,     0,   357,
       0,     0,     0,   352,   354,   353,     0,   236,   349,   330,
     329,     0,     0,   360,   359,     0,   427,   316,   318,   317,
     315,   314,   401,   390,   393,   396,     0,     0,     0,     0,
     368,   366,     0,     0,   385,   386,     0,   256,   252,   251,
       0,     0,   246,   249,   288,   289,     0,   425,   424,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   334,   345,   321,     0,   333,   339,
     345,     0,   331,   332,   345,   335,     0,     0,   378,     0,
       3,   213,   475,    37,    39,    38,    41,    40,    42,    43,
      45,    44,     0,     0,     0,     0,   101,     0,   492,    46,
      47,    65,   209,    50,    51,    52,     0,    53,    34,     0,
     476,     0,     0,     0,     0,     0,     0,   265,   226,   266,
     432,   452,   459,     0,     0,     0,     0,     0,   444,   444,
     444,   444,   435,   437,     0,   371,   372,   370,     0,     0,
       0,     0,     0,     0,   208,   202,     0,   200,     0,   203,
     298,   303,     0,   426,   430,   428,   403,     0,   404,   389,
     413,   412,   411,   410,   408,     0,     0,   406,     0,   381,
       0,     0,   245,     0,   250,   293,   290,   294,   263,   423,
     417,     0,     0,   364,     0,     0,     0,   416,   418,   345,
     345,   328,   346,   347,   324,   340,   325,   337,   326,     0,
     112,   119,     0,   120,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,   206,    85,    66,    67,     0,    32,
      53,   100,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   244,   231,   233,
     230,   235,   234,   282,   278,   279,   261,   262,   241,   242,
     227,     0,     0,     0,     0,     0,     0,   443,     0,     0,
       0,     0,     0,     0,     0,   137,     0,   355,     0,     0,
       0,     0,   237,   121,   231,     0,   303,     0,     0,   302,
       0,   312,     0,     0,     0,     0,     0,   300,   361,     0,
       0,   367,   369,   405,   254,   255,   260,   259,   258,   257,
       0,   247,     0,   291,     0,     0,   264,   228,   419,     0,
     358,   362,   420,     0,   323,   322,     0,     0,   107,     0,
       0,     0,     0,     0,     0,   109,     0,     0,     0,     0,
     111,   375,   236,   123,     0,     0,   214,     0,     0,    48,
       0,   106,   102,    84,    83,     0,     0,     0,    75,    76,
      77,    79,    78,    80,    96,    81,     0,     0,    55,     0,
       0,    94,    97,    88,    86,    90,     0,    68,    69,    70,
      71,    72,    74,    73,     0,   118,   117,   116,   115,    36,
      35,   287,   283,   284,   281,     0,     0,     0,     0,   460,
     463,   455,   456,     0,     0,   439,     0,     0,   447,   436,
       0,   444,   438,   363,     0,     0,   139,   141,   356,     0,
     238,   306,   204,   301,   313,   309,     0,   310,   311,     0,
     299,   431,   387,   253,   292,   236,   236,   296,   295,   421,
     422,   341,   336,   271,     0,   272,     0,   273,     0,    33,
     148,   175,   151,   175,   161,   163,   156,   167,   171,   169,
     147,   146,   162,   167,   153,   145,   173,   173,   144,   175,
     175,     0,   267,   108,     0,   208,     0,   212,     0,     0,
     208,    33,     0,     0,   103,     0,    82,     0,    95,    56,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    89,    87,    91,   113,     0,   280,   239,   243,   240,
       0,   467,   453,   454,   177,     0,     0,   441,   445,   446,
     440,     0,     0,   185,     0,     0,   135,     0,     0,     0,
     263,     0,   274,   268,   269,   270,     0,   158,   157,     0,
     149,   170,   154,     0,   152,   150,     0,   164,   155,   159,
     160,   110,   124,   122,   125,   207,   215,   218,     0,     0,
     205,    49,     0,   105,    99,     0,    92,    58,    59,    60,
      61,    62,    64,    63,    98,     0,   462,     0,     0,   143,
       0,   451,     0,     0,   442,     0,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   199,   199,   136,   183,
     140,     0,   132,   133,   134,     0,   304,   308,     0,   229,
     297,     0,   285,     0,     0,     0,     0,   216,     0,     0,
     104,    93,     0,     0,     0,   179,     0,     0,     0,   181,
     176,   449,   448,   450,     0,   198,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
       0,   307,     0,     0,   232,   174,   166,     0,   168,   172,
     219,     0,   466,   464,   465,     0,   178,   180,   182,   142,
     197,   194,   196,   187,   186,   193,   192,   191,   188,   189,
     190,   195,   184,   127,     0,   275,   286,     0,   217,   470,
     471,   468,   469,   474,   185,   165,     0,     0,   461,   126,
       0,     0,   472,     0,     0,     0,   473
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -747,  -747,  -747,   560,  -280,  -747,  -440,  -366,  -483,   439,
     199,  -747,  -747,  -747,   206,  -747,   726,  -747,  -747,  -747,
    -747,   -95,   -93,  -747,    84,  -747,  -747,  -747,  -747,  -747,
    -747,    37,   295,   156,   101,  -747,  -747,   109,  -558,  -747,
    -747,  -746,   -70,   154,  -747,  -747,  -747,   -87,  -321,  -747,
    -747,  -671,  -747,   -38,  -108,    10,     3,  -747,   222,   252,
    -347,   594,   -17,  -747,   442,  -207,  -747,  -747,  -282,    73,
    -148,  -747,  -747,  -747,  -747,  -747,   209,  -747,  -747,  -157,
     297,   106,  -747,  -193,    14,   467,  -747,  -175,  -747,  -747,
    -747,  -747,  -747,  -747,  -747,  -123,   700,  -747,  -747,  -747,
     477,   -32,  -325,  -747,  -323,  -747,   652,  -747,   452,  -747,
    -747,  -747,   228,  -747,  -747,  -747,  -747,  -747,  -747,  -747,
    -747,   793,   595,  -747,   596,  -747,  -747,  -747,    35,  -747,
    -747,  -747,   566,  -105,   326,  -747,  -747,  -747,  -747,  -747,
    -747,  -747,   353,    18,  -747,  -747,  -747,  -747,  -747,   366,
    -747,  -747,  -747,  -747,   -20,    52,  -747,  -348,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,   396,   289,   290,   291,   559,   366,
     561,   293,   412,   541,   542,   675,   294,   295,   296,   574,
     398,    29,    30,   532,   533,    31,    75,   795,    32,   192,
     605,   606,   607,   661,   730,   734,   732,   737,   727,   769,
     820,   788,   789,   826,    33,   202,   337,    34,   171,    35,
     403,   535,   670,   748,    36,   297,    38,    39,    40,    41,
     334,   506,   134,   231,   232,   233,   360,   500,   448,   507,
     179,   399,   802,   176,   177,   444,   445,   584,   844,   236,
     367,   368,   626,   627,   340,   341,   485,   615,    42,   211,
     114,    43,   262,   258,   161,   254,   199,   162,    44,   193,
     194,   203,   511,    45,   204,    46,   244,    47,   220,   221,
      48,   327,    68,   268,    49,    50,    51,    52,   132,   226,
      53,   125,   126,   213,   347,    54,   223,    55,   110,   354,
      56,   143,   144,   239,   344,    57,   206,   345,    58,    59,
      60,   322,   323,   462,   710,   707,    61,   187,   311,   312,
     701,   768,   883,   888,   298,   299,   163,   111,   300
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     105,   105,   145,   112,    63,   408,   210,   112,   165,   339,
      37,    62,   590,   473,   146,   301,   302,   303,   503,   207,
     494,   208,   103,   106,   449,   364,   252,   209,   886,   308,
     167,   815,   240,   256,   190,   493,   715,   362,   525,   195,
     248,   816,  -221,   667,   791,   713,   237,   504,   764,   807,
     127,   812,   457,   586,   839,   673,   846,   105,   859,   558,
     104,   104,   770,   677,   189,   878,   772,   496,   105,   305,
     884,     1,   402,   679,   680,   324,    67,   306,     1,   188,
     172,   173,   174,   178,  -221,   728,   249,   325,   234,   852,
     197,   333,   333,   873,   817,    76,   219,   216,   222,   705,
     170,   739,   740,  -265,   824,   305,  -276,   227,   128,   446,
     353,   113,   107,   306,  -276,   771,   447,   104,   241,   773,
     235,   245,   108,   350,    37,   351,   385,   497,   104,   498,
     146,   352,   384,   146,   664,   721,   371,   386,   889,   603,
     375,   388,   749,   475,   608,  -265,   250,   131,   540,   587,
     818,   178,   853,   363,   624,   499,   461,   105,   708,   450,
     133,   105,   168,   404,   313,   716,   706,   622,   228,   874,
     887,   253,   112,   505,    21,    21,   146,   505,    37,   269,
     558,   437,   326,   271,   105,   665,   854,   175,   105,   238,
     558,   558,   217,   217,   105,   495,   166,   229,   756,   757,
     758,   759,   760,   761,   762,   763,   329,   230,   105,   819,
     332,   373,   338,   526,   105,   310,  -221,   104,   668,   776,
     714,   104,   372,   526,   808,   373,   376,   145,    37,   668,
     169,   847,    69,   668,   146,   164,  -265,   709,   146,   146,
     808,   105,   105,   105,   104,   668,   318,   130,   104,   319,
    -231,  -231,  -231,   480,   104,   170,   514,   515,   430,   431,
     432,   433,   434,   379,   380,   381,   481,   509,   348,   180,
     482,   513,   811,   483,   348,   181,   181,  -265,   720,   722,
     689,    37,   320,   718,   612,   545,   546,   547,    63,   616,
     318,   224,   225,   319,   364,   410,   182,   413,   468,   484,
     189,   104,   104,   104,   697,   698,   699,     1,   617,   618,
     488,   438,   438,   438,   191,   558,   558,   558,   558,   558,
     558,   558,   558,   491,   219,   196,   320,   578,   105,  -479,
     105,  -477,   105,   823,   183,   321,   458,   459,   460,    63,
     575,     7,   576,   198,   743,   201,   474,  -231,   577,   750,
     777,   778,   779,   879,   780,  -231,   781,  -231,   112,   880,
      70,   881,   205,   774,   782,   783,   784,   785,   786,   214,
      71,   787,   212,    14,   882,   792,   793,   857,   794,   601,
     218,   534,   536,    72,    73,    74,   215,   184,   104,   558,
     479,   242,   487,   146,   146,   243,   185,   186,    64,   246,
      17,   480,   480,    65,   691,    63,   692,   693,   316,   317,
      21,   147,    62,    66,   481,   481,   580,   251,   482,   482,
     581,   483,   483,   247,   695,   257,   719,   261,   146,   255,
     260,   313,   798,   263,    25,   264,   562,   265,   596,   597,
     598,   266,   600,   146,   267,    37,   596,   484,   484,   304,
     146,   146,   146,   105,   146,   309,   314,   315,   146,   330,
     328,   563,   105,   564,   565,   331,   105,   333,   335,   105,
     105,   148,   149,   566,   105,   599,   343,   342,   105,   355,
     356,   115,   116,   358,   609,   359,   361,   338,   374,   382,
     681,   387,   338,   400,   112,     1,   105,   401,  -114,   150,
     117,   435,   151,   682,   683,   684,   685,   686,   687,   688,
     118,   436,  -478,   104,   338,   119,   684,   685,   686,   687,
     688,   451,   104,   439,   441,   442,   479,   178,   800,   104,
     613,   452,   120,   152,   104,   273,   274,   275,   620,   276,
     277,   278,   121,   279,   280,   281,   453,   454,   455,   153,
     457,   456,   154,   440,   440,   440,   104,   562,   755,   745,
     463,   464,   875,    63,   465,   466,   155,   156,   469,   122,
     410,   682,   683,   684,   685,   686,   687,   688,   470,   123,
     477,   489,   490,   510,   516,  -350,   517,   518,   530,   272,
     273,   274,   275,   531,   276,   277,   278,   537,   279,   280,
     281,   157,   538,   124,   560,   540,   282,   158,   174,   292,
     585,   105,   588,   591,   592,   593,   594,   611,   283,   284,
     389,   614,   159,   619,   623,   631,   285,   390,   632,   338,
     666,   391,   682,   683,   684,   685,   686,   687,   688,   392,
     434,   669,   286,   702,   534,   694,   700,   703,   746,   711,
     712,   726,   717,   729,   731,   733,   146,   736,   766,   741,
     146,   767,   754,   393,   775,   801,   803,   804,   805,   806,
     809,   104,   287,   688,   813,   814,   821,    37,   369,   370,
     822,   825,   838,   842,   840,   856,   843,   378,   845,    77,
     848,   849,   383,   860,   596,   536,   394,   855,   858,   861,
     862,   863,   864,   112,   865,   397,   146,   146,   866,   105,
     867,   868,   869,   105,   870,   877,   871,   526,   885,   890,
     892,   405,   406,   407,   409,   411,   336,   893,   270,   894,
     896,   338,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   443,   891,   895,   678,   674,   742,   160,
     395,   790,   704,   595,   735,   536,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   738,   146,   872,   796,
     307,   851,   472,   104,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   288,    89,    90,    91,    92,    93,
      94,    95,    96,   799,   696,    97,    98,    99,   100,   101,
     102,   765,   628,   476,   105,   501,   200,   467,   492,   259,
     508,   129,   349,   377,   512,   621,   602,   589,   357,     0,
     536,     0,   338,     0,     0,     0,     0,     0,     0,    21,
       0,   520,   146,   522,   524,     0,     0,   529,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
      77,     0,     0,   543,   544,     0,   548,   549,   550,   551,
     552,   553,   554,   555,   104,     0,     0,   567,   568,   569,
     570,   571,   572,   573,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   135,   478,    97,    98,    99,   100,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     610,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       1,   827,   828,   829,   830,   831,   832,   833,   834,   835,
     836,   837,     0,     0,   272,   273,   274,   275,   629,   276,
     277,   278,   630,   279,   280,   281,     0,     0,   633,     0,
     635,   282,   637,     0,     0,   639,     0,   662,     0,     0,
       0,     0,     0,   283,   284,   365,     0,   671,     0,   672,
       0,   285,     0,     0,   676,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   286,     0,   690,
       0,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,     0,     0,   443,     0,     0,   287,     0,     0,
     502,     0,     0,    21,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,     0,    97,    98,    99,   100,
     101,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   723,     0,   724,     0,   725,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,     0,     0,    97,
      98,    99,   100,   101,   102,   744,     0,     0,   747,     0,
       0,     0,   753,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   288,
      89,    90,    91,    92,    93,    94,    95,    96,     0,     0,
      97,    98,    99,   100,   101,   102,     0,   797,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
       0,   810,    97,    98,    99,   100,   101,   102,     0,     0,
       0,   272,   273,   274,   275,     0,   276,   277,   278,     0,
     279,   280,   281,     0,     0,     0,     0,     0,   282,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     283,   284,     0,     0,     0,     0,     0,   841,   285,   136,
     137,     0,     0,     0,     0,     0,     0,   850,   747,     0,
       0,     0,     0,     0,   286,     0,   272,   273,   274,   275,
     471,   276,   277,   278,     0,   279,   280,   281,     0,     0,
       0,     0,     0,   282,     0,     0,     0,     0,     0,     0,
       0,   690,   876,     0,   287,   283,   284,     0,     0,   272,
     273,   274,   275,   285,   276,   277,   278,     0,   279,   280,
     281,     0,     0,     0,     0,     0,   282,     0,     0,   286,
       0,     0,     0,     0,     0,     0,     0,     0,   283,   284,
     138,   139,     0,     0,     0,     0,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   287,
       0,    21,   286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     141,   142,   287,     0,     0,     0,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   288,    89,    90,    91,
      92,    93,    94,    95,    96,     0,     0,    97,    98,    99,
     100,   101,   102,     0,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,     0,     0,    97,    98,    99,   100,   101,
     102,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,   288,    89,    90,    91,    92,    93,    94,    95,    96,
       0,     0,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,     0,     0,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   288,    89,    90,    91,    92,    93,
      94,    95,    96,     0,     0,    97,    98,    99,   100,   101,
     102,   272,   273,   274,   275,     0,   276,   277,   278,     0,
     279,   280,   281,     0,     0,     0,     0,     0,   282,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     283,   284,     0,     0,   272,   273,   274,   275,   285,   276,
     277,   278,     0,   279,   280,   281,     0,     0,     0,     0,
       0,   282,     0,     0,   286,     0,     0,     0,     0,     0,
       0,     0,     0,   283,   284,     0,     0,     0,     0,     0,
       0,   285,   272,   273,   274,   275,     0,   276,   277,   278,
       0,   279,   280,   281,   287,     0,     0,   286,   521,   282,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   283,   284,     0,     0,     0,     0,     0,     0,   285,
       0,     0,     0,     0,     0,     0,     0,   287,     0,     0,
       0,   523,     0,     0,     0,   286,     0,     0,     0,     0,
     272,   273,   274,   275,     0,   276,   277,   278,     0,   279,
     280,   281,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   287,     0,     0,   135,   556,
     557,     0,     0,     0,     0,     0,     0,   285,   136,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   286,     0,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,   288,    89,    90,    91,
      92,    93,    94,    95,    96,     0,     0,    97,    98,    99,
     100,   101,   102,   287,    77,     0,   346,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   288,
      89,    90,    91,    92,    93,    94,    95,    96,     0,     0,
      97,    98,    99,   100,   101,   102,    77,     0,     0,   138,
     139,   336,     0,     0,     0,     0,     0,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,   288,    89,    90,
      91,    92,    93,    94,    95,    96,    77,     0,    97,    98,
      99,   100,   101,   102,   181,     0,     0,     0,     0,     0,
     478,   625,     0,     0,     0,     0,     0,     0,     0,   141,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,     0,   336,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,   288,    89,    90,    91,    92,
      93,    94,    95,    96,     0,     0,    97,    98,    99,   100,
     101,   102,   579,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   135,     0,    97,    98,    99,   100,   101,   102,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    77,
       0,    97,    98,    99,   100,   101,   102,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,   109,     0,
      97,    98,    99,   100,   101,   102,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      77,     0,    97,    98,    99,   100,   101,   102,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
     135,     0,    97,    98,    99,   100,   101,   102,   604,     0,
       0,     0,     0,     0,   486,     0,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,     0,     0,    97,    98,    99,
     100,   101,   102,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,     0,     0,   539,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,     0,     0,    97,    98,
      99,   100,   101,   102,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,     0,     0,    97,    98,    99,   100,   101,
     102,     0,     0,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     0,     0,    97,    98,    99,   100,   101,   102,
       0,     0,     0,     0,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,     0,    97,    98,    99,   100,
     101,   102,     0,     0,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,     0,     0,    97,    98,    99,   100,
     101,   102,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,     1,     0,     0,     0,     0,     0,     2,
       0,     0,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     6,     0,     0,     7,     8,     9,
       0,     0,    10,     0,     0,     0,     0,     0,    11,     0,
      12,     0,     0,     0,     0,     0,   640,   641,   642,    13,
       0,     0,     0,   643,     0,     0,     0,     0,     0,    14,
       0,   644,     0,     0,     0,   645,   646,     0,   647,     0,
       0,     0,     0,     0,   648,     0,     0,     0,     0,     0,
       0,    15,     0,     0,   649,    16,    17,     0,     0,    18,
       0,    19,    20,     0,     0,     0,    21,     0,     0,    22,
      23,   650,     0,     0,    24,     0,     0,     0,     0,     0,
       0,   651,     0,   652,   752,   653,     0,     0,     0,     0,
      25,     0,     0,     0,     0,     0,     0,   654,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   655,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   656,   657,   658,
       0,     0,     0,     0,     0,     0,     0,   659,   660,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
       0,     0,     0,     0,     0,     0,     0,     0,   527,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     434,   528,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,     0,     0,     0,     0,     0,     0,     0,
       0,   634,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   636,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   638,     0,     0,     0,     0,     0,
       0,     0,     0,   582,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,     0,     0,   663,     0,     0,
     583,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,     0,     0,   751,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434
};

static const yytype_int16 yycheck[] =
{
       8,     9,    22,    11,     1,   285,   114,    15,    25,   202,
       0,     1,   452,   334,    22,   172,   173,   174,   366,   114,
      41,   114,     8,     9,   306,   232,    28,   114,    58,   177,
      83,    10,   137,   156,    66,   358,    40,   100,    41,    71,
     145,    20,    41,    41,   715,    41,    23,    90,    41,    41,
      15,    90,    62,   120,    41,    81,    41,    65,    41,   425,
       8,     9,    20,   546,     4,    41,    20,    92,    76,   112,
      41,    40,    40,   556,   557,   102,   176,   120,    40,    65,
      15,    16,    17,    89,    83,   643,    30,   114,    45,    53,
      76,   173,   173,   839,    73,    90,   128,   121,   121,    79,
     174,   659,   660,    41,   775,   112,   112,    40,   168,     5,
     218,   213,   158,   120,   120,    73,    12,    65,   138,    73,
      77,   141,   168,   218,   114,   218,    66,   152,    76,   154,
     138,   218,   255,   141,   216,   216,   241,   260,   884,   464,
     245,   264,   216,   336,   469,    83,    90,    94,   174,   216,
     129,    89,   116,   216,   502,   180,   166,   165,    55,   307,
      99,   169,   215,   271,   184,   169,   146,   490,   101,   840,
     200,   173,   180,   216,   143,   143,   184,   216,   168,   165,
     546,   143,   209,   169,   192,   532,   150,   122,   196,   166,
     556,   557,   216,   216,   202,   216,     0,   130,   681,   682,
     683,   684,   685,   686,   687,   688,   192,   140,   216,   188,
     196,   243,   202,   216,   222,   180,   215,   165,   216,    59,
     216,   169,   242,   216,   216,   257,   246,   247,   218,   216,
     107,   216,     4,   216,   242,   165,   174,   134,   246,   247,
     216,   249,   250,   251,   192,   216,    43,    19,   196,    46,
      15,    16,    17,    91,   202,   174,   379,   380,    34,    35,
      36,    37,    38,   249,   250,   251,   104,   372,   216,   128,
     108,   376,   755,   111,   222,    41,    41,   215,   625,   626,
     560,   271,    79,   121,   477,    28,    29,    30,   285,   482,
      43,   178,   179,    46,   501,   285,    41,   287,   330,   137,
       4,   249,   250,   251,   586,   587,   588,    40,   483,   484,
     342,   301,   302,   303,   103,   681,   682,   683,   684,   685,
     686,   687,   688,   355,   356,   186,    79,   435,   336,    40,
     338,    42,   340,   773,    93,   132,   318,   319,   320,   336,
     435,    74,   435,     4,   665,   103,   336,   112,   435,   670,
     190,   191,   192,   189,   194,   120,   196,   122,   366,   195,
     158,   197,   169,   711,   204,   205,   206,   207,   208,   168,
     168,   211,   135,   106,   210,   184,   185,   817,   187,   132,
      90,   401,   402,   181,   182,   183,   123,   146,   336,   755,
     338,    42,   340,   401,   402,    89,   155,   156,   153,    42,
     133,    91,    91,   158,     8,   402,    10,    11,    67,    68,
     143,     3,   402,   168,   104,   104,   436,   158,   108,   108,
     437,   111,   111,   216,   581,    89,   619,   112,   436,   203,
     203,   451,   121,   214,   167,   212,   426,   177,   458,   459,
     460,    40,   462,   451,   175,   435,   466,   137,   137,    54,
     458,   459,   460,   461,   462,   167,   118,   157,   466,   216,
      20,     8,   470,    10,    11,   102,   474,   173,    86,   477,
     478,    63,    64,    20,   482,   461,    14,   216,   486,   166,
     216,    45,    46,    90,   470,     5,    40,   477,    23,     4,
      19,     5,   482,    61,   502,    40,   504,   146,    40,    91,
      64,    40,    94,    32,    33,    34,    35,    36,    37,    38,
      74,    42,    42,   461,   504,    79,    34,    35,    36,    37,
      38,   216,   470,   301,   302,   303,   474,    89,   721,   477,
     478,    23,    96,   125,   482,     4,     5,     6,   486,     8,
       9,    10,   106,    12,    13,    14,    23,    23,   118,   141,
      62,   118,   144,   301,   302,   303,   504,   547,    19,   667,
     216,    54,   842,   560,    86,    40,   158,   159,    54,   133,
     560,    32,    33,    34,    35,    36,    37,    38,   121,   143,
     216,   216,   166,     4,    40,   177,   216,    41,    41,     3,
       4,     5,     6,   149,     8,     9,    10,   170,    12,    13,
      14,   193,   216,   167,    40,   174,    20,   199,    17,   170,
     216,   619,   112,     4,     4,    23,    23,    41,    32,    33,
      34,   124,   214,   108,    41,    41,    40,    41,     5,   619,
      23,    45,    32,    33,    34,    35,    36,    37,    38,    53,
      38,    40,    56,     4,   664,    41,    59,     4,   668,   166,
     109,    40,    47,    40,   127,    40,   664,    40,     4,    41,
     668,   142,    82,    77,    40,    97,     5,     5,     5,     5,
      40,   619,    86,    38,    23,   202,    10,   667,   239,   240,
      10,    23,   216,    54,    40,    10,    98,   248,    41,     3,
      41,    41,   253,     4,   714,   715,   110,    23,   109,     4,
     152,     4,     4,   711,     5,   266,   714,   715,     5,   717,
       5,     5,     5,   721,     5,     5,     8,   216,    41,    23,
       5,   282,   283,   284,   285,   286,    40,     4,   168,   201,
       5,   721,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   304,    23,    23,   547,   541,   664,    23,
     164,   714,   596,   458,   653,   775,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   657,   775,   838,   717,
     176,   809,   333,   721,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   720,   585,   209,   210,   211,   212,   213,
     214,   695,   505,   336,   812,   363,   106,   330,   356,   157,
     371,    18,   217,   247,   375,   489,   463,   451,   222,    -1,
     840,    -1,   812,    -1,    -1,    -1,    -1,    -1,    -1,   143,
      -1,   392,   840,   394,   395,    -1,    -1,   398,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
       3,    -1,    -1,   414,   415,    -1,   417,   418,   419,   420,
     421,   422,   423,   424,   812,    -1,    -1,   428,   429,   430,
     431,   432,   433,   434,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,     3,    47,   209,   210,   211,   212,   213,
     214,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     471,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      40,   777,   778,   779,   780,   781,   782,   783,   784,   785,
     786,   787,    -1,    -1,     3,     4,     5,     6,   509,     8,
       9,    10,   513,    12,    13,    14,    -1,    -1,   519,    -1,
     521,    20,   523,    -1,    -1,   526,    -1,   528,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    -1,   538,    -1,   540,
      -1,    40,    -1,    -1,   545,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,   560,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,   585,    -1,    -1,    86,    -1,    -1,
      47,    -1,    -1,   143,    -1,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,    -1,    -1,   209,   210,   211,   212,
     213,   214,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   634,    -1,   636,    -1,   638,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,    -1,    -1,   209,
     210,   211,   212,   213,   214,   666,    -1,    -1,   669,    -1,
      -1,    -1,   673,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,    -1,    -1,
     209,   210,   211,   212,   213,   214,    -1,   718,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
      -1,   752,   209,   210,   211,   212,   213,   214,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      32,    33,    -1,    -1,    -1,    -1,    -1,   798,    40,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,   808,   809,    -1,
      -1,    -1,    -1,    -1,    56,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   842,   843,    -1,    86,    32,    33,    -1,    -1,     3,
       4,     5,     6,    40,     8,     9,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      94,    95,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,   143,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     144,   145,    86,    -1,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,    -1,    -1,   209,   210,   211,
     212,   213,   214,    -1,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,    -1,    -1,   209,   210,   211,   212,   213,
     214,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
      -1,    -1,   209,   210,   211,   212,   213,   214,    -1,    -1,
      -1,    -1,    -1,    -1,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,    -1,    -1,   209,   210,   211,   212,   213,
     214,     3,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,     3,     4,     5,     6,    40,     8,
       9,    10,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    40,     3,     4,     5,     6,    -1,     8,     9,    10,
      -1,    12,    13,    14,    86,    -1,    -1,    56,    90,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    90,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    10,    -1,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,     3,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,     3,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,    -1,    -1,   209,   210,   211,
     212,   213,   214,    86,     3,    -1,    34,    -1,    -1,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,    -1,    -1,
     209,   210,   211,   212,   213,   214,     3,    -1,    -1,    94,
      95,    40,    -1,    -1,    -1,    -1,    -1,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,     3,    -1,   209,   210,
     211,   212,   213,   214,    41,    -1,    -1,    -1,    -1,    -1,
      47,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,
     145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    40,    -1,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,    -1,    -1,   209,   210,   211,   212,
     213,   214,    34,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,     3,    -1,   209,   210,   211,   212,   213,   214,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,     3,
      -1,   209,   210,   211,   212,   213,   214,    -1,    -1,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,     3,    -1,
     209,   210,   211,   212,   213,   214,    -1,    -1,    -1,    -1,
      -1,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
       3,    -1,   209,   210,   211,   212,   213,   214,    -1,    -1,
      -1,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
       3,    -1,   209,   210,   211,   212,   213,   214,   129,    -1,
      -1,    -1,    -1,    -1,    47,    -1,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,    -1,    -1,   209,   210,   211,
     212,   213,   214,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    41,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,    -1,    -1,   209,   210,
     211,   212,   213,   214,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,    -1,    -1,   209,   210,   211,   212,   213,
     214,    -1,    -1,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,    -1,    -1,   209,   210,   211,   212,   213,   214,
      -1,    -1,    -1,    -1,    -1,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,    -1,    -1,   209,   210,   211,   212,
     213,   214,    -1,    -1,    -1,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,    -1,    -1,   209,   210,   211,   212,
     213,   214,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    40,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    74,    75,    76,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    96,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,   106,
      -1,    65,    -1,    -1,    -1,    69,    70,    -1,    72,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,   128,    -1,    -1,    88,   132,   133,    -1,    -1,   136,
      -1,   138,   139,    -1,    -1,    -1,   143,    -1,    -1,   146,
     147,   105,    -1,    -1,   151,    -1,    -1,    -1,    -1,    -1,
      -1,   115,    -1,   117,   160,   119,    -1,    -1,    -1,    -1,
     167,    -1,    -1,    -1,    -1,    -1,    -1,   131,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,   162,   163,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,   172,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    90,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    90,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    41,    -1,    -1,
      75,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    41,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    40,    46,    49,    60,    64,    71,    74,    75,    76,
      79,    85,    87,    96,   106,   128,   132,   133,   136,   138,
     139,   143,   146,   147,   151,   167,   218,   219,   220,   238,
     239,   242,   245,   261,   264,   266,   271,   272,   273,   274,
     275,   276,   305,   308,   315,   320,   322,   324,   327,   331,
     332,   333,   334,   337,   342,   344,   347,   352,   355,   356,
     357,   363,   272,   273,   153,   158,   168,   176,   329,   329,
     158,   168,   181,   182,   183,   243,    90,     3,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   209,   210,   211,
     212,   213,   214,   301,   372,   375,   301,   158,   168,     3,
     345,   374,   375,   213,   307,    45,    46,    64,    74,    79,
      96,   106,   133,   143,   167,   338,   339,   345,   168,   338,
     329,    94,   335,    99,   279,     3,    13,    14,    94,    95,
     126,   144,   145,   348,   349,   371,   375,     3,    63,    64,
      91,    94,   125,   141,   144,   158,   159,   193,   199,   214,
     233,   311,   314,   373,   165,   279,     0,    83,   215,   107,
     174,   265,    15,    16,    17,   122,   290,   291,    89,   287,
     128,    41,    41,    93,   146,   155,   156,   364,   301,     4,
     318,   103,   246,   316,   317,   318,   186,   301,     4,   313,
     313,   103,   262,   318,   321,   169,   353,   238,   239,   264,
     271,   306,   135,   340,   168,   123,   121,   216,    90,   318,
     325,   326,   121,   343,   178,   179,   336,    40,   101,   130,
     140,   280,   281,   282,    45,    77,   296,    23,   166,   350,
     350,   371,    42,    89,   323,   371,    42,   216,   350,    30,
      90,   158,    28,   173,   312,   203,   312,    89,   310,   323,
     203,   112,   309,   214,   212,   177,    40,   175,   330,   301,
     220,   301,     3,     4,     5,     6,     8,     9,    10,    12,
      13,    14,    20,    32,    33,    40,    56,    86,   198,   222,
     223,   224,   226,   228,   233,   234,   235,   272,   371,   372,
     375,   296,   296,   296,    54,   112,   120,   278,   287,   167,
     345,   365,   366,   371,   118,   157,    67,    68,    43,    46,
      79,   132,   358,   359,   102,   114,   209,   328,    20,   301,
     216,   102,   301,   173,   277,    86,    40,   263,   272,   300,
     301,   302,   216,    14,   351,   354,    34,   341,   372,   339,
     238,   239,   264,   271,   346,   166,   216,   341,    90,     5,
     283,    40,   100,   216,   282,    34,   226,   297,   298,   226,
     226,   350,   371,   318,    23,   350,   371,   349,   226,   301,
     301,   301,     4,   226,   312,    66,   312,     5,   312,    34,
      41,    45,    53,    77,   110,   164,   221,   226,   237,   288,
      61,   146,    40,   267,   271,   226,   226,   226,   221,   226,
     272,   226,   229,   272,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    40,    42,   143,   272,   275,
     276,   275,   275,   226,   292,   293,     5,    12,   285,   285,
     287,   216,    23,    23,    23,   118,   118,    62,   360,   360,
     360,   166,   360,   216,    54,    86,    40,   317,   318,    54,
     121,     7,   226,   265,   272,   300,   302,   216,    47,   372,
      91,   104,   108,   111,   137,   303,    47,   372,   318,   216,
     166,   318,   325,   321,    41,   216,    92,   152,   154,   180,
     284,   281,    47,   374,    90,   216,   278,   286,   226,   350,
       4,   319,   226,   350,   312,   312,    40,   216,    41,    90,
     226,    90,   226,    90,   226,    41,   216,    47,    90,   226,
      41,   149,   240,   241,   371,   268,   371,   170,   216,    41,
     174,   230,   231,   226,   226,    28,    29,    30,   226,   226,
     226,   226,   226,   226,   226,   226,    32,    33,   224,   225,
      40,   227,   272,     8,    10,    11,    20,   226,   226,   226,
     226,   226,   226,   226,   236,   238,   239,   264,   271,    34,
     371,   279,    48,    75,   294,   216,   120,   216,   112,   366,
     223,     4,     4,    23,    23,   249,   371,   371,   371,   301,
     371,   132,   359,   319,   129,   247,   248,   249,   319,   301,
     226,    41,   300,   372,   124,   304,   300,   304,   304,   108,
     372,   351,   321,    41,   374,    80,   299,   300,   297,   226,
     226,    41,     5,   226,    90,   226,    90,   226,    90,   226,
      50,    51,    52,    57,    65,    69,    70,    72,    78,    88,
     105,   115,   117,   119,   131,   148,   161,   162,   163,   171,
     172,   250,   226,    41,   216,   277,    23,    41,   216,    40,
     269,   226,   226,    81,   231,   232,   226,   225,   227,   225,
     225,    19,    32,    33,    34,    35,    36,    37,    38,   221,
     226,     8,    10,    11,    41,   296,   293,   285,   285,   285,
      59,   367,     4,     4,   250,    79,   146,   362,    55,   134,
     361,   166,   109,    41,   216,    40,   169,    47,   121,   300,
     277,   216,   277,   226,   226,   226,    40,   255,   255,    40,
     251,   127,   253,    40,   252,   251,    40,   254,   254,   255,
     255,    41,   241,   265,   226,   271,   371,   226,   270,   216,
     265,    41,   160,   226,    82,    19,   225,   225,   225,   225,
     225,   225,   225,   225,    41,   298,     4,   142,   368,   256,
      20,    73,    20,    73,   374,    40,    59,   190,   191,   192,
     194,   196,   204,   205,   206,   207,   208,   211,   258,   259,
     248,   268,   184,   185,   187,   244,   372,   226,   121,   286,
     300,    97,   289,     5,     5,     5,     5,    41,   216,    40,
     226,   225,    90,    23,   202,    10,    20,    73,   129,   188,
     257,    10,    10,   223,   268,    23,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   216,    41,
      40,   226,    54,    98,   295,    41,    41,   216,    41,    41,
     226,   270,    53,   116,   150,    23,    10,   223,   109,    41,
       4,     4,   152,     4,     4,     5,     5,     5,     5,     5,
       5,     8,   259,   258,   268,   221,   226,     5,    41,   189,
     195,   197,   210,   369,    41,    41,    58,   200,   370,   258,
      23,    23,     5,     4,   201,    23,     5
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   217,   218,   219,   219,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   221,   221,   222,   222,   222,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   225,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   227,   227,   228,
     229,   229,   230,   230,   231,   232,   232,   233,   233,   233,
     233,   233,   233,   234,   235,   236,   236,   236,   236,   237,
     237,   238,   239,   240,   240,   241,   242,   242,   243,   243,
     243,   243,   244,   244,   244,   244,   245,   246,   246,   247,
     247,   248,   248,   249,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   251,   251,   251,   252,   252,
     253,   253,   254,   254,   255,   255,   256,   256,   257,   257,
     257,   257,   257,   258,   258,   258,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   260,   260,
     261,   262,   262,   263,   263,   264,   264,   264,   265,   265,
     266,   266,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   272,   272,   273,   273,   273,   273,   274,   274,
     275,   275,   276,   276,   276,   276,   277,   277,   277,   278,
     278,   278,   278,   278,   279,   279,   280,   280,   280,   281,
     281,   282,   282,   282,   282,   283,   283,   284,   284,   284,
     284,   285,   285,   286,   286,   287,   287,   288,   288,   288,
     288,   288,   288,   288,   289,   289,   290,   290,   291,   292,
     292,   293,   294,   294,   294,   295,   295,   296,   296,   296,
     297,   297,   297,   297,   298,   298,   299,   299,   300,   300,
     300,   300,   300,   300,   300,   301,   302,   302,   302,   303,
     303,   303,   303,   304,   305,   306,   306,   306,   306,   307,
     307,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   309,   309,   309,   310,
     310,   310,   311,   311,   311,   312,   312,   312,   313,   313,
     314,   314,   315,   315,   316,   316,   317,   318,   319,   320,
     321,   321,   322,   322,   323,   323,   324,   325,   326,   326,
     327,   328,   328,   329,   329,   330,   330,   331,   331,   332,
     333,   334,   335,   335,   336,   336,   336,   337,   338,   338,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   340,   340,   341,   341,   342,   343,   343,   344,   345,
     346,   346,   346,   346,   347,   348,   348,   349,   349,   349,
     349,   349,   349,   349,   350,   350,   351,   352,   353,   353,
     354,   354,   355,   356,   356,   357,   357,   358,   358,   359,
     359,   359,   359,   360,   360,   361,   361,   361,   362,   362,
     362,   362,   363,   363,   363,   363,   363,   364,   364,   365,
     365,   366,   367,   367,   368,   368,   368,   368,   369,   369,
     369,   369,   370,   370,   370,   371,   371,   372,   372,   373,
     374,   374,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     5,
       1,     1,     1,     1,     2,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     2,     3,     4,     3,     4,
       3,     4,     5,     6,     3,     4,     3,     1,     3,     5,
       1,     0,     1,     2,     4,     2,     0,     4,     5,     4,
       6,     4,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     5,     7,     1,     3,     3,    12,    10,     1,     1,
       1,     0,     1,     1,     1,     0,     8,     3,     0,     1,
       3,     1,     5,     3,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     1,     2,     2,     1,     2,     2,     2,
       2,     1,     1,     1,     2,     5,     3,     0,     3,     0,
       1,     0,     3,     0,     3,     0,     2,     0,     2,     1,
       2,     1,     2,     1,     3,     0,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     0,
       4,     0,     2,     1,     3,     7,     4,     7,     0,     2,
       1,     1,     3,     0,     1,     3,     3,     5,     1,     3,
       2,     1,     3,     3,     1,     2,     3,     4,     5,     8,
       1,     1,     9,     4,     4,     4,     0,     2,     3,     4,
       4,     2,     2,     4,     0,     3,     1,     3,     0,     1,
       2,     1,     1,     4,     3,     2,     0,     1,     1,     1,
       1,     1,     1,     0,     1,     0,     2,     3,     4,     4,
       4,     3,     3,     3,     0,     3,     1,     0,     3,     1,
       3,     2,     0,     1,     1,     0,     2,     0,     1,     1,
       1,     2,     3,     1,     1,     3,     1,     3,     1,     3,
       2,     3,     2,     1,     5,     1,     3,     6,     5,     2,
       2,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       0,     3,     5,     5,     4,     4,     4,     2,     4,     3,
       3,     3,     3,     3,     3,     3,     4,     2,     0,     1,
       2,     4,     1,     1,     0,     0,     2,     2,     0,     1,
       0,     1,     3,     3,     1,     3,     4,     1,     1,     3,
       1,     3,     5,     6,     2,     0,     3,     3,     1,     3,
       4,     1,     1,     1,     0,     3,     0,     2,     3,     2,
       2,     4,     0,     1,     0,     1,     1,     6,     1,     3,
       2,     1,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     0,     1,     1,     5,     2,     0,     4,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     3,     4,
       4,     5,     5,     3,     1,     1,     1,     3,     2,     0,
       1,     3,     3,     1,     1,     4,     6,     1,     3,     3,
       4,     4,     5,     1,     0,     1,     1,     0,     3,     3,
       3,     2,     4,     7,     7,     6,     6,     0,     1,     1,
       3,     9,     2,     0,     3,     3,     3,     0,     1,     1,
       1,     1,     3,     6,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result, yyscan_t scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result, yyscan_t scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParseResult* result, yyscan_t scanner)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParseResult* result, yyscan_t scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (ParseResult* result, yyscan_t scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    {
      /*merge_nodes($$, result->malloc_pool_, T_STMT_LIST, $1);*/
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_STMT_LIST,(yyvsp[-1].node) );
      result->Doc.SetObject().AddMember("ROOT",*(yyval.node) , result->Doc.GetAllocator());
      //result->result_tree_ = $$;
      delete (yyval.node);
      YYACCEPT;
    }

    break;

  case 3:

    {
      if ((yyvsp[0].node) != NULL)
        /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3 );
        {
        	malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
        }
      else
        (yyval.node) = (yyvsp[-2].node);
    }

    break;

  case 4:

    {
      (yyval.node) = ((yyvsp[0].node) != NULL) ? (yyvsp[0].node) : NULL;
    }

    break;

  case 5:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 6:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 7:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 8:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 9:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 10:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 11:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 12:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 13:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 14:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 15:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 16:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 17:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 18:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 19:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 20:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 21:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 22:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 23:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 24:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 25:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 26:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 27:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 28:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 29:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 30:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 31:

    { (yyval.node) = NULL; }

    break;

  case 32:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 33:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 34:

    { //$$ = $1;
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
		 SafeAddMember((yyval.node),"COLUMN_NAME"  ,(yyvsp[0].node), result->Doc.GetAllocator());

    	 }

    break;

  case 35:

    {
     // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, $3);
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, $3);
				malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember((yyval.node),"RELATION_NAME",(yyvsp[-2].node), result->Doc.GetAllocator());
				SafeAddMember((yyval.node),"COLUMN_NAME"  ,(yyvsp[0].node), result->Doc.GetAllocator());
     // dup_expr_string($$->str_value_, result, @3.first_column, @3.last_column);
    }

    break;

  case 36:

    {
      // malloc_terminal_node(node, result->malloc_pool_, T_STAR);
      rapidjson::Value* node ;
      malloc_terminal_node(node, result->Doc.GetAllocator(), T_STAR);
      // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, node);
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, node);
				malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember((yyval.node),"RELATION_NAME",(yyvsp[-2].node), result->Doc.GetAllocator());
				SafeAddMember((yyval.node),"COLUMN_NAME"  ,node, result->Doc.GetAllocator());
    }

    break;

  case 37:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","STRING", result->Doc.GetAllocator());}

    break;

  case 38:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","DATE_VALUE", result->Doc.GetAllocator());}

    break;

  case 39:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","INTNUM", result->Doc.GetAllocator());}

    break;

  case 40:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","APPROXNUM", result->Doc.GetAllocator());}

    break;

  case 41:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","BOOL", result->Doc.GetAllocator());}

    break;

  case 42:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","NULL", result->Doc.GetAllocator());}

    break;

  case 43:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","QUESTIONMARK", result->Doc.GetAllocator());}

    break;

  case 44:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 45:

    { (yyval.node) = (yyvsp[0].node); (yyvsp[0].node)->AddMember("CONST_TYPE","SYSTEM_VARIABLE", result->Doc.GetAllocator());}

    break;

  case 46:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 47:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 48:

    { (yyval.node) = (yyvsp[-1].node); }

    break;

  case 49:

    {
      /*ParseNode *node = NULL;*/
      /*malloc_non_terminal_node(node, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/
      /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, node);*/
      rapidjson::Value* node ;
      //malloc_non_terminal_node(&node, result->Doc.GetAllocator(), T_LINK_NODE, $2, $4);
      malloc_list_node(&node,result->Doc.GetAllocator(),2, (yyvsp[-3].node), (yyvsp[-1].node));
      merge_nodes((yyval.node), result->Doc.GetAllocator(),T_EXPR_LIST, node);

    }

    break;

  case 50:

    {
      (yyval.node) = (yyvsp[0].node);
      /*
      yyerror(&@1, result, "CASE expression is not supported yet!");
      YYABORT;
      */
    }

    break;

  case 51:

    {  (yyval.node) = (yyvsp[0].node); }

    break;

  case 52:

    {  (yyval.node) = (yyvsp[0].node); }

    break;

  case 53:

    {	
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SUB_SELECT);
      SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[0].node), result->Doc.GetAllocator());	
    	//$$ = $1; 
    }

    break;

  case 54:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EXISTS, 1, $2);*/
    	//malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_EXISTS, $2);
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_OP_EXISTS);
    	(yyval.node)->AddMember("SUB_LINK_TYPE","EXISTS", result->Doc.GetAllocator());
    	SafeAddMember((yyval.node),"SUB_LINK_BODY",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 55:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 56:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_POS, (yyvsp[0].node));

    }

    break;

  case 57:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_NEG, (yyvsp[0].node));

    }

    break;

  case 58:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","ADDX", T_OP_ADD,  (yyvsp[-2].node), (yyvsp[0].node));  }

    break;

  case 59:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS, 2, $1, $3); */ malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MINUSX",T_OP_MINUS,(yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 60:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MULX", T_OP_MUL,  (yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 61:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","DIVX", T_OP_DIV,  (yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 62:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","REMX", T_OP_REM,  (yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 63:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POWX", T_OP_POW,  (yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 64:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MODX", T_OP_MOD,  (yyvsp[-2].node), (yyvsp[0].node));}

    break;

  case 65:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 66:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POS", T_OP_POS, (yyvsp[0].node));
    }

    break;

  case 67:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NEG", T_OP_NEG, (yyvsp[0].node));
    }

    break;

  case 68:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","ADD", T_OP_ADD, (yyvsp[-2].node),(yyvsp[0].node));    }

    break;

  case 69:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS,2, $1, $3);*/  malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MINUS", T_OP_MINUS, (yyvsp[-2].node),(yyvsp[0].node));}

    break;

  case 70:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MUL", T_OP_MUL, (yyvsp[-2].node),(yyvsp[0].node));   }

    break;

  case 71:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","DIV", T_OP_DIV, (yyvsp[-2].node),(yyvsp[0].node));   }

    break;

  case 72:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","REM", T_OP_REM, (yyvsp[-2].node),(yyvsp[0].node));   }

    break;

  case 73:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POW", T_OP_POW, (yyvsp[-2].node),(yyvsp[0].node));   }

    break;

  case 74:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MOD", T_OP_MOD, (yyvsp[-2].node),(yyvsp[0].node));   }

    break;

  case 75:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LE", T_OP_LE, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 76:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LT", T_OP_LT, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 77:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EQ, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","EQ", T_OP_EQ, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 78:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","GE", T_OP_GE, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 79:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","GT", T_OP_GT, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 80:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NE", T_OP_NE, (yyvsp[-2].node),(yyvsp[0].node));     }

    break;

  case 81:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 2, $1, $3); */    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LIKE", T_OP_LIKE, (yyvsp[-2].node),(yyvsp[0].node)); }

    break;

  case 82:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_LIKE, 2, $1, $4);*/ }

    break;

  case 83:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_AND, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","AND", T_OP_AND, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 84:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_OR, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","OR", T_OP_OR, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 85:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT, 1, $2);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT", T_OP_NOT, (yyvsp[0].node));
    }

    break;

  case 86:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NULL", T_OP_IS, (yyvsp[-2].node));
    }

    break;

  case 87:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT_NULL", T_OP_IS_NOT, (yyvsp[-3].node));
    }

    break;

  case 88:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 89:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, (yyvsp[-3].node),(yyvsp[0].node));
    }

    break;

  case 90:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 91:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, (yyvsp[-3].node),(yyvsp[0].node));

    }

    break;

  case 92:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_BTW, 3, $1, $3, $5);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","BTW", T_OP_BTW, (yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 93:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_BTW, 3, $1, $4, $6);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT_BTW", T_OP_NOT_BTW, (yyvsp[-5].node),(yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 94:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IN", T_OP_IN, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 95:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_IN, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT_IN", T_OP_NOT_IN, (yyvsp[-3].node),(yyvsp[0].node));
    }

    break;

  case 96:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_CNN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","CNN", T_OP_CNN, (yyvsp[-2].node),(yyvsp[0].node));
    }

    break;

  case 97:

    {
    	(yyval.node) = (yyvsp[0].node);	
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_OP_IN);
    	(yyval.node)->AddMember("SUB_LINK_TYPE","IN", result->Doc.GetAllocator());
    	SafeAddMember((yyval.node),"SUB_LINK_BODY",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 98:

    { 
    /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $2);*/ 
      merge_nodes((yyval.node), result->Doc.GetAllocator(),T_EXPR_LIST, (yyvsp[-1].node));

    }

    break;

  case 99:

    {
      /*merge_nodes($$, result->malloc_pool_, T_WHEN_LIST, $3);
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_CASE, 3, $2, $$, $4);*/
       // merge_nodes($$, result->Doc.GetAllocator(),T_WHEN_LIST, $3);
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","CASE", T_CASE,  (yyvsp[-3].node), (yyval.node), (yyvsp[-1].node));

    }

    break;

  case 100:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 101:

    { (yyval.node) = NULL; }

    break;

  case 102:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 103:

    {
     /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,  $1, $2);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-1].node), (yyvsp[0].node));

     }

    break;

  case 104:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_THEN, 2, $2, $4);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","THEN", T_THEN,  (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 105:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 106:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_NULL);*/ }

    break;

  case 107:

    {
    	
      if (strcasecmp_((yyvsp[-3].node), "count") != 0)
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
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","STAR", T_FUN_COUNT, node);
      }
    }

    break;

  case 108:

    {
    	        

      if (strcasecmp_((yyvsp[-4].node), "count") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, (yyvsp[-2].node), (yyvsp[-1].node));

      }
      else if (strcasecmp_((yyvsp[-4].node), "sum") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, $3, $4);*/
        
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, (yyvsp[-2].node), (yyvsp[-1].node));

      }
      else if (strcasecmp_((yyvsp[-4].node), "max") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MAX", T_FUN_MAX, (yyvsp[-2].node), (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-4].node), "min") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MIN", T_FUN_MIN, (yyvsp[-2].node), (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-4].node), "avg") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","AVG", T_FUN_AVG, (yyvsp[-2].node), (yyvsp[-1].node));
      }
      else
      {
        yyerror(&(yylsp[-4]), result, "Wrong system function with 'DISTINCT/ALL'!");
        YYABORT;
      }
    }

    break;

  case 109:

    {
      if (strcasecmp_((yyvsp[-3].node), "count") == 0)
      {
       //if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       //{
       //  yyerror(&@1, result, "COUNT function only support 1 parameter!");
       //  YYABORT;
       //}
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, NULL, $3);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-3].node), "sum") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "SUM function only support 1 parameter!");
       //   YYABORT;
       // }
       // /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-3].node), "max") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "MAX function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, NULL, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MAXX", T_FUN_MAX, (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-3].node), "min") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "MIN function only support 1 parameter!");
       //   YYABORT;
       // }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MINX", T_FUN_MIN, (yyvsp[-1].node));
      }
      else if (strcasecmp_((yyvsp[-3].node), "avg") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "AVG function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","AVGX", T_FUN_AVG, (yyvsp[-1].node));
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
         merge_nodes(params, result->Doc.GetAllocator(),T_EXPR_LIST, (yyvsp[-1].node));
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUNX", T_FUN_SYS, (yyvsp[-3].node), params);
      
      }
    }

    break;

  case 110:

    {
      if (strcasecmp_((yyvsp[-5].node), "cast") == 0)
      {
        (*(yyvsp[-1].node))["value_"].Swap((*(yyvsp[-1].node))["type_"]);
        rapidjson::Value tmp(T_INT);
        (*(yyvsp[-1].node))["type_"].Swap(tmp);
        /*ParseNode *params = NULL;*/
        /*malloc_non_terminal_node(params, result->malloc_pool_, T_EXPR_LIST, 2, $3, $5);*/
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, params);*/
         rapidjson::Value *params ;
         malloc_non_terminal_node(&params, result->Doc.GetAllocator(), T_EXPR_LIST,(yyvsp[-3].node),(yyvsp[-1].node));
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CAST", T_FUN_SYS, (yyvsp[-5].node), params);
      }
      else
      {
        yyerror(&(yylsp[-5]), result, "AS support cast function only!");
        YYABORT;
      }
    }

    break;

  case 111:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, (yyvsp[-3].node), (yyvsp[-1].node));

    }

    break;

  case 112:

    {
      if (strcasecmp_((yyvsp[-2].node), "now") == 0 ||
          strcasecmp_((yyvsp[-2].node), "current_time") == 0 ||
          strcasecmp_((yyvsp[-2].node), "current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME", T_CUR_TIME, (yyvsp[-2].node));

      }
      else if (strcasecmp_((yyvsp[-2].node), "strict_current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME_UPS, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME_UPS", T_CUR_TIME_UPS, (yyvsp[-2].node));

      }
      else
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, (yyvsp[-2].node));

      }
      //yyerror(&@1, result, "system/user-define function is not supported yet!");*/
      //YYABORT;
    }

    break;

  case 113:

    {
      (yyval.node) = (yyvsp[-3].node);
      /*$$->children_[0] = $3;*/
     // $$->PushBack($3, result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"WHEN_FUNC_STMT",(yyvsp[-1].node), result->Doc.GetAllocator());
    }

    break;

  case 114:

    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ROW_COUNT, 1, NULL);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","ROW_COUNT", T_ROW_COUNT, NULL);

    }

    break;

  case 119:

    {
       /*malloc_terminal_node($$, result->malloc_pool_, T_ALL);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_ALL);
			  

    }

    break;

  case 120:

    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/          
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_DISTINCT);

    }

    break;

  case 121:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DELETE, 3, $3, $4, $5);*/
      malloc_terminal_node( (yyval.node), result->Doc.GetAllocator(), T_DELETE );
      (yyval.node)->AddMember("OPERATION_NAME","DELETE_STMT", result->Doc.GetAllocator() );
      
     SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[-2].node), result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[-1].node), result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"OPT_WHEN",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 122:

    {
    
         malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_UPDATE);
         (yyval.node)->AddMember("OPERATION_NAME","UPDATE_STMT", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[-4].node), result->Doc.GetAllocator());
     		 SafeAddMember((yyval.node),"SET_LIST",(yyvsp[-2].node), result->Doc.GetAllocator());
     		 SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[-1].node), result->Doc.GetAllocator());
				 SafeAddMember((yyval.node),"WHEN_CLAUSE",(yyvsp[0].node), result->Doc.GetAllocator());
				 SafeAddMember((yyval.node),"HINTS",(yyvsp[-5].node), result->Doc.GetAllocator());
    }

    break;

  case 123:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 124:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1,$3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
 
    }

    break;

  case 125:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_ASSIGN_ITEM, 2, $1, $3);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_ASSIGN_ITEM);
      SafeAddMember((yyval.node),"COLUNM_NAME",(yyvsp[-2].node), result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"EXPR",(yyvsp[0].node), result->Doc.GetAllocator());

    }

    break;

  case 126:

    {
  malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_CREATE_INDEX  );
  (yyval.node)->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if((yyvsp[-10].node)) (yyval.node)->AddMember("CONSTRAINT_TYPE",*(yyvsp[-10].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_NAME",*(yyvsp[-8].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("RELATION_NAME",*(yyvsp[-6].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_TYPE",*(yyvsp[-4].node), result->Doc.GetAllocator() ); 
  (yyval.node)->AddMember("COLUMN_LIST",*(yyvsp[-2].node), result->Doc.GetAllocator() ); 
  if((yyvsp[0].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[0].node), result->Doc.GetAllocator() ); 
   // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_CREATE_INDEX,$2, $4, $6, index_column_list,table_options);
   //malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_UNIQUE);  
   //$$->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
}

    break;

  case 127:

    {
	malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_CREATE_INDEX  );
  (yyval.node)->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if((yyvsp[-8].node)) (yyval.node)->AddMember("CONSTRAINT_TYPE",*(yyvsp[-8].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_NAME",*(yyvsp[-6].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("RELATION_NAME",*(yyvsp[-4].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("COLUMN_LIST",*(yyvsp[-2].node), result->Doc.GetAllocator() ); 
  if((yyvsp[0].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[0].node), result->Doc.GetAllocator() ); 

}

    break;

  case 128:

    {
		
		  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_UNIQUE); 
		  (yyval.node)->AddMember("str_value_","UNIQUE", result->Doc.GetAllocator() ); 
	}

    break;

  case 129:

    {  
		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_FULLTEXT); 
		(yyval.node)->AddMember("str_value_","FULLTEXT", result->Doc.GetAllocator() ); 

	}

    break;

  case 130:

    {  
		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_SPATIAL); 
		(yyval.node)->AddMember("str_value_","SPATIAL", result->Doc.GetAllocator() ); 

	}

    break;

  case 131:

    {
		(yyval.node) = NULL;
	}

    break;

  case 132:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_HASH);
		 (yyval.node)->AddMember("str_value_","HASH", result->Doc.GetAllocator() );
	}

    break;

  case 133:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_BTREE); 
		 (yyval.node)->AddMember("str_value_","BTREE", result->Doc.GetAllocator() );
	}

    break;

  case 134:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_SKIPLIST); 
		 (yyval.node)->AddMember("str_value_","SKIPLIST", result->Doc.GetAllocator() );
	}

    break;

  case 135:

    { (yyval.node) = NULL; }

    break;

  case 136:

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
    
  malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_CREATE_TABLE  );
  (yyval.node)->AddMember("OPERATION_NAME","CREATE_TABLE", result->Doc.GetAllocator() );
  if((yyvsp[-5].node)) (yyval.node)->AddMember("IS_EXISTS",*(yyvsp[-5].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[-4].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("TABLE_ELEMENT",*(yyvsp[-2].node), result->Doc.GetAllocator() );
  if((yyvsp[0].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[0].node), result->Doc.GetAllocator() ); 
    
    
    }

    break;

  case 137:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_IF_NOT_EXISTS);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_IF_NOT_EXISTS);
      (yyval.node)->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    }

    break;

  case 138:

    { (yyval.node) = NULL; }

    break;

  case 139:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 140:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 141:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 142:

    {
      /*ParseNode* col_list= NULL;*/
      /*merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, $4);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIMARY_KEY, 1, col_list);*/
         rapidjson::Value *col_list ;
         merge_nodes(col_list, result->Doc.GetAllocator(),  T_COLUMN_LIST,(yyvsp[-1].node));
         malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_PRIMARY_KEY, col_list);

    }

    break;

  case 143:

    {
      /*ParseNode *attributes = NULL;*/
      /*merge_nodes(attributes, result->malloc_pool_, T_COLUMN_ATTRIBUTES, $3);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DEFINITION, 3, $1, $2, attributes);*/
 
			   rapidjson::Value *attributes;
			   merge_nodes(attributes, result->Doc.GetAllocator(),  T_COLUMN_ATTRIBUTES,(yyvsp[0].node));
         malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_COLUMN_DEFINITION, (yyvsp[-2].node), (yyvsp[-1].node), attributes);
    
    }

    break;

  case 144:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT );*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
      (yyval.node)->AddMember("str_value_","TINYINT", result->Doc.GetAllocator() );

    }

    break;

  case 145:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_SHORT);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_SHORT);
      (yyval.node)->AddMember("str_value_","SMALLINT", result->Doc.GetAllocator() );

    }

    break;

  case 146:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
      (yyval.node)->AddMember("str_value_","INT", result->Doc.GetAllocator() );
    }

    break;

  case 147:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT);*/ 
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
       (yyval.node)->AddMember("str_value_","INT", result->Doc.GetAllocator() );

    }

    break;

  case 148:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_LONGLONG);*/
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_LONGLONG);
       (yyval.node)->AddMember("str_value_","BIGINT", result->Doc.GetAllocator() );

     }

    break;

  case 149:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        (yyval.node)->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
}
      else{
        /*merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        (yyval.node)->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
 }
      yyerror(&(yylsp[-1]), result, "DECIMAL type is not supported");
      YYABORT;
    }

    break;

  case 150:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);}
      else{
       /* merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
     merge_nodes((yyval.node), result->Doc.GetAllocator(),T_TYPE_DECIMAL, (yyvsp[0].node));}
     (yyval.node)->AddMember("str_value_","NUMERIC", result->Doc.GetAllocator() );
       
      yyerror(&(yylsp[-1]), result, "NUMERIC type is not supported");
      YYABORT;
    }

    break;

  case 151:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_BOOLEAN );*/ 
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_BOOLEAN);
    (yyval.node)->AddMember("str_value_","BOOLEAN", result->Doc.GetAllocator() );

    }

    break;

  case 152:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_FLOAT, 1, $2);*/ 
        malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_FLOAT,(yyvsp[0].node));
        (yyval.node)->AddMember("str_value_","FLOAT", result->Doc.GetAllocator() );

    }

    break;

  case 153:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DOUBLE);
    (yyval.node)->AddMember("str_value_","REAL", result->Doc.GetAllocator() );

     }

    break;

  case 154:

    {
      (void)((yyvsp[0].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DOUBLE);
       (yyval.node)->AddMember("str_value_","DOUBLE", result->Doc.GetAllocator() );
    }

    break;

  case 155:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP, 1, $2);*/
     malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}
     (yyval.node)->AddMember("str_value_","TIMESTAMP", result->Doc.GetAllocator() );
 
    }

    break;

  case 156:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
         malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);
         (yyval.node)->AddMember("str_value_","DATETIME", result->Doc.GetAllocator() );

     }

    break;

  case 157:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
     malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER,(yyvsp[0].node));
     }
     (yyval.node)->AddMember("str_value_","CHARACTER", result->Doc.GetAllocator() );
  
    }

    break;

  case 158:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER);
      (yyval.node)->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
      }
   
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER,(yyvsp[0].node)); 
      (yyval.node)->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
       }
    }

    break;

  case 159:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR);
      (yyval.node)->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
      }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR,(yyvsp[0].node));
      (yyval.node)->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
         }
    }

    break;

  case 160:

    {
      if ((yyvsp[0].node) == NULL){
        /* malloc_terminal_node(result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR); 
      (yyval.node)->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR, (yyvsp[0].node));
      (yyval.node)->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         } 
  
    }

    break;

  case 161:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CREATETIME);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CREATETIME);  
    (yyval.node)->AddMember("str_value_","CREATETIME", result->Doc.GetAllocator() );  
     }

    break;

  case 162:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_MODIFYTIME);*/ 
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_MODIFYTIME);    
    (yyval.node)->AddMember("str_value_","MODIFYTIME", result->Doc.GetAllocator() ); 
    }

    break;

  case 163:

    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DATE);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DATE);     
    (yyval.node)->AddMember("str_value_","DATE", result->Doc.GetAllocator() );
      yyerror(&(yylsp[0]), result, "DATE type is not supported");
      YYABORT;
    }

    break;

  case 164:

    {
      if ((yyvsp[0].node) == NULL){
        /*malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIME);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIME);    } 
      else{       /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIME, 1, $2);*/
    malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_TIME,(yyvsp[0].node));     }
    (yyval.node)->AddMember("str_value_","TIME", result->Doc.GetAllocator() );
      yyerror(&(yylsp[-1]), result, "TIME type is not supported");
      YYABORT;
    }

    break;

  case 165:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,$2, $4);      
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-3].node), (yyvsp[-1].node));
     (yyval.node)->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    }

    break;

  case 166:

    { (yyval.node) = (yyvsp[-1].node); }

    break;

  case 167:

    { (yyval.node) = NULL; }

    break;

  case 168:

    { (yyval.node) = (yyvsp[-1].node); }

    break;

  case 169:

    { (yyval.node) = NULL; }

    break;

  case 170:

    { (yyval.node) = NULL; }

    break;

  case 171:

    { (yyval.node) = NULL; }

    break;

  case 172:

    { (yyval.node) = (yyvsp[-1].node); }

    break;

  case 173:

    { (yyval.node) = NULL; }

    break;

  case 174:

    { (yyval.node) = (yyvsp[-1].node); }

    break;

  case 175:

    { (yyval.node) = NULL; }

    break;

  case 176:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $2);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-1].node), (yyvsp[0].node));
    }

    break;

  case 177:

    { (yyval.node) = NULL; }

    break;

  case 178:

    {
      (void)((yyvsp[0].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_NOT_NULL);
    }

    break;

  case 179:

    {
      (void)((yyvsp[0].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_NULL);

    }

    break;

  case 180:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $2);*/ 
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CONSTR_DEFAULT,(yyvsp[0].node));

    }

    break;

  case 181:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_AUTO_INCREMENT);*/ 
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_AUTO_INCREMENT);

    }

    break;

  case 182:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_PRIMARY_KEY);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_PRIMARY_KEY);
     }

    break;

  case 183:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 184:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
   //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE,$1, $3);
   malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 185:

    {
      (yyval.node) = NULL;
    }

    break;

  case 186:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_JOIN_INFO, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_JOIN_INFO, (yyvsp[0].node));
   
    }

    break;

  case 187:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXPIRE_INFO, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_EXPIRE_INFO, (yyvsp[0].node));
  
    }

    break;

  case 188:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_TABLET_MAX_SIZE, (yyvsp[0].node));
 
    }

    break;

  case 189:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_EXTERN_SIZE);
   		if((yyvsp[0].node))(yyval.node)->AddMember("EXTERN_SIZE",*(yyvsp[0].node), result->Doc.GetAllocator() );
    }

    break;

  case 190:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
	     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_SKIP_LEVEL);
   		if((yyvsp[0].node))(yyval.node)->AddMember("SKIP_LEVEL",*(yyvsp[0].node), result->Doc.GetAllocator() ); 
    }

    break;

  case 191:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_BLOCK_SIZE, 1, $3);*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_TABLET_BLOCK_SIZE);
   	 if((yyvsp[0].node))(yyval.node)->AddMember("TABLET_BLOCK_SIZE",*(yyvsp[0].node), result->Doc.GetAllocator() );
    }

    break;

  case 192:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_ID, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_TABLET_ID, (yyvsp[0].node));
 
    }

    break;

  case 193:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_REPLICA_NUM, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_REPLICA_NUM, (yyvsp[0].node));
 
    }

    break;

  case 194:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMPRESS_METHOD, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_COMPRESS_METHOD, (yyvsp[0].node));
  
    }

    break;

  case 195:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_USE_BLOOM_FILTER, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_USE_BLOOM_FILTER, (yyvsp[0].node));
   
    }

    break;

  case 196:

    {
      (void)((yyvsp[-1].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSISTENT_MODE);*/
       /*$$->value_ = 1;*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSISTENT_MODE);
    rapidjson::Value val_val_(1);
    (yyval.node)->AddMember("value_", val_val_, result->Doc.GetAllocator());
    
    }

    break;

  case 197:

    {
      (void)((yyvsp[-1].node)); /*  make bison mute*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMMENT, 1, $3);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_COMMENT,(yyvsp[0].node));

    }

    break;

  case 198:

    { (yyval.node) = NULL; }

    break;

  case 199:

    { (yyval.node) = NULL; }

    break;

  case 200:

    {
      /*ParseNode *tables = NULL;
      merge_nodes(tables, result->malloc_pool_, T_TABLE_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_DROP_TABLE, 2, $3, tables);
      */
      
      rapidjson::Value *tables ;
      merge_nodes(tables, result->Doc.GetAllocator(),T_TABLE_LIST, (yyvsp[0].node));
		  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_DROP_TABLE);      
      (yyval.node)->AddMember("OPERATION_NAME","DROP_TABLE", result->Doc.GetAllocator() );
      if((yyvsp[-1].node))(yyval.node)->AddMember("IF_EXISTS",*(yyvsp[-1].node), result->Doc.GetAllocator() );
			(yyval.node)->AddMember("TABLE_LIST",*tables, result->Doc.GetAllocator() );
   
    }

    break;

  case 201:

    { (yyval.node) = NULL; }

    break;

  case 202:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_IF_EXISTS);*/ 
   malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_IF_EXISTS);   }

    break;

  case 203:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 204:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
  // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);  
  malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));    
  
    }

    break;

  case 205:

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
      merge_nodes(val_list, result->Doc.GetAllocator(),T_VALUE_LIST, (yyvsp[-1].node));
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_INSERT,$3, $4,val_list,NULL,$1,$7);  
         malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INSERT);
         (yyval.node)->AddMember("OPERATION_NAME","INSERT_TABLE", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[-4].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"OPT_INSERT_COLUMNS",(yyvsp[-3].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"VALUE_LIST", val_list, result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[-6].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"OPT_WHEN",(yyvsp[0].node), result->Doc.GetAllocator());

    }

    break;

  case 206:

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
         malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INSERT);  
         (yyval.node)->AddMember("OPERATION_NAME","INSERT_SELECT_STMT", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[-1].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"SELECT_STMT",(yyvsp[0].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[-3].node), result->Doc.GetAllocator());

    }

    break;

  case 207:

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
         merge_nodes(col_list,result->Doc.GetAllocator(), T_COLUMN_LIST, (yyvsp[-2].node));
         malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INSERT);  
         (yyval.node)->AddMember("OPERATION_NAME","INSERT_SELECT_STMT", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[-4].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"COLUMNS_LIST",col_list, result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"SELECT_STMT",(yyvsp[0].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[-6].node), result->Doc.GetAllocator());
    }

    break;

  case 208:

    { (yyval.node) = NULL; }

    break;

  case 209:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 210:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;
      */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
      rapidjson::Value tmp(1);
      SafeAddMember((yyval.node),"value_",&tmp, result->Doc.GetAllocator());

    }

    break;

  case 211:

    {
     /*
      malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;
      */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
      rapidjson::Value tmp(0);      
      SafeAddMember((yyval.node),"value_",&tmp, result->Doc.GetAllocator());
    }

    break;

  case 212:

    {
       /* merge_nodes($$, result->malloc_pool_, T_COLUMN_LIST, $2);*/
       merge_nodes((yyval.node),result->Doc.GetAllocator(),T_BOOL,(yyvsp[-1].node));
    }

    break;

  case 213:

    { (yyval.node) = NULL; }

    break;

  case 214:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 215:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 216:

    {
    /*  merge_nodes($$, result->malloc_pool_, T_VALUE_VECTOR, $2);*/
    merge_nodes((yyval.node),result->Doc.GetAllocator(),T_VALUE_VECTOR,(yyvsp[-1].node));
    }

    break;

  case 217:

    {
  /*  merge_nodes($4, result->malloc_pool_, T_VALUE_VECTOR, $4);*/
  /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $4);*/
  rapidjson::Value  *insert_vals  ;
  merge_nodes(insert_vals,result->Doc.GetAllocator(),T_VALUE_VECTOR,(yyvsp[-1].node));
  //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, insert_vals);
  malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-4].node), insert_vals);
  }

    break;

  case 218:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 219:

    {
   /*   malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
 
    }

    break;

  case 220:

    {
     /* $$ = $1;
      $$->children_[14] = $2;
      if ($$->children_[12] == NULL && $2 != NULL)
      {
        malloc_terminal_node($$->children_[12], result->malloc_pool_, T_BOOL);
        $$->children_[12]->value_ = 1;
      }
      */
       (yyval.node) = (yyvsp[-1].node);
       (yyval.node)->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

       SafeAddMember((yyval.node),"HINTS",(yyvsp[0].node) , result->Doc.GetAllocator());
       if((yyval.node)->HasMember("limit") && (yyvsp[0].node) != NULL)
       	{
       		(*(yyval.node))["limit"].SetObject().AddMember("value_", rapidjson::Value(1), result->Doc.GetAllocator());
       	}
    }

    break;

  case 221:

    { 
    	(yyval.node) = (yyvsp[0].node); 
      (yyval.node)->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

    	//malloc_terminal_node($$,result->Doc.GetAllocator(),T_SUB_SELECT);
			//SafeAddMember($$,"SUB_SELECT",$1, result->Doc.GetAllocator());	
    }

    break;

  case 222:

    { 
        malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  	SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[-1].node) , result->Doc.GetAllocator());
    	  //$$ = $2; 
    	
    	}

    break;

  case 223:

    { 
  	  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[-1].node) , result->Doc.GetAllocator());
  	  //$$ = $2; 
  	
  	}

    break;

  case 224:

    {
      (yyval.node)= (yyvsp[0].node);
    }

    break;

  case 225:

    {
      (yyval.node) = (yyvsp[-1].node);
      //$$->children_[12] = $2;
      SafeAddMember((yyval.node),"limit",(yyvsp[0].node) , result->Doc.GetAllocator());

    }

    break;

  case 226:

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
      	select.CopyFrom(*(yyvsp[-2].node),result->Doc.GetAllocator());
      	if (select.HasMember("ORDER_BY_CLAUSE") && (yyvsp[-1].node) ) {select.RemoveMember("ORDER_BY_CLAUSE");}select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[-1].node),result->Doc.GetAllocator());
      if((yyvsp[0].node))select.AddMember("limit",*(yyvsp[0].node),result->Doc.GetAllocator());
     // 	if($3)select.AddMember("ORDER_BY_CLAUSE",*$3,result->Doc.GetAllocator());
      (yyval.node)->Swap(select);
    }

    break;

  case 227:

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
      select.CopyFrom(*(yyvsp[-3].node),result->Doc.GetAllocator());

      if ((yyvsp[-2].node))
      {
      	if (select.HasMember("ORDER_BY_CLAUSE") /*&& $2*/) {select.RemoveMember("ORDER_BY_CLAUSE");select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[-2].node),result->Doc.GetAllocator());}
      	else if((yyvsp[-2].node)) select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[-2].node),result->Doc.GetAllocator());
      }	
     if ( select.HasMember("limit") /*&& $3*/ ){select.RemoveMember("limit");}
     	select.AddMember("limit",*(yyvsp[-1].node),result->Doc.GetAllocator());
     if ( select.HasMember("for_update") )	{select.RemoveMember("for_update");} 
     if((yyvsp[0].node))select.AddMember("for_update",*(yyvsp[0].node),result->Doc.GetAllocator());
     (yyval.node)->Swap(select);
    }

    break;

  case 228:

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
       merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[-1].node));
      
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);                   
       SafeAddMember((yyval.node),"DISTINCT",(yyvsp[-2].node),result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"LIMIT",(yyvsp[0].node),result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"HINTS",(yyvsp[-3].node),result->Doc.GetAllocator());
           }

    break;

  case 229:

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
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[-4].node));
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"DISTINCT",(yyvsp[-5].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[-1].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"LIMIT",(yyvsp[0].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"HINTS",(yyvsp[-6].node),result->Doc.GetAllocator());
    }

    break;

  case 230:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 231:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 232:

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
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[-5].node));
      rapidjson::Value  *from_list    ;
      merge_nodes(from_list,result->Doc.GetAllocator(),T_FROM_LIST   ,(yyvsp[-3].node));
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"DISTINCT",(yyvsp[-6].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FROM_CLAUSE",from_list,result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[-2].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"GROUP_BY_CLAUSE",(yyvsp[-1].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"HAVING_CLAUSE",(yyvsp[0].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"HINTS",(yyvsp[-7].node),result->Doc.GetAllocator());
    }

    break;

  case 233:

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
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      
      SafeAddMember((yyval.node),"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[-1].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[-3].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[0].node),result->Doc.GetAllocator());
    }

    break;

  case 234:

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
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[-1].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[-3].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[0].node),result->Doc.GetAllocator());
    }

    break;

  case 235:

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
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"SET_OPERATION",set_op,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[-1].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[-3].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[0].node),result->Doc.GetAllocator());
    }

    break;

  case 236:

    {(yyval.node) = NULL;}

    break;

  case 237:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 238:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 2, $3, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_WHERE_CLAUSE, (yyvsp[0].node), (yyvsp[-1].node));
    }

    break;

  case 239:

    {
      if ((*(yyvsp[-2].node))["type_"].GetInt()== T_QUESTIONMARK && (*(yyvsp[0].node))["type_"].GetInt()== T_QUESTIONMARK)
      {
       /* $4->value_++;*/
       int i = ((*(yyvsp[0].node))["value_"]).GetInt();++i;
       rapidjson::Value tmp(i);
       (*(yyvsp[0].node))["value_"].Swap(tmp);
       
      }
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, $4);*/
     	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_WHERE_CLAUSE, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 240:

    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
      malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
      if ((*(yyvsp[-2].node))["type_"].GetInt()  == T_QUESTIONMARK && (*(yyvsp[0].node))["type_"].GetInt() == T_QUESTIONMARK )
      	{
      		int i =(*(yyvsp[0].node))["value_"].GetInt();
      		rapidjson::Value tmp(++i);
      		(*(yyvsp[0].node))["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[0].node), (yyvsp[-2].node));
	
    }

    break;

  case 241:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, NULL);*/
   		malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[0].node), NULL);
 
    }

    break;

  case 242:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, NULL, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, NULL, (yyvsp[0].node));

    }

    break;

  case 243:

    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
    	malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
       if ((*(yyvsp[-2].node))["type_"].GetInt()  == T_QUESTIONMARK && (*(yyvsp[0].node))["type_"].GetInt() == T_QUESTIONMARK )
      	{
      			int i = (*(yyvsp[0].node))["value_"].GetInt();
      			rapidjson::Value tmp(++i);
      		  (*(yyvsp[0].node))["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[0].node), (yyvsp[-2].node));	
    }

    break;

  case 244:

    {
      (yyval.node) = NULL;
    }

    break;

  case 245:

    {
     /* if ($2)
      {
        merge_nodes($$, result->malloc_pool_, T_HINT_OPTION_LIST, $2);
      }
      else
      {
        $$ = NULL;
      }*/
      if ((yyvsp[-1].node))
      {
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_HINT_OPTION_LIST, (yyvsp[-1].node));	
      }
      else
      {
        (yyval.node) = NULL;
      }
    }

    break;

  case 246:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 247:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);	
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
 
    }

    break;

  case 248:

    {
      (yyval.node) = NULL;
    }

    break;

  case 249:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 250:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $2);	
        malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-1].node), (yyvsp[0].node));

    }

    break;

  case 251:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_READ_STATIC);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_READ_STATIC);	

    }

    break;

  case 252:

    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_HOTSPOT);*/
        malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_HOTSPOT);	

    }

    break;

  case 253:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_READ_CONSISTENCY);
      $$->value_ = $3;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_READ_CONSISTENCY);	
      rapidjson::Value tmp;
      	tmp.SetInt((yyvsp[-1].ival));
      (*(yyval.node))["value_"].Swap(tmp );

    }

    break;

  case 254:

    {
      (yyval.node) = (yyvsp[-1].node);
    }

    break;

  case 255:

    {
      (yyval.node) = (yyvsp[-1].node);
    }

    break;

  case 256:

    {
      (yyval.node) = NULL;
    }

    break;

  case 257:

    {
    (yyval.ival) = 3;
  }

    break;

  case 258:

    {
    (yyval.ival) = 4;
  }

    break;

  case 259:

    {
    (yyval.ival) = 1;
  }

    break;

  case 260:

    {
    (yyval.ival) = 2;
  }

    break;

  case 261:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 262:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 263:

    { (yyval.node) = NULL; }

    break;

  case 264:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 265:

    { (yyval.node) = NULL; }

    break;

  case 266:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
    rapidjson::Value tmp(1);
    (*(yyval.node))["value_"].Swap(tmp );
    }

    break;

  case 267:

    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $1, $3);*/
      rapidjson::Value *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(0);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 268:

    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(0);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[-2].node), (yyvsp[0].node)); 
    }

    break;

  case 269:

    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 1;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[-2].node), (yyvsp[0].node));   
    }

    break;

  case 270:

    {
     /* ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 2;
      malloc_non_terminal_node($$, result->malloc_pool_, T_EXPR_LIST, 3, default_type, $2, $4);*/
      rapidjson::Value  *default_type ;
      malloc_terminal_node(default_type,result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*default_type)["value_"].Swap(tmp);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[-2].node), (yyvsp[0].node));     
    }

    break;

  case 271:

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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[0].node));     

    }

    break;

  case 272:

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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[0].node));     
  
    }

    break;

  case 273:

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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[0].node));     
  
    }

    break;

  case 274:

    { (yyval.node) = NULL; }

    break;

  case 275:

    {
    /*   merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $3);*/
    merge_nodes((yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,(yyvsp[0].node));
    }

    break;

  case 276:

    { (yyval.node) = (yyvsp[0].node);}

    break;

  case 277:

    { (yyval.node) = NULL; }

    break;

  case 278:

    {
   /*   merge_nodes($$, result->malloc_pool_, T_SORT_LIST, $3);*/
        merge_nodes((yyval.node),result->Doc.GetAllocator(),T_SORT_LIST,(yyvsp[0].node));
     //    malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_LIST);  
      //   SafeAddMember($$,"ORDER_BY_CLAUSE",$3,result->Doc.GetAllocator());
    cout<<"T_SORT_LIST"<<endl;
      }

    break;

  case 279:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 280:

    { /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    	//   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1,$3);
    	malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    	}

    break;

  case 281:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_SORT_KEY, 2, $1, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SORT_KEY, (yyvsp[-1].node),(yyvsp[0].node));

    }

    break;

  case 282:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_ASC);
	
    	}

    break;

  case 283:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_ASC);
	
    	}

    break;

  case 284:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_DESC); */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_DESC);
	
    	}

    break;

  case 285:

    { (yyval.node) = 0; }

    break;

  case 286:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 287:

    {
      (yyval.node) = NULL;
    }

    break;

  case 288:

    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_ALL); */
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_ALL);

    }

    break;

  case 289:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_DISTINCT);

    }

    break;

  case 290:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, $1);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PROJECT_STRING);
      SafeAddMember((yyval.node),"PROJECT",       (yyvsp[0].node) , result->Doc.GetAllocator());
       // dup_expr_string
      
    }

    break;

  case 291:

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
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_PROJECT_STRING);
       SafeAddMember((yyval.node),"PROJECT",       (yyvsp[-1].node) , result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"PROJECT_ALIAS", (yyvsp[0].node), result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    }

    break;

  case 292:

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
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_PROJECT_STRING);
     SafeAddMember((yyval.node),"PROJECT",      (yyvsp[-2].node) , result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"PROJECT_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    }

    break;

  case 293:

    {
    /*  ParseNode* star_node = NULL;
      malloc_terminal_node(star_node, result->malloc_pool_, T_STAR);
      malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, star_node);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);*/
      rapidjson::Value *star_node ;
      malloc_terminal_node(star_node,result->Doc.GetAllocator(),T_STAR);
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PROJECT_STRING);
      SafeAddMember((yyval.node),"PROJECT",star_node, result->Doc.GetAllocator());

      // dup_expr_string
    }

    break;

  case 294:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 295:

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
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 296:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 297:

    {/* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
		malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    	}

    break;

  case 298:

    {
     // $$ = $1;
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
      SafeAddMember((yyval.node),"RELATION",(yyvsp[0].node), result->Doc.GetAllocator());

    }

    break;

  case 299:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[-2].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"TABLE_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 300:

    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    //  malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[-1].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"RELATION_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 301:

    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[-2].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"SUB_SELECT_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 302:

    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[-1].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"SUB_SELECT_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());
    }

    break;

  case 303:

    {
    	(yyval.node) = (yyvsp[0].node);
    }

    break;

  case 304:

    {
    /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $2, $5);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $2, $5);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[-3].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"RELATION_ALIAS",(yyvsp[0].node), result->Doc.GetAllocator());    	
    	
    	yyerror(&(yylsp[-4]), result, "qualied joined table can not be aliased!");
      YYABORT;
    }

    break;

  case 305:

    {
    	 (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 306:

    {
    	(yyval.node) = (yyvsp[-1].node);
    }

    break;

  case 307:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, $2, $1, $4, $6);*/
     rapidjson::Value  *node ;
     malloc_terminal_node(node,result->Doc.GetAllocator(), T_JOIN_CONDITION);
     SafeAddMember(node,"JOIN_CONDITION",(yyvsp[0].node), result->Doc.GetAllocator());
     malloc_non_terminal_node_with_type(&(yyval.node),result->Doc.GetAllocator(), "JOIN_TYPE",(*(yyvsp[-4].node))["JOIN_TYPE"].GetString(), T_JOINED_TABLE, (yyvsp[-5].node), (yyvsp[-2].node), node);

    }

    break;

  case 308:

    {
     /* ParseNode* node = NULL;*/
     /* malloc_terminal_node(node, result->malloc_pool_, T_JOIN_INNER);*/
    /*	malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, node, $1, $3, $5);*/
    rapidjson::Value  *node ;
    malloc_terminal_node(node,result->Doc.GetAllocator(), T_JOIN_INNER);
     	rapidjson::Value  *node2 ;
     	malloc_terminal_node(node2,result->Doc.GetAllocator(), T_JOIN_CONDITION);
     	SafeAddMember(node2,"JOIN_CONDITION",(yyvsp[0].node), result->Doc.GetAllocator());
    malloc_non_terminal_node_with_type(&(yyval.node),result->Doc.GetAllocator(), "JOIN_TYPE","INNER_JOIN" ,T_JOINED_TABLE,  node, (yyvsp[-4].node), (yyvsp[-2].node), node2);
    }

    break;

  case 309:

    {
      /* make bison mute*/
      (void)((yyvsp[0].node));
      /*malloc_terminal_node($$, result->malloc_pool_, T_JOIN_FULL);*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_FULL);
     (yyval.node)->AddMember("JOIN_TYPE","FULL_JOIN", result->Doc.GetAllocator());    	

    }

    break;

  case 310:

    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_LEFT);*/
       (void)((yyvsp[0].node));
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_LEFT);
  	 	 (yyval.node)->AddMember("JOIN_TYPE","LEFT_JOIN", result->Doc.GetAllocator());
    }

    break;

  case 311:

    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_RIGHT);*/
       (void)((yyvsp[0].node));
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_RIGHT);
       (yyval.node)->AddMember("JOIN_TYPE","RIGHT_JOIN", result->Doc.GetAllocator());
    }

    break;

  case 312:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_JOIN_INNER);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_INNER);
      (yyval.node)->AddMember("JOIN_TYPE","INNER_JOIN", result->Doc.GetAllocator());

    }

    break;

  case 313:

    { (yyval.node) = NULL; }

    break;

  case 314:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_EXPLAIN, 1, $3);
      $$->value_ = ($2 ? 1 : 0); positive: verbose */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_EXPLAIN);
      (yyval.node)->AddMember("OPERATION_NAME","EXPLAIN", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("STMT",*(yyvsp[0].node),result->Doc.GetAllocator());
      //rapidjson::Value tmp($2 ? 1 : 0);
      //(*$$)["value_"].Swap(tmp);
 
    }

    break;

  case 315:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 316:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 317:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 318:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 319:

    { (yyval.node) = (rapidjson::Value*)1; }

    break;

  case 320:

    { (yyval.node) = NULL; }

    break;

  case 321:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLES, 1, $3malloc_*/ 
    	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLES, (yyvsp[0].node));
    	(yyval.node)->AddMember("OPERATION_NAME","COMMAND", result->Doc.GetAllocator() );
    	}

    break;

  case 322:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
    	  malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS, (yyvsp[-1].node),(yyvsp[0].node));
    	}

    break;

  case 323:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS, (yyvsp[-1].node),(yyvsp[0].node));
	
    	}

    break;

  case 324:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLE_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, (yyvsp[0].node));

    	
    	}

    break;

  case 325:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_SERVER_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, (yyvsp[0].node));
	
    	}

    break;

  case 326:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_VARIABLES, 1, $4);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_VARIABLES, (yyvsp[0].node));
      //$$->value_ = $2;
       rapidjson::Value tmp((yyvsp[-2].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 327:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_SCHEMA);*/ 
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SHOW_SCHEMA);	
    	}

    break;

  case 328:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_CREATE_TABLE, 1, $4);*/ 
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_CREATE_TABLE,(yyvsp[0].node));		
    	}

    break;

  case 329:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/ 
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS,(yyvsp[-1].node),(yyvsp[0].node));			
    	}

    break;

  case 330:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS,(yyvsp[-1].node),(yyvsp[0].node));			
	
    	 }

    break;

  case 331:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_WARNINGS, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_WARNINGS,(yyvsp[0].node));			
 
    }

    break;

  case 332:

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
      if ((*(yyvsp[-1].node))["type_"].GetInt()!= T_FUN_COUNT)
      {
        yyerror(&(yylsp[-2]), result, "Only COUNT(*) function is supported in SHOW WARNINGS statement!");
        YYABORT;  
      }
       else
      {
      	rapidjson::Value tmp(1);
        (*(yyval.node))["value_"].Swap(tmp);
      }
    }

    break;

  case 333:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_GRANTS, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_GRANTS,(yyvsp[0].node));
    }

    break;

  case 334:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_PARAMETERS, 1, $3*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_PARAMETERS,(yyvsp[0].node));
  
    }

    break;

  case 335:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_PROCESSLIST*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_SHOW_PROCESSLIST);
      /*$$->value_ = $2;*/
       
       rapidjson::Value tmp((yyvsp[-1].ival));
      (*(yyval.node))["value_"].Swap(tmp);
      }

    break;

  case 336:

    {
      /*if ($2->value_ < 0 || $4->value_ < 0)
      {
        yyerror(&@1, result, "OFFSET/COUNT must not be less than 0!"
        YYABORT;
      }
      malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, $2, $4malloc_*/
      if ((*(yyvsp[-2].node))["value_"].GetInt()< 0 || (*(yyvsp[0].node))["value_"].GetInt() < 0)
      {
        yyerror(&(yylsp[-3]), result, "OFFSET/COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_LIMIT,  (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 337:

    {
       /*if ($2->value_ < 0)
      {
        yyerror(&@1, result, "COUNT must not be less than 0!");
        YYABORT;
      }
     malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, NULL, $2);*/
     if ((*(yyvsp[0].node))["value_"].GetInt()< 0 )
     	{
     		yyerror(&(yylsp[-1]), result, "COUNT must not be less than 0!");
        YYABORT;
     	}
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_LIMIT,  NULL, (yyvsp[0].node));
 
    }

    break;

  case 338:

    { (yyval.node) = NULL; }

    break;

  case 339:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 340:

    { (yyval.node) = NULL; }

    break;

  case 341:

    { (yyval.node) = NULL; }

    break;

  case 342:

    { (yyval.ival) = 1; }

    break;

  case 343:

    { (yyval.ival) = 0; }

    break;

  case 344:

    { (yyval.ival) = 0; }

    break;

  case 345:

    { (yyval.node) = NULL; }

    break;

  case 346:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $2);*/ 
        malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_LIKE, (yyvsp[0].node));
	
    	}

    break;

  case 347:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 1, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_WHERE_CLAUSE, (yyvsp[0].node));
	
    }

    break;

  case 348:

    { (yyval.node) = NULL; }

    break;

  case 349:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $1);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_LIKE, (yyvsp[0].node));
	
    }

    break;

  case 350:

    { (yyval.ival) = 0; }

    break;

  case 351:

    { (yyval.ival) = 1; }

    break;

  case 352:

    {
       /* merge_nodes($$, result->malloc_pool_, T_CREATE_USER, $3);*/
      // merge_nodes($$,result->Doc.GetAllocator(),T_CREATE_USER, $3);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CREATE_USER,(yyvsp[0].node));
      (yyval.node)->AddMember("OPERATION_NAME","CREATE_USER", result->Doc.GetAllocator() );
    }

    break;

  case 353:

    {
    	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CREATE_USER,(yyvsp[0].node));
      (yyval.node)->AddMember("OPERATION_NAME","CREATE_USER", result->Doc.GetAllocator() );
    	
    }

    break;

  case 354:

    {
        (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 355:

    {
       /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
       //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
       malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 356:

    {
      /*  malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_USER_SPEC, 2, $1, $4);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CREATE_USER_SPEC);
      (yyval.node)->AddMember("USER_NAME",*(yyvsp[-3].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("PASSWORD", *(yyvsp[0].node), result->Doc.GetAllocator() );
     
    }

    break;

  case 357:

    {
        (yyval.node) = (yyvsp[0].node);
     // malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
     // SafeAddMember($$,"USER_NAME",$1, result->Doc.GetAllocator());
    }

    break;

  case 358:

    {
        (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 359:

    {
       /* merge_nodes($$, result->malloc_pool_, T_DROP_USER, $3);*/
        merge_nodes((yyval.node),result->Doc.GetAllocator(),T_DROP_USER, (yyvsp[0].node));
				(yyval.node)->AddMember("OPERATION_NAME","DROP_USER", result->Doc.GetAllocator() );

    }

    break;

  case 360:

    {
    	printf(" user \n");
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 361:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 362:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $5);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SET_PASSWORD);
    (yyval.node)->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
    (yyval.node)->AddMember("USER_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("PASSWORD",*(yyvsp[0].node), result->Doc.GetAllocator() );



    }

    break;

  case 363:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $6);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SET_PASSWORD);
      (yyval.node)->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("USER_NAME",*(yyvsp[-3].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("PASSWORD",*(yyvsp[0].node), result->Doc.GetAllocator() );
      
      

    }

    break;

  case 364:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 365:

    {
      (yyval.node) = NULL;
    }

    break;

  case 366:

    {
      /*merge_nodes($$, result->malloc_pool_, T_RENAME_USER, $3);*/
     // merge_nodes($$,result->Doc.GetAllocator(),T_RENAME_USER, $3);
      
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_RENAME_USER,(yyvsp[0].node));
      (yyval.node)->AddMember("OPERATION_NAME","RENAME_USER", result->Doc.GetAllocator() );

    }

    break;

  case 367:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_RENAME_INFO, 2, $1, $3);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_RENAME_INFO);
      (yyval.node)->AddMember("OLD_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("NEW_NAME",*(yyvsp[0].node), result->Doc.GetAllocator() );
  
    }

    break;

  case 368:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 369:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 370:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LOCK_USER, 2, $3, $4);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LOCK_USER,(yyvsp[-1].node) ,(yyvsp[0].node));
    }

    break;

  case 371:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(1);
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 372:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(0);
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 373:

    {
      (void)(yyval.node);
    }

    break;

  case 374:

    {
    }

    break;

  case 375:

    {
      (yyval.ival) = 1;
    }

    break;

  case 376:

    {
      (yyval.ival) = 0;
    }

    break;

  case 377:

    {
      (void)(yyvsp[0].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_BEGIN);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BEGIN);
      rapidjson::Value tmp(0);
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 378:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BEGIN);
       
       rapidjson::Value tmp((yyvsp[0].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 379:

    {
      (void)(yyvsp[0].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_COMMIT);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_COMMIT);
			(yyval.node)->AddMember("OPERATION_NAME","COMMIT", result->Doc.GetAllocator() );

    }

    break;

  case 380:

    {
      (void)(yyvsp[0].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_ROLLBACK);*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_ROLLBACK);
			 (yyval.node)->AddMember("OPERATION_NAME","ROLLBACK", result->Doc.GetAllocator() );

    }

    break;

  case 381:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_KILL, 3, $2, $3, $4);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_KILL );
    (yyval.node)->AddMember("OPERATION_NAME","KILL", result->Doc.GetAllocator() );
    (yyval.node)->AddMember("IS_GLOBAL",*(yyvsp[-2].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("OPT_FLAG",*(yyvsp[-1].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("INTNUM",*(yyvsp[0].node), result->Doc.GetAllocator() );



    }

    break;

  case 382:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
    }

    break;

  case 383:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
       $$->value_ = 1;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
       (*(yyval.node))["value_"] = rapidjson::Value(-1);
    }

    break;

  case 384:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
      
    }

    break;

  case 385:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
       rapidjson::Value tmp(1);
       (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 386:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
     
    }

    break;

  case 387:

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
      
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_GRANT );
			(yyval.node)->AddMember("OPERATION_NAME","GRANT", result->Doc.GetAllocator() );
    	(yyval.node)->AddMember("PRIV_LEVEL",*(yyvsp[-2].node), result->Doc.GetAllocator() );
    	(yyval.node)->AddMember("PRIV_TYPE", *(yyvsp[-4].node), result->Doc.GetAllocator() );
    	(yyval.node)->AddMember("USER_NAME", *(yyvsp[0].node), result->Doc.GetAllocator() );
    }

    break;

  case 388:

    {
    	printf(" priv_type_list \n");
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 389:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 390:

    {
    	
      (void)(yyvsp[0].node);                 /* useless */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALL;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALL);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","ALL", result->Doc.GetAllocator() );
    }

    break;

  case 391:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALTER;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALTER);
      (yyval.node)->AddMember("str_value_","ALTER", result->Doc.GetAllocator() );
    }

    break;

  case 392:

    {
    	printf(" CREATE \n");
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE);
      (yyval.node)->AddMember("str_value_","CREATE", result->Doc.GetAllocator() );
    }

    break;

  case 393:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE_USER;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE_USER);
      (yyval.node)->AddMember("str_value_","CREATE_USER", result->Doc.GetAllocator() );
    }

    break;

  case 394:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DELETE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DELETE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","DELETE", result->Doc.GetAllocator() );
    }

    break;

  case 395:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DROP;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DROP);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","DROP", result->Doc.GetAllocator() );
    }

    break;

  case 396:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_GRANT_OPTION;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_GRANT_OPTION);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","GRANT_OPTION", result->Doc.GetAllocator() );
    }

    break;

  case 397:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_INSERT;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_INSERT);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","INSERT", result->Doc.GetAllocator() );
    }

    break;

  case 398:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_UPDATE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_UPDATE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","UPDATE", result->Doc.GetAllocator() );
    }

    break;

  case 399:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_SELECT;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_SELECT);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","SELECT", result->Doc.GetAllocator() );
    }

    break;

  case 400:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_REPLACE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_REPLACE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","REPLACE", result->Doc.GetAllocator() );
    }

    break;

  case 401:

    {
    
      (void)(yyval.node);
    }

    break;

  case 402:

    {
    	
      (void)(yyval.node);
    }

    break;

  case 403:

    {
      /* means global priv_level */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_LEVEL);
     
    }

    break;

  case 404:

    {
      
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL, 1, $1);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_PRIV_LEVEL,(yyvsp[0].node));
    

    }

    break;

  case 405:

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
		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_REVOKE );
		(yyval.node)->AddMember("OPERATION_NAME","REVOKE", result->Doc.GetAllocator() );
    (yyval.node)->AddMember("PRIV_LEVEL",*(yyvsp[-2].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("PRIV_TYPE", *(yyvsp[-3].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("USER_NAME", *(yyvsp[0].node), result->Doc.GetAllocator() );                                 
    }

    break;

  case 406:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 407:

    {
      (yyval.node) = NULL;
    }

    break;

  case 408:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PREPARE, 2, $2, $4);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PREPARE);
      
      (yyval.node)->AddMember("OPERATION_NAME","PREPARE", result->Doc.GetAllocator() );
   		(yyval.node)->AddMember("PREPARE_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
   		(yyval.node)->AddMember("PREPARE_STMT",*(yyvsp[0].node), result->Doc.GetAllocator() );
    }

    break;

  case 409:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 410:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 411:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 412:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 413:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 414:

    {
     /* merge_nodes($$, result->malloc_pool_, T_VARIABLE_SET, $2);
      $$->value_ = 2;*/

      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_VARIABLE_SET,(yyvsp[0].node));      
      (yyval.node)->AddMember("OPERATION_NAME","SET", result->Doc.GetAllocator() );
    }

    break;

  case 415:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 416:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 417:

    {
      (void)((yyvsp[-1].node));
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
       (yyval.node)->AddMember("VARIABLE_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
       (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );

    }

    break;

  case 418:

    {
      (void)((yyvsp[-1].node));
       /*$1->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
    rapidjson::Value tmp(T_SYSTEM_VARIABLE);
    (yyvsp[-2].node)->AddMember("type_", tmp,result->Doc.GetAllocator());
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
     (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
     (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );

    }

    break;

  case 419:

    {
      (void)((yyvsp[-1].node));
     /* $2->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $2, $4);
      $$->value_ = 1;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
   	  (yyvsp[-2].node)->AddMember("type_", tmp,result->Doc.GetAllocator());
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL);
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );

    }

    break;

  case 420:

    {
      //(void)($3);
     // rapidjson::Value tmp(T_SYSTEM_VARIABLE);
     // $2->AddMember("type_", tmp,result->Doc.GetAllocator());

      malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
      //rapidjson::Value tmp1(2);
      //$$->AddMember("value_",tmp1, result->Doc.GetAllocator() );
      
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );

    }

    break;

  case 421:

    {
      //(void)($4);

      //rapidjson::Value tmp(T_SYSTEM_VARIABLE);

      // $3->AddMember("type_", tmp,result->Doc.GetAllocator());
      malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
      rapidjson::Value tmp1(1);
      (yyval.node)->AddMember("value_",tmp1, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );

    }

    break;

  case 422:

    {
     // (void)($4);

      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
      //(*$3)["type_"].Swap(tmp);
    //  $3->AddMember("type_", tmp,result->Doc.GetAllocator());

      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL);
      rapidjson::Value tmp1(2);
      (yyval.node)->AddMember("value_",tmp1, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );
      
    }

    break;

  case 423:

    {
     // (void)($2);

       malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
       rapidjson::Value tmp(2);
       (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
       
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[-2].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[0].node), result->Doc.GetAllocator() );
    }

    break;

  case 424:

    {
    	 
    	 (yyval.node) = NULL; 
    	 }

    break;

  case 425:

    { (yyval.node) = NULL; }

    break;

  case 426:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 427:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXECUTE, 2, $2, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXECUTE,(yyvsp[-1].node), (yyvsp[0].node));

    }

    break;

  case 428:

    {
     /* merge_nodes($$, result->malloc_pool_, T_ARGUMENT_LIST, $2);*/
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_ARGUMENT_LIST,(yyvsp[0].node));

    }

    break;

  case 429:

    {
      (yyval.node) = NULL;
    }

    break;

  case 430:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 431:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 432:

    {
      (void)((yyvsp[-2].node));
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DEALLOCATE, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_DEALLOCATE,(yyvsp[0].node));
    }

    break;

  case 433:

    { (yyval.node) = NULL; }

    break;

  case 434:

    { (yyval.node) = NULL; }

    break;

  case 435:

    {
      /*ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, alter_actions);*/
      
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_ALTER_TABLE );
    
      (yyval.node)->AddMember("OPERATION_NAME","ALTER_TABLE", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[-1].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("ALTER_ACTIONS",*(yyvsp[0].node), result->Doc.GetAllocator() );
      
      
    }

    break;

  case 436:

    {
     // yyerror(&@1, result, "Table rename is not supported now");
     // YYABORT;
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_TABLE_RENAME, 1, $6);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_ACTION_LIST, 1, $$);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, $$);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_ALTER_TABLE );
      (yyval.node)->AddMember("OPERATION_NAME","RENAME_TABLE_NAME", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[-3].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("NEW_NAME",*(yyvsp[0].node), result->Doc.GetAllocator() );
      
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_TABLE_RENAME, $6);
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_ALTER_TABLE, $3, $$);
    }

    break;

  case 437:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 438:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));
    }

    break;

  case 439:

    {
      (void)((yyvsp[-1].node)); /* make bison mute */
      (yyval.node) = (yyvsp[0].node); /* T_COLUMN_DEFINITION */
    }

    break;

  case 440:

    {
      (void)((yyvsp[-2].node)); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DROP, 1, $3);
      $$->value_ = $4;*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_DROP, (yyvsp[-1].node));
       rapidjson::Value tmp((yyvsp[0].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 441:

    {
      (void)((yyvsp[-2].node)); /* make bison mute */
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_ALTER, 2, $3, $4);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_ALTER, (yyvsp[-1].node), (yyvsp[0].node));

    }

    break;

  case 442:

    {
      (void)((yyvsp[-3].node)); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_RENAME, 2, $3, $5);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_RENAME, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 443:

    { (yyval.node) = NULL; }

    break;

  case 444:

    { (yyval.node) = NULL; }

    break;

  case 445:

    { (yyval.ival) = 2; }

    break;

  case 446:

    { (yyval.ival) = 1; }

    break;

  case 447:

    { (yyval.ival) = 0; }

    break;

  case 448:

    {
      (void)((yyvsp[0].node)); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CONSTR_NOT_NULL);
    }

    break;

  case 449:

    {
      (void)((yyvsp[0].node)); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CONSTR_NULL);
    }

    break;

  case 450:

    {
       /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CONSTR_DEFAULT,(yyvsp[0].node));
       
    }

    break;

  case 451:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_NULL);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $$);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_NULL);
      malloc_non_terminal_node (&(yyval.node),result->Doc.GetAllocator(),T_CONSTR_DEFAULT, node);
    }

    break;

  case 452:

    {
      /*merge_nodes($$, result->malloc_pool_, T_SYTEM_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_SYSTEM, 1, $$);*/
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_SYTEM_ACTION_LIST, (yyvsp[0].node));
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_ALTER_SYSTEM,(yyval.node));
    }

    break;

  case 453:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[0].node), (yyvsp[-4].node));
    }

    break;

  case 454:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[0].node), (yyvsp[-4].node));
      
    }

    break;

  case 455:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[0].node));
 
    }

    break;

  case 456:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[0].node));

    }

    break;

  case 457:

    {
      (yyval.node) = NULL;
    }

    break;

  case 458:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_FORCE);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_FORCE);
    }

    break;

  case 459:

    {
      (yyval.node) = (yyvsp[0].node);
    }

    break;

  case 460:

    {
     /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[-2].node), (yyvsp[0].node));

    }

    break;

  case 461:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SYSTEM_ACTION, 5,
                               $1,    /* param_name 
                               $3,    /* param_value 
                               $4,    /* comment 
                               $8,    /* server type 
                               $9     /* cluster or IP/port 
                               );
      $$->value_ = $5;                 scope */
      SafeAddMember((yyval.node),"param_name",(yyvsp[-8].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"param_value",(yyvsp[-6].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"comment",(yyvsp[-5].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"server_type",(yyvsp[-1].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"cluster",(yyvsp[0].node),result->Doc.GetAllocator());
			 rapidjson::Value tmp((yyvsp[-4].ival));
			(*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 462:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 463:

    { (yyval.node) = NULL; }

    break;

  case 464:

    { (yyval.ival) = 0; }

    break;

  case 465:

    { (yyval.ival) = 1; }

    break;

  case 466:

    { (yyval.ival) = 2; }

    break;

  case 467:

    { (yyval.ival) = 2; }

    break;

  case 468:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 1;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 469:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 4;*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
     rapidjson::Value tmp(4);
     (*(yyval.node))["value_"].Swap( tmp); 
    }

    break;

  case 470:

    {
     /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 2;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*(yyval.node))["value_"].Swap(tmp); 
    }

    break;

  case 471:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 3;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(3);
      (*(yyval.node))["value_"].Swap(tmp); 
    }

    break;

  case 472:

    {
     /* malloc_non_terminal_node($$ , result->malloc_pool_, T_CLUSTER, 1, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CLUSTER,(yyvsp[0].node));
    }

    break;

  case 473:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SERVER_ADDRESS, 2, $3, $6);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SERVER_ADDRESS,(yyvsp[-3].node), (yyvsp[0].node));
    }

    break;

  case 474:

    { (yyval.node) = NULL; }

    break;

  case 475:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 476:

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
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_IDENT);
      if((yyvsp[0].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[0].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);
    }

    break;

  case 477:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 478:

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
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_IDENT);
      if((yyvsp[0].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[0].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
			rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);

    }

    break;

  case 479:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 480:

    { (yyval.node) = (yyvsp[0].node); }

    break;

  case 481:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_IDENT);
      $$->str_value_ = parse_strdup($1->keyword_name, result->malloc_pool_);
      if ($$->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_IDENT);
      if((yyvsp[0].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[0].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);

    }

    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}


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
