#ifndef QYAN_TAB_HPP  
#define QYAN_TAB_HPP  
#include "parser.hh"
#include<vector>
#include<string>
#include "../../util/log/log_util.h"


// 生成1个常数1
rapidjson::Value  * create_const_value(rapidjson::Document::AllocatorType& Allocator){
rapidjson::Value  * v = new rapidjson::Value;
v->SetObject().AddMember("tag",T_INT, Allocator );
v->AddMember("str_value_","1", Allocator );
v->AddMember("value_",1, Allocator );
v->AddMember("CONST_TYPE","INTNUM", Allocator );
return v;
}

//嵌套 两个由 and 连接的 conditions
rapidjson::Value  * nest_and_condition(rapidjson::Value & nested_one,rapidjson::Value & nested_two,rapidjson::Document::AllocatorType& Allocator){
rapidjson::Value tmp1;
rapidjson::Value tmp2;

rapidjson::Value  * v = new rapidjson::Value;
v->SetObject().AddMember("tag",T_OP_AND, Allocator );
v->AddMember("OP_TYPE","AND", Allocator );

rapidjson::Value  * children = new rapidjson::Value;
children->SetArray().PushBack(tmp1.CopyFrom(nested_one,Allocator),Allocator);
children->PushBack(tmp2.CopyFrom(nested_two,Allocator),Allocator);
v->AddMember("children",*children, Allocator );
return v;
}

//嵌套 两个由 EQ 连接的 and conditions 
rapidjson::Value  * nest_eq_condition(rapidjson::Value & nested_one,rapidjson::Value & nested_two,rapidjson::Document::AllocatorType& Allocator){
rapidjson::Value tmp1;
rapidjson::Value tmp2;
	
rapidjson::Value  * v = new rapidjson::Value;
v->SetObject().AddMember("tag",T_OP_EQ, Allocator );
v->AddMember("OP_TYPE","EQ", Allocator );

rapidjson::Value  * children = new rapidjson::Value;
children->SetArray().PushBack(tmp1.CopyFrom(nested_one,Allocator),Allocator).PushBack(tmp2.CopyFrom(nested_two,Allocator),Allocator);
v->AddMember("children",*children, Allocator );
return v;
}

//嵌套 两个由 EQ 连接的 or conditions
rapidjson::Value  * nest_or_eq_condition(rapidjson::Value & nested_one,rapidjson::Value & nested_two,rapidjson::Document::AllocatorType& Allocator){
rapidjson::Value tmp1;
rapidjson::Value tmp2;
	
rapidjson::Value  * v = new rapidjson::Value;
v->SetObject().AddMember("tag",T_OP_OR, Allocator );
v->AddMember("OP_TYPE","OR", Allocator );

rapidjson::Value  * children = new rapidjson::Value;
children->SetArray().PushBack(tmp1.CopyFrom(nested_one,Allocator),Allocator).PushBack(tmp2.CopyFrom(nested_two,Allocator),Allocator);
v->AddMember("children",*children, Allocator );
return v;
}

#define MAKE_EMPTY( empty ) \
	  rapidjson::Value  (empty) ; \
		(empty).SetObject().AddMember("tag",T_IGNORE,doc->GetAllocator() );\
		(empty).AddMember("IS_IGNORE",1,doc->GetAllocator() );
 


void rapidjson_log(rapidjson::Value  * v)
	{
		 rapidjson::StringBuffer buffer;
     rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		 rapidjson::Document    Doc;
		 rapidjson::Value   		vv;
		 Doc.SetObject().AddMember( "LOG",vv.CopyFrom( *v, Doc.GetAllocator() ),Doc.GetAllocator() );
		 
		 Doc.Accept(writer);
		 
		 CPP_DEBUG<<buffer.GetString() << std::endl;
	}
	
	void rapidjson_log(rapidjson::Value  & v)
	{
		rapidjson_log(&v);
	}


 struct SelectItem
    {
      //uint64_t   expr_id_;
      bool       is_real_alias_;
      string     alias_name_;
      string     expr_name_;
      int        type_;
    };

 struct OrderItem
    {
      enum OrderType
      {
        ASC,
        DESC
      };

      //uint64_t   expr_id_;
      OrderType  order_type_;
    };

    struct JoinedTable
    {
      enum JoinType
      {
        T_FULL,
        T_LEFT,
        T_RIGHT,
        T_INNER,
      };
    };
        
struct TableItem  
{  
    string    table_name_;  
    string    alias_name_;  
    string    sub_select_alias_name_;
    TableItem(string & table_name , string & alias_name, string & sub_select_alias_name ):table_name_(table_name),alias_name_(alias_name),sub_select_alias_name_(sub_select_alias_name){}
};  

struct RawTarget
{
	  std::string    relation_name;  
    std::string    column_name;  
    std::string    project_alias;   
  RawTarget (const char * _relation_name,  const char * _column_name ):relation_name(_relation_name),column_name(_column_name){}
	RawTarget (const char * _column_name ):column_name(_column_name){}
  RawTarget (std::string & _relation_name, std::string & _column_name ):relation_name(_relation_name),column_name(_column_name){}


};


struct GroupTarget
{
	std::string    relation_name; 
	std::string    alias_name; 
    std::string    column_name;  
	GroupTarget (std::string & _relation_name,  std::string & _column_name ):relation_name(_relation_name),column_name(_column_name){}
	GroupTarget (const char * _column_name ):column_name(_column_name){}

};

struct OrderTarget
{
	std::string    relation_name; 
	std::string    alias_name;
    std::string    column_name;  
	OrderTarget (std::string & _relation_name,  std::string & _column_name ):relation_name(_relation_name),column_name(_column_name){}
	OrderTarget (const char * _column_name ):column_name(_column_name){}

};


#define check_and_assign_member( target, _member ) \
if(  root->HasMember( _member ) )					 \
		{                                                 		\
			(target) = &( (*root)[ _member ] );			\
		}																						\
		else CPP_DEBUG<<"do not have "<<_member<<endl;



class QueryAnalyser
{
public:
rapidjson::Value    *root;
rapidjson::Document *doc;

int is_distinct;
int is_join;
int sub_links_count;
int is_select_all;
// 原始要素
rapidjson::Value  * project_lists;
rapidjson::Value  * from_list;
rapidjson::Value  * where_list;
rapidjson::Value  * group_list;
rapidjson::Value  * having_list;
rapidjson::Value  * order_list;
rapidjson::Value  * hints_list;

// select_list 解析要素
vector<rapidjson::Value *> aggregat_funs; 					// 聚合函数
vector<RawTarget> raw_target_list;         // 不可再分的非常量目标 
vector<rapidjson::Value *> project_opers;           // 作用于目标列的操作
vector<rapidjson::Value *> nomal_funs;							// 非聚合普通函数

//from_list 解析要素
vector<QueryAnalyser>      sub_querys;  		  // from  中的子查询
rapidjson::Value  *        sub_query_father;  // 当自己就是子查询时，sub_query_father  指向 RELATION 的上一层
vector<TableItem>     		 tables;				 	  // 解析后的表
vector<rapidjson::Value *> single_fromlists;  // from  中的子查询


// where 条件要素
vector<QueryAnalyser> sub_links; 	   					// where 中的子链接
rapidjson::Value  * sub_link_father;          // 当自己就是自连接中的 子查询时，sub_link_father  指向 SUB_LINK_BODY 的上一层
QueryAnalyser  *   up_stmt; 					//如果是子连接 则还要存一个上层 where

vector<rapidjson::Value *> join_conditions;   				// 关联条件
vector<rapidjson::Value *> const_conditions;         	// 常数不可再分条件
vector<rapidjson::Value *> nomal_single_conditions;  	// 单操作数不可再分条件
vector<rapidjson::Value *> nomal_double_conditions;  	// 双操作数不可再分条件
vector<rapidjson::Value *> complex_double_conditions; // 可再分双操作数条件
vector<rapidjson::Value *> nomal_btw_conditions;      // between and 
	
// Group 条件要素	
vector< GroupTarget > group_target;      

// Order by 条件要素	
vector< OrderTarget > order_target;   

int order_by_tag;   

//	having 条件要素
vector< rapidjson::Value * > having_conditions;      // between and 	

    // 是否是子连接 
    int check_if_sub_query_link(int tag)
    {
    	if(tag == T_OP_EXISTS || tag == T_OP_IN || tag == T_OP_NOT_IN )
    	{
    	  return 1;
    	}
    	return 0;
    }	
    
     // 是否是逻辑连接 
    int check_if_logic_predication(int tag)
    {
    	switch(tag)
    	{
    		case  T_OP_AND  :
    	  case  T_OP_OR   :   
    	  return 1;
    	}
    	return 0;
    }	
    
     // 是否是常量值 
    int check_if_const_value(int tag)
    {
    	if( (tag>= T_INT  && tag <= T_UNKNOWN) || (tag>= T_TYPE_INTEGER  && tag <= T_TYPE_MODIFYTIME) )
    	{
    	  return 1;
    	}
    	return 0;
    }	
    
    // 是否是关联连接 
     int check_if_join_condition(int tag)
    {
    	if( tag == T_OP_NAME_FIELD  || tag == T_IDENT )
    	{
    	  return 1;
    	}
    	return 0;
    }	
    
        // 是否是字段引用
     int check_if_name_filed(int tag)
    {
    	if( tag == T_OP_NAME_FIELD   )
    	{
    	  return 1;
    	}
    	return 0;
    }	
    
 
      // 是否是关联连接 
     int check_if_obvious_join(int tag)
    {
    	if( tag >= T_JOIN_INNER  && tag <= T_JOIN_RIGHT )
    	{
    	  return 1;
    	}
    	return 0;
    }	
  
   // 是否是聚合函数 
     int check_if_aggregation_fun(int tag)
    {
    	if( ( tag >= T_FUN_MAX  && tag <= T_FUN_AVG ) )
    	{
    	  return 1;
    	}
    	return 0;
    }	
    // 是否是时间函数 
     int check_if_time_fun(int tag)
    {
    	if(  tag >= T_CUR_TIME  && tag <= T_CUR_TIME_OP )  
    	{
    	  return 1;
    	}
    	return 0;
    }	
    
void swap_father(rapidjson::Value *father, rapidjson::Value *member, int tag ,const char * type_name ){
 		 	rapidjson::Value  *val_father ;
		  val_father = new rapidjson::Value;
		  rapidjson::Value val_tag;
		  val_tag.SetInt(tag);	
		  val_father->SetObject().AddMember("tag", val_tag, doc->GetAllocator() ).AddMember( rapidjson::StringRef( type_name ) ,*member, doc->GetAllocator() ) ;
		  father->Swap(*val_father);
}
	
public:
QueryAnalyser(rapidjson::Value & value ,rapidjson::Document & doc_ , QueryAnalyser * up_stmt_ = NULL ):root( &( value ) ) ,
																																		doc( &doc_ ),
																																		project_lists(NULL),
																																		from_list		 (NULL),
																																		where_list	 (NULL),
																																		up_stmt (up_stmt_),
																																		group_list	(NULL),
																																		having_list (NULL),
																																		order_list	(NULL),
																																		hints_list	(NULL),
																																		sub_links_count ( 0 ),
																																		order_by_tag ( 0 ),
																																		is_select_all ( 0 )
{
select_prepared();
}

//QueryAnalyser(QueryAnalyser & qa):root(qa.root),doc(qa.doc),is_distinct(qa.is_distinct),is_join(qa.is_join),sub_links_count(qa.sub_links_count),is_select_all(qa.is_select_all),
//																	project_lists(qa.project_lists),from_list(qa.from_list),where_list(qa.where_list),group_list(qa.group_list),having_list(qa.having_list),order_list(qa.order_list),hints_list(qa.hints_list),
//																	aggregat_funs(qa.aggregat_funs),raw_target_list(qa.raw_target_list),project_opers(qa.project_opers),nomal_funs(qa.nomal_funs),
//																	sub_querys(qa.sub_querys),sub_query_father(qa.sub_query_father),tables(qa.tables),single_fromlists(qa.single_fromlists),
//																	sub_links(qa.sub_links),sub_link_father(qa.sub_link_father),up_stmt(qa.up_stmt),
//																	join_conditions(qa.join_conditions),const_conditions(qa.const_conditions),nomal_single_conditions(qa.nomal_single_conditions),nomal_double_conditions(qa.nomal_double_conditions),
//																	complex_double_conditions(qa.complex_double_conditions),nomal_btw_conditions(qa.nomal_btw_conditions),
//																	group_target(qa.group_target),order_target(qa.order_target){}

void clone (QueryAnalyser & qa)
{
// 上下文要素
//root = qa.root;
//doc  = qa.doc;

// 原始要素
//project_lists = qa.project_lists;
//from_list = qa.from_list;
//where_list = qa.where_list;
//group_list = qa.group_list;
//having_list = qa.having_list;
//order_list = qa.order_list;
//hints_list = qa.hints_list;

//类别判断
is_distinct = qa.is_distinct;
is_join = qa.is_join;
sub_links_count = qa.sub_links_count;
is_select_all= qa.is_select_all;

// select_list 解析要素
aggregat_funs   = qa.aggregat_funs; 					// 聚合函数
raw_target_list = qa.raw_target_list;         // 不可再分的非常量目标 
project_opers   = qa.project_opers;           // 作用于目标列的操作
nomal_funs      = qa.nomal_funs;							// 非聚合普通函数

//from_list 解析要素
sub_querys       = qa.sub_querys;  		  // from 中的子查询
sub_query_father = qa.sub_query_father; // 当自己就是子查询时，sub_query_father  指向 RELATION 的上一层
tables           = qa.tables;				 	  // 解析后的表
single_fromlists = qa.single_fromlists; // from 中的子查询

// where 条件要素
sub_links        = qa.sub_links; 	   					// where 中的子链接
sub_link_father  = qa.sub_link_father;        // 当自己就是自连接中的 子查询时，sub_link_father  指向 SUB_LINK_BODY 的上一层
up_stmt          = qa.up_stmt; 					      //如果是子连接 则还要存一个上层 where

join_conditions           = qa.join_conditions;   				// 关联条件
const_conditions          = qa.const_conditions;         	// 常数不可再分条件
nomal_single_conditions   = qa.nomal_single_conditions;  	// 单操作数不可再分条件
nomal_double_conditions   = qa.nomal_double_conditions;  	// 双操作数不可再分条件
complex_double_conditions = qa.complex_double_conditions; // 可再分双操作数条件
nomal_btw_conditions      = qa.nomal_btw_conditions;      // between and 
	
// Group 条件要素	
group_target = qa.group_target;      

// Order by 条件要素	
order_target = qa.order_target;   
}

void set_sub_link_father(rapidjson::Value  * v){
	sub_link_father = v;
	
}

void set_sub_query_father(rapidjson::Value  * v){
	sub_query_father = v;
	
}
	// 特殊关联关系打标签
int mark_special_join(rapidjson::Value  * v0,int tag,int level){
int tmp[2] = {0};
int i = 0;
CPP_DEBUG<< " mark_special_join in" <<endl;
rapidjson::Value  * v = v0;
if ( v0->HasMember("JOIN_CONDITION") ) v = &(*v0)["JOIN_CONDITION"];
rapidjson_log( v );
if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 2 ){
for (auto& vv : (*v)["children"].GetArray()) 
{
	tmp[i++] = vv["tag"].GetInt() ;
	cout<<vv["tag"].GetInt()<<endl;
}
CPP_DEBUG<< " Resolve_Two_Oper_condition " <<endl;

// 关联条件
if( check_if_join_condition(tmp[0]) && check_if_join_condition(tmp[1]) && (*v)["tag"].GetInt() == T_OP_EQ ){
	 CPP_DEBUG<< "特殊关联条件 " <<endl;
	 if(tag == T_SEMI_JOIN_LIST)v->AddMember("SEMI_JOIN_LEVEL",level,doc->GetAllocator());
	 if(tag == T_ANTI_JOIN_LIST)v->AddMember("ANTI_JOIN_LEVEL",level,doc->GetAllocator());

	 join_conditions.emplace_back( v );
	 return 0;
}
// 逻辑关系 相连的两个条件 --> 可继续细分
if(  check_if_logic_predication( (*v)["tag"].GetInt() ) )
{

	// 递归细分
	 mark_special_join( &((*v)["children"][0]), tag,level );
	 mark_special_join( &((*v)["children"][0]), tag,level );
	
	return 0;
}

}
	 	
}
				
    //0. in 子链接转换成 exists 子链接
			// in 替换成 exists
			// 并把 x in （select y ）转换成 exists 中的where 条件
void transform_in_to_exists(rapidjson::Value  * v ){

      if (  v->HasMember("OP_TYPE")  && (*v)["tag"].GetInt() == T_OP_NOT &&
      	    (*v)["children"][0]["tag"].GetInt() == T_OP_EXISTS ){
      	    	(*v)["children"][0]["tag"].SetInt(T_OP_NOT_EXISTS);
      	    	(*v)["children"][0]["SUB_LINK_TYPE"].SetString("NOT EXISTS");
      	    	v->Swap((*v)["children"][0] );
      	    	return;
      	    }

			if (  v->HasMember("OP_TYPE")  &&
				 (   (*v)["tag"].GetInt() == T_OP_IN || (*v)["tag"].GetInt() == T_OP_NOT_IN ) &&
				 ( (*v)["children"][1].HasMember("SUB_LINK_TYPE")  )
				
				){
						rapidjson::Value & sub_select = (*v)["children"][1]["SUB_LINK_BODY"]["SUB_SELECT"];
						if((*v)["tag"].GetInt() == T_OP_IN ) {
							(*v)["children"][1]["SUB_LINK_TYPE"].SetString("EXISTS"); // 改成 exists
							(*v)["children"][1]["tag"] = T_OP_EXISTS;
						}
							else if( (*v)["tag"].GetInt() == T_OP_NOT_IN ){
								(*v)["children"][1]["SUB_LINK_TYPE"].SetString("NOT EXISTS"); // 改成not exists
								(*v)["children"][1]["tag"].SetInt(T_OP_NOT_EXISTS);
						}
						rapidjson::Value  * veq =	 nest_eq_condition( (*v)["children"][0],       
								  																				sub_select["SELECT_CLAUSE"]["children"][0]["PROJECT"],         
																													doc->GetAllocator());             
						
						if(sub_select.HasMember("WHERE_CLAUSE") ){
							
							sub_select["WHERE_CLAUSE"].Swap( *nest_and_condition( 
																									*veq,
																									sub_select["WHERE_CLAUSE"],
																									doc->GetAllocator()
																						 )
																						 );
						}else{
						                                          
							sub_select.AddMember("WHERE_CLAUSE", *veq ,doc->GetAllocator()	);
							
						}
						//消掉in
						v->Swap((*v)["children"][1] );
					 //return;
				}


}

//pushback_subquery_from_list
void pushback_subquery_from_list( rapidjson::Value  * fromlist, rapidjson::Value  * pushback_list,rapidjson::Document::AllocatorType& Allocator ){
		//遍历 from_list 将数据表填入 table_names, 将子查询 填入 sub_querys
  	if( fromlist->IsArray() ) {
  		for (auto& v : ( (*fromlist).GetArray() )  ){  				
  				pushback_subquery_from_list(&v,pushback_list,Allocator );
         }//end for
    }
  else if(NULL != fromlist && NULL != pushback_list  ){
  	pushback_list->PushBack(*fromlist,Allocator );
  	}
         
} // end 

void   pull_up_subquerys(){
   if( 0 != sub_querys.size() ){
   	pull_up_subquerys(this);
  }
}

//子查询上拉
void   pull_up_subquerys(QueryAnalyser *qa ){
	// 递归上拉子链接
	if( qa->sub_querys.size()> 0 ){
		CPP_DEBUG<<"0>>>pull_up_subquerys"<<endl;
		for( auto &sub_query : qa->sub_querys ){
				pull_up_subquerys( &sub_query );
		}
		// 清理子连接	  
	  qa->sub_querys.clear();
	//return ;
	}
	CPP_DEBUG<<" qa->up_stmt "<<  qa->up_stmt  <<endl;
	CPP_DEBUG<<" a->sub_querys.size() "<<  qa->sub_querys.size() <<endl;
	//最底层的子连接，上拉到上一层的 from list
	if(/*qa->up_stmt && */ 0 == qa->sub_querys.size()){
		
		//rapidjson_log(qa->root);
		
		//先判读是否可以上拉
		//聚合函数不能上拉
		// 非关联,先暂时上拉 
		if(qa->aggregat_funs.size()>0 || qa->group_target.size()>0)return;
		
		// 创建 join list
		rapidjson::Value  join_list ;
		
		// 将 from_list 上拉到父层的 semi join 或 anti join	
  	join_list.SetObject().Swap( (*(qa->root))["FROM_CLAUSE"] );
		
		//rapidjson::Value  empty ;
		//empty.SetObject().AddMember("tag",T_IGNORE,doc->GetAllocator() );
		
	  // 将 from_list 上拉到父层
		pushback_subquery_from_list(&join_list["children"],
															&(*(qa->up_stmt->from_list))["children"] ,
															doc->GetAllocator() );

   
	  // 将 conditions 上拉到父层 conditions
		qa->up_stmt->where_list->Swap(
			 *nest_and_condition(*(qa->where_list),
													 *(qa->up_stmt->where_list),
													   doc->GetAllocator()        )
												);
		
		//清理已经被上拉的子查询
		//1. 获得刚上拉到父层 from_list 数组里的最后一个位置 last
		//2. 将要删除的value 与 last位置的value Swap
		//3. 父层 from_list PopBack() 即完成清理
			int last = (*(qa->up_stmt->from_list))["children"].Size() - 1;
			qa->sub_query_father->Swap( (*(qa->up_stmt->from_list))["children"][last] );
			(*(qa->up_stmt->from_list))["children"].PopBack();
			
				
			}
					 
	}

//pushback_sublink_from_list
void pushback_sublink_from_list( rapidjson::Value  * fromlist, rapidjson::Value  * pushback_list,rapidjson::Document::AllocatorType& Allocator,int tag,int level ){
		//遍历 from_list 将数据表填入 table_names, 将子查询 填入 sub_querys
  	if( fromlist->IsArray() ) {
  		for (auto& v : ( (*fromlist).GetArray() )  ){  				
  				pushback_sublink_from_list(&v,pushback_list,Allocator,tag,level );
         }//end for
    }
  else if(NULL != fromlist && NULL != pushback_list  ){
  	
  	if(!fromlist->HasMember("LEVEL") ){
  		(*fromlist)["tag"].SetInt(tag);
  				if( (*fromlist)["tag"].GetInt() == T_SEMI_JOIN_LIST )fromlist->AddMember("SEMI_JOIN",1,Allocator);
  				if( (*fromlist)["tag"].GetInt() == T_ANTI_JOIN_LIST )fromlist->AddMember("ANTI_JOIN",1,Allocator);

  		fromlist->AddMember("LEVEL",level,Allocator);
  	}

  	pushback_list->PushBack(*fromlist,Allocator );
  	}
         
} // end 

void   pull_up_sublinks(){
   pull_up_sublinks(this);
}

//子链接 上拉为 semi join 或 anti join
void   pull_up_sublinks(QueryAnalyser *qa,int level = 0 ){
	// 递归上拉子链接
	if( qa->sub_links.size()> 0 ){
		
		for( auto &sub_link : qa->sub_links ){
				pull_up_sublinks( &sub_link ,level+1 );
		}
		// 清理子连接	  
	  qa->sub_links.clear();
	//return ;
	}
	//最底层的子连接，上拉到上一层的 from list
	if(qa->up_stmt && 0 == qa->sub_links.size()){
		
		//先判读是否可以上拉
		//聚合函数不能上拉
		// 非关联,先暂时上拉 
		if(qa->aggregat_funs.size()>0 || qa->group_target.size()>0)return;
		
		// 创建 semi_join list
		rapidjson::Value  semi_join_list ;
		
		// 将 from_list 上拉到父层的 semi join 或 anti join	
		semi_join_list.SetObject().Swap( (*(qa->root))["FROM_CLAUSE"] );
		
		//区分 semi join 和 anti join	,并挂到 father 上
		if((*(qa->sub_link_father))["tag"].GetInt() == T_OP_EXISTS    ){
		  semi_join_list["tag"].SetInt(T_SEMI_JOIN_LIST);
		  //qa->where_list->AddMember("SEMI_JOIN_LEVEL",level,doc->GetAllocator());
		  mark_special_join(qa->where_list,T_SEMI_JOIN_LIST, level);

		//  semi_join_list.AddMember("SEMI_JOIN_LEVEL",level,doc->GetAllocator());
			
		}
		if((*(qa->sub_link_father))["tag"].GetInt() == T_OP_NOT_EXISTS){
			semi_join_list["tag"].SetInt(T_ANTI_JOIN_LIST);
      //qa->where_list->AddMember("ANTI_JOIN_LEVEL",level,doc->GetAllocator());
		  mark_special_join(qa->where_list,T_ANTI_JOIN_LIST, level);
		//	semi_join_list.AddMember("ANTI_JOIN_LEVEL",level,doc->GetAllocator());
		}
   
   //(*(qa->up_stmt->from_list))["children"].PushBack(semi_join_list,doc->GetAllocator()); 
	  
	  rapidjson::Value  up_stmt_new_child ;
	  up_stmt_new_child.SetArray();
	  
	  // 将 from_list 上拉到父层
		pushback_sublink_from_list(&semi_join_list["children"],
															//&(*(qa->up_stmt->from_list))["children"] ,
															&up_stmt_new_child,
															doc->GetAllocator(),semi_join_list["tag"].GetInt(),level );
	  (*(qa->up_stmt->from_list))["children"].PushBack( up_stmt_new_child,doc->GetAllocator() );
	  // 将 conditions 上拉到父层 conditions
	  // 将 sub_link 替换成 sub_link 里的 where_list
	  qa->sub_link_father->Swap( *(qa->where_list) );
		
	}
}

void resolve_from_list_help( rapidjson::Value  * v,int level = 0 ){
	
					int is_alias = 0;
					int is_obvious_join = 0;

//rapidjson_log(v);

  				if( (*v).HasMember("RELATION_ALIAS") )is_alias = 1;
  				if( check_if_obvious_join((*v)["tag"].GetInt()) )is_obvious_join = 1;
  				
  				string table_name;  // 表名
  				string alias_name;  // 表别名
  				string sub_select_alias_name;  // 表别名
  				
  				// 显式的 联接写法
  				if(is_obvious_join){
  				   
  			  		for (int i = 1; i < 4; i++){ // 使用 SizeType 而不是 size_t
  			  		 if(i <3 )resolve_from_list( (&((*v)["children"][i])) , 0 );
  			  			if(3 == i){
  			  				join_conditions.emplace_back(&((*v)["children"][i]["JOIN_CONDITION"]));
  			  				resolve_where_list(  &((*v)["children"][i]["JOIN_CONDITION"]),v );
  			  			}
  			  	}
  			  }
  				
  				  if( (*v).HasMember("RELATION") && (*v)["RELATION"].HasMember("str_value_") ) table_name=string((*v)["RELATION"]["str_value_"].GetString()); 	// 表名				
  					if( (*v).HasMember("RELATION_ALIAS") ) alias_name=string((*v)["RELATION_ALIAS"]["str_value_"].GetString()); 		//表别名
  				  if( (*v).HasMember("SUB_SELECT_ALIAS") ) sub_select_alias_name=string((*v)["SUB_SELECT_ALIAS"]["str_value_"].GetString()); //子查询别名
  						
  				// 隐式的 内联写法
  				if(is_alias){
  				 //alias_name=string((*v)["RELATION_ALIAS"]["str_value_"].GetString()); 					
            
            //2. 子查询的情况，子查询无表名
            if( (*v)["RELATION"].HasMember("SUB_SELECT") ){
            			(*v)["RELATION"].AddMember("DEEP_LEVEL", level+1, doc->GetAllocator());
            			//sub_querys.emplace_back(&(v) );
  								// 递归子查询
  									 sub_querys.emplace_back( (*v)["RELATION"]["SUB_SELECT"], *doc , this );
  									 (sub_querys.end()-1)->set_sub_query_father(v);
  									 CPP_DEBUG<<"===========sub_querys.size()"<< sub_querys.size() <<endl;
  								//if( (*v)["SUB_SELECT"].HasMember("FROM_CLAUSE") )resolve_from_list( &((*v)["SUB_SELECT"]["FROM_CLAUSE"]), level+1 );
            	}
      		}	
							 // 插入解析后的表
  			 			 tables.emplace_back( TableItem(table_name,alias_name,sub_select_alias_name) );
  			 			 single_fromlists.emplace_back( v );
}

//解析 from_list
void resolve_from_list( rapidjson::Value  * fromlist,int level = 0 ){
  // 初步通过 fromlist 的个数判断是否关联
   //if( fromlist->HasMember("children")  &&  (*fromlist)["children"].GetArray().Size() != 1 )is_join = 1 ;else is_join = 0;
   //遍历 from_list 将数据表填入 table_names, 将子查询 填入 sub_querys
  	if( fromlist->IsArray() ) {
  		for (auto& v : ( (*fromlist).GetArray() )  ){  				
  				resolve_from_list( &(v),level);
         }//end for
    }
    else if(NULL != fromlist)resolve_from_list_help(fromlist,level);
         
} // end 




// 分析 where_list
void resolve_where_list( rapidjson::Value  * where_list,rapidjson::Value  * where_list_father ){
	
	resolve_single_condition( where_list ,where_list_father );
   	
}


// 判断 1 , 识别关联条件
// 判断 2 , 识别子连接  exists, in, not exists , not in
// 判断 3 ，识别普通条件
// 判断 4， 识别常量条件 5 > 3
 void resolve_single_condition( rapidjson::Value  * v ,rapidjson::Value  *  father){
 			int tmp[2] = {0};
 	    int i = 0;
			
			//0. 将in 转成 exists
			transform_in_to_exists(v);
			
			//1. 子连接,语法分析阶段已经打过标签了
			if ( v->HasMember("SUB_LINK_TYPE") ) {
					
					 // 记录 子连接的个数
					 ++sub_links_count;
					// 递归处理 子连接
					 sub_links.emplace_back( QueryAnalyser((*v)["SUB_LINK_BODY"]["SUB_SELECT"], *doc , this ));
  				 (sub_links.end()-1)->set_sub_link_father(v);
  				 return;
			} 
			
			  //2 单操作数条件
			if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 1 ){
				for (auto& vv : (*v)["children"].GetArray()) 
					{
						tmp[i++] = vv["tag"].GetInt() ;
						cout<<vv["tag"].GetInt()<<endl;
					}
						CPP_DEBUG<< " Resolve_One_Oper_condition " <<endl;
			  				 		  				 
				// 是常数条件
				if( check_if_const_value(tmp[0])   ){
						swap_father( father,v, T_CONST_CONDITION, "CONST_CONDITION"  );
						const_conditions.emplace_back( &(*father)["CONST_CONDITION"]  );
						return ;
				}
				// 是某个字段的情况
				if	( check_if_name_filed(tmp[0])  ){
					 swap_father( father,v, T_NORMAL_SINGLE_CONDITION, "NORMAL_SINGLE_CONDITION"  );
				   nomal_single_conditions.emplace_back( &(*father)["NORMAL_SINGLE_CONDITION"]  );
				   return ;
				}		  
			}
			
			// 3. 其他 两操作数条件打标签
			if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 2 ){
					for (auto& vv : (*v)["children"].GetArray()) 
						{
							tmp[i++] = vv["tag"].GetInt() ;
							cout<<vv["tag"].GetInt()<<endl;
						}
				 	CPP_DEBUG<< " Resolve_Two_Oper_condition " <<endl;

				 	// 关联条件
				 	if( check_if_join_condition(tmp[0]) && check_if_join_condition(tmp[1]) && (*v)["tag"].GetInt() == T_OP_EQ ){
						 CPP_DEBUG<< "关联条件 " <<endl;
				 		 swap_father( father,v, T_JOIN_CONDITION, "JOIN_CONDITION"  );
				 		 join_conditions.emplace_back( &(*father)["JOIN_CONDITION"] );
				 		 return ;
				 	}
				 
				 // 两个都是常数条件
				 if(  ( check_if_const_value(tmp[0]) && check_if_const_value(tmp[1]) ) ){
				 				
				 				//v->AddMember("is_const_condition", 1, doc->GetAllocator());
				 				//const_conditions.emplace_back(v);
				 				
				 		    swap_father( father,v, T_CONST_CONDITION, "CONST_CONDITION"   );
				 				const_conditions.emplace_back( &(*father)["CONST_CONDITION"]  );
				 				return ;
				 }
				 
				 // 其中一个条件是常量的情况，另一个条件是字段的情况
				 if(   check_if_const_value(tmp[0]) && check_if_name_filed(tmp[1]) ) 
				 	{
				 		 swap_father( father,v, T_NORMAL_DOUBLE_CONDITION, "NORMAL_DOUBLE_CONDITION"  );
				 		 //resolve_where_list( &((*father)["NORMAL_DOUBLE_CONDITION"]["children"][1]), &((*father)["NORMAL_DOUBLE_CONDITION"]["children"][1]) );
						 nomal_double_conditions.emplace_back( &(*father)["NORMAL_DOUBLE_CONDITION"]  );
						 return ;
				 		
				 	}
				 	// 其中一个条件是常量,另一个条件是字段的情况
				 if	( check_if_const_value(tmp[1]) && check_if_name_filed(tmp[0])  ){
				 
				 	 swap_father( father,v, T_NORMAL_DOUBLE_CONDITION, "NORMAL_DOUBLE_CONDITION"  );
				 	 //resolve_where_list( &((*father)["NORMAL_DOUBLE_CONDITION"]["children"][0]), &((*father)["NORMAL_DOUBLE_CONDITION"]["children"][0]) );
					 nomal_double_conditions.emplace_back( &(*father)["NORMAL_DOUBLE_CONDITION"]  );
					 return ;
				 }
				 		
				 		
				 // 逻辑关系 相连的两个条件 --> 可继续细分
				 if(  check_if_logic_predication( (*v)["tag"].GetInt() ) )
				 	{
				 		 	  swap_father( father,v, T_COMPLEX_DOUBLE_CONDITION, "COMPLEX_DOUBLE_CONDITION"  );
				 				complex_double_conditions.emplace_back( &( (*father)["COMPLEX_DOUBLE_CONDITION"] ) );
				 				CPP_DEBUG<< "递归细分 " <<endl;
				 				// 递归细分
				 			   resolve_where_list( &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][0]), &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][0]) );
				 			 	CPP_DEBUG<< "递归细分2 " <<endl; 
				 			 	 resolve_where_list( &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][1]), &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][1]) );

				 				return ;
				 }
				 				 
			}
			
		  // 4. 其他 3操作数条件打标签
			if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 3 ){
					
					int tmp[3] = {0};
					for (auto& vv : (*v)["children"].GetArray()) 
						{
							tmp[i++] = vv["tag"].GetInt() ;
							cout<<vv["tag"].GetInt()<<endl;
						}
					if( (*v)["tag"].GetInt() == T_OP_BTW && check_if_const_value(tmp[1])  &&  check_if_const_value(tmp[2]) )
					{
						swap_father( father,v, T_BTW_CONDITION, "NORMAL_BTW_CONDITION"  );
						nomal_btw_conditions.emplace_back( (&(*father)["NORMAL_BTW_CONDITION"]) );
					}
			}
 	
 }
 
 void resolve_project_list_help( rapidjson::Value  * v,int level = 0 ){
 	  rapidjson::Value  * vv ;
		if ( v->HasMember("PROJECT") )
			vv = &(*v)["PROJECT"];
		else vv = v;

		if ( vv->HasMember(rapidjson::StringRef("FUN_TYPE") )   ) {
				if (check_if_aggregation_fun( (*vv)["tag"].GetInt()) ) {	
					CPP_DEBUG<< "聚合函数 in"  <<endl;
					//聚合函数	
					aggregat_funs.emplace_back( vv );
					vv->AddMember("IS_AGGREGATE", 1, doc->GetAllocator());
				}
				else {
					//普通函数函数	
					nomal_funs.emplace_back( vv );
					vv->AddMember("IS_NOMAL_FUN", 1, doc->GetAllocator());
				}
			if ( vv->HasMember("children") )resolve_project_list( &(*vv)["children"],level);
			return;
		}
		
			if ( vv->HasMember("OP_TYPE")   ) {
			//目标上的运算	
			project_opers.emplace_back( vv );
			vv->AddMember("IS_PROJECT_OPER", 1, doc->GetAllocator());
			if ( vv->HasMember("children") )resolve_project_list(  &(*vv)["children"] ,level);
			return;
		}

			// raw project column
			if ( (*vv)["tag"] == T_OP_NAME_FIELD  ){
				if( vv->HasMember("RELATION_NAME") ) raw_target_list.emplace_back( RawTarget ( (*vv)["RELATION_NAME"]["str_value_"].GetString(),(*vv)["COLUMN_NAME"]["str_value_"].GetString() ) );
				else raw_target_list.emplace_back( RawTarget ( (*vv)["COLUMN_NAME"]["str_value_"].GetString() ) );
				return;
			}
			
			if ( v->HasMember("PROJECT_ALIAS") ){
			vv = &(*v)["PROJECT_ALIAS"];
			(raw_target_list.end()-1)->project_alias = (*vv)["str_value_"].GetString();
			return;
		  }
		  
		  if ( (*vv)["tag"] == T_STAR  ){
		  	CPP_DEBUG<<"******************"<<endl;
				vv->AddMember("SELECT_ALL",1,doc->GetAllocator());
				is_select_all = 1;
			return;
		  }
			
}


//解析 project_list
void resolve_project_list( rapidjson::Value  * projectlist,int level = 0 ){
   //遍历 projectlist 将数据表填入 table_names, 将子查询 填入 sub_querys
   	
  	if( projectlist->IsArray() ) {
  		for (auto& v : ( (*projectlist).GetArray() )  ){  				
  				resolve_project_list( &(v),level);
         }//end for
    }
    else if(NULL != projectlist)resolve_project_list_help(projectlist,level);
         
} // end 


//解析 groupby_list
void resolve_goupby_list( rapidjson::Value  * goupbylist){
  // 初步通过 goupbylist 的个数判断是否关联
  	if( goupbylist->IsArray() ) {
  		for (auto& v : ( (*goupbylist).GetArray() )  ){  				
  				resolve_goupby_list( &(v) );
         }//end for
    }
    else if(NULL != goupbylist)resolve_goupby_list_help(goupbylist);
         
} // end 


void resolve_goupby_list_help( rapidjson::Value  * v ){
	    if( (*v)["tag"].GetInt() == T_OP_NAME_FIELD ){
	    	 string relation_name;
	    	 string column_name;
	    		if( v->HasMember("RELATION_NAME") ){
	    				relation_name = (*v)["RELATION_NAME"]["str_value_"].GetString() ;
	    		}
	    		
	    		if( v->HasMember("COLUMN_NAME") ){
	    				column_name = (*v)["COLUMN_NAME"]["str_value_"].GetString() ;
	    		}
	    		group_target.emplace_back( relation_name, column_name );
	    }
}

//解析 orderby_list
void resolve_orderby_list( rapidjson::Value  * orderbylist){
  // 初步通过 orderbylist 的个数判断是否关联
  	if( orderbylist->IsArray() ) {
  		for (auto& v : ( (*orderbylist).GetArray() )  ){  				
  				resolve_orderby_list( &(v) );
         }//end for
    }
    else if(NULL != orderbylist)resolve_orderby_list_help(orderbylist);
         
} // end 


void resolve_orderby_list_help( rapidjson::Value  * v ){
	    if( (*v)["tag"].GetInt() == T_OP_NAME_FIELD ){
	    	 string relation_name;
	    	 string column_name;
	    		if( v->HasMember("RELATION_NAME") ){
	    				relation_name = (*v)["RELATION_NAME"]["str_value_"].GetString() ;
	    		}
	    		
	    		if( v->HasMember("COLUMN_NAME") ){
	    				column_name = (*v)["COLUMN_NAME"]["str_value_"].GetString() ;
	    		}
	    		order_target.emplace_back( relation_name, column_name );
	    }
	    
	    if( (*v)["tag"].GetInt() == T_SORT_ASC || (*v)["tag"].GetInt() == T_SORT_DESC ){
	    	order_by_tag = (*v)["tag"].GetInt(); 
	    }
}



int select_prepared()
{
	// 基本校验
	if(!root)return -1;
	//if( (*root)["tag"]!= T_STMT_LIST || (!root->HasMember("children")) || (*root)["children"].Size() == 0 )return -1;
	
		// 基本赋值
    //检查是否有 distinct			                                     
	  
	  	if(root->HasMember("T_DISTINCT") )is_distinct = 1 ; else is_distinct = 0;
	 //检查是否有 select_clause                                     
	  check_and_assign_member(project_lists,"SELECT_CLAUSE");        
	  //检查是否有 from_list                                         
	  check_and_assign_member(from_list,"FROM_CLAUSE");              
	  //检查是否有 where_list                                        
	  check_and_assign_member(where_list,"WHERE_CLAUSE");                   
	   //检查是否有 group_list                                       
	  check_and_assign_member(group_list,"GROUP_BY_CLAUSE");                
	   //检查是否有 having_list                                      
	  check_and_assign_member(having_list,"HAVING_CLAUSE");            
	  //检查是否有 order_list                                        
	  check_and_assign_member(order_list,"ORDER_BY_CLAUSE");                

   // if( project_lists->HasMember("SUB_SELECT") )project_lists =  &(*project_lists)["SUB_SELECT"];
		resolve_project_list( &(*project_lists)["children"] );
    if(NULL != from_list){
    		resolve_from_list ( &(*from_list)["children"] );
    			if( NULL != where_list )resolve_where_list( where_list , where_list );
    }
    
      if( group_list && group_list->HasMember("children") ) resolve_goupby_list( &(*group_list)["children"] );
 		 // having 处理 having_list 处理
 		  if( having_list ) resolve_where_list( having_list , having_list );
 		 // order 处理 orderby_list 处理
 		  if( order_list  )	resolve_orderby_list( order_list );
 		  
 	//  CPP_DEBUG<<"<< 1 >>"<<endl;
  //  for(auto &a : aggregat_funs ){
  //  	rapidjson_log( a );
  //  }
  //  
  //  CPP_DEBUG<<"<< 2 >>"<<endl;
  //   for(auto &a : raw_target_list ){
  //  	cout<<a.relation_name<<" "<<a.column_name<<" "<<a.project_alias<<endl;
  //  }
  //  
  //  CPP_DEBUG<<"<< 3 >>"<<endl;
  //   for(auto &a : project_opers ){
  //  	rapidjson_log( a );
  //  }
  //  
  //  CPP_DEBUG<<"<< 4 >>"<<endl;
  //  for(auto &a : nomal_funs ){
  //  	rapidjson_log( a );
  //  }
}

};

#endif
