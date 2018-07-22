#ifndef INDEX_ADDR_SCAN
#define INDEX_ADDR_SCAN


/*
 * g++ -w -lpthread -C -std=c++11 index_scan_Addr.hpp
 */

#include <map>
#include <set>
#include <algorithm>
#include "skiplist_index_scan.h"
#include "hash_index_scan.h"
#include "ops.hpp"


struct index_Addr {
	long			block_no;
	unsigned long long	record_num;
	index_Addr( long _block_no, unsigned long long _record_num ) : block_no( _block_no ), record_num( _record_num )
	{
	}


	bool operator ==( const index_Addr & other )
	{
		return(block_no == other.block_no && record_num == other.record_num);
	}
};

bool operator <( const index_Addr & a, const index_Addr & b )
{
	if ( a.block_no != b.block_no )
		return(a.block_no < b.block_no);
	else return(a.record_num < b.record_num);
}


typedef std::set< index_Addr > finded_Addr_t;

bool find_Addr( finded_Addr_t & mapAddr, long block_no, long long record_num )
{
	if ( mapAddr.empty() )
		return(false);
	auto iter = mapAddr.find( index_Addr( block_no, record_num ) );

	if ( iter != mapAddr.end() )
		return(true);
	else return(false);
}


/* 插入一个整型索引的数据,保证每个桶相同的 val 相邻 */

inline int mem_skiplist_index_scanAddr_long(
	       mem_table_t *mem_table,
/* in */ struct mem_skiplist_index_t * mem_skiplist_index,
/* in */ mem_skiplist_entry_t *in,
	       mem_skiplist_entry_t **last_find_entry,
/* in */ unsigned long long Tn,         /* 当前事务ID */
	       finded_Addr_t & finded_Addr,
	       finded_Addr_t & ret_list,               /* 原始结果集 */
	       int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	DEBUG( "mem_skiplist_index_scanAddr_long() start!\n" );
	int			ret			= 0;
	struct    record_t	* return_record_ptr	= 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];

	mem_skiplist_entry_t * finded_entry = 0;
	if ( !mem_skiplist_find_one_at_lowest( mem_skiplist_index,
					       in,
					       &finded_entry ) )
	{
		DEBUG( "Pass in lowest level in skiplist_space!\n" );
		/* 插入结果集 */
		ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num, &return_record_ptr );
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space!\n" );
			DEBUG( "finded_Addr.size() is %ld!\n", finded_Addr.size() );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete( mem_skiplist_index,
									finded_entry,
									Tn /* 本事务ID */
									);
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
						return(err);
					}
				}
			}
			*last_find_entry = finded_entry;
		}
		/*  */
		while ( !mem_skiplist_find_EQO(
				mem_skiplist_index,
				finded_entry,
				in,
				&finded_entry ) )
		{
			/* 插入结果集 */
			ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num, &return_record_ptr );
			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete( mem_skiplist_index,
										finded_entry,
										Tn /* 本事务ID */
										);
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
							return(err);
						}
					}
				}
				*last_find_entry = finded_entry;
				DEBUG( "*last_find_entry is %0x !\n", *last_find_entry );
			}
		}
	}
	DEBUG( "mem_skiplist_index_scanAddr_long() end!\n" );
	return(0);
}


/* 插入一个整型索引的数据,保证每个桶相同的 val 相邻 */

inline int mem_skiplist_index_scanAddr_str(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	DEBUG( "mem_skiplist_index_scanAddr_str() start!\n" );
	int			ret			= 0;
	struct    record_t	* return_record_ptr	= 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	mem_skiplist_entry_t * finded_entry = 0;
	if ( !mem_skiplist_find_one_at_lowest_str( mem_skiplist_index,
						   in,
						   &finded_entry ) )
	{
		DEBUG( "Pass in lowest level in skiplist_space!\n" );
		/* 插入结果集 */
		ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num, &return_record_ptr );
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space!\n" );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
									    finded_entry,
									    Tn /* 本事务ID */
									    );
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
						return(err);
					}
				}
			}
			*last_find_entry = finded_entry;
		}
		/*  */
		while ( !mem_skiplist_find_EQO_str(
				mem_skiplist_index,
				finded_entry,
				in,
				&finded_entry ) )
		{
			/* 插入结果集 */
			ret = get_record( mem_table, finded_entry->block_no, finded_entry->record_num, &return_record_ptr );
			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
										    finded_entry,
										    Tn /* 本事务ID */
										    );
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
							return(err);
						}
					}
				}
				*last_find_entry = finded_entry;
			}
		}
	}
	DEBUG( "mem_skiplist_index_scanAddr_str() end!\n" );
	return(0);
}


/*  将本层 prev到  <= in->lkey 的节点，扫描出来 */

inline int mem_skiplist_LE_scanAddr(
	mem_table_t *mem_table,
	mem_skiplist_index_t *mem_skiplist_index,
	mem_skiplist_entry_t *prev,
	mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;
	int			ret;

	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_LE_scanAddr(),prev_entry is %0x,input_key is %ld     \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
		printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %ld \n ", right_entry->lkey );


		if ( mem_skiplist_index->nil != right_entry &&
		     right_entry->lkey <= in->lkey )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;
			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete( mem_skiplist_index,
										finded_entry,
										Tn /* 本事务ID */
										);
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && right_entry->lkey <= in->lkey );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_LE_scan end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  将本层 prev到  <= in->lkey 的节点，扫描出来 */

inline int mem_skiplist_LE_scanAddr_str(
	mem_table_t *mem_table,
	mem_skiplist_index_t *mem_skiplist_index,
	mem_skiplist_entry_t *prev,
	mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;
	int			ret;

	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_LE_scanAddr_str(),prev_entry is %0x,input_key is %ld         \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %s \n ", right_entry->ckey );


		if ( mem_skiplist_index->nil != right_entry &&
		     strcmp( right_entry->ckey, in->ckey ) <= 0 )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
										    finded_entry,
										    Tn /* 本事务ID */
										    );
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && strcmp( right_entry->ckey, in->ckey ) <= 0 );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_LE_scanAddr_str end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  将本层 prev到  < in->lkey 的节点，扫描出来 */

inline int mem_skiplist_L_scanAddr(
	mem_table_t *mem_table,
	mem_skiplist_index_t *mem_skiplist_index,
	mem_skiplist_entry_t *prev,
	mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;
	int			ret;

	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_L_scanAddr(),prev_entry is %0x,input_key is %ld      \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %ld \n ", right_entry->lkey );


		if ( mem_skiplist_index->nil != right_entry &&
		     right_entry->lkey < in->lkey )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete( mem_skiplist_index,
										finded_entry,
										Tn /* 本事务ID */
										);
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && right_entry->lkey < in->lkey );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_L_scan end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  将本层 prev到  < in->ckey 的节点，扫描出来 */

inline int mem_skiplist_L_scanAddr_str(
	mem_table_t *mem_table,
	mem_skiplist_index_t *mem_skiplist_index,
	mem_skiplist_entry_t *prev,
	mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
  /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;
	int			ret;

	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_L_scanAddr_str(),prev_entry is %0x,input_key is %ld  \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %s \n ", right_entry->ckey );


		if ( mem_skiplist_index->nil != right_entry &&
		     strcmp( right_entry->ckey, in->ckey ) < 0 )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
										    finded_entry,
										    Tn /* 本事务ID */
										    );
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && strcmp( right_entry->ckey, in->ckey ) < 0 );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_L_scanAddr_str end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/* __________________________________________________________________________________ */

/*  获得本层 > lkey的前继节点 */

inline int mem_skiplist_G_scanAddr( mem_table_t *mem_table,
				    mem_skiplist_index_t *mem_skiplist_index,
				    mem_skiplist_entry_t *prev,
				    mem_skiplist_entry_t *in,
				    mem_skiplist_entry_t **last_find_entry,
                                    /* in */ unsigned long long Tn,     /* 当前事务ID */
				    finded_Addr_t & finded_Addr,
				    finded_Addr_t & ret_list,           /* 原始结果集 */
				    int oper_type = BASIC_OPS_SCAN      /* 操作类型默认是扫描 */
				    )
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_find_G(),prev_entry is %0x,input_key is %ld  \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETG_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %ld \n ", right_entry->lkey );


		if ( mem_skiplist_index->nil != right_entry &&
		     right_entry->lkey > in->lkey )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete( mem_skiplist_index,
										finded_entry,
										Tn /* 本事务ID */
										);
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && right_entry->lkey > in->lkey );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_find_G end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  获得本层 >= lkey的前继节点 */

inline int mem_skiplist_GE_scanAddr( mem_table_t *mem_table,
				     mem_skiplist_index_t *mem_skiplist_index,
				     mem_skiplist_entry_t *prev,
				     mem_skiplist_entry_t *in,
				     mem_skiplist_entry_t **last_find_entry,
                                     /* in */ unsigned long long Tn,    /* 当前事务ID */
				     finded_Addr_t & finded_Addr,
				     finded_Addr_t & ret_list,          /* 原始结果集 */
				     int oper_type = BASIC_OPS_SCAN     /* 操作类型默认是扫描 */
				     )
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld         \n ", prev_entry, in->lkey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE(),prev_entry is %0x,input_key is %ld      \n ",prev_entry,in->lkey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %ld \n ", right_entry->lkey );


		if ( mem_skiplist_index->nil != right_entry &&
		     right_entry->lkey >= in->lkey )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete( mem_skiplist_index,
										finded_entry,
										Tn /* 本事务ID */
										);
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && right_entry->lkey >= in->lkey );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_find_GE end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  获得本层 > ckey的前继节点 */

inline int mem_skiplist_G_scanAddr_str( mem_table_t *mem_table,
					mem_skiplist_index_t *mem_skiplist_index,
					mem_skiplist_entry_t *prev,
					mem_skiplist_entry_t *in,
					mem_skiplist_entry_t **last_find_entry,
                                        /* in */ unsigned long long Tn, /* 当前事务ID */
					finded_Addr_t & finded_Addr,
					finded_Addr_t & ret_list,       /* 原始结果集 */
					int oper_type = BASIC_OPS_SCAN  /* 操作类型默认是扫描 */
					)
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_find_G_str(),prev_entry is %0x,input_key is %s       \n ", prev_entry, in->ckey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE_str(),prev_entry is %0x,input_key is %s   \n ",prev_entry,in->ckey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETG_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %s \n ", right_entry->ckey );


		if ( mem_skiplist_index->nil != right_entry &&
		     strcmp( right_entry->ckey, in->ckey ) > 0 )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;
			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
										    finded_entry,
										    Tn /* 本事务ID */
										    );
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && strcmp( right_entry->ckey, in->ckey ) > 0 );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_find_G_str end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE_str ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


/*  获得本层 >= ckey的前继节点 */

inline int mem_skiplist_GE_scanAddr_str( mem_table_t *mem_table,
					 mem_skiplist_index_t *mem_skiplist_index,
					 mem_skiplist_entry_t *prev,
					 mem_skiplist_entry_t *in,
					 mem_skiplist_entry_t **last_find_entry,
                                         /* in */ unsigned long long Tn,        /* 当前事务ID */
					 finded_Addr_t & finded_Addr,
					 finded_Addr_t & ret_list,              /* 原始结果集 */
					 int oper_type = BASIC_OPS_SCAN         /* 操作类型默认是扫描 */
					 )
{
	/* 右指针 和 它的数据指针 */
	record_t		* right_record	= NULL;
	mem_skiplist_entry_t	* right_entry	= NULL;
	record_t		* prev_record	= NULL;
	mem_skiplist_entry_t	* prev_entry	= prev;
	int			err;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	DEBUG( "Enter mem_skiplist_find_GE_str(),prev_entry is %0x,input_key is %s      \n ", prev_entry, in->ckey );
	/* IMPORTANT_INFO("Enter mem_skiplist_find_GE_str(),prev_entry is %0x,input_key is %s   \n ",prev_entry,in->ckey); */
	do
	{
		/*	do{ */
		if ( right_record && right_record->is_used == 0 )
			printf( "right_record->is_used == 0 \n" );
		prev_record = (record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

		SKIPLIST_RLOCK( &(prev_record->row_lock) );
		err = get_record( mem_skiplist_index->heap_space,
				  prev_entry->right_block_no,
				  prev_entry->right_record_num,
				  &right_record );
		SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
		if ( right_record->is_used == 0 )
			return(SKIPLIST_INDEX_ERR_GETGE_FAILED);

		if ( err )
			return(err);
		/*	}while( right_record->is_used == 0 ); */

		right_entry = (mem_skiplist_entry_t *) ( (char *) (right_record) + RECORD_HEAD_SIZE);
		DEBUG( " go pass entry %s \n ", right_entry->ckey );


		if ( mem_skiplist_index->nil != right_entry &&
		     strcmp( right_entry->ckey, in->ckey ) >= 0 )
		{
			prev_entry = right_entry;
			/* 插入结果集 */
			ret = get_record( mem_table, right_entry->block_no, right_entry->record_num, &return_record_ptr );
			mem_skiplist_entry_t * finded_entry = right_entry;

			if ( !ret )
			{
				DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
				if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
				{
					ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
					if ( BASIC_OPS_DELETE == oper_type )
					{
						int err = 0;
						err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
										    finded_entry,
										    Tn /* 本事务ID */
										    );
						if ( 0 != err )
						{
							ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
							return(err);
						}
					}
				}
			}
		}
	}
	while ( right_entry != mem_skiplist_index->nil && strcmp( right_entry->ckey, in->ckey ) >= 0 );

	*last_find_entry = prev_entry;

	DEBUG( " mem_skiplist_find_GE_str end,prev_record is %0x \n ", right_record->record_num );
	/* IMPORTANT_INFO(" End mem_skiplist_find_GE_str ,prev_record is %ld \n ",prev_entry); */

	return(0);
}


inline int mem_skiplist_index_scanAddr_long_btw(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *min,
        /* in */ mem_skiplist_entry_t *max,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	if ( !mem_skiplist_index_scanAddr_long(
		     mem_table,
		     mem_skiplist_index,
		     min,
		     last_find_entry,
		     Tn,
		     finded_Addr,
		     ret_list,  /* 原始结果集 */
		     oper_type
		     )
	     )
	{
		DEBUG( "return  mem_skiplist_LE_scan,last_find_entry is %0x \n", *last_find_entry );
		return(mem_skiplist_LE_scanAddr(
			       mem_table,
			       mem_skiplist_index,
			       *last_find_entry,
			       max,
			       last_find_entry,
			       Tn,
			       finded_Addr,
			       ret_list, /* 原始结果集 */
			       oper_type
			       ) );
	}
}


inline int mem_skiplist_index_scanAddr_str_btw(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *min,
        /* in */ mem_skiplist_entry_t *max,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	if ( !mem_skiplist_index_scanAddr_str(
		     mem_table,
		     mem_skiplist_index,
		     min,
		     last_find_entry,
		     Tn,
		     finded_Addr,
		     ret_list,  /* 原始结果集 */
		     oper_type
		     )
	     )
	{
		return(mem_skiplist_LE_scanAddr_str(
			       mem_table,
			       mem_skiplist_index,
			       *last_find_entry,
			       max,
			       last_find_entry,
			       Tn,
			       finded_Addr,
			       ret_list, /* 原始结果集 */
			       oper_type
			       ) );
	}
}


/*
 * -------------------------------------------------------------------------------------------
 * 扫描所有 < 某个数的结果集
 */

inline int mem_skiplist_index_scanAddr_long_L(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得最低层头节点 */
	prev_entry	= mem_skiplist_getlevel_head( mem_skiplist_index, 1 );
	prev_record	= (struct record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

	DEBUG( "Get first elemet %d\n", prev_entry->lkey );

	SKIPLIST_RLOCK( &(prev_record->row_lock) );
	err = get_record( mem_skiplist_index->heap_space,
			  prev_entry->right_block_no,
			  prev_entry->right_record_num,
			  &return_record_ptr );
	SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	if ( (return_record_ptr)->is_used == 0 )
		return(SKIPLIST_INDEX_ERR_GETL_FAILED);

	if ( err )
		return(err);

	*last_find_entry = prev_entry;
	DEBUG( "Prepare Serach one %ld\n", in->lkey );

	/*
	 * if( mem_skiplist_index->nil != prev_entry &&
	 *  prev_entry->lkey < in->lkey   )
	 * {
	 *              //插入结果集
	 *      if(!ret)
	 *      {
	 *
	 *                              DEBUG("Find one skiplist record in skiplist_space next link!\n");
	 */
	mem_skiplist_entry_t * finded_entry = *last_find_entry;

	if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
	{
		ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
		if ( BASIC_OPS_DELETE == oper_type )
		{
			int err = 0;
			err = mem_skiplist_mvcc_delete( mem_skiplist_index,
							finded_entry,
							Tn /* 本事务ID */
							);
			if ( 0 != err )
			{
				ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
				return(err);
			}
		}
	}
	/*
	 *      }
	 *
	 * }
	 */
/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_L_scanAddr(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 <= 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_long_LE(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得最低层头节点 */
	prev_entry	= mem_skiplist_getlevel_head( mem_skiplist_index, 1 );
	prev_record	= (struct record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

	SKIPLIST_RLOCK( &(prev_record->row_lock) );
	err = get_record( mem_skiplist_index->heap_space,
			  prev_entry->right_block_no,
			  prev_entry->right_record_num,
			  &return_record_ptr );
	SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	if ( (return_record_ptr)->is_used == 0 )
		return(SKIPLIST_INDEX_ERR_GETLE_FAILED);

	if ( err )
		return(err);

	*last_find_entry = prev_entry;
	DEBUG( "Prepare Serach one %ld\n", in->lkey );

/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_LE_scanAddr(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 > 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_long_G(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得对应节点 */
	err = mem_skiplist_search( mem_skiplist_index,
				   in,
				   last_find_entry
				   );

	if ( err )
		return(err);
	return_record_ptr = (struct record_t *) ( (char *) (*last_find_entry) - RECORD_HEAD_SIZE);


	DEBUG( "Find minst element %ld\n", (*last_find_entry)->lkey );

	if ( (*last_find_entry)->lkey > in->lkey )
	{
		mem_skiplist_entry_t *finded_entry = *last_find_entry;
		/* 插入结果集 */
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete( mem_skiplist_index,
									finded_entry,
									Tn /* 本事务ID */
									);
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
						return(err);
					}
				}
			}
		}
	}
/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_G_scanAddr(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 >= 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_long_GE(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret			= 0;
	struct    record_t	* return_record_ptr	= 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得对应节点 */
	err = mem_skiplist_search( mem_skiplist_index,
				   in,
				   last_find_entry
				   );

	if ( err )
		return(err);
	return_record_ptr = (struct record_t *) ( (char *) (*last_find_entry) - RECORD_HEAD_SIZE);


	DEBUG( "Prepare Serach one %ld\n", in->lkey );

	if ( (*last_find_entry)->lkey >= in->lkey )
	{
		mem_skiplist_entry_t *finded_entry = *last_find_entry;
		/* 插入结果集 */
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete( mem_skiplist_index,
									finded_entry,
									Tn /* 本事务ID */
									);
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete err is %d\n", err );
						return(err);
					}
				}
			}
		}
	}
/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_GE_scanAddr(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 < 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_str_L(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得最低层头节点 */
	prev_entry	= mem_skiplist_getlevel_head( mem_skiplist_index, 1 );
	prev_record	= (struct record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

	SKIPLIST_RLOCK( &(prev_record->row_lock) );
	err = get_record( mem_skiplist_index->heap_space,
			  prev_entry->right_block_no,
			  prev_entry->right_record_num,
			  &return_record_ptr );
	SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	if ( (return_record_ptr)->is_used == 0 )
		return(SKIPLIST_INDEX_ERR_GETL_FAILED);

	if ( err )
		return(err);

	*last_find_entry = prev_entry;
	DEBUG( "Prepare Serach one %ld\n", in->lkey );

/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_L_scanAddr_str(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 <= 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_str_LE(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得最低层头节点 */
	prev_entry	= mem_skiplist_getlevel_head( mem_skiplist_index, 1 );
	prev_record	= (struct record_t *) ( (char *) prev_entry - RECORD_HEAD_SIZE);

	SKIPLIST_RLOCK( &(prev_record->row_lock) );
	err = get_record( mem_skiplist_index->heap_space,
			  prev_entry->right_block_no,
			  prev_entry->right_record_num,
			  &return_record_ptr );
	SKIPLIST_RUNLOCK( &(prev_record->row_lock) );
	if ( (return_record_ptr)->is_used == 0 )
		return(SKIPLIST_INDEX_ERR_GETLE_FAILED);

	if ( err )
		return(err);

	*last_find_entry = prev_entry;
	DEBUG( "Prepare Serach one %ld\n", in->lkey );

/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_LE_scanAddr_str(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 > 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_str_G(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得对应节点 */
	err = mem_skiplist_search_str( mem_skiplist_index,
				       in,
				       last_find_entry
				       );

	if ( err )
		return(err);
	return_record_ptr = (struct record_t *) ( (char *) (*last_find_entry) - RECORD_HEAD_SIZE);


	DEBUG( "Prepare Serach one %ld\n", in->lkey );

	if ( strcmp( (*last_find_entry)->ckey, in->ckey ) > 0 )
	{
		mem_skiplist_entry_t *finded_entry = *last_find_entry;

		/* 插入结果集 */
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
									    finded_entry,
									    Tn /* 本事务ID */
									    );
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
						return(err);
					}
				}
			}
		}
	}
/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_G_scanAddr_str(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 扫描所有 >= 某个数的结果集 */

inline int mem_skiplist_index_scanAddr_str_GE(
	mem_table_t *mem_table,
        /* in */ struct mem_skiplist_index_t * mem_skiplist_index,
        /* in */ mem_skiplist_entry_t *in,
	mem_skiplist_entry_t **last_find_entry,
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
/* 1.从最低层开始找 */
	mem_skiplist_entry_t	* prev_entry;
	struct record_t		* prev_record;
	int			err = 0;

	int			ret;
	struct    record_t	* return_record_ptr = 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];


	/* 获得对应节点 */
	err = mem_skiplist_search_str( mem_skiplist_index,
				       in,
				       last_find_entry
				       );

	if ( err )
		return(err);
	return_record_ptr = (struct record_t *) ( (char *) (*last_find_entry) - RECORD_HEAD_SIZE);


	DEBUG( "Prepare Serach one %ld\n", in->lkey );

	if ( strcmp( (*last_find_entry)->ckey, in->ckey ) >= 0 )
	{
		mem_skiplist_entry_t *finded_entry = *last_find_entry;
		/* 插入结果集 */
		if ( !ret )
		{
			DEBUG( "Find one skiplist record in skiplist_space next link!\n" );
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_skiplist_mvcc_delete_str( mem_skiplist_index,
									    finded_entry,
									    Tn /* 本事务ID */
									    );
					if ( 0 != err )
					{
						ERROR( "mem_skiplist_mvcc_delete_str err is %d\n", err );
						return(err);
					}
				}
			}
		}
	}
/* 范围扫入 */
	DEBUG( "return  mem_skiplist_index_L_scanAddr_long,last_find_entry is %0x \n", *last_find_entry );
	return(mem_skiplist_GE_scanAddr_str(
		       mem_table,
		       mem_skiplist_index,
		       *last_find_entry,
		       in,
		       last_find_entry,
		       Tn,
		       finded_Addr,
		       ret_list, /* 原始结果集 */
		       oper_type
		       ) );
}


/* 插入一个整型索引的数据,保证每个桶相同的 val 相邻 */
inline int mem_hash_index_scanAddr_long(
	mem_table_t *mem_table,
        /* in */ struct mem_hash_index_t * mem_hash_index,
        /* in */ unsigned long key,
        /* in */ int (*hash_fun)( unsigned long, /*返回哈希表的行号*/ struct  mem_block_t *, unsigned long      * ),
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	if ( NULL == hash_fun )
		return(INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL);
	DEBUG( "Enter mem_hash_index_scan_long(),key = %ld,finded_Addr.size()= %ld ------------ { \n", key,finded_Addr.size() );

	/*
	 * 1 array_space 不存在数据，则存入数据
	 * 2 array_space 存在数据，link_space 不存在数据，插入link_space
	 * 3 存在数据，link_space  存在数据，插入link_space最近的地方
	 */
	unsigned long			record_num_temp		= 0;
	long				block_no_temp		= 0;
	long				mem_table_no		= 0;
	struct    record_t		* record_ptr		= 0;
	struct    record_t		* return_record_ptr	= 0;
	struct  mem_hash_entry_t	* array_space_entry	= 0;
	long				link_block_no;

	char buf[mem_table->record_size - RECORD_HEAD_SIZE];


	int	ret;
	int	ret2;
	ret = mem_hash_index_select_long(
		mem_hash_index,
		key,
		hash_fun,
	        /* out */ &block_no_temp,
	        /* out */ &record_num_temp,
	        /* out */ &record_ptr,       /* IF FOUND ,RETURN FOUNDED RECORD   */
		&array_space_entry,
		&mem_table_no
		);
	struct  mem_hash_entry_t	* entry		= (struct mem_hash_entry_t *) ( (char *) (record_ptr) + RECORD_HEAD_SIZE);
	struct  mem_hash_entry_t	* finded_entry	= entry;
	int				err;
	DEBUG( "switch(ret)\n" );

	switch ( ret )
	{
	/* 连续空间内没找到，就不存在 */
	case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
	{
		return(ret);
		break;
	}
	/* 连续空间内找到 */
	case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
		/*
		 * 通过索引获得最终的数据
		 * 通过索引获得最终的数据
		 */
		ret2 = get_record( mem_table, entry->block_no, entry->record_num, &return_record_ptr );
		if ( !ret2 )
		{
			DEBUG( "Find one hash record in array_space!\n" );
			if( finded_Addr.empty() )CPP_DEBUG<<"finded_Addr is empty"<<std::endl;
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				DEBUG( "ret_list.insert( index_Addr(%ld,%ld) );!\n", finded_entry->block_no, finded_entry->record_num  );
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int					err			= 0;
					struct record_t				** record_ptr_temp	= NULL;
					struct mem_hash_index_input_long	input;
					input.key		= key;
					input.hash_fun		= hash_fun;
					input.block_no		= finded_entry->block_no;
					input.record_num	= finded_entry->record_num;

					err = __mem_hash_index_mvcc_del_l(
						mem_hash_index,
						&input,
						record_ptr_temp,
						Tn,        /* 事务ID */
						1
						);
					if ( 0 != err )
					{
						ERROR( "__mem_hash_index_mvcc_del_l err is %d\n  ------------ }{  ", err );
						return(err);
					}
				}
			}
		}
	/* 链接空间内找到 */
	case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
	{
		DEBUG( "case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:\n" );
		if ( ret != SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND )
		{
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int					err			= 0;
					struct record_t				** record_ptr_temp	= NULL;
					struct mem_hash_index_input_long	input;
					input.key		= key;
					input.hash_fun		= hash_fun;
					input.block_no		= finded_entry->block_no;
					input.record_num	= finded_entry->record_num;

					err = __mem_hash_index_mvcc_del_l(
						mem_hash_index,
						&input,
						record_ptr_temp,
						Tn,        /* 事务ID */
						1
						);
					if ( 0 != err )
					{
						ERROR( "__mem_hash_index_mvcc_del_l err is %d  ------------ } \n", err );
						return(err);
					}
				}
			}
		}
		while ( true )
		{
			link_block_no = ( (struct mem_hash_entry_t *) ( ( (char *) (record_ptr) + RECORD_HEAD_SIZE) ) )->link_block_no;
			DEBUG( "link_block_no is %d !\n", link_block_no );

			if ( link_block_no == -1 )
				break;
			ret2 = get_record(
				mem_hash_index->linked_space,
				link_block_no,
				( (struct mem_hash_entry_t *) ( ( (char *) (record_ptr) + RECORD_HEAD_SIZE) ) )->link_record_num,
				&record_ptr
				);
			if ( !record_ptr || record_ptr->is_used == 0 )
				break;

			row_rlock( &(record_ptr->row_lock) );                                                   /*上行锁 */
			entry = (struct mem_hash_entry_t *) ( (char *) (record_ptr) + RECORD_HEAD_SIZE);        /* 相等就一直找下去 */
			if ( entry->hash_lkey == key )
			{
				/* 通过索引获得最终的数据 */
				ret2 = get_record( mem_table, entry->block_no, entry->record_num, &return_record_ptr );
				if ( !ret2 )
				{
					if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
					{
						ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
						if ( BASIC_OPS_DELETE == oper_type )
						{
							int					err			= 0;
							struct record_t				** record_ptr_temp	= NULL;
							struct mem_hash_index_input_long	input;
							input.key		= key;
							input.hash_fun		= hash_fun;
							input.block_no		= finded_entry->block_no;
							input.record_num	= finded_entry->record_num;

							err = __mem_hash_index_mvcc_del_l(
								mem_hash_index,
								&input,
								record_ptr_temp,
								Tn, /* 事务ID */
								1
								);
							if ( 0 != err )
							{
								ERROR( "__mem_hash_index_mvcc_del_l err is %d  ------------ } \n", err );
								return(err);
							}
						}
					}
				}
			}else  {                                        /* 否则就不找了 */
				row_runlock( &(record_ptr->row_lock) ); /* 解行锁 */
				break;
			}
			row_runlock( &(record_ptr->row_lock) );         /* 解行锁 */
		}
		break;
	}
	/* 链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置 */
	case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
	{
		return(ret);
		break;
	}
	default:
		return(ret);
	}
	DEBUG( "mem_hash_index_scan_long() END  ------------ } \n" );

	return(0);
}


/* 插入一个整型索引的数据,保证每个桶相同的 val 相邻 */
inline int mem_hash_index_scanAddr_str(
	mem_table_t *mem_table,
        /* in */ struct mem_hash_index_t * mem_hash_index,
        /* in */ char                    * key,
        /* in */ int (*hash_fun)( char *, struct  mem_block_t *, /*杩斿洖鍝堝笇琛ㄧ殑琛屽彿*/ unsigned long      * ),
        /* in */ unsigned long long Tn,         /* 当前事务ID */
	finded_Addr_t & finded_Addr,
	finded_Addr_t & ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN          /* 操作类型默认是扫描 */
	)
{
	if ( NULL == hash_fun )
		return(INSERT_MEM_HASH_INDEX_ERR_HASH_FUN_IS_NULL);
	DEBUG( "Enter mem_hash_index_scan_str(),key = %s\n", key );

	/*
	 * 1 array_space 不存在数据，则存入数据
	 * 2 array_space 存在数据，link_space 不存在数据，插入link_space
	 * 3 存在数据，link_space  存在数据，插入link_space最近的地方
	 */
	unsigned long			record_num_temp		= 0;
	long				block_no_temp		= 0;
	long				mem_table_no		= 0;
	struct    record_t		* record_ptr		= 0;
	struct  mem_hash_entry_t	* array_space_entry	= 0;
	long				link_block_no;


	char		buf[mem_table->record_size - RECORD_HEAD_SIZE];
	struct record_t *return_record_ptr = 0;

	int	ret;
	int	ret2;
	ret = mem_hash_index_select_str(
		mem_hash_index,
		key,
		hash_fun,
	        /* out */ &block_no_temp,
	        /* out */ &record_num_temp,
	        /* out */ &record_ptr,       /* IF FOUND ,RETURN FOUNDED RECORD   */
		&array_space_entry,
		&mem_table_no
		);
	struct  mem_hash_entry_t	* entry		= (struct mem_hash_entry_t *) ( (char *) (record_ptr) + RECORD_HEAD_SIZE);
	struct  mem_hash_entry_t	* finded_entry	= entry;

	int err;
	DEBUG( "switch(ret)\n" );

	switch ( ret )
	{
	/* 连续空间内没找到，就不存在 */
	case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_NOT_FOUND:
	{
		return(ret);
		break;
	}
	/* 连续空间内找到 */
	case SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND:
		/*
		 * 通过索引获得最终的数据
		 * 通过索引获得最终的数据
		 */
		ret2 = get_record( mem_table, entry->block_no, entry->record_num, &return_record_ptr );
		if ( !ret2 )
		{
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int				err			= 0;
					struct record_t			** record_ptr_temp	= NULL;
					struct mem_hash_index_input_str input;
					strcpy( input.key, key );
					input.hash_fun		= hash_fun;
					input.block_no		= finded_entry->block_no;
					input.record_num	= finded_entry->record_num;
					err			= __mem_hash_index_mvcc_del_str(
						mem_hash_index,
						&input,
						record_ptr_temp,
						Tn, /* 本事务ID */
						1
						);
					if ( 0 != err )
					{
						ERROR( "__mem_hash_index_mvcc_del_str err is %d\n", err );
						return(err);
					}
				}
			}
		}
	/* 链接空间内找到 */
	case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:
	{
		DEBUG( "case SELECT_MEM_HASH_INDEX_LINKED_SPACE_FOUND:\n" );
		if ( ret != SELECT_MEM_HASH_INDEX_ARRAY_SPACE_FOUND )
		{
			if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
			{
				ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
				if ( BASIC_OPS_DELETE == oper_type )
				{
					int				err			= 0;
					struct record_t			** record_ptr_temp	= NULL;
					struct mem_hash_index_input_str input;
					strcpy( input.key, key );
					input.hash_fun		= hash_fun;
					input.block_no		= finded_entry->block_no;
					input.record_num	= finded_entry->record_num;
					err			= __mem_hash_index_mvcc_del_str(
						mem_hash_index,
						&input,
						record_ptr_temp,
						Tn, /* 本事务ID */
						1
						);
					if ( 0 != err )
					{
						ERROR( "__mem_hash_index_mvcc_del_str err is %d\n", err );
						return(err);
					}
				}
			}
		}
		while ( true )
		{
			link_block_no = ( (struct mem_hash_entry_t *) ( ( (char *) (record_ptr) + RECORD_HEAD_SIZE) ) )->link_block_no;
			DEBUG( "link_block_no is %d !\n", link_block_no );

			if ( link_block_no == -1 )
				break;
			ret2 = get_record(
				mem_hash_index->linked_space,
				link_block_no,
				( (struct mem_hash_entry_t *) ( ( (char *) (record_ptr) + RECORD_HEAD_SIZE) ) )->link_record_num,
				&record_ptr
				);
			if ( !record_ptr || record_ptr->is_used == 0 )
				break;

			row_rlock( &(record_ptr->row_lock) );                                                   /*上行锁 */
			entry = (struct mem_hash_entry_t *) ( (char *) (record_ptr) + RECORD_HEAD_SIZE);        /* 相等就一直找下去 */
			if ( strcmp( entry->hash_ckey, key ) == 0 )
			{
				/* 通过索引获得最终的数据 */
				ret2 = get_record( mem_table, entry->block_no, entry->record_num, &return_record_ptr );
				if ( !ret2 )
				{
					if ( (!finded_Addr.empty() && find_Addr( finded_Addr, finded_entry->block_no, finded_entry->record_num ) ) || (finded_Addr.empty() ) )
					{
						ret_list.insert( index_Addr( finded_entry->block_no, finded_entry->record_num ) );
						if ( BASIC_OPS_DELETE == oper_type )
						{
							int				err			= 0;
							struct record_t			** record_ptr_temp	= NULL;
							struct mem_hash_index_input_str input;
							strcpy( input.key, key );
							input.hash_fun		= hash_fun;
							input.block_no		= finded_entry->block_no;
							input.record_num	= finded_entry->record_num;
							err			= __mem_hash_index_mvcc_del_str(
								mem_hash_index,
								&input,
								record_ptr_temp,
								Tn, /* 本事务ID */
								1
								);
							if ( 0 != err )
							{
								ERROR( "__mem_hash_index_mvcc_del_str err is %d\n", err );
								return(err);
							}
						}
					}
				}
			}else  {                                        /* 否则就不找了 */
				row_runlock( &(record_ptr->row_lock) ); /* 解行锁 */
				break;
			}
			row_runlock( &(record_ptr->row_lock) );         /* 解行锁 */
		}
		break;
	}
	/* 链接空间内没找到，就插入到连续空间后面,array_space_entry 此时指向对应连续空间的位置 */
	case SELECT_MEM_HASH_INDEX_LINKED_SPACE_NOT_FOUND:
	{
		return(ret);
		break;
	}
	default:
		return(ret);
	}
	DEBUG( "mem_hash_index_scan_str() END\n" );
	return(0);
}


template<typename record_type >
inline int merg_index_result(
	mem_table_t *mem_table,
	finded_Addr_t & finded_Addr,
	unsigned long long Tn,                          /* 当前事务ID */
	std::list<record_type>* ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN                  /* 操作类型默认是扫描 */
	)
{
	DEBUG( "merg_index_result() start!\n" );
	int			ret			= 0;
	struct    record_t	* return_record_ptr	= 0;
	char			buf[mem_table->record_size - RECORD_HEAD_SIZE];
	record_type		return_record;
	return_record.set_row_size( mem_table->record_size - RECORD_HEAD_SIZE );
	return_record.allocate( mem_table->record_size - RECORD_HEAD_SIZE );


	for ( auto &v : finded_Addr )
	{
		ret = get_record( mem_table, v.block_no, v.record_num, &return_record_ptr );
		if ( !mem_mvcc_read_record( mem_table, return_record_ptr, (char *) buf, Tn ) )
		{
			if ( BASIC_OPS_SCAN == oper_type )
			{
				memcpy( return_record.get_data(), buf, mem_table->record_size - RECORD_HEAD_SIZE );
				DEBUG( "Find one skiplist record in skiplist_space!\n" );
				ret_list->emplace_back( return_record );
			}

			if ( BASIC_OPS_DELETE == oper_type )
			{
				int err = 0;
				err = mem_mvcc_delete_record( mem_table,
							      return_record_ptr,
							      Tn /* 本事务ID */
							      );
				if ( 0 != err )
				{
					ERROR( "mem_mvcc_delete_record err is %d\n", err );
					return(err);
				}
			}
		}
	}
}


template<typename record_type, typename field_list_type >
inline int merg_index_result_with_prolist_and_conlist(
	mem_table_t *mem_table,
	finded_Addr_t & finded_Addr,
	compare_list*com_list,                          /* 比较函数链 */
	field_list_type & field_list,                   /* 原始投影字段列表 */
	unsigned long long Tn,                          /* 当前事务ID */
	std::list<record_type>* ret_list,               /* 原始结果集 */
	int oper_type = BASIC_OPS_SCAN                  /* 操作类型默认是扫描 */
	)
{
	DEBUG( "merg_index_result() start! ----------------- { \n" );
	int			ret			= 0;
	struct    record_t	* return_record_ptr	= 0;

	/* 条件字段需要的变量 */
	int		j		= -1;
	int		is_ok		= 0;
	compare_list	* com_list_iter = com_list;

	struct field_t	*fields_table	= mem_table->config.fields_table;
	int		field_used_num	= 0;
	field_used_num = mem_table->config.field_used_num;

	/* 抽取字段需要的变量 */

	/* 构造抽取字段列表 */
	std::list<field_t> pro_fields;
	/* 抽取字段总长度 */
	size_t	pro_size = 0;
	int	k;
	
	DEBUG( "field_list.size() is %d \n",field_list.size() );

	for ( auto &one : field_list )
	{
		k = get_field_index( const_cast<char *>(one.c_str() ), mem_table );
		DEBUG( "get_field_index()= %d \n",k );

		if ( k >= 0 && k < field_used_num )
		{
			/* field = ( field_type * )( (char *)(record_ptr) + RECORD_HEAD_SIZE + fields_table[k].field_dis ); */
			pro_fields.push_back( fields_table[k] );
			pro_size += fields_table[k].field_size;
		}
	}

	/*  */
	char buf[mem_table->record_size - RECORD_HEAD_SIZE];

	record_type return_record;
	return_record.set_row_size( pro_size );
	return_record.allocate( pro_size );

	DEBUG( "finded_Addr.size() = %d \n",finded_Addr.size() );

	for ( auto &v : finded_Addr )
	{
		DEBUG("for(auto &v : finded_Addr )\n");
		ret = get_record( mem_table, v.block_no, v.record_num, &return_record_ptr );
		if ( !mem_mvcc_read_record( mem_table, return_record_ptr, (char *) buf, Tn ) )
		{
			/* 已经删除的行不处理 */
			if ( return_record_ptr->is_used != 1 )
				continue;
			DEBUG( "return_record_ptr addr is %0x,return_record_ptr->is_used = %d\n", return_record_ptr, return_record_ptr->is_used );

			is_ok = 1;
			while ( com_list_iter )
			{
				/* 获得字段在字段表中的排序位置 */
				j	= -1;
				j	= get_field_index( com_list_iter->field_name, mem_table /*,field*/ );
				DEBUG( "get_field_index is %d \n", j );
				/* 处理每一行记录 */
				if ( -1 != j && field_used_num != j ) /* 条件判断 */
				{
					int field_type_nr = fields_table[j].field_type;
					/*
					 * int const field_type_const_nr = const_cast<int >(field_type_nr);
					 * auto field = get_field_by_index<field_type_nr>::get(mem_table, record_ptr, j,field_type_nr ) ;
					 */
					int get_field_ret = get_field_by_index_help( com_list_iter, mem_table, return_record_ptr, j, field_type_nr );
					DEBUG( "get_field_ret is %d \n", get_field_ret );

					if ( get_field_ret != 0 )
					{
						is_ok = 0;
						break;
					}
				}

				if ( com_list_iter )
					com_list_iter = com_list_iter->next;
			}
			com_list_iter = com_list;

			if ( is_ok ) /*!mem_table_read_record(mem_table , record_ptr, (char *)buf )*/
			{
				if ( BASIC_OPS_SCAN == oper_type )
				{
					size_t pos = 0;
					for ( auto &one_field : pro_fields )
					{
						memcpy( return_record.get_data() + pos, buf + one_field.field_dis, one_field.field_size );
						pos += one_field.field_size;
					}

					DEBUG( "Get one record!\n" );
					ret_list->emplace_back( return_record );
				}

				if ( BASIC_OPS_DELETE == oper_type )
				{
					int err = 0;
					err = mem_mvcc_delete_record( mem_table,
								      return_record_ptr,
								      Tn /* 本事务ID */
								      );
					if ( 0 != err )
					{
						ERROR( "mem_mvcc_delete_record err is %d\n", err );
						return(err);
					}
				}
			}
		}
	}
	
  DEBUG( "merg_index_result() end!  ----------------- } \n" );
  return 0;
}


#endif