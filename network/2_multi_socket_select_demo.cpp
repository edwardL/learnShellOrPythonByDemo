#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

void display_time(const char*str)
{
 int seconds;
 int second = time((time_t*)NULL);
 printf("%s,%d\n",str,second);
}

int main()
{
 fd_set readfds;
 struct timeval timeout;
 int ret;

 // 监控标准输入0,
 FD_ZERO(&readfds);
 FD_SET(STDIN_FILENO,&readfds);
 
 while(1)
 {
 timeout.tv_sec = 5; // 阻塞5 秒
 timeout.tv_usec = 0;
 
 display_time("\nbefore select\n");
 ret = select(1,&readfds,NULL,NULL,&timeout);
 
 display_time("\nafter select\n");

 switch(ret)
 {
 case 0:
	printf("no data in ten seconds. \n");
 	exit(EXIT_SUCCESS);
	break;
 case -1:
	perror("select");
	exit(EXIT_FAILURE);
	break;
 default:
	getchar();
	printf("data is available now.\n");
 }
 }
 return 0;
}
