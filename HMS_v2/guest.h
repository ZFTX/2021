#ifndef GUEST_H
#define GUEST_H

#include "tools.h"

class Guest
{
	string name;
	char sex;
	string id;
public:
	Guest(const string& name="",char sex='m',const string& id=""):name(name),sex(sex),id(id) {}
	const string& getName(void)
	{
		return name;
	}
	char getSex(void)
	{
		return sex;
	}
	const string& getId(void)
	{
		return id;	
	}
	
	void setName(const string& name)
	{
		this->name = name;
	}
	void setSex(char sex)
	{
		this->sex = sex;
	}
	void setId(const string& id)
	{
		this->id = id;
	}
	
	void show(void)
	{
		cout << name << " " << sex << " " << id << endl;
	}
};

#endif//GUEST_H
