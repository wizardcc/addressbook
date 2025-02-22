//socket.c

#include<sys/types.h>
#include<sys/socket.h>

#include<stdlib.h>
#include<stdio.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include"../address.h"

int InitNet()
{
	struct sockaddr_in server_addr;//服务器信息
	int sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(2222);
	server_addr.sin_addr.s_addr = inet_addr("192.168.1.111");	//Nano地址
	
	int ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(-1 == ret)
	{
		perror("connect");
		exit(1);
	}
	return sockfd;
}
/*
 １．通知服务器下线
 ２．关闭ＴＣＰ连接
 ３．退出程序
*/
void exit_client(int fd)
{
	Chat c;
	c.cmd = EXIT;	//表示下线
	int ret = send(fd, &c, sizeof(c), 0);
	if(-1 == ret)
	{
		perror("send");
	}

	close(fd);

	exit(0);
}

/*添加信息*/
void add_info(int fd)
{
	Chat c;
	
	printf("请输入姓名和电话：\n");
	scanf("%s%s",c.name,c.tel);

	c.cmd = ADDINFO;
	int ret = send(fd, &c,sizeof(c), 0);
	if (-1 == ret)
	{
		perror("send");
	}

	printf("信息录入成功！\n");
	sleep(3);
}
/*查询函数*/
void search_info(int fd)
{
	Chat c;
	
	printf("请输入待查询姓名：\n");
	scanf("%s",c.name);

	c.cmd = SEARCHINFO;
	int ret = send(fd,&c,sizeof(c),0);
	if(-1 == ret)
	{
		perror("send");
	}
	while(1)//循环接收信息，所以必须用ｗｈｉｌｅ循环
	{
		memset(&c,0,sizeof(c));
		ret = recv(fd,&c,sizeof(c),0);
		if(-1 == ret)
		{
			perror("recv");
		}
		if(!strcmp(c.name,"bye")&& !strcmp(c.tel,"bye"))
		{
			break;
		}
		printf("\t\t姓名%s	电话%s\n",c.name,c.tel);
	}
	sleep(3);
}
/*删除信息*/
void delete_info(int fd)
{
	Chat c;
	
	printf("请输入待删除联系人姓名：\n");
	scanf("%s",c.name);
	//开始删除
	c.cmd = DELINFO;
	int ret = send(fd, &c,sizeof(c), 0);
	if (-1 == ret)
	{
		perror("send");
	}

	printf("信息删除成功！\n");
	sleep(3);
}
/*更改信息*/
void update_info(int fd)
{
	Chat c;
	//更改前查询
	printf("请输入待更改姓名：\n");
	scanf("%s",c.name);

	c.cmd = UPDATEINFO;
	int ret = send(fd,&c,sizeof(c),0);
	if(-1 == ret)
	{
		perror("send");
	}
	while(1)//循环接收信息，所以必须用ｗｈｉｌｅ循环
	{
		memset(&c,0,sizeof(c));
		ret = recv(fd,&c,sizeof(c),0);
		if(-1 == ret)
		{
			perror("recv");
		}
		if(!strcmp(c.name,"bye")&& !strcmp(c.tel,"bye"))
		{
			break;
		}
		printf("\t\t姓名%s	电话%s\n",c.name,c.tel);
	}
	memset(&c,0,sizeof(c));

	printf("请输入联系人更改后姓名和电话：\n");
	scanf("%s%s",c.name,c.tel);

	//c.cmd = UPDATEINFO;
	ret = send(fd, &c,sizeof(c), 0);
	if (-1 == ret)
	{
		perror("send");
	}

	printf("信息修改成功！\n");
	sleep(3);
}
/*显示信息*/
void show_info(int fd)
{
	Chat c;
	
	c.cmd = SHOWINFO;
	int ret = send(fd,&c,sizeof(c),0);
	if(-1 == ret)
	{
		perror("send");
	}
	while(1)//循环接收信息，所以必须用ｗｈｉｌｅ循环
	{
		memset(&c,0,sizeof(c));
		ret = recv(fd,&c,sizeof(c),0);
		if(-1 == ret)
		{
			perror("recv");
		}
		if(!strcmp(c.name,"bye")&& !strcmp(c.tel,"bye"))
		{
			break;
		}
		printf("\t\t姓名%s	电话%s\n",c.name,c.tel);
	}
	sleep(3);
}
