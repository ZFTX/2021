#include <stdio.h>
#include <mcheck.h>
#include "teacher.h"
#include "principal.h"
#include "student.h"
#include "tools.h"
 
int main(int argc, const char* argv[])
{
	mtrace();
	for(;;)
	{
		switch(menu())
		{
			case '1': student();
				break;
			case '2': teacher();
				break;
			case '3': principal();
				break;
			case 'q': 
				puts("您已退出学生管理系统");
			return 0;
			default:
				puts("输入错误，请重新输入！");
		}
		anykey_continue();	
	}
	muntrace();
}

