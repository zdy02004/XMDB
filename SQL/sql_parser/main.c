%option noyywrap nounput noinput nodefault yylineno case-insensitive
%option noyyalloc noyyrealloc noyyfree
%option reentrant bison-bridge bison-locations
%option header-file="sql_parser.lex.h"
%{
#include "parser.hh"
#include <stdarg.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include "stdarg.h"
#include "parser.tab.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
//#include "ob_non_reserved_keywords.h"


extern void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s,...);
extern void yyerror(YYLTYPE* yylloc, ParseResult* p,const char* s,...);

//#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = result->yylineno_;\
//  yylloc->first_column = result->yycolumn_;\
//  yylloc->last_column = yylloc->first_column + yyleng - 1;\
//  result->yycolumn_ += yyleng;



rapidjson::Value * malloc_new_node(rapidjson::Document::AllocatorType& Allocator, int node_tag)
{
	rapidjson::Value *val_father = new rapidjson::Value;
 
  val_father->SetObject().AddMember("tag", node_tag, Allocator);
  
	return val_father;
}


int check_value(std::string & str)
{
	if (str == std::string("") || str.size()==0)
		return -1;
		else return 0;
} 

inline unsigned char escaped_char(unsigned char c)
{
  switch (c)
  {
    case 'b':
      return '\b';
    case 'f':
      return '\f';
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case 't':
      return '\t';
    default:
      return c;
  }
}

/* quote_type: 0 - single quotes; 1 - double quotation marks */
int64_t parse_string(const char* src, char* dest, int64_t len, int quote_type)
{
  int64_t i;
  int64_t index = 0;
  for(i = 0; i < len; ++i)
  {
    unsigned char c = src[i];
    if(c == '\\')
    {
      if (i < len - 1)
      {
        c = src[++i];
      }
      else
      {
        break;
      }
      c = escaped_char(c);
    }
    else if (quote_type == 0 && c == '\'' && i + 1 < len && src[i + 1] == '\'')
    {
      ++i;
    }
    else if (quote_type == 1 && c == '"' && i + 1 < len && src[i + 1] == '"')
    {
      ++i;
    }
    dest[index++] = c;
  }
  assert(index <= len);
  dest[index] = '\0';
  return index;
}

int64_t parse_binary(const char* src, char* dest, int64_t len)
{
  int64_t i;
  int64_t index = 0;
  for(i = 0; i < len; i += 2)
  {
    char buf[3];
    buf[0] = src[i];
    buf[1] = src[i+1];
    buf[2] = 0;
    unsigned char a = strtol(buf,0, 16);
    dest[index++] = (char)a;
  }
  return index;
}

char* str_tolower(char *buff)
{
	if (buff)
  {
    char  *ptr = buff;
    unsigned char ch = *ptr;
    while (*ptr)
    {
      ch = *ptr;
      if (ch >= 'A' && ch <= 'Z')
        ch += 'a' - 'A';
      else if (ch >= 0x80 && isupper(ch))
        ch = tolower(ch);
      *ptr = ch;
      ptr++;
    }
  }
	return buff;
}

#define dup_str(text)									\
  char _buf[256];                       \
  int _len = sprintf(_buf, "%s", (text));\
  rapidjson::Value str;                 \
  str.SetString(_buf, _len, ((ParseResult*)yyextra)->Doc.GetAllocator());



%}

%x hint
%x sq

space         [ \t\n\r\f]
non_newline   [^\n\r]
sql_comment   ("--"{non_newline}*)
whitespace    ({space}+|{sql_comment})
hint_begin    (\/\*\+({space}*hint{space}+)?)
c_cmt_begin   \/\*(?:[^\+])
c_cmt_end     \*+\/
c_cmt_cnt     [^*/]+
c_comment     ({c_cmt_begin}{c_cmt_cnt}{c_cmt_end})
comment       ({c_comment}|{sql_comment})
identifer         ([A-Za-z_][A_Za-z0-9_]*)
system_variable  (@@[A-Za-z_][A_Za-z0-9_]*)
temp_variable (@[A-Za-z_][A_Za-z0-9_]*)

quote         '
sqbegin       {quote}
sqend         {quote}
sqdouble      {quote}{quote}
sqcontent     [^\\']+
sqescape      [\\][^0-7]
sqoctal       [\\][0-7]{1,3}
sqnewline     {quote}{whitespace}{quote}


%%
ADD               { return ADD; }
ALTER             { return ALTER; }
AND               { return AND; }
ANY               { return ANY; }
ALL               { return ALL; }
AS                { return AS; }
ASC               { return ASC; }
BEGIN             { return BEGI; }
BETWEEN           { return BETWEEN; }
BIGINT            { return BIGINT; }
BINARY            { return BINARY; }
BOOL(EAN)?        { return BOOLEAN; }
BOTH              { return BOTH; }
BY                { return BY; }
CASCADE           { return CASCADE; }
CASE              { return CASE; }
CHAR(ACTER)?      { return CHARACTER; }
CLUSTER           { return CLUSTER; }
COLUMN            { return COLUMN; }
COLUMNS           { return COLUMNS; }
COMMIT            { return COMMIT; }
CONSISTENT        { return CONSISTENT; }
CREATE            { return CREATE; }
CREATETIME        { return CREATETIME; }
CURRENT_USER      { return CURRENT_USER; }
DATE              { return DATE; }
DATETIME          { return DATETIME; }
DEALLOCATE        { return DEALLOCATE; }
DEC(IMAL)?        { return DECIMAL; }
DEFAULT           { return DEFAULT; }
DELETE            { return DELETE; }
DESC              { return DESC; }
DESCRIBE          { return DESCRIBE; }
DISTINCT          { return DISTINCT; }
DOUBLE            { return DOUBLE; }
DROP              { return DROP; }
DUAL              { return DUAL; }
ELSE              { return ELSE; }
END               { return END; }
ERROR             { return ERROR; }
EXCEPT            { return EXCEPT; }
EXECUTE           { return EXECUTE; }
EXISTS            { return EXISTS; }
EXPLAIN           { return EXPLAIN; }
FLOAT             { return FLOAT; }
FLOAT4            { return FLOAT; }
FLOAT8            { return DOUBLE; }
FOR               { return FOR; }
FROM              { return FROM; }
FULL              { return FULL; }
GRANT             { return GRANT; }
GROUP             { return GROUP; }
GLOBAL            { return GLOBAL; }
HAVING            { return HAVING; }
IDENTIFIED        { return IDENTIFIED; }
IF                { return IF; }
IN                { return IN; }
INNER             { return INNER; }
INT               { return INTEGER; }
INTEGER           { return INTEGER; }
INTERSECT         { return INTERSECT; }
INSERT            { return INSERT; }
INTO              { return INTO; }
IS                { return IS; }
JOIN              { return JOIN; }
KEY               { return KEY; }
LEADING           { return LEADING; }
LEFT              { return LEFT; }
LIMIT             { return LIMIT; }
LIKE              { return LIKE; }
LOCAL             { return LOCAL; }
LOCKED            { return LOCKED; }
MEDIUMINT         { return MEDIUMINT; }
MEMORY            { return MEMORY; }
MOD               { return MOD; }
MODIFYTIME        { return MODIFYTIME; }
NOT               { return NOT; }
NUMERIC           { return NUMERIC; }
OFFSET            { return OFFSET; }
ON                { return ON; }
OPTION            { return OPTION; }
OR                { return OR; }
ORDER             { return ORDER; }
OUTER             { return OUTER; }
COMMENT           { return COMMENT; }
PARAMETERS        { return PARAMETERS; }
PASSWORD          { return PASSWORD; }
PRECISION         { return PRECISION; }
PREPARE           { return PREPARE; }
PRIMARY           { return PRIMARY; }
REAL              { return REAL; }
RENAME            { return RENAME; }
REPLACE           { return REPLACE; }
RESTRICT          { return RESTRICT; }
REVOKE            { return REVOKE; }
RIGHT             { return RIGHT; }
ROLLBACK          { return ROLLBACK; }
PRIVILEGES        { return PRIVILEGES; }
SELECT            { return SELECT; }
SCHEMA            { return SCHEMA; }
PROCESSLIST       { return PROCESSLIST; }
SCOPE             { return SCOPE; }
SESSION           { return SESSION; }
SET               { return SET; }
SHOW              { return SHOW; }
SMALLINT          { return SMALLINT; }
SNAPSHOT          { return SNAPSHOT; }
SPFILE            { return SPFILE; }
START             { return START; }
STATIC            { return STATIC; }
WEAK              { return WEAK;   }
STRONG            { return STRONG; }
SYSTEM            { return SYSTEM; }
TABLE             { return TABLE; }
TABLES            { return TABLES; }
THEN              { return THEN; }
TIME              { return TIME; }
TIMESTAMP         { return TIMESTAMP; }
TINYINT           { return TINYINT; }
TO                { return TO; }
TRAILING          { return TRAILING; }
TRANSACTION       { return TRANSACTION; }
UNION             { return UNION; }
UPDATE            { return UPDATE; }
USER              { return USER; }
USING             { return USING; }
VALUES            { return VALUES; }
VARBINARY         { return VARBINARY; }
VARCHAR(ACTER)?   { return VARCHAR; }
WHERE             { return WHERE; }
WHEN              { return WHEN; }
WITH              { return WITH; }
WORK              { return WORK; }
KILL              { return KILL; }
QUERY             { return QUERY; }
CONNECTION        { return CONNECTION; }
FROZEN            { return FROZEN;}
@@global          { return GLOBAL_ALIAS; }
@@session         { return SESSION_ALIAS; }
CHANGE_OBI        { return CHANGE_OBI; }
SWITCH_CLUSTER    { return SWITCH_CLUSTER; }
SET_MASTER_CLUSTER  { return SET_MASTER_CLUSTER; }
SET_SLAVE_CLUSTER   { return SET_SLAVE_CLUSTER;  }
UNIQUE              { return UNIQUE;  }
FULLTEXT            { return FULLTEXT;  }
SPATIAL             { return SPATIAL;  }
HASH                { return HASH;  }
BTREE               { return BTREE;  }
SKIPLIST            { return SKIPLIST;  }
INDEX               { return INDEX;  }
EXTERN_SIZE         { return EXTERN_SIZE;  }

MASTER            { return MASTER; }
SLAVE             { return SLAVE;  }
FORCE             { return FORCE;  }

NULL   {
  /*malloc_new_node(yylval->node, result->malloc_pool_, T_NULL, 0);*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(),T_NULL);
  return NULLX;
}

[0-9]+ {
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_INT);

  dup_str(yytext);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", strlen(yytext),((ParseResult*)yyextra)->Doc.GetAllocator());
  

  //check_value(yylval->node["str_value_"]);
  return INTNUM;
}

[0-9]+E[-+]?[0-9]+ |
[0-9]+"."[0-9]*E[-+]?[0-9]+ |
"."[0-9]+E[-+]?[0-9]+ {
  /*ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DOUBLE, 0);
  yylval->node = node;
  node->str_value_ = parse_strdup(yytext, result->malloc_pool_);
  check_value(node->str_value_);*/
  
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_DOUBLE);
    
    dup_str(yytext);
  	yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  	yylval->node->AddMember("value_", strlen(yytext),((ParseResult*)yyextra)->Doc.GetAllocator());
  //check_value(yylval->node["str_value_"]);
  return APPROXNUM;
}

[0-9]+"."[0-9]* |
"."[0-9]+ {
  /*ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DOUBLE, 0);
  yylval->node = node;
  node->str_value_ = parse_strdup(yytext, result->malloc_pool_);
  check_value(node->str_value_);*/
  
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_DOUBLE);
  
  dup_str(yytext);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", strlen(yytext),((ParseResult*)yyextra)->Doc.GetAllocator());
  return APPROXNUM;
}

TRUE {
  /*malloc_new_node(yylval->node, result->malloc_pool_, T_BOOL, 0);
  yylval->node->value_ = 1;*/
  
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_BOOL);
  yylval->node->AddMember("value_", 1,((ParseResult*)yyextra)->Doc.GetAllocator());
  return BOOL;
}
UNKNOWN {
  /* Unknown is can only appears in grammer 'expr is unknown'
     * and it is equal to NULL semanticly
     * so we set its value to to NULL directly
     */
  /*yylval->node = new_node(((ParseResult*)yyextra)->Allocator, T_NULL, 0); 
  malloc_new_node(, result->malloc_pool_, T_NULL, 0);*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_NULL);
  yylval->node->AddMember("value_", 0,((ParseResult*)yyextra)->Doc.GetAllocator());
  return UNKNOWN;
}
FALSE {
  /*malloc_new_node(yylval->node, result->malloc_pool_, T_BOOL, 0);
  yylval->node->value_ = 0;*/
  
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_BOOL); 
  yylval->node->AddMember("value_", 0,((ParseResult*)yyextra)->Doc.GetAllocator());

  return BOOL;
}

{sqbegin} {
  BEGIN(sq);
  ((ParseResult*)yyextra)->start_col_ = yylloc->first_column;
  char ** tmp_literal = & (((ParseResult*)yyextra)->tmp_literal_);
if (*tmp_literal == NULL)
  {
  /*  *tmp_literal = (char*) parse_malloc(
                               result->input_sql_len_ + 1, 
                               result->malloc_pool_
                               ); */
   *tmp_literal = (char*)((ParseResult*)yyextra)->Doc.GetAllocator().Malloc(((ParseResult*)yyextra)->input_sql_len_ + 1);                            
   // check_value(*tmp_literal);
  }
   /* malloc_new_node(yylval->node, result->malloc_pool_, T_STRING, 0);*/
  //yylval->node->value_ = 0;
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_STRING); 
  yylval->node->AddMember("value_", 0,((ParseResult*)yyextra)->Doc.GetAllocator());
}

<sq>{sqend} {
  BEGIN(INITIAL);
  yylloc->first_column = ((ParseResult*)yyextra)->start_col_;
  char * tmp_literal = ((ParseResult*)yyextra)->tmp_literal_;
  tmp_literal[ ((ParseResult*)yyextra)->input_sql_len_ + 1  ] = '\0';
/*  yylval->node->str_value_ = parse_strndup(tmp_literal, yylval->node->value_ + 1,
                                          result->malloc_pool_);*/
  
  char _buf[ ((ParseResult*)yyextra)->input_sql_len_ + 1 ];                       
  int _len = sprintf(_buf, "%s", (tmp_literal));
 // memmove(_buf, tmp_literal, ((ParseResult*)yyextra)->input_sql_len_ + 1);
  rapidjson::Value str;                 
  str.SetString(_buf, _len , ((ParseResult*)yyextra)->Doc.GetAllocator());
  
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  
 // ((ParseResult*)yyextra)->Doc.GetAllocator().Free(result->tmp_literal_);
  ((ParseResult*)yyextra)->tmp_literal_ = NULL;
  
  return STRING;  
}

<sq>{sqdouble} {
	int tmp = (*(yylval->node))["value_"].GetInt();
((ParseResult*)yyextra)->tmp_literal_[tmp++] = '\'';
 (*(yylval->node))["value_"].SetInt(tmp);
  
}

<sq>{sqcontent} {
	int tmp = (*(yylval->node))["value_"].GetInt();
  memmove(((ParseResult*)yyextra)->tmp_literal_ + tmp, yytext, yyleng);
  
  tmp+= yyleng;
  (*(yylval->node))["value_"].SetInt(tmp);
}

<sq>{sqescape} {
	 int tmp = (*(yylval->node))["value_"].GetInt();
   ((ParseResult*)yyextra)->tmp_literal_[tmp++] = escaped_char(yytext[1]);
   (*(yylval->node))["value_"].SetInt(tmp);
}

<sq>{sqoctal} {
	int tmp = (*(yylval->node))["value_"].GetInt();
  unsigned char c = strtoul(yytext+1, NULL, 8);
  ((ParseResult*)yyextra)->tmp_literal_[tmp++] = c;
  (*(yylval->node))["value_"].SetInt(tmp);
}

<sq>{sqnewline} { /* ignore */ }

<sq>. {
  /* Uncatched '\' before end '\'' */
  int tmp = (*(yylval->node))["value_"].GetInt();
    ((ParseResult*)yyextra)->tmp_literal_[tmp++] = yytext[0];
  (*(yylval->node))["value_"].SetInt(tmp);
}

<sq><<EOF>>  {
  //yyerror(yylloc, yyextra, "unterminated quoted string");
  return ERROR;

}

\"(\\.|\"\"|[^"\\\n])*\" {
  /* ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_IDENT, 0);
  yylval->node = node;
  char* src = yytext+1;
  int len = strlen(src) - 1; //remove last quote charactor
  char* dest = (char*) parse_malloc(len + 1, result->malloc_pool_);
  check_value(dest);
  node->str_value_ = dest;
  node->value_ = parse_string(src, dest, len, 1);*/
 
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_IDENT); 
  
  dup_str(yytext+1);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", strlen(yytext+1),((ParseResult*)yyextra)->Doc.GetAllocator());
  return NAME;
}

\"(\\.|[^"\n])*$ {
 // yyerror(yylloc, yyextra, "Unterminated string %s",(yytext));
  return ERROR;
}

X'([0-9A-F]{2})+'|0X([0-9A-F]{2})+ {
  /*  二进制
  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_BINARY, 0);
  char* src = yytext + 2;
  char* dest = 0;

  size_t len = strlen(src);
  if(src[len - 1] == '\'')
  {
    --len;
  }
  assert((len % 2) == 0);

  //dest = (char*) malloc(len/2);
  dest = (char*) parse_malloc(len / 2, result->malloc_pool_);
  check_value(dest);
  node->str_value_ = dest;
  node->value_ = parse_binary(src, dest, len);

  */
  char* src = yytext + 2;
  //char* dest = 0;

  size_t len = strlen(src);
  if(src[len - 1] == '\'')
  {
    --len;
  }
 // dest = (char*) malloc(len / 2);
  char dest[len / 2];
  
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_BINARY); 
  dup_str(dest);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", parse_binary(src, dest, len),((ParseResult*)yyextra)->Doc.GetAllocator());
  return STRING;
}

Date{whitespace}?'[0-9]{4}(-[0-9]{2}){2}' {
  /*  Date 先不支持
  int year, month, day;
  struct  tm time;
  int ret = 0;


  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DATE, 0);
  char* dest = strchr(yytext, '\'');
  dest =  parse_strdup(dest + 1, result->malloc_pool_); // skip left quote
  check_value(dest);
  size_t len = strlen(dest);
  dest[len - 1] = '\0'; //remove final '

  node->str_value_ = dest;

  ret = sscanf(dest, "%4d-%2d-%2d", &year, &month, &day);
  assert(ret == 3);

  memset(&time, 0, sizeof(struct tm));
  time.tm_year = year - 1900;
  time.tm_mon = month - 1;
  time.tm_mday = day;
  time.tm_hour = 0;
  time.tm_min = 0;
  time.tm_sec = 0;
  time.tm_isdst = -1;

  node->value_ = mktime(&time) * 1000000L;//change to micro seconds
  yylval->node = node;*/
  return DATE_VALUE;
}

Time{whitespace}?'[0-9]{2}(:[0-9]{2}){2}[.][0-9]{1,6}' {
  /*  Time 先不支持
  int hour, minute, second, micro_sec;
  struct  tm time;
  int ret = 0;

  /* ParseNode* node = new_node(result->malloc_pool_, T_DATE, 0);
  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DATE, 0);
  char* dest = strchr(yytext, '\'');
  dest =  parse_strdup(dest + 1, result->malloc_pool_);  // skip left quote
  check_value(dest);
  size_t len = strlen(dest);
  dest[len - 1] = '\0';//remove final '
  node->str_value_ = dest;

  ret = sscanf(dest, "%2d:%2d:%2d.%d",
    &hour, &minute, &second, &micro_sec);
  assert(ret == 4);

  memset(&time, 0, sizeof(struct tm));
  time.tm_year = 0;
  time.tm_mon = 0;
  time.tm_mday = 0;
  time.tm_hour = hour;
  time.tm_min = minute;
  time.tm_sec = second;
  time.tm_isdst = -1;

  node->value_ = mktime(&time) * 1000000L + micro_sec;// unit is microseconds
  yylval->node = node;*/
    
  int hour, minute, second, micro_sec;
  struct  tm time;
  int ret = 0;

  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_DATE);
  
  char* dest = strchr(yytext, '\'');
  char new_dest[strlen(dest) + 1];
  
  size_t len = strlen(dest);
  new_dest[len - 1] = '\0';//remove final '
  memmove(new_dest, dest, len);
  
  dup_str(new_dest);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());

  ret = sscanf(new_dest, "%2d:%2d:%2d.%d", &hour, &minute, &second, &micro_sec);
  assert(ret == 4);
  memset(&time, 0, sizeof(struct tm));
  time.tm_year = 0;
  time.tm_mon = 0;
  time.tm_mday = 0;
  time.tm_hour = hour;
  time.tm_min = minute;
  time.tm_sec = second;
  time.tm_isdst = -1;
  yylval->node->AddMember("value_", mktime(&time) * 1000000L + micro_sec,((ParseResult*)yyextra)->Doc.GetAllocator());
  return DATE_VALUE;
}

Time{whitespace}?'[0-9]{2}(:[0-9]{2}){2}[.]?' {
 
  /* int hour, minute, second;
  struct  tm time;
  int ret = 0;

  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DATE, 0);
  char* dest = strchr(yytext, '\'');
  dest =  parse_strdup(dest + 1, result->malloc_pool_);  // skip left quote
  check_value(dest);
  size_t len = strlen(dest);
  dest[len - 1] = '\0';//remove final '
  node->str_value_ = dest;

  ret = sscanf(dest, "%2d:%2d:%2d",
    &hour, &minute, &second);
  assert(ret == 3);

  memset(&time, 0, sizeof(struct tm));
  time.tm_year = 0;
  time.tm_mon = 0;
  time.tm_mday = 0;
  time.tm_hour = hour;
  time.tm_min = minute;
  time.tm_sec = second;
  time.tm_isdst = -1;

  node->value_ = mktime(&time) * 1000000L;// unit is microseconds
  yylval->node = node;*/
  return DATE_VALUE;
}


Timestamp{whitespace}?'[0-9]{4}(-[0-9]{2}){2}[ ][0-9]{2}(:[0-9]{2}){2}[.][0-9]{1,6}' {
 /*  int year, month, day, hour, minute, second, micro_sec;
  struct  tm time;
  int ret = 0;

  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DATE, 0);
  char* dest = strchr(yytext, '\'');
  dest =  parse_strdup(dest + 1, result->malloc_pool_);;  // skip left quote
  check_value(dest);
  size_t len = strlen(dest);
  dest[len - 1] = '\0';//remove final '
  node->str_value_ = dest;

  ret = sscanf(dest, "%4d-%2d-%2d %2d:%2d:%2d.%d",
    &year, &month, &day,
    &hour, &minute, &second, &micro_sec);
  assert(ret == 7);

  memset(&time, 0, sizeof(struct tm));
  time.tm_year = year - 1900;
  time.tm_mon = month - 1;
  time.tm_mday = day;
  time.tm_hour = hour;
  time.tm_min = minute;
  time.tm_sec = second;
  time.tm_isdst = -1;

  node->value_ = mktime(&time) * 1000000L +  micro_sec;// unit is microseconds
  yylval->node = node;*/
  return DATE_VALUE;
}

Timestamp{whitespace}?'[0-9]{4}(-[0-9]{2}){2}[ ][0-9]{2}(:[0-9]{2}){2}[.]?' {
   /* int year, month, day, hour, minute, second;
  struct  tm time;
  int ret = 0;

  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_DATE, 0);
  char* dest = strchr(yytext, '\'');
  dest =  parse_strdup(dest + 1, result->malloc_pool_);;  // skip left quote
  check_value(dest);
  size_t len = strlen(dest);
  --len;
  dest[len] = '\0';//remove final '
  node->str_value_ = dest;

  ret = sscanf(dest, "%4d-%2d-%2d %2d:%2d:%2d",
    &year, &month, &day,
    &hour, &minute, &second);
  assert(ret == 6);

  memset(&time, 0, sizeof(struct tm));
  time.tm_year = year - 1900;
  time.tm_mon = month - 1;
  time.tm_mday = day;
  time.tm_hour = hour;
  time.tm_min = minute;
  time.tm_sec = second;
  time.tm_isdst = -1;

  node->value_ = mktime(&time) * 1000000L;// unit is microseconds
  yylval->node = node;*/
  return DATE_VALUE;
}

\/\*HINT\+[^*]+\*\/    {
/*  size_t len = 0;
  char* dest;
  ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_HINT, 0);
  dest = parse_strdup(yytext + 3, result->malloc_pool_);
  check_value(dest);
  len = strlen(dest);
  dest[len - 2] = '\0';

  node->str_value_ = dest;
  node->value_ = len - 1;

  yylval->node = node;*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_HINT); 
    
    dup_str(yytext+ 3);
    yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  	yylval->node->AddMember("value_", strlen(yytext+3),((ParseResult*)yyextra)->Doc.GetAllocator());
  return HINT_VALUE;
}

{hint_begin} {
  BEGIN hint;
  return HINT_BEGIN;
}
<hint>{c_cmt_end} {
  BEGIN INITIAL;
  return HINT_END;
}
<hint>[ \t\r\n] {}
<hint>READ_STATIC  {
  return READ_STATIC;
}
<hint>READ_CONSISTENCY  {
  return READ_CONSISTENCY;
}
<hint>WEAK  {
  return WEAK;
}
<hint>STRONG  {
  return STRONG;
}
<hint>STATIC  {
  return STATIC;
}
<hint>FROZEN  {
  return FROZEN;
}
<hint>[(),]  {
  return yytext[0];
}
<hint>HOTSPOT  {
  return HOTSPOT;
}
<hint>{identifer} {}
<hint>. {}

{comment} { /* ignore */ }

[-+&~|^/%*(),.;!] { return yytext[0];}

"||" {return CNNOP;}
"=" {return COMP_EQ;}
">=" {return COMP_GE;}
">" {return COMP_GT;}
"<=" {return COMP_LE;}
"<" {return COMP_LT;}
"!="|"<>" {return COMP_NE;}

"?" {
  /*malloc_new_node(yylval->node, result->malloc_pool_, T_QUESTIONMARK, 0);
  yylval->node->value_ = 0;*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_QUESTIONMARK);
  return QUESTIONMARK;
}

{system_variable} {
   /*ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_SYSTEM_VARIABLE, 0);
  yylval->node = node;
  // skip '@@'
  node->str_value_ = parse_strdup(yytext + 2, result->malloc_pool_);
  check_value(node->str_value_);
  node->value_ = strlen(node->str_value_);*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_SYSTEM_VARIABLE);
   dup_str(yytext+ 2);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", strlen(yytext+2),((ParseResult*)yyextra)->Doc.GetAllocator());
  return SYSTEM_VARIABLE;
}

{temp_variable} {
  /*ParseNode* node = NULL;
  malloc_new_node(node, result->malloc_pool_, T_TEMP_VARIABLE, 0);
  yylval->node = node;
  node->str_value_ = parse_strdup(yytext + 1, result->malloc_pool_);
  check_value(node->str_value_);
  node->value_ = strlen(node->str_value_);*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_TEMP_VARIABLE);
  dup_str(yytext+ 1);
  yylval->node->AddMember("str_value_", str,((ParseResult*)yyextra)->Doc.GetAllocator());
  yylval->node->AddMember("value_", strlen(yytext+1),((ParseResult*)yyextra)->Doc.GetAllocator());
  return TEMP_VARIABLE;
}

{identifer} {
  int ret = NAME;
  const NonReservedKeyword *word = NULL;
  if ((word = non_reserved_keyword_lookup(yytext)) == NULL)
  {
   /* ParseNode* node = NULL;
    malloc_new_node(node, result->malloc_pool_, T_IDENT, 0);
    yylval->node = node;
    char *dup_value = parse_strdup(yytext, result->malloc_pool_);
    check_value(dup_value);
    node->str_value_ = str_tolower(dup_value);
    node->value_ = strlen(node->str_value_);*/
  yylval->node = malloc_new_node(((ParseResult*)yyextra)->Doc.GetAllocator(), T_IDENT);

  dup_str(yytext);
  yylval->node->AddMember("str_value_", str ,((ParseResult*)yyextra)->Doc.GetAllocator());
  //cout<<"yylex print : "<<yytext<<endl;
  yylval->node->AddMember("value_", strlen(yytext),((ParseResult*)yyextra)->Doc.GetAllocator());
  ret = NAME;
  }
  else
  {
    yylval->non_reserved_keyword = const_cast<NonReservedKeyword *>(word);
    ret = word->keyword_type;
  }
  return ret;
}

[ \t\r\n]    {}
"--"[ \t].*;

<<EOF>>    {return END_P;}
.    {
 // yyerror(yylloc, result, "mystery charactor '%c'", *yytext);
  return ERROR;
}
%%

void * yyalloc (size_t bytes, void* yyscanner)
{
  //ParseResult *p = yyget_extra(yyscanner);
  //return parse_malloc(bytes, p->malloc_pool_);
  return malloc(bytes);
}

void * yyrealloc (void * ptr, size_t bytes, void* yyscanner)
{
  //ParseResult *p = yyget_extra(yyscanner);
  //return parse_realloc(ptr, bytes, p->malloc_pool_);
  return realloc(ptr,bytes);;
}

void yyfree (void * ptr, void * yyscanner)
{
  /* Do nothing -- we leave it to the garbage collector. */
// parse_free(ptr);
   free(ptr);
}


//int yywrap(void)
//{
//return 1;
//}
