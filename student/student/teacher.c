#include <stdio.h>
#include "teacher.h"

int teacher(void)
{
	if(log_on() == false)
	{
		return 0;
	}
	release_file();
	for(;;)
	{
		switch(menu_t())
		{
			case '0' : add_stu_key();break;//添加学生
			case '1' : add_stu_file();break;//导入学生
			case '2' : del_stu();break;//删除学生
			case '3' : find_stu();break;//查找学生
			case '4' : modify_stu();break;//修改学生信息
			case '5' : enter_score_key();break;//输入成绩
			case '6' : enter_score_file();break;//导入成绩
			case '7' : reset_stu();break;//重置学生密码
			case '8' : show_stu();break;//显示学生信息
			case '9' : unlock();break;//解锁
			case 'q' : preserve_file();return 0;
		}
	anykey_continue();
	}
}
