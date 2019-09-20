#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
#define BACKLOG_SIZE 20//等待队列的长度
#define RECV_BUFF_SIZE 80//读写缓冲区的大小
int  iofd_tmp[10]={0};//存放已建立连接的读写套接字的数组
const int len=10;//最大可连接读写套接字的个数
int Max_num=0;//上面的数组中已建立连接的读写套接字数量


struct timeval select_time={10,0};
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

  //设置select的监管列表 把上面的监听套接字加入监管列表
   fd_set  readfd_list;
   FD_ZERO(&readfd_list);
    FD_SET(lisfd,&readfd_list);
  cout<<"select start working ......"<<endl;
   //进入while循环
   while(1)
   {
   //找出当前已有的套接字中最大的那个套接字
   int Max_iofd=lisfd;
   for(int i=0;i<Max_num;i++)
   {
     Max_iofd=iofd_tmp[i]>Max_iofd?iofd_tmp[i]:Max_iofd;
       
   }
 //select阻塞轮询 
 int ret=select(Max_iofd+1,&readfd_list,NULL,NULL,&select_time);
   //如果轮询结果是没有select出错了 返回-1
 
   if(ret==-1)
   {
       cout<<"select error"<<endl;
       close(lisfd);
       return -1;

   }
   //如果轮询结果是没有就绪的套接字导致超时  返回0
   else if(ret==0)
   {
       //cout<<"time out"<<endl;
       continue;
   }
   //如果轮询结果是有就绪套接字 返回就绪的套接字数量
   else
   {
       cout<<"get client request"<<endl;
       if(FD_ISSET(lisfd,&readfd_list)&&Max_num<len)//看监听套接字是否刻可读 即是否有连接上来了
       {
           socklen_t servaaddr_len=sizeof(servaaddr);
           int iofd=accept(lisfd,(sockaddr*)&servaaddr,&servaaddr_len );
           FD_SET(iofd,&readfd_list);//将创建的文件读写套接字加入监听列表
           for(int i=0;i<len;i++)//在读写套接字数组中找到一个零位置为套接字大小
           {
               if(iofd_tmp[i]==0){iofd_tmp[i]=iofd;}
           }
           Max_num++;
       }
    
       for(int i=0;i<len;i++) //看读写套接字上是否刻可读 即是否有数据发送到读写套接字上面了
       {
             if(iofd_tmp[i]!=0&&FD_ISSET(iofd_tmp[i],&readfd_list))//如果这个套接字上有可读数据 则读取
          {
                     //读取数据recv
                    char recv_buffer[RECV_BUFF_SIZE];
                      int ret_val=recv(iofd_tmp[i],(void*)recv_buffer,RECV_BUFF_SIZE,0);
                      if(ret_val==-1)
                     {
                           cout<<"data read error"<<endl;
                              close(iofd_tmp[i]);
                          iofd_tmp[i]=0;
                          FD_CLR(iofd_tmp[i],&readfd_list);
                          Max_num--;
               
                      }
                      else if(ret_val==0)
                      {
                          cout<<"client closed"<<endl;
                            close(iofd_tmp[i]);
                          iofd_tmp[i]=0;
                          FD_CLR(iofd_tmp[i],&readfd_list);
                          Max_num--;
                        
                      }
                      else
                      {
                            cout<<"data from client:"<<endl;
                            cout<<recv_buffer<<endl;
                      }
                      
                   
           
          }
       
   }
   

   }

}
   close(lisfd);
    return 0;

}
