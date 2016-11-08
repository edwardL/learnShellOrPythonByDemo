#ifndef MUTEX_H
#define MUTEX_H

class Mutex
{
public:
 Mutex():holder_(0)
 {
  int ret = pthread_mutex_init(&mutex,NULL);
  assert(0 == ret);
 }
 ~Mutex()
 {
  assert(0 == holder_);
  int ret = pthread_mutex_destroy(&mutex);
  assert(0 == ret);
 }
protected:
 void lock()
 {
  pthread_mutex_lock(&mutex);
 }

 void unlock()
 {
  pthread_mutex_unlock(&mutex);
 }

 pthread_mutex_t* getThreadMutex()
 {
  return &mutex;
 }

private:
 pthread_mutex_t mutex;
 pid_t holder_;
};


#endif
