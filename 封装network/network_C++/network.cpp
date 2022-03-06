#include "network.h"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

NetWork::NetWork(void)
{
	addrlen = sizeof(addr);
	type = SOCK_STREAM;
	is_svr = true;
}

//	备份参数，完成通信地址结构初始化
NetWork::NetWork(int type,const char* ip,short port,bool is_svr):type(type),is_svr(is_svr)
{
	//	不可以在构造函数中创建socket，因为创建可能失败，但构造函数没有返回值
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	addrlen = sizeof(addr);
}

NetWork::~NetWork(void)
{
	close(sock);
}

//	创建socket 绑定 监听 连接
bool NetWork::start(void)
{
	//	创建socket
	sock = socket(AF_INET,type,0);
	if(0 > sock)
	{
		perror("socket");
		return false;
	}

	//	根据type和is_svr执行
	if(is_svr)
	{
		if(bind(sock,(sockaddr*)&addr,addrlen))	
		{
			perror("bind");
			return false;
		}
		if(SOCK_STREAM == type && listen(sock,50))
		{
			perror("listen");
			return false;
		}
	}
	else if(SOCK_STREAM == type && connect(sock,(sockaddr*)&addr,addrlen))
	{
		perror("connect");
		return false;
	}
	return true;
}

//	TCP服务端执行
NetWork* NetWork::accept(void)
{
	if(SOCK_STREAM != type || !is_svr)
	{
		puts("accept:只允许type是SOCK_STREAM且是服务端才能调用该函数\n");
		return NULL;
	}

	//	实例化一个NetWork
	NetWork* nw = new NetWork;	//调用无参构造，需要重载一个无参构造
	nw->sock = ::accept(sock,(sockaddr*)&nw->addr,&nw->addrlen);
	//需要调用全局的系统函数accept 要加::指定访问
	if(0 > nw->sock)
	{
		perror("accept");
		delete nw;
		return NULL;
	}
	return nw;
}

int NetWork::send(const char* buf,int flag)
{
	if(SOCK_STREAM == type)
		return ::send(sock,buf,strlen(buf)+1,flag);
	else
		return sendto(sock,buf,strlen(buf)+1,flag,(sockaddr*)&addr,addrlen);
}

int NetWork::send(const char* buf,size_t len,int flag)
{
	if(SOCK_STREAM == type)
		return ::send(sock,buf,len,flag);
	else
		return sendto(sock,buf,len,flag,(sockaddr*)&addr,addrlen);
}

int NetWork::recv(char* buf,size_t len,int flag)
{
	if(SOCK_STREAM == type)
		return ::recv(sock,buf,len,flag);
	else
		return recvfrom(sock,buf,len,flag,(sockaddr*)&addr,&addrlen);
}

