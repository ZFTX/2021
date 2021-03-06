#include "principal.h"

char prc_pwd[7] = {};

int principal(void)
{
	relase_file_p();
	stdin->_IO_read_ptr = stdin->_IO_read_end;		
	if(strcmp(prc_pwd, "123456") == 0)//将校长密码初始化为123456,若登录时密码为123456则默认是初次登录，需要修改密码
	{	
		printf("首次登录请修改默认密码\n");		
		printf("请输入修改后的密码：\n");
		sfgets(prc_pwd, 7);
		if(strcmp(prc_pwd, "123456") != 0)//不允许修改后的密码和默认密码相同
		{
			printf("修改成功！\n");	
		}
		while(strcmp(prc_pwd, "123456") == 0)//如果修改后密码与初始化密码相同则需要重新输入
		{
			printf("修改后的密码不能和初始密码相同！请重新输入\n");
			sfgets(prc_pwd, 7);
		}
	}
	else if(strcmp(prc_pwd, "123456") != 0)//若登录时密码不是123456则认为已经登录过，不需要修改密码
	{
		char key[8] = {};
		printf("请输入登录密码：");
		get_pwd(key, 1, 8);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		if(strcmp(prc_pwd, key) == 0)//将输入的密码与存储的密码比较，相同则登录成功
		{
			show_msg("\n登录成功！", 1);
		}
		if(strcmp(prc_pwd, key) == 0)//将输入的密码与存储的密码比较，不同则登录失败
		{
			show_msg("\n密码错误！", 1);
			return 0;
		}
	}	
	while(true)
	{
		switch(menu_p())//显示校长菜单
		{
			case '1': modify_p();					
					break;//重置校长密码
			case '2': reset_tch();
					break;//重置教师密码
			case '3': add_tch();
					break;//添加教师
			case '4': del_tch();
					break;//删除教师
			case '5': show_ontch();
					break;//显示所有在职教师
			case '6':  show_notch();
					break;//显示所有离职教师
			case '7': unlock_tch();
					break;//解锁教师账号
			case 'q': perserve_file_t();return 0;//将更改保存到文件并退出
		}
	}
}
