#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "initsock.h"
#include "common.h"

CInitSock initSock;

int main(int argc,char** argv)
{
  int n = 0;
  SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(sListen == INVALID_SOCKET)
  { 
   PrintError("socket() failed.\n");
   exit(EXIT_FAILURE);
  }

  // 绑定本地端口
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVPORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(server_addr.sin_zero),8);

  int on = 1;
  setsockopt(sListen,SOL_SOCKET,SO_REUSEADDR,(const char*)&on,sizeof(on));

  if(bind(sListen,(struct sockaddr*)&server_addr,sizeof(struct sockaddr)) == SOCKET_ERROR)
  {
    PrintError("bind() failed.");
    exit(EXIT_FAILURE);
  }
  //开始监听
  if(listen(sListen,BACKLOG) == SOCKET_ERROR)
  {
    PrintError("listen failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in remoteAddr;
  socklen_t nAddrlen = sizeof(struct sockaddr_in);

  // 循环接收数据
  while(1)
  {
   SOCKET sClient;
   printf("等待客户端连接中\n");
   sClient = accept(sListen,(struct sockaddr*)&remoteAddr,&nAddrlen);
   if(sClient == INVALID_SOCKET)
   {
    PrintError("accept failed");
    continue;
   }
   printf("接收到一个客户端连接:%s\n",inet_ntoa(remoteAddr.sin_addr));
  
   if((n= fork()) == 0)
   {
   char recvData[MAXDATASIZE] = {0};
   close(sListen);
   // 接收数据
   int recvbytes  = recv(sClient,recvData,MAXDATASIZE,0);
   if(recvbytes == 0)
   {
   printf("recv() no data\n");
   }else if(recvbytes < 0)
   {
    PrintError("recv() failed");
   }else if(recvbytes > 0)
   {
     recvData[recvbytes] = '\0';
     printf("收到信息:%s\n",recvData);
   }
   // 发送数据到客户端
   char* sendData = "客户端，hello";
   send(sClient,sendData,strlen(sendData),0);

   close(sClient);
   exit(EXIT_SUCCESS);
 
   }else if(n < 0)
   {
   printf("fork failed ! %s\n",strerror(errno));
   exit(EXIT_FAILURE);
   } 
   close(sClient);
  }
   exit(EXIT_SUCCESS);
}
