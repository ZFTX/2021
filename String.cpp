#include <iostream>
#include <string.h>
using namespace std;

class String
{
	char* str;
public:
	String(const char* str="")
	{
		this->str = new char[strlen(str)+1];
		strcpy(this->str,str);
	}
	String(const String& that)
	{
		str = new char[strlen(that.str)+1];
		strcpy(str,that.str);
	}
	~String(void)
	{
		delete[] str;
	}
	String& operator=(const String& that)
	{
		if(this != &that)
		{
			delete[] str;
			str = new char[strlen(that.str)+1];
			strcpy(str,that.str);
		}
		return *this;
	}

	void show(void)
	{
		cout << str << endl;	
	}
};

int main(int argc,const char* argv[])
{
	String str("hehehahaxixi");
	str.show();
	String str1 = str;
	str1.show();
	String str2;
	str2 = str;
	str2.show();
}
