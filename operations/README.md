>本模块主要基于C ++ 11 实现了操纵类功能。
* * *
>基本实现
*   实现了普通内存表的全表带条件的scan, hash索引的scan，跳表索引带范围的scan。
*   基于stl实现常见的对stl容器的关系操作函数 并，差，交，映射 MAP,hash内连接，hash内semi连接，内anti连接。过滤 filter，分组group，去重 distinct等。
*   节点执行器，exec_node ，主要实现了then语法糖，可接收不同参数规格的指针函数或lambda，既要控制他们的的执行顺序，又最大化他们在线程池中的并发。
    可以看做是带前继约束的 task 实现，也可以看做是重 cpu 的函数调度器。
