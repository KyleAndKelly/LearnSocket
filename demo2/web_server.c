#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <pthread.h>
#include "http.h"

#define BUFFER_SIZE 1024

//处理用户的连接的线程方法
void *handle(void *arg){
    int conn = *((int *)arg),i=0,j=0,len=0;
    char buffer[BUFFER_SIZE];
    char *buf = NULL;
    char temp[1024];
    int fp = -1;
    int count = 0;
    int flag = 0;
    //需要优化
    while(1){
            memset(buffer,0,sizeof(buffer));
            len = recv(conn, buffer, sizeof(buffer),0);
        if (buf == NULL) {
            buf = (char *)malloc(BUFFER_SIZE);
        }else {
            buf = (char *)realloc(buf, (i + 1)*BUFFER_SIZE);
        }
        for (j = 0; j < BUFFER_SIZE; j++) {
            buf[i*BUFFER_SIZE + j] = buffer[j];
            if(buffer[j]==13&&buffer[j+1]==10&&buffer[j+2]==13&&buffer[j+3]==10&&j<BUFFER_SIZE-4){
                flag = 1;
            }
        }
        if(flag)
            break;
        }
    printf("%s\n\n",buf);
    Request res = parseRequest(buf);
    free(buf);
    //处理请求文件  发送数据
    //发送状态码  (用字符串链接)
    len = strlen("HTTP/1.1 200 OK\r\nConnection: close\r\nAccept-Ranges: bytes\r\n")+1;
    buf = (char *)malloc(sizeof(char)*len);
    strcpy(buf,"HTTP/1.1 200 OK\r\nConnection: close\r\nAccept-Ranges: bytes\r\n");
    sprintf(temp,"Content-Type: %s\r\n", getFileType(res.file));
    len += strlen(temp);
    buf = (char *)realloc(buf,sizeof(char)*len);
    strcat(buf,temp);
    printf("filename: %s\n", res.file);
    printf("Content-Length: %d\n", getFileSize(res.file));
    sprintf(temp, "Content-Length: %d\r\n\r\n", getFileSize(res.file));
    len += strlen(temp);
    buf = (char *)realloc(buf,sizeof(char)*len);
    strcat(buf,temp);
    //二进制发送文件
    fp = open(res.file,O_RDONLY);
    while (1) {
        i = read(fp,temp,sizeof(temp));
        if (i <= 0)
            break;
        buf = (char *)realloc(buf,sizeof(char)*(len+i));
        memcpy(&buf[len], temp, i);
        len+=i;
    }
    close(fp);
    buf = (char *)realloc(buf,sizeof(char)*(len+4));
    memcpy(&buf[len], "\r\n", 2);
    send(conn, buf, (len+2), 0);
    printf("finish\n");
    close(conn);//关闭连接
}

int main(int argc,char *argv[]){
    struct sockaddr_in client_addr;     //获取客户机信息
    socklen_t length = sizeof(client_addr); //类型大小
    pthread_t *thread = NULL;       //处理事务线程
    int conn,*temp=NULL,err=0;
    int httpServerFd = socket(AF_INET,SOCK_STREAM,0);
    int   opt   =   1; 
    setsockopt(httpServerFd,   SOL_SOCKET,   SO_REUSEADDR, &opt, sizeof(int));
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(atoi(argv[1]));
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(httpServerFd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1){
        printf("绑定失败!\n");
        return 0;   
    }    
    ///listen，成功返回0，出错返回-1
    if(listen(httpServerFd,10) == -1){
        printf("监听失败!\n");
        return 0;   
    }

    while(1){
            ///成功返回非负描述字，出错返回-1
            conn = accept(httpServerFd, (struct sockaddr*)&client_addr, &length);
        if(conn==-1){
            printf("客户机连接出错!\n");
            return 0;
        }
        temp = (int *)malloc(sizeof(int));
        *temp = conn;
        thread = (pthread_t *)malloc(sizeof(pthread_t));
        err = pthread_create(thread,NULL,handle,(void *)temp);  
        if(err != 0 ){  
            printf("create thread fail\n");
        }  
    }

}
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
http.h
　　这个文件本想将http协议相关的东西进行封装下，做的时候发现需要实现的功能比较简单，所以只有一个请求头结构体，以及一个请求头的构造
#pragma once
typedef struct req {
    char *method;           //请求方式
    char *file;             //请求文件
    char *host;             //主机名称
    char *accept;           //请求文件类型
    char *accept_Language;  //请求语言
    char *accept_Encoding;  //客户端支持编码
    char *connection;       //链接状态
    char *user_Agent;       //用户环境
    //form表单 暂不处理
}Request;
Request parseRequest(char *buffer);     //根据请求头构造请求信息
1
2
3
4
5
6
7
8
9
10
11
12
13
http.c
#include "http.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
Request parseRequest(char * buffer)
{
    Request req;
    char *head = NULL,**line = NULL,*temp=NULL;
    int i = 0, line_count = 0,head_count=0,index=0;
    req.accept = NULL;
    req.accept_Encoding = NULL;
    req.accept_Language = NULL;
    req.connection = NULL;
    req.host = NULL;
    req.method = NULL;
    req.file = NULL;
    req.user_Agent = NULL;
    //按行解析请求头
    line_count = countChar(buffer, '\n');
    line = (char **)malloc(line_count*sizeof(char *));
    for (i = 0; i < line_count; i++)
        line[i] = NULL;
    temp = strtok(buffer, "\n");
    i = 0;
    while (temp) {
        line[i] = (char *)malloc((strlen(temp)+1)*sizeof(char));
        strcpy(line[i++], temp);
        temp = strtok(NULL, "\n");
    }
    for (i = 0; i < line_count&&line[i]!=NULL; i++) {
        head = strtok(line[i], " ");
        if (strcmp(head, "GET")==0) {       //获取请求文件  暂时不解析参数
            temp = strtok(NULL, " ");
            index = indexOfStrFirst(temp, '?');
            if(index!=-1)
                temp[index] = '\0';
            req.file = (char *)malloc((strlen("/var/www/html")+strlen(temp) + 1));
            printf("length:%d\n",(strlen(temp) + 1));
            sprintf(req.file,"/var/www/html%s", temp);
        }else if (strcmp(head, "POST")==0) {    //获取请求文件  暂时不解析参数
            temp = strtok(NULL, " ");
            index = indexOfStrFirst(temp, '?');
            if(index!=-1)
                temp[index] = '\0';
            req.file = (char *)malloc((strlen(temp) + 1));
            strcpy(req.file, temp);
        }else if (strcmp(head, "Host:")==0) {
            printf("FN:%s\n",req.file);
            printf("LN:%d\n",strlen(req.file));
            temp = strtok(NULL, " ");
            req.host = (char *)malloc((strlen(temp) + 1));
            strcpy(req.host, temp);
            printf("FN:%s\n",req.file);
            printf("LN:%d\n",strlen(req.file));
        }else if (strcmp(head, "User-Agent:")==0) {
            temp = strtok(NULL, " ");
            req.user_Agent = (char *)malloc((strlen(temp) + 1));
            strcpy(req.user_Agent, temp);
        }else if (strcmp(head, "Accept:")==0) {
            temp = strtok(NULL, " ");
            req.accept = (char *)malloc((strlen(temp) + 1));
            strcpy(req.accept, temp);
        }else if (strcmp(head, "Accept-Language:")==0) {
            temp = strtok(NULL, " ");
            req.accept_Language = (char *)malloc((strlen(temp) + 1));
            strcpy(req.accept_Language, temp);
        }else if (strcmp(head, "Accept-Encoding:")==0) {
            temp = strtok(NULL, " ");
            req.accept_Encoding = (char *)malloc((strlen(temp) + 1));
            strcpy(req.accept_Encoding, temp);
        }else if (strcmp(head, "Connection:")==0) {
            temp = strtok(NULL, " ");
            req.connection= (char *)malloc((strlen(temp) + 1));
            strcpy(req.connection, temp);
        }
    }
    return req;
}
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
util.h
　　这个文件里面是一些工具方法
#pragma once
int countChar(char *str, char c); //统计一串字符串中某个字符的个数
int indexOfStrFirst(char *str, char c); //查询字符首次出现的位置
char *getFileType(const char *filename);    //获取对应的HTML的响应头的文件类型
int getFileSize(const char *filename);      //获取文件大小
1
2
3
4
5
util.c
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int countChar(char * str, char c)
{
    int i = 0,count=0;
    for(i=0;i<strlen(str);i++)
        if (str[i] == c)
            count++;
    return count;
}

int indexOfStrFirst(char * str, char c)
{
    int i = 0;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}
char *getFileType(const char *filename){ //根据扩展名返回文件类型描述  
    char sExt[32];
    const char *p_start = filename;
    memset(sExt, 0, sizeof(sExt));
    while (*p_start)
    {
        if (*p_start == '.')
        {
            p_start++;
            strncpy(sExt, p_start, sizeof(sExt));
            break;
        }
        p_start++;
    }

    if (strncmp(sExt, "bmp", 3) == 0)
        return "image/bmp";

    if (strncmp(sExt, "gif", 3) == 0)
        return "image/gif";

    if (strncmp(sExt, "ico", 3) == 0)
        return "image/x-icon";

    if (strncmp(sExt, "jpg", 3) == 0)
        return "image/jpeg";

    if (strncmp(sExt, "avi", 3) == 0)
        return "video/avi";

    if (strncmp(sExt, "css", 3) == 0)
        return "text/css";

    if (strncmp(sExt, "dll", 3) == 0)
        return "application/x-msdownload";

    if (strncmp(sExt, "exe", 3) == 0)
        return "application/x-msdownload";

    if (strncmp(sExt, "dtd", 3) == 0)
        return "text/xml";

    if (strncmp(sExt, "mp3", 3) == 0)
        return "audio/mp3";

    if (strncmp(sExt, "mpg", 3) == 0)
        return "video/mpg";

    if (strncmp(sExt, "png", 3) == 0)
        return "image/png";

    if (strncmp(sExt, "ppt", 3) == 0)
        return "application/vnd.ms-powerpoint";

    if (strncmp(sExt, "xls", 3) == 0)
        return "application/vnd.ms-excel";

    if (strncmp(sExt, "doc", 3) == 0)
        return "application/msword";

    if (strncmp(sExt, "mp4", 3) == 0)
        return "video/mpeg4";

    if (strncmp(sExt, "ppt", 3) == 0)
        return "application/x-ppt";

    if (strncmp(sExt, "wma", 3) == 0)
        return "audio/x-ms-wma";

    if (strncmp(sExt, "wmv", 3) == 0)
        return "video/x-ms-wmv";

    return "text/html";
}

int getFileSize(const char * filename)
{
    int fileSize = 0;
    FILE *fp = NULL;
    if (filename == NULL)
        return 0;
    //以二进制的形式读取
    fp = fopen(filename, "rb");
    if (fp == NULL)
        return 0;
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    fclose(fp);
    return fileSize;
}
--------------------- 
作者：JavaLitterBoy 
来源：CSDN 
原文：https://blog.csdn.net/g1418377085/article/details/76994218 
版权声明：本文为博主原创文章，转载请附上博文链接！
