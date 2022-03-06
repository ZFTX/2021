#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct NetWork
{
	int sock_fd;
	int type;
	struct sockaddr_in addr;
	socklen_t addrlen;
	bool issvr;
}NetWork;

typedef struct sockaddr* SP;

//	分配内存、创建socket对象、初始化地址结构体、绑定、监听、连接
NetWork* init_nw(int type,short port,const char* ip,bool issvr);

// 等待连接，前提：type是SOCK_STREAM且是服务端才能调用该函数
NetWork* accept_nw(NetWork* nw);

//	具备send和sendto的功能
int send_nw(NetWork* nw,const void* buf,size_t len);

//	具备recv和recvfrom的功能
int recv_nw(NetWork* nw,void* buf,size_t len);

//	关闭socket且释放内存
void close_nw(NetWork* nw);


#endif//NETWORK_H
