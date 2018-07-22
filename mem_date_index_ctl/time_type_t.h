#ifndef MEM_TIME_T
#define MEM_TIME_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>  
#include <time.h>    
#include <stdlib.h>    
#include <string.h>  
//��������
#define TIME_ERR_STR_IS_NULL        21001

//ϵͳ֧�ֵ����ʱ�� 2038��
#define MAX_TIME  2147483647


//���ϵͳʱ��
inline time_t get_systime()
{
	return time(NULL);
}

//�ַ���ת time_t
inline time_t  str_to_time(char * szTime)  
{  
    struct tm tm_;    
    time_t t_;    
    strptime(szTime, "%Y-%m-%d %H:%M:%S", &tm_); //���ַ���ת��Ϊtmʱ��    
    tm_.tm_isdst = -1;    
    t_  = mktime(&tm_);                         //��tmʱ��ת��Ϊ��ʱ��    
    //t_ += 3600;                                //������3600   
    return t_;  
}  

//�ַ���ת time_t
inline time_t  str_to_time2(char * szTime)  
{  
    struct tm tm_;    
    time_t t_;    
    strptime(szTime, "%Y%m%d%H%M%S", &tm_); //���ַ���ת��Ϊtmʱ��    
    tm_.tm_isdst = -1;    
    t_  = mktime(&tm_);                         //��tmʱ��ת��Ϊ��ʱ��    
    //t_ += 3600;                                //������3600   
    return t_;  
}  

//time_t ת �ַ���
inline int time_to_str(time_t t,char * str)
{
if(0 == str)return TIME_ERR_STR_IS_NULL;
        char szBuf[64] = {0};  
        struct tm  sttm;  
        sttm = *localtime(&t);//���ʱ��    
        strftime(szBuf, 64, "%Y%m%d%H%M%S", &sttm);    
return 0;
}

#ifdef __cplusplus

}

#endif

#endif 