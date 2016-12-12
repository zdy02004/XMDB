#include <stdio.h>
#include "cJSON.h"

/*
 * 作者：搁浅的贝
 * 邮箱：1163925944＠qq.com
 * 编译命令：
 * 	gcc demo.c cJSON.c -g -lm -o demo 

 测试JSON格式
 * 
{
        "name": "邝东宇",
        "school":       "CSDN大学",
        "height":       1.750000,
        "age":  22,
        "details":      {
                "a":    null,
                "b":    false,
                "c":    "***********",
                "d":    true,
                "e":    [1, 2, 3, 4, 5, 6],
                "f":    ["111", "222", "333", "444", "555", "666"]
        },
        "skills":       ["Linux", "服务端", "Java", 26]
}

 */
int make_json();
char* filename="json.txt";

int main()
{
		make_json();

		parse_json();
}
int parse_json()
{
	FILE* fp;
	char data[1024]={0};
	fp=fopen(filename,"r");
	if(fp==NULL)
		return -1;
	fread(data,sizeof(data),1,fp);
	
	cJSON* root,*item;
	root=cJSON_Parse(data);
	
	item=cJSON_GetObjectItem(root,"name");
	if(item) puts(item->valuestring);
	puts(item->string);
	item=cJSON_GetObjectItem(root,"age");
	if(item) printf("%d\n",item->valueint);
	item=cJSON_GetObjectItem(root,"details");
	item=cJSON_GetObjectItem(root,"skills");
	if(item)
	{
		int i;
		int count=cJSON_GetArraySize(item);
		for(i=0;i<count-1;i++)
		{
			cJSON* t=cJSON_GetArrayItem(item,i);
			puts(t->valuestring);
		}
	}
}


int make_json()
{
	cJSON* root, *detail, *array;
	
	root=cJSON_CreateObject();
	detail=cJSON_CreateObject();
	array=cJSON_CreateArray();
	
	if(root==NULL || detail==NULL || array==NULL)
	{
		printf("Error\n");
		return -1;
	}
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("邝东宇"));	//添加字符串或者对象
	cJSON_AddStringToObject(root,"school","CSDN大学");
	cJSON_AddItemToObject(root,"height",cJSON_CreateNumber(1.75));
	cJSON_AddNumberToObject(root, "age",22);	//添加数字

	//嵌套对象
	cJSON_AddItemToObject(root,"details",detail);	
	cJSON_AddNullToObject(detail,"a");
	cJSON_AddFalseToObject(detail,"b");
	cJSON_AddStringToObject(detail,"c","***********");
	cJSON_AddBoolToObject(detail,"d",8);
	int tt[6]={1,2,3,4,5,6};
	char* mm[6]={"111","222","333","444","555","666"}; 
	cJSON_AddItemToObject(detail,"e",cJSON_CreateIntArray(tt,6));
	cJSON_AddItemToObject(detail,"f",cJSON_CreateStringArray(mm,6));
	//嵌套数组
	cJSON_AddItemToObject(root,"skills",array);
	cJSON_AddItemToArray(array,cJSON_CreateString("Linux"));
	cJSON_AddItemToArray(array,cJSON_CreateString("服务端"));
	cJSON_AddItemToArray(array,cJSON_CreateString("Java"));
	cJSON_AddItemToArray(array,cJSON_CreateNumber(26));
	
	puts(cJSON_Print(root));
	cJSON_Delete(root);
	
	printf("MakeJson END.............\n\n");
}
