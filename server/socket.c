//socket.c

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../address.h"

int fd[1024] = {0};
pthread_t tid;	//线程号

int InitNet()
{
	struct sockaddr_in server_addr;
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket");
	}

	int opt = 1;
	setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&server_addr, 0 ,sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(2222);
	server_addr.sin_addr.s_addr = inet_addr("192.168.1.111");
	int ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(-1 == ret)
	{
		perror("bind");
		exit(1);
	}
	ret = listen(sockfd,10);
	if(-1 == ret)
	{
		perror("listen");
		exit(1);
	}

	return sockfd;
}

void exit_client(int fd)
{
	printf("客户端%d下线\n", fd);
	close(fd);	//关闭TCP连接
	pthread_exit((void *)0);	//线程退出
}

void *client_handler(void *arg)	//线程函数
{
	Chat c;
	int fd = *(int *)arg;
	while(1)
	{
		int ret = recv(fd, &c, sizeof(c), 0);
		if (-1 == ret)
		{
			perror("recv");
		}
		switch(c.cmd)
		{
			case ADDINFO:
				add_info(&c);
				break;
			case DELINFO:
				delete_info(&c,fd);
				break;
			case UPDATEINFO:
				update_info(&c,fd);
				break;
			case SEARCHINFO:
				search_info(&c,fd);
				break;
			case SHOWINFO:
				show_info(fd);
				break;
			case EXIT:
				exit_client(fd);
				break;
		}
	}
}

void main_handler(int sockfd)
{
	struct sockaddr_in client_addr;	//保存客户端信息
	int i = 0;
	int length = sizeof(client_addr);
	while(1)
	{
		for (i = 0; i< 1024; i++)
		{
			if (0 == fd[i])
			{
				break;
			}
		}
		fd[i] = accept(sockfd, (struct sockaddr *)&client_addr, &length);	//接收客户端连接

		printf("接受客户端连接　%d\n", fd[i]);

		int ret = pthread_create(&tid, NULL, client_handler, &fd[i]);	//启动线程处理TCP连接（一个线程对应一个客户端）
		if (-1 == ret)
		{
			perror("pthread_create");
			exit(1);
		}
	}
}
