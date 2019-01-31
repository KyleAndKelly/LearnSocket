/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLINE 80
#define SERV_PORT 8000
int main(void)
{
/*变量定义*/
struct sockaddr_in servaddr, cliaddr;
socklen_t cliaddr_len;
int listenfd, connfd;
char buf[MAXLINE];
char str[INET_ADDRSTRLEN];
int i, n;
/*创建套接字socket()*/
listenfd = socket(AF_INET, SOCK_STREAM, 0);
/*初始化地址结构体*/
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
/*给套接字绑定地址bind*/
bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
/*使套接字处于监听状态listen*/
listen(listenfd, 20);
printf("Accepting connections ...\n");
while (1) 
{
/*接受客户端的请求accept*/
cliaddr_len = sizeof(cliaddr);
connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
/*读取客户端发来的数据read*/
n = read(connfd, buf, MAXLINE);
/*处理客户端发来的数据*/
printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),ntohs(cliaddr.sin_port));
for (i = 0; i < n; i++)
{
  buf[i] = toupper(buf[i]);
}

/*向客户端发送请求write*/
write(connfd, buf, n);
/*关闭连接close*/
close(connfd);
}
}
