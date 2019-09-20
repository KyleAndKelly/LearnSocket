#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
#define BACKLOG_SIZE  20//设定listen等待队列的大小
#define RECV_BUFF_SIZE 80//设定接收缓存区的字节大小
int main()
{
  //创建地址结构体sockaddr_in
  struct sockaddr_in servaaddr;
  bzero(&servaaddr,sizeof(servaaddr));
  servaaddr.sin_family=AF_INET;
  servaaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaaddr.sin_port=htons(8000);
  //创建监听套接字socket
  int lisfd=socket(AF_INET,SOCK_STREAM,0);
  if(lisfd==-1)
  {cout<<"creat socket error!"<<endl; return -1;}
  //监听套接字绑定到地址上bind
  if(bind(lisfd,( struct sockaddr *)&servaaddr,sizeof(servaaddr)))
  {cout<<"bind socket error!"<<endl; return -1;}
  //开始在该地址上监听listen(设定连接队列, 客户端connect发起第一次握手就放入连接队列,等待accept从队列中取出处理连接,将服务器端变为被动监听 ,非阻塞)
    if(listen(lisfd,BACKLOG_SIZE))
  {cout<<"listen socket error!"<<endl; return -1;}
  //建立while循环
  while(1)
  {
      cout<<"waiting for client connection"<<endl;
        //从连接队列中取出客户端连接请求accept( 即向客户端回复第二次握手 ,同时创建数据传输套接字)
        socklen_t lisfd_addr_len=sizeof(servaaddr);
        int iofd=accept(lisfd,(struct sockaddr*)&servaaddr,&lisfd_addr_len);
        if(iofd==-1)
        {
            cout<<"accept socket error"<<endl;
            return -1;
        }
        //读取数据recv
        char recv_buffer[RECV_BUFF_SIZE];
        int ret_val=recv(iofd,(void*)recv_buffer,RECV_BUFF_SIZE,0);
        if(ret_val==-1)
        {
                cout<<"data read error"<<endl;
                return -1;   
               
         }
         cout<<"receve data  bytes:"<<ret_val<<endl;
         cout<<"data from client:"<<endl;
        cout<<recv_buffer<<endl;
        //发送数据send
        cout<<"now send data to client"<<endl;
        char* send_data="hello from server!";
        if(send(iofd,(void*)send_data,RECV_BUFF_SIZE,0)==-1)
        {
            cout<<"data send error"<<endl;
            return -1;
        }
        
        //关闭连接close
        close(iofd);

  }

    return 0;
}