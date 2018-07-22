
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



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





/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     EXCEPT = 270,
     UNION = 271,
     INTERSECT = 272,
     OR = 273,
     AND = 274,
     NOT = 275,
     COMP_NE = 276,
     COMP_GE = 277,
     COMP_GT = 278,
     COMP_EQ = 279,
     COMP_LT = 280,
     COMP_LE = 281,
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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  897

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   460

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      62,    64,    65,    67,    71,    73,    77,    81,    83,    85,
      87,    89,    91,    93,    95,    97,    99,   101,   103,   107,
     113,   115,   117,   119,   121,   124,   126,   129,   132,   136,
     140,   144,   148,   152,   156,   160,   162,   165,   168,   172,
     176,   180,   184,   188,   192,   196,   200,   204,   208,   212,
     216,   220,   224,   229,   233,   237,   240,   244,   249,   253,
     258,   262,   267,   273,   280,   284,   289,   293,   295,   299,
     305,   307,   308,   310,   313,   318,   321,   322,   327,   333,
     338,   345,   350,   354,   359,   361,   363,   365,   367,   369,
     371,   373,   379,   387,   389,   393,   397,   410,   421,   423,
     425,   427,   428,   430,   432,   434,   435,   444,   448,   449,
     451,   455,   457,   463,   467,   469,   471,   473,   475,   477,
     480,   483,   485,   488,   490,   493,   496,   498,   501,   504,
     507,   510,   512,   514,   516,   519,   525,   529,   530,   534,
     535,   537,   538,   542,   543,   547,   548,   551,   552,   555,
     557,   560,   562,   565,   567,   571,   572,   576,   580,   584,
     588,   592,   596,   600,   604,   608,   612,   616,   620,   622,
     623,   628,   629,   632,   634,   638,   646,   651,   659,   660,
     663,   665,   667,   671,   672,   674,   678,   682,   688,   690,
     694,   697,   699,   703,   707,   709,   712,   716,   721,   727,
     736,   738,   740,   750,   755,   760,   765,   766,   769,   773,
     778,   783,   786,   789,   794,   795,   799,   801,   805,   806,
     808,   811,   813,   815,   820,   824,   827,   828,   830,   832,
     834,   836,   838,   840,   841,   843,   844,   847,   851,   856,
     861,   866,   870,   874,   878,   879,   883,   885,   886,   890,
     892,   896,   899,   900,   902,   904,   905,   908,   909,   911,
     913,   915,   918,   922,   924,   926,   930,   932,   936,   938,
     942,   945,   949,   952,   954,   960,   962,   966,   973,   979,
     982,   985,   988,   990,   992,   996,   998,  1000,  1002,  1004,
    1006,  1007,  1011,  1017,  1023,  1028,  1033,  1038,  1041,  1046,
    1050,  1054,  1058,  1062,  1066,  1070,  1074,  1079,  1082,  1083,
    1085,  1088,  1093,  1095,  1097,  1098,  1099,  1102,  1105,  1106,
    1108,  1109,  1111,  1115,  1119,  1121,  1125,  1130,  1132,  1134,
    1138,  1140,  1144,  1150,  1157,  1160,  1161,  1165,  1169,  1171,
    1175,  1180,  1182,  1184,  1186,  1187,  1191,  1192,  1195,  1199,
    1202,  1205,  1210,  1211,  1213,  1214,  1216,  1218,  1225,  1227,
    1231,  1234,  1236,  1238,  1241,  1243,  1245,  1248,  1250,  1252,
    1254,  1256,  1258,  1259,  1261,  1263,  1269,  1272,  1273,  1278,
    1280,  1282,  1284,  1286,  1288,  1291,  1293,  1297,  1301,  1305,
    1310,  1315,  1321,  1327,  1331,  1333,  1335,  1337,  1341,  1344,
    1345,  1347,  1351,  1355,  1357,  1359,  1364,  1371,  1373,  1377,
    1381,  1386,  1391,  1397,  1399,  1400,  1402,  1404,  1405,  1409,
    1413,  1417,  1420,  1425,  1433,  1441,  1448,  1455,  1456,  1458,
    1460,  1464,  1474,  1477,  1478,  1482,  1486,  1490,  1491,  1493,
    1495,  1497,  1499,  1503,  1510,  1511,  1513,  1515,  1517,  1519,
    1521,  1523,  1525,  1527,  1529,  1531,  1533,  1535,  1537,  1539,
    1541,  1543,  1545,  1547,  1549,  1551,  1553,  1555,  1557,  1559,
    1561,  1563,  1565,  1567,  1569,  1571,  1573
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     218,     0,    -1,   219,    83,    -1,   219,   215,   220,    -1,
     220,    -1,   271,    -1,   264,    -1,   245,    -1,   242,    -1,
     239,    -1,   238,    -1,   261,    -1,   305,    -1,   308,    -1,
     344,    -1,   347,    -1,   352,    -1,   357,    -1,   363,    -1,
     355,    -1,   315,    -1,   320,    -1,   322,    -1,   324,    -1,
     327,    -1,   337,    -1,   342,    -1,   331,    -1,   332,    -1,
     333,    -1,   334,    -1,    -1,   226,    -1,   221,   216,   226,
      -1,   371,    -1,   372,    42,   371,    -1,   372,    42,    34,
      -1,     4,    -1,     6,    -1,     5,    -1,     9,    -1,     8,
      -1,    10,    -1,    12,    -1,    14,    -1,    13,    -1,   222,
      -1,   223,    -1,    40,   226,    41,    -1,    40,   221,   216,
     226,    41,    -1,   228,    -1,   233,    -1,   234,    -1,   272,
      -1,    86,   272,    -1,   224,    -1,    32,   225,    -1,    33,
     225,    -1,   225,    32,   225,    -1,   225,    33,   225,    -1,
     225,    34,   225,    -1,   225,    35,   225,    -1,   225,    36,
     225,    -1,   225,    38,   225,    -1,   225,    37,   225,    -1,
     224,    -1,    32,   226,    -1,    33,   226,    -1,   226,    32,
     226,    -1,   226,    33,   226,    -1,   226,    34,   226,    -1,
     226,    35,   226,    -1,   226,    36,   226,    -1,   226,    38,
     226,    -1,   226,    37,   226,    -1,   226,    26,   226,    -1,
     226,    25,   226,    -1,   226,    24,   226,    -1,   226,    22,
     226,    -1,   226,    23,   226,    -1,   226,    21,   226,    -1,
     226,    28,   226,    -1,   226,    20,    28,   226,    -1,   226,
      19,   226,    -1,   226,    18,   226,    -1,    20,   226,    -1,
     226,    31,    10,    -1,   226,    31,    20,    10,    -1,   226,
      31,     8,    -1,   226,    31,    20,     8,    -1,   226,    31,
      11,    -1,   226,    31,    20,    11,    -1,   226,    29,   225,
      19,   225,    -1,   226,    20,    29,   225,    19,   225,    -1,
     226,    30,   227,    -1,   226,    20,    30,   227,    -1,   226,
      27,   226,    -1,   272,    -1,    40,   221,    41,    -1,    56,
     229,   230,   232,    82,    -1,   226,    -1,    -1,   231,    -1,
     230,   231,    -1,   174,   226,   160,   226,    -1,    81,   226,
      -1,    -1,   373,    40,    34,    41,    -1,   373,    40,   237,
     226,    41,    -1,   373,    40,   221,    41,    -1,   373,    40,
     226,    47,   250,    41,    -1,   373,    40,   288,    41,    -1,
     373,    40,    41,    -1,   235,    40,   236,    41,    -1,   198,
      -1,   271,    -1,   264,    -1,   239,    -1,   238,    -1,    45,
      -1,    77,    -1,    74,    90,   301,   277,   265,    -1,   167,
     279,   301,   146,   240,   277,   265,    -1,   241,    -1,   240,
     216,   241,    -1,   371,    24,   226,    -1,    64,   243,   186,
     301,   121,   301,   169,   244,    40,   268,    41,   258,    -1,
      64,   243,   186,   301,   121,   301,    40,   268,    41,   258,
      -1,   181,    -1,   182,    -1,   183,    -1,    -1,   184,    -1,
     185,    -1,   187,    -1,    -1,    64,   158,   246,   301,    40,
     247,    41,   258,    -1,   103,    20,    86,    -1,    -1,   248,
      -1,   247,   216,   248,    -1,   249,    -1,   129,   109,    40,
     268,    41,    -1,   371,   250,   256,    -1,   163,    -1,   148,
      -1,   115,    -1,   105,    -1,    50,    -1,    72,   251,    -1,
     119,   251,    -1,    52,    -1,    88,   252,    -1,   131,    -1,
      78,   253,    -1,   162,   254,    -1,    70,    -1,    57,   255,
      -1,    51,   255,    -1,   171,   255,    -1,   172,   255,    -1,
      65,    -1,   117,    -1,    69,    -1,   161,   254,    -1,    40,
       5,   216,     5,    41,    -1,    40,     5,    41,    -1,    -1,
      40,     5,    41,    -1,    -1,   127,    -1,    -1,    40,     5,
      41,    -1,    -1,    40,     5,    41,    -1,    -1,   256,   257,
      -1,    -1,    20,    10,    -1,    10,    -1,    73,   223,    -1,
     188,    -1,   129,   109,    -1,   259,    -1,   258,   216,   259,
      -1,    -1,   194,   260,     4,    -1,   192,   260,     4,    -1,
     206,   260,     5,    -1,   207,   260,     5,    -1,   208,   260,
       5,    -1,   205,   260,     5,    -1,   204,   260,     5,    -1,
     196,   260,     5,    -1,   190,   260,     4,    -1,   211,   260,
       8,    -1,   191,   260,   152,    -1,    59,   260,     4,    -1,
      24,    -1,    -1,    79,   158,   262,   263,    -1,    -1,   103,
      86,    -1,   300,    -1,   263,   216,   300,    -1,   266,   107,
     301,   267,   170,   269,   265,    -1,   266,   107,   301,   271,
      -1,   266,   107,   301,    40,   268,    41,   271,    -1,    -1,
     174,   226,    -1,   133,    -1,   106,    -1,    40,   268,    41,
      -1,    -1,   371,    -1,   268,   216,   371,    -1,    40,   270,
      41,    -1,   269,   216,    40,   270,    41,    -1,   226,    -1,
     270,   216,   226,    -1,   273,   265,    -1,   272,    -1,    40,
     273,    41,    -1,    40,   272,    41,    -1,   274,    -1,   276,
     287,    -1,   275,   291,   287,    -1,   275,   290,   278,   287,
      -1,   143,   279,   296,   298,   286,    -1,   143,   279,   296,
     298,    90,    80,   277,   286,    -1,   276,    -1,   272,    -1,
     143,   279,   296,   298,    90,   299,   277,   289,   295,    -1,
     275,    16,   296,   275,    -1,   275,    17,   296,   275,    -1,
     275,    15,   296,   275,    -1,    -1,   173,   226,    -1,   173,
       7,   226,    -1,   112,   285,   120,   285,    -1,   120,   285,
     112,   285,    -1,   112,   285,    -1,   120,   285,    -1,   112,
     285,   216,   285,    -1,    -1,    99,   280,   100,    -1,   281,
      -1,   280,   216,   281,    -1,    -1,   282,    -1,   281,   282,
      -1,   130,    -1,   101,    -1,   140,    40,   284,    41,    -1,
      40,   283,    41,    -1,   283,   216,    -1,    -1,   180,    -1,
     154,    -1,   152,    -1,    92,    -1,     5,    -1,    12,    -1,
      -1,   278,    -1,    -1,    89,   167,    -1,   226,    90,   226,
      -1,    53,   226,    90,   226,    -1,   110,   226,    90,   226,
      -1,   164,   226,    90,   226,    -1,    53,    90,   226,    -1,
     110,    90,   226,    -1,   164,    90,   226,    -1,    -1,    97,
      54,   221,    -1,   291,    -1,    -1,   122,    54,   292,    -1,
     293,    -1,   292,   216,   293,    -1,   226,   294,    -1,    -1,
      48,    -1,    75,    -1,    -1,    98,   226,    -1,    -1,    45,
      -1,    77,    -1,   226,    -1,   226,   374,    -1,   226,    47,
     374,    -1,    34,    -1,   297,    -1,   298,   216,   297,    -1,
     300,    -1,   299,   216,   300,    -1,   301,    -1,   301,    47,
     372,    -1,   301,   372,    -1,   272,    47,   372,    -1,   272,
     372,    -1,   302,    -1,    40,   302,    41,    47,   372,    -1,
     372,    -1,    40,   302,    41,    -1,   300,   303,   108,   300,
     121,   226,    -1,   300,   108,   300,   121,   226,    -1,    91,
     304,    -1,   111,   304,    -1,   137,   304,    -1,   104,    -1,
     124,    -1,    87,   307,   306,    -1,   271,    -1,   238,    -1,
     264,    -1,   239,    -1,   213,    -1,    -1,   147,   159,   312,
      -1,   147,    63,    90,   301,   312,    -1,   147,    63,    30,
     301,   312,    -1,   147,   158,   203,   312,    -1,   147,   199,
     203,   312,    -1,   147,   311,   212,   312,    -1,   147,   141,
      -1,   147,    64,   158,   301,    -1,    76,   301,   313,    -1,
      75,   301,   313,    -1,   147,   214,   309,    -1,   147,   233,
     214,    -1,   147,   193,   310,    -1,   147,   125,   312,    -1,
     147,   314,   177,    -1,   112,     5,   216,     5,    -1,   112,
       5,    -1,    -1,   323,    -1,    89,    66,    -1,    89,    66,
      40,    41,    -1,    94,    -1,   144,    -1,    -1,    -1,    28,
       4,    -1,   173,   226,    -1,    -1,     4,    -1,    -1,    91,
      -1,    64,   168,   316,    -1,    64,   168,   318,    -1,   317,
      -1,   316,   216,   317,    -1,   318,   102,    54,   319,    -1,
       4,    -1,     4,    -1,    79,   168,   321,    -1,   318,    -1,
     321,   216,   318,    -1,   146,   126,   323,    24,   319,    -1,
      46,   168,   318,   102,    54,   319,    -1,    89,   318,    -1,
      -1,   132,   168,   326,    -1,   318,   166,   318,    -1,   325,
      -1,   326,   216,   325,    -1,    46,   168,   318,   328,    -1,
     114,    -1,   209,    -1,   176,    -1,    -1,   175,    61,   149,
      -1,    -1,    49,   329,    -1,   151,   165,   330,    -1,    60,
     329,    -1,   138,   329,    -1,   139,   335,   336,     5,    -1,
      -1,    94,    -1,    -1,   178,    -1,   179,    -1,    96,   338,
     121,   341,   166,   321,    -1,   339,    -1,   338,   216,   339,
      -1,    45,   340,    -1,    46,    -1,    64,    -1,    64,   168,
      -1,    74,    -1,    79,    -1,    96,   123,    -1,   106,    -1,
     167,    -1,   143,    -1,   133,    -1,   135,    -1,    -1,    34,
      -1,   372,    -1,   136,   338,   343,    90,   321,    -1,   121,
     341,    -1,    -1,   128,   345,    90,   346,    -1,   374,    -1,
     271,    -1,   264,    -1,   239,    -1,   238,    -1,   146,   348,
      -1,   349,    -1,   348,   216,   349,    -1,    14,   350,   226,
      -1,   371,   350,   226,    -1,    94,   371,   350,   226,    -1,
     144,   371,   350,   226,    -1,    95,    42,   371,   350,   226,
      -1,   145,    42,   371,   350,   226,    -1,    13,   350,   226,
      -1,   166,    -1,    24,    -1,    14,    -1,    85,   345,   353,
      -1,   169,   354,    -1,    -1,   351,    -1,   354,   216,   351,
      -1,   356,   128,   345,    -1,    71,    -1,    79,    -1,    46,
     158,   301,   358,    -1,    46,   158,   301,   132,   166,   301,
      -1,   359,    -1,   358,   216,   359,    -1,    43,   360,   249,
      -1,    79,   360,   371,   361,    -1,    46,   360,   371,   362,
      -1,   132,   360,   371,   166,   374,    -1,    62,    -1,    -1,
      55,    -1,   134,    -1,    -1,   146,    20,    10,    -1,    79,
      20,    10,    -1,   146,    73,   223,    -1,    79,    73,    -1,
      46,   153,   146,   365,    -1,    46,   153,   364,    67,   118,
      24,     4,    -1,    46,   153,   364,    68,   118,    24,     4,
      -1,    46,   153,   155,   118,    24,     4,    -1,    46,   153,
     156,   157,    24,     4,    -1,    -1,    93,    -1,   366,    -1,
     365,   216,   366,    -1,   371,    24,   223,   367,   368,   202,
      24,   369,   370,    -1,    59,     4,    -1,    -1,   142,    24,
     116,    -1,   142,    24,   150,    -1,   142,    24,    53,    -1,
      -1,   197,    -1,   210,    -1,   189,    -1,   195,    -1,    58,
      24,     5,    -1,   200,    24,     4,   201,    24,     5,    -1,
      -1,     3,    -1,   375,    -1,     3,    -1,   375,    -1,     3,
      -1,     3,    -1,   375,    -1,   188,    -1,   189,    -1,   190,
      -1,   191,    -1,   192,    -1,   193,    -1,   194,    -1,   195,
      -1,   196,    -1,   197,    -1,   198,    -1,   199,    -1,   200,
      -1,   201,    -1,   202,    -1,   203,    -1,   205,    -1,   204,
      -1,   206,    -1,   209,    -1,   210,    -1,   211,    -1,   212,
      -1,   213,    -1,   214,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "DATE_VALUE",
  "HINT_VALUE", "BOOL", "APPROXNUM", "NULLX", "UNKNOWN", "QUESTIONMARK",
  "SYSTEM_VARIABLE", "TEMP_VARIABLE", "EXCEPT", "UNION", "INTERSECT", "OR",
  "AND", "NOT", "COMP_NE", "COMP_GE", "COMP_GT", "COMP_EQ", "COMP_LT",
  "COMP_LE", "CNNOP", "LIKE", "BETWEEN", "IN", "IS", "'+'", "'-'", "'*'",
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
  "function_name", "column_label", "unreserved_keyword", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
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
       0,     0,     0,     0,     0,     0,     0,   244,   231,   235,
     230,   233,   234,   282,   278,   279,   261,   262,   241,   242,
     227,     0,     0,     0,     0,     0,     0,   443,     0,     0,
       0,     0,     0,     0,     0,   137,     0,   355,     0,     0,
       0,     0,   237,   121,   231,     0,   303,     0,     0,   302,
       0,   312,     0,     0,     0,     0,     0,   300,   361,     0,
       0,   367,   369,   405,   254,   255,   260,   259,   258,   257,
       0,   247,     0,   291,     0,     0,   264,   228,   419,     0,
     358,   362,   420,     0,   323,   322,     0,     0,   107,     0,
       0,     0,     0,     0,     0,   109,     0,     0,     0,     0,
     111,   375,   236,   123,     0,     0,   214,     0,     0,    48,
       0,   106,   102,    84,    83,     0,     0,     0,    80,    78,
      79,    77,    76,    75,    96,    81,     0,     0,    55,     0,
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

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -738
static const yytype_int16 yypact[] =
{
    2173,    31,   -46,   -88,   -88,   204,  -738,    37,  1886,  1886,
     -73,  1915,  -122,   436,  -738,  1915,   -33,  -738,   436,   -88,
     141,    57,  1226,   408,    81,    57,   270,   -53,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,   189,  -738,     1,   125,  -738,
      36,    62,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,   186,
    -738,  -738,   284,   290,    -7,  1886,   339,  -738,  -738,  -738,
     242,   339,  -738,  -738,  -738,   167,  1886,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,   370,  -738,  -738,   370,   277,   339,  -738,
     214,  -738,  -738,  -738,   267,   256,  -738,   227,  -738,  -738,
     280,  -738,  -738,  -738,  -738,   -49,  -738,   316,   339,   -23,
    -738,  -738,    82,   152,   185,  -738,    11,    11,  1977,   365,
     320,  1977,   371,   201,  -738,    11,  -738,  -738,   239,   260,
    -738,  -738,    -2,  -738,  -738,   218,    -2,   334,   224,   313,
     215,   223,   264,   393,   262,  1886,  -738,  -738,  2173,  1886,
    1569,  -738,   185,   185,   185,   390,   171,   166,   282,  -738,
    1915,  -738,  -738,  -738,  1977,   329,   310,   241,    65,  -738,
     -27,   448,  1886,   257,  -738,   374,  1886,   312,  -738,  -738,
    -738,   397,  1773,  -738,   272,   472,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -738,  1682,   436,   267,   323,
    -738,   275,  1682,   403,  -738,  -738,   490,  -738,  -738,  -738,
     457,   -63,   152,  -738,  -738,  -738,   941,  -738,  -738,  1569,
    1569,    11,  1977,   339,   474,    11,  1977,  1655,  1569,  1886,
    1886,  1886,   497,  1569,  -738,    -2,  -738,    72,  -738,  -738,
      -2,   506,  -738,  -738,    -2,  -738,   586,   460,  -738,   366,
    -738,    42,    73,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,  1569,  1569,  1569,  1198,  1569,   487,   491,  -738,
    -738,  -738,  2577,  -738,  -738,  -738,   503,  -738,  -738,   502,
     504,    43,    43,    43,  1569,   261,   261,   456,  -738,  -738,
    -738,   332,  -738,   523,   526,   527,   435,   437,   492,   492,
     492,     0,   344,  -738,   507,  -738,  -738,  -738,   478,   525,
     339,   514,   459,  1253,   125,  -738,   686,   362,   847,   -11,
    1947,  -738,   339,  -738,  -738,   367,  -738,   415,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,   339,   339,  -738,   339,  -738,
     -21,    95,  -738,   152,  -738,  -738,   983,  -738,   -43,  2577,
    2577,  1569,    11,  -738,   578,  1569,    11,  -738,  2577,    -2,
      -2,  -738,  -738,  2577,  -738,   544,  -738,   372,  -738,   545,
    -738,  -738,  1286,  -738,  1498,  1531,    -3,  2371,  1569,   546,
     444,  1977,   890,   427,  -738,   891,  -738,  -738,   386,  2005,
     235,  2577,   430,  -738,  1569,  1569,   331,  1569,  1569,  1569,
    1569,  1569,  1569,  1569,  1569,  1627,   565,   388,  1569,  1569,
    1569,  1569,  1569,  1569,  1569,   267,  1808,    57,  -738,   591,
    -738,   591,  -738,  2495,   394,  -738,  -738,  -738,   -56,   500,
    -738,  1977,   451,   609,   610,   592,   593,  -738,  1977,  1977,
    1977,  1886,  1977,   247,   578,  -738,  1859,  -738,   374,   578,
    1886,  1569,  2577,  -738,  1743,   -11,   574,  1773,  1886,  -738,
     499,  -738,  1773,   499,   499,   513,  1886,  -738,  -738,   472,
     339,  -738,  -738,   272,  -738,  -738,  -738,  -738,  -738,  -738,
     583,   152,  1915,  -738,  1711,   941,  -738,  -738,  2577,  1569,
    -738,  -738,  2577,  1569,  -738,  -738,   584,   623,  -738,  1569,
    2401,  1569,  2422,  1569,  2444,  -738,  1569,  2216,  1569,  2526,
    -738,  -738,   -74,  -738,   606,     2,  -738,   601,  1569,  -738,
    1569,    33,  -738,  2473,   891,  1569,  1627,   565,   811,   811,
     811,   811,   811,   811,   704,   727,  1627,  1627,  -738,   471,
    1198,  -738,  -738,  -738,  -738,  -738,   469,   300,   300,   602,
     602,   602,   602,  -738,   604,  -738,  -738,  -738,  -738,  -738,
    -738,   185,  -738,  -738,  -738,  1569,   261,   261,   261,  -738,
     587,  -738,  -738,   639,   643,  -738,  2216,    50,    12,  -738,
     483,   492,  -738,  -738,   541,     4,  -738,  -738,  -738,     6,
    2577,   605,   -11,  -738,  -738,  -738,   293,  -738,  -738,  1773,
    -738,  -738,   272,  -738,  -738,   312,   -64,   -11,  -738,  2577,
    2577,  -738,  -738,  2577,  1569,  2577,  1569,  2577,  1569,  2577,
    -738,   611,  -738,   611,  -738,  -738,  -738,   613,   528,   614,
    -738,  -738,  -738,   613,  -738,  -738,   617,   617,  -738,   611,
     611,   618,  2577,  -738,  1977,   125,  1569,    31,  1977,  1569,
     -96,  2553,  2174,  1569,  -738,   576,   727,   539,  -738,  -738,
    -738,  1627,  1627,  1627,  1627,  1627,  1627,  1627,  1627,     7,
    2577,  -738,  -738,  -738,  -738,   941,  -738,  -738,  -738,  -738,
     657,   520,  -738,  -738,  -738,    46,    61,  -738,  -738,  -738,
    -738,  1915,   624,   160,  1859,  1977,   191,  1886,  1569,   311,
     171,  1773,   568,  2577,  2577,  2577,   661,  -738,  -738,   662,
    -738,  -738,  -738,   663,  -738,  -738,   664,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  2577,  -738,  -738,  2577,     8,   630,
    -738,  -738,  1569,  2577,  -738,  1627,   600,   482,   482,   635,
     635,   635,   635,  -738,  -738,   -35,  -738,   650,   473,    21,
     666,  -738,   670,   451,  -738,  1977,   658,   658,   658,   658,
     658,   658,   658,   658,   658,   658,   658,   658,   465,  -738,
    -738,    13,  -738,  -738,  -738,   644,  -738,  2577,  1569,  -738,
     -11,   629,   588,   647,    15,   649,   652,  -738,  1569,  1569,
    2577,   600,  1773,    39,   667,  -738,   675,   451,   589,  -738,
    -738,  -738,  -738,  -738,    17,  -738,   693,   695,   548,   697,
     698,   699,   703,   705,   706,   707,   709,   708,   160,   160,
    1977,  2577,  1569,  1569,  -738,  -738,  -738,   710,  -738,  -738,
    2577,    24,  -738,  -738,  -738,    90,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,  -738,   465,    29,   501,  2577,   677,  -738,  -738,
    -738,  -738,  -738,   -30,   160,  -738,   696,   720,  -738,   465,
     714,   723,  -738,   529,   721,   724,  -738
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -738,  -738,  -738,   560,  -280,  -738,  -440,  -366,  -483,   439,
     199,  -738,  -738,  -738,   206,  -738,   725,  -738,  -738,  -738,
    -738,   -95,   -93,  -738,    85,  -738,  -738,  -738,  -738,  -738,
    -738,    38,   295,   155,   101,  -738,  -738,   109,  -554,  -738,
    -738,  -737,   -70,   154,  -738,  -738,  -738,   -87,  -321,  -738,
    -738,  -671,  -738,   -39,  -108,    10,     3,  -738,   222,   234,
    -367,   595,   -17,  -738,   431,  -207,  -738,  -738,  -282,    83,
    -148,  -738,  -738,  -738,  -738,  -738,   208,  -738,  -738,  -157,
     296,   107,  -738,  -193,    14,   470,  -738,  -114,  -738,  -738,
    -738,  -738,  -738,  -738,  -738,  -123,   701,  -738,  -738,  -738,
     475,   -32,  -232,  -738,  -322,  -738,   651,  -738,   453,  -738,
    -738,  -738,    97,  -738,  -738,  -738,  -738,  -738,  -738,  -738,
    -738,   793,   596,  -738,   590,  -738,  -738,  -738,    35,  -738,
    -738,  -738,   569,  -105,   326,  -738,  -738,  -738,  -738,  -738,
    -738,  -738,   354,   221,  -738,  -738,  -738,  -738,  -738,   368,
    -738,  -738,  -738,  -738,   -20,    52,  -738,  -348,    -8
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -480
static const yytype_int16 yytable[] =
{
     105,   105,   145,   112,    63,   408,   210,   112,   165,   339,
      37,    62,   590,   473,   146,   301,   302,   303,   503,   207,
     494,   208,   103,   106,   449,   364,   252,   209,   886,   308,
     167,   815,   240,   256,   190,   237,   493,   362,   525,   195,
     248,   816,  -221,   667,   791,   713,   715,   504,   764,   807,
     127,   172,   173,   174,   839,   812,   846,   105,   859,   558,
     104,   104,   457,   677,   586,   878,   770,   708,   105,   305,
     884,     1,   216,   679,   680,   324,   189,   306,   170,   188,
     480,   772,   402,     1,  -221,   107,   183,   325,    67,   728,
     197,   113,   852,   481,   817,   108,   219,   482,   222,   333,
     483,    69,   873,  -265,   824,   739,   740,    64,   318,   333,
     353,   319,    65,  -479,   673,  -477,   130,   104,   241,   771,
     749,   245,    66,   350,    37,   351,   484,    76,   104,   705,
     146,   352,   384,   146,   773,   128,   371,   386,   385,   184,
     375,   388,   664,   475,   320,  -265,   709,   889,   185,   186,
     818,   178,   721,   363,   624,   853,   133,   105,   175,   450,
     587,   105,   168,   404,   313,   665,   461,   217,   622,   874,
     887,   253,   112,   505,    21,   716,   146,   238,    37,   269,
     558,   505,   326,   271,   105,    21,   437,   496,   105,   854,
     558,   558,   227,   217,   105,   495,   706,   321,   756,   757,
     758,   759,   760,   761,   762,   763,   329,   540,   105,   819,
     332,   373,   338,   526,   105,   310,  -221,   104,   668,   776,
     714,   104,   372,   526,   808,   373,   376,   145,    37,   668,
     234,   847,   603,   668,   146,   131,  -265,   608,   146,   146,
     808,   105,   105,   105,   104,   668,   164,   497,   104,   498,
    -231,  -231,  -231,   228,   104,   178,   514,   515,   720,   722,
     224,   225,   235,   379,   380,   381,   446,   509,   348,   249,
     166,   513,   811,   447,   348,   499,   181,  -265,  -276,   879,
     689,    37,   229,   305,   612,   880,  -276,   881,    63,   616,
     318,   306,   230,   319,   364,   410,   169,   413,   468,   170,
     882,   104,   104,   104,   697,   698,   699,     1,   316,   317,
     488,   438,   438,   438,   180,   558,   558,   558,   558,   558,
     558,   558,   558,   491,   219,   181,   320,   578,   105,   250,
     105,   182,   105,   823,   430,   431,   432,   433,   434,    63,
     575,     7,   576,   189,   743,   191,   474,  -231,   577,   750,
     777,   778,   779,   196,   780,  -231,   781,  -231,   112,   545,
     546,   547,    70,   774,   782,   783,   784,   785,   786,   617,
     618,   787,    71,    14,   198,   792,   793,   857,   794,   601,
     201,   534,   536,   205,   480,    72,    73,    74,   104,   558,
     479,   212,   487,   146,   146,   214,   563,   481,   564,   565,
      17,   482,   480,   215,   483,    63,   218,   242,   566,   243,
      21,   147,    62,   246,   718,   481,   580,   247,   251,   482,
     581,   255,   483,   257,   695,   261,   719,   260,   146,   263,
     484,   313,   798,   266,    25,   264,   562,   267,   596,   597,
     598,   265,   600,   146,   304,    37,   596,   314,   484,   309,
     146,   146,   146,   105,   146,   273,   274,   275,   146,   276,
     277,   278,   105,   279,   280,   281,   105,   315,   328,   105,
     105,   148,   149,   330,   105,   599,   331,   691,   105,   692,
     693,   115,   116,   335,   609,   333,   343,   338,   342,   355,
     681,   356,   338,   358,   112,   359,   105,   361,   374,   150,
     117,   382,   151,   682,   683,   684,   685,   686,   687,   688,
     118,   387,   401,   104,   338,   119,   684,   685,   686,   687,
     688,   400,   104,   439,   441,   442,   479,     1,   800,   104,
     613,  -114,   120,   152,   104,   440,   440,   440,   620,   458,
     459,   460,   121,   435,   436,   178,  -478,   452,   451,   153,
     453,   454,   154,   455,   457,   456,   104,   562,   755,   745,
     463,   464,   875,    63,   465,   466,   155,   156,   469,   122,
     410,   682,   683,   684,   685,   686,   687,   688,   477,   123,
     470,   490,   510,   489,   516,  -350,   518,   530,   517,   272,
     273,   274,   275,   531,   276,   277,   278,   537,   279,   280,
     281,   157,   538,   124,   540,   560,   282,   158,   174,   292,
     585,   105,   588,   591,   592,   611,   593,   594,   283,   284,
     389,   619,   159,   614,   623,   631,   285,   390,   632,   338,
     666,   391,   682,   683,   684,   685,   686,   687,   688,   392,
     434,   669,   286,   702,   534,   694,   700,   703,   746,   711,
     712,   726,   717,   729,   733,   731,   146,   736,   754,   741,
     146,   766,   767,   393,   775,   801,   803,   804,   805,   806,
     809,   104,   287,   688,   813,   814,   821,    37,   369,   370,
     822,   838,   825,   842,   840,   856,   843,   378,   845,    77,
     848,   855,   383,   849,   596,   536,   394,   860,   858,   861,
     862,   863,   864,   112,   865,   397,   146,   146,   866,   105,
     867,   868,   869,   105,   870,   877,   871,   526,   885,   892,
     890,   405,   406,   407,   409,   411,   336,   893,   270,   896,
     894,   338,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   443,   891,   895,   678,   674,   160,   742,
     395,   704,   790,   595,   735,   536,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   738,   146,   872,   796,
     851,   307,   472,   104,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   288,    89,    90,    91,    92,    93,
      94,    95,    96,   696,   501,    97,    98,    99,   100,   101,
     102,   628,   765,   799,   105,   467,   476,   200,   259,   492,
     508,   129,   357,   349,   512,   621,   377,   602,     0,   589,
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
      83,    10,   137,   156,    66,    24,   358,   100,    41,    71,
     145,    20,    41,    41,   715,    41,    40,    90,    41,    41,
      15,    15,    16,    17,    41,    90,    41,    65,    41,   425,
       8,     9,    62,   546,   120,    41,    20,    55,    76,   112,
      41,    40,   121,   556,   557,   102,     4,   120,   174,    65,
      91,    20,    40,    40,    83,   158,    93,   114,   176,   643,
      76,   213,    53,   104,    73,   168,   128,   108,   121,   173,
     111,     4,   839,    41,   775,   659,   660,   153,    43,   173,
     218,    46,   158,    40,    81,    42,    19,    65,   138,    73,
     216,   141,   168,   218,   114,   218,   137,    90,    76,    79,
     138,   218,   255,   141,    73,   168,   241,   260,    66,   146,
     245,   264,   216,   336,    79,    83,   134,   884,   155,   156,
     129,    89,   216,   216,   502,   116,    99,   165,   122,   307,
     216,   169,   215,   271,   184,   532,   166,   216,   490,   840,
     200,   173,   180,   216,   143,   169,   184,   166,   168,   165,
     546,   216,   209,   169,   192,   143,   143,    92,   196,   150,
     556,   557,    40,   216,   202,   216,   146,   132,   681,   682,
     683,   684,   685,   686,   687,   688,   192,   174,   216,   188,
     196,   243,   202,   216,   222,   180,   215,   165,   216,    59,
     216,   169,   242,   216,   216,   257,   246,   247,   218,   216,
      45,   216,   464,   216,   242,    94,   174,   469,   246,   247,
     216,   249,   250,   251,   192,   216,   165,   152,   196,   154,
      15,    16,    17,   101,   202,    89,   379,   380,   625,   626,
     178,   179,    77,   249,   250,   251,     5,   372,   216,    30,
       0,   376,   755,    12,   222,   180,    41,   215,   112,   189,
     560,   271,   130,   112,   477,   195,   120,   197,   285,   482,
      43,   120,   140,    46,   501,   285,   107,   287,   330,   174,
     210,   249,   250,   251,   586,   587,   588,    40,    67,    68,
     342,   301,   302,   303,   128,   681,   682,   683,   684,   685,
     686,   687,   688,   355,   356,    41,    79,   435,   336,    90,
     338,    41,   340,   773,    34,    35,    36,    37,    38,   336,
     435,    74,   435,     4,   665,   103,   336,   112,   435,   670,
     190,   191,   192,   186,   194,   120,   196,   122,   366,    28,
      29,    30,   158,   711,   204,   205,   206,   207,   208,   483,
     484,   211,   168,   106,     4,   184,   185,   817,   187,   132,
     103,   401,   402,   169,    91,   181,   182,   183,   336,   755,
     338,   135,   340,   401,   402,   168,     8,   104,    10,    11,
     133,   108,    91,   123,   111,   402,    90,    42,    20,    89,
     143,     3,   402,    42,   121,   104,   436,   216,   158,   108,
     437,   203,   111,    89,   581,   112,   619,   203,   436,   214,
     137,   451,   121,    40,   167,   212,   426,   175,   458,   459,
     460,   177,   462,   451,    54,   435,   466,   118,   137,   167,
     458,   459,   460,   461,   462,     4,     5,     6,   466,     8,
       9,    10,   470,    12,    13,    14,   474,   157,    20,   477,
     478,    63,    64,   216,   482,   461,   102,     8,   486,    10,
      11,    45,    46,    86,   470,   173,    14,   477,   216,   166,
      19,   216,   482,    90,   502,     5,   504,    40,    24,    91,
      64,     4,    94,    32,    33,    34,    35,    36,    37,    38,
      74,     5,   146,   461,   504,    79,    34,    35,    36,    37,
      38,    61,   470,   301,   302,   303,   474,    40,   721,   477,
     478,    40,    96,   125,   482,   301,   302,   303,   486,   318,
     319,   320,   106,    40,    42,    89,    42,    24,   216,   141,
      24,    24,   144,   118,    62,   118,   504,   547,    19,   667,
     216,    54,   842,   560,    86,    40,   158,   159,    54,   133,
     560,    32,    33,    34,    35,    36,    37,    38,   216,   143,
     121,   166,     4,   216,    40,   177,    41,    41,   216,     3,
       4,     5,     6,   149,     8,     9,    10,   170,    12,    13,
      14,   193,   216,   167,   174,    40,    20,   199,    17,   170,
     216,   619,   112,     4,     4,    41,    24,    24,    32,    33,
      34,   108,   214,   124,    41,    41,    40,    41,     5,   619,
      24,    45,    32,    33,    34,    35,    36,    37,    38,    53,
      38,    40,    56,     4,   664,    41,    59,     4,   668,   166,
     109,    40,    47,    40,    40,   127,   664,    40,    82,    41,
     668,     4,   142,    77,    40,    97,     5,     5,     5,     5,
      40,   619,    86,    38,    24,   202,    10,   667,   239,   240,
      10,   216,    24,    54,    40,    10,    98,   248,    41,     3,
      41,    24,   253,    41,   714,   715,   110,     4,   109,     4,
     152,     4,     4,   711,     5,   266,   714,   715,     5,   717,
       5,     5,     5,   721,     5,     5,     8,   216,    41,     5,
      24,   282,   283,   284,   285,   286,    40,     4,   168,     5,
     201,   721,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   304,    24,    24,   547,   541,    23,   664,
     164,   596,   714,   458,   653,   775,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   657,   775,   838,   717,
     809,   176,   333,   721,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   585,   363,   209,   210,   211,   212,   213,
     214,   505,   695,   720,   812,   330,   336,   106,   157,   356,
     371,    18,   222,   217,   375,   489,   247,   463,    -1,   451,
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
     140,   280,   281,   282,    45,    77,   296,    24,   166,   350,
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
     226,   350,   371,   318,    24,   350,   371,   349,   226,   301,
     301,   301,     4,   226,   312,    66,   312,     5,   312,    34,
      41,    45,    53,    77,   110,   164,   221,   226,   237,   288,
      61,   146,    40,   267,   271,   226,   226,   226,   221,   226,
     272,   226,   229,   272,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    40,    42,   143,   272,   275,
     276,   275,   275,   226,   292,   293,     5,    12,   285,   285,
     287,   216,    24,    24,    24,   118,   118,    62,   360,   360,
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
     223,     4,     4,    24,    24,   249,   371,   371,   371,   301,
     371,   132,   359,   319,   129,   247,   248,   249,   319,   301,
     226,    41,   300,   372,   124,   304,   300,   304,   304,   108,
     372,   351,   321,    41,   374,    80,   299,   300,   297,   226,
     226,    41,     5,   226,    90,   226,    90,   226,    90,   226,
      50,    51,    52,    57,    65,    69,    70,    72,    78,    88,
     105,   115,   117,   119,   131,   148,   161,   162,   163,   171,
     172,   250,   226,    41,   216,   277,    24,    41,   216,    40,
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
     226,   225,    90,    24,   202,    10,    20,    73,   129,   188,
     257,    10,    10,   223,   268,    24,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   216,    41,
      40,   226,    54,    98,   295,    41,    41,   216,    41,    41,
     226,   270,    53,   116,   150,    24,    10,   223,   109,    41,
       4,     4,   152,     4,     4,     5,     5,     5,     5,     5,
       5,     8,   259,   258,   268,   221,   226,     5,    41,   189,
     195,   197,   210,   369,    41,    41,    58,   200,   370,   258,
      24,    24,     5,     4,   201,    24,     5
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result, yyscan_t scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseResult* result;
    yyscan_t scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result, yyscan_t scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseResult* result;
    yyscan_t scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParseResult* result, yyscan_t scanner)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, result, scanner)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    ParseResult* result;
    yyscan_t scanner;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, result, scanner); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParseResult* result, yyscan_t scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, result, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    ParseResult* result;
    yyscan_t scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (ParseResult* result, yyscan_t scanner);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (ParseResult* result, yyscan_t scanner)
#else
int
yyparse (result, scanner)
    ParseResult* result;
    yyscan_t scanner;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_STMT_LIST,(yyvsp[(1) - (2)].node) );
      result->Doc.SetObject().AddMember("ROOT",*(yyval.node) , result->Doc.GetAllocator());
      //result->result_tree_ = $$;
      delete (yyval.node);
      YYACCEPT;
    ;}
    break;

  case 3:

    {
      if ((yyvsp[(3) - (3)].node) != NULL)
        /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3 );
        {
        	malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
        }
      else
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 4:

    {
      (yyval.node) = ((yyvsp[(1) - (1)].node) != NULL) ? (yyvsp[(1) - (1)].node) : NULL;
    ;}
    break;

  case 5:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 6:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 7:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 8:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 9:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 10:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 11:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 12:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 13:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 14:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 15:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 16:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 17:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 18:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 19:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 20:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 21:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 22:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 23:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 24:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 25:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 26:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 27:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 28:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 29:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 30:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 31:

    { (yyval.node) = NULL; ;}
    break;

  case 32:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 33:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 34:

    { //$$ = $1;
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
		 SafeAddMember((yyval.node),"COLUMN_NAME"  ,(yyvsp[(1) - (1)].node), result->Doc.GetAllocator());

    	 ;}
    break;

  case 35:

    {
     // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, $3);
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, $3);
				malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember((yyval.node),"RELATION_NAME",(yyvsp[(1) - (3)].node), result->Doc.GetAllocator());
				SafeAddMember((yyval.node),"COLUMN_NAME"  ,(yyvsp[(3) - (3)].node), result->Doc.GetAllocator());
     // dup_expr_string($$->str_value_, result, @3.first_column, @3.last_column);
    ;}
    break;

  case 36:

    {
      // malloc_terminal_node(node, result->malloc_pool_, T_STAR);
      rapidjson::Value* node ;
      malloc_terminal_node(node, result->Doc.GetAllocator(), T_STAR);
      // malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NAME_FIELD, 2, $1, node);
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_NAME_FIELD, $1, node);
				malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_OP_NAME_FIELD);
				SafeAddMember((yyval.node),"RELATION_NAME",(yyvsp[(1) - (3)].node), result->Doc.GetAllocator());
				SafeAddMember((yyval.node),"COLUMN_NAME"  ,node, result->Doc.GetAllocator());
    ;}
    break;

  case 37:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","STRING", result->Doc.GetAllocator());;}
    break;

  case 38:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","DATE_VALUE", result->Doc.GetAllocator());;}
    break;

  case 39:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","INTNUM", result->Doc.GetAllocator());;}
    break;

  case 40:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","APPROXNUM", result->Doc.GetAllocator());;}
    break;

  case 41:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","BOOL", result->Doc.GetAllocator());;}
    break;

  case 42:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","NULL", result->Doc.GetAllocator());;}
    break;

  case 43:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","QUESTIONMARK", result->Doc.GetAllocator());;}
    break;

  case 44:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 45:

    { (yyval.node) = (yyvsp[(1) - (1)].node); (yyvsp[(1) - (1)].node)->AddMember("CONST_TYPE","SYSTEM_VARIABLE", result->Doc.GetAllocator());;}
    break;

  case 46:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 47:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 48:

    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 49:

    {
      /*ParseNode *node = NULL;*/
      /*malloc_non_terminal_node(node, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/
      /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, node);*/
      rapidjson::Value* node ;
      //malloc_non_terminal_node(&node, result->Doc.GetAllocator(), T_LINK_NODE, $2, $4);
      malloc_list_node(&node,result->Doc.GetAllocator(),2, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
      merge_nodes((yyval.node), result->Doc.GetAllocator(),T_EXPR_LIST, node);

    ;}
    break;

  case 50:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
      /*
      yyerror(&@1, result, "CASE expression is not supported yet!");
      YYABORT;
      */
    ;}
    break;

  case 51:

    {  (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 52:

    {  (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 53:

    {	
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SUB_SELECT);
      SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[(1) - (1)].node), result->Doc.GetAllocator());	
    	//$$ = $1; 
    ;}
    break;

  case 54:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EXISTS, 1, $2);*/
    	//malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_OP_EXISTS, $2);
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_OP_EXISTS);
    	(yyval.node)->AddMember("SUB_LINK_TYPE","EXISTS", result->Doc.GetAllocator());
    	SafeAddMember((yyval.node),"SUB_LINK_BODY",(yyvsp[(2) - (2)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 55:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 56:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_POS, (yyvsp[(2) - (2)].node));

    ;}
    break;

  case 57:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_NEG, (yyvsp[(2) - (2)].node));

    ;}
    break;

  case 58:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","ADDX", T_OP_ADD,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));  ;}
    break;

  case 59:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS, 2, $1, $3); */ malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MINUSX",T_OP_MINUS,(yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 60:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MULX", T_OP_MUL,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 61:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","DIVX", T_OP_DIV,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 62:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","REMX", T_OP_REM,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 63:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POWX", T_OP_POW,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 64:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3); */   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MODX", T_OP_MOD,  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 65:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 66:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POS, 1, $2);*/
    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POS", T_OP_POS, (yyvsp[(2) - (2)].node));
    ;}
    break;

  case 67:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NEG, 1, $2);*/
    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NEG", T_OP_NEG, (yyvsp[(2) - (2)].node));
    ;}
    break;

  case 68:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_ADD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","ADD", T_OP_ADD, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));    ;}
    break;

  case 69:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MINUS,2, $1, $3);*/  malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MINUS", T_OP_MINUS, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));;}
    break;

  case 70:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MUL, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MUL", T_OP_MUL, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));   ;}
    break;

  case 71:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_DIV, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","DIV", T_OP_DIV, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));   ;}
    break;

  case 72:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_REM, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","REM", T_OP_REM, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));   ;}
    break;

  case 73:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_POW, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","POW", T_OP_POW, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));   ;}
    break;

  case 74:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_MOD, 2, $1, $3);*/   malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","MOD", T_OP_MOD, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));   ;}
    break;

  case 75:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LE", T_OP_LE, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 76:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LT", T_OP_LT, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 77:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_EQ, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","EQ", T_OP_EQ, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 78:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","GE", T_OP_GE, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 79:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_GT, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","GT", T_OP_GT, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 80:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NE, 2, $1, $3);*/    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NE", T_OP_NE, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));     ;}
    break;

  case 81:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 2, $1, $3); */    malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","LIKE", T_OP_LIKE, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 82:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_LIKE, 2, $1, $4);*/ ;}
    break;

  case 83:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_AND, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","AND", T_OP_AND, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 84:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_OR, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","OR", T_OP_OR, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 85:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT, 1, $2);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT", T_OP_NOT, (yyvsp[(2) - (2)].node));
    ;}
    break;

  case 86:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NULL", T_OP_IS, (yyvsp[(1) - (3)].node));
    ;}
    break;

  case 87:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT_NULL", T_OP_IS_NOT, (yyvsp[(1) - (4)].node));
    ;}
    break;

  case 88:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 89:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, (yyvsp[(1) - (4)].node),(yyvsp[(4) - (4)].node));
    ;}
    break;

  case 90:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS", T_OP_IS, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 91:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IS_NOT, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IS_NOT", T_OP_IS_NOT, (yyvsp[(1) - (4)].node),(yyvsp[(4) - (4)].node));

    ;}
    break;

  case 92:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_BTW, 3, $1, $3, $5);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","BTW", T_OP_BTW, (yyvsp[(1) - (5)].node),(yyvsp[(3) - (5)].node),(yyvsp[(5) - (5)].node));
    ;}
    break;

  case 93:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_BTW, 3, $1, $4, $6);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT_BTW", T_OP_NOT_BTW, (yyvsp[(1) - (6)].node),(yyvsp[(4) - (6)].node),(yyvsp[(6) - (6)].node));
    ;}
    break;

  case 94:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_IN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","IN", T_OP_IN, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 95:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_NOT_IN, 2, $1, $4);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","NOT_IN", T_OP_NOT_IN, (yyvsp[(1) - (4)].node),(yyvsp[(4) - (4)].node));
    ;}
    break;

  case 96:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_CNN, 2, $1, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","CNN", T_OP_CNN, (yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 97:

    {
    	(yyval.node) = (yyvsp[(1) - (1)].node);	
    	malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_OP_IN);
    	(yyval.node)->AddMember("SUB_LINK_TYPE","IN", result->Doc.GetAllocator());
    	SafeAddMember((yyval.node),"SUB_LINK_BODY",(yyvsp[(1) - (1)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 98:

    { 
    /*merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $2);*/ 
      merge_nodes((yyval.node), result->Doc.GetAllocator(),T_EXPR_LIST, (yyvsp[(2) - (3)].node));

    ;}
    break;

  case 99:

    {
      /*merge_nodes($$, result->malloc_pool_, T_WHEN_LIST, $3);
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_CASE, 3, $2, $$, $4);*/
       // merge_nodes($$, result->Doc.GetAllocator(),T_WHEN_LIST, $3);
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","CASE", T_CASE,  (yyvsp[(2) - (5)].node), (yyval.node), (yyvsp[(4) - (5)].node));

    ;}
    break;

  case 100:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 101:

    { (yyval.node) = NULL; ;}
    break;

  case 102:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 103:

    {
     /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,  $1, $2);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));

     ;}
    break;

  case 104:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_THEN, 2, $2, $4);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"OP_TYPE","THEN", T_THEN,  (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    ;}
    break;

  case 105:

    { (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 106:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_NULL);*/ ;}
    break;

  case 107:

    {
    	
      if (strcasecmp_((yyvsp[(1) - (4)].node), "count") != 0)
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
    ;}
    break;

  case 108:

    {
    	        

      if (strcasecmp_((yyvsp[(1) - (5)].node), "count") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));

      }
      else if (strcasecmp_((yyvsp[(1) - (5)].node), "sum") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, $3, $4);*/
        
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));

      }
      else if (strcasecmp_((yyvsp[(1) - (5)].node), "max") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, $3, $4);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MAX", T_FUN_MAX, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (5)].node), "min") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MIN", T_FUN_MIN, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (5)].node), "avg") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, $3, $4);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","AVG", T_FUN_AVG, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else
      {
        yyerror(&(yylsp[(1) - (5)]), result, "Wrong system function with 'DISTINCT/ALL'!");
        YYABORT;
      }
    ;}
    break;

  case 109:

    {
      if (strcasecmp_((yyvsp[(1) - (4)].node), "count") == 0)
      {
       //if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       //{
       //  yyerror(&@1, result, "COUNT function only support 1 parameter!");
       //  YYABORT;
       //}
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_COUNT, 2, NULL, $3);*/
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","COUNT", T_FUN_COUNT, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (4)].node), "sum") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "SUM function only support 1 parameter!");
       //   YYABORT;
       // }
       // /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SUM, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SUM", T_FUN_SUM, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (4)].node), "max") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "MAX function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MAX, 2, NULL, $3);*/
       malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MAXX", T_FUN_MAX, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (4)].node), "min") == 0)
      {
       // if ((*$3)["type_"].GetInt() == T_LINK_NODE)
       // {
       //   yyerror(&@1, result, "MIN function only support 1 parameter!");
       //   YYABORT;
       // }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_MIN, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","MINX", T_FUN_MIN, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp_((yyvsp[(1) - (4)].node), "avg") == 0)
      {
      //  if ((*$3)["type_"].GetInt() == T_LINK_NODE)
      //  {
      //    yyerror(&@1, result, "AVG function only support 1 parameter!");
      //    YYABORT;
      //  }
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_AVG, 2, NULL, $3);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","AVGX", T_FUN_AVG, (yyvsp[(3) - (4)].node));
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
         merge_nodes(params, result->Doc.GetAllocator(),T_EXPR_LIST, (yyvsp[(3) - (4)].node));
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUNX", T_FUN_SYS, (yyvsp[(1) - (4)].node), params);
      
      }
    ;}
    break;

  case 110:

    {
      if (strcasecmp_((yyvsp[(1) - (6)].node), "cast") == 0)
      {
        (*(yyvsp[(5) - (6)].node))["value_"].Swap((*(yyvsp[(5) - (6)].node))["type_"]);
        rapidjson::Value tmp(T_INT);
        (*(yyvsp[(5) - (6)].node))["type_"].Swap(tmp);
        /*ParseNode *params = NULL;*/
        /*malloc_non_terminal_node(params, result->malloc_pool_, T_EXPR_LIST, 2, $3, $5);*/
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, params);*/
         rapidjson::Value *params ;
         malloc_non_terminal_node(&params, result->Doc.GetAllocator(), T_EXPR_LIST,(yyvsp[(3) - (6)].node),(yyvsp[(5) - (6)].node));
         malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CAST", T_FUN_SYS, (yyvsp[(1) - (6)].node), params);
      }
      else
      {
        yyerror(&(yylsp[(1) - (6)]), result, "AS support cast function only!");
        YYABORT;
      }
    ;}
    break;

  case 111:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 2, $1, $3);*/
      malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));

    ;}
    break;

  case 112:

    {
      if (strcasecmp_((yyvsp[(1) - (3)].node), "now") == 0 ||
          strcasecmp_((yyvsp[(1) - (3)].node), "current_time") == 0 ||
          strcasecmp_((yyvsp[(1) - (3)].node), "current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME", T_CUR_TIME, (yyvsp[(1) - (3)].node));

      }
      else if (strcasecmp_((yyvsp[(1) - (3)].node), "strict_current_timestamp") == 0)
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_CUR_TIME_UPS, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","CUR_TIME_UPS", T_CUR_TIME_UPS, (yyvsp[(1) - (3)].node));

      }
      else
      {
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_FUN_SYS, 1, $1);*/
        malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","SYS_FUN", T_FUN_SYS, (yyvsp[(1) - (3)].node));

      }
      //yyerror(&@1, result, "system/user-define function is not supported yet!");*/
      //YYABORT;
    ;}
    break;

  case 113:

    {
      (yyval.node) = (yyvsp[(1) - (4)].node);
      /*$$->children_[0] = $3;*/
     // $$->PushBack($3, result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"WHEN_FUNC_STMT",(yyvsp[(3) - (4)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 114:

    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ROW_COUNT, 1, NULL);*/
     malloc_non_terminal_node_with_type(&(yyval.node), result->Doc.GetAllocator(),"FUN_TYPE","ROW_COUNT", T_ROW_COUNT, NULL);

    ;}
    break;

  case 119:

    {
       /*malloc_terminal_node($$, result->malloc_pool_, T_ALL);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_ALL);
			  

    ;}
    break;

  case 120:

    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/          
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_DISTINCT);

    ;}
    break;

  case 121:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DELETE, 3, $3, $4, $5);*/
      malloc_terminal_node( (yyval.node), result->Doc.GetAllocator(), T_DELETE );
      (yyval.node)->AddMember("OPERATION_NAME","DELETE_STMT", result->Doc.GetAllocator() );
      
     SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[(3) - (5)].node), result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[(4) - (5)].node), result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"OPT_WHEN",(yyvsp[(5) - (5)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 122:

    {
    
         malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_UPDATE);
         (yyval.node)->AddMember("OPERATION_NAME","UPDATE_STMT", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[(3) - (7)].node), result->Doc.GetAllocator());
     		 SafeAddMember((yyval.node),"SET_LIST",(yyvsp[(5) - (7)].node), result->Doc.GetAllocator());
     		 SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[(6) - (7)].node), result->Doc.GetAllocator());
				 SafeAddMember((yyval.node),"WHEN_CLAUSE",(yyvsp[(7) - (7)].node), result->Doc.GetAllocator());
				 SafeAddMember((yyval.node),"HINTS",(yyvsp[(2) - (7)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 123:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 124:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1,$3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
 
    ;}
    break;

  case 125:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_ASSIGN_ITEM, 2, $1, $3);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_ASSIGN_ITEM);
      SafeAddMember((yyval.node),"COLUNM_NAME",(yyvsp[(1) - (3)].node), result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"EXPR",(yyvsp[(3) - (3)].node), result->Doc.GetAllocator());

    ;}
    break;

  case 126:

    {
  malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_CREATE_INDEX  );
  (yyval.node)->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if((yyvsp[(2) - (12)].node)) (yyval.node)->AddMember("CONSTRAINT_TYPE",*(yyvsp[(2) - (12)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_NAME",*(yyvsp[(4) - (12)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("RELATION_NAME",*(yyvsp[(6) - (12)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_TYPE",*(yyvsp[(8) - (12)].node), result->Doc.GetAllocator() ); 
  (yyval.node)->AddMember("COLUMN_LIST",*(yyvsp[(10) - (12)].node), result->Doc.GetAllocator() ); 
  if((yyvsp[(12) - (12)].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[(12) - (12)].node), result->Doc.GetAllocator() ); 
   // malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_CREATE_INDEX,$2, $4, $6, index_column_list,table_options);
   //malloc_terminal_node($$,result->Doc.GetAllocator(), T_INDEX_UNIQUE);  
   //$$->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
;}
    break;

  case 127:

    {
	malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_CREATE_INDEX  );
  (yyval.node)->AddMember("OPERATION_NAME","CREATE_INDEX", result->Doc.GetAllocator() );
  if((yyvsp[(2) - (10)].node)) (yyval.node)->AddMember("CONSTRAINT_TYPE",*(yyvsp[(2) - (10)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("INDEX_NAME",*(yyvsp[(4) - (10)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("RELATION_NAME",*(yyvsp[(6) - (10)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("COLUMN_LIST",*(yyvsp[(8) - (10)].node), result->Doc.GetAllocator() ); 
  if((yyvsp[(10) - (10)].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[(10) - (10)].node), result->Doc.GetAllocator() ); 

;}
    break;

  case 128:

    {
		
		  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_UNIQUE); 
		  (yyval.node)->AddMember("str_value_","UNIQUE", result->Doc.GetAllocator() ); 
	;}
    break;

  case 129:

    {  
		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_FULLTEXT); 
		(yyval.node)->AddMember("str_value_","FULLTEXT", result->Doc.GetAllocator() ); 

	;}
    break;

  case 130:

    {  
		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_SPATIAL); 
		(yyval.node)->AddMember("str_value_","SPATIAL", result->Doc.GetAllocator() ); 

	;}
    break;

  case 131:

    {
		(yyval.node) = NULL;
	;}
    break;

  case 132:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_HASH);
		 (yyval.node)->AddMember("str_value_","HASH", result->Doc.GetAllocator() );
	;}
    break;

  case 133:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_BTREE); 
		 (yyval.node)->AddMember("str_value_","BTREE", result->Doc.GetAllocator() );
	;}
    break;

  case 134:

    { 
		 malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_INDEX_SKIPLIST); 
		 (yyval.node)->AddMember("str_value_","SKIPLIST", result->Doc.GetAllocator() );
	;}
    break;

  case 135:

    { (yyval.node) = NULL; ;}
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
  if((yyvsp[(3) - (8)].node)) (yyval.node)->AddMember("IS_EXISTS",*(yyvsp[(3) - (8)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[(4) - (8)].node), result->Doc.GetAllocator() );
  (yyval.node)->AddMember("TABLE_ELEMENT",*(yyvsp[(6) - (8)].node), result->Doc.GetAllocator() );
  if((yyvsp[(8) - (8)].node))(yyval.node)->AddMember("OPT_OPITION",*(yyvsp[(8) - (8)].node), result->Doc.GetAllocator() ); 
    
    
    ;}
    break;

  case 137:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_IF_NOT_EXISTS);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_IF_NOT_EXISTS);
      (yyval.node)->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    ;}
    break;

  case 138:

    { (yyval.node) = NULL; ;}
    break;

  case 139:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 140:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 141:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 142:

    {
      /*ParseNode* col_list= NULL;*/
      /*merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, $4);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIMARY_KEY, 1, col_list);*/
         rapidjson::Value *col_list ;
         merge_nodes(col_list, result->Doc.GetAllocator(),  T_COLUMN_LIST,(yyvsp[(4) - (5)].node));
         malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_PRIMARY_KEY, col_list);

    ;}
    break;

  case 143:

    {
      /*ParseNode *attributes = NULL;*/
      /*merge_nodes(attributes, result->malloc_pool_, T_COLUMN_ATTRIBUTES, $3);*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DEFINITION, 3, $1, $2, attributes);*/
 
			   rapidjson::Value *attributes;
			   merge_nodes(attributes, result->Doc.GetAllocator(),  T_COLUMN_ATTRIBUTES,(yyvsp[(3) - (3)].node));
         malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_COLUMN_DEFINITION, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), attributes);
    
    ;}
    break;

  case 144:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT );*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
      (yyval.node)->AddMember("str_value_","TINYINT", result->Doc.GetAllocator() );

    ;}
    break;

  case 145:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_SHORT);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_SHORT);
      (yyval.node)->AddMember("str_value_","SMALLINT", result->Doc.GetAllocator() );

    ;}
    break;

  case 146:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT);*/ 
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
      (yyval.node)->AddMember("str_value_","INT", result->Doc.GetAllocator() );
    ;}
    break;

  case 147:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_INT);*/ 
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_INT);
       (yyval.node)->AddMember("str_value_","INT", result->Doc.GetAllocator() );

    ;}
    break;

  case 148:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_LONGLONG);*/
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_LONGLONG);
       (yyval.node)->AddMember("str_value_","BIGINT", result->Doc.GetAllocator() );

     ;}
    break;

  case 149:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        (yyval.node)->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
}
      else{
        /*merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
        malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);
        (yyval.node)->AddMember("str_value_","DECIMAL", result->Doc.GetAllocator() );
 }
      yyerror(&(yylsp[(1) - (2)]), result, "DECIMAL type is not supported");
      YYABORT;
    ;}
    break;

  case 150:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DECIMAL);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DECIMAL);}
      else{
       /* merge_nodes($$, result->malloc_pool_, T_TYPE_DECIMAL, $2);*/
     merge_nodes((yyval.node), result->Doc.GetAllocator(),T_TYPE_DECIMAL, (yyvsp[(2) - (2)].node));}
     (yyval.node)->AddMember("str_value_","NUMERIC", result->Doc.GetAllocator() );
       
      yyerror(&(yylsp[(1) - (2)]), result, "NUMERIC type is not supported");
      YYABORT;
    ;}
    break;

  case 151:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_BOOLEAN );*/ 
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_BOOLEAN);
    (yyval.node)->AddMember("str_value_","BOOLEAN", result->Doc.GetAllocator() );

    ;}
    break;

  case 152:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_FLOAT, 1, $2);*/ 
        malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_FLOAT,(yyvsp[(2) - (2)].node));
        (yyval.node)->AddMember("str_value_","FLOAT", result->Doc.GetAllocator() );

    ;}
    break;

  case 153:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DOUBLE);
    (yyval.node)->AddMember("str_value_","REAL", result->Doc.GetAllocator() );

     ;}
    break;

  case 154:

    {
      (void)((yyvsp[(2) - (2)].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DOUBLE);*/
       malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DOUBLE);
       (yyval.node)->AddMember("str_value_","DOUBLE", result->Doc.GetAllocator() );
    ;}
    break;

  case 155:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP, 1, $2);*/
     malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);}
     (yyval.node)->AddMember("str_value_","TIMESTAMP", result->Doc.GetAllocator() );
 
    ;}
    break;

  case 156:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIMESTAMP);*/
         malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIMESTAMP);
         (yyval.node)->AddMember("str_value_","DATETIME", result->Doc.GetAllocator() );

     ;}
    break;

  case 157:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER);}

      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
     malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER,(yyvsp[(2) - (2)].node));
     }
     (yyval.node)->AddMember("str_value_","CHARACTER", result->Doc.GetAllocator() );
  
    ;}
    break;

  case 158:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER);
      (yyval.node)->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
      }
   
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_CHARACTER, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_CHARACTER,(yyvsp[(2) - (2)].node)); 
      (yyval.node)->AddMember("str_value_","BINARY", result->Doc.GetAllocator() );
       }
    ;}
    break;

  case 159:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR);
      (yyval.node)->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
      }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR,(yyvsp[(2) - (2)].node));
      (yyval.node)->AddMember("str_value_","VARCHAR", result->Doc.GetAllocator() );
         }
    ;}
    break;

  case 160:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /* malloc_terminal_node(result->malloc_pool_, T_TYPE_VARCHAR);*/
      malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR); 
      (yyval.node)->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         }
      else{
        /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_VARCHAR, 1, $2);*/
      malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_VARCHAR, (yyvsp[(2) - (2)].node));
      (yyval.node)->AddMember("str_value_","VARBINARY", result->Doc.GetAllocator() );
         } 
  
    ;}
    break;

  case 161:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_CREATETIME);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_CREATETIME);  
    (yyval.node)->AddMember("str_value_","CREATETIME", result->Doc.GetAllocator() );  
     ;}
    break;

  case 162:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_MODIFYTIME);*/ 
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_MODIFYTIME);    
    (yyval.node)->AddMember("str_value_","MODIFYTIME", result->Doc.GetAllocator() ); 
    ;}
    break;

  case 163:

    {
      /* malloc_terminal_node($$, result->malloc_pool_, T_TYPE_DATE);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_DATE);     
    (yyval.node)->AddMember("str_value_","DATE", result->Doc.GetAllocator() );
      yyerror(&(yylsp[(1) - (1)]), result, "DATE type is not supported");
      YYABORT;
    ;}
    break;

  case 164:

    {
      if ((yyvsp[(2) - (2)].node) == NULL){
        /*malloc_terminal_node($$, result->malloc_pool_, T_TYPE_TIME);*/
    malloc_terminal_node((yyval.node), result->Doc.GetAllocator(), T_TYPE_TIME);    } 
      else{       /*malloc_non_terminal_node($$, result->malloc_pool_, T_TYPE_TIME, 1, $2);*/
    malloc_non_terminal_node(&(yyval.node), result->Doc.GetAllocator(), T_TYPE_TIME,(yyvsp[(2) - (2)].node));     }
    (yyval.node)->AddMember("str_value_","TIME", result->Doc.GetAllocator() );
      yyerror(&(yylsp[(1) - (2)]), result, "TIME type is not supported");
      YYABORT;
    ;}
    break;

  case 165:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $2, $4);*/ 
     //malloc_non_terminal_node(&$$, result->Doc.GetAllocator(), T_LINK_NODE,$2, $4);      
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
     (yyval.node)->AddMember("str_value_","not_exists", result->Doc.GetAllocator() );
    ;}
    break;

  case 166:

    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 167:

    { (yyval.node) = NULL; ;}
    break;

  case 168:

    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 169:

    { (yyval.node) = NULL; ;}
    break;

  case 170:

    { (yyval.node) = NULL; ;}
    break;

  case 171:

    { (yyval.node) = NULL; ;}
    break;

  case 172:

    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 173:

    { (yyval.node) = NULL; ;}
    break;

  case 174:

    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 175:

    { (yyval.node) = NULL; ;}
    break;

  case 176:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/ 
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $2);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
    ;}
    break;

  case 177:

    { (yyval.node) = NULL; ;}
    break;

  case 178:

    {
      (void)((yyvsp[(2) - (2)].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_NOT_NULL);
    ;}
    break;

  case 179:

    {
      (void)((yyvsp[(1) - (1)].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_NULL);

    ;}
    break;

  case 180:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $2);*/ 
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CONSTR_DEFAULT,(yyvsp[(2) - (2)].node));

    ;}
    break;

  case 181:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_AUTO_INCREMENT);*/ 
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_AUTO_INCREMENT);

    ;}
    break;

  case 182:

    { /* malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_PRIMARY_KEY);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSTR_PRIMARY_KEY);
     ;}
    break;

  case 183:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 184:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
   //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE,$1, $3);
   malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 185:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 186:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_JOIN_INFO, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_JOIN_INFO, (yyvsp[(3) - (3)].node));
   
    ;}
    break;

  case 187:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXPIRE_INFO, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_EXPIRE_INFO, (yyvsp[(3) - (3)].node));
  
    ;}
    break;

  case 188:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_TABLET_MAX_SIZE, (yyvsp[(3) - (3)].node));
 
    ;}
    break;

  case 189:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
   		malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_EXTERN_SIZE);
   		if((yyvsp[(3) - (3)].node))(yyval.node)->AddMember("EXTERN_SIZE",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );
    ;}
    break;

  case 190:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->/*malloc_pool_, T_TABLET_MAX_SIZE, 1, $3);*/
	     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_SKIP_LEVEL);
   		if((yyvsp[(3) - (3)].node))(yyval.node)->AddMember("SKIP_LEVEL",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() ); 
    ;}
    break;

  case 191:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_BLOCK_SIZE, 1, $3);*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_TABLET_BLOCK_SIZE);
   	 if((yyvsp[(3) - (3)].node))(yyval.node)->AddMember("TABLET_BLOCK_SIZE",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );
    ;}
    break;

  case 192:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_TABLET_ID, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_TABLET_ID, (yyvsp[(3) - (3)].node));
 
    ;}
    break;

  case 193:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_REPLICA_NUM, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_REPLICA_NUM, (yyvsp[(3) - (3)].node));
 
    ;}
    break;

  case 194:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMPRESS_METHOD, 1, $3);*/
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_COMPRESS_METHOD, (yyvsp[(3) - (3)].node));
  
    ;}
    break;

  case 195:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_USE_BLOOM_FILTER, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_USE_BLOOM_FILTER, (yyvsp[(3) - (3)].node));
   
    ;}
    break;

  case 196:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      /* malloc_terminal_node($$, result->malloc_pool_, T_CONSISTENT_MODE);*/
       /*$$->value_ = 1;*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_CONSISTENT_MODE);
    rapidjson::Value val_val_(1);
    (yyval.node)->AddMember("value_", val_val_, result->Doc.GetAllocator());
    
    ;}
    break;

  case 197:

    {
      (void)((yyvsp[(2) - (3)].node)); /*  make bison mute*/
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COMMENT, 1, $3);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_COMMENT,(yyvsp[(3) - (3)].node));

    ;}
    break;

  case 198:

    { (yyval.node) = NULL; ;}
    break;

  case 199:

    { (yyval.node) = NULL; ;}
    break;

  case 200:

    {
      /*ParseNode *tables = NULL;
      merge_nodes(tables, result->malloc_pool_, T_TABLE_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_DROP_TABLE, 2, $3, tables);
      */
      
      rapidjson::Value *tables ;
      merge_nodes(tables, result->Doc.GetAllocator(),T_TABLE_LIST, (yyvsp[(4) - (4)].node));
		  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_DROP_TABLE);      
      (yyval.node)->AddMember("OPERATION_NAME","DROP_TABLE", result->Doc.GetAllocator() );
      if((yyvsp[(3) - (4)].node))(yyval.node)->AddMember("IF_EXISTS",*(yyvsp[(3) - (4)].node), result->Doc.GetAllocator() );
			(yyval.node)->AddMember("TABLE_LIST",*tables, result->Doc.GetAllocator() );
   
    ;}
    break;

  case 201:

    { (yyval.node) = NULL; ;}
    break;

  case 202:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_IF_EXISTS);*/ 
   malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_IF_EXISTS);   ;}
    break;

  case 203:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 204:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
  // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);  
  malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));    
  
    ;}
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
      merge_nodes(val_list, result->Doc.GetAllocator(),T_VALUE_LIST, (yyvsp[(6) - (7)].node));
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_INSERT,$3, $4,val_list,NULL,$1,$7);  
         malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INSERT);
         (yyval.node)->AddMember("OPERATION_NAME","INSERT_TABLE", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[(3) - (7)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"OPT_INSERT_COLUMNS",(yyvsp[(4) - (7)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"VALUE_LIST", val_list, result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[(1) - (7)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"OPT_WHEN",(yyvsp[(7) - (7)].node), result->Doc.GetAllocator());

    ;}
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
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[(3) - (4)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"SELECT_STMT",(yyvsp[(4) - (4)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[(1) - (4)].node), result->Doc.GetAllocator());

    ;}
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
         merge_nodes(col_list,result->Doc.GetAllocator(), T_COLUMN_LIST, (yyvsp[(5) - (7)].node));
         malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INSERT);  
         (yyval.node)->AddMember("OPERATION_NAME","INSERT_SELECT_STMT", result->Doc.GetAllocator() );
         SafeAddMember((yyval.node),"TABLE_NAME",(yyvsp[(3) - (7)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"COLUMNS_LIST",col_list, result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"SELECT_STMT",(yyvsp[(7) - (7)].node), result->Doc.GetAllocator());
         SafeAddMember((yyval.node),"REPLACE_OR_INSERT",(yyvsp[(1) - (7)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 208:

    { (yyval.node) = NULL; ;}
    break;

  case 209:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 210:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;
      */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
      rapidjson::Value tmp(1);
      SafeAddMember((yyval.node),"value_",&tmp, result->Doc.GetAllocator());

    ;}
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
    ;}
    break;

  case 212:

    {
       /* merge_nodes($$, result->malloc_pool_, T_COLUMN_LIST, $2);*/
       merge_nodes((yyval.node),result->Doc.GetAllocator(),T_BOOL,(yyvsp[(2) - (3)].node));
    ;}
    break;

  case 213:

    { (yyval.node) = NULL; ;}
    break;

  case 214:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 215:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 216:

    {
    /*  merge_nodes($$, result->malloc_pool_, T_VALUE_VECTOR, $2);*/
    merge_nodes((yyval.node),result->Doc.GetAllocator(),T_VALUE_VECTOR,(yyvsp[(2) - (3)].node));
    ;}
    break;

  case 217:

    {
  /*  merge_nodes($4, result->malloc_pool_, T_VALUE_VECTOR, $4);*/
  /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $4);*/
  rapidjson::Value  *insert_vals  ;
  merge_nodes(insert_vals,result->Doc.GetAllocator(),T_VALUE_VECTOR,(yyvsp[(4) - (5)].node));
  //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, insert_vals);
  malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (5)].node), insert_vals);
  ;}
    break;

  case 218:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 219:

    {
   /*   malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
 
    ;}
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
       (yyval.node) = (yyvsp[(1) - (2)].node);
       (yyval.node)->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

       SafeAddMember((yyval.node),"HINTS",(yyvsp[(2) - (2)].node) , result->Doc.GetAllocator());
       if((yyval.node)->HasMember("limit") && (yyvsp[(2) - (2)].node) != NULL)
       	{
       		(*(yyval.node))["limit"].SetObject().AddMember("value_", rapidjson::Value(1), result->Doc.GetAllocator());
       	}
    ;}
    break;

  case 221:

    { 
    	(yyval.node) = (yyvsp[(1) - (1)].node); 
      (yyval.node)->AddMember("OPERATION_NAME","SELECT", result->Doc.GetAllocator() );

    	//malloc_terminal_node($$,result->Doc.GetAllocator(),T_SUB_SELECT);
			//SafeAddMember($$,"SUB_SELECT",$1, result->Doc.GetAllocator());	
    ;}
    break;

  case 222:

    { 
        malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  	SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[(2) - (3)].node) , result->Doc.GetAllocator());
    	  //$$ = $2; 
    	
    	;}
    break;

  case 223:

    { 
  	  malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT_WITH_PARENS);
		  SafeAddMember((yyval.node),"SUB_SELECT",(yyvsp[(2) - (3)].node) , result->Doc.GetAllocator());
  	  //$$ = $2; 
  	
  	;}
    break;

  case 224:

    {
      (yyval.node)= (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 225:

    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
      //$$->children_[12] = $2;
      SafeAddMember((yyval.node),"limit",(yyvsp[(2) - (2)].node) , result->Doc.GetAllocator());

    ;}
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
      	select.CopyFrom(*(yyvsp[(1) - (3)].node),result->Doc.GetAllocator());
      	if (select.HasMember("ORDER_BY_CLAUSE") && (yyvsp[(2) - (3)].node) ) {select.RemoveMember("ORDER_BY_CLAUSE");}select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[(2) - (3)].node),result->Doc.GetAllocator());
      if((yyvsp[(3) - (3)].node))select.AddMember("limit",*(yyvsp[(3) - (3)].node),result->Doc.GetAllocator());
     // 	if($3)select.AddMember("ORDER_BY_CLAUSE",*$3,result->Doc.GetAllocator());
      (yyval.node)->Swap(select);
    ;}
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
      select.CopyFrom(*(yyvsp[(1) - (4)].node),result->Doc.GetAllocator());

      if ((yyvsp[(2) - (4)].node))
      {
      	if (select.HasMember("ORDER_BY_CLAUSE") /*&& $2*/) {select.RemoveMember("ORDER_BY_CLAUSE");select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[(2) - (4)].node),result->Doc.GetAllocator());}
      	else if((yyvsp[(2) - (4)].node)) select.AddMember("ORDER_BY_CLAUSE",*(yyvsp[(2) - (4)].node),result->Doc.GetAllocator());
      }	
     if ( select.HasMember("limit") /*&& $3*/ ){select.RemoveMember("limit");}
     	select.AddMember("limit",*(yyvsp[(3) - (4)].node),result->Doc.GetAllocator());
     if ( select.HasMember("for_update") )	{select.RemoveMember("for_update");} 
     if((yyvsp[(4) - (4)].node))select.AddMember("for_update",*(yyvsp[(4) - (4)].node),result->Doc.GetAllocator());
     (yyval.node)->Swap(select);
    ;}
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
       merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[(4) - (5)].node));
      
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);                   
       SafeAddMember((yyval.node),"DISTINCT",(yyvsp[(3) - (5)].node),result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"LIMIT",(yyvsp[(5) - (5)].node),result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"HINTS",(yyvsp[(2) - (5)].node),result->Doc.GetAllocator());
           ;}
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
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[(4) - (8)].node));
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"DISTINCT",(yyvsp[(3) - (8)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[(7) - (8)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"LIMIT",(yyvsp[(8) - (8)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"HINTS",(yyvsp[(2) - (8)].node),result->Doc.GetAllocator());
    ;}
    break;

  case 230:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 231:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
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
      merge_nodes(project_list,result->Doc.GetAllocator(),T_PROJECT_LIST,(yyvsp[(4) - (9)].node));
      rapidjson::Value  *from_list    ;
      merge_nodes(from_list,result->Doc.GetAllocator(),T_FROM_LIST   ,(yyvsp[(6) - (9)].node));
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SELECT);  
      SafeAddMember((yyval.node),"DISTINCT",(yyvsp[(3) - (9)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"SELECT_CLAUSE",project_list,result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FROM_CLAUSE",from_list,result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"WHERE_CLAUSE",(yyvsp[(7) - (9)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"GROUP_BY_CLAUSE",(yyvsp[(8) - (9)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"HAVING_CLAUSE",(yyvsp[(9) - (9)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"HINTS",(yyvsp[(2) - (9)].node),result->Doc.GetAllocator());
    ;}
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
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[(3) - (4)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[(1) - (4)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[(4) - (4)].node),result->Doc.GetAllocator());
    ;}
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
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[(3) - (4)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[(1) - (4)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[(4) - (4)].node),result->Doc.GetAllocator());
    ;}
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
      SafeAddMember((yyval.node),"ALL_SPECIFIED",(yyvsp[(3) - (4)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"FORMER_SELECT_STMT",(yyvsp[(1) - (4)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"LATER_SELECT_STMT",(yyvsp[(4) - (4)].node),result->Doc.GetAllocator());
    ;}
    break;

  case 236:

    {(yyval.node) = NULL;;}
    break;

  case 237:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 238:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 2, $3, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_WHERE_CLAUSE, (yyvsp[(3) - (3)].node), (yyvsp[(2) - (3)].node));
    ;}
    break;

  case 239:

    {
      if ((*(yyvsp[(2) - (4)].node))["type_"].GetInt()== T_QUESTIONMARK && (*(yyvsp[(4) - (4)].node))["type_"].GetInt()== T_QUESTIONMARK)
      {
       /* $4->value_++;*/
       int i = ((*(yyvsp[(4) - (4)].node))["value_"]).GetInt();++i;
       rapidjson::Value tmp(i);
       (*(yyvsp[(4) - (4)].node))["value_"].Swap(tmp);
       
      }
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, $4);*/
     	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_WHERE_CLAUSE, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));

    ;}
    break;

  case 240:

    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
      malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
      if ((*(yyvsp[(2) - (4)].node))["type_"].GetInt()  == T_QUESTIONMARK && (*(yyvsp[(4) - (4)].node))["type_"].GetInt() == T_QUESTIONMARK )
      	{
      		int i =(*(yyvsp[(4) - (4)].node))["value_"].GetInt();
      		rapidjson::Value tmp(++i);
      		(*(yyvsp[(4) - (4)].node))["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].node));
	
    ;}
    break;

  case 241:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $2, NULL);*/
   		malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[(2) - (2)].node), NULL);
 
    ;}
    break;

  case 242:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, NULL, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, NULL, (yyvsp[(2) - (2)].node));

    ;}
    break;

  case 243:

    {
      /*if ($2->type_ == T_QUESTIONMARK && $4->type_ == T_QUESTIONMARK)
      {
        $4->value_++;
      }
    	malloc_non_terminal_node($$, result->malloc_pool_, T_LIMIT_CLAUSE, 2, $4, $2);*/
       if ((*(yyvsp[(2) - (4)].node))["type_"].GetInt()  == T_QUESTIONMARK && (*(yyvsp[(4) - (4)].node))["type_"].GetInt() == T_QUESTIONMARK )
      	{
      			int i = (*(yyvsp[(4) - (4)].node))["value_"].GetInt();
      			rapidjson::Value tmp(++i);
      		  (*(yyvsp[(4) - (4)].node))["value_"].Swap(tmp);
      	}
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LIMIT_CLAUSE, (yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].node));	
    ;}
    break;

  case 244:

    {
      (yyval.node) = NULL;
    ;}
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
      if ((yyvsp[(2) - (3)].node))
      {
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_HINT_OPTION_LIST, (yyvsp[(2) - (3)].node));	
      }
      else
      {
        (yyval.node) = NULL;
      }
    ;}
    break;

  case 246:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 247:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);	
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
 
    ;}
    break;

  case 248:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 249:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 250:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $2);*/
        //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $2);	
        malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));

    ;}
    break;

  case 251:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_READ_STATIC);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_READ_STATIC);	

    ;}
    break;

  case 252:

    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_HOTSPOT);*/
        malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_HOTSPOT);	

    ;}
    break;

  case 253:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_READ_CONSISTENCY);
      $$->value_ = $3;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_READ_CONSISTENCY);	
      rapidjson::Value tmp;
      	tmp.SetInt((yyvsp[(3) - (4)].ival));
      (*(yyval.node))["value_"].Swap(tmp );

    ;}
    break;

  case 254:

    {
      (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 255:

    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
    ;}
    break;

  case 256:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 257:

    {
    (yyval.ival) = 3;
  ;}
    break;

  case 258:

    {
    (yyval.ival) = 4;
  ;}
    break;

  case 259:

    {
    (yyval.ival) = 1;
  ;}
    break;

  case 260:

    {
    (yyval.ival) = 2;
  ;}
    break;

  case 261:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 262:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 263:

    { (yyval.node) = NULL; ;}
    break;

  case 264:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 265:

    { (yyval.node) = NULL; ;}
    break;

  case 266:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
    rapidjson::Value tmp(1);
    (*(yyval.node))["value_"].Swap(tmp );
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node)); 
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));   
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));     
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[(3) - (3)].node));     

    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[(3) - (3)].node));     
  
    ;}
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
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,default_type, default_operand, (yyvsp[(3) - (3)].node));     
  
    ;}
    break;

  case 274:

    { (yyval.node) = NULL; ;}
    break;

  case 275:

    {
    /*   merge_nodes($$, result->malloc_pool_, T_EXPR_LIST, $3);*/
    merge_nodes((yyval.node),result->Doc.GetAllocator(),T_EXPR_LIST,(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 276:

    { (yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 277:

    { (yyval.node) = NULL; ;}
    break;

  case 278:

    {
   /*   merge_nodes($$, result->malloc_pool_, T_SORT_LIST, $3);*/
        merge_nodes((yyval.node),result->Doc.GetAllocator(),T_SORT_LIST,(yyvsp[(3) - (3)].node));
     //    malloc_terminal_node($$,result->Doc.GetAllocator(),T_SORT_LIST);  
      //   SafeAddMember($$,"ORDER_BY_CLAUSE",$3,result->Doc.GetAllocator());
    cout<<"T_SORT_LIST"<<endl;
      ;}
    break;

  case 279:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 280:

    { /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    	//   malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1,$3);
    	malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    	;}
    break;

  case 281:

    {
    	/*malloc_non_terminal_node($$, result->malloc_pool_, T_SORT_KEY, 2, $1, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SORT_KEY, (yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node));

    ;}
    break;

  case 282:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_ASC);
	
    	;}
    break;

  case 283:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_ASC); */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_ASC);
	
    	;}
    break;

  case 284:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SORT_DESC); */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SORT_DESC);
	
    	;}
    break;

  case 285:

    { (yyval.node) = 0; ;}
    break;

  case 286:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 287:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 288:

    {
    /*  malloc_terminal_node($$, result->malloc_pool_, T_ALL); */
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_ALL);

    ;}
    break;

  case 289:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_DISTINCT);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_DISTINCT);

    ;}
    break;

  case 290:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_PROJECT_STRING, 1, $1);
      dup_expr_string($$->str_value_, result, @1.first_column, @1.last_column);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PROJECT_STRING);
      SafeAddMember((yyval.node),"PROJECT",       (yyvsp[(1) - (1)].node) , result->Doc.GetAllocator());
       // dup_expr_string
      
    ;}
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
       SafeAddMember((yyval.node),"PROJECT",       (yyvsp[(1) - (2)].node) , result->Doc.GetAllocator());
       SafeAddMember((yyval.node),"PROJECT_ALIAS", (yyvsp[(2) - (2)].node), result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    ;}
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
     SafeAddMember((yyval.node),"PROJECT",      (yyvsp[(1) - (3)].node) , result->Doc.GetAllocator());
     SafeAddMember((yyval.node),"PROJECT_ALIAS",(yyvsp[(3) - (3)].node), result->Doc.GetAllocator());

     // dup_expr_string
     // dup_expr_string
    ;}
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
    ;}
    break;

  case 294:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
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
    malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 296:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 297:

    {/* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3); */
    //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_LINK_NODE, $1, $3);
		malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    	;}
    break;

  case 298:

    {
     // $$ = $1;
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
      SafeAddMember((yyval.node),"RELATION",(yyvsp[(1) - (1)].node), result->Doc.GetAllocator());

    ;}
    break;

  case 299:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[(1) - (3)].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"TABLE_ALIAS",(yyvsp[(3) - (3)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 300:

    {
      /* malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    //  malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[(1) - (2)].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"RELATION_ALIAS",(yyvsp[(2) - (2)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 301:

    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $3);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[(1) - (3)].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"SUB_SELECT_ALIAS",(yyvsp[(3) - (3)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 302:

    {
     /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $1, $2);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $1, $2);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[(1) - (2)].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"SUB_SELECT_ALIAS",(yyvsp[(2) - (2)].node), result->Doc.GetAllocator());
    ;}
    break;

  case 303:

    {
    	(yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 304:

    {
    /*	malloc_non_terminal_node($$, result->malloc_pool_, T_ALIAS, 2, $2, $5);*/
    // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(), T_ALIAS, $2, $5);
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_RELATION);
    SafeAddMember((yyval.node),"RELATION",(yyvsp[(2) - (5)].node), result->Doc.GetAllocator());
    SafeAddMember((yyval.node),"RELATION_ALIAS",(yyvsp[(5) - (5)].node), result->Doc.GetAllocator());    	
    	
    	yyerror(&(yylsp[(1) - (5)]), result, "qualied joined table can not be aliased!");
      YYABORT;
    ;}
    break;

  case 305:

    {
    	 (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 306:

    {
    	(yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 307:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_JOINED_TABLE, 4, $2, $1, $4, $6);*/
     rapidjson::Value  *node ;
     malloc_terminal_node(node,result->Doc.GetAllocator(), T_JOIN_CONDITION);
     SafeAddMember(node,"JOIN_CONDITION",(yyvsp[(6) - (6)].node), result->Doc.GetAllocator());
     malloc_non_terminal_node_with_type(&(yyval.node),result->Doc.GetAllocator(), "JOIN_TYPE",(*(yyvsp[(2) - (6)].node))["JOIN_TYPE"].GetString(), T_JOINED_TABLE, (yyvsp[(1) - (6)].node), (yyvsp[(4) - (6)].node), node);

    ;}
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
     	SafeAddMember(node2,"JOIN_CONDITION",(yyvsp[(5) - (5)].node), result->Doc.GetAllocator());
    malloc_non_terminal_node_with_type(&(yyval.node),result->Doc.GetAllocator(), "JOIN_TYPE","INNER_JOIN" ,T_JOINED_TABLE,  node, (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), node2);
    ;}
    break;

  case 309:

    {
      /* make bison mute*/
      (void)((yyvsp[(2) - (2)].node));
      /*malloc_terminal_node($$, result->malloc_pool_, T_JOIN_FULL);*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_FULL);
     (yyval.node)->AddMember("JOIN_TYPE","FULL_JOIN", result->Doc.GetAllocator());    	

    ;}
    break;

  case 310:

    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_LEFT);*/
       (void)((yyvsp[(2) - (2)].node));
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_LEFT);
  	 	 (yyval.node)->AddMember("JOIN_TYPE","LEFT_JOIN", result->Doc.GetAllocator());
    ;}
    break;

  case 311:

    {
      /* make bison mute
      (void)($2);
      malloc_terminal_node($$, result->malloc_pool_, T_JOIN_RIGHT);*/
       (void)((yyvsp[(2) - (2)].node));
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_RIGHT);
       (yyval.node)->AddMember("JOIN_TYPE","RIGHT_JOIN", result->Doc.GetAllocator());
    ;}
    break;

  case 312:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_JOIN_INNER);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_JOIN_INNER);
      (yyval.node)->AddMember("JOIN_TYPE","INNER_JOIN", result->Doc.GetAllocator());

    ;}
    break;

  case 313:

    { (yyval.node) = NULL; ;}
    break;

  case 314:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_EXPLAIN, 1, $3);
      $$->value_ = ($2 ? 1 : 0); positive: verbose */
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_EXPLAIN);
      (yyval.node)->AddMember("OPERATION_NAME","EXPLAIN", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("STMT",*(yyvsp[(3) - (3)].node),result->Doc.GetAllocator());
      //rapidjson::Value tmp($2 ? 1 : 0);
      //(*$$)["value_"].Swap(tmp);
 
    ;}
    break;

  case 315:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 316:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 317:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 318:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 319:

    { (yyval.node) = (rapidjson::Value*)1; ;}
    break;

  case 320:

    { (yyval.node) = NULL; ;}
    break;

  case 321:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLES, 1, $3malloc_*/ 
    	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLES, (yyvsp[(3) - (3)].node));
    	(yyval.node)->AddMember("OPERATION_NAME","COMMAND", result->Doc.GetAllocator() );
    	;}
    break;

  case 322:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
    	  malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS, (yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));
    	;}
    break;

  case 323:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $4, $5)*/ 
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS, (yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));
	
    	;}
    break;

  case 324:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_TABLE_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, (yyvsp[(4) - (4)].node));

    	
    	;}
    break;

  case 325:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_SERVER_STATUS, 1, $4)*/ 
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_TABLE_STATUS, (yyvsp[(4) - (4)].node));
	
    	;}
    break;

  case 326:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_VARIABLES, 1, $4);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_VARIABLES, (yyvsp[(4) - (4)].node));
      //$$->value_ = $2;
       rapidjson::Value tmp((yyvsp[(2) - (4)].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 327:

    { /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_SCHEMA);*/ 
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SHOW_SCHEMA);	
    	;}
    break;

  case 328:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_CREATE_TABLE, 1, $4);*/ 
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_CREATE_TABLE,(yyvsp[(4) - (4)].node));		
    	;}
    break;

  case 329:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/ 
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS,(yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));			
    	;}
    break;

  case 330:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_COLUMNS, 2, $2, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_COLUMNS,(yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));			
	
    	 ;}
    break;

  case 331:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_WARNINGS, 1, $3);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SHOW_WARNINGS,(yyvsp[(3) - (3)].node));			
 
    ;}
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
      if ((*(yyvsp[(2) - (3)].node))["type_"].GetInt()!= T_FUN_COUNT)
      {
        yyerror(&(yylsp[(1) - (3)]), result, "Only COUNT(*) function is supported in SHOW WARNINGS statement!");
        YYABORT;  
      }
       else
      {
      	rapidjson::Value tmp(1);
        (*(yyval.node))["value_"].Swap(tmp);
      }
    ;}
    break;

  case 333:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_GRANTS, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_GRANTS,(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 334:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SHOW_PARAMETERS, 1, $3*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_PARAMETERS,(yyvsp[(3) - (3)].node));
  
    ;}
    break;

  case 335:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_SHOW_PROCESSLIST*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_SHOW_PROCESSLIST);
      /*$$->value_ = $2;*/
       
       rapidjson::Value tmp((yyvsp[(2) - (3)].ival));
      (*(yyval.node))["value_"].Swap(tmp);
      ;}
    break;

  case 336:

    {
      /*if ($2->value_ < 0 || $4->value_ < 0)
      {
        yyerror(&@1, result, "OFFSET/COUNT must not be less than 0!"
        YYABORT;
      }
      malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, $2, $4malloc_*/
      if ((*(yyvsp[(2) - (4)].node))["value_"].GetInt()< 0 || (*(yyvsp[(4) - (4)].node))["value_"].GetInt() < 0)
      {
        yyerror(&(yylsp[(1) - (4)]), result, "OFFSET/COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_LIMIT,  (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    ;}
    break;

  case 337:

    {
       /*if ($2->value_ < 0)
      {
        yyerror(&@1, result, "COUNT must not be less than 0!");
        YYABORT;
      }
     malloc_non_terminal_node($$, result->/*malloc_pool_, T_SHOW_LIMIT, 2, NULL, $2);*/
     if ((*(yyvsp[(2) - (2)].node))["value_"].GetInt()< 0 )
     	{
     		yyerror(&(yylsp[(1) - (2)]), result, "COUNT must not be less than 0!");
        YYABORT;
     	}
    malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_SHOW_LIMIT,  NULL, (yyvsp[(2) - (2)].node));
 
    ;}
    break;

  case 338:

    { (yyval.node) = NULL; ;}
    break;

  case 339:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 340:

    { (yyval.node) = NULL; ;}
    break;

  case 341:

    { (yyval.node) = NULL; ;}
    break;

  case 342:

    { (yyval.ival) = 1; ;}
    break;

  case 343:

    { (yyval.ival) = 0; ;}
    break;

  case 344:

    { (yyval.ival) = 0; ;}
    break;

  case 345:

    { (yyval.node) = NULL; ;}
    break;

  case 346:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $2);*/ 
        malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_LIKE, (yyvsp[(2) - (2)].node));
	
    	;}
    break;

  case 347:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_WHERE_CLAUSE, 1, $2);*/
     malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_WHERE_CLAUSE, (yyvsp[(2) - (2)].node));
	
    ;}
    break;

  case 348:

    { (yyval.node) = NULL; ;}
    break;

  case 349:

    { /*malloc_non_terminal_node($$, result->malloc_pool_, T_OP_LIKE, 1, $1);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_OP_LIKE, (yyvsp[(1) - (1)].node));
	
    ;}
    break;

  case 350:

    { (yyval.ival) = 0; ;}
    break;

  case 351:

    { (yyval.ival) = 1; ;}
    break;

  case 352:

    {
       /* merge_nodes($$, result->malloc_pool_, T_CREATE_USER, $3);*/
      // merge_nodes($$,result->Doc.GetAllocator(),T_CREATE_USER, $3);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CREATE_USER,(yyvsp[(3) - (3)].node));
      (yyval.node)->AddMember("OPERATION_NAME","CREATE_USER", result->Doc.GetAllocator() );
    ;}
    break;

  case 353:

    {
    	malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(), T_CREATE_USER,(yyvsp[(3) - (3)].node));
      (yyval.node)->AddMember("OPERATION_NAME","CREATE_USER", result->Doc.GetAllocator() );
    	
    ;}
    break;

  case 354:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 355:

    {
       /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
       //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
       malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 356:

    {
      /*  malloc_non_terminal_node($$, result->malloc_pool_, T_CREATE_USER_SPEC, 2, $1, $4);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CREATE_USER_SPEC);
      (yyval.node)->AddMember("USER_NAME",*(yyvsp[(1) - (4)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("PASSWORD", *(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );
     
    ;}
    break;

  case 357:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
     // malloc_terminal_node($$,result->Doc.GetAllocator(), T_RELATION);
     // SafeAddMember($$,"USER_NAME",$1, result->Doc.GetAllocator());
    ;}
    break;

  case 358:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 359:

    {
       /* merge_nodes($$, result->malloc_pool_, T_DROP_USER, $3);*/
        merge_nodes((yyval.node),result->Doc.GetAllocator(),T_DROP_USER, (yyvsp[(3) - (3)].node));
				(yyval.node)->AddMember("OPERATION_NAME","DROP_USER", result->Doc.GetAllocator() );

    ;}
    break;

  case 360:

    {
    	printf(" user \n");
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 361:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 362:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $5);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SET_PASSWORD);
    (yyval.node)->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
    (yyval.node)->AddMember("USER_NAME",*(yyvsp[(3) - (5)].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("PASSWORD",*(yyvsp[(5) - (5)].node), result->Doc.GetAllocator() );



    ;}
    break;

  case 363:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_SET_PASSWORD, 2, $3, $6);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_SET_PASSWORD);
      (yyval.node)->AddMember("OPERATION_NAME","SET_PASWD", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("USER_NAME",*(yyvsp[(3) - (6)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("PASSWORD",*(yyvsp[(6) - (6)].node), result->Doc.GetAllocator() );
      
      

    ;}
    break;

  case 364:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 365:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 366:

    {
      /*merge_nodes($$, result->malloc_pool_, T_RENAME_USER, $3);*/
     // merge_nodes($$,result->Doc.GetAllocator(),T_RENAME_USER, $3);
      
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_RENAME_USER,(yyvsp[(3) - (3)].node));
      (yyval.node)->AddMember("OPERATION_NAME","RENAME_USER", result->Doc.GetAllocator() );

    ;}
    break;

  case 367:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_RENAME_INFO, 2, $1, $3);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_RENAME_INFO);
      (yyval.node)->AddMember("OLD_NAME",*(yyvsp[(1) - (3)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("NEW_NAME",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );
  
    ;}
    break;

  case 368:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 369:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1 ,$3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 370:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LOCK_USER, 2, $3, $4);*/
   malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_LOCK_USER,(yyvsp[(3) - (4)].node) ,(yyvsp[(4) - (4)].node));
    ;}
    break;

  case 371:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(1);
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 372:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BOOL);
      rapidjson::Value tmp(0);
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 373:

    {
      (void)(yyval.node);
    ;}
    break;

  case 374:

    {
    ;}
    break;

  case 375:

    {
      (yyval.ival) = 1;
    ;}
    break;

  case 376:

    {
      (yyval.ival) = 0;
    ;}
    break;

  case 377:

    {
      (void)(yyvsp[(2) - (2)].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_BEGIN);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BEGIN);
      rapidjson::Value tmp(0);
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 378:

    {
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_BEGIN);
       
       rapidjson::Value tmp((yyvsp[(3) - (3)].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 379:

    {
      (void)(yyvsp[(2) - (2)].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_COMMIT);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_COMMIT);
			(yyval.node)->AddMember("OPERATION_NAME","COMMIT", result->Doc.GetAllocator() );

    ;}
    break;

  case 380:

    {
      (void)(yyvsp[(2) - (2)].node);
      /*malloc_terminal_node($$, result->malloc_pool_, T_ROLLBACK);*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_ROLLBACK);
			 (yyval.node)->AddMember("OPERATION_NAME","ROLLBACK", result->Doc.GetAllocator() );

    ;}
    break;

  case 381:

    {
    /*  malloc_non_terminal_node($$, result->malloc_pool_, T_KILL, 3, $2, $3, $4);*/
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(), T_KILL );
    (yyval.node)->AddMember("OPERATION_NAME","KILL", result->Doc.GetAllocator() );
    (yyval.node)->AddMember("IS_GLOBAL",*(yyvsp[(2) - (4)].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("OPT_FLAG",*(yyvsp[(3) - (4)].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("INTNUM",*(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );



    ;}
    break;

  case 382:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
    ;}
    break;

  case 383:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
       $$->value_ = 1;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
       (*(yyval.node))["value_"] = rapidjson::Value(-1);
    ;}
    break;

  case 384:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
      
    ;}
    break;

  case 385:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 1;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
       rapidjson::Value tmp(1);
       (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 386:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_BOOL);
      $$->value_ = 0;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_BOOL);
     
    ;}
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
    	(yyval.node)->AddMember("PRIV_LEVEL",*(yyvsp[(4) - (6)].node), result->Doc.GetAllocator() );
    	(yyval.node)->AddMember("PRIV_TYPE", *(yyvsp[(2) - (6)].node), result->Doc.GetAllocator() );
    	(yyval.node)->AddMember("USER_NAME", *(yyvsp[(6) - (6)].node), result->Doc.GetAllocator() );
    ;}
    break;

  case 388:

    {
    	printf(" priv_type_list \n");
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 389:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
      malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 390:

    {
    	
      (void)(yyvsp[(2) - (2)].node);                 /* useless */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALL;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALL);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","ALL", result->Doc.GetAllocator() );
    ;}
    break;

  case 391:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_ALTER;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_ALTER);
      (yyval.node)->AddMember("str_value_","ALTER", result->Doc.GetAllocator() );
    ;}
    break;

  case 392:

    {
    	printf(" CREATE \n");
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE);
      (yyval.node)->AddMember("str_value_","CREATE", result->Doc.GetAllocator() );
    ;}
    break;

  case 393:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_CREATE_USER;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_CREATE_USER);
      (yyval.node)->AddMember("str_value_","CREATE_USER", result->Doc.GetAllocator() );
    ;}
    break;

  case 394:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DELETE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DELETE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","DELETE", result->Doc.GetAllocator() );
    ;}
    break;

  case 395:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_DROP;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp( OB_PRIV_DROP);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","DROP", result->Doc.GetAllocator() );
    ;}
    break;

  case 396:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_GRANT_OPTION;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_GRANT_OPTION);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","GRANT_OPTION", result->Doc.GetAllocator() );
    ;}
    break;

  case 397:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_INSERT;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_INSERT);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","INSERT", result->Doc.GetAllocator() );
    ;}
    break;

  case 398:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_UPDATE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_UPDATE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","UPDATE", result->Doc.GetAllocator() );
    ;}
    break;

  case 399:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_SELECT;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_SELECT);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","SELECT", result->Doc.GetAllocator() );
    ;}
    break;

  case 400:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_TYPE);
      $$->value_ = OB_PRIV_REPLACE;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_TYPE);
      rapidjson::Value tmp(OB_PRIV_REPLACE);
      (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("str_value_","REPLACE", result->Doc.GetAllocator() );
    ;}
    break;

  case 401:

    {
    
      (void)(yyval.node);
    ;}
    break;

  case 402:

    {
    	
      (void)(yyval.node);
    ;}
    break;

  case 403:

    {
      /* means global priv_level */
      /*malloc_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PRIV_LEVEL);
     
    ;}
    break;

  case 404:

    {
      
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PRIV_LEVEL, 1, $1);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_PRIV_LEVEL,(yyvsp[(1) - (1)].node));
    

    ;}
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
    (yyval.node)->AddMember("PRIV_LEVEL",*(yyvsp[(3) - (5)].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("PRIV_TYPE", *(yyvsp[(2) - (5)].node), result->Doc.GetAllocator() );
    (yyval.node)->AddMember("USER_NAME", *(yyvsp[(5) - (5)].node), result->Doc.GetAllocator() );                                 
    ;}
    break;

  case 406:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 407:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 408:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_PREPARE, 2, $2, $4);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_PREPARE);
      
      (yyval.node)->AddMember("OPERATION_NAME","PREPARE", result->Doc.GetAllocator() );
   		(yyval.node)->AddMember("PREPARE_NAME",*(yyvsp[(2) - (4)].node), result->Doc.GetAllocator() );
   		(yyval.node)->AddMember("PREPARE_STMT",*(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );
    ;}
    break;

  case 409:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 410:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 411:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 412:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 413:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 414:

    {
     /* merge_nodes($$, result->malloc_pool_, T_VARIABLE_SET, $2);
      $$->value_ = 2;*/

      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_VARIABLE_SET,(yyvsp[(2) - (2)].node));      
      (yyval.node)->AddMember("OPERATION_NAME","SET", result->Doc.GetAllocator() );
    ;}
    break;

  case 415:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 416:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE, $1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 417:

    {
      (void)((yyvsp[(2) - (3)].node));
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
       malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
       (yyval.node)->AddMember("VARIABLE_NAME",*(yyvsp[(1) - (3)].node), result->Doc.GetAllocator() );
       (yyval.node)->AddMember("VALUE",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );

    ;}
    break;

  case 418:

    {
      (void)((yyvsp[(2) - (3)].node));
       /*$1->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $1, $3);
      $$->value_ = 2;*/
    rapidjson::Value tmp(T_SYSTEM_VARIABLE);
    (yyvsp[(1) - (3)].node)->AddMember("type_", tmp,result->Doc.GetAllocator());
    malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
     (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(1) - (3)].node), result->Doc.GetAllocator() );
     (yyval.node)->AddMember("VALUE",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );

    ;}
    break;

  case 419:

    {
      (void)((yyvsp[(3) - (4)].node));
     /* $2->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node($$, result->malloc_pool_, T_VAR_VAL, 2, $2, $4);
      $$->value_ = 1;*/
      rapidjson::Value tmp(T_SYSTEM_VARIABLE);
   	  (yyvsp[(2) - (4)].node)->AddMember("type_", tmp,result->Doc.GetAllocator());
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_VAR_VAL);
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(2) - (4)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );

    ;}
    break;

  case 420:

    {
      //(void)($3);
     // rapidjson::Value tmp(T_SYSTEM_VARIABLE);
     // $2->AddMember("type_", tmp,result->Doc.GetAllocator());

      malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
      //rapidjson::Value tmp1(2);
      //$$->AddMember("value_",tmp1, result->Doc.GetAllocator() );
      
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(2) - (4)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );

    ;}
    break;

  case 421:

    {
      //(void)($4);

      //rapidjson::Value tmp(T_SYSTEM_VARIABLE);

      // $3->AddMember("type_", tmp,result->Doc.GetAllocator());
      malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
      rapidjson::Value tmp1(1);
      (yyval.node)->AddMember("value_",tmp1, result->Doc.GetAllocator() );
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(3) - (5)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[(5) - (5)].node), result->Doc.GetAllocator() );

    ;}
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
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(3) - (5)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[(5) - (5)].node), result->Doc.GetAllocator() );
      
    ;}
    break;

  case 423:

    {
     // (void)($2);

       malloc_terminal_node( (yyval.node),result->Doc.GetAllocator(),T_VAR_VAL );
       rapidjson::Value tmp(2);
       (yyval.node)->AddMember("value_",tmp, result->Doc.GetAllocator() );
       
      (yyval.node)->AddMember("COLUMN_NAME",*(yyvsp[(1) - (3)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("VALUE",*(yyvsp[(3) - (3)].node), result->Doc.GetAllocator() );
    ;}
    break;

  case 424:

    {
    	 
    	 (yyval.node) = NULL; 
    	 ;}
    break;

  case 425:

    { (yyval.node) = NULL; ;}
    break;

  case 426:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 427:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_EXECUTE, 2, $2, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_EXECUTE,(yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 428:

    {
     /* merge_nodes($$, result->malloc_pool_, T_ARGUMENT_LIST, $2);*/
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_ARGUMENT_LIST,(yyvsp[(2) - (2)].node));

    ;}
    break;

  case 429:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 430:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 431:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     // malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1,$3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
    break;

  case 432:

    {
      (void)((yyvsp[(1) - (3)].node));
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_DEALLOCATE, 1, $3);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_DEALLOCATE,(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 433:

    { (yyval.node) = NULL; ;}
    break;

  case 434:

    { (yyval.node) = NULL; ;}
    break;

  case 435:

    {
      /*ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_TABLE, 2, $3, alter_actions);*/
      
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_ALTER_TABLE );
    
      (yyval.node)->AddMember("OPERATION_NAME","ALTER_TABLE", result->Doc.GetAllocator() );
      (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[(3) - (4)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("ALTER_ACTIONS",*(yyvsp[(4) - (4)].node), result->Doc.GetAllocator() );
      
      
    ;}
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
      (yyval.node)->AddMember("TABLE_NAME",*(yyvsp[(3) - (6)].node), result->Doc.GetAllocator() );
      (yyval.node)->AddMember("NEW_NAME",*(yyvsp[(6) - (6)].node), result->Doc.GetAllocator() );
      
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_TABLE_RENAME, $6);
      //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_ALTER_TABLE, $3, $$);
    ;}
    break;

  case 437:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 438:

    {
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 439:

    {
      (void)((yyvsp[(2) - (3)].node)); /* make bison mute */
      (yyval.node) = (yyvsp[(3) - (3)].node); /* T_COLUMN_DEFINITION */
    ;}
    break;

  case 440:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_DROP, 1, $3);
      $$->value_ = $4;*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_DROP, (yyvsp[(3) - (4)].node));
       rapidjson::Value tmp((yyvsp[(4) - (4)].ival));
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 441:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
     /* malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_ALTER, 2, $3, $4);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_ALTER, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));

    ;}
    break;

  case 442:

    {
      (void)((yyvsp[(2) - (5)].node)); /* make bison mute */
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_COLUMN_RENAME, 2, $3, $5);*/
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_COLUMN_RENAME, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));

    ;}
    break;

  case 443:

    { (yyval.node) = NULL; ;}
    break;

  case 444:

    { (yyval.node) = NULL; ;}
    break;

  case 445:

    { (yyval.ival) = 2; ;}
    break;

  case 446:

    { (yyval.ival) = 1; ;}
    break;

  case 447:

    { (yyval.ival) = 0; ;}
    break;

  case 448:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NOT_NULL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CONSTR_NOT_NULL);
    ;}
    break;

  case 449:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      /*malloc_terminal_node($$, result->malloc_pool_, T_CONSTR_NULL);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_CONSTR_NULL);
    ;}
    break;

  case 450:

    {
       /*malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CONSTR_DEFAULT,(yyvsp[(3) - (3)].node));
       
    ;}
    break;

  case 451:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_NULL);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CONSTR_DEFAULT, 1, $$);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_NULL);
      malloc_non_terminal_node (&(yyval.node),result->Doc.GetAllocator(),T_CONSTR_DEFAULT, node);
    ;}
    break;

  case 452:

    {
      /*merge_nodes($$, result->malloc_pool_, T_SYTEM_ACTION_LIST, $4);
      malloc_non_terminal_node($$, result->malloc_pool_, T_ALTER_SYSTEM, 1, $$);*/
      merge_nodes((yyval.node),result->Doc.GetAllocator(),T_SYTEM_ACTION_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_ALTER_SYSTEM,(yyval.node));
    ;}
    break;

  case 453:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[(7) - (7)].node), (yyvsp[(3) - (7)].node));
    ;}
    break;

  case 454:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 3, node, $7, $3);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[(7) - (7)].node), (yyvsp[(3) - (7)].node));
      
    ;}
    break;

  case 455:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_MASTER);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_MASTER);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[(6) - (6)].node));
 
    ;}
    break;

  case 456:

    {
      /*ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_SET_SLAVE);
      malloc_non_terminal_node($$, result->malloc_pool_, T_CHANGE_OBI, 2, node, $6);*/
      rapidjson::Value *node ;
      malloc_terminal_node(node,result->Doc.GetAllocator(),T_SET_SLAVE);
      malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CHANGE_OBI, node, (yyvsp[(6) - (6)].node));

    ;}
    break;

  case 457:

    {
      (yyval.node) = NULL;
    ;}
    break;

  case 458:

    {
     /* malloc_terminal_node($$, result->malloc_pool_, T_FORCE);*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_FORCE);
    ;}
    break;

  case 459:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 460:

    {
     /*  malloc_non_terminal_node($$, result->malloc_pool_, T_LINK_NODE, 2, $1, $3);*/
     //malloc_non_terminal_node(&$$,result->Doc.GetAllocator(),T_LINK_NODE,$1, $3);
     malloc_list_node(&(yyval.node),result->Doc.GetAllocator(),2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));

    ;}
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
      SafeAddMember((yyval.node),"param_name",(yyvsp[(1) - (9)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"param_value",(yyvsp[(3) - (9)].node),result->Doc.GetAllocator());
      SafeAddMember((yyval.node),"comment",(yyvsp[(4) - (9)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"server_type",(yyvsp[(8) - (9)].node),result->Doc.GetAllocator());
			SafeAddMember((yyval.node),"cluster",(yyvsp[(9) - (9)].node),result->Doc.GetAllocator());
			 rapidjson::Value tmp((yyvsp[(5) - (9)].ival));
			(*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 462:

    { (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 463:

    { (yyval.node) = NULL; ;}
    break;

  case 464:

    { (yyval.ival) = 0; ;}
    break;

  case 465:

    { (yyval.ival) = 1; ;}
    break;

  case 466:

    { (yyval.ival) = 2; ;}
    break;

  case 467:

    { (yyval.ival) = 2; ;}
    break;

  case 468:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 1;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(1);
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 469:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 4;*/
     malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
     rapidjson::Value tmp(4);
     (*(yyval.node))["value_"].Swap( tmp); 
    ;}
    break;

  case 470:

    {
     /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 2;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(2);
      (*(yyval.node))["value_"].Swap(tmp); 
    ;}
    break;

  case 471:

    {
      /*malloc_terminal_node($$, result->malloc_pool_, T_INT);
      $$->value_ = 3;*/
      malloc_terminal_node((yyval.node),result->Doc.GetAllocator(),T_INT);
      rapidjson::Value tmp(3);
      (*(yyval.node))["value_"].Swap(tmp); 
    ;}
    break;

  case 472:

    {
     /* malloc_non_terminal_node($$ , result->malloc_pool_, T_CLUSTER, 1, $3);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_CLUSTER,(yyvsp[(3) - (3)].node));
    ;}
    break;

  case 473:

    {
      /*malloc_non_terminal_node($$, result->malloc_pool_, T_SERVER_ADDRESS, 2, $3, $6);*/
       malloc_non_terminal_node(&(yyval.node),result->Doc.GetAllocator(),T_SERVER_ADDRESS,(yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
    ;}
    break;

  case 474:

    { (yyval.node) = NULL; ;}
    break;

  case 475:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
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
      if((yyvsp[(1) - (1)].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);
    ;}
    break;

  case 477:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
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
      if((yyvsp[(1) - (1)].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
			rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);

    ;}
    break;

  case 479:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 480:

    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
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
      if((yyvsp[(1) - (1)].non_reserved_keyword))(yyval.node)->AddMember("str_value_",rapidjson::StringRef((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name),result->Doc.GetAllocator());
      rapidjson::Value tmp(strlen((*(yyval.node))["str_value_"].GetString()));
      (*(yyval.node))["value_"].Swap(tmp);

    ;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, result, scanner, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, result, scanner, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, result, scanner, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, result, scanner);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
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



