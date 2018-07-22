#ifndef _LOG_UTIL_
#define _LOG_UTIL_



#include <stdio.h>

#include <pthread.h>
#define __DEBUG__  


#ifdef __cplusplus
extern "C" {

#endif

#include <sys/time.h>
char now_buffer[50] = { 0 };

char * GetTime()
{
    #ifdef _WIN32
     
        SYSTEMTIME st;
        GetLocalTime(&st);
       sprintf(now_buffer,"%d-%d-%d %d:%d:%d",st.wYear, st.wMonth ,st.wDay,st.wHour ,st.wMinute,st.wSecond);  
          return now_buffer;
    #else
        struct timeval tv;
        struct tm      tm;
        size_t         len = 28;
 
        gettimeofday(&tv, NULL);
        localtime_r(&tv.tv_sec, &tm);
        strftime(now_buffer, len, "%Y-%m-%d %H:%M:%S", &tm);
        len = strlen(now_buffer);
        sprintf(now_buffer + len, ".%06.6d,", (int)(tv.tv_usec));
 
        return now_buffer;
    #endif
    return 0;
}


int GetTimeForNAME(char *buffer)
{
        struct timeval tv;
        struct tm      tm;
        size_t         len = 28;
 
        char buf[64];
        gettimeofday(&tv, NULL);
        localtime_r(&tv.tv_sec, &tm);
        strftime(buf, len, "%Y%m%d%H%M%S", &tm);
        sprintf(buf + 14, ".%06.6d", (int)(tv.tv_usec));
        strcat(buffer,buf);

    return 0;
}
#define IMPORTANT_INFO(format,...) printf("%s [ " __FILE__" ,%s () Line: %05d ,tid: %ld ]:>>>IMPORTANT_INFO " format "",GetTime(),__FUNCTION__, __LINE__, pthread_self() ,##__VA_ARGS__)  
#define ERROR(format,...) printf("%s [" __FILE__ ",%s () Line: %05d ,tid: %ld ]:>>>>Err " format "",GetTime(),__FUNCTION__, __LINE__,pthread_self() , ##__VA_ARGS__)  

#ifdef __DEBUG__  
#define DEBUG(format,...) printf("%s [" __FILE__ ",%s () Line: %05d ,tid: %ld ]: " format "",GetTime(),__FUNCTION__, __LINE__,pthread_self(), ##__VA_ARGS__)  

#ifdef __cplusplus
#define CPP_DEBUG std::cout<<GetTime()<<" [ " <<__FILE__<<","<<__FUNCTION__<<" () Line: "<<__LINE__<<" ,tid: "<<pthread_self()<<" ] "
#define CPP_ERROR std::cout<<GetTime()<<" [ " <<__FILE__<<","<<__FUNCTION__<<" () Line: "<<__LINE__<<" ,tid: "<<pthread_self()<<" ]:>>>>Err "
#endif 

#else  
#define DEBUG(format,...) 
#ifdef __cplusplus
typdedef struct null_log
{
	template<class T>
	null_log& operator << (T a)
	{
		return *this;
	}
}null_log;
#define CPP_DEBUG null_log
#endif 
//#define ERROR(format,...) printf("%s["__FILE__",%s() Line:%05d]:>>>>Err  " format "",GetTime(),__FUNCTION__, __LINE__, ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) printf("%s["__FILE__",%s() Line:%05d]:>>>>IMPORTANT_INFO  " format "",GetTime(),__FUNCTION__, __LINE__, ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) 


#endif  

#ifdef __cplusplus

}

#endif
#endif  
