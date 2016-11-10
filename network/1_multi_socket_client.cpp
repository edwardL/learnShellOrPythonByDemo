#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

int main()
{
 int socket_fd = socket(AF_INET,SOCK_STREAM,0);
 
 struct sockaddr_in server_addr;
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(5875);
 server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
 if(connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
 {
  perror("connect error");
  cout << "connect error\n" << endl;
  return 0;
 }
 
 char readbuf[1024];
 char sendbuf[1024];
 
 while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
 {
 int ret = send(socket_fd,sendbuf,strlen(sendbuf),0);
 if(ret < 0)
 {
  perror("send error");
 }
 
 recv(socket_fd,readbuf,sizeof(readbuf),0);
 fputs(readbuf,stdout);
 memset(sendbuf,0,sizeof(sendbuf));
 memset(readbuf,0,sizeof(readbuf));
 
 }
 return 0;
}
