#include <stdio.h>

int main(int argc,const char* argv[])
{
	if(3 != argc)
	{
		printf("User: ./Cp src dest\n");
		return 0;
	}
	FILE* frp = fopen(argv[1],"r");
	if(NULL == frp)
	{
		perror("fopen");
		return 1;
	}

	FILE* fwp =  fopen(argv[2],"r");
	if(fwp)
	{
		printf("目标文件已存在，是否覆盖(y/n)?\n");
		char cmd = getchar();
		if('y' != cmd && 'Y' != cmd)
		{
			printf("停止拷贝\n");
			return 0;
		}
		fclose(fwp);
	}
	fwp = fopen(argv[2],"w");
	if(NULL == fwp)
	{
		perror("fopen");
		return 1;
	}

	char buf[1024] = {};

	int ret = 0;
	while(0 < (ret = fread(buf,1,sizeof(buf),frp)))
	{
		fwrite(buf,1,ret,fwp);	
	}
	fclose(frp);
	fclose(fwp);


}






