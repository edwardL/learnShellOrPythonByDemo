#ifndef SINGLETON_H
#define SINGLETON_H

#include "mutex_lock.h"
#include<iostream>
using namespace std;
class singleton
{
public:
	virtual ~singleton()
	{

	}

	static singleton* getInstance()
	{
	 MutexLockGuard lock(mutex);
	 if(NULL == instance_)
	 {
	   instance_ = new singleton();
	 }
	 return instance;
	}

	static singleton* getInstanceLessLock()
	{
	 if(NULL == instance_)
	 {
	  MutexLockGuard lock(mutex);
	  if(NULL == instance_)
	  {
	    instance_ = new singleton();
	  }
	 }
	 return instance_;
	}
private:
	singleton()
	{
	}

	static singleton* instance_;
	Mutex mutex;
};

#endif
