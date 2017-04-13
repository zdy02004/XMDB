#include "parser.hh"
#include "query_analyser.hpp"

int main()
{

const char *sql_str = ""
   // "select distinct qty as quantity, user_name, qty / 100, id + 1000 as new_id, new_id as n_id "
   // "from (select * from table_1 where condition > 1) table1_alias, table_2  "
   // "where table_1.user_id = table_2.user_id and table_1.user_id = 12 and table_2.acct_id = 23 group by table_1.c having table_1.c = 1 ORDER BY table_2.c";
    " select sum(o.c1) t1,o.c2 + 4 t2,o.c3 t3   "
     " from  table_name table1 join table_name2  table2 on a.k = b.u "
     " where o.c3 = table2.k1  and table2.k1 = 1 and not 1 "
     " and c3 between 1 and 2 ";

cout<< sql_str <<endl;

ParseResult result;
 int ret = parse_init(&result);
  parse_sql(&result, sql_str, strlen(sql_str));
  //ASSERT_NE(result.result_tree_, (ParseNode*)NULL);

   
    rapidjson::StringBuffer buffer;
    //rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    	
    	
    result.Doc.Accept(writer);
    
   // cout<<result.Doc["ROOT"]["tag"].GetInt()<<endl;
  

    std::cout << buffer.GetString() << std::endl;

    for (auto& v : result.Doc["ROOT"]["children"].GetArray() ){
   QueryAnalyser qa( v ,result.Doc );
  }	
  
  rapidjson_log( &result.Doc["ROOT"] );
parse_terminate(&result);
return 0;
}
