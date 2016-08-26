#!/usr/bin/python 
# -*- coding: utf-8 -*-

L = ["edwar","asd","edward","asd"]
a = L[2:]
print a

L = range(100)
a = L[2:]
#print a

for a in L:
    a = a + 10

from collections import Iterable
print isinstance("abc",Iterable)


L = range(1,11)
L = []
for x in range(1,11):
    L.append(x*x)

print L

print [x * x for x in range(1,11)]

import os
print [d for d in os.listdir(".")]

x = "abc"
y = 123
print isinstance(x,str)
print isinstance(y,str)

def f(x):
    return x*x
print map(f,[1,2,3,4,5,6])

# 文件读写
try:
    f = open("./python_demo.py1",'r')
except:
    f = open("./python_demo.py","r")
    #print f.read()
finally:
    pass

for line in f.readlines():
 #   print(line.strip())
    pass


from collections import deque
q = deque(['a','b','c'])
q.append('x')
q.appendleft(y)
print q

#测试  socket
import socket
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(('www.sina.com.cn',80))
s.send("GET / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n")
#接收数据
buffer = []
while True:
    #每次最多接收1k字节
    d = s.recv(1024)
    if d:
        buffer.append(d)
    else:
        break
s.close()
data = "".join(buffer)
#print data
#将接收到的数据分离HTTP头部
header,html = data.split('\r\n\r\n',1)
print header

with open("sina.html","wb") as f:
    f.write(html)

#socket 服务器端编程
import threading,thread,time
def tcplink(sock,addr):
    print 'accept new connection from %s:%s' % addr
    sock.send("welcome!")
    while True:
        data = sock.recv(1024)
        time.sleep(1)
        if data == 'exit' or not data:
            break
        sock.send('hello, %s' % data)
    sock.close()
    print 'connection from %s:%s closed' % addr

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("127.0.0.1",9999))
s.listen(5)
#print("waiting for connection...")
#while True:
    #接受一个连接
#    sock,addr = s.accept()
    #创建新线程来处理TCP 连接
#    t = threading.Thread(target=tcplink,args=((sock,addr)))
#    t.start()

#SQLite 数据库
import sqlite3
#连接到SQLite 数据库
if not os.path.isfile("test.db"):
    conn = sqlite3.connect("test.db")
#创建一个cursor
    cursor = conn.cursor()
#执行一条SQL 语句，创建user表
    cursor.execute("create table user (id varchar(20) primary key,name varchar(20))")
    cursor.execute("insert into user(id,name) values(\'1\',\'edward\')")
    print cursor.rowcount
    cursor.close
    conn.commit()
    conn.close()
else:
    conn = sqlite3.connect("test.db")
    cursor = conn.cursor()
    cursor.execute("select * from user where id=?",("1",))
    values = cursor.fetchall()
    print values
    cursor.close()
    conn.close()

from wsgiref.simple_server import make_server
