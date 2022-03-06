#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "list_queue.h"

#define SWAP(a,b) {typeof(a) t=(a);(a)=(b);(b)=t;}
#define TYPE int
#define LEN 20

typedef void (*SortFP)(TYPE*,size_t);

void show_arr(TYPE* arr,size_t len)
{
	for(int i=0; i<len; printf("%d ",arr[i++]));
	printf("\n");
}

//	冒泡
void bubble_sort(TYPE* arr,size_t len)
{
	bool flag = true;
	for(int i=len-1; i>0 && flag; i--)
	{
		flag = false;
		for(int j=0; j<i; j++)
		{
			if(arr[j] > arr[j+1])	
			{
				SWAP(arr[j],arr[j+1]);
				flag = true;
			}
		}
	}
	printf("%s ",__func__);
}

//	选择排序
void select_sort(TYPE* arr,size_t len)
{
	for(int i=0; i<len-1; i++)
	{
		int min = i;
		for(int j=i+1; j<len; j++)
		{
			if(arr[j] < arr[min]) min = j;	
		}
		if(min != i) SWAP(arr[i],arr[min]);
	}
	printf("%s ",__func__);
}

// 	插入排序
void insert_sort(TYPE* arr,size_t len)
{
	for(int i=1,j=0; i<len; i++)
	{
		int val = arr[i];
		for(j=i; j>0 && arr[j-1]>val; j--)
		{
			arr[j] = arr[j-1];
		}
		if(j != i)	arr[j] = val;
	}
	printf("%s ",__func__);
}

//	希尔排序
void shell_sort(TYPE* arr,size_t len)
{
	for(int k=len/2; k>0; k/=2)
	{
		for(int i=k,j=0; i<len; i++)
		{
			int val = arr[i];
			for(j=i; j-k>=0 && arr[j-k] > val; j-=k)
			{
				arr[j] = arr[j-k];	
			}
			if(j != i) arr[j] = val;
		}
	}
	printf("%s ",__func__);
}

void _quick_sort(TYPE* arr,int left,int right)
{
	if(left >= right) return;

	//	计算标杆的下标
	int pi = (left+right)/2;
	//	备份标杆的值
	TYPE pv = arr[pi];
	//	备份左右标杆的下标
	int l = left,r = right;
/*	测试
	for(int i=left; i<=right; i++)
	{
		if(i == pi) printf("[%d] ",arr[i]);
		else printf("%d ",arr[i]);
	}
	printf("\n");
*/
	//	左右标杆相遇才停止
	while(l < r)
	{
		//	从标杆左边找比pv大的数
		while(l<pi && arr[l] <= pv) l++;
		//	如果l没有超过pi，说明在pi的左边找到了比pv大的值
		if(l<pi)
		{
			arr[pi] = arr[l];
			pi = l;
		}
		
		//	从标杆右边找比pv小的数
		while(r>pi && arr[r] >= pv) r--;
		//	r没超出范围，说明在右边找到比pv小的数
		if(r>pi)
		{
			arr[pi] = arr[r];
			pi = r;
		}
	}

	//	还原pv到pi
	arr[pi] = pv;
	if(pi-1 > left)  _quick_sort(arr,left,pi-1);
	if(right > pi+1) _quick_sort(arr,pi+1,right);
}

void quick_sort(TYPE* arr,size_t len)
{
	_quick_sort(arr,0,len-1);
	printf("%s ",__func__);
}

//	合并
void merge(TYPE* arr,int l,int p,int r,TYPE* temp)
{
	//	合并之前，左右部分各自有序
	//	l左部分最左 p左部分最右 p+1右部分最左 r右部分最右
	if(arr[p] <= arr[p+1]) return;

	int k = l, i = l, j = p+1;
	while(i<=p && j<=r)
	{
		//	左右部分最小值相比较
		if(arr[i] < arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	//	比完后，把剩下没比较过的放入temp末尾
	while(i <= p)	temp[k++] = arr[i++];
	while(j <= r)	temp[k++] = arr[j++];
	//	把temp的合并后数据赋值给arr
	memcpy(arr+l,temp+l,sizeof(TYPE)*(r-l+1));
}

//	拆分并合并
void _merge_sort(TYPE* arr,int l,int r,TYPE* temp)
{
	if(l >= r) return;
	int p = (l+r)/2;
	_merge_sort(arr,l,p,temp);
	_merge_sort(arr,p+1,r,temp);
	merge(arr,l,p,r,temp);
}

// 	归并排序
void merge_sort(TYPE* arr,size_t len)
{
	//	申请临时空间
	TYPE* temp = malloc(sizeof(TYPE)*len);
	_merge_sort(arr,0,len-1,temp);
	free(temp);
	printf("%s ",__func__);
}

//	归并排序的循环实现
void merge_sort_for(TYPE* arr,size_t len)
{
	TYPE* temp = malloc(sizeof(TYPE)*len);
	TYPE* p1 = arr, *p2 = temp;

	//	s是间隔的元素个数
	for(int s=1; s<len; s*=2)
	{
		for(int l=0; l<len; l+=s*2)
		{
			//	l是此次合并的左部分最左
			//	r是此次合并的右部分最右+1
			int r = (l+s*2)<len ? l+s*2 : len;
			//	p是右部分最左
			int p = (l+s)<len ? l+s: len;
			int k = l,i = l,j = p;
			while(i<p && j<r)
			{
				if(p1[i] <= p1[j])
					p2[k++] = p1[i++];
				else
					p2[k++] = p1[j++];
			}
			while(i<p) p2[k++] = p1[i++];
			while(j<r) p2[k++] = p1[j++];
		}
		//	把全部合并后的结果重新复制给arr
		memcpy(arr,temp,sizeof(TYPE)*len);
	}
	free(temp);
	printf("%s ",__func__);
}

//	从堆顶root下标开始调整成大根堆
void create_heap(TYPE* arr,size_t len,int root)
{	
	//	root下标
	if(root >= len) return;
	//	left左孩子下标 right右孩子下标
	int left = 2*root + 1;
	int right = 2*root + 2;
	create_heap(arr,len,left);
	create_heap(arr,len,right);
	if(right < len && arr[right] > arr[left])
		SWAP(arr[left],arr[right]);
	if(left < len && arr[left] > arr[root])
		SWAP(arr[left],arr[root]);
}

//	堆排序-递归
void heap_sort_recursion(TYPE* arr,size_t len)
{
	create_heap(arr,len,0);
	for(int i=len-1; i>0; i--)
	{
		SWAP(arr[0],arr[i]);
		create_heap(arr,i,0);
	}
	printf("%s ",__func__);
}

//	堆排序-循环实现
void heap_sort_for(TYPE* arr,size_t len)
{
	for(int i=len-1; i>0; i--)
	{
		int p = (i+1)/2-1;
		if(arr[i] > arr[p]) SWAP(arr[i],arr[p]);
	}

	for(int i=len-1; i>0; i--)
	{
		SWAP(arr[0],arr[i]);
		for(int j=i-1; j>0; j--)
		{
			int p = (j+1)/2-1;
			if(arr[j] > arr[p]) SWAP(arr[j],arr[p]);
		}
	}
	printf("%s ",__func__);
}

//	计数排序
void count_sort(TYPE* arr,size_t len)
{
	TYPE max = arr[0], min = arr[0];
	for(int i=1; i<len; i++)
	{
		if(arr[i] > max) max = arr[i];
		if(arr[i] < min) min = arr[i];
	}

	//	创建哈希表
	TYPE* temp = calloc(sizeof(TYPE),max-min+1);
	
	//	标记哈希表
	for(int i=0; i<len; i++)
	{
		temp[arr[i]-min]++;	
	}

	//	访问哈希表，还原数据
	for(int i=0,j=0; i<=max-min; i++)
	{
		while(temp[i]--) arr[j++] = i+min;
	}

	free(temp);
	printf("%s ",__func__);
}

//	cnt表示桶的数量  range是桶中数值的范围
void _bucket_sort(TYPE* arr,size_t len,int cnt,TYPE range)
{
	//	申请桶的内存
	//	start指向桶的首地址，end指向桶的末尾数据
	TYPE* bucket_start[cnt], *bucket_end[cnt];
	for(int i=0; i<cnt; i++)
	{
		//	数据可能都在一桶中
		bucket_start[i] = malloc(sizeof(TYPE)*len);
		bucket_end[i] = bucket_start[i];
	}

	//	处理数据，按照桶的范围把数据放入对应的桶中
	//  0-24 25-49 50-74 75-99
	for(int i=0; i<len; i++)
	{
		for(int j=0; j<cnt; j++)
		{
			if(j*range <= arr[i] && arr[i] < (j+1)*range)
			{
				*(bucket_end[j]) = arr[i];
				bucket_end[j]++;
			}
		}
	}

	//	对每个桶进行各自的排序
	for(int i=0; i<cnt; i++)
	{
		//	计算每个桶中元素的数量
		int size = bucket_end[i] - bucket_start[i];
		//	桶中有数据时，调用其他的排序函数
		if(1 < size)
			count_sort(bucket_start[i],size);
		//	把桶中已有序的数据，重新放入arr
		memcpy(arr,bucket_start[i],sizeof(TYPE)*size);
		arr += size;
		free(bucket_start[i]);
		bucket_start[i] = NULL;
		bucket_end[i] = NULL;
	}
}

//	桶排序
void bucket_sort(TYPE* arr,size_t len)
{
	_bucket_sort(arr,len,4,25);
	printf("%s ",__func__);
}

//	基数排序
void radix_sort(TYPE* arr,size_t len)
{
	ListQueue* queue[10] = {};
	for(int i=0; i<10; i++)
	{
		queue[i] = create_list_queue();	
	}

	//	循环次数由最大值的位数决定
	TYPE max = arr[0];
	for(int i=1; i<len; i++)
	{
		if(max < arr[i]) max = arr[i];	
	}

	for(int i=1,k=1; max/k > 0; k*=10,i++)
	{
		//	i是1表示处理个位，2表示处理十位....
		int mod = pow(10,i);
		int div = mod / 10;
		for(int j=0; j<len; j++)
		{
			//	计算每个数据的第i位的值
			char pos_num = arr[j]%mod/div;
			//	根据值，把数据存入对应的队列
			push_list_queue(queue[pos_num],arr[j]);
		}
		
		//	十个队列依次出队，返回给arr
		int index = 0;
		for(int j=0; j<10; j++)
		{
			while(!empty_list_queue(queue[j]))
			{
				arr[index++] = front_list_queue(queue[j]);
				pop_list_queue(queue[j]);
			}
		}
	}

	for(int i=0; i<10; i++)
	{
		destory_list_queue(queue[i]);	
	}
	printf("%s ",__func__);
}

int main(int argc,const char* argv[])
{
	SortFP sort[] = {bubble_sort,select_sort,insert_sort,shell_sort,quick_sort,merge_sort,merge_sort_for,heap_sort_recursion,heap_sort_for,count_sort,bucket_sort,radix_sort};
	TYPE arr[LEN] = {};

	for(int i=0; i<sizeof(sort)/sizeof(sort[0]); i++)
	{
		for(int j=0; j<LEN; j++)
		{
			arr[j] = rand()%100;
		}
		printf("-----------------------------\n");
		printf("排序前:\n");
		show_arr(arr,LEN);
		sort[i](arr,LEN);
		printf("排序后:\n");
		show_arr(arr,LEN);
	}


}




