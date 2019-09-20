#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
using namespace std;
#define RECV_BUFF_SIZE 80
int main()
{
    //设定要发送到哪个地址(地址结构体)
     struct sockaddr_in servaddr;
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
servaddr.sin_port=htons(8000);
    //创建套接字socket
    int iofd=socket(AF_INET,SOCK_STREAM,0);
    if(iofd==-1){
        cout<<"creat socket error"<<endl;
    }
 
    //请求连接connect
   if( connect(iofd,(sockaddr*)&servaddr,RECV_BUFF_SIZE))
   {
       cout<<"connect error"<<endl;
       return -1;
   }
        //发送数据send
        char *send_data="hello from client!";
        if(send(iofd,(void*)send_data,RECV_BUFF_SIZE,0)==-1)
        {
            cout<<"data send error"<<endl;
            return -1;
        }
       cout<<"connect success"<<endl;
       //读取数据recv
        char recv_buffer[RECV_BUFF_SIZE];
        if(recv(iofd,(void*)recv_buffer,RECV_BUFF_SIZE,0)==-1)
        {
                cout<<"data read error"<<endl;
                return -1;   
               
         }
         cout<<"data from server:"<<endl;
             cout<<recv_buffer<<endl;

        //关闭连接close
        close(iofd);


}