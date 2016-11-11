
/*************************************************
Author: xiongchuanliang
Description: I/O复用(异步阻塞)模式例子_客户端代码
编译命令:
Linux:
g++ -o tcpclientasynselect tcpclientasynselect.cpp -m64 -I./common
**************************************************/

// 客户端代码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initsock.h"
#include "common.h"

int main(int argc, char* argv[])
{	  
	 int sclient = 0;	//连接服务端的套接字
	 int flags =  0;	//fcntl返回标识
	 int recvbytes = 0; //服务端返回的数据长度
	 char recvData[MAXDATASIZE] = {0};	//保存服务端返回的数据
	
	 fd_set readset, writeset;	//用于select()函数	
	 int fp = 0;	 //文件句柄的
	 int selectMaxfd = 0; //fd_set集合中所有文件句柄的范围，即所有文件句柄的最大值加1，
	 int ret = 0;;

	 //取出传入参数
	 const size_t MaxLen = 500;
	 char  testMsg[MaxLen]={0};

	 if(argc < 3)
	 {		
	    printf("Usage:%s [ip address] [any string]\n",argv[0]);
		exit(EXIT_FAILURE);
	 }else{
		strncpy(testMsg,argv[2],strlen(argv[2]));		
		printf("Message: %s \n",testMsg);
	 }

	 //除了用open() 也可以用后面的方式打开文件：FILE * fpw = NULL;	fpw = fopen(...)  fp = fileno(fpw);
	 if( (fp = open("xcl.log",O_WRONLY|O_CREAT|O_TRUNC,0640)) < 0) 
	 {
		 perror("open() failed\n");
		 exit(EXIT_FAILURE);
	 }	

	//建立套接字
	sclient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		PrintError("invalid() failed");
		exit(EXIT_FAILURE);
	}

	//指定要连接的服务器地址和端口
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVPORT);
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);	//用户输入的ip参数		
	memset(&(server_addr.sin_zero),0,8);

	//设为非阻塞模式
	 flags = fcntl(sclient, F_GETFL, 0);
	 fcntl(sclient, flags|O_NONBLOCK);

	//将套接字连接上服务器
	if( connect(sclient,(struct sockaddr *)&server_addr,sizeof(struct sockaddr) ) == -1)
	{
		PrintError("connect() failed");
		exit(EXIT_FAILURE);
	}

	//I/O复用(异步阻塞)模式--发送数据到服务端
	if( send(sclient,testMsg,strlen(testMsg),0) == -1)
	{
		PrintError("connect() failed");
		exit(EXIT_FAILURE);
	}
	printf("send success!\n");

	//I/O复用(异步阻塞)模式--接收返回的数据	
	while(1)
	{
		int check_timeval = 5;		//轮询间隔
		struct timeval timeout={check_timeval,0}; //阻塞式select, 超时时间.  timeval{一个是秒数，另一个是毫秒数}

		FD_ZERO(&readset);		// 初始化,即将指定的文件句柄集清空
		FD_SET(sclient,&readset); //添加描述符至fd_set集合
		FD_ZERO(&writeset);
		FD_SET(fp,&writeset); //添加描述符至fd_set集合

		selectMaxfd = sclient > fp ? (sclient + 1) : (fp + 1); 

		ret = select(selectMaxfd,&readset,NULL,NULL,NULL); //阻塞模式
		//ret = select(selectMaxfd,&readset,NULL,NULL,&timeout); //阻塞模式
		switch( ret)
		{
		  case -1: //error 发生错误
		    PrintError("select() error\n");
			exit(EXIT_FAILURE);
			break;
		  case 0: //timeout 超时
		    printf("select() timeout\n");
			goto end;
			break;
		  default:
				if(FD_ISSET(sclient, &readset))  //测试sock是否可读，即是否网络上有数据
				{
					 //接收数据
					 recvbytes = recv(sclient,recvData,MAXDATASIZE, MSG_DONTWAIT); //非阻塞模式
					 if( recvbytes == 0)
					 {
						printf("recv() no data!\n");
					 }else if( recvbytes < 0){
						PrintError("recv() failed");
						exit(EXIT_FAILURE);
					 }else if(recvbytes > 0 ){
						recvData[recvbytes] = '\0';
						printf("recv:%s\n", recvData);
					 }
				}

				  if(FD_ISSET(fp, &writeset)) //>0表示可读写
				  {
					  //printf("fp writeset .....\n");
					  if(recvbytes > 0 ){	

						  printf("writeset= %s \n",recvData);
						  write(fp, recvData, strlen(recvData)+1); 
						  printf("fp writeset end.\n");
						  //关闭		
						  goto end;
					   }
										
				  }			
		}
	}

	end:
	//关闭文件句柄
	close(fp);

	//关闭套接字，结束此次TCP会话
	close(sclient);

	exit(EXIT_SUCCESS);
}


