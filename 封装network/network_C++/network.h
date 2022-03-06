#ifndef NETWORK_H
#define NETWORK_H
#include <cstdio>
#include <netinet/in.h>

/*
struct 关键字可以省略
使用bool类型不需要加头文件
class 中成员的默认是private属性
struct 中成员的默认是public属性
如果定义了有参构造、则编译器不再自动生成无参构造
函数可以设置默认形参，但要靠右，必须在声明写
函数可以重载
如果局部标识符屏蔽全局标识符，:: 可以指定访问全局标识符
在构造函数中，可使用初始化列表
在成员函数中，成员变量可直接使用
void*，void*不能自动转换成其他类型，必须使用强制类型转换

*/
class NetWork
{
	int sock;			//	socket描述符
	int type;			//	协议类型
	sockaddr_in addr;	//	通信地址
	socklen_t addrlen;	//	通信地址结构体字节数
	bool is_svr;		//	是否是服务端

public:
	NetWork(void);
	NetWork(int type,const char* ip,short port,bool is_svr=false);
	~NetWork(void);

	bool start(void);
	NetWork* accept(void);
	int send(const char* buf,int flag=0);
	int send(const char* buf,size_t len,int flag=0);
	int recv(char* buf,size_t len,int flag=0);
};


#endif//NETWORK_H
