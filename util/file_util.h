#ifndef FILE_UTIL_T
#define FILE_UTIL_T

#ifdef __cplusplus

extern "C" {

#endif


#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  
#include<string.h>
#include <sys/stat.h>
#include "log/log_util.h"

#define NO_FILE_FOUNDED 				 430010
#define NOT_FOUND_WANTED_FILE    430011
#define ERR_INPUT_ARRAY_IS_NULL  430012
#define ERR_INPUT_KEY_IS_NULL  	 430013

typedef struct dirent_list 
{	
struct dirent 			* dir_entry;	
struct dirent_list  * next;

}dirent_list;

#define DIRENT_LIST_SIZE sizeof(dirent_list)
#define DIRENT_SIZE sizeof(struct dirent)

int file_cmp_str(const void *a, const void *b) 
{ 
     return strcmp(((struct dirent *)a)->d_name,((struct dirent *)b)->d_name);  //���� 
     //return(*(int *)b-*(int *)a); //���� 
}

//����һ���ļ����µ������ļ���ɵ��б�
//�����ֵ�������
int get_dir_file_list(const char *path,
											long* file_count,
											struct dirent ** dirent_array
											//dirent_list ** dlist
											)  
{
	  DIR       *dir;
    struct    dirent    *ptr;
    struct stat info;
    *file_count = 0;
    dirent_list * dl = (struct dirent_list *)malloc(DIRENT_LIST_SIZE);
    dirent_list * pre = dl;
    char pbuf[512];  
    
    dir = opendir(path);
    while((ptr = readdir(dir)) != NULL)
    {
    	snprintf(pbuf, 512, "%s/%s", path, ptr->d_name);  
    	
    	 //�õ��ļ���Ϣ  
      lstat(pbuf, &info);  

    	//stat(ptr->d_name,&info);
    	//DEBUG("Travle: %s,S_ISDIR : %d \n",ptr->d_name,S_ISDIR(info.st_mode));
      if(S_ISDIR(info.st_mode))continue;
    	if(0 == *file_count)
    		{
    			dl->dir_entry = ptr;
    		}
    		else
    			{
    				dirent_list * dl_entry = (dirent_list *)malloc(DIRENT_LIST_SIZE);
    				dl_entry->dir_entry = ptr;
    			  pre->next = dl_entry;
    			  pre = dl_entry;
    			  
    			}
    	++(*file_count);
    }
    
    if( 0 == (*file_count) )
    	{
    		closedir(dir);
    		free(dl);
    		IMPORTANT_INFO("NO_FILE_FOUNDED\n");
    		return NO_FILE_FOUNDED;
    	}
    
    struct dirent 	* dir_entry = (struct dirent 	*)malloc(DIRENT_SIZE*(*file_count));
    
    dirent_list * list = dl;
    dirent_list * pre_ = list;
    long i = 0;
    for(;i<(*file_count);++i)
    {
    	memcpy(&(dir_entry[i]),dl->dir_entry,DIRENT_SIZE);
    	pre_ = dl;
    	dl = dl->next;
    	free(pre_);
    }
        
		
		*dirent_array = dir_entry;
		 qsort(dir_entry,(*file_count),DIRENT_SIZE,file_cmp_str);
		 
		 
     closedir(dir);
	
	   return 0;
}

//���ļ�ǰ׺���ˣ��������ļ�ǰ׺�Ĺ��˵�
int dirent_list_filter_head(struct dirent** dir_entry,long *entry_size,
														char * cmp_str,int n)
{
  if(NULL == dir_entry)
  	{
				ERROR("ERR_INPUT_ARRAY_IS_NULL\n");
	  		return ERR_INPUT_ARRAY_IS_NULL;  	
	  }
	char buf[n+1];
	long i = 0;
	long ret = *entry_size;
	//DEBUG("*entry_size is %d\n",ret);
	for(; i<(*entry_size);++i)
	{
		strncpy(buf,(*dir_entry)[i].d_name,n);
		if(strcmp(buf,cmp_str))
			{
						DEBUG("%s is filted\n",buf );
						memset(&((*dir_entry)[i]),0,DIRENT_SIZE);
						--ret;
			}
	}
	//DEBUG("*ret is %d\n",ret);
	struct dirent* ret_entry = (struct dirent*)malloc(DIRENT_SIZE*ret);
	long j = 0;
  for(i = 0;i<(*entry_size);++i)
	{
      if ( *(char *)(&((*dir_entry)[i]))== 0 )continue;
      memcpy(&(ret_entry[j++]),&((*dir_entry)[i]),DIRENT_SIZE);
  }
  
  free(*dir_entry);
  *dir_entry = ret_entry;
  *entry_size = ret;
	return 0;
}

/*
Ѱ�����������У���С�����������λ��
ʹ���۰����
*/
int dirent_array_search_min(struct dirent array[], long n, char * v,long * pos)  
{  
	  if(NULL == array)
	  	{
	  		ERROR("ERR_INPUT_ARRAY_IS_NULL\n");
	  		return ERR_INPUT_ARRAY_IS_NULL;
	  	}
	  	 if(NULL == v)
	  	{
	  		ERROR("ERR_INPUT_KEY_IS_NULL\n");
				return ERR_INPUT_KEY_IS_NULL;
	  	}	
	  	
	  	
    long left, right, middle;  
    left = -1, right = n;  
    while (left + 1 != right)  
    {  
        middle = left + (right - left) / 2;  
        if ( strcmp(array[middle].d_name , v)<0 )  
        {  
            left = middle;  
        }  
        else  
        {  
            right = middle;  
        }  
    }  
  DEBUG(" right is %d,n is %d \n",right,n);
    if( (right >= n || strcmp(array[right].d_name,v)< 0  )  && right!=0)
    {  
        *pos = -1;   //�޸�2014-9-9.������ô���ɱ�־����find=false;
        IMPORTANT_INFO("NOT_FOUND_WANTED_FILE\n");
        return  NOT_FOUND_WANTED_FILE;
    }  
    *pos = right;
    return 0;  
}  


#ifdef __cplusplus

}

#endif

#endif 