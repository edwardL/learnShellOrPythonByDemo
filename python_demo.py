#!/usr/bin/python
# -*- coding: UTF-8 -*-
print "你好，世界"

if True:
    print "True"
else:
    print "False"

if True:
    print "true"
elif False:
    print "false"
else:
    print "else"

import sys; x = 'runoob'; sys.stdout.write(x + '\n')

count = 100 # 赋值整型变量
miles = 100.0 # 浮点型
name = "john" #字符串

print count
print miles
print name

a = b = c = 1
a , b , c = 1 , 2 , "edward"
print(a,b,c)

s = 'iloveyou'

print s[1:5]
print s[2:] + s[:3]

list = ['abcd',785,2.1,"edward"]
tinylist = [123,"123"]
print list
print list[0]
print list[1:3]
print list + tinylist

tuple = ("122","edward",120)
print tuple[0]
print tuple

dict = {}
dict["key"] = "value"
dict[1] = "1"

print dict["key"]
print dict[1]

if True:
    pass
else:
    print "not pass"

count = 0
while (count < 9):
    print "the count is:",count
    count = count + 1

for letter in "Python":
    print '当前字母：',letter
fruits = ["banana","apple","mango"]
for fruit in fruits:
    print '当前水果：',fruit

print "多线程demo"
import thread
import time
"""

def print_time(threadName,delay):
    count = 0
    while count <= 5:
        time.sleep(delay)
        count += 1
        print "%s: %s" % (threadName,time.ctime(time.time()))
"""
# create two thread
#try:
#    thread.start_new_thread(print_time,("Thread-1",2,))
#    thread.start_new_thread(print_time,("thread-2",3,))
#except:
#    print "error : unable to start threads"

#while 1:
#    pass


print "demo of threading -------------------------------------"
import threading
import time
exitFlag = 0
class myThread(threading.Thread):
    def __init__(self,threadID,name,counter):
        threading.Thread.__init__(self)
        self.threadid = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print "Starting "+ self.name
        print_time_func(self.name,self.counter,5)
        print "Exiting "+ self.name

def print_time_func(threadName,delay,counter):
    while counter:
        if exitFlag:
            thread.exit()
        time.sleep(delay)
        print "%s: %s" % (threadName,time.ctime(time.time()))
        counter -= 1

# create new thread
thread1 = myThread(1,"thread-1",1)
thread2 = myThread(2,"thread-2",2)

#thread1.start()
#thread2.start()
#print("Exiting main thread")

print "demo of thread lock-------------------------------"
import threading
import time

class MyThread(threading.Thread):
    def __init__(self,threadid,name,counter):
        threading.Thread.__init__(self)
        self.threadid = threadid
        self.name = name
        self.counter = counter
    def run(self):
        print "starting " + self.name
        threadLock.acquire()
        print_time_func(self.name,self.counter,3)
        threadLock.release()

threadLock = threading.Lock()
threads = []

thread1 = MyThread(1,"mythread-1",1)
thread2 = MyThread(2,"mythread-2",2)

#thread1.start()
#thread2.start()

threads.append(thread1)
threads.append(thread2)

#for t in threads:
#    t.join()
#print "Exiting Main Thread"

print "demo of python simple network programing"

import os,socket,thread,sys
import time

"""
        服务端基类， 
通过TCP 文本协议进行通信，重载
OnRecv 函数处理
"""

class BaseServer(object):
    def __init__(self):
        self.socket = None
        self.connect = None
        self.address = None
        self.recv_timeout = 5
        self.recv_buff_size = 1024
        
    def Init(self,ip,port):
        self.socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.socket.bind((ip,port))
        self.socket.listen(5)
        print "Server Init OK"
        sys.stderr.write("Server Init ok \n")

    def NetWorkFunc(self):
        print "Network func begin"
        while True:
            self.connection, self.address = self.socket.accept()
            try:
                self.connection.settimeout(self.recv_timeout)
                buf = self.connection.recv(self.recv_buff_size)
                self.OnRecv(buf)
            except socket.timeout:
                print "recv data time out"
            self.connection.close()

    def Run(self):
        try:
            thread.start_new_thread(NetWorkFunc,())
        except Exception,e:
            print "start network thread func error"

        while True:
            pass

    def OnRecv(self):
        pass

    def Start(self):
        pass
