#define cast_marco_FIELD_TYPE_INT			( __ptr )  (FIELD_INT   *		)(__ptr)
#define cast_marco_FIELD_TYPE_SHORT		( __ptr )  (FIELD_SHORT *		)(__ptr)
#define cast_marco_FIELD_TYPE_LONG		( __ptr )  (FIELD_LONG  *		)(__ptr)
#define cast_marco_FIELD_TYPE_LONGLONG( __ptr )  (FIELD_LONGLONG *)(__ptr)
#define cast_marco_FIELD_TYPE_FLOAT		( __ptr )  (FIELD_FLOAT 	 *)(__ptr)
#define cast_marco_FIELD_TYPE_DOUBLE	( __ptr )  (FIELD_DOUBLE 	 *)(__ptr)
#define cast_marco_FIELD_TYPE_DATE		( __ptr )  (FIELD_DATE 		 *)(__ptr)
#define cast_marco_FIELD_TYPE_STR			( __ptr )  (char  				 *)(__ptr)

#define cast_marco( n, __ptr ) \
n == FIELD_TYPE_INT			 ? cast_marco_FIELD_TYPE_INT(__ptr)			:  \
n == FIELD_TYPE_SHORT 	 ? cast_marco_FIELD_TYPE_SHORT(__ptr) 	:  \
n == FIELD_TYPE_LONG		 ? cast_marco_FIELD_TYPE_LONG(__ptr)		:  \
n == FIELD_TYPE_LONGLONG ? cast_marco_FIELD_TYPE_LONGLONG(__ptr):  \
n == FIELD_TYPE_FLOAT		 ? cast_marco_FIELD_TYPE_FLOAT(__ptr)		:  \
n == FIELD_TYPE_DOUBLE	 ? cast_marco_FIELD_TYPE_DOUBLE(__ptr)	:  \
n == FIELD_TYPE_DATE		 ? cast_marco_FIELD_TYPE_DATE(__ptr)		:  \
n == FIELD_TYPE_STR			 ? cast_marco_FIELD_TYPE_STR(__ptr);


#define define_marco_FIELD_TYPE_INT	(__ptr)		   FIELD_INT   __ptr 
#define define_marco_FIELD_TYPE_SHORT	(__ptr)	   FIELD_SHORT __ptr
#define define_marco_FIELD_TYPE_LONG(__ptr)		   FIELD_LONG  __ptr
#define define_marco_FIELD_TYPE_LONGLONG(__ptr)  FIELD_LONGLONG __ptr
#define define_marco_FIELD_TYPE_FLOAT(__ptr)		 FIELD_FLOAT 	  __ptr 
#define define_marco_FIELD_TYPE_DOUBLE(__ptr)	   FIELD_DOUBLE 	__ptr
#define define_marco_FIELD_TYPE_DATE(__ptr)		   FIELD_DATE 		__ptr
#define define_marco_FIELD_TYPE_STR	(__ptr)		   (char *)       __ptr

#define define_marco( n,__ptr ) \
n == FIELD_TYPE_INT			 ? define_marco_FIELD_TYPE_INT(__ptr)			:  \
n == FIELD_TYPE_SHORT 	 ? define_marco_FIELD_TYPE_SHORT(__ptr) 	:  \
n == FIELD_TYPE_LONG		 ? define_marco_FIELD_TYPE_LONG(__ptr)		:  \
n == FIELD_TYPE_LONGLONG ? define_marco_FIELD_TYPE_LONGLONG(__ptr):  \
n == FIELD_TYPE_FLOAT		 ? define_marco_FIELD_TYPE_FLOAT(__ptr)		:  \
n == FIELD_TYPE_DOUBLE	 ? define_marco_FIELD_TYPE_DOUBLE(__ptr)	:  \
n == FIELD_TYPE_DATE		 ? define_marco_FIELD_TYPE_DATE(__ptr)		:  \
n == FIELD_TYPE_STR			 ? define_marco_FIELD_TYPE_STR(__ptr);


struct row_mapper
{
	rapidjson::Value  * v;
	size_t size;
	record_meta                 meta;
	record_tuple               *Tuple_output; //输出集
	record_tuple               *Tuple_input;  //输入集
	row_mapper 								 *next;
  int 											 tag;	
  
	inline void set_tag(int _tag){tag = _tag;}
	inline void flush_tuple(){ Tuple_output->meta = &meta; }
	inline void set_input_tuple (record_tuple *Tuple_output_){ Tuple_output = Tuple_output_; }
	inline void set_output_tuple(record_tuple *Tuple_input_){ Tuple_input = Tuple_input_;flush_tuple(); }
	inline row_mapper& set_size(size_t _size){ size = _size;return *this;	}
	inline void set_next(row_mapper *_next){next =_next;}
	
	virtual void mapper() = 0;
	virtual int push_field(mem_table_t *_mem_table ,std::string _field_name,std::string _alias_name) = 0;
};

//直接映射
struct raw_row_mapper:public row_mapper
{
	mem_table_t * 							mem_table ;   //表名
	std::string  							  field_name;		//字段名
	std::string 								alias_name;		//别名
	
	virtual int push_field(mem_table_t *_mem_table ,std::string _field_name,std::string _alias_name) 
	{
		mem_table = _memtab;
		field_name = _field_name;
		alias_name = _alias_name;
		
		return row_mapper::meta.push_field(mem_table,field_name,_alias_name);
	}
		
	virtual void mapper() 
	{
		char * target = NULL;
		row_mapper::Tuple_input->get_field(mem_table , field_name, &target);
		row_mapper::Tuple_output->set_field(mem_table , alias_name, target);
		if( NULL != next )return next->mapper();
	}

};

int get_endian()
{
    union {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;
        if(un.c[0]==1 && un.c[1] == 2)
            return 1;//big-endian
        else if (un.c[0] == 2 && un.c[1] == 1)
           return 0;//little-endian
        else
            return -1;
   
}

//普通函数
struct nomalfuns_row_mapper:public row_mapper
{
/* 1. arithmetic operators */
};

//两个都是字段的操作
struct opers_row_mapper:public row_mapper
{

	mem_table_t * 						 mem_table1;
	mem_table_t * 						 mem_table2;
	std::string								 field_name1;
	std::string								 field_name2;
	std::string  						   alias_name;
			
	virtual int push_field(mem_table_t * _memtab1,std::string&_field_name1,
												 mem_table_t * _memtab2,std::string&_field_name2,std::string _alias_name
											  ) 
	{
	  mem_table1 = _memtab1; 
	  mem_table2 = _memtab2;
		field_name1 = _field_name1;
		field_name2 = _field_name2;
		alias_name =  _alias_name;
		switch(tag)
		{
			case T_OP_ADD :{
				if( alias_name.empty() )alias_name = field_name1+"+"+field_name2;
				break;
				}
			case T_OP_MINUS :{
				if( alias_name.empty() )alias_name = field_name1+"-"+field_name2;
				break;
				}
			case T_OP_MUL :{
				if( alias_name.empty() )alias_name = field_name1+"*"+field_name2;
				break;
				}
			case T_OP_DIV :{
				if( alias_name.empty() )alias_name = field_name1+"/"+field_name2;
				break;
				}		
			}  
		return row_mapper::meta.push_field(mem_table1,field_name1,alias_name);
	}

	 		
	virtual void mapper() 
	{	
		char * target = NULL;
		char * target2 = NULL;
		field_t field1;
		field_t field2;
		get_field( mem_table1 , field_name1, &field1 ); 
		get_field( mem_table2 , field_name2, &field2 ); 
		record_tuples.get_field( mem_table1 , field_name1, &target ); 
		record_tuples.get_field( mem_table2 , field_name2, &target2);
    long long result;
    
		switch(tag)
		{
			case T_OP_ADD :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) + ( *cast_marco( field2.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );

				break;
				}
			case T_OP_MINUS :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) - ( *cast_marco( field2.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_MUL :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) * ( *cast_marco( field2.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_DIV :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) / ( *cast_marco( field2.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_MOD :
				
		}
		if( NULL != next )return next->mapper();
	}


};

//1个是字段,1个是常数的情况
struct simple_opers_row_mapper:public row_mapper
{
	mem_table_t *              mem_table1;
	std::string								 field_name1;
	std::string								 condition;
	std::string								 alias_name;
	bool											 is_string;

	virtual int push_field(mem_table_t * _mem_table1,std::string&_field_name1,
												 std::string& _condition,std::string _alias_name
											  ) 
	{
	  mem_table1  = _mem_table1; 
		field_name1 = _field_name1;
		alias_name  =  _alias_name;
		condition   = _condition;  
    
		
		
		switch(tag)
		{
			case T_OP_ADD :{
				if( alias_name.empty() )alias_name = field_name1+"+"+condition;
				break;
				}
			case T_OP_MINUS :{
				if( alias_name.empty() )alias_name = field_name1+"-"+condition;
				break;
				}
			case T_OP_MUL :{
				if( alias_name.empty() )alias_name = field_name1+"*"+condition;
				break;
				}
			case T_OP_DIV :{
				if( alias_name.empty() )alias_name = field_name1+"/"+condition;
				break;
				}		
				case T_OP_MOD :{
				if( alias_name.empty() )alias_name = field_name1+"%"+condition;
				break;
				}	
			}  
		return row_mapper::meta.push_field(mem_table1,field_name1,alias_name);
	}

		
	virtual void mapper() 
	{	
		char * target = NULL;
		char * target2 = NULL;
		field_t field1;
		get_field( mem_table1 , field_name1, &field1 ); 
		record_tuples1.get_field( mem_table1 , field_name1, &target ); 
		target2 = &atol( condition.c_str() );

    long long result;
    
		switch(tag)
		{
			case T_OP_NEG :{
				 ( *cast_marco( field1.field_no, &result ) ) =  -( *cast_marco( field1.field_no, target ) ) ;
				row_mapper::Tuple_output->set_field(mem_table1 , alias_name, &result);

				break;
				}
			case T_OP_ADD :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) + ( *cast_marco( field1.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_MINUS :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) - ( *cast_marco( field1.field_no, target2 ) );
				target2 = &atol( condition.c_str() )
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_MUL :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) * ( *cast_marco( field1.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_DIV :{
				 ( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) / ( *cast_marco( field1.field_no, target2 ) );
		    row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
				break;
				}
			case T_OP_MOD :{
				 if( *target2 != 0 ){
				 	( *cast_marco( field1.field_no, &result ) ) =  ( *cast_marco( field1.field_no, target ) ) % ( *cast_marco( field1.field_no, target2 ) );
		      row_mapper::Tuple_output->set_field(mem_table1 , alias_name, (char *)(&result)  );
		    }
				break;
				}
				
		}
		if( NULL != next )return next->mapper();
	}


};


  
//暂时只支持最简单的聚集函数 --聚合参数
//暂时不支持，select 中含有非聚集函数的情况
struct aggregat_row_mapper:public row_mapper
{
	int tag;
	std::list<generic_result> *results;
	long long result;
	mem_table_t *              mem_table1;
	std::string								 field_name1;
	std::string								 alias_name;
	
	void set_result(std::list<generic_result> *_result){results = _result;}
	
	virtual int push_field(mem_table_t * _mem_table1,std::string&_field_name1,
												 std::string _alias_name
											  ) 
	{
	  mem_table1  = _mem_table1; 
		field_name1 = _field_name1;
		alias_name  =  _alias_name;
    result = 0;
		switch(tag)
		{
			case T_FUN_MAX :{
				if( alias_name.empty() )alias_name = "MAX("+field_name1+")";
				break;
				}
			case T_FUN_MIN :{
				if( alias_name.empty() )alias_name = "MIN("+field_name1+")";
				break;
				}
			case T_FUN_SUM :{
				if( alias_name.empty() )alias_name = "SUM("+field_name1+")";
				break;
				}
			case T_FUN_AVG :{
				if( alias_name.empty() )alias_name = "AVG("+field_name1+")";
				break;
				}		
				case T_FUN_COUNT :{
				if( alias_name.empty() )alias_name = "COUNT("+field_name1+")";
				break;
				}	
			}  
			size_t tmp = row_mapper::meta.size;
			int ret =  row_mapper::meta.push_field(mem_table1,field_name1,alias_name);
			row_mapper::meta.size = tmp + sizeof(FIELD_LONGLONG);
			return ret;
	}
		
	virtual void mapper() 
	{	
		char * target;
		char * target2;
		field_t field1;
		get_field( mem_table1 , field_name1, &field1 ); 
		
		switch(tag)
		{
			case T_FUN_MAX :{
				for(std::list<generic_result> ::iterator it = (*results)::begin() ; it !=(*results)::rbegin();++it )
				{
				record_tuple record_tuples;
				record_tuples.meta = &row_mapper::meta;
				record_tuples.result = it->data;
				record_tuples.get_field( mem_table , field_name, &target);
				
				record_tuple record_tuples2;
				record_tuples2.meta = &row_mapper::meta;
				record_tuples2.result = (it+1)->data;
				record_tuples2.get_field( mem_table , field_name, &target2);
				
				( *cast_marco( field1.field_no, &result ) ) = std::max(   ( *cast_marco( field1.field_no, target ) ) , ( *cast_marco( field1.field_no, target2 ) ) );
				}
				break;
			}
			case T_FUN_MIN :{
				for(std::list<generic_result> ::iterator it = (*results)::begin() ; it !=(*results)::rbegin();++it )
				{
				record_tuple record_tuples;
				record_tuples.meta = &row_mapper::meta;
				record_tuples.result = it->data;
				record_tuples.get_field( mem_table , field_name, &target);
				
				record_tuple record_tuples2;
				record_tuples2.meta = &row_mapper::meta;
				record_tuples2.result = (it+1)->data;
				record_tuples2.get_field( mem_table , field_name, &target2);
				
				( *cast_marco( field1.field_no, &result ) ) = std::min(   ( *cast_marco( field1.field_no, target ) ) , ( *cast_marco( field1.field_no, target2 ) ) );
				}
				break;
			}
			case T_FUN_SUM :{
				for(std::list<generic_result> ::iterator it = (*results)::begin() ; it !=(*results)::end();++it )
				{
				record_tuple record_tuples;
				record_tuples.meta = &row_mapper::meta;
				record_tuples.result = it->data;
				record_tuples.get_field( mem_table , field_name, &target);
				
				( *cast_marco( field1.field_no, &result ) ) +=  *cast_marco( field1.field_no, target )  ;
				}
				break;
			}
			case T_FUN_AVG :{
				for(std::list<generic_result> ::iterator it = (*results)::begin() ; it !=(*results)::end();++it )
				{
				record_tuple record_tuples;
				record_tuples.meta =&row_mapper::meta;
				record_tuples.result = it->data;
				record_tuples.get_field( mem_table , field_name, &target);
				
				( *cast_marco( field1.field_no, &result ) ) +=  *cast_marco( field1.field_no, target )  ;
				}
				if(results->size() ! = 0 )result /= results->size();
				else result = 0;
				break;
			}
			case T_FUN_COUNT :{
				result = results->size();
				break;
			}
		}
		
	}
	if( NULL != next )return next->mapper();

};

int handl_row_target( std::list<plan_node *>	& plan_node_list )
{
	std::vector<std::string>	table_names; 
	std::vector<std::string>	column_names; 
	std::vector<mem_table_t *>	mem_tables; 
	std::vector<std::string>	alias_names;
	//std::map<std::string, off_t>table_name_dis;
	std::list<generic_result>*  input ;	

	// 对齐别名和真实表名
    for(auto &v :raw_target_list){
			auto s  = std::find_if(tables.begin(),tables.end(),[&](TableItem& s){return v.relation_name == s.alias_name_;});
	   	if( tables.end() != s )
	   	{
				v.relation_name == s->table_name_;
				v.alias_name 	== s->alias_name_;			
	   	}

	//填充入参
	  table_names .push_back(v.relation_name);
		column_names.push_back(v.column_name  );
		alias_names .push_back(v.alias_name   );
		mem_tables	.push_back( std::find_if(tables.begin(),tables.end(),[&](TableItem& s){return v.relation_name == s.table_name_;})->mem_table);
	   
    }
	
	
gat_last_meta;
for(auto &v : raw_target_list)
	{
		
		
		
		meta.put_field(mem_table_t *_mem_table ,v.column_name );
		
		
	}

return 0;
}


 int make_row_mapper_help( row_mapper* pre ,rapidjson::Value  * v,std::list<generic_result> *result,rapidjson::Value **out  ){
 	  rapidjson::Value  * vv ;
		if ( v->HasMember("PROJECT") )
			vv = &(*v)["PROJECT"];
		else vv = v;
			
		//中间结果的元数据描述
		record_meta  meta;
		int err =  0;
		
		//从group by 获得源 meta
		if( !group_target.empty() ){meta = *groupby_result_meta;}
		//从 join 获得源 meta
	  else if(is_join){	err = get_record_meta_from_join(join_eq_condition_only_inner_join_list, meta); }
		//从原始表 获得源 meta
		else err = meta.from_table( tables.begin()->mem_table );	
		
		//1. 聚合运算，需要修改
		if ( vv->HasMember(rapidjson::StringRef("FUN_TYPE") )   ) {
				if (check_if_aggregation_fun( (*vv)["tag"].GetInt()) ) {	
					CPP_DEBUG<< "聚合函数 in"  <<endl;
					//聚合函数	
				 //projection
				  std::string  relation_name;
				  mem_table_t* local_mem_table;
				  std::string  column_name;
				  std::string  alias_name;

					for (auto& children : (*vv)["children"].GetArray()) 
					{
						if( children.HasMember("RELATION_NAME") ){
							relation_name =children["RELATION_NAME"]["str_value_"].GetString();
							auto s  = std::find_if(tables.begin(),tables.end(),[&](TableItem& s){return relation_name == s.alias_name_;});
	   						if( tables.end() != s )
	   						{
									relation_name  = s->table_name_;
									local_mem_tables  =s->mem_table;
	   						}
						}
						
						if( children.HasMember("COLUMN_NAME"  ) )column_name = children["COLUMN_NAME"]["str_value_"].GetString();
						if( children.HasMember("RELATION_ALIAS"))alias_name = children["RELATION_ALIAS"]["str_value_"].GetString();

					}	
					
				aggregat_row_mapper* node = new  aggregat_row_mapper;
				node->set_tag( (*vv)["tag"].GetInt()) );
				node->set_meta(meta_meta);
				node->set_size(meta.size);
				node->set_result(result);
				node->push_field(local_mem_table,column_name,alias_name);
				pre->set_next(node);
				}
				else {
					//普通函数函数	
				node->set_tag( (*vv)["tag"].GetInt()) );
				node->set_meta(meta_meta);
				node->set_size(meta.size);
				}
			return;
		}
			//2. 目标上的运算	
			//2.1 字段之间的 + - * / 运算
			//2.2 字段与常数之间的 + - * / 运算
			if ( vv->HasMember("OP_TYPE")   ) {
		
			if( vv->HasMember("children") )
			{   
				  //projection
				  std::string  relation_name[2];
				  mem_table_t* local_mem_tables[2];
				  std::string  column_name[2];
				  std::string  alias_name[2];
					//条件
				  std::string condition_string;
				  std::string const_type;
				  
				  int i = 0;
				  int j = 0;
				  int k = 0;
					for (auto& children : (*vv)["children"].GetArray()) 
					{
						if( children.HasMember("RELATION_NAME") ){
							relation_name[i++]=children["RELATION_NAME"]["str_value_"].GetString();
							auto s  = std::find_if(tables.begin(),tables.end(),[&](TableItem& s){return relation_name[i] == s.alias_name_;});
	   						if( tables.end() != s )
	   						{
									relation_name[i] = s->table_name_;
									local_mem_tables[i] =s->mem_table;
	   						}
	   						++i;
						}
						
						if( children.HasMember("COLUMN_NAME"  ) )column_name[j++]=children["COLUMN_NAME"]["str_value_"].GetString();
						if( children.HasMember("RELATION_ALIAS"))alias_name[k++]=children["RELATION_ALIAS"]["str_value_"].GetString();
						if( children.HasMember("CONST_TYPE"   ) ){
							condition_string=children["str_value_"].GetString();
							const_type=children["CONST_TYPE"].GetString();
						}
					}

					
					// 两个字段的情况
					if( 2 =i )
						{
							opers_row_mapper* orm = new opers_row_mapper;
							orm->set_tag((*vv)["tag"].GetInt());
							orm->meta = meta;
							// orm->set_input_tuple();
							orm->push_field( local_mem_tables[0],column_name[0],
												  		 local_mem_tables[1],column_name[1],alias_name[0]);
							pre->set_next(orm);
							*out = orm;
						}
					// 1个是字段，1个是常量的情况
					if( 1 =i )
						{
							simple_opers_row_mapper * sorm = new simple_opers_row_mapper;
							sorm->set_tag((*vv)["tag"].GetInt());
							sorm->meta = meta;
							// orm->set_input_tuple();
							sorm->push_field(local_mem_tables[0],column_name[0],condition_string,alias_name[0] ); 
							pre->set_next(sorm);
							*out = sorm;
						}
			}

			return;
		}

			//3. 原始目标上的提取
			if ( (*vv)["tag"] == T_OP_NAME_FIELD  ){
			if( vv->HasMember("children") )
			{   
				  //projection
				  std::string  relation_name;
				  mem_table_t* local_mem_table;
				  std::string  column_name;
				  std::string  alias_name;

					for (auto& children : (*vv)["children"].GetArray()) 
					{
						if( children.HasMember("RELATION_NAME") ){
							relation_name =children["RELATION_NAME"]["str_value_"].GetString();
							auto s  = std::find_if(tables.begin(),tables.end(),[&](TableItem& s){return relation_name == s.alias_name_;});
	   						if( tables.end() != s )
	   						{
									relation_name  = s->table_name_;
									local_mem_tables  =s->mem_table;
	   						}
						}
						
						if( children.HasMember("COLUMN_NAME"  ) )column_name = children["COLUMN_NAME"]["str_value_"].GetString();
						if( children.HasMember("RELATION_ALIAS"))alias_name = children["RELATION_ALIAS"]["str_value_"].GetString();

					}
			}	
				
			raw_row_mapper * rrm = new raw_row_mapper;
			rrm->meta = meta;
			rrm->push_field(local_mem_table ,column_name,alias_name) ;
			pre->set_next(rrm);
			*out = rrm;
			return;
			}
		  
		  if ( (*vv)["tag"] == T_STAR  ){	
			return;
		  }			
}