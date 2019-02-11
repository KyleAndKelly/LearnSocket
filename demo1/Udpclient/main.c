/* udp client.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <ctype.h>

int main(int argc, char *argv[])
{

/*变量初始化*/
struct sockaddr_in servaddr;
int sockfd, n;
char buf[80];

/*创建套接字socket()*/
sockfd = socket(AF_INET, SOCK_DGRAM, 0);

/*设定ip和端口*/
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
servaddr.sin_port = htons(8000);

while (fgets(buf, 80, stdin) != NULL)
 {

/*发送数据sendto*/
n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

/*接收服务器的反馈recvfrom*/
n = recvfrom(sockfd, buf, 80, 0, NULL, 0);

/*在显示器上显示服务器发回的数据write*/
write(STDOUT_FILENO, buf, n);
}
/*关闭套接字close*/
close(sockfd);
return 0;
}
