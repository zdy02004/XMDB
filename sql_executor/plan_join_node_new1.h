/*
g++ -C -std=c++11 plan_join_node2.h -w

*/
#ifndef PLAN_JOIN_NODE
#define PLAN_JOIN_NODE

#include "plan_node.h"
#include "../util/cpp17_detail.hpp"

#include <functional>
#include <memory>


#define PLAN_TYPE_DO_JOIN										20
#define PLAN_TYPE_DO_SEMI_JOIN							21
#define PLAN_TYPE_DO_ANTI_JOIN							22

typedef std::list<generic_result> join_ret_type;

// 内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
//shared_ptr<std::list<generic_result> >
int
ret_hash_inner_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2,join_ret_type * ret)
{
//typedef typename cpp17_detail::invoke_result<fun_type1, typename T1::value_type >::type  key_type1; 
//typedef typename cpp17_detail::invoke_result<fun_type2, typename T2::value_type >::type  key_type2; 
	
typedef compare_field  key_type1; 
typedef compare_field  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;

        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
//shared_ptr<ret_type     >  ret (make_shared<ret_type>());

//ret->reserve(1.6*container1.size());
DEBUG("ret_hash_inner_join_ctl::make hash cache! \n");

for(typename T1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}
DEBUG("ret_hash_inner_join_ctl::join logical() ! \n");

for(typename T2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
   			//auto row = make_pair((*it2), (*it) );
  
  generic_result return_record;
  return_record.set_row_size( it2->get_row_size() + it->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it2)),it2->get_row_size());
  memcpy(return_record.get_data()+it2->get_row_size(),(char *)(&(*it)),it->get_row_size());
  
  ret->push_back(return_record);
   }
}
  //return ret;
  return 0;

}


// 半内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
//shared_ptr<std::list<generic_result> >
int
ret_hash_inner_semi_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2,join_ret_type * ret)
{
//typedef typename cpp17_detail::invoke_result<fun_type1, typename T1::value_type >::type  key_type1; 
//typedef typename cpp17_detail::invoke_result<fun_type2, typename T2::value_type >::type  key_type2; 
typedef compare_field  key_type1; 
typedef compare_field  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;
typedef std::unordered_map<key_type2,std::vector<typename T2::value_type> > hash_map_type2;
//typedef std::list<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

//shared_ptr<ret_type     >  ret (make_shared<ret_type>());

//ret->reserve(1*container1.size());

for(typename T1::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
	 key_type1 key = key_fun1(*it);
   (*hash_container)[key].emplace_back(*it);
}

for(typename T2::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
	 if((*hash_container2)[key].empty())
	 {
	 (*hash_container2)[key].emplace_back(*it);
	 for(auto it2 = (*hash_container)[key].begin();it2!=(*hash_container)[key].end();++it2) 
   {
   			//auto row = make_pair((*it2), (*it) );
  
  generic_result return_record;
  return_record.set_row_size( it2->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it2)),it2->get_row_size()); 
  ret->push_back(return_record);
   }
 }
}
  //return ret;
return 0;
}
// 反内关联函数
template<class T1,class T2,typename fun_type1,typename fun_type2>
//shared_ptr<std::list<generic_result> >
int
ret_hash_inner_anti_join_ctl(const T1 & container1,const T2 &container2,fun_type1 key_fun1,fun_type2 key_fun2,join_ret_type * ret)
{
//typedef typename cpp17_detail::invoke_result<fun_type1,typename T1::value_type >::type  key_type1; 
//typedef typename cpp17_detail::invoke_result<fun_type2,typename T2::value_type >::type  key_type2; 
typedef compare_field  key_type1; 
typedef compare_field  key_type2; 
typedef std::unordered_map<key_type1,std::vector<typename T1::value_type> > hash_map_type;
typedef std::unordered_map<key_type2,std::vector<typename T2::value_type> > hash_map_type2;
//typedef std::list<generic_result> ret_type;
        
shared_ptr<hash_map_type>  hash_container (make_shared<hash_map_type>());
shared_ptr<hash_map_type>  hash_container2 (make_shared<hash_map_type2>());

//shared_ptr<ret_type     >  ret (make_shared<ret_type>());

//ret->reserve(1*container1.size());

for(typename T1::const_iterator	it = container2.begin();it!=container2.end();++it) 
{
	 key_type2 key = key_fun2(*it);
   (*hash_container2)[key].emplace_back(*it);
}

for(typename T2::const_iterator	it = container1.begin();it!=container1.end();++it) 
{
key_type1 key = key_fun1(*it);
if((*hash_container2)[key].empty())
{ 
  generic_result return_record;
  return_record.set_row_size( it->get_row_size() );
  return_record.allocate();
  memcpy(return_record.get_data(),(char *)(&(*it)),it->get_row_size());
  ret->push_back(return_record);
}

}
 // return ret;
 return 0;

}

struct do_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;
record_meta *meta1;
record_meta *meta2;
record_meta out_meta;

record_tuple record_tuple1;
record_tuple record_tuple2;
std::list<generic_result>*  ret_list1 ;
std::list<generic_result>*  ret_list2 ;


field_t field1;
field_t field2;
int is_first;
//shared_ptr<std::list<generic_result> > ret_list;
std::list<generic_result>  ret_list;



// 为了防止循环编译依赖，暂时加的模板
do_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							record_meta *_meta1,
              record_meta *_meta2,
							std::list<generic_result> * _ret_list1,
							std::list<generic_result> * _ret_list2,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		meta1				(_meta1),
		meta2				(_meta2),
		out_meta    (*_meta1),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
record_tuple1.meta = meta1;
record_tuple2.meta = meta2;
out_meta.append_by_meta(*meta2); 
}
	
virtual int execute( unsigned long long  trans_no  )
{
DEBUG("do_join_node::execute(%d) --------------{ \n",trans_no);
char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

  int ret =ret_hash_inner_join_ctl(*ret_list1,*ret_list2,
	[&](const generic_result& x) {	
	     record_tuple1.result = const_cast<generic_result *>(&x);
		   char * addr = NULL;
		   record_tuple1.get_field(mem_table1 ,column_name1,&addr);	
		   memcpy(buf1,addr,field1.field_size);	   
	     return compare_field( buf1 , field1 , field1.field_size );

	},
	[&](const generic_result& x) {
       record_tuple2.result = const_cast<generic_result *>(&x);
 		   char * addr = NULL;
		   record_tuple2.get_field(mem_table2 ,column_name2,&addr);	
		   memcpy(buf2,addr,field2.field_size);	   
	     return compare_field( buf2 , field2 , field2.field_size );
	},
	&ret_list
	);
	
	
	DEBUG("do_join_node::execute(%d) --------------}\n",trans_no);
 return ret;


}

virtual std::list<generic_result>* get_ret_list()
{
	//return ret_list.get();
	return &ret_list;

}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};



struct do_semi_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;
record_meta *meta1;
record_meta *meta2;
record_meta out_meta;

record_tuple record_tuple1;
record_tuple record_tuple2;
std::list<generic_result> * ret_list1 ;
std::list<generic_result> * ret_list2 ;

field_t field1;
field_t field2;
int is_first;
//shared_ptr<std::list<generic_result> > ret_list;
std::list<generic_result>  ret_list;

// 为了防止循环编译依赖，暂时加的模板
do_semi_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							record_meta *_meta1,
              record_meta *_meta2,
							std::list<generic_result> * _ret_list1,
							std::list<generic_result> * _ret_list2,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		meta1				(_meta1),
		meta2				(_meta2),
		out_meta    (*_meta1),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_SEMI_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
record_tuple1.meta = meta1;
record_tuple2.meta = meta2;
//out_meta.append_by_meta(*meta2); // semi_join 和 meta1 相同

}
	
virtual int execute( unsigned long long  trans_no  )
{

char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

  int ret =ret_hash_inner_join_ctl(*ret_list1,*ret_list2,
	[&](const generic_result& x) {	
	     record_tuple1.result = const_cast<generic_result *>(&x);
		   char * addr = NULL;
		   record_tuple1.get_field(mem_table1 ,column_name1,&addr);	
		   memcpy(buf1,addr,field1.field_size);	   
	     return compare_field( buf1 , field1 , field1.field_size );

	},
	[&](const generic_result& x) {
	     record_tuple2.result = const_cast<generic_result *>(&x);
		   char * addr = NULL;
		   record_tuple2.get_field(mem_table2 ,column_name2,&addr);	
		   memcpy(buf2,addr,field2.field_size);	   
	     return compare_field( buf2 , field2 , field2.field_size );
	},
	&ret_list
	 );
 return ret;
}

virtual std::list<generic_result>* get_ret_list()
{
	//return ret_list.get();
	return &ret_list;

}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};


struct do_anti_join_node:public plan_node
{
	
std::string table_name1; 
std::string table_name2;
std::string column_name1;
std::string column_name2;
mem_table_t *mem_table1 ;
mem_table_t *mem_table2 ;
record_meta *meta1;
record_meta *meta2;
record_meta out_meta;

record_tuple record_tuple1;
record_tuple record_tuple2;
std::list<generic_result> * ret_list1 ;
std::list<generic_result> * ret_list2 ;

field_t field1;
field_t field2;
int is_first;
//shared_ptr<std::list<generic_result> > ret_list;
std::list<generic_result>  ret_list;

// 为了防止循环编译依赖，暂时加的模板
do_anti_join_node( std::string &_table_name1 ,
							std::string &_table_name2 ,
							std::string &_column_name1,
							std::string &_column_name2,
							mem_table_t *_mem_table1  ,
							mem_table_t *_mem_table2  ,
							record_meta *_meta1,
              record_meta *_meta2,
							std::list<generic_result> * _ret_list1,
							std::list<generic_result> * _ret_list2,
							rapidjson::Value& _json,
  						rapidjson::Document * _Doc,
  						int _is_first
  									
):plan_node(_json,_Doc),	
		//table_name1(join_eq_condition_origin.relation_name[0]),
		//table_name2(join_eq_condition_origin.relation_name[1]),
		//column_name1(join_eq_condition_origin.column_name[0]),
		//column_name2(join_eq_condition_origin.column_name[1]),
		//mem_table1(join_eq_condition_origin.mem_table[0]),
		//mem_table2(join_eq_condition_origin.mem_table[1]),
		//ret_list1(table_ret_map[table_name1]),
		//ret_list2(table_ret_map[table_name2]),
		table_name1 (_table_name1), 
		table_name2 (_table_name2),
		column_name1(_column_name1),
		column_name2(_column_name2),
		mem_table1  (_mem_table1),
		mem_table2  (_mem_table2),
		meta1				(_meta1),
		meta2				(_meta2),
		out_meta    (*_meta1),
		ret_list1(_ret_list1),
		ret_list2(_ret_list2),
		is_first(_is_first)
{
plan_type = PLAN_TYPE_DO_ANTI_JOIN;		
get_field(mem_table1 ,column_name1, field1);
get_field(mem_table2 ,column_name2, field2);
record_tuple1.meta = meta1;
record_tuple2.meta = meta2;
//out_meta.append_by_meta(*meta2); // anti_join 和 meta1 相同

}
	
virtual int execute( unsigned long long  trans_no  )
{

char buf1[field1.field_size+1];
buf1[field1.field_size+1];	
buf1[field1.field_size]='\0';

char buf2[field2.field_size+1];	
buf2[field2.field_size+1];	
buf2[field2.field_size]='\0';	

int field1_type = field1.field_type;
int field2_type = field2.field_type;

int ret =ret_hash_inner_join_ctl(*ret_list1,*ret_list2,
	[&](const generic_result& x) {	
	     record_tuple1.result = const_cast<generic_result *>(&x);
		   char * addr = NULL;
		   record_tuple1.get_field(mem_table1 ,column_name1,&addr);	
		   memcpy(buf1,addr,field1.field_size);	   
	     return compare_field( buf1 , field1 , field1.field_size );

	},
	[&](const generic_result& x) {
	     record_tuple2.result = const_cast<generic_result *>(&x);
	     char * addr = NULL;
		   record_tuple2.get_field(mem_table2 ,column_name2,&addr);	
		   memcpy(buf2,addr,field2.field_size);	   
	     return compare_field( buf2 , field2 , field2.field_size );
	},
	&ret_list
	);
 return 0;
}

virtual std::list<generic_result>* get_ret_list()
{
	//return ret_list.get();
	return &ret_list;
}

virtual void make_json()
{
	return ;
}

virtual std::string to_sring()
{
	//return 0;
}


};








#endif 