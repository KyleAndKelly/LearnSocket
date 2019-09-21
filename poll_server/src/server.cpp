#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<poll.h>
using namespace std;
#define POLLFD_SIZE 10//设定poll的监管套接字的最大数量
#define BACKLOG_SIZE 20//客户端连接队列的长度
#define RECV_BUFF_SIZE 80//设定好接收缓存区的大小
int main()
{
  //创建poll监管结构体数组
  struct pollfd pollfd_list[POLLFD_SIZE];
//创建监听套接字 并在监管结构体数组第零位设定

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
 pollfd_list[0].fd=lisfd;
  pollfd_list[0].events=POLLIN;

//创建读写套接字 在监管结构体数组后面位设定-1
for(int i=1;i<POLLFD_SIZE;i++)
{
   pollfd_list[i].fd=-1;
     pollfd_list[i].events=POLLIN;
}
//得到当前监管结构体数组中已监管的套接字中最大下标
int max_index=0;
//进入while循环
while(1)
{
  cout<<"poll start working...... "<<endl;
//poll开始工作

 int ret_val=poll(pollfd_list, max_index+1,9000 );
 if(ret_val==-1)//poll出错
 {
   cout<<"poll error!"<<endl;
   break;
 }
 else if(ret_val==0)//poll超时
 {
   cout<<"time out"<<endl;
   continue;
 }
else//poll 找到存在就绪的文件描述符
{
      int flag=0;
      if(pollfd_list[0].revents==POLLIN)//如果是监听套接字就绪
      {
        int i=1;
         for(;i<POLLFD_SIZE;i++)//找到一个空位
         {
           if(pollfd_list[i].fd==-1)//遍历找到一个空位
           {
            socklen_t servaaddr_len=sizeof(servaaddr);
            int iofd=accept(lisfd,(sockaddr*)&servaaddr,&servaaddr_len );//创建读写套接字
            if(iofd==-1)
            {
            cout<<"accept socket error"<<endl;
            close(iofd);
           continue;
            }
            else{//读写套接字加入监管结构体列表
                  pollfd_list[i].fd=iofd;
            pollfd_list[i].events=POLLIN;
            if(i>max_index){max_index=i;}
            break;
            }
          
            }

           }
           if(i==POLLFD_SIZE)
           {
             cout<<"cannot connect client more!.."<<endl;
           }
         }

      }

         for(int i=0;i<POLLFD_SIZE;i++)//如果是读写套接字就绪
          {
            if(pollfd_list[i].revents==POLLIN&&pollfd_list[i].fd!=-1)//找到读写就绪的套接字
            {
                     //读取数据recv
                    char recv_buffer[RECV_BUFF_SIZE];
                      int ret_val=recv(pollfd_list[i].fd,(void*)recv_buffer,RECV_BUFF_SIZE,0);
                      if(ret_val==-1)//读取失败
                     {
                      
                           cout<<"data read error from client:"<<pollfd_list[i].fd<<endl;
               
                      }
                      else if(ret_val==0)//客户端关闭
                      {
                          cout<<"client closed:"<<pollfd_list[i].fd<<endl;
                        pollfd_list[i].fd=-1;
                      
                         close( pollfd_list[i].fd);
                          continue;
                          
                      }
                      else//客户端有数据传过来了
                      {
                        
                            cout<<"data from client:"<<pollfd_list[i].fd<<endl;
                            cout<<recv_buffer<<endl;
                      }
               
                

            }
          }
        



}





  return 0;

}