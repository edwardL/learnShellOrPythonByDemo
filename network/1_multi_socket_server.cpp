#include<sys/socket.h>
#include<sys/types.h>
#include<iostream>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
using namespace std;

int main()
{
 // create new socket
 int socket_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
 
 // 通过结构体sockaddr_in 设置socket 连接属性
 struct sockaddr_in socket_addr;
 socket_addr.sin_family = AF_INET;
 socket_addr.sin_port = htons(5875);
 socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 
 if(bind(socket_fd,(struct sockaddr*)&socket_addr,sizeof(socket_addr)) == -1)
 {
  perror("bind");
  cout<<"bind socket error"<<endl;
  return 0;
 }

 if(listen(socket_fd,20) == -1)
 {
  cout<<"listen error " << endl;
  return 0;
 }
 
 char buffer[1023] = {0};
 
 struct sockaddr_in client_addr;
 socklen_t length = sizeof(struct sockaddr_in);
 int client_socket = accept(socket_fd,(struct sockaddr*)&client_addr,&length);
 if(client_socket == -1)
 {
  cout<<"accept error" <<endl;
  return 0;
 }

 while(1)
 {
  memset(buffer,0,sizeof(buffer) / sizeof(char));
  if(recv(client_socket,buffer,sizeof(buffer),0) == -1)
  {
    cout<<"recv error "<<endl;
    return 0;
  }
  if(send(client_socket,buffer,sizeof(buffer),0) == -1)
  {
   cout <<"send error" <<endl;
  }
  cout<<buffer<<endl;
 }
 close(client_socket);
 close(socket_fd);
 return 0;
}


