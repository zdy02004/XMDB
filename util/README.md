>**本模块主要收集了工具类功能**
* * *
*   log 下是常用打日志函数
*   cas_ring.h C 实现的基于 cas 的由循环数组构成的无锁队列。当队列为空时不阻塞。
*   cas_sleep_ring.h C 实现的基于cas 的由循环数组构成的无锁队列。当队列为空时阻塞线程。
*   cpp_thread_pool.h C++11 实现的线程池，其中的任务队列由基于 cas 和循环数组的无锁队列构成。
*   cpu_count.h 获取主机的 cpu 核数。
*   cthread_pool.h C 实现的线程池，其中的任务队列由基于 cas 的由循环数组构成的无锁队列构成。
*   file_entry_map.h (文件名,地址) 速查表，用于速查 mmap的文件名-》 内存映射地址
*   file_util.h redo C 实现的，重做机制用到的文件操作
*   func_task_t.hpp  C++11 实现的回调函数无锁队列，用于实现 exec_node的等待队列
*   mempool.h C 实现的小内存块内存池，分配函数上使用无锁链表实现。小于 65536字节的会基于他管理，大于 65536的 调用 libc 内存分配函数。
*   str_num_map.h  C 实现的（字符串，整数）速查表。
*   util_random.h  C 实现的随机数生成函数，用于跳表调用。从levelDB 的逻辑中移植。

