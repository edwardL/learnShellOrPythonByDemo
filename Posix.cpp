#include "Posix.h"
#include<iostream>
using namespace std;

Posix::Posix(){
  threadNumber = 8;
}

static void* actionRun(void* param)
{
	Posix* posix = static_cast<Posix*>(param);
	posix->action(); // 执行子类重写的虚函数
	return NULL;
}

int Posix::pthreadMutexInit(void)
{
	return pthread_mutex_init(&this->mutex,NULL);
}

int Posix::pthreadMutexLock(void)
{
	return pthread_mutex_lock(&this->mutex);
}

int Posix::pthreadMutexUnlock(void)
{
	return pthread_mutex_unlock(&this->mutex);
}

int Posix::pthreadMutexDestroy(void)
{
 	return pthread_mutex_destroy(&this->mutex);
}

int Posix::getThreadNumber(void)
{
	return this->threadNumber;
}

void Posix::setThreadNumber(int number)
{
	this->threadNumber = number;
}

void Posix::Run()
{
	pthread_t threads[this->threadNumber];
	for (int count = 0; count < this->threadNumber; count++)
	{
	  if(pthread_create(&threads[count],NULL,actionRun,this) != 0)
	  {
	    cerr << " 线程创建失败，线程号 = " << count << endl;
 	  }
	}
	for(int i = 0; i < this->threadNumber; i++)
	{
	   if(pthread_join(threads[i],NULL) != 0)
	   {
		cerr << "线程执行失败 , 线程号 = " << i << endl;
	   }
	}
}


