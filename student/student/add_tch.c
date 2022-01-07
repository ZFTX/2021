#include <stdio.h>
#include "tools.h"
int main()
{
	FILE *p =fopen("teacher.txt","a");
	Teacher tea = {"李a",'m',100100,"123456",0,0};
	fwrite(&tea,1,sizeof(Teacher),p);
}
