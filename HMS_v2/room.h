#ifndef ROOM_H
#define ROOM_H

#include "tools.h"
#include "guest.h"

class Room
{
	char type;	//	房型
	short id;	//	房号
	float price;//	房价
	Guest** guests;	//	房客指针数组
	int guest_cnt;	//	房客人数
public:
	Room(char type,short id,float price):type(type),id(id),price(price)
	{
		guests = new Guest*[type];
		guest_cnt = 0;
	}
	
	short getId(void)
	{
		return id;	
	}
	
	void setType(char type)
	{
		this->type = type;
	}
	void setId(char id)
	{
		this->id = id;
	}
	void setPrice(char price)
	{
		this->price = price;
	}
	
	//	入住
	bool in(Guest* guest)
	{
		if(guest_cnt >= type)
			return false;
		guests[guest_cnt++] = guest;
		return true;
	}
	
	void show(void)
	{
		printf("%hd %hhd %g\n",id,type,price);
		for(int i=0; i<guest_cnt; i++)
		{
			cout << "房客" << i+1 << ":";
			guests[i]->show();
		} 
	}
};

#endif//ROOM_H
