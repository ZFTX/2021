#ifndef HOTEL_H
#define HOTEL_H

#include "tools.h"
#include "room.h"

class Hotel
{
	static Hotel hotel;	//	单例模式
	int level_cnt;		//	层数
	int* level_room;	//	每层房间数量	
	Room*** rooms;		//	房间类指针
	
	Hotel(void) {}		//	私有化构造函数

public:
	static Hotel& getHotel(void)	//	获取酒店对象的接口函数
	{
		return hotel;
	}
	void load(const char* path);	//	加载房间信息
	void business(void);	//	营业
	int menu(void);			//	菜单
	void in(void);			// 	入住
	void out(void);			//	退房
	void list(void);		//	显示空房间信息
	void query(void);		//	查询已入住房间、房客信息
	Room* find_room(short room_id);	//	找房间
};

#endif//HOTEL_H
