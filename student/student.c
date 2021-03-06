#include "student.h"
#include "tools_s.h"
#include "tools_t.h"

Student *stu = NULL;
int num_student = 0;

void student(void)
{
	FILE *frpst = fopen("student.txt", "a");
	num_student = ftell(frpst) / sizeof(Student);
	fclose(frpst);
	stu=calloc(STU_MAX, sizeof(Student));
	frpst=fopen("student.txt", "r"); //打开读取文件
	if(frpst == NULL)
	{
		perror("fopen");
		return;
	}
	fread(stu, sizeof(Student), STU_MAX, frpst);//用stu结构数组来接
	fclose(frpst);
	int id1;
	int *id2 = &id1;
	char stu_pwd[7];
	char pwd_first[7] = {"123456"};		//定义全局变量
	int i=0, k = 3;
	printf("请输入您的学号：\n");
	scanf("%d", &id1);
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存区
	for(i=0;i<num_student;i++)
	{	
		if(id1 == stu[i].id)//对比学号
		{
			if(!strcmp(stu[i].pwd, pwd_first))//对比密码是否为初始密码
			{
				printf("首次登录请修改默认密码\n");		
				printf("请输入修改后的密码：\n");
				while(strcmp(stu[i].pwd, pwd_first) == 0)//对比密码是否为初始密码,是进入循环
				{	
					char sp[8] = {};
					sfgets(sp,8);
					stdin->_IO_read_ptr = stdin->_IO_read_end;//清除缓存区
					if(strlen(sp) > 6)//判断密码输入长度，不能超过6位
					{
						printf("密码超过6位，重新输入\n");
						return;
					}
					if(strcmp(sp, pwd_first) != 0)//判断新输入密码是否和初始密码相同
					{
						modify_s(id2,sp);		//修改为新密码
						fwpst();
						return;	
					}
					puts("修改后的密码不能与初始密码相同，请重新输入：");
				}
			}	
			else
			{
				if(stu[i].is_lock == false)//判断账号是否上锁
				{
					while(k >= 0)		//判断错误输入次数，超过4次上锁
					{
						printf("输入密码:\n");
						get_pwd(stu_pwd, 1, 7);
						stdin->_IO_read_ptr = stdin->_IO_read_end;
						if(strlen(stu_pwd) > 6)//判断密码输入长度，不能超过6位
						{
							printf("密码超过6位，重新输入\n");
							break;
						}
						if(!strcmp(stu[i].pwd, stu_pwd))//对比密码是否正确
						{
							printf("\n密码正确\n");
							for(;;)//循环，进入学生界面
							{
								switch(menu_s())//调用学生菜单
								{
									case '1': find_score(id2);
										break;
									case '2': modify_s1(id2);
										break;
									case '3': show_stu1(id2);
										break;
									case 'q': fwpst();
										return;
								}
								anykey();
							}
						}
						else
						{
							printf("密码错误,重新输入,还有%d次机会\n", k);
							k--;
						}		
					}
					stu[i].is_lock = true;//四次错误后锁定学生账号
					printf("%s", stu[i].name);
					puts("账号被锁定，联系老师解锁");
					fwpst();//保存
					return;			
				}
				else
				{
					puts("账号已被锁定，联系老师解锁");
					return;
				}
			}
		}
	}
	if(i == num_student)
	{
		puts("学号不存在\n");
	}

}

