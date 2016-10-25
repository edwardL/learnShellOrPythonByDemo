#include "basethread.h"
BaseThread::BaseThread()
{
 tid = 0;
 threadStatus = THREAD_STATUS_NEW;
}

bool BaseThread::start()
{
 int ret = 0;
 ret =pthread_create(&tid,NULL,thread_proxy_func,this);
 return (ret == 0);
}

pthread_t BaseThread::getThreadID()
{
	return tid;
}

int BaseThread::getState()
{
	return threadStatus;
}

void BaseThread::join()
{
 if(tid > 0)
 {
  pthread_join(tid,NULL);
  threadStatus=THREAD_STATUS_EXIT;
 }
}

void BaseThread::join(unsigned long millisTime)
{
 if(tid == 0)
 {
  return;
 }
 if(millisTime == 0)
 {
  join();
 }else{
 unsigned long k = 0;
 while(threadStatus != THREAD_STATUS_EXIT && k <= millisTime)
 {
   usleep(100);
   k++;
 }
 }
}

void* BaseThread::thread_proxy_func(void* args)
{
 BaseThread * thread = static_cast<BaseThread*>(args);
 thread->run();
 return NULL;
}

