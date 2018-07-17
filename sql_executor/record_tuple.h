/*
 g++ -C -w -std=c++11 record_tuple.h
*/

#ifndef SQL_FIELD
#define SQL_FIELD


#include "sql_field.h"
#include <unordered_map>
#define RECORD_META_EMPTY_TABLE 77001
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
  		get_field(mem_table ,_field_name,field);
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
  
  	if( NULL == _mem_table )return RECORD_META_EMPTY_TABLE;
  	std::string total_name 		=  std::string( _mem_table->config.table_name ) + std::string(".")+_field_name;	
  	field_index_map[total_name] =  table_fields.size() ;

  	table_fields.emplace_back(_mem_table,_field_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size; 
	return 0;
  }
  
      //�����ֶ�Ԫ��Ϣ
  int push_field(mem_table_t *_mem_table ,std::string _field_name,std::string _alias_name)
  {  
  
  	if( NULL == _mem_table )return RECORD_META_EMPTY_TABLE;
  	std::string total_name 		=  _alias_name;	
  	field_index_map[total_name] =  table_fields.size() ;

  	table_fields.emplace_back(_mem_table,_field_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size; 
	return 0;
  }
  
  //����ͶӰ�ޱ����ֶ�
  int add_field(field_t& field)
  {  
  
  	std::string total_name 		=  std::string(field.field_name);	
  	field_index_map[total_name] =  table_fields.size() ;

  	table_fields.emplace_back(total_name,table_fields.size(),size );
  	size += table_fields.rbegin()->field.field_size; 
	return 0;
  }
  
   //��mem_table ��ת������ 
  int from_table(mem_table_t * mem_table )
  {  
  	if( NULL == mem_table )return RECORD_META_EMPTY_TABLE;
		for(int i = 0;i < mem_table->config.field_used_num; ++i  )
 	 	{
 	 	   field_t& field = mem_table->config.fields_table[i];
 	 		  push_field(mem_table ,std::string(field.field_name ) );
			  
 	 	}
		return 0;
  }
  
   //�� �ַ����б� ��ת������ ,ֻ����������ͬһ��������
  template<class list_type>
  int append_by_string_list(mem_table_t * mem_table,list_type& str_list )
  {  
  	if( NULL == mem_table )return RECORD_META_EMPTY_TABLE;
		for(auto &v : str_list )push_field(mem_table ,v );
		return 0;
  }
  
    int append_by_meta(record_meta & meta2 )
  {  
		for(auto &v : meta2.table_fields )push_field(v.mem_table ,std::string(v.field.field_name) );
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
  
  record_tuple(record_meta  * _meta,generic_result *	_result):meta(_meta),result(_result){allocate();}
  int allocate(){return result->allocate(meta->size); }
  
  // ͨ�������֣��ֶ��������Լ���meta �� �ҳ���Ӧ field ��
  // ���� field ��Ϣ�� copy ���ݽ�ȥ��src�ж�Ӧ��ƫ��
  int set_field( mem_table_t *_mem_table , std::string _field_name, const char * src )
  {
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
     		strncpy( result->data + field.field_dis , src , field.field_size );
    		return 0;
    	}
    	return -1;
    	
  }
  
  // ͨ���ֶ��������Լ���meta �� �ҳ���Ӧ field ��
  // ���� field ��Ϣ�� copy ���ݽ�ȥ��src�ж�Ӧ��ƫ��
  // ��Ҫ���ڷ�ԭ�������
  int set_field(  std::string _field_name, const char * src )
  {
  	std::string total_name =  _field_name;
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
     		strncpy( result->data + field.field_dis , src , field.field_size );
    		return 0;
    	}
    	return -1;
    	
  }
  
  //����ָ���ֶε��׵�ַ
  int get_field(mem_table_t *_mem_table ,std::string _field_name, char ** target)
  {
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field_t &field = meta->table_fields[n].field;
     		*target = (char *)(result->data + field.field_dis);
    		return 0;
    	}
    	return -1;
    	
  }
  
    //����ָ���ֶε��׵�ַ
  int get_field_desc(mem_table_t *_mem_table ,std::string _field_name,field_t &field )
  {
  	std::string total_name = std::string( _mem_table->config.table_name ) + std::string(".") + _field_name;
    	
    if( meta->field_index_map.find(total_name) != meta->field_index_map.end() ){
    	  int n = meta->field_index_map[total_name];
    	  field = meta->table_fields[n].field;
    		return 0;
    	}
    	return -1;
    	
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