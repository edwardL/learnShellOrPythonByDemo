#ifndef POSIX_H_
#define POSIX_H_

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

using namespace std;

class Posix
{
public:
	Posix();
	int getThreadNumber(void); // 获取线程数量
	int pthreadMutexInit(void); // 初始化线程锁
	int pthreadMutexLock(void); // 加锁
	int pthreadMutexUnlock(void); // 解锁
	int pthreadMutexDestroy(void); // 销毁锁
	void setThreadNumber(int threadNumber); //设置开启线程数
	void Run();	// 所有线程开始执行
	virtual void action()=0; // 每个线程执行的内容,在子类中重写
	
protected:
	int threadNumber;
	//线程锁
	pthread_mutex_t mutex;
};


#endif
