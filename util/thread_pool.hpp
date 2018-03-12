#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H
#include <memory> // shared_ptr 
#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <queue>
 
namespace thread_pool
{

 using Task = std::function<void()>;

//循环任务队列
template<typename T> 
class _queue 
{ 
    public: 
        _queue(){} 
       // ~_queue(){delete []pBase;} 

        bool IsEmpty()const {return queue.empty();} 
        void Push(T e); 
        size_t length();
        T Pop(); 
        std::mutex locker;
				std::queue<T> queue;
    private: 
        void Insert(T &e); 


}; 

template<typename T> 
void _queue<T>::Insert(T &e) 
{ 
queue.emplace(e);
} 

template<typename T> 
void _queue<T>::Push(T e) 
{ 
    Insert(e); 
} 

template<typename T> 
T _queue<T>::Pop() 
{ 
	T task {std::move(queue.front())};    // 取一个 task
	queue.pop();
  return task; 
} 

template<typename T> 
size_t _queue<T>::length() 
{ 
  return queue.size(); 
} 
 

//________________________________________
template<typename T> 
class worker
{
T * father;
std::thread _thread;
_queue<Task> * job_pool;
_queue<Task> jobs;
size_t _max_fetch;
std::atomic<bool> is_stop;
std::mutex mtx; // 局互斥锁.
std::condition_variable cv; // 全局条件变量.
	bool is_wait = 0;
public:
worker(int max_fetch,_queue<Task> * in_job_pool,T * _father):job_pool(in_job_pool),_max_fetch(max_fetch),father(_father),is_wait(0){
	is_stop.store(0);
_thread=std::thread (([this](){do_work();}));
		

	}

void do_work()
{
while(1)
{

if(is_stop.load())
	{
	  std::cout<<"is_stop();!"<<std::endl;

		father->active--;
   	return;
}
//if(is_stop)break;

    
	   while(!jobs.IsEmpty())
	   {
	   		//std::cout<<"do_work!"<<std::endl;
	   	(jobs.Pop())();
	   }
	    get_jobs();

}

}

//停止工作
void stop()
{
	is_stop.store(true);
	//is_stop = 1;
	 cv.notify_one();
	_thread.join();
}
//停止工作
void start()
{
	is_stop.store(false);
	//is_stop = 0;
}

void notify_one()
{
	if(is_wait==1)
	{
	cv.notify_one();
	father->active++;
	is_wait = 0;
  }
}

void get_jobs()
{
	//全局队列上锁
std::unique_lock<std::mutex> lck(job_pool->locker);

	
if(jobs.IsEmpty() && !job_pool->IsEmpty())
{
size_t i = 0;
_max_fetch = father->active.load();
//size_t max = (job_pool->length()/_max_fetch)>1?(job_pool->length()/_max_fetch):1; 
//size_t max = (job_pool->length()/(father->workers.size()))>1?(job_pool->length()/(father->workers.size())):1; 
int max =father->workers.size();//+(job_pool->length()/_max_fetch);
for(size_t i = 0;i<max&&!job_pool->IsEmpty();++i)
{
jobs.Push(job_pool->Pop());
}
return;
}

if(job_pool->IsEmpty() && jobs.IsEmpty())
	{
		std::cout<<"cv.wait!"<<std::endl;
		father->active--;
		is_wait= 1;
		cv.wait(lck, [this](){ return (!job_pool->IsEmpty())||(job_pool->IsEmpty() && is_stop.load()); });    // wait 直到有 task
	}

}

};


class task_executor{
	
	
   // 任务队列
   _queue<Task> task_pool;
   std::atomic<bool>  stop;
	 
public:
	// 线程池
  std::vector<worker<task_executor> * > workers;
  // 活跃线程数
	std::atomic<int>  active;
		task_executor(size_t size = 4)
		{
      stop.store(0);
      active.store(size);
			for(size_t i = 0; i< size; ++i){
				worker<task_executor> * _work = new worker<task_executor>(size,&task_pool,this);
				workers.emplace_back(_work);
           // thread_pool.emplace_back(
           // 	[this,_work](){
           // 		_work->do_work();
           // 		}
           // 	);    // push_back(std::thread{...})
        }
		}
	
	~task_executor(){
      // for(std::thread& thread : thread_pool){
      //     //thread.detach();      // 让线程“自生自灭”
      //     thread.join();        // 等待任务结束， 前提：线程一定会执行完
      // }
        for(auto _work : workers){
           delete _work;      // 让线程“自生自灭”
            //thread.join();        // 等待任务结束， 前提：线程一定会执行完
        }
    }
    // 停止任务提交
    void shutdown(){
    	stop.store(true);
    	 for(auto _worker : workers){
        _worker->stop();
        }
  }
    
    
     // 重启任务提交
  //  void restart(){
  //  	  //stop.store(false);
  //  	  stop = 0;
  //      for(work& worker : workers){
  //      worker->start();
  //  }

size_t get_waited()
{
	std::lock_guard<std::mutex> lock {task_pool.locker};
	return  task_pool.length();
}

     // 提交一个任务
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))> {
        if(stop.load()){    // stop == true ??
            throw std::runtime_error("task executor have closed commit.");
        }
        
        using ResType =  decltype(f(args...));    // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
        auto task = std::make_shared<std::packaged_task<ResType()>>(
                        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                );    // wtf !
        {    // 添加到全局任务队列
            std::lock_guard<std::mutex> lock {task_pool.locker};
            task_pool.Push([task](){   // push(Task{...})
                (*task)();
            });
        }
      
      for( auto _work : workers){
        _work->notify_one();    // 唤醒线程执行
      }
        
        std::future<ResType> future = task->get_future();
        return future;
    }
	

};

//___________________________________________________________

void f()
{
	  for(int i=0;i<1000;++i);
    //std::cout << "hello, f !" << std::endl;
}

struct G{
    int operator()(){
    		  for(int i=0;i<100000;++i);

      //  std::cout << "hello, g !" << std::endl;
        return 42;
    }
};

int test()
{
try{
    task_executor executor {4};
    
    for(int k = 0;k<200000;++k){
    std::future<void> ff = executor.commit(f);
    std::future<int> fg = executor.commit(G{});
    //	if(k>20000 && k%200 == 0)std::this_thread::sleep_for(std::chrono::seconds(1));

  //  std::future<std::string> fh = executor.commit([]()->std::string { std::cout << "hello, h !" << std::endl; return "hello,fh !";});
    
  }
    
    //ff.get();
    //std::cout << fg.get() << " " << fh.get() << std::endl;
    	
    //executor.restart();    // 重启任务
    //executor.commit(f).get();    //
     executor.shutdown();
   //  while(executor.active.load() == 0 && executor.get_waited() == 0 )
   //  {
   //  std::this_thread::sleep_for(std::chrono::seconds(1));
		// }
    std::cout << "end... " <<executor.active.load() <<std::endl;
    return 0;
}catch(std::exception& e){
    std::cout << "some unhappy happened... " << e.what() << std::endl;
}
}

}
#endif