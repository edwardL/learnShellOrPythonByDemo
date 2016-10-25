#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include<iostream>
#include<pthread.h>
using namespace std;
class BaseThread
{
private:
	// 当前线程的ID
	pthread_t tid;
	// 线程的状态
	int threadStatus;
	static void* thread_proxy_func(void * args);
public:
	static const int THREAD_STATUS_NEW = 0;
	static const int THREAD_STATUS_RUNNING = 1;
	static const int THREAD_STATUS_EXIT = -1;

	//构造函数
	BaseThread();

	// 线程的运行实体
	virtual void run()=0;

	// 开始执行线程
	bool start();

	// 获取线程ID
	pthread_t getThreadID();
	// 获取线程状态
	int getState();
	
	// 等待线程退出
	void join();
	void join(unsigned long millisTime);
};

class MultiThread : public BaseThread
{
public:
	void run()
	{
	 int number = 0;
  	 for(int i = 0; i < 10; i++)
 	 {
 	   cout << "current count is " << number++<<"-------";
	   cout << "pid is " << getpid() << " tid is " << getThreadID()<<endl;
	   sleep(1);
	 }
	}
};

#endif
