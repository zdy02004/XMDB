#ifndef _LOG_UTIL_
#define _LOG_UTIL_



#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define TICK \
   struct timeval __tv1;\
   gettimeofday(&__tv1, NULL);
   

#define TOCK \
  struct timeval __tv2;\
   gettimeofday(&__tv2, NULL);\
   if(__tv1.tv_sec == __tv2.tv_sec)printf("%ld us \n", __tv2.tv_usec-__tv1.tv_usec );\
   	else\
   printf(" %ld us \n",  __tv2.tv_usec + (__tv2.tv_sec - __tv1.tv_sec )*1000000 - __tv1.tv_usec   );




//#define __DEBUG__  


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
#define IMPORTANT_INFO(format,...) printf("%s["__FILE__",%s() Line:%05d,tid:%ld]:>>>IMPORTANT_INFO "format"",GetTime(),__FUNCTION__, __LINE__, pthread_self() ,##__VA_ARGS__)  
#define ERROR(format,...) printf("%s["__FILE__",%s() Line:%05d ,tid:%ld]:>>>>Err "format"",GetTime(),__FUNCTION__, __LINE__,pthread_self() , ##__VA_ARGS__)  

#ifdef __DEBUG__  
#define DEBUG(format,...) printf("%s["__FILE__",%s() Line:%05d,tid:%ld]: "format"",GetTime(),__FUNCTION__, __LINE__,pthread_self(), ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) printf("%s["__FILE__",%s() Line:%05d]:>>>>IMPORTANT_INFO  "format"",GetTime(),__FUNCTION__, __LINE__, ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) 
#else  
#define DEBUG(format,...)  
//#define ERROR(format,...) printf("%s["__FILE__",%s() Line:%05d]:>>>>Err  "format"",GetTime(),__FUNCTION__, __LINE__, ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) printf("%s["__FILE__",%s() Line:%05d]:>>>>IMPORTANT_INFO  "format"",GetTime(),__FUNCTION__, __LINE__, ##__VA_ARGS__)  
//#define IMPORTANT_INFO(format,...) 




#endif  

#ifdef __cplusplus

}

#endif
#endif  
