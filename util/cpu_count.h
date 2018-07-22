#if !defined (_WIN32) && !defined (_WIN64)  
#define LINUX  
#include <sys/sysinfo.h>  
#else  
#define WINDOWS  
#include <windows.h>  
#endif  
unsigned get_cput_core()  
{  
  unsigned count = 1; // 至少一个  
  #if defined (LINUX)  
  count = get_nprocs();   
  #elif defined (WINDOWS)  
  SYSTEM_INFO si;  
  GetSystemInfo(&si);  
  count = si.dwNumberOfProcessors;  
  #endif  
}
