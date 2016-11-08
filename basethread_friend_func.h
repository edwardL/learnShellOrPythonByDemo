#ifndef THREAD_H
#define THREAD_H

#include<iostream>
using namespace std;
#include<pthread.h>

class Thread
{
private:
	pthread_t tid;
	int threadStatus;

public:
	static const int THREAD_STATUS_NEW = 0;
	static const int THREAD_STATUS_RUNNING = 1;
	static const int THREAD_STATUS_EXIT = -1;

	Thread();
	virtual void run()=0;

	bool start();
	int getState();
	pthread_t getThreadID();

	void join();
	void join(unsigned long milliTime);
	friend void* thread_proxy_func(void* args);
};

class MultiThread : public Thread
{
public:
	void run()
	{
	int number = 0;
	for(int i=0; i < 10; i++)
	 {
	  cout << "current number is " << number++;
	  cout << "pid is "<<getpid() << "TID is " << getThreadID() << endl;
	 }

	}
};

#endif
