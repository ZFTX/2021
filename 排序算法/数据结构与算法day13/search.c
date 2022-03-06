#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define LEN 10

#define SWAP(a,b) {typeof(a) t=(a);(a)=(b);(b)=t;}
#define show_arr(arr,len) {for(int i=0; i<len; printf("%d ",arr[i++]));printf("\n");}

//	顺序查找
int order_search(int* arr,int len,int key)
{
	for(int i=0; i<len; i++)
	{
		if(arr[i] == key)
			return i;
	}
	return -1;
}

//	排序
void sort(int* arr,int len)
{
	for(int i=0; i<len-1; i++)
	{
		for(int j=i+1; j<len; j++)
		{
			if(arr[i] > arr[j]) SWAP(arr[i],arr[j]);	
		}
	}
}

//	循环二分
int binary_search_for(const int* arr,int len,int key)
{
	int l = 0, r = len-1;
	while(l <= r)
	{
		int p = (l+r)/2;
		if(arr[p] == key) return p;

		if(arr[p] > key)
			r = p-1;
		else
			l = p+1;
	}
	return -1;
}

int _binary_search_recursion(int* arr,int l,int r,int key)
{
	if(l > r) return -1;
	int p = (l+r)/2;
	if(arr[p] == key)
		return p;
	if(key < arr[p])
		return _binary_search_recursion(arr,l,p-1,key);
	else
		return _binary_search_recursion(arr,p+1,r,key);
}
//	递归二分
int binary_search_recursion(int* arr,int len,int key)
{
	return _binary_search_recursion(arr,0,len-1,key);		
}

//	哈希查找
bool hash_search(int* arr,int len,int key)
{
	/*
	//	直接定址法
	//	创建哈希表
	int hash[1000] = {};

	//	标记
	for(int i=0; i<len; i++)
	{
		hash[arr[i]]++;	
	}
	//	查找
	return hash[key];
	*/
	int max = arr[0],min = arr[0];
	for(int i=1; i<len; i++)
	{
		if(arr[i] > max) max = arr[i];
		if(arr[i] < min) min = arr[i];
	}
	printf("%d %d\n",max,min);
	//	创建哈希表
	int hash[max-min+1];
	memset(hash,0,4*(max-min+1));
	//	标记
	for(int i=0; i<len; i++)
	{
		hash[arr[i]-min]++;	
	}
	return hash[key-min];
}

int main(int argc,const char* argv[])
{
	int arr[LEN] = {};
	for(int i=0; i<LEN; i++)
	{
		arr[i] = rand()%100;	
		printf("%d ",arr[i]);
	}
	printf("\norder_search:%d\n",order_search(arr,LEN,23));
	sort(arr,LEN);
	show_arr(arr,LEN);
	printf("binary_search_for:%d\n",binary_search_recursion(arr,LEN,2));
	printf("hash:%d\n",hash_search(arr,LEN,1));
}




