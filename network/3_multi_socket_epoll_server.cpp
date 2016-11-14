#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "initsock.h"
#include "common.h"

#include <sys/epoll.h>

CInitSock initSock;

#define MAX_EVENTS 10

int do_use_fd(int client); // 与客户端交互
int setnonblocking(int sock);

int main(int argc,char** argv)
{
 int n = 0;
 SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
 if(sListen == INVALID_SOCKET)
 {
   PrintError("socket() failed\n");
   exit(EXIT_FAILURE);
 }

 // 绑定本地ip 和端口到套接字
 struct sockaddr_in server_addr;
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(SERVPORT);
 server_addr.sin_addr.s_addr = INADDR_ANY;
 
 bzero(&(server_addr.sin_zero),8);

 int on = 1;
 setsockopt(sListen,SOL_SOCKET,SO_REUSEADDR,(const char*)&on,sizeof(on));
 
 if(bind(sListen,(struct sockaddr*)&server_addr,sizeof(struct sockaddr)) == -1)
 {
   PrintError("bind() failed\n");
   exit(EXIT_FAILURE);
 }
 
 // 开始监听
 if(listen(sListen,BACKLOG) == SOCKET_ERROR)
 {
  PrintError("listen failed");
  exit(EXIT_FAILURE);
 }

 struct epoll_event ev, events[MAX_EVENTS];
 SOCKET conn_sock,nfds, epollfd;
 
 // 指定内核需要监听的描述数
 epollfd = epoll_create(10);
 
 if(epollfd == -1)
 {
  PrintError("epoll_create");
  exit(EXIT_FAILURE);
 }
 
 ev.events = EPOLLIN | EPOLLET;
 ev.data.fd = sListen;
 
 if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sListen,&ev) == -1)
 {
  PrintError("epoll_ctl: listensock");
  exit(EXIT_FAILURE);
 }
 
 socklen_t nAddrlen = sizeof(struct sockaddr_in);
 for(;;)
 { 
 nfds = epoll_wait(epollfd,events,MAX_EVENTS,-1);
 if(nfds == -1) {
 continue;
 }

 // 遍历发生了指定监听的时间的fd
 for(n = 0; n < nfds; ++n)
 {
  if(events[n].data.fd == sListen) {
   conn_sock = accept(sListen,(struct sockaddr*)&server_addr,&nAddrlen);
   if(conn_sock == -1)
   {
    PrintError("accept");
    continue;
   }
 // 将新连接设置为非阻塞
  setnonblocking(conn_sock);
 // 设置event 为监控读操作
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = conn_sock;
 // 将这个新设置的event 假如到epoll 的监听队列中
 if(epoll_ctl(epollfd,EPOLL_CTL_ADD, conn_sock,&ev) == -1)
  {
    PrintError("epoll_ctl: conn_sock");
  }
  } else {   // 如果不是slisten 的话表明不是有新的连接，而是有数据到来。
  do_use_fd(events[n].data.fd);  
  }
 }
 } // end of for

 close(sListen);
 close(epollfd);
 exit(EXIT_SUCCESS);
}

// 与客户端交互
int do_use_fd(int client)
{
 char recvData[MAXDATASIZE] = {0};
 int recvbytes = read(client,recvData,MAXDATASIZE);
 if(recvbytes == 0)
 {
   printf("read() no data");
 } else if(recvbytes < 0)
 {
   if(errno != EAGAIN) 
   {
     PrintError("read failed");
     close(client);
   }
 }else if(recvbytes > 0)
 {
  recvData[recvbytes] = '\0';
  printf("msg:%s\n",recvData);
  char sendData[MAXDATASIZE] = {0};
  strcpy(sendData,"hello client\n");
  int sendbytes = write(client,sendData,sizeof(sendData));
  if(sendbytes < 0)
  {
   PrintError("write failed");
   close(client);
  }else{
  printf("write success: %d\n",sendbytes);
  }

 }

}

// 设置套接字为不阻塞
int setnonblocking(int client)
{
  int flags= fcntl(client,F_GETFL,0);
  flags |= O_NONBLOCK;
  fcntl(client,F_SETFL,flags);
  return 0;
}
