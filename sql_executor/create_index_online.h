#ifndef CREATE_INDEX_ONLINE
#define CREATE_INDEX_ONLINE

/*

 g++ -C -w -std=c++11 create_index_online.h


*/

#include<map>
#include"index_dml_t.h"

template< typename ContainerT, typename PredicateT >
  void erase_if( ContainerT& items, const PredicateT& predicate ) {
    for( auto it = items.begin(); it != items.end(); ) {
      if( predicate(*it) ) it = items.erase(it);
      else ++it;
    }
  };
//


//if( INDEX_TYPE_HASH == index_type )mem_hash_index_t	*  mem_hash_index; //HASH ����ָ��
//if( INDEX_TYPE_SKIP == index_type )mem_skiplist_index_t	*   mem_skiplist_index; //skiplist ����ָ��

template<class T>
struct get_mem_index_type_from_entry_type
{
	typedef T type;
};

template<>
struct get_mem_index_type_from_entry_type<mem_hash_entry_t>
{
	typedef mem_hash_index_t type;
};

template<>
struct get_mem_index_type_from_entry_type<mem_skiplist_entry_t>
{
	typedef mem_skiplist_index_t type;
};


// ��Ҫ�½�һ������
template<class INDEX_ENTERY_TYPE>
struct online_create_index
{
mem_table_t *mem_table;
std::string field_name;  // ���������ֶ���
int         index_type;
long long   Tn;   // ������ʱ����������
index_dml_t<INDEX_ENTERY_TYPE>  index_dml;
int          error;

typedef typename get_mem_index_type_from_entry_type<INDEX_ENTERY_TYPE>::type  mem_index_ptr_t;

online_create_index(mem_table_t * _mem_table , std::string& _field_name ,int _index_type ):mem_table(_mem_table),field_name(_field_name),error(0),
																																													 index_type(_index_type),index_dml( mem_table, field_name , index_type  )
{
}

~online_create_index()
{
	if(error)
		{
			int err = 0;
			CPP_ERROR<<"rollback_trans : "<<Tn<<"\n";
			if(0!=(err=rollback_trans(Tn)))ERROR("rollback_trans failed,Tn is %d\n",err);
		}
	
}


//sys_transaction_manager_t transaction_manager;

//��������һʱ�̵� ��δ�ύ�� scn  list<record_t> 
std::map<unsigned  long long, std::list<struct record_t*> > un_commit_map;
long long commit_scn ;
long long un_commit_scn ;
long long high_level ;
long end_block_no;

int get_un_commit_scn( long long& un_commit_scn , long long& commit_scn,long & end_block_no, long long&  high_level )
{
CPP_DEBUG<<"START get_un_commit_scn() \n";

	int err = 0;
	record_t * record_ptr;
	long  block_no;
	
// �޸� �ֶ�������ʶ
MEM_TRANSACTION_LOCK(&(transaction_manager.locker));    //���� 
int is_ok = 1;
while(is_ok)
{
int i = 0;
	struct  mem_block_t * mem_block_temp = mem_table->config.mem_blocks_table;
	for(;i<mem_table->config.mem_block_used-1;++i)
		{
			mem_block_temp = mem_block_temp->next; 
		}
			if( 0!= (HIGH_LEVEL_TRYLOCK(&(mem_block_temp->high_level_lock))) )
			{
				//IMPORTANT_INFO("HIGH_LEVEL_TRYLOCK =0\n");
				return HIGH_LEVEL_TRY_LOCK;  //��ˮλ������
			}		
		unsigned  long  high_level_temp = mem_block_temp->high_level;  
    if(mem_block_temp->space_start_addr + mem_block_temp->high_level* mem_table->record_size < mem_block_temp->space_end_addr - mem_table->record_size )
    {		
    	 DEBUG("----- try to get record  high level -----\n");
    	 //���ؿ���߼���
    	 end_block_no = mem_block_temp->block_no;
       high_level=high_level_temp;
       is_ok = 0;
       //DEBUG(" ----- try to allocate record by high level end -----\n");
    }	
	 HIGH_LEVEL_UNLOCK(&(mem_block_temp->high_level_lock)); //��ˮλ�߽��� 		
}

un_commit_scn = transaction_manager.scn;						 		//���δ������С scn������� scn ����ʱ ���Ͳ�������
commit_scn    = transaction_manager.commit_scn;				  //������ύ��� scn 
MEM_TRANSACTION_UNLOCK(&(transaction_manager.locker)); //����
//mem_table_force_del_record( mem_table , record_ptr);
CPP_DEBUG<<"End get_un_commit_scn() \n";

return 0;
}

//��õ�ǰʱ�� commit_scn
unsigned  long long get_commit_scn(  )
{
CPP_DEBUG<<"START get_commit_scn() \n";
MEM_TRANSACTION_LOCK(&(transaction_manager.locker));   //���� 
long long commit_scn      = transaction_manager.commit_scn;			 //������ύ��� scn 
MEM_TRANSACTION_UNLOCK(&(transaction_manager.locker)); //����
CPP_DEBUG<<"END get_commit_scn() \n";

return commit_scn;
}

// ��һ��ȫ��ɨ
int scan_all_row_to_create_index( mem_table_t *mem_table,mem_index_ptr_t*  mem_index_ptr ){
		CPP_DEBUG<<"START scan_all_row_to_create_index() \n";

if(error){
	CPP_ERROR<<"SOME ERROR HAPPEND BEFORE scan_all_row_to_create_index \n";
	return error;
	}	
	
int ret = get_un_commit_scn( commit_scn , un_commit_scn, end_block_no, high_level );
char buf[mem_table->record_size - RECORD_HEAD_SIZE];

int __i = 0;											 
struct record_t     * record_ptr;
struct record_t * out_record_ptr = NULL;

//����һ�����񣬱����� get_un_commit_scn ֮��
if(0!=(error=allocate_trans(&Tn))){
	ERROR("allocate_trans[%d] failed,Tn is %d\n",Tn,error); 
	 return error;
}
// ��ʼһ������
if(0!=(error=start_trans(Tn))){
	ERROR("start_trans failed,Tn is %d\n",error); 
  return error;
}

  struct mem_block_t  * __mem_block_temp = mem_table->config.mem_blocks_table;	
 
	for(;__i<mem_table->config.mem_block_used;++__i)//�������п�																
	{
			unsigned  long  __high_level_temp = 0;
      
				for(; //����������
				__mem_block_temp->space_start_addr + (__high_level_temp)* (mem_table->record_size) < __mem_block_temp->space_end_addr - mem_table->record_size ;
				++__high_level_temp
				   )		 															
				{
					// ����Ѿ�ɨ�赽�����������㣬����Ͳ���ɨ����
					if( __mem_block_temp->block_no == end_block_no && __high_level_temp == __high_level_temp )return 0;
					
					//DEBUG("__high_level_temp = %ld\n",__high_level_temp);
						// �ҵ����õļ�¼λ��
						record_ptr = (struct record_t *) ( (char *)__mem_block_temp->space_start_addr + (__high_level_temp) * (mem_table->record_size) );
						// �Ѿ�ɾ�����в�����
						if(record_ptr->is_used != 1)continue;
					  DEBUG("record_ptr addr is %0x,record_ptr->is_used = %d\n",record_ptr,record_ptr->is_used);

						if( !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn) )
						{
									//����һ������
									row_wlock   (  &(record_ptr->row_lock ) );
									// ��create index ֮ǰ���Ѿ��ύ���ˣ�ɾ�����ܣ�mvcc_insert
									if ( record_ptr->scn <= commit_scn ){
									   			if ( record_ptr->is_used == 0 ) {
									   				row_wunlock   (  &(record_ptr->row_lock ) );
									   		  	DEBUG("record_ptr->scn is %d,commit_scn is %d , un_commit_scn is %d,record_ptr->is_used is %d \n",record_ptr->scn,commit_scn, un_commit_scn,record_ptr->is_used);

									   				continue;
									   			}
									   else { 
									   	
									   	  ret = index_dml.insert_into_index_scn(mem_index_ptr, //����ָ��
												record_ptr,       //��Ӧ���ϵ�ԭʼ���� ��ָ��
												buf,
												&out_record_ptr,	
												Tn ,
 												record_ptr->scn  );
												if(ret){
													row_wunlock   (  &(record_ptr->row_lock ) );
													return ret;
												       }
												       
									   			}
									}
									
									// ��create index ֮ǰû���ύ�� �������־��Ѿ��ύ���ˣ�ɾ�����ܣ�mvcc_insert
									// ���ڻ�û���ύ�ģ����� map
									int scn;
									if ( record_ptr->scn > commit_scn && record_ptr->scn < un_commit_scn ){
									   unsigned  long long  commit_scn2  = get_commit_scn();
										 	DEBUG("record_ptr->scn is %d,commit_scn is %d , un_commit_scn is %d,commit_scn2 is %d \n",record_ptr->scn,commit_scn, un_commit_scn,commit_scn2);

											// ���ύ
											if( record_ptr->scn <= commit_scn2 ){
												
									   			if ( record_ptr->is_used == 0 ) {
									   				row_wunlock   (  &(record_ptr->row_lock ) );
									   				continue;
									   			}
									   			else { 
									   				scn = record_ptr->scn;
									   				ret = index_dml.insert_into_index_scn(mem_index_ptr, //����ָ��
														record_ptr,       //��Ӧ���ϵ�ԭʼ���� ��ָ��
														buf,
														&out_record_ptr,	
														Tn ,
 														record_ptr->scn  );
 														
														if(ret){
															row_wunlock   (  &(record_ptr->row_lock ) );
															return ret;
														       }
									   			}
									   		}
									    // δ�ύ
									   	else un_commit_map[record_ptr->scn].push_back( record_ptr );
									//ȫ��ɨ����
									}
									row_wunlock   (  &(record_ptr->row_lock ) );
						}
						
				}
			__mem_block_temp = __mem_block_temp->next;      //��һ����
	}
	CPP_DEBUG<<"END scan_all_row_to_create_index() \n";

	return 0;
}

// �ȴ������������
int deal_uncommit_scn( mem_index_ptr_t*  mem_index_ptr )
{
	CPP_DEBUG<<"START deal_uncommit_scn() \n";

	if(error){
	CPP_ERROR<<"SOME ERROR HAPPEND BEFORE deal_uncommit_scn \n";
	return error;
	}	
	
	
unsigned  long long last_scn= get_commit_scn();
struct record_t * out_record_ptr = NULL;
char buf[mem_table->record_size - RECORD_HEAD_SIZE];
record_t * record_ptr = NULL;

//long scn;
//error = get_trans_scn( Tn, &scn);

//  last_scn < un_commit_scn && scn != un_commit_scn ��ȫ��ɨ��ʼ��һʱ�̵�δ�ύ�����ύ��ʱ�򣬰����ǲ�������������ȴ�����ִ����
while( last_scn < un_commit_scn  )
{
	DEBUG("last_scn: %d <= un_commit_scn : %d \n",last_scn, un_commit_scn );
usleep(1000000); // ���ڻ��� create index ʱû���ύ������͵ȴ�1s������
last_scn = get_commit_scn();

auto commit_end = un_commit_map.upper_bound(last_scn);

for( std::map<unsigned  long long, std::list<struct record_t * > >::iterator  i = un_commit_map.begin(); i != commit_end ;   )
{
	for(auto &v : i->second )
		{
			record_ptr = v;
			if( !mem_mvcc_read_record(mem_table , record_ptr, (char *)buf,Tn) )
			{
			  row_wlock   (  &(record_ptr->row_lock ) );
			  //��¼δʹ�û��߻ع���ɾ����
			  if( 0 == record_ptr->is_used )
			  {
			  	row_wunlock (  &(record_ptr->row_lock )    );
			  	continue;
			  }
	      
			  //���������е� scn
			  if( record_ptr->scn > commit_scn && record_ptr->scn < un_commit_scn )
			  	{ 
			  						   				error = index_dml.insert_into_index_scn(mem_index_ptr, //����ָ��
			  											record_ptr,       //��Ӧ���ϵ�ԭʼ���� ��ָ��
			  											buf,
			  											&out_record_ptr,	
			  											Tn ,
 			  											record_ptr->scn  );
			  											if(error){
			  												row_wunlock   (  &(record_ptr->row_lock ) );
			  												return error;
			  											       }
			  	}
		    
			  row_wunlock   (  &(record_ptr->row_lock ) );
			 }

		}
		i = un_commit_map.erase(i); //���������� for ���� ++ 
}

}

if(0!=(error=commit_trans(Tn)))ERROR("commit_trans failed,Tn is %d\n",error); 
		CPP_DEBUG<<"END deal_uncommit_scn() \n";

return error;
}


int execute(  mem_index_ptr_t*  mem_index_ptr  )
{
	int ret = scan_all_row_to_create_index( mem_table,   mem_index_ptr ) ;
	if(ret)
		{
			CPP_ERROR<<"scan_all_row_to_create_index err is "<<ret<<std::endl;
			return ret;
		}
		
	 ret = deal_uncommit_scn(  mem_index_ptr );
	if(ret)
		{
			CPP_ERROR<<"scan_all_row_to_create_index err is "<<ret<<std::endl;
			return ret;
		}
		return 0;
	
}

};
   	
   	
#endif