
/*************************************************
Author: xiongchuanliang
Description: Socket库的初始化及清理
			 Windows除定义头文件外还需要WSAStartup及WSACleanup套接字库
			 UNIX/Linux只需定义好头文件即可。
			 CInitSock类的做法参考自<<Windows-网络与通信程序设计>>
**************************************************/

#ifndef __INITSOCK_H__
#define __INITSOCK_H__

#include <stdio.h>
#include <string.h>

#if defined(WIN32) || defined(__cplusplus_winrt)  
	#include <winsock2.h>
	#pragma comment(lib,"ws2_32.lib")
	//#include <Windows.h>
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>  
	#include <fcntl.h> //同步非阻塞模型

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/socketvar.h>

	#include <sys/select.h>	//异步阻塞 select
	#include <sys/time.h>	
	#include <sys/stat.h>

#endif
//#include <Windows.h>
#include "common.h"

class CInitSock		
{
public:
	CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
	{
		#ifdef _MS_WINDOWS
			//初始化WS2_32.dll
			WSADATA wsaData;
			WORD sockVersion = MAKEWORD(minorVer, majorVer);
			if(WSAStartup(sockVersion, &wsaData) != 0)
			{
				printf("WSAStartup() failed.\n");		
				exit(EXIT_FAILURE);
			}
		#endif
	}
	~CInitSock()
	{	
		#ifdef _MS_WINDOWS	
			//解除与Socket库的绑定并且释放Socket库所占用的系统资源
			if(WSACleanup( )== SOCKET_ERROR)
			{
				printf("WSACleanup() failed.\n");
			}
		#endif
	}
};
#endif // __INITSOCK_H__
