#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <ctype.h>
int main(void)
{
    /*变量声明*/
	char buf[80];//数据接收缓存区
	struct sockaddr_in client_addr;//指向客户端发送方的套接字
	socklen_t client_len;//存储客户端发送方的缓存区大小
	char str[INET_ADDRSTRLEN];//存储转换后的字符串形式点分十进制ip
    /*创建套接字socket()*/

       int udp_server=socket(AF_INET,SOCK_DGRAM,0);//创建一个ipv4下udp协议的套接字
    /*绑定ip和端口bind()*/
        struct sockaddr_in udp_addr;//创建一个ipv4地址结构体
	bzero(&udp_addr,sizeof(udp_addr));//用bzero函数清零
	udp_addr.sin_family=AF_INET;//将结构体内的地址族设置为AF_INET
	udp_addr.sin_addr.s_addr=htonl(INADDR_ANY);//设置本机内任意一个网卡ip
	udp_addr.sin_port=htons(8000);//设置端口号为8000
	bind(udp_server,(struct sockaddr *) &udp_addr,sizeof(udp_addr));//绑定套接字和地址结构体
   	printf("开始监听...\n");

	while(1)
	{
    /*接收数据recvfrom()*/
	client_len = sizeof(client_addr);
	int n=recvfrom(udp_server,buf,80,0,(struct sockaddr *)&client_addr,&client_len);  
    /*处理数据*/
	printf("接收到来自 %s : %d 的请求\n",inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)),ntohs(client_addr.sin_port));
	for (int i = 0; i < n; i++)
		buf[i] = toupper(buf[i]);//把小写的字符转换成大写的字符
   /*响应数据sendto()*/
	n = sendto(udp_server, buf, n, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
	}

    /*关闭套接字close()*/
	close(udp_server);
	return(0);
}
