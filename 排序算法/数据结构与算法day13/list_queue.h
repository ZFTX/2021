#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int

typedef struct Node
{
	TYPE data;
	struct Node* next;
}Node;

//	设计链式队列
typedef struct ListQueue
{
	Node* front;	//	队头指针
	Node* rear;		//	队尾指针
	size_t cnt;		//	节点个数
}ListQueue;

//	创建
ListQueue* create_list_queue(void);

//	队空
bool empty_list_queue(ListQueue* queue);

//	入队
void push_list_queue(ListQueue* queue,TYPE data);

//	出队
bool pop_list_queue(ListQueue* queue);

//	队头
TYPE front_list_queue(ListQueue* queue);

//	队尾
TYPE rear_list_queue(ListQueue* queue);

//	数量
size_t size_list_queue(ListQueue* queue);

//	销毁
void destory_list_queue(ListQueue* queue);


#endif//LIST_QUEUE_H
