#include "../file_util.h"
#include "../../mem_date_index_ctl/mem_transaction.h"

int main()  
{  
	struct dirent * dirent_array = NULL;
	char * path ="../";
	long file_count = 0;
	char * cmp_str ="redo_index";
	
	if( NO_FILE_FOUNDED != get_dir_file_list(path, &file_count,&dirent_array))
		{
			dirent_list_filter_head(&dirent_array,&file_count,
														cmp_str,strlen(cmp_str));
			
			long i = 0;
			for(;i<file_count;++i)
			{
				DEBUG(" %s \n",dirent_array[i].d_name);
			}
			
		}
	long ret_pos = 0;
	char * start_str ="redo_index_20161206221236.104788";
	dirent_array_search_min(dirent_array, file_count, start_str,&ret_pos);
  //由于恢复的时间可能位于上一个文件的尾部，所以 ret_pos 要减一
	
	DEBUG("ret_pos = %d \n",--ret_pos);
	redo_file_redo_index(path,dirent_array[ret_pos].d_name,str_to_time2("20161206221236"));
	
	if( NULL != dirent_array)	free (dirent_array);
	return 0;
}