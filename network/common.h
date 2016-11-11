/*************************************************
Author: xiongchuanliang
Description: 公共模块定义
**************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if defined(WIN32) || defined(__cplusplus_winrt)  
	#ifndef _MS_WINDOWS
		#define _MS_WINDOWS
	#endif // _MS_WINDOWS

	#include <Windows.h>	

	typedef int					socklen_t;
#else
	#include <errno.h>
	#include <strings.h>
			
	typedef unsigned char       BYTE;
	typedef	int					SOCKET;		
	#define SOCKET_ERROR		-1
	#define INVALID_SOCKET		-1
#endif
	
	//Socket所使用的宏定义#define SERVPORT	3003 /* SOCKET端口号 */
	#define SERVPORT	5875 /* SOCKET端口号 */
	#define MAXDATASIZE    100  // 每次传输最大数据量
	#define BACKLOG		10	 /* 最大同时连接请求数 */

	//打印错误信息
    static void PrintError(const char* useMsg)
	{
		const size_t MaxLen = 500;
		char szMsg[MaxLen]={0};

		if(useMsg == NULL)
		{
			printf("ERROR: NULL POINT!\n");
			return;
		}

		#ifdef _MS_WINDOWS
			switch (WSAGetLastError()) 
			{
			case WSANOTINITIALISED:
			strcpy_s(szMsg,MaxLen,"A successful WSAStartup call must occur before using this function. ");
				break;
			case WSAENETDOWN:
			strcpy_s(szMsg,MaxLen,"The network subsystem has failed. ");
				break;
			case WSAEACCES:
			strcpy_s(szMsg,MaxLen,"The requested address is a broadcast address, \
								   but the appropriate flag was not set. Call setsockopt \
								   with the SO_BROADCAST parameter to allow the use of the broadcast address. ");
				break;
			case WSAEINVAL:
			strcpy_s(szMsg,MaxLen,"An unknown flag was specified, or MSG_OOB was specified \
								  for a socket with SO_OOBINLINE enabled. ");
				break;
			case WSAEINTR:
			strcpy_s(szMsg,MaxLen,"A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall. ");
				break;
			case WSAEINPROGRESS:
			strcpy_s(szMsg,MaxLen,"A blocking Windows Sockets 1.1 call is in progress, \
								  or the service provider is still processing a callback function. ");
				break;
			case WSAEFAULT:
			strcpy_s(szMsg,MaxLen,"The buf or to parameters are not part of the user\
								  address space, or the tolen parameter is too small. ");
				break;
			case WSAENETRESET:
			strcpy_s(szMsg,MaxLen,"The connection has been broken due to keep-alive activity \
								  detecting a failure while the operation was in progress. ");
				break;
			case WSAENOBUFS:
			strcpy_s(szMsg,MaxLen,"No buffer space is available. ");
				break;
			case WSAENOTCONN:
			strcpy_s(szMsg,MaxLen,"The socket is not connected (connection-oriented sockets only). ");
				break;
			case WSAENOTSOCK:
			strcpy_s(szMsg,MaxLen,"The descriptor is not a socket. ");
				break;
			case WSAEOPNOTSUPP:
			strcpy_s(szMsg,MaxLen,"MSG_OOB was specified, but the socket is not stream-style\
								  such as type SOCK_STREAM, OOB data is not supported in \
								  the communication domain associated with this socket, or the socket is \
								  unidirectional and supports only receive operations. ");
				break;
			case WSAESHUTDOWN:
			strcpy_s(szMsg,MaxLen,"The socket has been shut down; it is not possible to sendto on a socket \
								  after shutdown has been invoked with how set to SD_SEND or SD_BOTH. ");
				break;
			case WSAEWOULDBLOCK:
			strcpy_s(szMsg,MaxLen,"The socket is marked as nonblocking and the requested operation would block. ");
				break;
			case WSAEMSGSIZE:
			strcpy_s(szMsg,MaxLen,"The socket is message oriented, and the message is larger than the maximum \
								  supported by the underlying transport. ");
				break;
			case WSAEHOSTUNREACH:
			strcpy_s(szMsg,MaxLen,"The remote host cannot be reached from this host at this time. ");
				break;
			case WSAECONNABORTED:
			strcpy_s(szMsg,MaxLen,"The virtual circuit was terminated due to a time-out or other failure. \
								  The application should close the socket as it is no longer usable. ");
				break;
			case WSAECONNRESET:
			strcpy_s(szMsg,MaxLen,"The virtual circuit was reset by the remote side executing a hard or \
								  abortive close. For UPD sockets, the remote host was unable to deliver \
								  a previously sent UDP datagram and responded with a \"Port Unreachable\" ICMP packet. \
								  The application should close the socket as it is no longer usable. ");
				break;
			case WSAEADDRNOTAVAIL:
			strcpy_s(szMsg,MaxLen,"The remote address is not a valid address, for example, ADDR_ANY. ");
				break;
			case WSAEAFNOSUPPORT:
			strcpy_s(szMsg,MaxLen,"Addresses in the specified family cannot be used with this socket. ");
				break;
			case WSAEDESTADDRREQ:
			strcpy_s(szMsg,MaxLen,"A destination address is required. ");
				break;
			case WSAENETUNREACH:
			strcpy_s(szMsg,MaxLen,"The network cannot be reached from this host at this time. ");
				break;
			case WSAETIMEDOUT:
			strcpy_s(szMsg,MaxLen,"The connection has been dropped, because of a network failure\
								  or because the system on the other end went down without notice. ");
				break;
			default:
			strcpy_s(szMsg,MaxLen,"Unknown socket error. ");
			break;
			}
			printf("ERROR: %s\n %s\n", useMsg,szMsg);		
		#else		
			perror(useMsg);			
		#endif 				
	}

#endif // __COMMON_H__
