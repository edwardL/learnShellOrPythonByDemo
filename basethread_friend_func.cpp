#include "basethread_friend_func.h"

Thread::Thread()
{
 tid = 0;
 threadStatus = THREAD_STATUS_NEW;
}

bool Thread::start()
{
 int ret = 0; 
 ret = pthread_create(&tid,NULL,thread_proxy_func,this);
 return (ret == 0);
}

pthread_t Thread::getThreadID()
{
 return tid;
}

int Thread::getState()
{
 return threadStatus;
}

void Thread::join()
{
 if(tid > 0)
 {
  pthread_join(tid,NULL);
 }
}

void Thread::join(unsigned long millis)
{
 if(tid == 0)
 {
  return;
 }
 if(millis == 0)
 {
  join();
 }else{
 unsigned long k = 0;
 while(threadStatus != THREAD_STATUS_EXIT && k <= millis)
 {
  usleep(100);
  k++;
 }
 }
}

void* thread_proxy_func(void* args)
{
 Thread* thread = static_cast<Thread*>(args);
 thread->run();
 return NULL;
}

