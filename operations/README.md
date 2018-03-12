>**本模块主要基于C ++ 11 实现了执行类功能**
* * *
>基本实现
*   ops.hpp C++ 实现的普通内存表的全表带条件的scan, hash_index_scan.h  C 实现的hash索引的scan，skiplist_index_scan.h C 实现的跳表索引带范围的scan。
*   index_scan_Addr.hpp 索引扫描时只扫索引的实现。
*   physical_plan.hpp 物理执行计划（未完成）
*   physical_plan_node.hpp 物理执行节点（未完成）
*   func_help.hpp 基于stl实现常见的对stl容器的关系操作函数包括: 并，差，交，投影 map ,hash 内连接，hash 内semi 连接，内 anti 连接。过滤 filter，分组 group，去重 distinct 等。
*   execute_node.hpp C++11 实现的节点执行器，是sql执行器的任务执行组件。主要实现了then语法糖，达到类似 java 8中的 stream 的效果，可接收不同参数规格的指针函数或lambda，既可控制他们的执行顺序，又最大化他们在线程池中的并发。可以看做是带前继约束的 task 实现，也可以看做是 cpu hungry 函数的调度器。
