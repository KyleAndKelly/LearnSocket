
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include<poll.h>
#include <stdlib.h>
#include<poll.h>
#include <string.h>

using namespace std;
#define POLLFD_SIZE 10//设定poll的监管套接字的最大数量
#define BACKLOG_SIZE 20//客户端连接队列的长度
#define RECV_BUFF_SIZE 80//设定好接收缓存区的大小
#define EPOLL_EVENT_SIZE 20 //epoll事件表的最大监听套接字个数
int main()
{
//创建监听套接字
struct sockaddr_in servaaddr;
  bzero(&servaaddr,sizeof(servaaddr));
  servaaddr.sin_family=AF_INET;
  servaaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaaddr.sin_port=htons(8000);
  int lisfd=socket(AF_INET,SOCK_STREAM,0);
  if(lisfd==-1)
  {cout<<"creat socket error!"<<endl; return -1;}
  if(bind(lisfd,( struct sockaddr *)&servaaddr,sizeof(servaaddr)))
  {cout<<"bind socket error!"<<endl; return -1;}
    if(listen(lisfd,BACKLOG_SIZE))
  {cout<<"listen socket error!"<<endl; return -1;}
//创建监听套接字对应的事件结构体
struct epoll_event lisfd_event;
lisfd_event.data.fd=lisfd;
lisfd_event.events=EPOLLIN|EPOLLET;//设置为边缘触发模式
//创建epoll事件表
int epoll_event_table=epoll_create(EPOLL_EVENT_SIZE);
//创建epoll就绪事件结构体数组 将epoll查询结果放在里面
epoll_event events_result[20];
//监听套接字加入epoll事件表
epoll_ctl(epoll_event_table,EPOLL_CTL_ADD,lisfd,&lisfd_event);

//while循环
while(1)
{
      //epoll开始工作查看有无就绪事件
      int ret_val=epoll_wait(epoll_event_table,events_result,20,3000);//events事件数组里面有三种 一种是监听套接字 一种是
      if(ret_val==0)//epoll超时
      {
        cout<<"timr out "<<endl;
        continue;
      }
      else if(ret_val==-1)//epoll出错
      {
        cout<<"epoll error"<<endl;
      }
      else//epoll查询到有就绪事件
      {
         for(int i=0;i<ret_val;i++)
       {
         if(events_result[i].data.fd==lisfd)//如果就绪的是监听套接字
         {
           socklen_t len=sizeof(servaaddr);
           int iofd=accept(lisfd,(sockaddr*)&servaaddr,&len);
           if(iofd==-1)
           {
             cout<<"accept error"<<endl;
             continue;
           }
           struct epoll_event io_event;
           io_event.data.fd=iofd;
           io_event.events=EPOLLIN|EPOLLET;//设置为边缘触发模式
           epoll_ctl(epoll_event_table,EPOLL_CTL_ADD,iofd,&io_event);

         }
     
         else if(events_result[i].events&EPOLLIN)//如果就绪的是其他读写套接字,且其事件为可读
         {
            
            char recv_buff[RECV_BUFF_SIZE];
            int ret=recv(events_result[i].data.fd,recv_buff,RECV_BUFF_SIZE,0);
            if(ret==-1)
            {
                  cout<<"read error"<<endl;
            }
            else if(ret==0)
            {
              cout<<"client closed "<<events_result[i].data.fd<<endl;
              close(events_result[i].data.fd);
              epoll_ctl(epoll_event_table,EPOLL_CTL_DEL,events_result[i].data.fd,NULL);
          
            }
            else
            {
              cout<<"data from client "<<events_result[i].data.fd<<endl;
              cout<<recv_buff<<endl;
            }
            
         }
         else
         {
           cout<<"something else happen"<<endl;
         }
         

          
         
       }
        

        
         
      }
      
}


  return 0;

}