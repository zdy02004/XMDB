/*
 g++ -C -w -std=c++11 record_tuple.h
*/
#ifndef SQL_FIELD
#define SQL_FIELD

#include "sql_field.h"
#include <unordered_map>
#define RECORD_META_EMPTY_TABLE 77001
#define MEM_TABLE_IS_NULL       77002
#define FIELD_IS_EMPTY          77003
#define TOTAL_NAME_NOT_FOUND    77004
#define SRC_IS_NULL             77005
// �м��������ṹ
// Ԫ��������
// tuple ������

//ͨ�ý���� 
//��Ҫʵ�� allocate  get_date dealloc �ӿ�
//��ʹ�� malloc �������ǻ����߳��� �ڴ��
struct generic_result
{
	char* data;
	size_t row_size;
	bool operator == (const generic_result& other) {
	if( row_size == 0 || other.row_size == 0 )return false;
	else if(row_size != other.row_size )return false;
	else {
		return strncmp(data,other.data,row_size); 
	}

  }
  
	inline int allocate(size_t s){data =(char*)malloc(s);row_size = s; }
	inline int allocate(){data =(char*)malloc(row_size); }
	inline int deallocate(){free(data);}
	inline char * get_data(){return data;};
	inline void set_row_size( size_t s){row_size =s; }
	inline size_t get_row_size()const {return row_size; }
}	;	


// ���ֶ�
struct table_field_t
{
	field_t           field;
	mem_table_t      *mem_table;
	
	size_t size(){ return field.field_size;  }
	
  table_field_t(mem_table_t *_mem_table ,std::string _field_name,int _field_order,off_t _field_dis):mem_table(_mem_table)
  {
  	  int err = 0;
  	  err = get_field(mem_table ,_field_name,field);
  		if( err ){
  			
  			DEBUG("May be _field_name is total name:%s\n",_field_name.c_str() );
  			//std::string total_name(_field_name );

  			auto pos = _field_name.find(".");
  			if (pos!=std::string::npos)
  			{
  			std::string field_name(_field_name.substr(pos+1));
  				
  			CPP_DEBUG<<"May be field_name is "<<field_name<<std::endl; 					
  			err = get_field(mem_table ,field_name,field);
  			if(err)
  				{
  					ERROR("get_field ERR is %d\n",err );
  					return;
  				}
  			}
  		}
  		else DEBUG("field size is %d\n",field.field_size );
  		field.field_order 		= _field_order;   //�ֶ��ڼ�¼���ŵڼ���
  		field.field_dis 			= _field_dis;			//���ֶξ���������ʼ��ַ�ľ���
  }
  
  
  table_field_t(std::string _field_name,int _field_order,off_t _field_dis):mem_table(NULL)
  {
  		strcpy( field.field_name ,_field_name.c_str() );
  		field.field_order 		= _field_order;   //�ֶ��ڼ�¼���ŵڼ���
  		field.field_dis 			= _field_dis;			//���ֶξ���������ʼ��ַ�ľ���
  }
       
};

//�м�����recored ����
struct record_meta
{
	std::vector<table_field_t>  				    table_fields;
	std::unordered_map<std::string,int>			field_index_map; //�����ֶ�����vector������
 	//std::map<std::string,int>			field_index_map; //�����ֶ�����vector������
 	off_t										size;	
	
	record_meta():size(0){}
	
	  //����Ԫ����
  void operator = (const record_meta & other)
  {
  	table_fields = other.table_fields;
  	field_index_map = other.field_index_map;
  	size = other.size;
  }
  
    //�����ֶ�Ԫ��Ϣ
  int push_field(mem_table_t *_mem_table ,std::string _field_name)
  {  
  
  	if( NULL == _mem_table )
  		{
  			ERROR("RECORD_META_EMPTY_TABLE\n");
  			return RECORD_META_EMPTY_TABLE;
  		}
  	DEBUG("push_field2() begin ------- { \n");	
  	std::string total_name 		=  std::string( _mem_table->config.table_name ) + std::string(".")+_field_name;	
  	CPP_DEBUG<<"field_index_map["<< total_name<<"]= "<<table_fields.size()<<std::endl;	
  	field_index_map[total_name] =  table_fields.size() ;
    CPP_DEBUG<<"table_fields.emplace_back ("<< _field_name<<") pos = "<<size<<std::endl;	   
  	table_fields.emplace_back(_mem_table,_field_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size; 
  DEBUG("push_field2() end ------- } \n");	
	return 0;
  }
  
      //�����ֶ�Ԫ��Ϣ
  int push_field(mem_table_t *_mem_table ,std::string _field_name,std::string _alias_name)
  {  
    
  	  if( NULL == _mem_table )
  		{
  			ERROR("RECORD_META_EMPTY_TABLE\n");
  			return RECORD_META_EMPTY_TABLE;
  		}
  	DEBUG("push_field3() begin \n");	
  	std::string total_name 		=  _alias_name;	
  	CPP_DEBUG<<"field_index_map["<< total_name<<"]= "<<table_fields.size()<<std::endl;	
  	field_index_map[total_name] =  table_fields.size() ;
    CPP_DEBUG<<"table_fields.emplace_back ("<< _field_name<<") pos = "<<size<<std::endl;	   
  	table_fields.emplace_back(_mem_table,_field_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size; 
  	
   DEBUG("push_field3() end \n");		
	return 0;
  }
  
  //����ͶӰ�ޱ����ֶ�
  int add_field(mem_table_t *_mem_table ,field_t& field)
  {  
    DEBUG("add_field() begin ------ { \n");	
      if( NULL == _mem_table )
  		{
  			ERROR("RECORD_META_EMPTY_TABLE\n");
  			return RECORD_META_EMPTY_TABLE;
  		}
  	std::string total_name 		=  std::string(field.field_name);	
  	field_index_map[total_name] =  table_fields.size() ;
    CPP_DEBUG<<"table_fields.emplace_back("<< total_name<<") and pos is "<<size<<std::endl;	
  	//table_fields.emplace_back(total_name,table_fields.size(),size );
  	table_fields.emplace_back(_mem_table,total_name,table_fields.size(),size );

  	size += table_fields.rbegin()->field.field_size; 
    DEBUG("size = %d \n",size );
    
    for(auto iter=field_index_map.begin(); iter!=field_index_map.end(); iter++)
     CPP_DEBUG<<iter->first <<"->"<<iter->second<<std::endl;	
    
    DEBUG("add_field() end ------ }\n");
	return 0;
  }
  
   //��mem_table ��ת������ 
  int from_table(mem_table_t * mem_table )
  {  
  	  if( NULL == mem_table )
  		{
  			ERROR("RECORD_META_EMPTY_TABLE\n");
  			return RECORD_META_EMPTY_TABLE;
  		}
  		
  	DEBUG("from_table() begin \n");
		for(int i = 0;i < mem_table->config.field_used_num; ++i  )
 	 	{
 	 	   field_t& field = mem_table->config.fields_table[i];
 	 		  push_field(mem_table ,std::string(field.field_name ) );
			  
 	 	}
 	  DEBUG("from_table() end \n");	
		return 0;
  }
  
   //�� �ַ����б� ��ת������ ,ֻ��������ͬһ��������
  template<class list_type>
  int append_by_string_list(mem_table_t * mem_table,list_type& str_list )
  {  
  	DEBUG("Enter append_by_string_list\n");
  	if( NULL == mem_table )
  		{
  			ERROR("RECORD_META_EMPTY_TABLE\n");
  			return RECORD_META_EMPTY_TABLE;
  		}
		for(auto &v : str_list )push_field(mem_table ,v );
		
		DEBUG("Leave append_by_string_list\n");
		return 0;
  }
  
    int append_by_meta(record_meta & meta2 )
  {  
  	DEBUG("Enter append_by_meta ----- {\n");

		for(auto &v : meta2.table_fields )
			{
		    DEBUG("append_by_meta.append_by_meta() \n");
				push_field(v.mem_table ,std::string(v.field.field_name) );
				}
				
  	DEBUG("Leave append_by_meta ----- } \n");
		return 0;
  }
  
};


// �������� record
// �����࣬���ڸ�ֵ,�ͱȽ�
struct record_tuple
{
  record_meta    *    meta;
  generic_result *		result;	
  record_tuple():meta(NULL),result(NULL){}
  	
  // ���� = > < ʹ���� map �п��Զ� tuple ����
  // ��Ҫ���� group by ���У� order by ����
  // �Ը��ֶ� ����������
  bool operator ==(const record_tuple & other) const
  {
  	return *(result) == *(other.result);
  }
 
  bool operator < (const record_tuple & other) const
 {
 	for (auto &v : other.meta->table_fields)
 	{
 		if(compare_field(result->data+v.field.field_dis , v.field, v.field.field_size )!=compare_field(other.result->data+v.field.field_dis , v.field, v.field.field_size ) )
 			{
 				return compare_lt_field( result->data+v.field.field_dis, other.result->data+v.field.field_dis , v.field );
 			}
       else continue;
 		
 	}
 	return false;
 }
 
   bool operator > (const record_tuple & other) const
  {
  	for (auto &v : other.meta->table_fields)
  	{
  		if(compare_field(result->data+v.field.field_dis , v.field, v.field.field_size )!=compare_field(other.result->data+v.field.field_dis , v.field, v.field.field_size ) )
  			{
  				return compare_gt_field( result->data+v.field.field_dis, other.result->data+v.field.field_dis , v.field );
  			}
        else continue;
  		
  	}
  	return false;
  }
  
record_tuple(record_meta  * _meta,generic_result *	_result):meta(_meta),result(_result)
{
DEBUG("record_tuple init() \n");
allocate();

}
  	
  int allocate(){
  	DEBUG("result->allocate(%d)\n",meta->size );
  	return result->allocate( meta->size );
  	 }
  
  // ͨ�������֣��ֶ��������Լ���meta �� �ҳ���Ӧ field ��
  // ���� field ��Ϣ�� copy ���ݽ�ȥ��src�ж�Ӧ��ƫ��
  int set_field( mem_table_t *_mem_table , std::string _field_name, const char * src )
  {
  	DEBUG("set_field() begin \n");
// 	DEBUG(" *src = %d \n",*((int *)src) );
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    CPP_DEBUG<<"total_name = "<< total_name<<std::endl;	
	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
    	  CPP_DEBUG<<"field.field_dis = "<< field.field_dis<<std::endl;	
     		strncpy( result->data + field.field_dis , src , field.field_size );
     		DEBUG("set_field() end \n");
    		return 0;
    	}
    	ERROR("NOT FOUND field INFO ! \n");
    	return -1;
    	
  }
  
  // ͨ���ֶ��������Լ���meta �� �ҳ���Ӧ field ��
  // ���� field ��Ϣ�� copy ���ݽ�ȥ��src�ж�Ӧ��ƫ��
  // ��Ҫ���ڷ�ԭ�������
  int set_field(  std::string _field_name, const char * src )
  {
  	DEBUG("set_field() begin,   --------- {\n");
  	if( NULL == src )
  	{
  		ERROR("SRC_IS_NULL\n");
  		return SRC_IS_NULL;
  	}
  	std::string total_name =  _field_name;
    CPP_DEBUG<<"total_name = "<< total_name<<std::endl;	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
    	 
    	  DEBUG("result->data + field.field_dis is %0x \n", result->data + field.field_dis );
    	  DEBUG("src is %0x \n", src );

     		strncpy( result->data + field.field_dis , src , field.field_size );
     		DEBUG("set_field() end   --------- }\n");
    		return 0;
    	}
    	ERROR("NOT FOUND field INFO !   --------- }\n");
    	return -1;
    	
  }
  
  //����ָ���ֶε��׵�ַ
  int get_field(mem_table_t *_mem_table ,std::string _field_name, char ** target)
  {
  	DEBUG("get_field() begin,   ---------------{\n");
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    CPP_DEBUG<<"total_name = "<< total_name<<std::endl;	
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
     		*target = (char *)(result->data + field.field_dis);
    		return 0;
    	}
    ERROR("set_field() end,   ---------------{\n"); 	
    	return -1;
    	
  }
  
    //����ָ���ֶε��׵�ַ
  int get_field_desc(mem_table_t *_mem_table ,std::string _field_name,field_t &field )
  {
  	DEBUG("Enter get_field_desc  ---------------{\n");
  	if(NULL == _mem_table)
  		{
  			ERROR("_mem_table is NULL\n");
  			return MEM_TABLE_IS_NULL;
  		}
  		else DEBUG("_mem_table is %0x \n", _mem_table );	
  			
  		 if( _field_name.empty() )
  		{
  			ERROR("_field_name is empty  ---------------}\n");
  			return FIELD_IS_EMPTY;
  		}
  		else CPP_DEBUG<<"_field_name is "<<_field_name<<std::endl;
  	
  	DEBUG("_mem_table->config.table_name is %s \n", _mem_table->config.table_name );		
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    
    CPP_DEBUG<<"total_name is "<<total_name<<std::endl;
    		
    for(auto iter=meta->field_index_map.begin(); iter!=meta->field_index_map.end(); iter++)
         CPP_DEBUG<<iter->first <<"->"<<iter->second<<std::endl;		
    		
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field = meta->table_fields[n].field;
    	  DEBUG("Leave get_field_desc  ---------------}\n");
    		return 0;
    	}
    	ERROR("TOTAL_NAME_NOT_FOUND\n");
    	DEBUG("Leave get_field_desc  ---------------}\n");

    	return TOTAL_NAME_NOT_FOUND;
  }
  
};


// ʹ record_tuple ֧�� unordered_map
namespace std
{
    template<> struct hash<record_tuple>
    {
        typedef record_tuple argument_type;
        typedef uint64_t result_type;
       inline result_type operator()(argument_type const& s)  const
        {
           return MurmurHash64A()(s.result->data); 
          
        }
    };
}

// ���һ����ɨ�������е��ֶε�Ԫ��������
int get_talbe_scan_meta(
												/*in*/  QueryAnalyser * qa,										
												/*in*/  std::map<std::string,std::set<std::string> >&  scan_fields,        // ��Ҫɨ����ֶ�
												/*out*/ std::map<std::string,record_meta>						&  scan_metas          // ����ɨ����Ԫ��������

)
{
	
	int ret = 0;
	for (size_t i = 0 ;i <qa->tables.size();++i )
	{
				std::string table_name = qa->tables[i].table_name_;
				mem_table_t * mem_table = qa->tables[i].mem_table;
					
				record_meta one;
				one.append_by_string_list( mem_table,scan_fields[table_name] );
	      scan_metas[table_name] = one; 
	}
	return ret;
}






#endif 