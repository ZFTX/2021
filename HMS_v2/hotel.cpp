#include <stdlib.h>
#include "hotel.h"

Hotel Hotel::hotel;

void Hotel::load(const char* path)	//	加载房间信息
{
	FILE* frp = fopen(path,"r");
	if(NULL == frp)
	{
		perror("fopen");
		return;
	}
	fscanf(frp,"%d",&level_cnt);
	level_room = new int[level_cnt];
	rooms = new Room**[level_cnt];
	
	for(int i=0; i<level_cnt; i++)
	{
		fscanf(frp,"%d",&level_room[i]);
		rooms[i] = new Room*[level_room[i]];
		for(int j=0; j<level_room[i]; j++)
		{
			char type;short id;float price;
			fscanf(frp,"%hd %hhd %f",&id,&type,&price);
			rooms[i][j] = new Room(type,id,price);
		}
	}
}

void Hotel::business(void)	//	营业
{
	while(true)
	{
		switch(menu())
		{
			case '1':	in();	break;
			case '2':	out();	break;
			case '3':	list();	break;
			case '4':	query();break;
			case '5':	return;
		}
	}	
}

int Hotel::menu(void)		//	菜单
{
	system("clear");
	cout << "***欢迎使用指针酒店管理系统***" << endl;
	cout << "1、入住			2、退房" << endl;
	cout << "3、查看	 	    4、查询" << endl;
	cout << "5、退出" << endl;
	return get_cmd('1','5');
	
}

void Hotel::in(void)			// 	入住
{
	string name,id;
	char sex;
	cout << "请输入入住旅客的姓名、性别、身份证号：";
	cin >> name >> sex >> id;
	Guest* guest = new Guest(name,sex,id);
	
	short room_id;
	cout << "请输入要入住的房间号：";
	cin >> room_id;
	Room* room = find_room(room_id);
	if(NULL == room)
	{
		cout << "未找到该房间，请检查!"	 << endl;
		return;
	}
	
	if(room->in(guest))
		cout << "入住成功" << endl;
	else
		cout << "房间已满" << endl;
	
}

void Hotel::out(void)			//	退房
{
	cout << __func__ << endl;
}

void Hotel::list(void)		//	显示空房间信息
{
	cout << __func__ << endl;
}

void Hotel::query(void)		//	查询已入住房间、房客信息
{
	cout << __func__ << endl;
}

Room* Hotel::find_room(short room_id)	//	找房间
{
	for(int i=0; i<level_cnt; i++)
	{
		for(int j=0; j<level_room[i]; j++)
		{
			if(rooms[i][j]->getId() == room_id)
			{
				return rooms[i][j];
			}
		}
	}
	return NULL;
}

