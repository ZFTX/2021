#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "network.h"
using namespace std;

#define BUF_SIZE (4096)

int main(int argc,const char* argv[])
{
	if(3 != argc)
	{
		puts("User: ./client <ip> <port>");
		return 0;
	}

	NetWork* cnw = new NetWork(SOCK_STREAM,argv[1],atoi(argv[2]));
	if(!cnw->start())
	{
		delete cnw;
		return -1;
	}

	char* buf = new char[BUF_SIZE];
	for(;;)
	{
		cout << ">>>";
		cin >> buf;
		int ret = cnw->send(buf);
		if(0 >= ret || 0 == strcmp("quit",buf))
		{
			cout << "通信结束!" << endl;
			delete cnw;
			delete[] buf;
			return 0;
		}
		ret = cnw->recv(buf,BUF_SIZE);
		if(0 >= ret)
		{
			cout << "服务器正在升级" << endl;
			delete cnw;
			delete[] buf;
			return -1;
		}
		printf("recv:%s bits:%d\n",buf,ret);
	}
}
