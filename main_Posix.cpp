#include "Posix.h"
#include<iostream>
using namespace std;

class test : public Posix
{
public:
	test()
	{
	 pthreadMutexInit();
	}
	~test()
	{
	 pthreadMutexDestroy();
	}	
	static int count;
public:
	void action()
	{
	 pthreadMutexLock();
	 cout<< pthread_self()<<"---->" << ++count <<endl;
	 pthreadMutexUnlock();
	}
};

int test::count = 0;

int main()
{
	test * mytest = new test();
	mytest->setThreadNumber(10);
	mytest->Run();
	return 0;
}
