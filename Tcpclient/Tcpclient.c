/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
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
connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
/*向服务器发送数据*/
write(sockfd, str, strlen(str));
/*读取服务器发过来的数据*/
n = read(sockfd, buf, MAXLINE);
printf("Response from server:\n");
/*在显示器显示数据*/
write(STDOUT_FILENO, buf, n);
/*关闭连接*/
close(sockfd);
return 0;
}
