#include "tools.h"
#include <getch.h>

//	获取指令
char get_cmd(char start,char end)
{
	printf("请输入指令:");
	while(true)
	{
		char val = getch();
		if(start <= val && val <= end)
		{
			printf("%c\n",val);
			return val;	
		}
	}
}
