/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "error.h"
#define MAXLINE 80
#define SERV_PORT 8000
int main(int argc, char *argv[])
{
/*变量初始化*/
struct sockaddr_in servaddr;
char buf[MAXLINE];
int sockfd, n;
char *str;
if (argc != 2) {
fputs("usage: ./client message\n", stderr);
exit(1);
}
str = argv[1];

/*创建套接字*/
sockfd = socket(AF_INET, SOCK_STREAM, 0);
/*初始化地址结构体*/
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
servaddr.sin_port = htons(SERV_PORT);
/*连接服务器*/
int n1=connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
if(n1==-1)
    error_print("connect error");
/*向服务器发送数据*/
int n2=write(sockfd, str, strlen(str));
if(n2==-1)
    error_print("send error");
/*读取服务器发过来的数据*/
int n3 = read(sockfd, buf, MAXLINE);
if(n3==-1)
    error_print("read error");
printf("Response from server:\n");
/*在显示器显示数据*/
write(STDOUT_FILENO, buf, n);
/*关闭连接*/
close(sockfd);
return 0;
}
