#include "../../SQL/sql_parser/parser.hh"
//#include "../../SQL/sql_parser/query_analyser.hpp"
#include "../../SQL/sql_parser/queryOptimiser.hpp"
#include "../fun_oper.h"
#include "../make_query_plan_node.h"

/*
 
  g++ -g test_make_plan.cpp ../../SQL/sql_parser/*.o  -std=gnu++11 -o main -w  -lpthread 
*/

int main()
{
// distinct
const char *sql_str = ""
   // "select  distinct user_name,  qty  as quantity ,qty / 100, id + 1000 as new_id, 1 + 4 "
   //"from (select * from table_1 where condition > 1) table1_alias  , table_2  "   //sum(c1) t1,o.c2 + 4 t2,o.c3 t3
   //"where table_1.user_id = table_2.user_id and table_1.user_id = 12 and table_2.acct_id = 23 group by table_1.c having table_1.c = 1 ORDER BY table_2.c";
    
  //"select  user_name,  qty  as quantity from (select * from table_2 ) t where t.user_name = 'c' and not t.qty and '1' = '2' ";
  //  "select  user_name,  qty  as quantity from (select * from table_2 ) t where t.user_name = 'c' and not t.qty between 1 and 8 ";
 //  "select  user_name,  qty  as quantity from  table_2 t where t.user_name = 'c' and  t.ff is null and t.ee like '%cc'";
      "select  t.user_name,  qty  as quantity,sum(e+f+1),f*2,t3.user_id + t4.user_id,max(1,2) from  table_2 t,table_3 t3 where t.user_name = t3.user_name group by t3 order by t3";
 //     " and exists (select 1 from table_4 t4 where t3.user_id = t4.user_id)";

    
 //   " select  sum(c1) c1 , 2 - 4 * 3  t2  "
//    " from  table_name table1 where  a = 1 and a = b and not true "; //and ( t2.c = 3 or t2.d = 4 )";,(select k3.t4 from  table_name2  k3 where k3.aa>1 ) t1,(select k5.t5 from  table_name4  t4 where t4.a4>1 ) t4 "
     //" where 4 = 3   and not exists (select 1 from  table_name2 k3 where k3.aa in ( select uu from  table_name3 k4 where k4.aa = 1 ) ) and cc.e = 1";
    // " and c3 between 1 and 2 group by a.cc  , dd.kk having e.re = 1 order by cc.c11,dd.po "; exists ( select 1 from  table_name2 ) and

//"create table test_table ( id INT , name INT ) TABLET_BLOCK_SIZE = 512 , EXTERN_SIZE = 512 ";     
//"create index test_table_inx on  test_table ( id )";
//"create unique index test_table_inx on test_table USING hash ( id ,name )";
//"drop table test_table";
//"insert into test_table values (A,B)";
//"insert into test_table select a from b";
//"delete from  test_table where a = b ";
//"update test_table set k = 1 where a = b ";
//"explain select * from test_table ";
//"show tables ";  IDENTIFIED by test_pwd
//"create user 'test_user' IDENTIFIED by 'test_pwd' ";
//"drop user 'test_user' ";
//"SET PASSWORD FOR 'test_user' = 'test_pwd'";
//"RENAME USER 'test_user' TO 'test_pwd' ";
//"COMMIT";
//"ROLLBACK";
//"KILL 9";
//"GRANT CREATE ON test_table TO 'test_user' ";
//"REVOKE CREATE ON test_table FROM 'test_user' ";
//"Pprepare optimize_tables from \" SELECT A FORM B \" ";
//"SET @@sort_buffer_size = 10000"; //暂不支持
//"ALTER TABLE test_table  RENAME TO relation_factor2 ";



CPP_DEBUG<< sql_str <<endl;

ParseResult result;
 int ret = parse_init(&result);
  parse_sql(&result, sql_str, strlen(sql_str));
  //ASSERT_NE(result.result_tree_, (ParseNode*)NULL);

   
    rapidjson::StringBuffer buffer;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    	
    	
    result.Doc.Accept(writer);
    
 
//构造查询计划
  CPP_DEBUG <<"优化前 json"<< buffer.GetString() << std::endl;

 for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
  		//QueryAnalyser qa( v ,result.Doc );
  		if( v.HasMember("OPERATION_NAME") && v["OPERATION_NAME"] == "SELECT"  ){
  		QueryAnalyser qa( v ,result.Doc );
  		
  		for(auto& name : qa.tables){
  			CPP_DEBUG<<"Names: "<<name.table_name_<<" "<<name.alias_name_<<" "<<name.sub_select_alias_name_<<std::endl;
  			
  		}
  		
  		//上拉子链接
  		  qa.pull_up_sublinks();
  		//上拉子查询
  		  qa.pull_up_subquerys();
  		 CPP_DEBUG<<"Begin Optimiser\n "<<std::endl;

  		//逻辑优化器
  		QueryOptimiser qo (qa);
			
			//上拉子链接
  		  //qo.pull_up_sublinks();
  		//上拉子查询
  		  //qo.pull_up_subquerys();


  		//优化between
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_btw,&qo,std::placeholders::_1,std::placeholders::_2) );
		//优化 in
		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_in,&qo,std::placeholders::_1,std::placeholders::_2) );
  		//优化 not 
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_not,&qo,std::placeholders::_1,std::placeholders::_2) );
		//优化 const 
  		qo.optimiser_template( (qa.where_list) ,(qa.where_list),  std::bind(&QueryOptimiser::optimiser_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
		//优化 const 表达式
  		qo.optimiser_project_template( &(*(qa.project_lists))["children"] , 0 ,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );

		//优化 const 条件
		qo.optimiser_project_template( (qa.where_list) ,0,  std::bind(&QueryOptimiser::optimiser_project_const,&qo,std::placeholders::_1,std::placeholders::_2) );
		
    
    
	 //std::vector<fun_oper *>  projection_fun_oper_lists ;
   //esolve_to_opper_node(   &qa ,  projection_fun_oper_lists	);
		
		physical_query_plan phplan( &qa );
		
		}
  }	
  
  //优化后
  CPP_DEBUG <<"优化后 json\n";
  rapidjson_log( &result.Doc["ROOT"] );
  
   
  
parse_terminate(&result);
return 0;
}
