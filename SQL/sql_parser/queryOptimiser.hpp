#ifndef QOPT_TAB_HPP  
#define QOPT_TAB_HPP  
#include "query_analyser.hpp"
#include <functional>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>

class QueryOptimiser : public QueryAnalyser
{

public:
QueryOptimiser(rapidjson::Value & value ,rapidjson::Document & doc_ , QueryAnalyser * up_stmt_ = NULL ):QueryAnalyser(value,doc_,up_stmt_)
{

}

QueryOptimiser(QueryAnalyser &qa ):QueryAnalyser( *(qa.root),*(qa.doc),NULL)
{

}

// 
 void optimiser_template( rapidjson::Value  * vx ,rapidjson::Value  *  father, std::function<void(rapidjson::Value  * vx ,rapidjson::Value  *  father)> func ){
if( vx->IsArray()  ){
			 	printf("vx->IsArray()\n");
  		for (auto& v : (*vx).GetArray()  ){  				
  				optimiser_template( &(v),vx, func);
         }//end for
}
if(vx->IsObject()){

		if( vx->HasMember("COMPLEX_DOUBLE_CONDITION")  ){
			 	printf("COMPLEX_DOUBLE_CONDITION\n");
				optimiser_template( &(*vx)["COMPLEX_DOUBLE_CONDITION"] ,vx,func);
		}
		if( vx->HasMember("NORMAL_DOUBLE_CONDITION")  ){
			 	printf("NORMAL_DOUBLE_CONDITION\n");
				optimiser_template( &(*vx)["NORMAL_DOUBLE_CONDITION"] ,vx,func);
		}
		if( vx->HasMember("NORMAL_SINGLE_CONDITION")  ){
			 	printf("NORMAL_SINGLE_CONDITION\n");
				optimiser_template( &(*vx)["NORMAL_SINGLE_CONDITION"] ,vx,func);
		}
		if( vx->HasMember("JOIN_CONDITION")  ){
			 	printf("JOIN_CONDITION\n");
				optimiser_template( &(*vx)["JOIN_CONDITION"] ,vx,func);
		}
		
		if( vx->HasMember("children")  ){
			 	printf("children\n");
			if( (*vx)["children"].IsArray() ) {
  		for (auto& v : (*vx)["children"].GetArray()  ){ 
  				printf("in children\n"); 				
  				optimiser_template( &(v),vx,func);
         }//end for
    }
		}
		 // 1. 其他 3操作数条件打标签
 if(vx->IsObject()){ 
 		printf("vx->IsObject() 2\n");
    func(vx,father);
    return;
  }
}
}
//将 btw 转化为 and
 void optimiser_btw( rapidjson::Value  * vx ,rapidjson::Value  *  father){

//if( vx->IsArray()  ){
//			 	printf("vx->IsArray()\n");
//  		for (auto& v : (*vx).GetArray()  ){  				
//  				optimiser_btw( &(v),vx);
//         }//end for
//}
//if(vx->IsObject()){
		
 // 1. 其他 3操作数条件打标签
 if ( vx->HasMember("NORMAL_BTW_CONDITION")  ){
 	printf("NORMAL_BTW_CONDITION\n");
 			rapidjson::Value  * v = &(((*vx)["NORMAL_BTW_CONDITION"]));
				int i = 0;
			if ( v->HasMember("children") && (*v)["children"].GetArray().Size()== 3 ){
					
					int tmp[3] = {0};
					for (auto& vv : (*v)["children"].GetArray()) 
						{
							tmp[i++] = vv["tag"].GetInt() ;
							cout<<vv["tag"].GetInt()<<endl;
						}
					if( (*v)["tag"].GetInt() == T_OP_BTW && check_if_const_value(tmp[1])  &&  check_if_const_value(tmp[2]) )
					{
						//rapidjson::Value   father ;
						//father.SetObject().AddMember("tag",T_NORMAL_DOUBLE_CONDITION, doc->GetAllocator() );
						
						rapidjson::Value   obj ;
						obj.SetObject().AddMember("tag",T_OP_GE, doc->GetAllocator() )
						.AddMember( "OP_TYPE","GT",doc->GetAllocator() );
						
						rapidjson::Value   children1 ;
						rapidjson::Value   condition1;
						rapidjson::Value   condition2;
						
						children1.SetArray()
						.PushBack(condition1.CopyFrom((*v)["children"][0],doc->GetAllocator()), doc->GetAllocator() )
						.PushBack(condition2.CopyFrom((*v)["children"][1],doc->GetAllocator()), doc->GetAllocator() );
						obj.AddMember("children",children1, doc->GetAllocator() );
						
						rapidjson::Value   obj2 ;
						obj2.SetObject().AddMember("tag",T_OP_LE, doc->GetAllocator() )
						.AddMember( "OP_TYPE","LT",doc->GetAllocator() );
						
						rapidjson::Value   children2 ;
						rapidjson::Value   condition21;
						rapidjson::Value   condition22;
						
						children2.SetArray()
						.PushBack(condition21.CopyFrom((*v)["children"][0],doc->GetAllocator()), doc->GetAllocator() )
						.PushBack(condition22.CopyFrom((*v)["children"][2],doc->GetAllocator()), doc->GetAllocator() );
						obj2.AddMember("children",children2, doc->GetAllocator() );
						
						rapidjson::Value  * nested = nest_and_condition( obj,obj2,doc->GetAllocator() );

						vx->Swap(*nested);
						
						//std::cout<<"<<nested3>>"<<std::endl;
						//rapidjson_log( v );
							
						//swap_father( nested,v, T_BTW_CONDITION, "NORMAL_BTW_CONDITION"  );
						//nomal_btw_conditions.emplace_back( (&(*father)["NORMAL_BTW_CONDITION"]) );
					}
			}
		}
	
		
}

//将 in 转化为 or
void optimiser_in( rapidjson::Value  * vx ,rapidjson::Value  *  father){
 	
 	  if ( (*vx)["tag"] == T_OP_IN  ){
 	  	 	 
 	  	  rapidjson::Value  * outter;
 	  	  rapidjson::Value  * pre;
 	  	  rapidjson::Value  * after;
 	  	  int size = 0;
 	  	  rapidjson::Value  * con[128];//暂时最多支持128个条件
 	  	  	
 	  	if ( vx->HasMember("children") ){
 	  		outter = 	&((*vx)["children"]);
 	  		pre    =  &(*outter)[0];
 	  		after  =  &(*outter)[1];
 	  	}
 	  	
 	  		if ( after->HasMember("children") ){
 	  			  		
 	  		after=&( (*after)["children"][0] );

 	  		for (auto& v : after->GetArray()  ){  				
  				con[size++] =  &(v);
         }//end for
  	  }
  	  int i = 0;
  	  
  	  rapidjson::Value  * ret = NULL;
  	  rapidjson::Value   tmp ;
  	  for(;i<size;++i){
  	  	rapidjson::Value   obj ;
				obj.SetObject().AddMember("tag",T_OP_EQ, doc->GetAllocator() )
				.AddMember( "OP_TYPE","EQ",doc->GetAllocator() );
				
				rapidjson::Value   children;
				rapidjson::Value   condition1;
				rapidjson::Value   condition2;
							
				children.SetArray()
				.PushBack(condition1.CopyFrom((*pre),doc->GetAllocator()), doc->GetAllocator() )
				.PushBack(condition2.CopyFrom((*after)[i],doc->GetAllocator()), doc->GetAllocator() );
			
				obj.AddMember("children",children, doc->GetAllocator() );
				
				if( 0 == i ){
					tmp = obj;
					ret = &tmp;
				}
				else 
				  ret = nest_or_eq_condition( *ret,obj,doc->GetAllocator() );
  	  }
  	  vx->Swap(*ret);
 	
}

}


void optimiser_not( rapidjson::Value  * vx ,rapidjson::Value  *  father){
 	
 	  if ( (*vx)["tag"] == T_OP_NOT  ){
 	  	 printf(" optimiser_not \n");
 	  	  rapidjson::Value  * outter;
 	  	  rapidjson::Value  * inner;
 	  	  	
 	  	if ( vx->HasMember("children") ){
 	  		outter = 	&((*vx)["children"][0]);
 	  	
 	  		//if ( outter->HasMember("children") ){
 	  			inner = outter;//	&((*outter)["children"]);
 	  			// =  !=
 	  			if(  (*inner)["tag"] == T_OP_EQ  ){
 	  				(*inner)["tag"] = T_OP_NE ;
 	  			}
 	  			
 	  			if(  (*inner)["tag"] == T_OP_NE  ){
 	  				(*inner)["tag"] =  T_OP_EQ;
 	  			}
 	  			// is not is
 	  			if(  (*inner)["tag"] == T_OP_IS  ){
 	  				(*inner)["tag"] =  T_OP_IS_NOT;
 	  			}
 	  			
 	  			if(  (*inner)["tag"] == T_OP_IS_NOT  ){
 	  				(*inner)["tag"] =  T_OP_IS;
 	  			}
 	  			//btw not btw
 	  			if(  (*inner)["tag"] == T_OP_BTW  ){
 	  				(*inner)["tag"] =  T_OP_NOT_BTW;
 	  			}

 	  			if(  (*inner)["tag"] == T_OP_NOT_BTW  ){
 	  				(*inner)["tag"] =  T_OP_BTW;
 	  			}
 	  			//like not like
 	  			if(  (*inner)["tag"] == T_OP_LIKE  ){
 	  				(*inner)["tag"] =  T_OP_NOT_LIKE;
 	  			}
 	  			
 	  			if(  (*inner)["tag"] == T_OP_NOT_LIKE  ){
 	  				(*inner)["tag"] =  T_OP_LIKE;
 	  			}
 	  			// in not in
 	  			if(  (*inner)["tag"] == T_OP_IN  ){
 	  				(*inner)["tag"] =  T_OP_NOT_IN;
 	  			}
 	  			
 	  			if(  (*inner)["tag"] == T_OP_NOT_IN  ){
 	  				(*inner)["tag"] =  T_OP_IN;
 	  			}
 	  					printf("ddddddddd\n");
 	  			if(  (*inner)["tag"] == T_BOOL  ){
 	  				if( (*inner)["value_"].GetInt() == 0 ){
 	  				(*inner)["value_"].SetInt(1);
 	  			}
 	  				else
 	  				{
 	  				(*inner)["value_"].SetInt(0);
 	  			  }
 	  			 
 	  			}
 	  			
 	  			vx->Swap(*inner);
 	  		//}
			
 	  	}

  	  
 	
}

}

void optimiser_const( rapidjson::Value  * vx ,rapidjson::Value  *  father){
	      rapidjson::Value  * outter;
	    	
	    	rapidjson::Value d;
		 	  rapidjson::Value tag;
		 	  tag.SetObject().SetInt(T_BOOL);
		 	  d.SetObject().AddMember( "tag",tag,doc->GetAllocator() );
		 	  
		 	  rapidjson::Value children;
		 	  rapidjson::Value child;
		 	  rapidjson::Value child_tag;
		 	  rapidjson::Value child_val;
		 	  rapidjson::Value CONST_TYPE;
		 	  if ( (*vx)["tag"] == T_CONST_CONDITION  ){
		 	  	 
		 	  	 outter = &( (*vx)["CONST_CONDITION"] );
 
 					 int oper_type = ((*outter)["tag"]).GetInt(); 
 					 
 					 printf("oper_type is %d\n",oper_type);
 					 if(oper_type == T_OP_NOT){
 					 	optimiser_not( outter , outter );
 					 	return;
 					 }
 					 
 					 
		 	  	 rapidjson::Value  * conditions[8];
		 	  	 int i = 0;
 		 	     if ( outter->HasMember("children")  )  {
		 	     				if( (*outter)["children"].IsArray() ) {
  										for (auto& v : (*outter)["children"].GetArray()  ){ 
  												conditions[i++] = &v;
      								   }//end for
      								}
		 	     }
		 	     
		 	     
		 	      rapidjson::Value  * first  = conditions[0] ;
		 	      rapidjson::Value  * second = conditions[1] ;
		 	      	 rapidjson_log( first  );
		 	      	 rapidjson_log( second );
		 	      	
		 	     if( first->HasMember("CONST_TYPE") && second->HasMember("CONST_TYPE") ) 
		 	     {
		 	     		if( (*first)["tag"].GetInt() == 1 && (*second)["tag"].GetInt() == 1 )
		 	     		{
		 	     			  long val1 = atoi((*first )["str_value_"].GetString()  );
		 	     			  long val2 = atoi((*second)["str_value_"].GetString()  );
		 	     			  int ret = 0;
		 	     			   
		 	     				switch(oper_type)
		 	     				{
		 	     					case T_OP_EQ:
		 	     						printf("T_OP_EQ\n");
		 	     						if( val1 == val2 )ret = 1;
		 	     							break;
		 	     					case T_OP_LE:
		 	     						if( val1 <= val2 )ret = 1;
		 	     							break;
		 	     					case T_OP_LT:	
		 	     						if( val1 < val2  )ret = 1;
		 	     							break;
		 	     					case T_OP_GE:	
		 	     						if( val1 >= val2 )ret = 1;
		 	     							break;
		 	     					case T_OP_GT:	
		 	     						if( val1 > val2  )ret = 1;
		 	     							break;
		 	     					case T_OP_NE:	
		 	     						if( val1 != val2 )ret = 1;
		 	     							break;
		 	     					case T_OP_AND:	
		 	     						if( val1 & val2  )ret = val1 & val2;
		 	     							break;
		 	     					case T_OP_OR:	
		 	     						if( val1 | val2  )ret = val1 | val2;
		 	     							break;
		 	     				}
		 	     	// 常量条件	替换为 布尔条件		
		 	     	
		 	     		//(*outter)["tag"].SetInt(T_BOOL);
		 	     		
		 	     		
		 	     		child.SetObject();
		 	     		child_tag.SetObject().SetInt(T_BOOL);
		 	     		if ( ret == 1 )	{child_val.SetObject().SetInt(1);	}
		 	     			else child_val.SetObject().SetInt(0);
		 	     		CONST_TYPE.SetObject().SetString("BOOL");			
		 	     		children.SetArray().PushBack(children, doc->GetAllocator() );
		 	     		
		 	     		printf("here\n");
		 	     		
		 	     		child.AddMember("tag",child_tag,doc->GetAllocator());	
		 	     		child.AddMember("value_",child_val,doc->GetAllocator());	
		 	     		child.AddMember("CONST_TYPE",CONST_TYPE,doc->GetAllocator());		 	     		
		 	     	
		 	  	 //rapidjson::Value  * outter;
		 	  	// outter = 	&((*vx)["children"]);
		 	  	   vx->Swap(child);
		 	  }
		 	}
		}


}


// optimiser project_list 
void optimiser_project_template( rapidjson::Value  * projectlist,int level , std::function<void(rapidjson::Value *  ,int  )> func ){
   //遍历 projectlist 将数据表填入 table_names, 将子查询 填入 sub_querys
   	
  	if( projectlist->IsArray() ) {
  		for (auto& v : ( (*projectlist).GetArray() )  ){  
  			  cout<<"ret01"<<endl;				
  				optimiser_project_template( &(v),level,func);
         }//end for
    }
    else if(NULL != projectlist)func( projectlist ,level );
         
} // end 

 
 void optimiser_project_const( rapidjson::Value  * v,int level = 0 ){ 
 	  rapidjson::Value  * vv ;
		if ( v->HasMember("PROJECT") )
			vv = &(*v)["PROJECT"];
		else vv = v;
			
		cout<<"optimiser_project_const"<<endl;				
	
    rapidjson::Value  *  proj[64];
    int i = 0;
    int j = 0;
    int ret = 0;
    int is_simple = 0;
      
    //      		   
		if ( vv->HasMember(rapidjson::StringRef("OP_TYPE") ) && vv->HasMember("children" ) ) {
				for (auto& it :  (*vv)["children"].GetArray()   ){  				
  				cout<<"optimiser_project_const 2"<<endl;				

  				if(it.HasMember("children")){
  					cout<<"[[[[[]]]]]]"<<endl;
  					rapidjson_log( &it ); 
  					optimiser_project_const( &it , level + 1 );
  				}
  				cout<<"optimiser_project_const 3"<<endl;
  				if( !it.HasMember("CONST_TYPE") /*&& it["CONST_TYPE"].GetString() != "INTNUM"*/ ){
  					continue;
  				}
  				//cout<<it["str_value_"].GetString()<<endl;
  				proj[i++] = &it;
         }//end for

     if( 0 == i ) return;
     if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
     cout<<"optimiser_project_const 4"<<endl;

		 if( vv->HasMember("OP_TYPE") && ((*vv)["tag"]).GetInt() == T_OP_ADD )	{
				  is_simple = 1;
				  for(;j<i;++j){
					if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				 	 ret += atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  }
				}		 		
		if( vv->HasMember("OP_TYPE") &&(*vv)["tag"].GetInt() == T_OP_MINUS )	{
					is_simple = 1;
				  if( 0 == j )
				  	{
				  		if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				  		ret = atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  		++j;
				  	}
				  
				  for(;j<i;++j){
				   if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				 	 ret -= atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  }
				}
				
		if( vv->HasMember("OP_TYPE") &&(*vv)["tag"].GetInt() == T_OP_MUL )	{
 				  is_simple = 1;

			    if( 0 == j ){
			    	if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
			    	ret = atoi( (*vv)["children"][j]["str_value_"].GetString() );
			    	++j;
			    }
				  for(;j<i;++j){
				  	if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				 	 ret *= atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  }
				}
		
		if( vv->HasMember("OP_TYPE") && (*vv)["tag"].GetInt() == T_OP_DIV )	{
			is_simple = 1;
			if( 0 == j ){
				if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				ret = atoi( (*vv)["children"][j]["str_value_"].GetString() );
				++j;
			}
		  for(;j<i;++j){
		  	if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
		 	 ret /= atoi( (*vv)["children"][j]["str_value_"].GetString() );
		  }
		}		
				
		 		
			if( vv->HasMember("FUN_TYPE") && (*vv)["tag"].GetInt() == T_FUN_SUM )	{
				 	is_simple = 1;
				  for(;j<i;++j){
				  	if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				 	 ret += atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  }
				}
			if( vv->HasMember("FUN_TYPE") && (*vv)["tag"].GetInt() == T_FUN_MIN)	{
				  is_simple = 1;
				   for(;j<i;++j){
				   	if( 0 == j ){
				   		if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				   		ret = atoi( (*vv)["children"][j]["str_value_"].GetString() );
				   		++j;
				   	}
				   if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				   ret = std::min( atoi( (*vv)["children"][j]["str_value_"].GetString() ),ret );
				  }
				}
			if( vv->HasMember("FUN_TYPE") && (*vv)["tag"].GetInt() == T_FUN_MAX)	{
					is_simple = 1;
					for(;j<i;++j){
				   	if( 0 == j ){
				   		if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				   		ret = atoi( (*vv)["children"][j]["str_value_"].GetString() );
				   		++j;
				   	}
				   if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				   ret = std::max( atoi( (*vv)["children"][j]["str_value_"].GetString() ),ret );
				  }
				}
				// 暂不支持平均数
			if( (*vv)["tag"].GetInt() == T_FUN_AVG)	{
					for(;j<i;++j){
						if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				 	 ret += atoi( (*vv)["children"][j]["str_value_"].GetString() );
				  }
				  if( !(*vv)["children"][j].HasMember("CONST_TYPE" ) )return;
				  ret /= i;
				}
		
			//if ( vv->HasMember("children") )optimiser_project_const( &(*vv)["children"],level );
			if( is_simple == 1 ){
				 rapidjson::Value   		tag;
				 tag.SetObject().SetInt(1);
				 
				 char sz[16];//字符串
				 sprintf(sz, "%d\0", ret);
				 				
				// string s;
				// s += to_string(ret) ;
				 cout<<" sz= "<< sz <<endl;
				  
				 rapidjson::Value   		str_value_;
				 str_value_.SetObject().SetString( sz,strlen(sz),doc->GetAllocator() );
				 
				 rapidjson::Value   		value_;
				 value_.SetObject().SetInt( strlen(sz) );
				 
				 rapidjson::Value   		CONST_TYPE;
				 CONST_TYPE.SetObject().SetString("INTNUM");
				 
				 rapidjson::Value   		PROJECT;
				 PROJECT.SetObject().AddMember("tag",tag,doc->GetAllocator())
				 .AddMember("str_value_",str_value_,doc->GetAllocator())
				 .AddMember("value_",value_,doc->GetAllocator())
				 .AddMember("CONST_TYPE",CONST_TYPE,doc->GetAllocator());
				 
				 vv->Swap(PROJECT);
			}
			
			return;
		}
}

// 子查询 上拉

// 子查询合并

// 子查询物化


//  like 'abc%'    ==>  trim(3) = abc     ok
//  betweent and   ==>  x >=  and x <=    ok
//  in (x1,x2,x3) ==>  ( x1 or x2 or x3 ) ok
//  not(!=)  ==> = or                     ok
//  or 重写


//  去除多余括号              从解析器来消除
//  常量传递 a = b and b = 5 ==> a = 5 and b =5 暂不打算支持（靠人来消除）
//  消除 常量运算             只支持简单的四则运算
//  常量表达式运算            OK
//  bool表达式化简            暂不打算支持	
//  重复条件消除              暂不打算支持（靠人来消除）
//  having 并入 where         OK


// 选择、投影操作下推 ，（不打算支持 非等 连接和下推）,选择操作扩张（关联）

// 聚合下推



// 物化器的物理查询优化

// 尽量使用 where 上的索引 ，索引可以启发使用 merge join
// ORDER BY 排序消除 排序下推 ， distinct 消除
// order by，group by，distinct，count(*),min,max 中 使用索引

// 数据量较少时 不适用索引
// 索引的泛化，关联表的关联条件是索引的，可以分别进行索引扫描。
};

#endif
