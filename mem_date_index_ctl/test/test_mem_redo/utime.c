#include "../../mem_transaction.h"
#include "../../mem_index_no_manager.h"

int main(int arcv,char * arc[])
{
	printf("main begin at %s\n",GetTime());
	volatile static int i = 0;
	for(;i<1000*1000;++i);
	printf("main  end  at %s\n",GetTime());
	return 0;
}
