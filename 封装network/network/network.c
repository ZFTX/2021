#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "network.h"

//	分配内存、创建socket对象、初始化地址结构体、绑定、监听、连接
NetWork* init_nw(int type,short port,const char* ip,bool issvr)
{
	NetWork* nw = malloc(sizeof(NetWork));	
	nw->type = type;
	nw->issvr = issvr;
	nw->addrlen = sizeof(struct sockaddr_in);

	nw->sock_fd = socket(AF_INET,type,0);
	if(0 > nw->sock_fd)
	{
		perror("socket");
		free(nw);
		return NULL;
	}

	//	初始化地址结构体
	bzero(&nw->addr,nw->addrlen);
	nw->addr.sin_family = AF_INET;
	nw->addr.sin_port = htons(port);
	nw->addr.sin_addr.s_addr = inet_addr(ip);

	//	是服务端
	if(issvr)
	{
		if(bind(nw->sock_fd,(SP)&nw->addr,nw->addrlen))
		{
			perror("bind");
			free(nw);
			return NULL;
		}
		
		//	TCP服务端 监听
		if(SOCK_STREAM == nw->type && listen(nw->sock_fd,50))
		{
			perror("listen");
			free(nw);
			return NULL;
		}
	}
	//	客户端且TCP
	else if(SOCK_STREAM == nw->type)
	{
		if(connect(nw->sock_fd,(SP)&nw->addr,nw->addrlen))
		{
			perror("connect");
			free(nw);
			return NULL;
		}
	}
	return nw;
}

// 等待连接，前提：type是SOCK_STREAM且是服务端才能调用该函数
NetWork* accept_nw(NetWork* nw)
{
	if(SOCK_STREAM != nw->type || !nw->issvr)
	{
		printf("只有TCP协议的服务端才能调用本函数!\n");
		return NULL;
	}

	NetWork* cli_nw = malloc(sizeof(NetWork));
	cli_nw->type = SOCK_STREAM;
	cli_nw->addrlen = nw->addrlen;
	cli_nw->issvr = true;
	cli_nw->sock_fd = accept(nw->sock_fd,(SP)&(cli_nw->addr),&cli_nw->addrlen);
	if(0 > cli_nw->sock_fd)
	{
		free(cli_nw);
		perror("accept");
		return NULL;
	}
	return cli_nw;
}

//	具备send和sendto的功能
int send_nw(NetWork* nw,const void* buf,size_t len)
{
	if(SOCK_DGRAM == nw->type)
		return sendto(nw->sock_fd,buf,len,0,(SP)&(nw->addr),nw->addrlen);
	else
		return send(nw->sock_fd,buf,len,0);
}

//	具备recv和recvfrom的功能
int recv_nw(NetWork* nw,void* buf,size_t len)
{
	if(SOCK_DGRAM == nw->type)
		return recvfrom(nw->sock_fd,buf,len,0,(SP)&(nw->addr),&nw->addrlen);
	else
		return recv(nw->sock_fd,buf,len,0);
}

//	关闭socket且释放内存
void close_nw(NetWork* nw)
{
	close(nw->sock_fd);
	free(nw);
}

