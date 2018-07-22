#ifndef MEM_TIME_T
#define MEM_TIME_T

#ifdef __cplusplus

extern "C" {

#endif

#include <stdio.h>  
#include <time.h>    
#include <stdlib.h>    
#include <string.h>  
//错误类型
#define TIME_ERR_STR_IS_NULL        21001

//系统支持的最大时间 2038年
#define MAX_TIME  2147483647


//获得系统时间
inline time_t get_systime()
{
	return time(NULL);
}

//字符串转 time_t
inline time_t  str_to_time(char * szTime)  
{  
    struct tm tm_;    
    time_t t_;    
    strptime(szTime, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间    
    tm_.tm_isdst = -1;    
    t_  = mktime(&tm_);                         //将tm时间转换为秒时间    
    //t_ += 3600;                                //秒数加3600   
    return t_;  
}  

//字符串转 time_t
inline time_t  str_to_time2(char * szTime)  
{  
    struct tm tm_;    
    time_t t_;    
    strptime(szTime, "%Y%m%d%H%M%S", &tm_); //将字符串转换为tm时间    
    tm_.tm_isdst = -1;    
    t_  = mktime(&tm_);                         //将tm时间转换为秒时间    
    //t_ += 3600;                                //秒数加3600   
    return t_;  
}  

//time_t 转 字符串
inline int time_to_str(time_t t,char * str)
{
if(0 == str)return TIME_ERR_STR_IS_NULL;
        char szBuf[64] = {0};  
        struct tm  sttm;  
        sttm = *localtime(&t);//输出时间    
        strftime(szBuf, 64, "%Y%m%d%H%M%S", &sttm);    
return 0;
}

#ifdef __cplusplus

}

#endif

#endif 