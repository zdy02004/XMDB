#include "../../mem_sequence.h"
#include"../util/log/log_util.h"



int main(int arc,char * arcvp[])
{
	init_mem_seq_manager();
	load_seq_cur("./seq_data.dat");
	
	DEBUG("test index no\n");
	
	long seq_no;
	allocate_seq_no(&seq_no);
DEBUG("allocate a seq_no is %d\n",seq_no);

	unsigned  long long  val;
	int i=0;
	for(;i<3;++i)
	{
	get_seqval_by_no(seq_no,&val);
	DEBUG("test seq[%ld] is %ld\n",seq_no,val);
  }
	get_seqval_by_no(1,&val);
	DEBUG("test seq[1] is %ld\n",val);
	save_seq_cur("./seq_data.dat");
  dest_mem_seq_manager();
//	



	return 0;
}