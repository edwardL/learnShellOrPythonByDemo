#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include<pthread.h>
#include<assert.h>
#include<errno.h>
#include<queue>
using namespace std;

class MutexLock
{
public:
  MutexLock():_holder(0)
  {
    int ret = pthread_mutex_init(&_mutex,NULL);
    assert(0 == ret);
  }
 
  ~MutexLock()
  {
    assert(0 == _holder);
    int ret = pthread_mutex_destroy(&_mutex);
    assert(0 == ret);
  }

protected:
  void Lock()
  {
    pthread_mutex_lock(&_mutex);
  }

  void Unlock()
  {
    _holder = 0;
    pthread_mutex_unlock(&_mutex);
  }

  pthread_mutex_t* getPthreadMutex()
  {
    return &_mutex;
  }

private:
 pthread_mutex_t _mutex;
 pid_t _holder;
};

class MutexLockGuard
{
public:
 explicit MutexLockGuard(MutexLock& mutex):mutex_(mutex)
 {
   mutex_.Lock();
 }
 ~MutexLockGuard()
 {
   mutex_.Unlock();
 }
private:
 MutexLock& mutex_;
};

template<typename T>
class BlockingQueue
{
public:
 BlockingQueue()
  :mutex_(),
  queue_()
  {
  }

  ~BlockingQueue()
  {

  }

  void put(const T& value)
  {
    MutexLockGuard lock(mutex_);
    queue_.push_back(x);
  }

  T take()
  {
   MutexLockGuard lock(mutex_);
   assert(!queue_.empty());
   T front(queue_.front());
   queue_.pop_front();  
   return front;
  }
private:
 mutable MutexLock mutex_;
 std::queue<T> queue_;
};


#endif
