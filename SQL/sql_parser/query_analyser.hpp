#ifndef QYAN_TAB_HPP  
#define QYAN_TAB_HPP  
#include "parser.hh"
#include<vector>


void rapidjson_log(rapidjson::Value  * v)
	{
		 rapidjson::StringBuffer buffer;
     rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		 rapidjson::Document    Doc; 
		 Doc.SetObject().AddMember("LOG",*v, Doc.GetAllocator() );
		 
		
		 Doc.Accept(writer);
		 
		  std::cout << buffer.GetString() << std::endl;
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
    TableItem(string & table_name , string & alias_name ):table_name_(table_name),alias_name_(alias_name){}
};  


#define check_and_assign_member( target, _member ) \
if(  root->HasMember( _member ) )					 \
		{                                                 		\
			(target) = &( (*root)[ _member ] );			\
		}																						\
		else cout<<"do not have "<<_member<<endl;



class QueryAnalyser
{
rapidjson::Value    *root;
rapidjson::Document *doc;

int is_distinct;
int is_join;
int sub_links_count;
// 原始要素
rapidjson::Value  * project_lists;
rapidjson::Value  * from_list;
rapidjson::Value  * where_list;
rapidjson::Value  * group_list;
rapidjson::Value  * having_list;
rapidjson::Value  * order_list;
rapidjson::Value  * hints_list;



//初步识别出的要素
vector<rapidjson::Value *> sub_querys;  // from  中的子查询
						
vector<TableItem>     tables;				 					// 解析后的表
vector<QueryAnalyser> sub_links; 	   					// where 中的子链接
rapidjson::Value  *   up_where_list; 					//如果是子连接 则还要存一个上层 where
vector<rapidjson::Value *> join_conditions;   // 关联条件

vector<rapidjson::Value *> const_conditions;         	// 常数不可再分条件
vector<rapidjson::Value *> nomal_single_conditions;  	// 单操作数不可再分条件
vector<rapidjson::Value *> nomal_double_conditions;  	// 双操作数不可再分条件
vector<rapidjson::Value *> complex_double_conditions; // 可再分双操作数条件
vector<rapidjson::Value *> nomal_btw_conditions;      // between and 
private:

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
    
        // 是否是关联连接 
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
    	if( ( tag >= T_FUN_MAX  && tag == T_FUN_AVG ) )
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
QueryAnalyser(rapidjson::Value & value ,rapidjson::Document & doc_ , rapidjson::Value * up_where_list_ = NULL ):root( &( value ) ) ,
																																		doc( &doc_ ),
																																		project_lists(NULL),
																																		from_list		 (NULL),
																																		where_list	 (NULL),
																																		up_where_list (up_where_list_),
																																		group_list	(NULL),
																																		having_list (NULL),
																																		order_list	(NULL),
																																		hints_list	(NULL),
																																		sub_links_count ( 0 )
{
select_prepared();
}

void resolve_from_list_help( rapidjson::Value  * v,int level = 0 ){
	        //rapidjson_log(v); cout<<"__________________________"<<endl;
	
					int is_alias = 0;
					int is_obvious_join = 0;

  				if( (*v)["tag"].GetInt() == T_ALIAS )is_alias = 1;
  				if( check_if_obvious_join((*v)["tag"].GetInt()) )is_obvious_join = 1;
  				
  				string table_name;  // 表名
  				string alias_name;  // 表别名
  				
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
  				
  				// 隐式的 内联写法
  				if(is_alias){
  				 table_name=string((*v)["RELATION"]["str_value_"].GetString()); 	// 表名				
  				 alias_name=string((*v)["RELATION_ALIAS"]["str_value_"].GetString()); 					
            
            
            //2. 子查询的情况，子查询无表名
            if( (*v)["RELATION"]["tag"].GetInt() == T_SUB_SELECT ){
            			(*v)["RELATION"].AddMember("DEEP_LEVEL", level+1, doc->GetAllocator());
            			//sub_querys.emplace_back(&(v) );
  								// 递归子查询
  								if( (*v)["SUB_SELECT"].HasMember("FROM_CLAUSE") )resolve_from_list( &((*v)["SUB_SELECT"]["FROM_CLAUSE"]), level+1 );
            	}
      		}	
							 // 插入解析后的表
  			 			 tables.emplace_back( TableItem(table_name,alias_name) );
}

//解析 from_list
void resolve_from_list( rapidjson::Value  * fromlist,int level = 0 ){
  // 初步通过 fromlist 的个数判断是否关联
   if( fromlist->HasMember("children")  &&  (*fromlist)["children"].GetArray().Size() != 1 )is_join = 1 ;else is_join = 0;
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
			
			//1. 子连接,语法分析阶段已经打过标签了
			if ( v->HasMember("SUB_LINK_TYPE") ) {
					 // 记录 子连接的个数
					 ++sub_links_count;
					// 递归处理 子连接
					 sub_links.emplace_back( (*v)["SUB_LINK_BODY"], *doc , where_list );
  				 return;
			} 
			
			  //2 单操作数条件
			if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 1 ){
				for (auto& vv : (*v)["children"].GetArray()) 
					{
						tmp[i++] = vv["tag"].GetInt() ;
						cout<<vv["tag"].GetInt()<<endl;
					}
						cout<< " Resolve_One_Oper_condition " <<endl;
			  				 		  				 
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
				 	cout<< " Resolve_Two_Oper_condition " <<endl;

				 	// 关联条件
				 	if( check_if_join_condition(tmp[0]) && check_if_join_condition(tmp[1]) && (*v)["tag"].GetInt() == T_OP_EQ ){
						 cout<< "关联条件 " <<endl;
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
				 				cout<< "递归细分 " <<endl;
				 				// 递归细分
				 			   resolve_where_list( &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][0]), &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][0]) );
				 			 	 resolve_where_list( &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][1]), &((*father)["COMPLEX_DOUBLE_CONDITION"]["children"][1]) );

				 				return ;
				 }
				 				 
			}
			
		  // 3. 其他 3操作数条件打标签
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
	  check_and_assign_member(group_list,"group_by");                
	   //检查是否有 having_list                                      
	  check_and_assign_member(having_list,"having_list");            
	  //检查是否有 order_list                                        
	  check_and_assign_member(order_list,"order_by");                


    if(NULL != from_list){
    		resolve_from_list ( from_list );
    			if(NULL != where_list)resolve_where_list(where_list,where_list);
    }
}

};

#endif
