#ifndef PARAS_TAB_HPP  
#define PARAS_TAB_HPP  
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "stdarg.h"
#include <iostream>//使用C++库  
#include <string>
#include <stdio.h>//printf和FILE要用的 

#define MAX_ERROR_MSG 1024
using namespace std;

#ifndef YYTOKENTYPE
#define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
 *       know about them.  */
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
     SKIP_LEVEL  = 454,
     UNLOCKED = 455,
     UPDATESERVER = 456,
     USE_BLOOM_FILTER = 457,
     VARIABLES = 458,
     VERBOSE = 459,
     WARNINGS = 460
   };

typedef enum ObPrivilegeType
  {
    OB_PRIV_INVALID = 0,      /*invalid privilege type*/
    OB_PRIV_ALL = 1,
    OB_PRIV_ALTER = 2,
    OB_PRIV_CREATE = 3,
    OB_PRIV_CREATE_USER = 4,
    OB_PRIV_DELETE = 5,
    OB_PRIV_DROP = 6,
    OB_PRIV_GRANT_OPTION = 7,
    OB_PRIV_INSERT = 8,
    OB_PRIV_UPDATE = 9,
    OB_PRIV_SELECT = 10,
    OB_PRIV_REPLACE = 11,
    OB_PRIV_NUM
  } ObPrivilegeType;
  

typedef enum NodeType
{
  T_INVALID = 0,  // Min tag

  /* Literal data type tags */
  T_INT = 1,
  T_STRING = 2,
  T_BINARY = 3,
  T_DATE = 4,     // WE may need time and timestamp here
  T_FLOAT = 5,
  T_DOUBLE = 6,
  T_DECIMAL = 7,
  T_BOOL = 8,
  T_NULL = 9,
  T_QUESTIONMARK = 10,
  T_UNKNOWN = 11,

  /* Reference type tags*/
  T_REF_COLUMN = 20,
  T_REF_EXPR = 21,
  T_REF_QUERY = 22,

  T_HINT  = 30,     // Hint message from rowkey
  T_IDENT = 31,
  T_STAR = 32,
  T_SYSTEM_VARIABLE = 33,
  T_TEMP_VARIABLE = 34,

  /* Data type tags */
  T_TYPE_INTEGER  = 40,
  T_TYPE_FLOAT = 41,
  T_TYPE_DOUBLE = 42,
  T_TYPE_DECIMAL = 43,
  T_TYPE_BOOLEAN = 44,
  T_TYPE_DATE = 45,
  T_TYPE_TIME = 46,
  T_TYPE_DATETIME = 47,
  T_TYPE_TIMESTAMP = 48,
  T_TYPE_CHARACTER = 49,
  T_TYPE_VARCHAR = 50,
  T_TYPE_CREATETIME = 51,
  T_TYPE_MODIFYTIME = 52,
  T_TYPE_SHORT = 53,
  T_TYPE_INT   = 54,
  T_TYPE_LONG  = 55,
  T_TYPE_LONGLONG  = 56,
  
  // @note !! the order of the following tags between T_MIN_OP and T_MAX_OP SHOULD NOT be changed
  /* Operator tags */
  T_MIN_OP = 100,
  /* 1. arithmetic operators */
  T_OP_NEG = 101,   // negative
  T_OP_POS= 102,   // positive
  T_OP_ADD= 103,
  T_OP_MINUS= 104,
  T_OP_MUL= 105,
  T_OP_DIV= 106,
  T_OP_POW= 107,
  T_OP_REM= 108,   // remainder
  T_OP_MOD= 109,
  T_OP_EQ= 110,      /* 2. Bool operators */
  T_OP_LE= 111,
  T_OP_LT= 112,
  T_OP_GE= 113,
  T_OP_GT= 114,
  T_OP_NE= 115,
  T_OP_IS= 116,
  T_OP_IS_NOT= 117,
  T_OP_BTW= 118,
  T_OP_NOT_BTW= 119,
  T_OP_LIKE= 120,
  T_OP_NOT_LIKE= 121,
  T_OP_NOT= 122,
  T_OP_AND= 123,
  T_OP_OR= 124,
  T_OP_IN= 125,
  T_OP_NOT_IN= 126,
  T_OP_ARG_CASE= 127,
  T_OP_CASE= 128,
  T_OP_ROW= 129,
  T_OP_EXISTS= 130,

  T_OP_CNN= 131,  /* 3. String operators */

  T_FUN_SYS= 61,                    // system functions, CHAR_LENGTH, ROUND, etc.
  T_OP_LEFT_PARAM_END= 62,
  T_MAX_OP= 63,

  T_CUR_TIME= 64,
  T_CUR_TIME_UPS= 65,
  T_CUR_TIME_OP= 66,

  T_ROW_COUNT= 67,
  T_FUN_SYS_CAST= 68,               // special system function : CAST(val AS type)

  /* 4. name filed specificator */
  T_OP_NAME_FIELD = 69,

  // @note !! the order of the following tags between T_FUN_MAX and T_FUN_AVG SHOULD NOT be changed
  /* Function tags */
  T_FUN_MAX= 70,
  T_FUN_MIN= 71,
  T_FUN_SUM= 72,
  T_FUN_COUNT= 73,
  T_FUN_AVG= 74,

  /* parse tree node tags */
  T_DELETE= 80,
  T_SELECT= 81,
  T_UPDATE= 82,
  T_INSERT= 83,
  T_EXPLAIN= 84,
  T_LINK_NODE= 85,
  T_ASSIGN_LIST= 86,
  T_ASSIGN_ITEM= 87,
  T_STMT_LIST= 88,
  T_EXPR_LIST= 89,
  T_WHEN_LIST= 90,
  T_PROJECT_LIST= 91,
  T_PROJECT_ITEM= 92,
  T_FROM_LIST= 93,
  T_SET_UNION= 94,
  T_SET_INTERSECT= 95,
  T_SET_EXCEPT= 96,
  T_WHERE_CLAUSE= 97,
  T_LIMIT_CLAUSE= 98,
  T_SORT_LIST= 140,
  T_SORT_KEY= 141,
  T_SORT_ASC= 142,
  T_SORT_DESC= 143,
  T_ALL= 144,
  T_DISTINCT= 145,
  T_ALIAS= 146,
  T_PROJECT_STRING= 147,
  T_COLUMN_LIST= 148,
  T_VALUE_LIST= 149,
  T_VALUE_VECTOR= 150,
  T_JOINED_TABLE= 151,
  T_JOIN_INNER= 152,
  T_JOIN_FULL= 153,
  T_JOIN_LEFT= 154,
  T_JOIN_RIGHT= 155,
  T_CASE= 156,
  T_WHEN= 157,

  T_CREATE_TABLE= 158,
  T_TABLE_ELEMENT_LIST= 159,
  T_TABLE_OPTION_LIST= 160,
  T_PRIMARY_KEY= 161,
  T_COLUMN_DEFINITION= 162,
  T_COLUMN_ATTRIBUTES= 163,
  T_CONSTR_NOT_NULL= 164,
  T_CONSTR_NULL= 165,
  T_CONSTR_DEFAULT= 166,
  T_CONSTR_AUTO_INCREMENT= 167,
  T_CONSTR_PRIMARY_KEY= 168,
  T_IF_NOT_EXISTS= 169,
  T_IF_EXISTS= 170,
  T_JOIN_INFO = 171,
  T_EXPIRE_INFO= 172,
  T_TABLET_MAX_SIZE= 173,
  T_TABLET_BLOCK_SIZE= 174,
  T_TABLET_ID= 175,
  T_REPLICA_NUM= 176,
  T_COMPRESS_METHOD= 177,
  T_COMMENT= 178,
  T_USE_BLOOM_FILTER= 179,
  T_CONSISTENT_MODE= 180,
  T_DROP_TABLE= 181,
  T_TABLE_LIST= 182,

  T_ALTER_TABLE= 183,
  T_ALTER_ACTION_LIST= 184,
  T_TABLE_RENAME= 185,
  T_COLUMN_DROP= 186,
  T_COLUMN_ALTER= 187,
  T_COLUMN_RENAME= 188,

  T_ALTER_SYSTEM= 189,
  T_CHANGE_OBI= 190,
  T_FORCE= 191,
  T_SET_MASTER= 192,
  T_SET_SLAVE= 193,
  T_SET_MASTER_SLAVE= 194,
  T_SYTEM_ACTION_LIST= 195,
  T_SYSTEM_ACTION= 196,
  T_CLUSTER= 197,
  T_SERVER_ADDRESS= 198,

  T_SHOW_TABLES= 199,
  T_SHOW_VARIABLES= 200,
  T_SHOW_COLUMNS= 201,
  T_SHOW_SCHEMA= 202,
  T_SHOW_CREATE_TABLE= 203,
  T_SHOW_TABLE_STATUS= 204,
  T_SHOW_PARAMETERS= 205,
  T_SHOW_SERVER_STATUS= 206,
  T_SHOW_WARNINGS= 207,
  T_SHOW_GRANTS= 208,
  T_SHOW_PROCESSLIST= 209,
  T_SHOW_LIMIT= 210,


  T_CREATE_USER= 211,
  T_CREATE_USER_SPEC= 212,
  T_DROP_USER= 213,
  T_SET_PASSWORD= 214,
  T_RENAME_USER= 215,
  T_RENAME_INFO= 216,
  T_LOCK_USER= 217,
  T_GRANT= 218,
  T_PRIVILEGES= 219,
  T_PRIV_LEVEL= 220,
  T_PRIV_TYPE= 221,
  T_USERS= 222,
  T_REVOKE= 223,
  T_BEGIN= 224,
  T_COMMIT= 225,
  T_PREPARE= 226,
  T_DEALLOCATE= 227,
  T_EXECUTE= 228,
  T_ARGUMENT_LIST= 229,
  T_VARIABLE_SET= 230,
  T_VAR_VAL= 231,
  T_ROLLBACK= 232,

  T_HINT_OPTION_LIST= 233,
  T_READ_STATIC= 234,
  T_HOTSPOT= 235,
  T_READ_CONSISTENCY= 236,

  T_KILL= 237,

  T_MAX= 238,
  T_RELATION= 239,
  T_THEN = 240,
  T_SELECT_NO_PARENS=241,
  T_SELECT_WITH_PARENS = 242,
  
  
  T_SUB_SELECT = 243,
  T_JOIN_CONDITION = 244,
  T_CONST_CONDITION = 245,
  T_NORMAL_DOUBLE_CONDITION = 246,
  T_NORMAL_SINGLE_CONDITION = 247,
  T_COMPLEX_DOUBLE_CONDITION = 248,
  T_BTW_CONDITION = 249,
  
  T_OP_NOT_EXISTS = 250,
  T_SEMI_JOIN_LIST = 251,
  T_ANTI_JOIN_LIST = 252,
  T_IGNORE = 253,
  
  T_CREATE_INDEX      = 254,
  T_INDEX_COLUMN_LIST = 255,
  T_INDEX_UNIQUE			= 256,
  T_INDEX_FULLTEXT		= 257,
  T_INDEX_SPATIAL			= 258,
  T_INDEX_HASH				= 259,
  T_INDEX_BTREE				= 260,
  T_INDEX_SKIPLIST		= 261,
  T_EXTERN_SIZE        = 262,
  T_SKIP_LEVEL				= 263
} NodeType;
  
  
#endif

#define ISSPACE(c) ((c) == ' ' || (c) == '\n' || (c) == '\r' || (c) == '\t' || (c) == '\f' || (c) == '\v')

#ifndef OB_NON_RESERVED_KEYWORDS_H_
#define OB_NON_RESERVED_KEYWORDS_H_
typedef struct _NonReservedKeyword
{
  const char *keyword_name;
  int keyword_type;
} NonReservedKeyword;

extern const NonReservedKeyword *non_reserved_keyword_lookup(const char *word);
#endif 

struct Type//通常这里面每个成员，每次只会使用其中一个，一般是定义成union以节省空间(但这里用了string等复杂类型造成不可以) 
{  
  //struct _ParseNode *node;
  rapidjson::Document *doc;
 // rapidjson::Document::AllocatorType Allocator;
  rapidjson::Value *node;
  char * str_name;
  int    ival;
  NonReservedKeyword * non_reserved_keyword;

};

#define YYSTYPE Type

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
#define yyltype YYLTYPE /* obsolescent; will be withdrawn */
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
//#define YYSTYPE Type//把YYSTYPE(即yylval变量)重定义为struct Type类型，这样lex就能向yacc返回更多的数据了  
  
#endif


typedef struct _ParseResult
{
  void*   		  				 yyscan_info_;
  rapidjson::Value  *    result_tree_;
  const char*   				 input_sql_;
  int           				 input_sql_len_;
  rapidjson::Document    Doc; 
  char    error_msg_[MAX_ERROR_MSG];
  int     start_col_;
  int     end_col_;
  int     line_;
  int     yycolumn_;
  int     yylineno_;
  char*   tmp_literal_;
} ParseResult;

extern int parse_sql(ParseResult* p, const char* buf, size_t len);
extern int parse_init(ParseResult* p);
extern int parse_terminate(ParseResult* p);
#endif

