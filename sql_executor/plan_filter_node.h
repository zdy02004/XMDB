/*
 g++ -C -w -std=c++11 plan_filter_node.h  
*/

#ifndef PLAN_FILTER_NODE
#define PLAN_FILTER_NODE  


#include "plan_node.h"

// ��Ҫ���ڶ��м������й���


// ������ڵ㸸��
template<class T>
struct filter_node:public plan_node
{
	std::string relation_name ; //����
	std::string column_name   ; //����
	std::string const_value   ; //����ֵ
	std::string const_type    ; //��������
	T* container;
	field_t field;
	
	filter_node( T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):plan_node(_json,_Doc),
  																					container(_container),
  																					field(_field),
  																					relation_name(_relation_name),
  																					column_name(_column_name),
  																					const_value(_const_value),
  																					const_type(_const_type){}

	virtual int execute( unsigned long long  trans_no  );

// ���ﲻ��ȫ ��ʱ����ôд
virtual std::list<generic_result>* get_ret_list()
{
	return container;
}
	
};


//������ȵĽڵ�
template<class T>
struct filter_eq_node:public filter_node<T>
{
filter_eq_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_EQ_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!( cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) ==  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );
										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};



template<class T>
struct filter_le_node:public filter_node<T>
{
filter_le_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type =PLAN_TYPE_LE_FIELTER ;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) <=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );
										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};


template<class T>
struct filter_lt_node:public filter_node<T>
{
filter_lt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_LT_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) <  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};


template<class T>
struct filter_ge_node:public filter_node<T>
{
filter_ge_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_GE_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) >=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};

template<class T>
struct filter_gt_node:public filter_node<T>
{
filter_gt_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type = PLAN_TYPE_GT_FIELTER;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) >  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};



template<class T>
struct filter_ne_node:public filter_node<T>
{
filter_ne_node(T* _container,
									field_t&  _field,
									rapidjson::Value& _json,
  								rapidjson::Document * _Doc,
  								std::string& _relation_name,
  								std::string& _column_name,
  								std::string& _const_value,
  								std::string& _const_type):filter_node<T>(_container,
																						_field,
																						_json,
  																					_Doc,
  																					_relation_name,
  																					_column_name,
  																					_const_value,
  																					_const_type){filter_node<T>::plan_type =PLAN_TYPE_GT_FIELTER ;}
  																					
virtual int execute( unsigned long long  trans_no  )
{
	int ret = 0;
	filter_node<T>::container->erase(std::remove_if(filter_node<T>::container->begin(),  filter_node<T>::container->end(),
		 [&](typename T::value_type & one ){
		 							// ����Ⱦ�ɾ����������ȵ�
									return	!(cast_field<T::value_type,filter_node<T>::field.field_type>( &one , filter_node<T>::field ) !=  cast_condition<filter_node<T>::field.field_type>( filter_node<T>::const_value , filter_node<T>::field ) );

										} ), 
									 filter_node<T>::container->end()); 
	return 0;
}

};






#endif 