#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getch.h>

int main(int argc,const char* argv[])
{
	if(3 != argc)
	{
		printf("User: ./cp src dest ...\n");
		return 0;
	}

	int src = open(argv[1],O_RDONLY);
	if(0 > src)
	{
		printf("源文件不存在，请检查!\n");
		return 0;
	}

	int dest = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,0644);
	if(0 > dest)
	{
		printf("目标文件已存在，是否覆盖(y/n)?\n");
		char ch = getch();
		if('y' != ch && 'Y' != ch)
		{
			printf("停止拷贝!\n");
			close(src);
			return 0;
		}
		else
		{
			printf("开始拷贝!\n");
			dest = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
		}
	}
	
	char buf[4096] = {};
	int ret = 0;
	while(ret = read(src,buf,sizeof(buf)))
	{
		write(dest,buf,ret);	
	}
	close(src);
	close(dest);
}


